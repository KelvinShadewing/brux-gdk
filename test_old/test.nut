/*========*\
| TEST NUT |
\*========*/

//////////////////////
// GLOBAL VARIABLES //
//////////////////////

//Misc
local brxQuit = false
::fntW <- newFont(newSprite("cp437w.png", 8, 8, 0, 0, 0, 0), 0, 0, true, 0)
::fntR <- newFont(newSprite("cp437r.png", 8, 8, 0, 0, 0, 0), 0, 0, true, 0)
::fntG <- newFont(newSprite("cp437g.png", 8, 8, 0, 0, 0, 0), 0, 0, true, 0)
::fntB <- newFont(newSprite("cp437b.png", 8, 8, 0, 0, 0, 0), 0, 0, true, 0)
::fntE <- newFont(newSprite("cp437e.png", 8, 8, 0, 0, 0, 0), 0, 0, true, 0)

print("fntE = " + findSprite("cp437e.png"))

drawKey <- function(key, str, x, y) {
	local ftu = 0

	if(keyDown(key)) ftu = fntG
	else ftu = fntR

	drawText(ftu, x, y, str)
}

//File menu handling stuff
::dirls <- arraySort(lsdir(getdir()))
::dircurs <- 0
::menutimerd <- 20
::menutimeru <- 20
::isnut <- function(str) {
	if(typeof str != "string") return false
	if(str.find(".sq") > 0 || str.find(".nut") > 0) return true
	return false
}
::tidydirls <- function() {
	local newarr = []
	for(local i = 0; i < dirls.len(); i++) {
		if((isdir(dirls[i]) && dirls[i] != ".") || isnut(dirls[i])) newarr.push(dirls[i])
	}
	dirls = newarr
}
tidydirls()
::menuFont <- fntW

local d = lsdir(".")
print(jsonWrite(arraySort(d)))

::lastbutton <- -1

///////////////
// FUNCTIONS //
///////////////

::mode0 <- function() { //Search for game
	if(keyPress(k_down)) dircurs++
	if(keyPress(k_up)) dircurs--

	if(keyDown(k_down)) {
		if(menutimerd > 0) menutimerd--
		else {
			menutimerd = 2
			dircurs++
		}
	}
	if(keyRelease(k_down)) menutimerd = 20

	if(keyDown(k_up)) {
		if(menutimeru > 0) menutimeru--
		else {
			menutimeru = 2
			dircurs--
		}
	}
	if(keyRelease(k_up)) menutimeru = 20

	if(dircurs < 0) dircurs += dirls.len()
	if(dircurs >= dirls.len()) dircurs -= dirls.len()

	for(local i = 0; i < dirls.len(); i++){
		if(isnut(dirls[i])) drawText(fntW, 0, 32 + (i * 8) - (dircurs * 8), "  " + dirls[i])
		else drawText(fntE, 0, 32 + (i * 8) - (dircurs * 8), "  " + dirls[i])

		if(i == dircurs) drawText(fntG, 0, 32 + (i * 8) - (dircurs * 8), "=>")
	}

	if(keyPress(k_enter)){
		if(isdir(dirls[dircurs])){
			chdir(dirls[dircurs])
			dirls = arraySort(lsdir(getdir()))
			dircurs = 0
			tidydirls()
		}

		if(isnut(dirls[dircurs]) == true) donut(dirls[dircurs])
	}

	drawText(fntW, 0, 0, "Current directory:\n" + getdir().tostring())
}

::mode1 <- function() { //Keyboard and mouse test
	//Mouse
	drawText(fntW, 0, 0, "Mouse Position: (" + mouseX().tostring() + "," + mouseY().tostring() + ")")

	//Keyboard
	drawKey(k_escape, "Esc", 0, 8)
	drawKey(k_f1, "F1", 8*4, 8)
	drawKey(k_f2, "F2", 8*7, 8)
	drawKey(k_f3, "F3", 8*10, 8)
	drawKey(k_f4, "F4", 8*13, 8)
	drawKey(k_f5, "F5", 8*16, 8)
	drawKey(k_f6, "F6", 8*19, 8)
	drawKey(k_f7, "F7", 8*22, 8)
	drawKey(k_f8, "F8", 8*25, 8)
	drawKey(k_f9, "F9", 8*28, 8)
	drawKey(k_f10, "FA", 8*30, 8)
	drawKey(k_f11, "FB", 8*33, 8)
	drawKey(k_f12, "FC", 8*36, 8)

	drawKey(k_tick, "~", 9, 16)
	drawKey(k_1, "1", 8*3, 16)
	drawKey(k_2, "2", 8*5, 16)
	drawKey(k_3, "3", 8*7, 16)
	drawKey(k_4, "4", 8*9, 16)
	drawKey(k_5, "5", 8*11, 16)
	drawKey(k_6, "6", 8*13, 16)
	drawKey(k_7, "7", 8*15, 16)
	drawKey(k_8, "8", 8*17, 16)
	drawKey(k_9, "9", 8*19, 16)
	drawKey(k_0, "0", 8*21, 16)
	drawKey(k_minus, "-", 8*23, 16)
	drawKey(k_equals, "=", 8*25, 16)
	drawKey(k_backspace, "Bck", 8*27, 16)
	drawKey(k_print, "Prt", 8*31, 16)

	drawKey(k_tab, "Tab", 0, 24)
	drawKey(k_q, "Q", 8*4, 24)
	drawKey(k_w, "W", 8*6, 24)
	drawKey(k_e, "E", 8*8, 24)
	drawKey(k_r, "R", 8*10, 24)
	drawKey(k_t, "T", 8*12, 24)
	drawKey(k_y, "Y", 8*14, 24)
	drawKey(k_u, "U", 8*16, 24)
	drawKey(k_i, "I", 8*18, 24)
	drawKey(k_o, "O", 8*20, 24)
	drawKey(k_p, "P", 8*22, 24)
	drawKey(k_lbrace, "[", 8*24, 24)
	drawKey(k_rbrace, "]", 8*26, 24)
	drawKey(k_backslash, "\\", 8*28, 24)
	drawKey(k_home, "Hm", 8*30, 24)
	drawKey(k_end, "Nd", 8*33, 24)

	drawKey(k_capslock, "Cap", 9, 32)
	drawKey(k_a, "A", 8*5, 32)
	drawKey(k_s, "S", 8*7, 32)
	drawKey(k_d, "D", 8*9, 32)
	drawKey(k_f, "F", 8*11, 32)
	drawKey(k_g, "G", 8*13, 32)
	drawKey(k_h, "H", 8*15, 32)
	drawKey(k_j, "J", 8*17, 32)
	drawKey(k_k, "K", 8*19, 32)
	drawKey(k_l, "L", 8*21, 32)
	drawKey(k_semicolon, "", 8*23, 32)
	drawKey(k_quote, "'", 8*25, 32)
	drawKey(k_enter, "Ent", 8*27, 32)
	drawKey(k_numlock, "Num", 8*31, 32)

	drawKey(k_lshift, "lSh", 8*2, 40)
	drawKey(k_z, "Z", 8*6, 40)
	drawKey(k_x, "X", 8*8, 40)
	drawKey(k_c, "C", 8*10, 40)
	drawKey(k_v, "V", 8*12, 40)
	drawKey(k_b, "B", 8*14, 40)
	drawKey(k_n, "N", 8*16, 40)
	drawKey(k_m, "M", 8*18, 40)
	drawKey(k_comma, ",", 8*20, 40)
	drawKey(k_period, ".", 8*22, 40)
	drawKey(k_slash, "/", 8*24, 40)
	drawKey(k_rshift, "rSh", 8*26, 40)

	drawKey(k_up, (30).tochar(), 8*31, 40)
	drawKey(k_down, (31).tochar(), 8*31, 48)
	drawKey(k_left, (17).tochar(), 8*29, 48)
	drawKey(k_right, (16).tochar(), 8*33, 48)

	drawKey(k_lcontrol, "lCn", 0, 48)
	drawKey(k_lsup, "Sup", 8*4, 48)
	drawKey(k_lalt, "lAl", 8*8, 48)
	drawKey(k_space, "[__]", 8*12, 48)
	drawKey(k_ralt, "rAl", 8*17, 48)
	drawKey(k_app, "App", 8*21, 48)
	drawKey(k_rcontrol, "rCn", 8*25	, 48)

	drawKey(k_num7, "7", 8, 64)
	drawKey(k_num8, "8", 16, 64)
	drawKey(k_num9, "9", 24, 64)
	drawKey(k_num4, "4", 8, 72)
	drawKey(k_num5, "5", 16, 72)
	drawKey(k_num6, "6", 24, 72)
	drawKey(k_num1, "1", 8, 80)
	drawKey(k_num2, "2", 16, 80)
	drawKey(k_num3, "3", 24, 80)
	drawKey(k_num0, "0", 8, 88)
	drawKey(k_numdel, ".", 16, 88)
	drawKey(k_numenter, "Rt", 32, 88)

	drawKey(k_insert, "Ins", 8*7, 64)
	drawKey(k_del, "Del", 8*7, 72)
	drawKey(k_pgup, "Pu", 8*7, 80)
	drawKey(k_pgdn, "Pd", 8*7, 88)
	drawKey(k_numdiv, "/", 24, 88)
	drawKey(k_nummul, "*", 32, 64)
	drawKey(k_numsub, "-", 32, 72)
	drawKey(k_numadd, "+", 32, 80)

	//Draw mouse angle
	setDrawColor(0xff0000ff)
	drawLine(160, 120, mouseX(), mouseY())
	drawText(fntW, 0, 224, "Angle to mouse from center: " + pointAngle(160, 120, mouseX(), mouseY()) + "\nDisplay resolution: " + displayW() + "x" + displayH())

	//Draw mouse reticle
	setDrawColor(0xffff)
	drawLine(mouseX() - 8, mouseY(), mouseX() + 8, mouseY())
	drawLine(mouseX(), mouseY() - 8, mouseX(), mouseY() + 8)
	drawCircle(mouseX(), mouseY(), 4, false)
}

::mode2 <- function() { //Gamepad test
	drawText(fntW, 0, 0, "Gamepads detected: " + joyCount().tostring())

	for(local i = 0; i < joyCount(); i++){
		drawText(fntW, 0, (8*i) + 8, "Gamepad " + i.tostring() + " name: " + joyName(i))
	}

	//Graphical test
	drawText(fntW, 160, 160, "Axes:\nX:" + joyX(0) + "\nY:" + joyY(0) + "\nH:" + joyH(0) + "\nV:" + joyV(0) + "\nL:" + joyL(0) + "\nR:" + joyR(0))

	//L stick
	setDrawColor(0xf8ff)
	drawCircle(64, 200, 8, false)
	setDrawColor(0x808080ff)
	if(joyButtonDown(0, 9)) setDrawColor(0xf8ff)
	if(joyButtonPress(0, 9)) setDrawColor(0xf8f800ff)
	if(joyButtonRelease(0, 9)) setDrawColor(0xf80000ff)
	drawCircle(64 + (joyX(0) / (js_max / 8)), 200 + (joyY(0) / (js_max / 8)), 4, true)

	//R stick
	setDrawColor(0xf8ff)
	drawCircle(96, 200, 8, false)
	setDrawColor(0x808080ff)
	if(joyButtonDown(0, 10)) setDrawColor(0xf8ff)
	if(joyButtonPress(0, 10)) setDrawColor(0xf8f800ff)
	if(joyButtonRelease(0, 10)) setDrawColor(0xf80000ff)
	drawCircle(96 + (joyH(0) / (js_max / 8)), 200 + (joyV(0) / (js_max / 8)), 4, true)

	setDrawColor(0xf8ff)

	//L trigger
	drawRect(48, 160, 8, 0 - (joyL(0) / (js_max / 32)), true)

	//R trigger
	drawRect(104, 160, 8, 0 - (joyR(0) / (js_max / 32)), true)

	//Button neutral
	setDrawColor(0x808080ff)
	drawCircle(128, 176, 4, true) //Y
	drawCircle(120, 184, 4, true) //X
	drawCircle(136, 184, 4, true) //B
	drawCircle(128, 192, 4, true) //A
	drawCircle(64, 176, 4, true) //Back
	drawCircle(96, 176, 4, true) //Start
	drawCircle(32, 160, 4, true) //L
	drawCircle(128, 160, 4, true) //R
	drawCircle(80, 160, 6, true) //Logo

	//Button down
	setDrawColor(0x0000f8ff)
	if(joyButtonDown(0, 3)) drawCircle(128, 176, 4, true) //Y
	if(joyButtonDown(0, 2)) drawCircle(120, 184, 4, true) //X
	if(joyButtonDown(0, 1)) drawCircle(136, 184, 4, true) //B
	if(joyButtonDown(0, 0)) drawCircle(128, 192, 4, true) //A
	if(joyButtonDown(0, 6)) drawCircle(64, 176, 4, true) //Back
	if(joyButtonDown(0, 7)) drawCircle(96, 176, 4, true) //Start
	if(joyButtonDown(0, 4)) drawCircle(32, 160, 4, true) //L
	if(joyButtonDown(0, 5)) drawCircle(128, 160, 4, true) //R
	if(joyButtonDown(0, 8)) drawCircle(80, 160, 6, true) //Logo

	//Button press
	setDrawColor(0xf8f800ff)
	if(joyButtonPress(0, 3)) drawCircle(128, 176, 4, true) //Y
	if(joyButtonPress(0, 2)) drawCircle(120, 184, 4, true) //X
	if(joyButtonPress(0, 1)) drawCircle(136, 184, 4, true) //B
	if(joyButtonPress(0, 0)) drawCircle(128, 192, 4, true) //A
	if(joyButtonPress(0, 6)) drawCircle(64, 176, 4, true) //Back
	if(joyButtonPress(0, 7)) drawCircle(96, 176, 4, true) //Start
	if(joyButtonPress(0, 4)) drawCircle(32, 160, 4, true) //L
	if(joyButtonPress(0, 5)) drawCircle(128, 160, 4, true) //R
	if(joyButtonPress(0, 8)) drawCircle(80, 160, 6, true) //Logo

	//Button release
	setDrawColor(0xf80000ff)
	if(joyButtonRelease(0, 3)) drawCircle(128, 176, 4, true) //Y
	if(joyButtonRelease(0, 2)) drawCircle(120, 184, 4, true) //X
	if(joyButtonRelease(0, 1)) drawCircle(136, 184, 4, true) //B
	if(joyButtonRelease(0, 0)) drawCircle(128, 192, 4, true) //A
	if(joyButtonRelease(0, 6)) drawCircle(64, 176, 4, true) //Back
	if(joyButtonRelease(0, 7)) drawCircle(96, 176, 4, true) //Start
	if(joyButtonRelease(0, 4)) drawCircle(32, 160, 4, true) //L
	if(joyButtonRelease(0, 5)) drawCircle(128, 160, 4, true) //R
	if(joyButtonRelease(0, 8)) drawCircle(80, 160, 6, true) //Logo

	//D-pad neutral
	setDrawColor(0x808080ff)
	drawCircle(32, 176, 4, true) //Up
	drawCircle(24, 184, 4, true) //Left
	drawCircle(40, 184, 4, true) //Right
	drawCircle(32, 192, 4, true) //Down

	//D-pad down
	setDrawColor(0x0000f8ff)
	if(joyHatDown(0, js_up)) drawCircle(32, 176, 4, true) //Up
	if(joyHatDown(0, js_left)) drawCircle(24, 184, 4, true) //Left
	if(joyHatDown(0, js_right)) drawCircle(40, 184, 4, true) //Right
	if(joyHatDown(0, js_down)) drawCircle(32, 192, 4, true) //Down

	//D-pad press
	setDrawColor(0xf8f800ff)
	if(joyHatPress(0, js_up)) drawCircle(32, 176, 4, true) //Up
	if(joyHatPress(0, js_left)) drawCircle(24, 184, 4, true) //Left
	if(joyHatPress(0, js_right)) drawCircle(40, 184, 4, true) //Right
	if(joyHatPress(0, js_down)) drawCircle(32, 192, 4, true) //Down

	//D-pad release
	setDrawColor(0xf80000ff)
	if(joyHatRelease(0, js_up)) drawCircle(32, 176, 4, true) //Up
	if(joyHatRelease(0, js_left)) drawCircle(24, 184, 4, true) //Left
	if(joyHatRelease(0, js_right)) drawCircle(40, 184, 4, true) //Right
	if(joyHatRelease(0, js_down)) drawCircle(32, 192, 4, true) //Down

	local currentpress = joyPressAny(0)
	if(currentpress != -1) lastbutton = currentpress
	drawText(fntW, 0, 232, "Last button pressed: " + lastbutton)
}

::mode3 <- function() {

}

///////////////////
// MAIN FUNCTION //
///////////////////

setScalingFilter(0)
setResolution(320, 240)
setBackgroundColor(0)
setFPS(30)
setDrawColor(0x0000ffff)
newActor(Actor, 0, 0)

::mode <- mode1

while(!brxQuit) {
	if(keyPress(k_escape)) brxQuit = true

	if(keyPress(k_home)) mode = mode0
	if(keyPress(k_f1)) mode = mode1
	if(keyPress(k_f2)) mode = mode2
	if(keyPress(k_f3)) mode = mode3

	mode()
	update()
}
