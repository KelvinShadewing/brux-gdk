//  Brux - Texture
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

/*==============*\
| TEXTURE HEADER |
\*==============*/

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

class Texture {
private:
	Uint32 numero, mar, pad, w, h, tex, col, row, frames = 0;
	bool didLoad;
public:
	Uint32 getnum() const { return numero; }
	Uint32 gettex() const { return tex; }
	Uint32 getw() const { return w; }
	Uint32 geth() const { return h; }
	const char* getname() const { return name.c_str(); }
}

#endif