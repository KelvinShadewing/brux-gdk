//  Brux - Main API
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

#ifndef BRUX_API_MAIN_HEADER
#define BRUX_API_MAIN_HEADER

#ifndef BRUX_API_GEN

#include <string>

#endif

namespace BruxAPI {

// Main
void wait(int seconds); // Doc'd
void update(); // Doc'd
std::string getOS(); // Doc'd
int getTicks(); // Doc'd
int getFPS(); // Doc'd
void setFPS(int max_fps); // Doc'd
void setWindowTitle(const std::string& title); // Doc'd
void setWindowIcon(const std::string& file); // Doc'd
int getFrames(); // Doc'd
int displayW(); // Doc'd
int displayH(); // Doc'd
std::string bruxVersion(); // Doc'd
void toggleFullscreen(); // Doc'd

} // namespace BruxAPI

#endif
