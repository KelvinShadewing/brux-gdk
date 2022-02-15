/*===========*\n\
| CORE SOURCE |
\*===========*/

#include "main.h"
#include "global.h"
#include "core.h"

void xyLoadCore() {
	const SQChar *cmd =" \n\
	const k__0 = 0; \n\
	const k__1 = 1; \n\
	const k__2 = 2; \n\
	const k__3 = 3; \n\
	 \n\
	const k_a = 4; \n\
	const k_b = 5; \n\
	const k_c = 6; \n\
	const k_d = 7; \n\
	const k_e = 8; \n\
	const k_f = 9; \n\
	const k_g = 10; \n\
	const k_h = 11; \n\
	const k_i = 12; \n\
	const k_j = 13; \n\
	const k_k = 14; \n\
	const k_l = 15; \n\
	const k_m = 16; \n\
	const k_n = 17; \n\
	const k_o = 18; \n\
	const k_p = 19; \n\
	const k_q = 20; \n\
	const k_r = 21; \n\
	const k_s = 22; \n\
	const k_t = 23; \n\
	const k_u = 24; \n\
	const k_v = 25; \n\
	const k_w = 26; \n\
	const k_x = 27; \n\
	const k_y = 28; \n\
	const k_z = 29; \n\
	 \n\
	const k_1 = 30; \n\
	const k_2 = 31; \n\
	const k_3 = 32; \n\
	const k_4 = 33; \n\
	const k_5 = 34; \n\
	const k_6 = 35; \n\
	const k_7 = 36; \n\
	const k_8 = 37; \n\
	const k_9 = 38; \n\
	const k_0 = 39; \n\
	 \n\
	const k_return = 40; \n\
	const k_enter = 40; \n\
	const k_escape = 41; \n\
	const k_backspace = 42; \n\
	const k_tab = 43; \n\
	const k_space = 44; \n\
	 \n\
	const k_minus = 45; \n\
	const k_equals = 46; \n\
	const k_lbracket = 47; \n\
	const k_lbrace = 47; \n\
	const k_rbracket = 48; \n\
	const k_rbrace = 48; \n\
	const k_backslash = 49; \n\
	const k_nonuslash = 50; \n\
	const k_semicolon = 51; \n\
	const k_apostrophe = 52; \n\
	const k_quote = 52; \n\
	const k_grave = 53; \n\
	const k_tick = 53; \n\
	const k_comma = 54; \n\
	const k_period = 55; \n\
	const k_fullstop = 55; \n\
	const k_dot = 55; \n\
	const k_slash = 56; \n\
	 \n\
	const k_capslock = 57; \n\
	const k_caps = 57; \n\
	 \n\
	const k_f1 = 58; \n\
	const k_f2 = 59; \n\
	const k_f3 = 60; \n\
	const k_f4 = 61; \n\
	const k_f5 = 62; \n\
	const k_f6 = 63; \n\
	const k_f7 = 64; \n\
	const k_f8 = 65; \n\
	const k_f9 = 66; \n\
	const k_f10 = 67; \n\
	const k_f11 = 68; \n\
	const k_f12 = 69; \n\
	 \n\
	const k_printscreen = 70; \n\
	const k_print = 70; \n\
	const k_scrolllock = 71; \n\
	const k_scroll = 71; \n\
	const k_pause = 72; \n\
	const k_insert = 73; \n\
	 \n\
	const k_home = 74; \n\
	const k_pageup = 75; \n\
	const k_pgup = 75; \n\
	const k_delete = 76; \n\
	const k_del = 76; \n\
	const k_end = 77; \n\
	const k_pagedown = 78; \n\
	const k_pgdn = 78; \n\
	const k_right = 79; \n\
	const k_left = 80; \n\
	const k_down = 81; \n\
	const k_up = 82; \n\
	 \n\
	const k_numlock = 83; \n\
	 \n\
	const k_numdivide = 84; \n\
	const k_numdiv = 84;\n\
	const k_nummultiply = 85; \n\
	const k_nummul = 85; \n\
	const k_numminus = 86; \n\
	const k_numsub = 86; \n\
	const k_numplus = 87; \n\
	const k_numadd = 87; \n\
	const k_numenter = 88; \n\
	const k_numreturn = 88; \n\
	const k_num1 = 89; \n\
	const k_num2 = 90; \n\
	const k_num3 = 91; \n\
	const k_num4 = 92; \n\
	const k_num5 = 93; \n\
	const k_num6 = 94; \n\
	const k_num7 = 95; \n\
	const k_num8 = 96; \n\
	const k_num9 = 97; \n\
	const k_num0 = 98; \n\
	const k_numperiod = 99; \n\
	const k_numfullstop = 99; \n\
	const k_numdelete = 99; \n\
	const k_numdel = 99; \n\
	const k_numdot = 99; \n\
	 \n\
	const k_nonusbackslash = 100; \n\
	const k_application = 101; \n\
	const k_app = 101; \n\
	const k_power = 102; \n\
	const k_numequals = 103; \n\
	 \n\
	const k_f13 = 104; \n\
	const k_f14 = 105; \n\
	const k_f15 = 106; \n\
	const k_f16 = 107; \n\
	const k_f17 = 108; \n\
	const k_f18 = 109; \n\
	const k_f19 = 110; \n\
	const k_f20 = 111; \n\
	const k_f21 = 112; \n\
	const k_f22 = 113; \n\
	const k_f23 = 114; \n\
	const k_f24 = 115; \n\
	 \n\
	const k_execute = 116; \n\
	const k_exe = 116; \n\
	const k_help = 117; \n\
	const k_menu = 118; \n\
	const k_select = 119; \n\
	const k_stop = 120; \n\
	const k_again = 121; \n\
	const k_undo = 122; \n\
	const k_cut = 123; \n\
	const k_copy = 124; \n\
	const k_paste = 125; \n\
	const k_find = 126; \n\
	const k_mute = 127; \n\
	const k_volumeup = 128; \n\
	const k_volup = 128; \n\
	const k_volumedown = 129; \n\
	const k_voldn = 129; \n\
	 \n\
	const k_numcomma = 133; \n\
	const k_numequalsas400 = 134; \n\
	 \n\
	const k_inat1 = 135; \n\
	const k_inat2 = 136; \n\
	const k_inat3 = 137; \n\
	const k_inat4 = 138; \n\
	const k_inat5 = 139; \n\
	const k_inat6 = 140; \n\
	const k_inat7 = 141; \n\
	const k_inat8 = 142; \n\
	const k_inat9 = 143; \n\
	 \n\
	const k_lang1 = 144; \n\
	const k_lang2 = 145; \n\
	const k_lang3 = 146; \n\
	const k_lang4 = 147; \n\
	const k_lang5 = 148; \n\
	const k_lang6 = 149; \n\
	const k_lang7 = 150; \n\
	const k_lang8 = 151; \n\
	const k_lang9 = 152; \n\
	 \n\
	const k_alterase = 153; \n\
	const k_sysreq = 154; \n\
	const k_cancel = 155; \n\
	const k_clear = 156; \n\
	const k_prior = 157; \n\
	const k_return2 = 158; \n\
	const k_separator = 159; \n\
	const k_out = 160; \n\
	const k_oper = 161; \n\
	const k_clearagain = 162; \n\
	const k_crsel = 163; \n\
	const k_exsel = 164; \n\
	 \n\
	const k_num00 = 176; \n\
	const k_num000 = 177; \n\
	 \n\
	const k_thousandsep = 178; \n\
	const k_decimalsep = 179; \n\
	const k_currency = 180; \n\
	const k_currencysub = 181; \n\
	 \n\
	const k_numlparen = 182; \n\
	const k_numrparen = 183; \n\
	const k_numlbrace = 184; \n\
	const k_numrbrace = 185; \n\
	const k_numtab = 186; \n\
	const k_numbackspace = 187; \n\
	const k_numa = 188; \n\
	const k_numb = 189; \n\
	const k_numc = 190; \n\
	const k_numd = 191; \n\
	const k_nume = 192; \n\
	const k_numf = 193; \n\
	const k_numxor = 194; \n\
	const k_numpower = 195; \n\
	const k_numpercent = 196; \n\
	const k_numless = 197; \n\
	const k_numgreater = 198; \n\
	const k_numampersand = 199; \n\
	const k_numamp = 199; \n\
	const k_numdblampersand = 200; \n\
	const k_numdblamp = 200; \n\
	const k_numverticalbar = 201; \n\
	const k_numvbar = 201; \n\
	const k_numdblverticalbar = 202; \n\
	const k_numdblvbar = 202; \n\
	const k_numcolon = 203; \n\
	const k_numhash = 204; \n\
	const k_numspace = 205; \n\
	const k_numat = 206; \n\
	const k_numexclam = 207; \n\
	const k_nummemstore = 208; \n\
	const k_nummemrecall = 209; \n\
	const k_nummemclear = 210; \n\
	const k_nummemadd = 211; \n\
	const k_nummemsubtract = 212; \n\
	const k_nummemsub = 212; \n\
	const k_nummemmultiply = 213; \n\
	const k_nummemmul = 213; \n\
	const k_nummemdivide = 214; \n\
	const k_nummemdiv = 214; \n\
	const k_numplusminus = 215; \n\
	const k_numaddsub = 215; \n\
	const k_numclear = 216; \n\
	const k_numclearentry = 217; \n\
	const k_numbinary = 218; \n\
	const k_numoctal = 219; \n\
	const k_numdecimal = 220; \n\
	const k_numhexadecimal = 221; \n\
	const k_numhex = 221; \n\
	 \n\
	const k_lctrl = 224; \n\
	const k_lcontrol = 224; \n\
	const k_lshift = 225; \n\
	const k_lalt = 226; \n\
	const k_lsup = 227; \n\
	const k_rctrl = 228; \n\
	const k_rcontrol = 228; \n\
	const k_rshift = 229; \n\
	const k_ralt = 230; \n\
	const k_rsup = 231; \n\
	 \n\
	const k_mode = 257; \n\
	 \n\
	const k_audionext = 258; \n\
	const k_audioprev = 259; \n\
	const k_audiostop = 260; \n\
	const k_audioplay = 261; \n\
	const k_audiomute = 262; \n\
	const k_mediaselect = 263; \n\
	const k_www = 264; \n\
	const k_mail = 265; \n\
	const k_calculator = 266; \n\
	const k_calc = 266; \n\
	const k_computer = 267; \n\
	const k_com = 267; \n\
	const k_acsearch = 268; \n\
	const k_achome = 269; \n\
	const k_acback = 270; \n\
	const k_acprev = 270; \n\
	const k_acforward = 271; \n\
	const k_acnext = 271; \n\
	const k_acstop = 272; \n\
	const k_acrefresh = 273; \n\
	const k_acbookmarks = 274; \n\
	 \n\
	const k_brightnessup = 275; \n\
	const k_brup = 275; \n\
	const k_brightnessdown = 276; \n\
	const k_brdn = 276; \n\
	const k_displayswitch = 277; \n\
	 \n\
	const k_kbdillumtoggle = 278; \n\
	const k_kbdillumdown = 279; \n\
	const k_kbdillumup = 280; \n\
	const k_eject = 281; \n\
	const k_sleep = 282; \n\
	 \n\
	const k_app1 = 283; \n\
	const k_app2 = 284; \n\
	 \n\
	const k_num_scancodes = 512; \n\
	 \n\
	const _1 = 1; \n\
	const _2 = 2; \n\
	const _3 = 4; \n\
	const _4 = 8; \n\
	const _5 = 16; \n\
	const _6 = 32; \n\
	const _7 = 64; \n\
	const _8 = 128; \n\
	const _9 = 256; \n\
	const _10 = 512; \n\
	const _11 = 1024; \n\
	const _12 = 2048; \n\
	const _13 = 4098; \n\
	const _14 = 8192; \n\
	const _15 = 16384; \n\
	const _16 = 32768; \n\
	const _17 = 65536; \n\
	const _18 = 131072; \n\
	const _19 = 262144; \n\
	const _20 = 524228; \n\
	const _21 = 1048576; \n\
	const _22 = 2097152; \n\
	const _23 = 4194304; \n\
	const _24 = 8388608; \n\
	const _25 = 16777216; \n\
	const _26 = 33554432; \n\
	const _27 = 67108864; \n\
	const _28 = 134217728; \n\
	const _29 = 268435456; \n\
	const _30 = 536870912; \n\
	const _31 = 1073741824; \n\
	const _32 = 2147483648; \n\
	 \n\
	const ha_left = 0; \n\
	const ha_center = 1; \n\
	const ha_right = 2; \n\
	const va_top = 0; \n\
	const va_center = 1; \n\
	const va_bottom = 2; \n\
	 \n\
	const bm_none = 0; \n\
	const bm_blend = 1; \n\
	const bm_add = 2; \n\
	const bm_sub = 3; \n\
	const bm_mod = 4; \n\
	 \n\
	const os_windows = 0; \n\
	const os_linux = 1; \n\
	const os_android = 2; \n\
	const os_mac = 3; \n\
	 \n\
	const js_max = 32768; \n\
	const js_up = 1; \n\
	const js_right = 2; \n\
	const js_down = 3; \n\
	const js_left = 4; \n\
	 \n\
	const c_white = 0xffffffff; \n\
	const c_red = 0xff0000ff; \n\
	const c_green = 0xff00ff; \n\
	const c_blue = 0xffff; \n\
	const c_gray = 0x808080ff; \n\
	const c_yellow = 0xffff00ff; \n\
	const c_magenta = 0xff00ffff; \n\
	const c_cyan = 0xffffff; \n\
	const c_black = 0xff; \n\
	const pi = 3.14159265358979323846; \n\
	 \n\
	arraySort <- function(arr){\n\t//Skip sorting if it's not an array\n\tif(typeof arr != \"array\") return arr;\n\n\t//or if there's nothing to sort\n\tif(arr.len() <= 1) return arr;\n\n\tlocal needsort = true;\n\twhile(needsort){\n\t\tneedsort = false;\n\t\tfor(local i = 0; i < arr.len() - 2; i++){\n\t\t\tif(arr[i] > arr[i+1]){\n\t\t\t\tlocal temp = arr[i];\n\t\t\t\tarr[i] = arr[i+1];\n\t\t\t\tarr[i+1] = temp;\n\t\t\t\tneedsort = true;\n\t\t\t};\n\t\t};\n\t};\n\n\treturn arr;\n}; \n\
	 \n\
	::jsonWrite <- function(Table) { \n\
		if(typeof(Table)!=\"array\" && typeof(Table)!=\"table\") \n\
			return Table.tostring(); \n\
		local Out = \"\"; \n\
		local AsString = function(Item) { \n\
			switch(typeof(Item)) { \n\
				case \"table\": \n\
				case \"array\": \n\
					return jsonWrite(Item); \n\
				case \"string\": \n\
					local Len = Item.len(); \n\
					local Str = \"\"; \n\
					for(local i=0;i<Len;i++) { \n\
						if(Item[i]=='\\\\' || Item[i]=='\\\"') \n\
							Str+=\"\\\\\"; \n\
						Str+=Item.slice(i, i+1) \n\
					} \n\
					return \"\\\"\"+Str+\"\\\"\"; \n\
				default: \n\
					return Item.tostring(); \n\
			} \n\
		} \n\
		if(typeof(Table) == \"table\") { \n\
			if(Table.len() == 0) return \"{}\"; \n\
			Out = \"{\"; \n\
			foreach(Key,Val in Table) \n\
				Out += \"\\\"\"+Key+\"\\\":\"+AsString(Val)+\", \"; \n\
			return Out.slice(0,-2) + \"}\"; \n\
		} \n\
		if(typeof(Table) == \"array\") { \n\
			if(Table.len() == 0) return \"[]\"; \n\
			Out = \"[\"; \n\
			foreach(Val in Table) \n\
				Out += AsString(Val)+\", \"; \n\
			return Out.slice(0,-2) + \"]\"; \n\
		} \n\
	} \n\
	 \n\
	::min <- function(a, b) { \n\
		if(a < b) return a \n\
		else return b \n\
	} \n\
	 \n\
	::max <- function(a, b) { \n\
		if(a > b) return a \n\
		else return b \n\
	} \n\
	print(\"Imported core lib.\");";

	SQInteger oldtop = sq_gettop(gvSquirrel);
	sq_compilebuffer(gvSquirrel, cmd, (int)strlen(cmd) * sizeof(SQChar), "core", 1);
	sq_pushroottable(gvSquirrel);
	sq_call(gvSquirrel, 1, SQFalse, SQTrue);
	sq_settop(gvSquirrel, oldtop);
};
