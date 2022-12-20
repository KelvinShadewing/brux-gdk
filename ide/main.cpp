#include "editorwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QCommandLineParser>
#include <QFile>

#include <KLocalizedContext>
#include <KLocalizedString>
#include <KAboutData>
#include <KMessageBox>

#include <iostream>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	QString syntaxPath = getenv("HOME");
	syntaxPath += "/.local/share/org.kde.syntax-highlighting/syntax/brux.xml";
	QFile syntaxCheck{syntaxPath};

	if (!syntaxCheck.exists()) {
		KGuiItem yesButton("Yes", QString(), "yes.tooltip", "Clicking this will create the file \"$HOME/.local/share/org.kde.syntax-highlighting/syntax/brux.xml\".");
		KGuiItem noButton("No", QString(), "no.tooltip", "Clicking this will not create a syntax highlighting definition for BRUX.");

		auto genSyntaxDefinition = KMessageBox::questionTwoActions(0, "Generate syntax highlighting definitions?", "Syntax Highlighting", yesButton, noButton);

		if (genSyntaxDefinition == KMessageBox::PrimaryAction) {
			QFile syntaxDefinition{":/brux.xml"};
			if (!syntaxDefinition.exists()) KMessageBox::error(0, "Couldn't locate the syntax definition.", "ERROR: Missing file");
			else if (!QFile::copy(":/brux.xml", syntaxPath)) KMessageBox::error(0, "Couldn't copy the syntax definition.", "ERROR: Copy fail");
		}
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
	return a.exec();
}
