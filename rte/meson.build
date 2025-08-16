project('brux-gdk', 'cpp', 'c', default_options: ['cpp_std=c++17', 'buildtype=release', 'default_library=static'], meson_version: '>=1.1.0')

# CMake module. Needed for physfs and simplesquirrel modules.
cmake = import('cmake')

# Configure file
config_dat = configuration_data()
config_dat.set('USE_SDL2_MIXER', get_option('USE_SDL2_MIXER'))

if (get_option('USE_SDL2_MIXER'))
	config_dat.set('USE_FASTFILL', get_option('USE_FASTFILL'))
endif

configure_file(input: 'src/config.hpp.in', output: 'config.hpp', configuration: config_dat)

# Dependencies
sdl = dependency('SDL2', fallback: ['sdl2'])
sdl_image = dependency('SDL2_image', fallback: ['sdl2_image'])
sdl_mixer = dependency('SDL2_mixer', fallback: ['sdl2_mixer'])
sdl_net = dependency('SDL2_net', fallback: ['sdl2_net'])
# Perhaps this should be removed or remade internally to reduce on an external dependency?
sdl_gfx = dependency('SDL2_gfx', fallback: ['sdl2_gfx'])

curl = dependency('curl', required: false)

if (not curl.found())
	curl = dependency('libcurl', required: true)
endif

git2 = dependency('libgit2')

physfs = dependency('physfs', required: false)

if (not physfs.found())
	physfs_proj = cmake.subproject('physfs')

	physfs = physfs_proj.get_variable('physfs')
endif

simplesquirrel = dependency('simplesquirrel', required: false)
simplesquirrel_static = false

if (not simplesquirrel.found())
	opts = cmake.subproject_options()

	opts.add_cmake_defines({'CMAKE_POLICY_VERSION_MINIMUM': '3.5', 'SSQ_USE_SQ_SUBMODULE': true})

	simplesquirrel_proj = cmake.subproject('simplesquirrel', options: opts)

	simplesquirrel_lib = simplesquirrel_proj.get_variable('simplesquirrel_static')

	simplesquirrel = declare_dependency(link_with: simplesquirrel_lib, include_directories: simplesquirrel_proj.include_directories('simplesquirrel_static'))
endif

deps = [sdl, sdl_image, sdl_mixer, sdl_net, sdl_gfx, curl, git2, physfs, simplesquirrel]

# TODO: allow swapping of audio backend in a more clean manner
src = [
	'src/audio/audio.cpp', 'src/audio/audio_none.cpp', 'src/audio/audio_sdl2.cpp',
	'src/brux/actors.cpp', 'src/brux/core.cpp', 'src/brux/fileio.cpp',
	'src/brux/flop.cpp', 'src/brux/global.cpp', 'src/brux/graphics.cpp',
	'src/brux/input.cpp', 'src/brux/main.cpp', 'src/brux/maths.cpp',
	'src/brux/net.cpp', 'src/brux/physics.cpp', 'src/brux/shapes.cpp',
	'src/brux/sprite.cpp', 'src/brux/text.cpp',
	'src/external/cJSON.c'
]

executable('brux', src, dependencies: deps, include_directories: include_directories('src'), install: true)
