project('brux-gdk', 'cpp', 'c', default_options: ['cpp_std=c++17', 'buildtype=release', 'default_library=static', 'prefix=/', 'bindir=', 'datadir='], meson_version: '>=1.0.1')

# CMake module. Needed for physfs and simplesquirrel modules.
cmake = import('cmake')

# Configure file
audio_backend = get_option('AUDIO_BACKEND')

config_dat = configuration_data()
config_dat.set('AUDIO_BACKEND', audio_backend)
config_dat.set('USE_FASTFILL', get_option('USE_FASTFILL'))

configure_file(input: 'src/config.hpp.in', output: 'config.hpp', configuration: config_dat)

# Dependencies
sdl = dependency('SDL2', fallback: ['sdl2'])
sdl_image = dependency('SDL2_image', fallback: ['sdl2_image'])
sdl_net = dependency('SDL2_net', fallback: ['sdl2_net'])

## TODO: Perhaps this should be removed or remade internally to reduce on an external dependency?
sdl_gfx = dependency('SDL2_gfx', fallback: ['sdl2_gfx'])

## Audio dependency/backend handling
audio_lib = []

if (audio_backend == 'sdl2')
	audio_lib = dependency('SDL2_mixer', fallback: ['sdl2_mixer'], required: false)
endif

## Other dependencies
curl = dependency('curl', required: false)

if (not curl.found())
	curl = dependency('libcurl', required: true)
endif

git2 = dependency('libgit2')

physfs = dependency('physfs', required: false)

if (not physfs.found())
	physfs_proj = cmake.subproject('physfs')

	physfs_lib = physfs_proj.get_variable('physfs')
	physfs = declare_dependency(link_with: physfs_lib, include_directories: physfs_proj.include_directories('physfs'))
endif

simplesquirrel = dependency('simplesquirrel', required: false)

if (not simplesquirrel.found())
	opts = cmake.subproject_options()

	opts.add_cmake_defines({'CMAKE_POLICY_VERSION_MINIMUM': '3.5', 'SSQ_USE_SQ_SUBMODULE': true})

	simplesquirrel_proj = cmake.subproject('simplesquirrel', options: opts)

	simplesquirrel_lib = simplesquirrel_proj.get_variable('simplesquirrel_static')
	squirrel_lib = simplesquirrel_proj.get_variable('squirrel_static')
	sqstdlib = simplesquirrel_proj.get_variable('sqstdlib_static')

	simplesquirrel = declare_dependency(link_with: [simplesquirrel_lib, squirrel_lib, sqstdlib], include_directories: simplesquirrel_proj.include_directories('simplesquirrel_static'))
endif

deps = [sdl, sdl_image, sdl_net, sdl_gfx, audio_lib, curl, git2, physfs, simplesquirrel]

# TODO: allow swapping of audio backend in a more clean manner
src = [
	'src/audio/audio.cpp', 'src/audio/audio_@0@.cpp'.format(audio_backend),
	'src/brux/actors.cpp', 'src/brux/core.cpp', 'src/brux/fileio.cpp',
	'src/brux/flop.cpp', 'src/brux/global.cpp', 'src/brux/graphics.cpp',
	'src/brux/input.cpp', 'src/brux/main.cpp', 'src/brux/maths.cpp',
	'src/brux/net.cpp', 'src/brux/physics.cpp', 'src/brux/shapes.cpp',
	'src/brux/sprite.cpp', 'src/brux/text.cpp',
	'src/external/cJSON.c'
]

executable('brux', src, dependencies: deps, include_directories: include_directories('src'), install: true)

#install_data('test/test.nut', install_dir: get_option('datadir'))
install_data('test/test.nut', install_dir: 'test')
install_subdir('test/res', install_dir: 'test')
