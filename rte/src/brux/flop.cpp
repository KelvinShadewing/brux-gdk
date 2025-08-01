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

int gvSprPixels = 0; //Sprite to hold sample texture

// Draw a texture with an affine transformation for pseudo-3D
void xyFlopDraw(
	int src, // Source texture ID
	int x, // Output X position
	int y, // Output Y Position
	int w, // Output Width
	int h, // Output Height
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
	|| fov <= 0) {
		xyPrint("xyFlopDraw: Invalid parameters or texture ID.");
		xyPrint("Source: %i, X: %i, Y: %i, Width: %i, Height: %i",
			src, x, y, w, h);
		if(far <= near) {
			xyPrint("Near plane (%i) must be less than far plane (%i).", near, far);
		}
		if(fov <= 0) {
			xyPrint("Field of view (%i) must be greater than 0.", fov);
		}
		if(src >= static_cast<int>(vcTextures.size())) {
			xyPrint("Texture ID %i is out of bounds (max %zu).", src, vcTextures.size() - 1);
		}
		if(vcTextures[src] == nullptr) {
			xyPrint("Texture ID %i is null.", src);
		}
		return;
	}

	// Temporary sprite to render individual pixels
	if(gvSprPixels == 0) {
		gvSprPixels = xyNewSpriteFT(src, 1, 1, 0, 0, 0, 0);
		if(gvSprPixels == 0) {
			xyPrint("Failed to create temporary sprite for xyFlopDraw.");
			return;
		}
	}
	xyReplaceSpriteTexture(gvSprPixels, src, 1, 1, 0, 0, 0, 0);

	// Get points along near and far planes
	float fov_rad = static_cast<float>(fov) * 3.14159265f / 180.0f;
	float fov_scale = tan(fov_rad / 2.0f);

	float rad = static_cast<float>(ca) * 3.14159265f / 180.0f; // Convert angle to radians
	float fovScale = static_cast<float>(fov_rad) / 90.0f; // Normalize FOV (assuming 90 is default)
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

	int src_w = xySpriteCol(gvSprPixels);
	int src_h = xySpriteRow(gvSprPixels);

	float center_x = w / 2.0f;
	float horizon = h; // Camera at bottom of screen

	float angle_rad = static_cast<float>(ca) * 3.14159265f / 180.0f;
	float cos_a = cos(angle_rad);
	float sin_a = sin(angle_rad);

	for (int j = -h / 2; j < h / 2; j++) {
		float z = near + (far - near) * ((float)j / (float)h);

		for (int i = 0; i < w; i++) {
			float dx = (i - center_x) / (h * fov_scale);
			float dy = z;

			// World position
			float world_x = cx + dx * cos_a - dy * sin_a;
			float world_y = cy + dx * sin_a + dy * cos_a;

			int ix = static_cast<int>(world_x) % src_w;
			int iy = static_cast<int>(world_y) % src_h;
			if (ix < 0) ix += src_w;
			if (iy < 0) iy += src_h;

			int frame = ix + iy * src_w;
			xyDrawSpriteExMod(gvSprPixels, frame, x + (i * scale), y + (j * scale), 0, SDL_FLIP_NONE, scale, scale, 1.0, 0xFFFFFFFF);
		}
	}

}

void xyRegisterFlopAPI(ssq::VM& vm) {
	vm.addFunc("flopDraw", xyFlopDraw);
};