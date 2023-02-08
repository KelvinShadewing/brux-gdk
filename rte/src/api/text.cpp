#include "api/text.hpp"

#include "brux/main.hpp"

#include "brux/global.hpp"
#include "brux/text.hpp"

namespace BruxAPI {

//////////
// TEXT //
//////////

int newFont(int i, int c, int t, bool m, int k) {
	// Sanitize inputs
	if (i < 0) i = 0;
	if (t > 255) t = 255;
	if (c > 255) c = 255;

	xyFont* newfont = new xyFont(i, (char)c, t, m, k);
	return newfont->getnum();
}

/** Macro to help easily check if a font is valid. **/
#define FONT_CHECK_VALID  if (f >= vcFonts.size() || vcFonts[f] == 0) return

void drawText(int f, int x, int y, const std::string& s) {
	FONT_CHECK_VALID;
	vcFonts[f]->draw(x, y, s);
}

SQInteger chint(HSQUIRRELVM v, int i) {
	const char s = (const char)i;

	sq_pushstring(v, &s, 1);

	return 1; // Returns data.
}

} // namespace BruxAPI
