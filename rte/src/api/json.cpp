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

#include "api/json.hpp"

#include "brux/main.hpp"

#include "brux/fileio.hpp"

namespace BruxAPI {

//////////
// JSON //
//////////

SQInteger jsonRead(HSQUIRRELVM v, const std::string& str) {
	sqDecodeJSON(v, str.c_str());
	return 1;
}

} // namespace BruxAPI
