#include "api/json.hpp"

#include "brux/main.hpp"

#include "brux/fileio.hpp"

namespace BruxAPI {

//////////
// JSON //
//////////

SQInteger jsonRead(HSQUIRRELVM v, const std::string& str) {
	sqDecodeJSON(v, str.c_str());
	return 1; // Returns data.
}

} // namespace BruxAPI
