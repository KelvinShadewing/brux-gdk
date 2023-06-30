//  Brux - Portability API Test Suite
//  Copyright (C) 2023 hexaheximal
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Affero General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Affero General Public License for more details.
//
//  You should have received a copy of the GNU Affero General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

::currentTest <- 1
::passedTests <- []
::failedTests <- []

::existantAPIs <- []
::nonexistantAPIs <- []

::apiList <- [
	// Actors

	"Actor",
	"newActor",
	"deleteActor",
	"runActors",
	"countActors",
	"checkActor",

	// Audio

	"loadSound",
	"loadMusic",
	"playSound",
	"playMusic",
	"deleteSound",
	"deleteMusic",
	"checkSound",
	"checkMusic",
	"stopSound",
	"stopChannel",
	"stopMusic",
	"setMaxChannels",
	"pauseMusic",
	"resumeMusic",
	"musicPaused",
	"fadeMusic",
	"setMusicVolume",
	"setSoundVolume",
	"getMusicVolume",
	"getAudioDriver",
	"isAudioAvailable",

	// File I/O

	"mount",
	"unmount",
	"fileExists",
	"fileWrite",
	"fileRead",
	"fileAppend",
	"fileDelete",
	"jsonRead",
	"jsonWrite",
	"getdir",
	"getPrefDir",
	"getWriteDir",
	"setWriteDir",
	"lsdir",
	"isdir",
	"createDir",
	"dostr",

	// Graphics

	"clearScreen",
	"setDrawTarget",
	"getDrawTarget",
	"drawImage",
	"setDrawColor",
	"drawRec",
	"drawCircle",
	"setBackgroundColor",
	"loadImage",
	"loadImageKeyed",
	"setScaling",
	"setScalingFilter",
	"setResolution",
	"screenW",
	"screenH",
	"displayW",
	"displayH",
	"windowW",
	"windowH",
	"newTexture",
	"drawLine",
	"drawPoint",
	"resetDrawTarget",
	"textureSetBlendMode",

	// Input

	"keyDown",
	"keyPress",
	"keyRelease",
	"keyPressAny",
	"mouseX",
	"mouseY",
	"mouseDown",
	"mousePress",
	"mouseRelease",
	"getQuit",
	"joyCount",
	"joyX",
	"joyY",
	"joyZ",
	"joyH",
	"joyV",
	"joyR",
	"joyL",
	"joyAxis",
	"joyHatPress",
	"joyHatRelease",
	"joyHatDown",
	"joyButtonPress",
	"joyButtonRelease",
	"joyButtonDown",
	"joyPressAny",
	"joyName",
	"joyAxisPress",
	"joyAxisRelease",
	"keyString",
	"mouseWheelX",
	"mouseWheelY",

	// Main

	"update",
	"getOS",
	"wait"
	"donut",
	"getFrames",
	"getTicks",
	"getFPS",
	"setFPS",
	"setWindowTitle",
	"setWindowIcon",
	"bruxVersion",
	"toggleFullscreen",

	// Maths

	"randInt",
	"randFloat",
	"lendirX",
	"lendirY",
	"distance2",
	"distance3",
	"inDistance2",
	"distance3",
	"wrap",
	"pointAngle",
	"round",
	"ceil",
	"floor",
	"abs",
	"binstr",

	// Misc

	"choose",

	// Shapes

	"hitLineLine",
	"hitLineCircle",
	"hitLinePoint",

	// Sprites

	"newSprite",
	"newSpriteFT",
	"drawSprite",
	"drawSpriteEx",
	"drawSpriteMod",
	"drawSpriteExMod",
	"deleteSprite",
	"findSprite",
	"spriteName",
	"spriteW",
	"spriteH",
	"replaceSprite",
	"spriteSetBlendMode",

	// Text

	"drawText",
	"newFont",
	"chint"
]

::score <- 0
::total <- 1

print("Checking if audio playback is available...")

if (getAudioDriver() != "None" && isAudioAvailable()) {
	score += 1;
}

::batchAPITest <- function(names) {
	local found = 0;
	local rootTable = getroottable();

	foreach (name in names) {
		if (name in getroottable()) {
			found++;
			existantAPIs.push(name);
			continue;
		}

		nonexistantAPIs.push(name);
	}

	total += names.len();
	score += found;
}

::doTest <- function(name, handler) {
	print("Test " + str(currentTest) + ": " + name)
	
	try {
		handler()
		print("PASS")
	} catch (e) {
		print("FAIL")
	}

	currentTest++;
}

print("Attempting to figure out which Brux APIs exist...")

batchAPITest(apiList)

print("Now entering graphical test...")

setResolution(400, 240)
setWindowTitle("Brux GDK Test Suite")

::sprFont <- newSprite("res/font.png", 6, 8, 0, 0, 0, 0)
::sprMidi <- newSprite("res/midi.png", 32, 32, 0, 0, 16, 19)
::sprOcean <- newSprite("res/ocean.png", 480, 240, 0, 0, 0, 0)
::font <- newFont(sprFont, 0, 0, false, 0)

::musTest <- loadMusic("res/bossa-nova.mp3")

playMusic(musTest, -1)

setFPS(60)

::frame <- 0
::text <- "Hello, World!"
::text2 <- "Press Enter (or up on the first joystick) to exit."
::x <- 0.0
::y <- 0.0
::x2 <- 0.0
::y2 <- 0.0
::midiX <- 0.0
::midiY <- 0.0
::midiFrame <- 0.0
::rspeed <- 3.98

while (!getQuit()) {
	x = (400 / 2) - ((6 * text.len()) / 2)
	y = 8 * 2

	x2 = (400 / 2) - ((6 * text2.len()) / 2)
	y2 = 240 - (8 * 2)

	midiX = (400 / 2)
	midiY = (240 / 2)

	x += sin(frame / 10.0) * 16.0;

	drawSprite(sprOcean, 0, 0, 0)
	drawSprite(sprMidi, 48 + (midiFrame % 7), midiX, midiY)
	drawText(font, x, y, text)
	drawText(font, x2, y2, text2)

	update()
	frame++;
	midiFrame += abs(rspeed) / (8 + abs(rspeed))

	if (keyPress(k_enter) || joyAxisPress(0, js_up, js_max / 4)) {
		break;
	}
} 

if (score == total) {
	print("All tests passed!")
}

print("Score: " + str(score) + " / " + str(total))

if (nonexistantAPIs.len() != 0) {
	print("Failed to find the following Brux APIs:")

	foreach (name in nonexistantAPIs) {
		print(name)
	}
}