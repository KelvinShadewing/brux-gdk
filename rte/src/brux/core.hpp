//  Brux - Core
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
| CORE HEADER |
\*===========*/

#ifndef _CORE_H_
#define _CORE_H_

#include <string>

namespace ssq {
	class VM;
}

void xyLoadCore();
void xyLoadActors();

/** General API functions */
void xyDonut(const std::string& file);
void xyRequire(const std::string& file);
void xyDostr(const std::string& str);

void xyRegisterCoreAPI(ssq::VM& vm);

#endif
