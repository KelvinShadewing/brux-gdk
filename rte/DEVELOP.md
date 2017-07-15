# Development Guide

This guide is to help programmers get on boarded with various IDEs and compilers to work on the game engine.

## Visual Studio 2017 - CMake

### Required Libraries

#### Fast Tracking
If you are building for `64bit` you can download an example structure of the following C++ libraries which will work with the existing documentation below.

    - Source Headers & Libraries - [c:\cpp](https://drive.google.com/open?id=0BwInc8An2aOMOGpjc2pRTU9wblE)
    - RTE Runtime / DLLs - [{REPO}\rte\bin](https://drive.google.com/open?id=0BwInc8An2aOMN0VBN3VkbUpKZjQ)

Install `Source Headers & Libraries` to C:\ and install `RTE Runtime / DLLs` to where this github repo is `{REPO}\rte\bin` it will have all the DLLs needed to run the application.

#### Custom Setup

You will need SDL and various SDL libraries, and Squirrel. Please be very aware of the builds you download as they could be for 32bits or 64bits and the game engine needs to compile against the right platform.

    - SDL2
    - SDL2_Image
    - SDL2_Mixer
    - SDL2_TTF
    - Squirrel 3.1

Visual Studo 2017 includes the ability to run CMake right from the editor. CMake has had Visual Studio Support, but that was running CMake outside of Visual Studo to generate the Visual Studio Solution/Projects. With Visual Studio you can just open the development folder that has `CMakeLists.txt`. From there it will run CMake and provide compile options from there. Here is how you open the folder:

 1. Install / Open Visual Studio 2017
 1. Make sure you have **Desktop development with C++** installed / enabled, if you do not, then do the following:
    1. Go to File -> New Project
    1. At the bottom left of the window there will be *Not finding what you are looking for?* then under it, it will say "Open Visual Studio Installer".
    1. Install **Desktop development with C++**
 1. Next go to File -> Open and find the folder that has `CMakeLists.txt`
 1. Visual Studio will start to process the CMake file and fail, this is expected. We need to specify where the needed libraries and includes are. While CMake is very portable its not 100% portable specifically for Windows based development.
 1. At this point we will want to edit the CMake settings. You can do this by right-clicking the `CMakeLists.txt` in the **Solution Explorer**. Then, choose `Change CMake Settings`. This will then generate `CMakeSettings.json` with various build types.
 1. At this point there will be 2-4 enteries in the JSON file and may look like this:

        {
        // See https://go.microsoft.com//fwlink//?linkid=834763 for more information about this file.
        "configurations": [
            ...
            {
            "name": "x64-Debug",
            "generator": "Visual Studio 15 2017 Win64",
            "configurationType": "Debug",
            "buildRoot": "${env.LOCALAPPDATA}\\CMakeBuild\\${workspaceHash}\\build\\${name}",
            "cmakeCommandArgs": "",
            "buildCommandArgs": "-m -v:minimal",
            "ctestCommandArgs": ""
            },
            ...
        ]
        }
    We want to add in the CMake varibles to various SDL & Squirrel folders. Here is an example build:

        {
        "name": "x64-Debug",
        "generator": "Visual Studio 15 2017 Win64",
        "configurationType": "Debug",
        "buildRoot": "${env.LOCALAPPDATA}\\CMakeBuild\\${workspaceHash}\\build\\${name}",
        "cmakeCommandArgs": "",
        "buildCommandArgs": "-m -v:minimal",
        "ctestCommandArgs": "",
        "variables": [
            {
            "name": "SDL2_PATH",
            "value": "C:\\cpp\\SDL2-2.0.5"
            },
            {
            "name": "SDL2_IMAGE_PATH",
            "value": "C:\\cpp\\SDL2_image-2.0.1"
            },
            {
            "name": "SDL2_TTF_PATH",
            "value": "C:\\cpp\\SDL2_ttf-2.0.14"
            },
            {
            "name": "SDL2_MIXER_INCLUDE_DIR",
            "value": "C:\\cpp\\SDL2_mixer-2.0.1\\include"
            },
            {
            "name": "SDL2_MIXER_LIBRARY",
            "value": "C:\\cpp\\SDL2_mixer-2.0.1\\lib\\x64\\SDL2_mixer.lib"
            },
            {
            "name": "Squirrel_DIR",
            "value": "C:\\cpp\\squirrel3\\include"
            },
            {
            "name": "Squirrel_LIBRARY",
            "value": "C:\\cpp\\squirrel3\\lib\\x64\\Debug\\squirrel.lib"
            },
            {
            "name": "Squirrel_STD_LIBRARY",
            "value": "C:\\cpp\\squirrel3\\lib\\x64\\Debug\\sqstdlib.lib"
            }
        ]
        },
 1. One thing to note is Visual Studio uses the build root as `"${env.LOCALAPPDATA}\\CMakeBuild\\${workspaceHash}\\build\\${name}"` which places this in places the folder in a place like `C:\Users\xingo\AppData\Local\CMakeBuild\61a2373d-b2ef...`. That is annoying at best. You can change it to anything you want like: `"buildRoot": "C:\\Users\\xingo\\Documents\\c++\\XYG-Studio-master\\rte\\bin\\${name}",`
 1. Don't forget when you are building for x86_64 or x64 CHANGE THE PROJECT SETTINGS. If you are just running through this document and finding out that SDL is still not being found, then its probably because you are using the wrong build profile.