/*====================*\
| XYG STANDARD LIBRARY |
\*====================*/



/////////////
//CONSTANTS//
/////////////

//Scan Codes
const sc_a = 4;
const sc_b = 5;
const sc_c = 6;
const sc_d = 7;
const sc_e = 8;
const sc_f = 9;
const sc_g = 10;
const sc_h = 11;
const sc_i = 12;
const sc_j = 13;
const sc_k = 14;
const sc_l = 15;
const sc_m = 16;
const sc_n = 17;
const sc_o = 18;
const sc_p = 19;
const sc_q = 20;
const sc_r = 21;
const sc_s = 22;
const sc_t = 23;
const sc_u = 24;
const sc_v = 25;
const sc_w = 26;
const sc_x = 27;
const sc_y = 28;
const sc_z = 29;
	
const sc_1 = 30;
const sc_2 = 31;
const sc_3 = 32;
const sc_4 = 33;
const sc_5 = 34;
const sc_6 = 35;
const sc_7 = 36;
const sc_8 = 37;
const sc_9 = 38;
const sc_0 = 39;
	
const sc_return = 40;
const sc_escape = 41;
const sc_backspace = 42;
const sc_tab = 43;
const sc_space = 44;
	
const sc_minus = 45;
const sc_equals = 46;
const sc_lbracket = 47;
const sc_rbracket = 48;
const sc_backslash = 49;
const sc_nonuslash = 50;
const sc_semicolon = 51;
const sc_apostrophe = 52;
const sc_quote = 52;
const sc_grave = 53;
const sc_tick = 53;
const sc_comma = 54;
const sc_period = 55;
const sc_fullstop = 55;
const sc_slash = 56;
	
const sc_capslock = 57;
	
const sc_f1 = 58;
const sc_f2 = 59;
const sc_f3 = 60;
const sc_f4 = 61;
const sc_f5 = 62;
const sc_f6 = 63;
const sc_f7 = 64;
const sc_f8 = 65;
const sc_f9 = 66;
const sc_f10 = 67;
const sc_f11 = 68;
const sc_f12 = 69;
	
const sc_printscreen = 70;
const sc_scrolllock = 71;
const sc_pause = 72;
const sc_insert = 73;
	
const sc_home = 74;
const sc_pageup = 75;
const sc_pgup = 75;
const sc_delete = 76;
const sc_end = 77;
const sc_pagedown = 78;
const sc_pgdn = 78;
const sc_right = 79;
const sc_left = 80;
const sc_down = 81;
const sc_up = 82;
	
const sc_numlock = 83;
	
const kp_divide = 84;
const kp_multiply = 85;
const kp_minus = 86;
const kp_plus = 87;
const kp_add = 87;
const kp_enter = 88;
const kp_1 = 89;
const kp_2 = 90;
const kp_3 = 91;
const kp_4 = 92;
const kp_5 = 93;
const kp_6 = 94;
const kp_7 = 95;
const kp_8 = 96;
const kp_9 = 97;
const kp_0 = 98;
const kp_period = 99;
const kp_fullstop = 99;
	
const sc_nonusbackslash = 100;
const sc_application = 101;
const sc_app = 101;
const sc_power = 102;
const kp_equals = 103;
	
const sc_f13 = 104;
const sc_f14 = 105;
const sc_f15 = 106;
const sc_f16 = 107;
const sc_f17 = 108;
const sc_f18 = 109;
const sc_f19 = 110;
const sc_f20 = 111;
const sc_f21 = 112;
const sc_f22 = 113;
const sc_f23 = 114;
const sc_f24 = 115;
	
const sc_execute = 116;
const sc_help = 117;
const sc_menu = 118;
const sc_select = 119;
const sc_stop = 120;
const sc_again = 121;
const sc_undo = 122;
const sc_cut = 123;
const sc_copy = 124;
const sc_paste = 125;
const sc_find = 126;
const sc_mute = 127;
const sc_volumeup = 128;
const sc_volup = 128;
const sc_volumedown = 129;
const sc_voldn = 129;
	
const kp_comma = 133;
const kp_equalsas400 = 134;
	
const sc_inat1 = 135;
const sc_inat2 = 136;
const sc_inat3 = 137;
const sc_inat4 = 138;
const sc_inat5 = 139;
const sc_inat6 = 140;
const sc_inat7 = 141;
const sc_inat8 = 142;
const sc_inat9 = 143;
	
const sc_lang1 = 144;
const sc_lang2 = 145;
const sc_lang3 = 146;
const sc_lang4 = 147;
const sc_lang5 = 148;
const sc_lang6 = 149;
const sc_lang7 = 150;
const sc_lang8 = 151;
const sc_lang9 = 152;
	
const sc_alterase = 153;
const sc_sysreq = 154;
const sc_cancel = 155;
const sc_clear = 156;
const sc_prior = 157;
const sc_return2 = 158;
const sc_separator = 159;
const sc_out = 160;
const sc_oper = 161;
const sc_clearagain = 162;
const sc_crsel = 163;
const sc_exsel = 164;
	
const kp_00 = 176;
const kp_000 = 177;
	
const sc_thousandsep = 178;
const sc_decimalsep = 179;
const sc_currency = 180;
const sc_currencysub = 181;
	
const kp_lparen = 182;
const kp_rparen = 183;
const kp_lbrace = 184;
const kp_rbrace = 185;
const kp_tab = 186;
const kp_backspace = 187;
const kp_a = 188;
const kp_b = 189;
const kp_c = 190;
const kp_d = 191;
const kp_e = 192;
const kp_f = 193;
const kp_xor = 194;
const kp_power = 195;
const kp_percent = 196;
const kp_less = 197;
const kp_greater = 198;
const kp_ampersand = 199;
const kp_amp = 199;
const kp_dblampersand = 200;
const kp_dblamp = 200;
const kp_verticalbar = 201;
const kp_vbar = 201;
const kp_dblverticalbar = 202;
const kp_dblvbar = 202;
const kp_colon = 203;
const kp_hash = 204;
const kp_space = 205;
const kp_at = 206;
const kp_exclam = 207;
const kp_memstore = 208;
const kp_memrecall = 209;
const kp_memclear = 210;
const kp_memadd = 211;
const kp_memsubtract = 212;
const kp_memsub = 212;
const kp_memmultiply = 213;
const kp_memmul = 213;
const kp_memdivide = 214;
const kp_memdiv = 214;
const kp_plusminus = 215;
const kp_addsub = 215;
const kp_clear = 216;
const kp_clearentry = 217;
const kp_binary = 218;
const kp_octal = 219;
const kp_decimal = 220;
const kp_hexadecimal = 221;
	
const sc_lctrl = 224;
const sc_lcontrol = 224;
const sc_lshift = 225;
const sc_lalt = 226;
const sc_lgui = 227;
const sc_rctrl = 228;
const sc_rcontrol = 228;
const sc_rshift = 229;
const sc_ralt = 230;
const sc_rgui = 231;
	
const sc_mode = 257;
	
const sc_audionext = 258;
const sc_audioprev = 259;
const sc_audiostop = 260;
const sc_audioplay = 261;
const sc_audiomute = 262;
const sc_mediaselect = 263;
const sc_www = 264;
const sc_mail = 265;
const sc_calculator = 266;
const sc_calc = 266;
const sc_computer = 267;
const sc_com = 267;
const sc_acsearch = 268;
const sc_achome = 269;
const sc_acback = 270;
const sc_acprev = 270;
const sc_acforward = 271;
const sc_acnext = 271;
const sc_acstop = 272;
const sc_acrefresh = 273;
const sc_acbookmarks = 274;
	
const sc_brightnessup = 275;
const sc_brup = 275;
const sc_brightnessdown = 276;
const sc_brdn = 276;
const sc_displayswitch = 277;
	
const sc_kbdillumtoggle = 278;
const sc_kbdillumdown = 279;
const sc_kbdillumup = 280;
const sc_eject = 281;
const sc_sleep = 282;
	
const sc_app1 = 283;
const sc_app2 = 284;
	
const sc_num_scancodes = 512;

//Bits
const _1 = 1;
const _2 = 2;
const _3 = 4;
const _4 = 8;
const _5 = 16;
const _6 = 32;
cosnt _7 = 64;
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