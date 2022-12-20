project('ide', 'cpp', version : '0.0.1', default_options : ['cpp_std=c++11'])

# Documentation: https://mesonbuild.com/Qt5-module.html
qt5 = import('qt5')
qt5dep = dependency('qt5', modules : ['Core', 'Widgets'], version : '>=5.12.0')
#kf5dep = meson.get_compiler('cpp').find_library('KF5CoreAddons')
kf5dep = dependency('KF5CoreAddons')
kf5xmldep = dependency('KF5XmlGui')
kf5translatedep = dependency('KF5I18n')
kf5syntaxdep = dependency('KF5SyntaxHighlighting')
kf5textdep = dependency('KF5TextEditor')
kf5partdep = dependency('KF5Parts')
tileddep = meson.get_compiler('cpp').find_library('tiled')
tilededitordep = meson.get_compiler('cpp').find_library('tilededitor')

included_directories = ['/usr/include/KF5/KCoreAddons', '/usr/include/KF5/KI18n', '/usr/include/KF5/KXmlGui', '/usr/include/KF5/KParts', '/usr/include/KF5/KSyntaxHighlighting', '/usr/include/KF5/KTextEditor', '/usr/include/tiled']
deparr = [qt5dep, kf5dep, kf5xmldep, kf5translatedep, kf5syntaxdep, kf5textdep, kf5partdep, tileddep, tilededitordep]

translations = qt5.compile_translations(ts_files : ['translations/ide_en_US.ts'], build_by_default : true)

generated_files = qt5.preprocess(
							qresources : ['resources.qrc'],
							moc_headers : ['editorwindow.h'],
							ui_files : ['ui/editorwindow.ui'],
							dependencies: deparr,
							include_directories: included_directories)

executable('ide',
		'main.cpp',
		'editorwindow.cpp',
		generated_files,
		dependencies : deparr,
		include_directories: included_directories,
		cpp_args : '-DVERSION="@0@"'.format(meson.project_version()))
