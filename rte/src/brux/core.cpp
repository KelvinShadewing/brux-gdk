//  Brux - Core
//  Copyright (C) 2016 KelvinShadewing
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

/*===========*\
| CORE SOURCE |
\*===========*/

#include "brux/main.hpp"
#include "brux/global.hpp"
#include "brux/core.hpp"

void xyLoadCore() {
	const SQChar *cmd =R"rew(
	const k__0 = 0;
	const k__1 = 1;
	const k__2 = 2;
	const k__3 = 3;

	const k_a = 4;
	const k_b = 5;
	const k_c = 6;
	const k_d = 7;
	const k_e = 8;
	const k_f = 9;
	const k_g = 10;
	const k_h = 11;
	const k_i = 12;
	const k_j = 13;
	const k_k = 14;
	const k_l = 15;
	const k_m = 16;
	const k_n = 17;
	const k_o = 18;
	const k_p = 19;
	const k_q = 20;
	const k_r = 21;
	const k_s = 22;
	const k_t = 23;
	const k_u = 24;
	const k_v = 25;
	const k_w = 26;
	const k_x = 27;
	const k_y = 28;
	const k_z = 29;

	const k_1 = 30;
	const k_2 = 31;
	const k_3 = 32;
	const k_4 = 33;
	const k_5 = 34;
	const k_6 = 35;
	const k_7 = 36;
	const k_8 = 37;
	const k_9 = 38;
	const k_0 = 39;

	const k_return = 40;
	const k_enter = 40;
	const k_escape = 41;
	const k_backspace = 42;
	const k_tab = 43;
	const k_space = 44;

	const k_minus = 45;
	const k_equals = 46;
	const k_lbracket = 47;
	const k_lbrace = 47;
	const k_rbracket = 48;
	const k_rbrace = 48;
	const k_backslash = 49;
	const k_nonuslash = 50;
	const k_semicolon = 51;
	const k_apostrophe = 52;
	const k_quote = 52;
	const k_grave = 53;
	const k_tick = 53;
	const k_comma = 54;
	const k_period = 55;
	const k_fullstop = 55;
	const k_dot = 55;
	const k_slash = 56;

	const k_capslock = 57;
	const k_caps = 57;

	const k_f1 = 58;
	const k_f2 = 59;
	const k_f3 = 60;
	const k_f4 = 61;
	const k_f5 = 62;
	const k_f6 = 63;
	const k_f7 = 64;
	const k_f8 = 65;
	const k_f9 = 66;
	const k_f10 = 67;
	const k_f11 = 68;
	const k_f12 = 69;

	const k_printscreen = 70;
	const k_print = 70;
	const k_scrolllock = 71;
	const k_scroll = 71;
	const k_pause = 72;
	const k_insert = 73;

	const k_home = 74;
	const k_pageup = 75;
	const k_pgup = 75;
	const k_delete = 76;
	const k_del = 76;
	const k_end = 77;
	const k_pagedown = 78;
	const k_pgdn = 78;
	const k_right = 79;
	const k_left = 80;
	const k_down = 81;
	const k_up = 82;

	const k_numlock = 83;

	const k_numdivide = 84;
	const k_numdiv = 84;
	const k_nummultiply = 85;
	const k_nummul = 85;
	const k_numminus = 86;
	const k_numsub = 86;
	const k_numplus = 87;
	const k_numadd = 87;
	const k_numenter = 88;
	const k_numreturn = 88;
	const k_num1 = 89;
	const k_num2 = 90;
	const k_num3 = 91;
	const k_num4 = 92;
	const k_num5 = 93;
	const k_num6 = 94;
	const k_num7 = 95;
	const k_num8 = 96;
	const k_num9 = 97;
	const k_num0 = 98;
	const k_numperiod = 99;
	const k_numfullstop = 99;
	const k_numdelete = 99;
	const k_numdel = 99;
	const k_numdot = 99;

	const k_nonusbackslash = 100;
	const k_application = 101;
	const k_app = 101;
	const k_power = 102;
	const k_numequals = 103;

	const k_f13 = 104;
	const k_f14 = 105;
	const k_f15 = 106;
	const k_f16 = 107;
	const k_f17 = 108;
	const k_f18 = 109;
	const k_f19 = 110;
	const k_f20 = 111;
	const k_f21 = 112;
	const k_f22 = 113;
	const k_f23 = 114;
	const k_f24 = 115;

	const k_execute = 116;
	const k_exe = 116;
	const k_help = 117;
	const k_menu = 118;
	const k_select = 119;
	const k_stop = 120;
	const k_again = 121;
	const k_undo = 122;
	const k_cut = 123;
	const k_copy = 124;
	const k_paste = 125;
	const k_find = 126;
	const k_mute = 127;
	const k_volumeup = 128;
	const k_volup = 128;
	const k_volumedown = 129;
	const k_voldn = 129;

	const k_numcomma = 133;
	const k_numequalsas400 = 134;

	const k_inat1 = 135;
	const k_inat2 = 136;
	const k_inat3 = 137;
	const k_inat4 = 138;
	const k_inat5 = 139;
	const k_inat6 = 140;
	const k_inat7 = 141;
	const k_inat8 = 142;
	const k_inat9 = 143;

	const k_lang1 = 144;
	const k_lang2 = 145;
	const k_lang3 = 146;
	const k_lang4 = 147;
	const k_lang5 = 148;
	const k_lang6 = 149;
	const k_lang7 = 150;
	const k_lang8 = 151;
	const k_lang9 = 152;

	const k_alterase = 153;
	const k_sysreq = 154;
	const k_cancel = 155;
	const k_clear = 156;
	const k_prior = 157;
	const k_return2 = 158;
	const k_separator = 159;
	const k_out = 160;
	const k_oper = 161;
	const k_clearagain = 162;
	const k_crsel = 163;
	const k_exsel = 164;

	const k_num00 = 176;
	const k_num000 = 177;

	const k_thousandsep = 178;
	const k_decimalsep = 179;
	const k_currency = 180;
	const k_currencysub = 181;

	const k_numlparen = 182;
	const k_numrparen = 183;
	const k_numlbrace = 184;
	const k_numrbrace = 185;
	const k_numtab = 186;
	const k_numbackspace = 187;
	const k_numa = 188;
	const k_numb = 189;
	const k_numc = 190;
	const k_numd = 191;
	const k_nume = 192;
	const k_numf = 193;
	const k_numxor = 194;
	const k_numpower = 195;
	const k_numpercent = 196;
	const k_numless = 197;
	const k_numgreater = 198;
	const k_numampersand = 199;
	const k_numamp = 199;
	const k_numdblampersand = 200;
	const k_numdblamp = 200;
	const k_numverticalbar = 201;
	const k_numvbar = 201;
	const k_numdblverticalbar = 202;
	const k_numdblvbar = 202;
	const k_numcolon = 203;
	const k_numhash = 204;
	const k_numspace = 205;
	const k_numat = 206;
	const k_numexclam = 207;
	const k_nummemstore = 208;
	const k_nummemrecall = 209;
	const k_nummemclear = 210;
	const k_nummemadd = 211;
	const k_nummemsubtract = 212;
	const k_nummemsub = 212;
	const k_nummemmultiply = 213;
	const k_nummemmul = 213;
	const k_nummemdivide = 214;
	const k_nummemdiv = 214;
	const k_numplusminus = 215;
	const k_numaddsub = 215;
	const k_numclear = 216;
	const k_numclearentry = 217;
	const k_numbinary = 218;
	const k_numoctal = 219;
	const k_numdecimal = 220;
	const k_numhexadecimal = 221;
	const k_numhex = 221;

	const k_lctrl = 224;
	const k_lcontrol = 224;
	const k_lshift = 225;
	const k_lalt = 226;
	const k_lsup = 227;
	const k_rctrl = 228;
	const k_rcontrol = 228;
	const k_rshift = 229;
	const k_ralt = 230;
	const k_rsup = 231;

	const k_mode = 257;

	const k_audionext = 258;
	const k_audioprev = 259;
	const k_audiostop = 260;
	const k_audioplay = 261;
	const k_audiomute = 262;
	const k_mediaselect = 263;
	const k_www = 264;
	const k_mail = 265;
	const k_calculator = 266;
	const k_calc = 266;
	const k_computer = 267;
	const k_com = 267;
	const k_acsearch = 268;
	const k_achome = 269;
	const k_acback = 270;
	const k_acprev = 270;
	const k_acforward = 271;
	const k_acnext = 271;
	const k_acstop = 272;
	const k_acrefresh = 273;
	const k_acbookmarks = 274;

	const k_brightnessup = 275;
	const k_brup = 275;
	const k_brightnessdown = 276;
	const k_brdn = 276;
	const k_displayswitch = 277;

	const k_kbdillumtoggle = 278;
	const k_kbdillumdown = 279;
	const k_kbdillumup = 280;
	const k_eject = 281;
	const k_sleep = 282;

	const k_app1 = 283;
	const k_app2 = 284;

	const k_num_scancodes = 512;

	const _1 = 1;
	const _2 = 2;
	const _3 = 4;
	const _4 = 8;
	const _5 = 16;
	const _6 = 32;
	const _7 = 64;
	const _8 = 128;
	const _9 = 256;
	const _10 = 512;
	const _11 = 1024;
	const _12 = 2048;
	const _13 = 4098;
	const _14 = 8192;
	const _15 = 16384;
	const _16 = 32768;
	const _17 = 65536;
	const _18 = 131072;
	const _19 = 262144;
	const _20 = 524228;
	const _21 = 1048576;
	const _22 = 2097152;
	const _23 = 4194304;
	const _24 = 8388608;
	const _25 = 16777216;
	const _26 = 33554432;
	const _27 = 67108864;
	const _28 = 134217728;
	const _29 = 268435456;
	const _30 = 536870912;
	const _31 = 1073741824;
	const _32 = 2147483648;

	const ha_left = 0;
	const ha_center = 1;
	const ha_right = 2;
	const va_top = 0;
	const va_center = 1;
	const va_bottom = 2;

	const bm_none = 0;
	const bm_blend = 1;
	const bm_add = 2;
	const bm_sub = 3;
	const bm_mod = 4;

	const os_windows = 0;
	const os_linux = 1;
	const os_android = 2;
	const os_mac = 3;

	const js_max = 32768;
	const js_up = 1;
	const js_right = 2;
	const js_down = 3;
	const js_left = 4;

	const c_white = 0xffffffff;
	const c_red = 0xff0000ff;
	const c_green = 0xff00ff;
	const c_blue = 0xffff;
	const c_gray = 0x808080ff;
	const c_yellow = 0xffff00ff;
	const c_magenta = 0xff00ffff;
	const c_cyan = 0xffffff;
	const c_black = 0xff;
	const pi = 3.14159265358979323846;

	arraySort <- function(arr){	//Skip sorting if it's not an array
	if(typeof arr != "array") return arr;	//or if there's nothing to sort
	if(arr.len() <= 1) return arr
		local needsort = true

		while(needsort) {
			needsort = false
			for(local i = 0; i < arr.len() - 2; i++) {
				if(arr[i] > arr[i+1]) {
					local temp = arr[i]
					arr[i] = arr[i+1]
					arr[i+1] = temp
					needsort = true
				}
			}
		}

		return arr
	}

	::jsonWrite <- function(Table) {
		if(typeof Table == "null") return "null"
		if(typeof(Table)!="array" && typeof(Table)!="table")
			return Table.tostring()
		local Out = ""
		local AsString = function(Item) {
			switch(typeof(Item)) {
				case "table":
				case "array":
					return jsonWrite(Item)
				case "string":
					local Len = Item.len()
					local Str = ""
					for(local i=0;i<Len;i++) {
						if(Item[i]=='\\' || Item[i]=='\"')
							Str+="\\"
						Str+=Item.slice(i, i+1)
					}
					return "\""+Str+"\""
				case "null":
					return "null"
				default:
					if("tostring" in Item) return Item.tostring()
					else return Item
			}
		}
		if(typeof(Table) == "table") {
			if(Table.len() == 0) return "{}"
			Out = "{"
			foreach(Key,Val in Table)
				Out += "\""+Key+"\":"+AsString(Val)+", "
			return Out.slice(0,-2) + "}"
		}
		if(typeof(Table) == "array") {
			if(Table.len() == 0) return "[]"
			Out = "["
			foreach(Val in Table)
				Out += AsString(Val)+", "
			return Out.slice(0,-2) + "]"
		}
	}

	::min <- function(a, b) {
		if(a < b) return a
		else return b
	}

	::max <- function(a, b) {
		if(a > b) return a
		else return b
	}

	::choose <- function(options) {
		if(typeof options != "array") return options
		return options[randInt(options.len())]
	}

	::system <- function(var) { print("I can't let you do that, Dave.") }

	::int <- function(var) { return var.tointeger() }
	::float <- function(var) { return var.tofloat() }
	::str <- function(var) { return var.tostring() }
	::char <- function(var) { return var.tochar() }
	::bool <- function(var) { return (var && true) }

	::eval <- function(expression) { return compilestring("return ("+expression+");")() }

	::drawSprite <- function(i, f, x, y, a = 0, l = 0, sx = 1.0, sy = 1.0, p = 1.0, c = 0xffffffff) { drawSpriteExMod(i, f, x, y, a, l, float(sx), float(sy), p, c)}

	print("Imported core lib.");)rew";

	SQInteger oldtop = sq_gettop(gvSquirrel);
	sq_compilebuffer(gvSquirrel, cmd, (int)strlen(cmd) * sizeof(SQChar), "core", 1);
	sq_pushroottable(gvSquirrel);
	sq_call(gvSquirrel, 1, SQFalse, SQTrue);
	sq_settop(gvSquirrel, oldtop);
};
