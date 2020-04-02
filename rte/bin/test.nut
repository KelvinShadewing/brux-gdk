/*========*\
| TEST NUT |
\*========*/
print("Test Nut");

//////////////////////
// GLOBAL VARIABLES //
//////////////////////

//Misc
local quit = false;
::fntW <- newFont(newSprite("cp437w.png", 8, 8, 0, 0, 0, 0, 0), 0, 0, 1, 0);
::fntR <- newFont(newSprite("cp437r.png", 8, 8, 0, 0, 0, 0, 0), 0, 0, 1, 0);
::fntG <- newFont(newSprite("cp437g.png", 8, 8, 0, 0, 0, 0, 0), 0, 0, 1, 0);
::fntB <- newFont(newSprite("cp437b.png", 8, 8, 0, 0, 0, 0, 0), 0, 0, 1, 0);
print("Created fonts.");

drawKey <- function(key, str, x, y){
	local ftu = 0;

	if(keyDown(key)) ftu = fntG;
	else ftu = fntR;

	drawText(ftu, x, y, str);
};

//Test table for printing as JSON
::blah <- {
	thing = "Value",
	otherthing = "Something"
};

///////////////
// FUNCTIONS //
///////////////

::mode1 <- function(){
	//Mouse
	drawText(fntW, 0, 0, "Mouse Position: (" + mouseX().tostring() + "," + mouseY().tostring() + ")");

	//Keyboard
	drawKey(k_escape, "Esc", 0, 8);
	drawKey(k_f1, "F1", 8*4, 8);
	drawKey(k_f2, "F2", 8*7, 8);
	drawKey(k_f3, "F3", 8*10, 8);
	drawKey(k_f4, "F4", 8*13, 8);
	drawKey(k_f5, "F5", 8*16, 8);
	drawKey(k_f6, "F6", 8*19, 8);
	drawKey(k_f7, "F7", 8*22, 8);
	drawKey(k_f8, "F8", 8*25, 8);
	drawKey(k_f9, "F9", 8*28, 8);
	drawKey(k_f10, "FA", 8*30, 8);
	drawKey(k_f11, "FB", 8*33, 8);
	drawKey(k_f12, "FC", 8*36, 8);

	drawKey(k_tick, "~", 9, 16);
	drawKey(k_1, "1", 8*3, 16);
	drawKey(k_2, "2", 8*5, 16);
	drawKey(k_3, "3", 8*7, 16);
	drawKey(k_4, "4", 8*9, 16);
	drawKey(k_5, "5", 8*11, 16);
	drawKey(k_6, "6", 8*13, 16);
	drawKey(k_7, "7", 8*15, 16);
	drawKey(k_8, "8", 8*17, 16);
	drawKey(k_9, "9", 8*19, 16);
	drawKey(k_0, "0", 8*21, 16);
	drawKey(k_minus, "-", 8*23, 16);
	drawKey(k_equals, "=", 8*25, 16);
	drawKey(k_backspace, "Bck", 8*27, 16);
	drawKey(k_print, "Prt", 8*31, 16);

	drawKey(k_tab, "Tab", 0, 24);
	drawKey(k_q, "Q", 8*4, 24);
	drawKey(k_w, "W", 8*6, 24);
	drawKey(k_e, "E", 8*8, 24);
	drawKey(k_r, "R", 8*10, 24);
	drawKey(k_t, "T", 8*12, 24);
	drawKey(k_y, "Y", 8*14, 24);
	drawKey(k_u, "U", 8*16, 24);
	drawKey(k_i, "I", 8*18, 24);
	drawKey(k_o, "O", 8*20, 24);
	drawKey(k_p, "P", 8*22, 24);
	drawKey(k_lbrace, "[", 8*24, 24);
	drawKey(k_rbrace, "]", 8*26, 24);
	drawKey(k_backslash, "\\", 8*28, 24);
	drawKey(k_home, "Hm", 8*30, 24);
	drawKey(k_end, "Nd", 8*33, 24);

	drawKey(k_capslock, "Cap", 9, 32);
	drawKey(k_a, "A", 8*5, 32);
	drawKey(k_s, "S", 8*7, 32);
	drawKey(k_d, "D", 8*9, 32);
	drawKey(k_f, "F", 8*11, 32);
	drawKey(k_g, "G", 8*13, 32);
	drawKey(k_h, "H", 8*15, 32);
	drawKey(k_j, "J", 8*17, 32);
	drawKey(k_k, "K", 8*19, 32);
	drawKey(k_l, "L", 8*21, 32);
	drawKey(k_semicolon, ";", 8*23, 32);
	drawKey(k_quote, "'", 8*25, 32);
	drawKey(k_enter, "Ent", 8*27, 32);
	drawKey(k_numlock, "Num", 8*31, 32);

	drawKey(k_lshift, "lSh", 8*2, 40);
	drawKey(k_z, "Z", 8*6, 40);
	drawKey(k_x, "X", 8*8, 40);
	drawKey(k_c, "C", 8*10, 40);
	drawKey(k_v, "V", 8*12, 40);
	drawKey(k_b, "B", 8*14, 40);
	drawKey(k_n, "N", 8*16, 40);
	drawKey(k_m, "M", 8*18, 40);
	drawKey(k_comma, ",", 8*20, 40);
	drawKey(k_period, ".", 8*22, 40);
	drawKey(k_slash, "/", 8*24, 40);
	drawKey(k_rshift, "rSh", 8*26, 40);

	drawKey(k_up, (30).tochar(), 8*31, 40);
	drawKey(k_down, (31).tochar(), 8*31, 48);
	drawKey(k_left, (17).tochar(), 8*29, 48);
	drawKey(k_right, (16).tochar(), 8*33, 48);

	drawKey(k_lcontrol, "lCn", 0, 48);
	drawKey(k_lsup, "Sup", 8*4, 48);
	drawKey(k_lalt, "lAl", 8*8, 48);
	drawKey(k_space, "[__]", 8*12, 48);
	drawKey(k_ralt, "rAl", 8*17, 48);
	drawKey(k_app, "App", 8*21, 48);
	drawKey(k_rcontrol, "rCn", 8*25	, 48);

	drawKey(k_num7, "7", 8, 64);
	drawKey(k_num8, "8", 16, 64);
	drawKey(k_num9, "9", 24, 64);
	drawKey(k_num4, "4", 8, 72);
	drawKey(k_num5, "5", 16, 72);
	drawKey(k_num6, "6", 24, 72);
	drawKey(k_num1, "1", 8, 80);
	drawKey(k_num2, "2", 16, 80);
	drawKey(k_num3, "3", 24, 80);
	drawKey(k_num0, "0", 8, 88);
	drawKey(k_numdel, ".", 16, 88);
	drawKey(k_numenter, "Rt", 32, 88);

	drawKey(k_insert, "Ins", 8*7, 64);
	drawKey(k_del, "Del", 8*7, 72);
	drawKey(k_pgup, "Pu", 8*7, 80);
	drawKey(k_pgdn, "Pd", 8*7, 88);
	drawKey(k_numdiv, "/", 24, 88);
	drawKey(k_nummul, "*", 32, 64);
	drawKey(k_numsub, "-", 32, 72);
	drawKey(k_numadd, "+", 32, 80);
};

::mode2 <- function(){
	//Gamepad test
	drawText(fntW, 0, 0, "Gamepads detected: " + getPads().tostring());


};

///////////////////
// MAIN FUNCTION //
///////////////////

setScalingFilter(0);
setResolution(320, 240);
setBackgroundColor(0);
setFPS(30);
//setDrawColor(0xFFFFFF);
print("Set draw color to white");

::mode <- mode1;

while(!quit){
	if(keyPress(k_escape)) quit = true;

	if(keyPress(k_f1)) mode = mode1;
	if(keyPress(k_f2)) mode = mode2;

	mode();
	update();
};

print(jsonWrite(blah));

::blah2 <- jsonRead(jsonWrite(blah));

print(blah2["thing"]);
