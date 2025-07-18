//  Brux - Flat Layer Oriented Perspective
//  Copyright (C) 2025 KelvinShadewing
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
| FLOP SOURCE |
\*===========*/

#include <simplesquirrel/vm.hpp>

#include "brux/flop.hpp"
#include "brux/sprite.hpp"

#include "brux/main.hpp"
#include "brux/global.hpp"

// Draw a texture with an affine transformation for pseudo-3D
void xyFlopDraw(
	int src, // Source texture ID
	int x, // Output X position
	int y, // Output Y position
	int w, // Output width
	int h, // Output height
	int cx, // Camera X position
	int cy, // Camera Y position
	int ca, // Camera angle
	int near, // Near plane distance
	int far, // Far plane distance
	int fov, // Field of view
	int scale // Scaling factor
) {
	if (src < 0
	|| src >= static_cast<int>(vcTextures.size())
	|| vcTextures[src] == nullptr
	|| near <= 0
	|| far <= 0
	|| far <= near
	|| fov <= 0)
		return; // Invalid texture IDs or parameters

	// Temporary sprite to render individual pixels
	int tspr = xyNewSpriteFT(src, 1, 1, 0, 0, 0, 0);

	// Get points along near and far planes
	float rad = static_cast<float>(ca) * 3.14159265f / 180.0f; // Convert angle to radians
	float fovScale = static_cast<float>(fov) / 90.0f; // Normalize FOV (assuming 90 is default)
	float nx0 = cx + near * cos(rad) * fovScale;
	float ny0 = cy + near * sin(rad) * fovScale;
	float nx1 = cx - near * cos(rad) * fovScale;
	float ny1 = cy - near * sin(rad) * fovScale;
	float fx0 = cx + far * cos(rad) * fovScale;
	float fy0 = cy + far * sin(rad) * fovScale;
	float fx1 = cx - far * cos(rad) * fovScale;
	float fy1 = cy - far * sin(rad) * fovScale;
	float cnx = (nx0 + nx1 + fx0 + fx1) / 4.0f; // Center X coordinate
	float cny = (ny0 + ny1 + fy0 + fy1) / 4.0f; // Center Y coordinate

	for(int i = 0; i < w; i++) {
		for(int j = 0; j < h; j++) {
			// Calculate the pixel position in the destination texture
			float px = static_cast<float>(i) - static_cast<float>(w) / 2.0f;
			float py = static_cast<float>(j) - static_cast<float>(h) / 2.0f;

			// Calculate the affine transformation
			float tx = cnx + (px * (fx0 - nx0) / w) + (py * (fx1 - nx1) / h);
			float ty = cny + (px * (fy0 - ny0) / w) + (py * (fy1 - ny1) / h);

			// Draw the pixel at the transformed position
			xyDrawSpriteExMod(tspr, i + (j * xySpriteW(tspr)), x + static_cast<int>(tx * scale), y + static_cast<int>(ty * scale), 0, SDL_FLIP_NONE, 1.0f, scale, scale, 0xFFFFFFFF);
		}
	}

	// Delete temporary sprite
	xyDeleteSprite(tspr);
}

void xyRegisterFlopAPI(ssq::VM& vm) {
	vm.addFunc("flopDraw", xyFlopDraw);
};