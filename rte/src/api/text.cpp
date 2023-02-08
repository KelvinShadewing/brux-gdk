//  Brux - Text API
//  Copyright (C) 2016 KelvinShadewing
//                2023 Vankata453
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
