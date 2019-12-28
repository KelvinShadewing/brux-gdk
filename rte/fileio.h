/*===============*\
| FILE I/O HEADER |
\*===============*/



#ifndef _FILEIO_H_
#define _FILEIO_H_

#include "main.h"

bool xyFileExists(const char* file);
void sqDecodeJSONTable(HSQUIRRELVM v, cJSON *Item);
SQInteger sqDecodeJSON(HSQUIRRELVM v);

////////////////////
// FILE I/O CLASS //
///////////////////{

class xyIO{
private:
    FILE *f;
    string n;
public:
    xyIO(string fname);
};

//}

#endif
