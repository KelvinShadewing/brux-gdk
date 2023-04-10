#include "editorwindow.hpp"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QCommandLineParser>
#include <QFile>
#include <QCryptographicHash>

#include <KLocalizedContext>
#include <KLocalizedString>
#include <KAboutData>
#include <KMessageBox>

#include <iostream>
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// Thanks StackOverflow, very cool!
// Only needed in main.cpp as editorwindow has no need for cryptographic hashes
QByteArray fileChecksum(QFile* file, QCryptographicHash::Algorithm hashAlgorithm) {
	if (file->exists() && file->open(QFile::ReadOnly)) {
		QCryptographicHash hash(hashAlgorithm);
		if (hash.addData(file)) {
			return hash.result();
		}
	}
	return QByteArray();
}

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	{
		QString syntaxPath = getenv("HOME");
		syntaxPath += "/.local/share/org.kde.syntax-highlighting/syntax/brux.xml";

		QString syntaxDirPath = getenv("HOME");
		syntaxDirPath += "/.local/share/org.kde.syntax-highlighting/";

		#ifdef __linux__
		QString mimePath = getenv("HOME");
		mimePath += "/.local/share/mime/packages/";
		#endif

		QDir(syntaxDirPath).mkpath(".");
		QDir(syntaxDirPath).mkpath("./syntax");

		QFile syntaxCheck{syntaxPath};
		QFile syntaxDefinition{":/brux.xml"};
		QByteArray syntaxUserDefinitionChecksum = fileChecksum(&syntaxCheck, QCryptographicHash::Algorithm::Sha512);
		QByteArray syntaxDefinitionChecksum = fileChecksum(&syntaxDefinition, QCryptographicHash::Algorithm::Sha512);

		QString word = "";
		QString extraDesc = "";
		if (!syntaxCheck.exists()) word = "Generate";
		else if (syntaxUserDefinitionChecksum != syntaxDefinitionChecksum) {
			word = "Update";
			extraDesc = "\n\nYou may be seeing this as you have either updated the BRUX IDE or modified the syntax definition file.";
		}

		if (word != "") {
			KGuiItem yesButton("Yes", QString(), word + "s the syntax highlighting definition and continues to the IDE", "Clicking this will create the file \"$HOME/.local/share/org.kde.syntax-highlighting/syntax/brux.xml\".");
			KGuiItem noButton("No", QString(), "Continues to the IDE without changes to syntax highlighting", "Clicking this will not change the syntax highlighting definition for BRUX.");

			auto genSyntaxDefinition = KMessageBox::questionYesNo(0, word + " syntax highlighting definitions?" + extraDesc + "\n\nThis will cover the following file extensions:\n*.nut\n*.brx", "Syntax Highlighting", yesButton, noButton);

			if (genSyntaxDefinition == KMessageBox::Yes) {
				QFile::remove(syntaxPath);
				if (!syntaxDefinition.exists()) KMessageBox::error(0, "Couldn't locate the syntax definition.", "ERROR: Missing file");
				else if (!QFile::copy(":/brux.xml", syntaxPath)) KMessageBox::error(0, "Couldn't copy the syntax definition.", "ERROR: Copy fail");
			}
		}

		#ifdef __linux__
		QFile mimeCheckBrux{mimePath + "/application-x-brux.xml"};
		QFile mimeCheckSquirrel{mimePath + "/text-x-squirrel.xml"};
		QFile mimeDefinitionBrux{":/application-x-brux.xml"};
		QFile mimeDefinitionSquirrel{":/application-x-brux.xml"};
		QByteArray mimeUserBruxDefinitionChecksum = fileChecksum(&mimeCheckBrux, QCryptographicHash::Algorithm::Sha512);
		QByteArray mimeUserSquirrelDefinitionChecksum = fileChecksum(&mimeCheckSquirrel, QCryptographicHash::Algorithm::Sha512);
		QByteArray mimeDefinitionBruxChecksum = fileChecksum(&mimeDefinitionBrux, QCryptographicHash::Algorithm::Sha512);
		QByteArray mimeDefinitionSquirrelChecksum = fileChecksum(&mimeDefinitionSquirrel, QCryptographicHash::Algorithm::Sha512);

		QString mimeWord = "";
		QString mimeDesc = "";
		if (!mimeDefinitionBrux.exists() && !mimeDefinitionSquirrel.exists()) mimeWord = "Generate";
		else if (mimeDefinitionBruxChecksum != mimeUserBruxDefinitionChecksum || mimeDefinitionSquirrelChecksum != mimeUserSquirrelDefinitionChecksum) {
			mimeWord = "Update";
			mimeDesc = "\n\nYou may be seeing this as you have either updated the BRUX IDE or modified the mimetype definition file(s).";
		}

		if (mimeWord != "") {
			KGuiItem yesButton("Yes", QString(), mimeWord + "s the syntax highlighting definition and continues to the IDE", "Clicking this will create the file \"$HOME/.local/share/org.kde.syntax-highlighting/syntax/brux.xml\".");
			KGuiItem noButton("No", QString(), "Continues to the IDE without changes to syntax highlighting", "Clicking this will not change the syntax highlighting definition for BRUX.");

			auto genSyntaxDefinition = KMessageBox::questionYesNo(0, mimeWord + " mimetype definitions?" + mimeDesc + "\n\
This will cover the following file extensions and their respective mimetypes:\n*.nut (text/x-squirrel)\n*.brx (application/x-brux)", "Syntax Highlighting", yesButton, noButton);

			if (genSyntaxDefinition == KMessageBox::Yes) {
				QString list[2] = {"application-x-brux", "text-x-squirrel"};
				if (mimeCheckBrux.exists()) QFile::remove(mimePath + "/application-x-brux.xml");
				if (mimeCheckSquirrel.exists()) QFile::remove(mimePath + "/text-x-squirrel.xml");
				for (QString string : list) {
					bool goodToCopy = true;
					if ((string == "application-x-brux" && !mimeDefinitionBrux.exists()) || (string == "text-x-squirrel" && !mimeDefinitionSquirrel.exists())) goodToCopy = false;

					if (goodToCopy) {
						std::cout << ":/" + string.toStdString() + ".xml" << "\n" << (mimePath + string + ".xml").toStdString() << std::endl;
						if (!QFile::copy(":/" + string + ".xml", (mimePath + string + ".xml"))) KMessageBox::error(0, "Couldn't copy the syntax definition.", "ERROR: Copy fail");
					}
					else {
						KMessageBox::error(0, "Couldn't locate the syntax definition.", "ERROR: Missing file");
					}
				}
				int returnValue = system("update-mime-database ~/.local/share/mime");
				if (returnValue != 0) {
					KMessageBox::error(0, "update-mime-database could not update the mime database.", "ERROR: Local mime database update failed.");
				}
			}
		}
		#endif
	}

	KAboutData aboutData(
		// The program name used internally.
		QStringLiteral("IDE"),
		// A displayable program name string.
		i18nc("@title", "BRUX IDE"),
		// The program version string.
		VERSION,
		// Short description of what the app does.
		i18n("IDE for the Brux game engine."),
		// The license this code is released under.
		KAboutLicense::File,
		// Copyright Statement.
		"");
	aboutData.setLicenseTextFile(":/LICENSE");
	aboutData.setDesktopFileName("ide");
	aboutData.addAuthor(i18nc("@info:credit", "Kelvin Shadewing"), i18nc("@info:credit", "Brux Developer"), QStringLiteral(""), QStringLiteral("https://kelvinshadewing.net"));
	aboutData.addAuthor(i18nc("@info:credit", "Tulip"), i18nc("@info:credit", "IDE Creator"), QStringLiteral(""), QStringLiteral("https://tulip-sudo.github.io"));
	aboutData.setBugAddress("https://github.com/KelvinShadewing/brux-gdk/issues");
	aboutData.setHomepage("https://github.com/KelvinShadewing/brux-gdk");

	KAboutData::setApplicationData(aboutData);

	QCommandLineParser Parser;
	Parser.addPositionalArgument("file", QCoreApplication::translate("main", "File or directory to open"));
	aboutData.setupCommandLine(&Parser);
	Parser.process(a);
	aboutData.processCommandLine(&Parser);

	QTranslator translator;
	const QStringList uiLanguages = QLocale::system().uiLanguages();
	for (const QString &locale : uiLanguages) {
		const QString baseName = "ide_" + QLocale(locale).name();
		if (translator.load(":/i18n/" + baseName)) {
			a.installTranslator(&translator);
			break;
		}
	}
	EditorWindow w;
	w.show();
	const QStringList args = Parser.positionalArguments();
	if (args.size() > 0) {
		if (!args.at(0).isEmpty()) {
			QString value = args.at(0);
			if (!value.contains("/")) value = QString(getenv("PWD")) + "/" + value;

			bool file = w.isFile(value);
			bool dir = w.isDirectory(value);

			// Determine what the argument is
			if (file) w.processFile(value, value.split("/").last());
			else if (dir) w.processDirectory(value, false);
			else std::cout << "Failed to process path" << std::endl;
		}
	}

	return a.exec();
}
