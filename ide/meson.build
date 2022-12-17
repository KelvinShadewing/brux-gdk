project('ide', 'cpp', default_options : ['cpp_std=c++11'])

# Documentation: https://mesonbuild.com/Qt5-module.html
qt5 = import('qt5')
qt5dep = dependency('qt5', modules : ['Core', 'Widgets'])
kf5dep = meson.get_compiler('cpp').find_library('KF5CoreAddons')
kf5syntaxdep = meson.get_compiler('cpp').find_library('KF5SyntaxHighlighting')
kf5textdep = meson.get_compiler('cpp').find_library('KF5TextEditor')
tileddep = meson.get_compiler('cpp').find_library('tiled')
tilededitordep = meson.get_compiler('cpp').find_library('tilededitor')

included_directories = ['/usr/include/KF5', '/usr/include/KF5/KXmlGui', '/usr/include/KF5/KParts', '/usr/include/KF5/KSyntaxHighlighting', '/usr/include/KF5/KTextEditor', '/usr/include/tiled']

translations = qt5.compile_translations(ts_files : ['translations/ide_en_US.ts'], build_by_default : true)

generated_files = qt5.preprocess(
							moc_headers : ['editorwindow.h'],
							ui_files : ['ui/editorwindow.ui'],
							dependencies: [qt5dep, kf5dep, kf5textdep],
							include_directories: included_directories)

executable('ide',
		'main.cpp',
		'editorwindow.cpp',
		generated_files,
		dependencies : [qt5dep, kf5dep, kf5textdep],
		include_directories: included_directories)
