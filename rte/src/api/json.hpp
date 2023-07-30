//  Brux - JSON API
//  Copyright (C) 2023 Vankata453
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

#ifndef BRUX_API_JSON_HEADER
#define BRUX_API_JSON_HEADER

#ifndef BRUX_API_GEN

#include <string>

#include <squirrel.h>

#endif

namespace BruxAPI {

//////////
// JSON //
//////////

SQInteger jsonRead(HSQUIRRELVM v, const std::string& str); // Doc'd

} // namespace BruxAPI

#endif
