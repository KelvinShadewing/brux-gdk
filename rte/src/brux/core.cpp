//  Brux - Core
//  Copyright (C) 2016 KelvinShadewing
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

/*===========*\
| CORE SOURCE |
\*===========*/

#include "brux/main.hpp"
#include "brux/global.hpp"
#include "brux/core.hpp"

void xyLoadCore() {
	const char* cmd =R"rew(
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
	const bm_white = 5;

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

	// Depreicated codes are left undefined
	const clop_write_data = 1;
	const clop_url = 2;
	const clop_port = 3;
	const clop_proxy = 4;
	const clop_usrpwd = 5;
	const clop_proxy_usrpwd = 6;
	const clop_range = 7;
	// 8
	const clop_readdata = 9;
	const clop_error_buffer = 10;
	const clop_write_function = 11;
	const clop_read_function = 12;
	const clop_timeout = 13;
	const clop_in_filesize = 14;
	const clop_post_fields = 15;
	const clop_referer = 16;
	const clop_ftp_port = 17;
	const clop_useragent = 18;
	const clop_lowspeed_limit = 19;
	const clop_lowspeed_time = 20;
	const clop_resume_from = 21;
	const clop_cookie = 22;
	const clop_http_header = 23;
	const clop_http_post = 24;
	const clop_ssl_cert = 25;
	const clop_key_passwd = 26;
	const clop_crlf = 27;
	const clop_quote = 28;
	const clop_header_data = 29;
	// 30
	const clop_cookie_file = 31;
	const clop_ssl_version = 32;
	const clop_time_condition = 33;
	const clop_time_value = 34;
	// 35
	const clop_custom_request = 36;
	const clop_stderr = 37;
	const clop_post_quote = 39;
	// 40
	const clop_verbose = 41;
	const clop_header = 42;
	const clop_noprogress = 43;
	const clop_nobody = 44;
	const clop_failon_error = 45;
	const clop_upload = 46;
	const clop_post = 47;
	const clop_dirlist_only = 48;
	// 49
	const clop_append = 50;
	const clop_netrc = 51;
	const clop_follow_location = 52;
	const clop_transfer_text = 53;
	const clop_put = 54;
	// 55
	const clop_progress_function = 56;
	const clop_xferinfo_data = 57;
	const clop_auto_referer = 58;
	const clop_proxy_port = 59;
	const clop_post_fieldsize = 60;
	const clop_http_proxy_tunnel = 61;
	const clop_interface = 62;
	const clop_krblevel = 63;
	const clop_ssl_verify_peer = 64;
	const clop_cainfo = 65;
	const clop_max_redirs = 68;
	const clop_file_time = 69;
	const clop_telnet_options = 70;
	const clop_max_connects = 71;
	// 72
	// 73
	const clop_fresh_connect = 74;
	const clop_forbid_reuse = 75;
	const clop_random_file = 76;
	const clop_egd_socket = 77;
	const clop_connect_timeout = 78;
	const clop_header_function = 79;
	const clop_http_get = 80;
	const clop_ssl_verifyhost = 81;
	const clop_cookie_jar = 82;
	const clop_ssl_ciphers = 83;
	const clop_http_version = 84;
	const clop_ftp_use_epsv = 85;
	const clop_ssl_cert_type = 86;
	const clop_ssl_key = 87;
	const clop_ssl_key_type = 88;
	const clop_ssl_engine = 89;
	const clop_ssl_engine_default = 90;
	// 91
	const clop_dns_cache_timeout = 92;
	const clop_prequote = 93;
	const clop_debug_function = 94;
	const clop_debug_data = 95;
	const clop_cookie_session = 96;
	const clop_capath = 97;
	const clop_buffer_size = 98;
	const clop_nosignal = 99;
	const clop_share = 100;
	const clop_proxy_type = 101;
	const clop_accept_encoding = 102;
	const clop_private = 103;
	const clop_http_200_aliases = 104;
	const clop_unrestricted_auth = 105;
	const clop_ftp_use_eprt = 106;
	const clop_http_auth = 107;
	const clop_ssl_ctx_function = 108;
	const clop_ssl_ctx_data = 109;
	const clop_ftp_create_missing_dirs = 110;
	const clop_proxy_auth = 111;
	const clop_server_response_timeout = 112;
	const clop_ip_resolve = 113;
	const clop_max_file_size = 114;
	const clop_infilesize_large = 115;
	const clop_resume_from_large = 116;
	const clop_max_filesize_large = 117;
	const clop_netrc_file = 118;
	const clop_use_ssl = 119;
	const clop_post_fieldsize_large = 120;
	const clop_tcp_nodelay = 121;
	// 122
	// 123
	// 124
	// 125
	// 126
	// 127
	// 128
	const clop_ftp_ssl_auth = 129;
	const clop_ioctl_function = 130;
	const clop_ioctl_data = 131;
	// 132
	// 133
	const clop_ftp_account = 134;
	const clop_cookie_list = 135;
	const clop_ignore_content_length = 136;
	const clop_ftp_skip_pasv_ip = 137;
	const clop_ftp_file_method = 138;
	const clop_local_port = 139;
	const clop_local_port_range = 140;
	const clop_connect_only = 141;
	const clop_conv_from_network_function = 142;
	const clop_conv_to_network_function = 143;
	const clop_conv_from_utf8_function = 144;
	const clop_max_send_speed_large = 145;
	const clop_max_recv_speed_large = 146;
	const clop_ftp_alternative_to_user = 147;
	const clop_sockopt_function = 148;
	const clop_sockopt_data = 149;
	const clop_ssl_sessionid_cache = 150;
	const clop_ssl_auth_types = 151;
	const clop_ssh_public_keyfile = 152;
	const clop_ssh_private_keyfile = 153;
	const clop_ftp_ssl_ccc = 154;
	const clop_timeout_ms = 155;
	const clop_connect_timeout_ms = 156;
	const clop_http_transfer_decoding = 157;
	const clop_http_content_decoding = 158;
	const clop_new_file_perms = 159;
	const clop_new_directory_perms = 160;
	const clop_post_redir = 161;
	const clop_ssh_host_public_key_md5 = 162;
	const clop_open_socket_function = 163;
	const clop_open_socket_data = 164;
	const clop_copy_post_fields = 165;
	const clop_proxy_transfer_mode = 166;
	const clop_seek_function = 167;
	const clop_seek_data = 168;
	const clop_crl_file = 169;
	const clop_issuer_cert = 170;
	const clop_address_scope = 171;
	const clop_cert_info = 172;
	const clop_username = 173;
	const clop_password = 174;
	const clop_proxy_username = 175;
	const clop_proxy_password = 176;
	const clop_no_proxy = 177;
	const clop_tftp_blksize = 178;
	// 179
	const clop_socks5_gssapi_nec = 180;
	const clop_protocols = 181;
	const clop_redir_protocols = 182;
	const clop_ssh_knownhosts = 183;
	const clop_ssh_key_function = 184;
	const clop_ssh_key_data = 185;
	const clop_mail_from = 186;
	const clop_mail_rcpt = 187;
	const clop_ftp_use_pret = 188;
	const clop_rtsp_request = 189;
	const clop_rtsp_session_id = 190;
	const clop_rtsp_stream_uri = 191;
	const clop_rtsp_transport = 192;
	const clop_rtsp_client_cseq = 193;
	const clop_rtsp_server_cseq = 194;
	const clop_interleave_data = 195;
	const clop_interleave_function = 196;
	const clop_wildcard_match = 197;
	const clop_chunk_bgn_function = 198;
	const clop_chunk_end_function = 199;
	const clop_fnmatch_function = 200;
	const clop_chunk_data = 201;
	const clop_fnmatch_data = 202;
	const clop_resolve = 203;
	const clop_tlsauth_username = 204;
	const clop_tlsauth_password = 205;
	const clop_tlsauth_type = 206;
	const clop_transfer_encoding = 207;
	const clop_close_socket_function = 208;
	const clop_close_socket_data = 209;
	const clop_gssapi_delegation = 210;
	const clop_dns_servers = 211;
	const clop_accept_timeout_ms = 212;
	const clop_tcp_keepalive = 213;
	const clop_tcp_keepidle = 214;
	const clop_tcp_keepintvl = 215;
	const clop_ssl_options = 216;
	const clop_mail_auth = 217;
	const clop_sasl_ir = 218;
	const clop_xferinfo_function = 219;
	const clop_xoauth2_bearer = 220;
	const clop_dns_interface = 221;
	const clop_dns_local_ip4 = 222;
	const clop_dns_local_ip6 = 223;
	const clop_login_options = 224;
	const clop_ssl_enable_alpn = 225;
	const clop_ssl_enable_npn = 226;
	const clop_expect_100_timeout = 227;
	const clop_proxy_header = 228;
	const clop_header_opt = 229;
	const clop_pinned_public_key = 230;
	const clop_unix_socket_path = 231;
	const clop_ssl_verify_status = 232;
	const clop_false_start = 233;
	const clop_path_as_is = 234;
	const clop_proxy_service_name = 235;
	const clop_service_name = 236;
	const clop_pipe_wait = 237;
	const clop_default_protocol = 238;
	const clop_stream_weight = 239;
	const clop_stream_depends = 240;
	const clop_stream_depends_e = 241;
	const clop_tftp_no_options = 242;
	const clop_connect_to = 243;
	const clop_tcp_fastopen = 244;
	const clop_keep_sending_on_error = 245;
	const clop_proxy_ca_info = 246;
	const clop_proxy_ca_path = 247;
	const clop_proxy_ssl_verify_peer = 248;
	const clop_proxy_ssl_verify_host = 249;
	const clop_proxy_ssl_version = 250;
	const clop_proxy_tls_auth_username = 251;
	const clop_proxy_tls_auth_password = 252;
	const clop_proxy_tls_auth_type = 253;
	const clop_proxy_ssl_cert = 254;
	const clop_proxy_ssl_cert_type = 255;
	const clop_proxy_ssl_key = 256;
	const clop_proxy_ssl_key_type = 257;
	const clop_proxy_key_passwd = 258;
	const clop_proxy_ssl_cipher_list = 259;
	const clop_proxy_crl_file = 260;
	const clop_proxy_ssl_options = 261;
	const clop_pre_proxy = 262;
	const clop_proxy_pinned_public_key = 263;
	const clop_abstract_unix_socket = 264;
	const clop_suppress_connect_headers = 265;
	const clop_request_target = 266;
	const clop_socks5_auth = 267;
	const clop_ssh_compression = 268;
	const clop_mime_post = 269;
	const clop_time_value_large = 270;
	const clop_happy_eyeballs_timeout_ms = 271;
	const clop_resolver_start_function = 272;
	const clop_resolver_start_data = 273;
	const clop_haproxy_protocol = 274;
	const clop_dns_shuffle_addresses = 275;
	const clop_tls13_ciphers = 276;
	const clop_proxy_tls13_ciphers = 277;
	const clop_disallow_username_in_url = 278;
	const clop_doh_url = 279;
	const clop_upload_buffer_size = 280;
	const clop_upkeep_interval_ms = 281;
	const clop_curlu = 282;
	const clop_trailer_function = 283;
	const clop_trailer_data = 284;
	const clop_http09_allowed = 285;
	const clop_altsvc_ctrl = 286;
	const clop_altsvc = 287;
	const clop_maxage_conn = 288;
	const clop_sasl_authzid = 289;
	const clop_mail_rcpt_allowfails = 290;
	const clop_ssl_cert_blob = 291;
	const clop_ssl_key_blob = 292;
	const clop_proxy_ssl_cert_blob = 293;
	const clop_proxy_ssl_key_blob = 294;
	const clop_issuer_cert_blob = 295;
	const clop_proxy_issuer_cert = 296;
	const clop_proxy_issuer_cert_blob = 297;
	const clop_ssl_ec_curves = 298;
	const clop_hsts_ctrl = 299;
	const clop_hsts = 300;
	const clop_hsts_read_function = 301;
	const clop_hsts_read_data = 302;
	const clop_hsts_write_function = 303;
	const clop_hsts_write_data = 304;
	const clop_aws_sigv4 = 305;
	const clop_doh_ssl_verify_peer = 306;
	const clop_doh_ssl_verify_host = 307;
	const clop_doh_ssl_verify_status = 308;
	const clop_ca_info_blob = 309;
	const clop_proxy_ca_info_blob = 310;
	const clop_ssh_host_public_key_sha256 = 311;
	const clop_prereq_function = 312;
	const clop_prereq_data = 313;
	const clop_max_lifetime_conn = 314;
	const clop_mime_optinos = 315;
	const clop_ssh_host_key_function = 316;
	const clop_ssh_host_key_data = 317;
	const clop_protocols_str = 318;
	const clop_redir_protocols_str = 319;
	const clop_ws_options = 320;
	const clop_ca_cache_timeout = 321;
	const clop_quick_exit = 322;

	::arraySort <- function(arr){
		if(typeof arr != "array")	// Skip sorting if it's not an array
		return arr;	// or if there's nothing to sort

		if(arr.len() <= 1) return arr
			local needsort = true;

			while(needsort) {
				needsort = false;
				for(local i = 0; i < arr.len() - 2; i++) {
					if(arr[i] > arr[i+1]) {
						local temp = arr[i];
						arr[i] = arr[i+1];
						arr[i+1] = temp;
						needsort = true;
					}
				}
			}

		return arr;
	};

	::jsonWrite <- function(Table) {
		if(typeof Table == "null")
			return "null";
		if(typeof(Table)!="array" && typeof(Table)!="table")
			return Table.tostring();
		local Out = "";
		local AsString = function(Item) {
			switch(typeof(Item)) {
				case "table":
				case "array":
					return jsonWrite(Item);
					break;

				case "string":
					local Len = Item.len();
					local Str = "";
					for(local i=0;i<Len;i++) {
						if(Item[i]=='\\' || Item[i]=='\"')
							Str+="\\";
						Str+=Item.slice(i, i+1);
					}
					return "\""+Str+"\"";
					break;

				case "null":
					return "null";
					break;

				default:
					if("tostring" in Item)
						return Item.tostring();
					else
						return Item;
			}
		}

		if(typeof(Table) == "table") {
			if(Table.len() == 0) return "{}";
			Out = "{";
			foreach(Key,Val in Table)
				Out += "\""+Key+"\":"+AsString(Val)+", ";
			return Out.slice(0,-2) + "}";
		}

		if(typeof(Table) == "array") {
			if(Table.len() == 0) return "[]";
			Out = "[";
			foreach(Val in Table)
				Out += AsString(Val)+", ";
			return Out.slice(0,-2) + "]";
		}
	};

	::min <- function(a, b) {
		if(a < b) return a;
		else return b;
	};

	::max <- function(a, b) {
		if(a > b) return a;
		else return b;
	};

	::choose <- function(...) {
		if(vargv.len() == 0)
			return null;
		return vargv[randInt(vargv.len())];
	};

	::wavg <- function(a, b, w) {
		return (1 - w) * a + w * b;
	};

	::deepClone <- function(obj) {
		if (typeof obj == "array") {
			local result = [];
			foreach (item in obj) {
				result.append(deepClone(item));
			}
			return result;
		} else if (typeof obj == "table") {
			local result = {};
			foreach (key, value in obj) {
				result[key] <- deepClone(value);
			}
			return result;
		} else {
			return obj;
		}
	};

	::system <- function(var) { print("I can't let you do that, Dave."); };

	::int <- function(var) { return var.tointeger(); };
	::float <- function(var) { return var.tofloat(); };
	::str <- function(var) { return var.tostring(); };
	::char <- function(var) { return var.tochar(); };
	::bool <- function(var) { return (var && true); };

	::eval <- function(expression) { return compilestring("return ("+expression+");")(); };

	::drawSprite <- function(i, f, x, y, a = 0, l = 0, sx = 1.0, sy = 1.0, p = 1.0, c = 0xffffffff) { drawSpriteExMod(i, f, x, y, a, l, float(sx), float(sy), p, c); };
	::newSprite <- function(i, w = 0, h = 0, px = 0, py = 0, m = 0, p = 0) { return __newSprite__OP__(i, w, h, px, py, m, p); };
	::newSpriteFT <- function(t, w = 0, h = 0, px = 0, py = 0, m = 0, p = 0) { return __newSpriteFT__OP__(t, w, h, px, py, m, p); };

	::shuffle <- function(arr) {
		if(typeof arr == "table") {
			local na = [];
			foreach(i in arr) {
				na.push(i);
			}
			return shuffle(na);
		}

		if(typeof arr != "array")
			return [arr];

		local na = clone(arr);

		for(local i = na.len() - 1; i >= 1; i--) {
			local j = floor(randInt(na.len()) % (i + 1));
			local t = na[i];
			na[i] = na[j];
			na[j] = t;
		}

		return na;
	};

	::chunk <- function(str, size) {
		if(typeof str != "string" || size <= 0)
			return [];

		local chunks = [];
		local l = str.len();
		for(local i = 0; i < l; i += size) {
			if(i + size < l)
				chunks.append(str.slice(i, i + size));
			else
				chunks.append(str.slice(i));
		}
		return chunks;
	};

	print("Imported core lib.");)rew";

	ssq::Script script = gvSquirrel.compileSource(cmd, "core.nut");
	gvSquirrel.run(script);
}


/** General API functions */

void xyDonut(const std::string& file) {
	xyPrint("Running %s...", file.c_str());
	ssq::Script script = gvSquirrel.compileFile(file.c_str());
	gvSquirrel.run(script);
}

void xyRequire(const std::string& file) {
	gvDidError = false;

	xyDonut(file);

	if(gvDidError)
		xyEnd();
}

void xyDostr(const std::string& str) {
	ssq::Script script = gvSquirrel.compileSource(str.c_str(), "std::string");
	gvSquirrel.run(script);
}


void xyRegisterCoreAPI(ssq::VM& vm) {
	vm.addFunc("import", xyDonut); // Clone of `donut()`
	vm.addFunc("donut", xyDonut); // Doc'd
	vm.addFunc("require", xyRequire);
	vm.addFunc("dostr", xyDostr); // Doc'd
}
