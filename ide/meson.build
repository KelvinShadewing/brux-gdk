project('ide', 'cpp', version : '0.0.2', default_options : ['cpp_std=c++17'])

# Documentation: https://mesonbuild.com/Qt5-module.html
fs = import('fs')
qt5 = import('qt5')
qt5dep = dependency('qt5', modules : ['Core', 'Widgets'], version : '>=5.12.0')
kf5dep = dependency('KF5CoreAddons', version : '>=5.78.0')
kf5xmldep = dependency('KF5XmlGui', version : '>=5.78.0')
kf5translatedep = dependency('KF5I18n', version : '>=5.78.0')
kf5syntaxdep = dependency('KF5SyntaxHighlighting', version : '>=5.78.0')
kf5textdep = dependency('KF5TextEditor', version : '>=5.78.0')
kf5partdep = dependency('KF5Parts', version : '>=5.78.0')

included_directories = ['/usr/include/KF5/KCoreAddons', '/usr/include/KF5/KI18n', '/usr/include/KF5/KXmlGui', '/usr/include/KF5/KParts', '/usr/include/KF5/KSyntaxHighlighting', '/usr/include/KF5/KTextEditor']
deparr = [qt5dep, kf5dep, kf5xmldep, kf5translatedep, kf5syntaxdep, kf5textdep, kf5partdep]

translations = qt5.compile_translations(ts_files : ['translations/ide_en_US.ts'], build_by_default : true)

generated_files = qt5.preprocess(
							qresources : ['resources.qrc'],
							moc_headers : ['editorwindow.hpp'],
							ui_files : ['ui/editorwindow.ui'],
							dependencies: deparr,
							include_directories: included_directories)

executable('ide',
		'main.cpp',
		'editorwindow.cpp',
		generated_files,
		dependencies : deparr,
		include_directories: included_directories,
		cpp_args : ['-DVERSION="@0@"'.format(meson.project_version()), '-Wno-deprecated-declarations']) # This is only here because of deprecated values in KF5.
