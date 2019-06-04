/*========*\
| TEST NUT |
\*========*/
print("Test Nut");

//////////////////////
// GLOBAL VARIABLES //
//////////////////////

//Misc
local quit = false;
::fntW <- newFont(newSprite("cp437w.png", 9, 16, 0, 0, 0, 0, 0), 0, 0, 1, 0);
::fntR <- newFont(newSprite("cp437r.png", 9, 16, 0, 0, 0, 0, 0), 0, 0, 1, 0);
::fntG <- newFont(newSprite("cp437g.png", 9, 16, 0, 0, 0, 0, 0), 0, 0, 1, 0);
::fntB <- newFont(newSprite("cp437b.png", 9, 16, 0, 0, 0, 0, 0), 0, 0, 1, 0);
print("Created fonts.");

drawKey <- function(key, str, x, y){
	local ftu = 0;

	if(keyDown(key)) ftu = fntG;
	else ftu = fntR;

	drawText(ftu, x, y, str);
};


///////////////////
// MAIN FUNCTION //
///////////////////

setScalingFilter(0);
setResolution(400, 240);
setBackgroundColor(0);
setFPS(30);

while(!quit){
	if(keyPress(k_escape)) quit = true;
	drawText(fntW, 0, 0, "Mouse Position: (" + mouseX().tostring() + "," + mouseY().tostring() + ")");

	//Keyboard
	drawKey(k_escape, "Esc", 0, 16);
	drawKey(k_f1, "F1", 9*4, 16);
	drawKey(k_f2, "F2", 9*7, 16);
	drawKey(k_f3, "F3", 9*10, 16);
	drawKey(k_f4, "F4", 9*13, 16);
	drawKey(k_f5, "F5", 9*16, 16);
	drawKey(k_f6, "F6", 9*19, 16);
	drawKey(k_f7, "F7", 9*22, 16);
	drawKey(k_f8, "F8", 9*25, 16);
	drawKey(k_f9, "F9", 9*28, 16);
	drawKey(k_f10, "F10", 9*31, 16);
	drawKey(k_f11, "F11", 9*35, 16);
	drawKey(k_f12, "F12", 9*39, 16);

	drawKey(k_tick, "~", 9, 32);
	drawKey(k_1, "1", 9*3, 32);
	drawKey(k_2, "2", 9*5, 32);
	drawKey(k_3, "3", 9*7, 32);
	drawKey(k_4, "4", 9*9, 32);
	drawKey(k_5, "5", 9*11, 32);
	drawKey(k_6, "6", 9*13, 32);
	drawKey(k_7, "7", 9*15, 32);
	drawKey(k_8, "8", 9*17, 32);
	drawKey(k_9, "9", 9*19, 32);
	drawKey(k_0, "0", 9*21, 32);
	drawKey(k_minus, "-", 9*23, 32);
	drawKey(k_equals, "=", 9*25, 32);
	drawKey(k_backspace, "Bck", 9*27, 32);
	drawKey(k_print, "Prt", 9*31, 32);
	drawKey(k_insert, "Ins", 9*35, 32);
	drawKey(k_del, "Del", 9*39, 32);

	drawKey(k_tab, "Tab", 0, 48);
	drawKey(k_q, "Q", 9*4, 48);
	drawKey(k_w, "W", 9*6, 48);
	drawKey(k_e, "E", 9*8, 48);
	drawKey(k_r, "R", 9*10, 48);
	drawKey(k_t, "T", 9*12, 48);
	drawKey(k_y, "Y", 9*14, 48);
	drawKey(k_u, "U", 9*16, 48);
	drawKey(k_i, "I", 9*18, 48);
	drawKey(k_o, "O", 9*20, 48);
	drawKey(k_p, "P", 9*22, 48);
	drawKey(k_lbrace, "[", 9*24, 48);
	drawKey(k_rbrace, "]", 9*26, 48);
	drawKey(k_backslash, "\\", 9*28, 48);
	drawKey(k_home, "Hm", 9*30, 48);
	drawKey(k_end, "Nd", 9*33, 48);
	drawKey(k_pgup, "Pu", 9*36, 48);
	drawKey(k_pgdn, "Pd", 9*39, 48);

	drawKey(k_capslock, "Cap", 9, 64);
	drawKey(k_a, "A", 9*5, 64);
	drawKey(k_s, "S", 9*7, 64);
	drawKey(k_d, "D", 9*9, 64);
	drawKey(k_f, "F", 9*11, 64);
	drawKey(k_g, "G", 9*13, 64);
	drawKey(k_h, "H", 9*15, 64);
	drawKey(k_j, "J", 9*17, 64);
	drawKey(k_k, "K", 9*19, 64);
	drawKey(k_l, "L", 9*21, 64);
	drawKey(k_semicolon, ";", 9*23, 64);
	drawKey(k_quote, "'", 9*25, 64);
	drawKey(k_enter, "Ent", 9*27, 64);
	drawKey(k_numlock, "Num", 9*31, 64);
	drawKey(k_numdiv, "/", 9*35, 64);
	drawKey(k_nummul, "*", 9*37, 64);
	drawKey(k_numsub, "-", 9*39, 64);
	drawKey(k_numadd, "+", 9*41, 64);

	drawKey(k_lshift, "lSh", 9*2, 80);
	drawKey(k_z, "Z", 9*6, 80);
	drawKey(k_x, "X", 9*8, 80);
	drawKey(k_c, "C", 9*10, 80);
	drawKey(k_v, "V", 9*12, 80);
	drawKey(k_b, "B", 9*14, 80);
	drawKey(k_n, "N", 9*16, 80);
	drawKey(k_m, "M", 9*18, 80);
	drawKey(k_comma, ",", 9*20, 80);
	drawKey(k_period, ".", 9*22, 80);
	drawKey(k_slash, "/", 9*24, 80);
	drawKey(k_rshift, "rSh", 9*26, 80);

	drawKey(k_up, (30).tochar(), 9*31, 80);
	drawKey(k_down, (31).tochar(), 9*31, 96);
	drawKey(k_left, (17).tochar(), 9*29, 96);
	drawKey(k_right, (16).tochar(), 9*33, 96);

	drawKey(k_lcontrol, "lCn", 0, 96);
	drawKey(k_lsup, "Sup", 9*4, 96);
	drawKey(k_lalt, "lAl", 9*8, 96);
	drawKey(k_space, "[__]", 9*12, 96);
	drawKey(k_ralt, "rAl", 9*17, 96);
	drawKey(k_app, "App", 9*21, 96);
	drawKey(k_rcontrol, "rCn", 9*25	, 96);

	drawKey(k_num7, "7", 9*35, 80);
	drawKey(k_num8, "8", 9*37, 80);
	drawKey(k_num9, "9", 9*39, 80);
	drawKey(k_num4, "4", 9*35, 96);
	drawKey(k_num5, "5", 9*37, 96);
	drawKey(k_num6, "6", 9*39, 96);
	drawKey(k_num1, "1", 9*35, 112);
	drawKey(k_num2, "2", 9*37, 112);
	drawKey(k_num3, "3", 9*39, 112);
	drawKey(k_num0, "0", 9*35, 128);
	drawKey(k_numdel, ".", 9*37, 128);
	drawKey(k_numenter, "Ret", 9*39, 128);

	update();
};
