//  Brux - Text
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
| TEXT SOURCE |
\*===========*/

#include <cctype>
#include <string>
#include "brux/text.hpp"

#include <simplesquirrel/vm.hpp>

#include "brux/global.hpp"
#include "brux/graphics.hpp"
#include "brux/main.hpp"
#include "brux/sprite.hpp"

// New bitmap font format to replace SDL_ttf.
// 
// When created, it takes an existing sprite
// to use as a bitmap font.
// 
// Each frame of the sprite is scanned,
// checking each pixel column for transparency
// to find the minimum and maximum X
// coordinates containing pixels with alpha
// values above the threshold.
// 
// Might be a good idea to bring back SDL_ttf
// to create bitmap fonts but use the same
// system either way to render.

xyFont::xyFont(Uint32 index, Uint32 firstchar, Uint8 threshold, bool monospace, int _kern, int emptyWidth) {
	// If there is no sprite that can be used, then cancel
	if(vcSprites.size() <= index || vcSprites[index] == 0) {
		xyPrint("The sprite does not exist!");
		delete this;
		return;
	}

	// Add to the list
	numero = -1;
	if(vcFonts.size() == 0) {
		vcFonts.push_back(this);
		numero = 0;
	} else {
		// Check for an open space in the list
		for(int i = 1; i < static_cast<int>(vcFonts.size()); i++) {
			if(vcFonts[i] == 0) {
				vcFonts[i] = this;
				numero = i;
				break;
			}
		}

		// If an open space wasn't found
		if(numero == -1) {
			vcFonts.push_back(this);
			numero = static_cast<int>(vcFonts.size()) - 1;
		}
	}

	// Get the sprite
	source = vcSprites[index];

	// Get frame number and x/width
	cx.resize(source->getframes());
	cw.resize(source->getframes());

	if(cx.size() > 0) {
		for(Uint32 i = 0; i < source->getframes(); i++) {
			cx[i] = 0;
			cw[i] = source->getw();
		}
	}

	// A monospace font is not scanned, but its ordinary space can still use
	// the explicit empty-character advance when one was supplied.
	if(monospace && emptyWidth > 0 && ' ' >= firstchar) {
		const Uint32 spaceFrame = static_cast<Uint32>(' ') - firstchar;
		if(spaceFrame < cw.size())
			cw[spaceFrame] = emptyWidth;
	}

	start = firstchar;
	kern = _kern;
	mono = monospace;

	if(!monospace) {
		SDL_Surface* ts = IMG_Load(source->source.c_str());
		if(ts == nullptr) {
			xyPrint("Could not load the bitmap font image for width scanning!");
			return;
		}

		// Scan each frame to find the minimum and maximum X coordinates
		// with non-transparent pixels. This is done by scanning left to right
		// for the minimum and right to left for the maximum.

		// Loop through each frame
		for(Uint32 i = 0; i < source->getframes(); i++) {
			// Find the minimum X coordinate with non-transparent pixels
			Uint32 minx = source->getw();
			bool found = false;
			for(Uint32 j = 0; j < source->getw(); j++) {
				for(Uint32 k = 0; k < source->geth(); k++) {
					Uint8 a = xyGetAlpha(xyGetSurfacePixel(ts, j + ((i % source->getcol()) * source->getw()), k + (i / source->getcol() * source->geth())));
					if(a > threshold) {
						minx = j;
						found = true;
						break;
					}
				}
				if(found)
					break;
			}

			// Find the maximum X coordinate with non-transparent pixels
			Uint32 maxx = 0;
			if(found) {
				for(Uint32 j = source->getw(); j-- > 0;) {
					bool foundRight = false;
					for(Uint32 k = 0; k < source->geth(); k++) {
						Uint8 a = xyGetAlpha(xyGetSurfacePixel(ts, j + ((i % source->getcol()) * source->getw()), k + (i / source->getcol() * source->geth())));
						if(a > threshold) {
							maxx = j;
							foundRight = true;
							break;
						}
					}
					if(foundRight)
						break;
				}
			}

			if(!found || i + start == ' ') {
				cx[i] = 0;
				cw[i] = emptyWidth > 0 ? emptyWidth : source->getw();
			} else {
				cx[i] = minx;
				cw[i] = maxx - minx + 1;
			}
		}

		SDL_FreeSurface(ts);
	}
};

int xyFont::characterWidth(char character) const {
	const int c = static_cast<unsigned char>(character) - start;
	if(c >= 0 && static_cast<size_t>(c) < cw.size())
		return cw[c] + kern;
	return source->getw() + kern;
}

int xyFont::textWidth(const std::string& text) const {
	int width = 0;
	for(size_t i = 0; i < text.length(); i++) {
		if(text[i] == '~' && i + 1 < text.length() && std::isalnum(static_cast<unsigned char>(text[i + 1]))) {
			i++;
			continue;
		}
		width += characterWidth(text[i]);
	}
	return width;
}

std::string xyFont::wrapText(const std::string& text, int wrapWidth) const {
	if(wrapWidth <= 0)
		return text;

	std::string wrapped;
	std::string token;
	std::string spaces;
	int lineWidth = 0;

	auto appendToken = [&]() {
		if(token.empty())
			return;

		const int tokenWidth = textWidth(token);
		const int spaceWidth = textWidth(spaces);
		if(lineWidth > 0 && lineWidth + spaceWidth + tokenWidth > wrapWidth) {
			wrapped += '\n';
			lineWidth = 0;
			spaces.clear();
		}
		else if(lineWidth > 0) {
			wrapped += spaces;
			lineWidth += spaceWidth;
		}

		wrapped += token;
		lineWidth += tokenWidth;
		token.clear();
		spaces.clear();
	};

	for(size_t i = 0; i < text.length(); i++) {
		const char ch = text[i];
		if(ch == '\n') {
			appendToken();
			wrapped += '\n';
			lineWidth = 0;
			spaces.clear();
		}
		else if(ch == ' ') {
			appendToken();
			spaces += ch;
		}
		else {
			token += ch;
			// Keep a hyphen on the preceding line, but allow a break after it.
			if(ch == '-')
				appendToken();
		}
	}
	appendToken();

	return wrapped;
}

void xyFont::draw(int x, int y, std::string text, Uint32 color, int wrapWidth) {
	text = wrapText(text, wrapWidth);
	int dx = x, dy = y; // Set cursor start position
	int c; // Current character by font index
	float alpha = (1.0f / 255.0f) * (color & 0xff);

	Uint32 curcol = color;

	// Loop to end of std::string
	for(int i = 0; i < static_cast<int>(text.length()); i++) {
		if (text[i] == '\n') {
			dy += source->geth();
			dx = x;
		} /* else if(text[i] == '$' && i < text.length() - 2 && text[i + 1] == '{') {
			// Special character support using frames from other sprites
			// Syntax: ${sprite,frame}

			std::string s = "";
			std::string f = "";
			SQInteger snum = 0;

			i += 2;

			xyPrint("Print A");

			while(text[i] != '}') {
				// Get the sprite and frame number
				while(text[i] != ',' && text[i] != '}') {
					s += text[i];
					i++;
				}
				i++;
				while(text[i] != '}') {
					f += text[i];
					i++;
				}
				i++;
			}

			xyPrint("Print B");

			// Translate the sprite variable name to a number
			sq_pushstring(gvSquirrel.getHandle(), s.c_str(), -1);
			sq_get(gvSquirrel.getHandle(), -1);
			sq_getinteger(gvSquirrel.getHandle(), -1, &snum);
			sq_pop(gvSquirrel.getHandle(), 2);

			xySprite* tempSrc = vcSprites[snum];
			c = std::stoi(f);
			tempSrc->draw(c, dx, dy);
			dx += tempSrc->getw() + kern;
		}*/
		else if(text[i] == '~' && i < text.length() - 1) {
			// Get next character for color code
			i++;
			if(isalnum(text[i])) {
				switch (text[i]) {
					case '0':
						curcol = color; // Normal
						break;
					case '1':
						curcol = 0x0000a8ff; // Dark Blue
						break;
					case '2':
						curcol = 0x00a800ff; // Dark Green
						break;
					case '3':
						curcol = 0xa80000ff; // Dark Red
						break;
					case '4':
						curcol = 0x006060ff; // Shadewing Teal
						break;
					case '5':
						curcol = 0xa800a8ff; // Dark Purple
						break;
					case '6':
						curcol = 0xf8a800ff; // Gold
						break;
					case '7':
						curcol = 0x808080ff; // Gray
						break;
					case '8':
						curcol = 0x505050ff; // Dark Gray
						break;
					case '9':
						curcol = 0x0000f8ff; // Blue
						break;
					case 'a':
					case 'A':
						curcol = 0x00f800ff; // Green
						break;
					case 'b':
					case 'B':
						curcol = 0x00f8f8ff; // Aqua
						break;
					case 'c':
					case 'C':
						curcol = 0xf80000ff; // Red
						break;
					case 'd':
					case 'D':
						curcol = 0xf800f8ff; // Purple
						break;
					case 'e':
					case 'E':
						curcol = 0xf8f800ff; // Yellow
						break;
					case 'f':
					case 'F':
						curcol = 0x000000ff; // Black
						break;
					case 'g':
					case 'G':
						curcol = 0xa8a8a8ff; // Light Gray
						break;
					case 'h':
					case 'H':
						curcol = 0xf88080ff; // Light Red
						break;
					case 'i':
					case 'I':
						curcol = 0x80f880ff; // Light Green
						break;
					case 'j':
					case 'J':
						curcol = 0xb0b0f8ff; // Light Blue
						break;
					case 'k':
					case 'K':
						curcol = 0x00d0d0ff; // Light Teal
						break;
					case 'l':
					case 'L':
						curcol = 0xf880f8ff; // Light Purple
						break;
					case 'm':
					case 'M':
						curcol = 0xf8f880ff; // Light Yellow
						break;
					case 'n':
					case 'N':
						curcol = 0xf8c870ff; // Tan
						break;
					case 'o':
					case 'O':
						curcol = 0x805010ff; // Brown
						break;
					case 'p':
					case 'P':
						curcol = 0xf868b0ff; // Pink
						break;
					case 'q':
					case 'Q':
						curcol = 0xf8b8d0ff; // Light Pink
						break;
					case 'r':
					case 'R':
						curcol = 0xf84068; // Dark Pink
						break;
					case 's':
					case 'S':
						curcol = 0x4880b8ff; // Steel Blue
						break;
					case 't':
					case 'T':
						curcol = 0x00a0a0ff; // Teal
						break;
					case 'u':
					case 'U':
						curcol = 0x303030ff; // Charcoal
						break;
					case 'v':
					case 'V':
						curcol = 0xf0f0e0ff; // Eggshell
					case 'w':
					case 'W':
						curcol = 0x8080a0ff; // Slate
					case 'x':
					case 'X':
						curcol = 0x704838ff; // Coffee
						break;
					case 'y':
					case 'Y':
						curcol = 0x80a080ff; // Olive
						break;
					case 'z':
					case 'Z':
						curcol = 0xb02050ff; // Rose
				}
			}
			else if(text[i] != '~')
				i--;
			else {
				c = (int)text[i] - start; // Get current character and apply font offset
				if (c >= 0 && static_cast<size_t>(c) < cw.size()) {
					source->draw(c, dx - cx[c], dy, 0, SDL_FLIP_NONE, 1, 1, alpha, curcol);
					dx += cw[c] + kern;
				} else {
					dx += source->getw() + kern;
				}
			}
		}
		else {
			c = (int)text[i] - start; // Get current character and apply font offset
			if (c >= 0 && static_cast<size_t>(c) < cw.size()) {
				source->draw(c, dx - cx[c], dy, 0, SDL_FLIP_NONE, 1, 1, alpha, curcol);
				dx += cw[c] + kern;
			} else {
				dx += source->getw() + kern;
			}
		}
	}
};

int xyFont::lineCount(const std::string& text, int wrapWidth) const {
	const std::string wrapped = wrapText(text, wrapWidth);
	int lines = 1;
	for(char character : wrapped) {
		if(character == '\n')
			lines++;
	}
	return lines;
}

Uint32 xyFont::getnum() {
	return numero;
};


/** API */

int xyNewFont(int i, int c, int t, bool m, int k, int emptyWidth) {
	// Sanitize inputs
	if (i < 0) {
		i = 0;
	}
	else if (t > 255) {
		t = 255;
	}
	else if (c > 255) {
		c = 255;
	}

	if(emptyWidth < 0)
		emptyWidth = 0;

	xyFont* newfont = new xyFont(i, static_cast<char>(c), static_cast<unsigned char>(t), m, k, emptyWidth);
	return newfont->getnum();
}

#define FONT_CHECK_VALID  if (f < 0 || f >= static_cast<int>(vcFonts.size()) || vcFonts[f] == 0) return

void xyDrawText(int f, float x, float y, const std::string& s, Uint32 c, int wrapWidth) {
	FONT_CHECK_VALID;
	vcFonts[f]->draw(static_cast<int>(x), static_cast<int>(y), s, c, wrapWidth);
}

#undef FONT_CHECK_VALID

int xyTextLineCount(int f, const std::string& s, int wrapWidth) {
	if(f < 0 || f >= static_cast<int>(vcFonts.size()) || vcFonts[f] == 0)
		return 0;
	return vcFonts[f]->lineCount(s, wrapWidth);
}

std::string xyChint(int i) {
	return std::string(1, static_cast<char>(i));
}


void xyRegisterTextAPI(ssq::VM& vm) {
	vm.addFunc("newFont", xyNewFont, ssq::DefaultArguments<int>(0)); // Doc'd
	vm.addFunc("drawText", xyDrawText, ssq::DefaultArguments<Uint32, int>(0xffffffff, 0)); // Doc'd
	vm.addFunc("textLineCount", xyTextLineCount, ssq::DefaultArguments<int>(0)); // Doc'd
	vm.addFunc("textWrap", [](int f, const std::string& s, int wrapWidth) {
		if(f < 0 || f >= static_cast<int>(vcFonts.size()) || vcFonts[f] == 0)
			return std::string();
		return vcFonts[f]->wrapText(s, wrapWidth);
	}, ssq::DefaultArguments<int>(0)); // Doc'd
	vm.addFunc("chint", xyChint); // Doc'd
	vm.addFunc("textWidth", [](int f, const std::string& s) {
		if(f < 0 || f >= static_cast<int>(vcFonts.size()) || vcFonts[f] == 0)
			return 0;
		return vcFonts[f]->textWidth(s);
	}); // Doc'd
}
