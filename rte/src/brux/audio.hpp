//  Brux - Audio
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

/*============*\
| AUDIO HEADER |
\*============*/

#ifndef _AUDIO_H_
#define _AUDIO_H_

Uint32 xyLoadSound(const std::string& filename);
Uint32 xyLoadMusic(const std::string& filename);
void xyDeleteSound(Uint32 sound);
void xyDeleteMusic(Uint32 music);
int xyPlaySound(Uint32 sound, Uint32 loops);
int xyPlayMusic(Uint32 music, Uint32 loops);
void xyStopSound(Uint32 sound);


#endif
