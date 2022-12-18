#include "editorwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QCommandLineParser>

#include <KLocalizedContext>
#include <KLocalizedString>
#include <KAboutData>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

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
