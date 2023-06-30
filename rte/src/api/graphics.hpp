//  Brux - Graphics API
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

#ifndef BRUX_API_GRAPHICS_HEADER
#define BRUX_API_GRAPHICS_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// Graphics
void clearScreen(); // Doc'd
void setDrawTarget(int tex); // Doc'd
int getDrawTarget(); // Doc'd
void resetDrawTarget();
void drawImage(int img, int x, int y); // Doc'd
void drawImagePart(int img, int x, int y, int ox, int oy, int w, int h);
void drawImageEx(int img, int x, int y, float a, int f, int w, int h, int c);
void setDrawColor(int color); // Doc'd
int loadImage(const std::string& file); // Doc'd
int loadImageKeyed(const std::string& file, int key); // Doc'd
void setBackgroundColor(int color); // Doc'd
void setScaling(float scale);
void setScalingFilter(int hint); // Doc'd
void setResolution(int w, int h); // Doc'd
int screenW(); // Doc'd
int screenH(); // Doc'd
int windowW();
int windowH();
int newTexture(int w, int h); // Doc'd
void textureSetBlendMode(int texture, int blend); // Doc'd
int findTexture(const std::string& name);
std::string getTextureName(int texture);
void printTextureNames();

} // namespace BruxAPI

#endif
