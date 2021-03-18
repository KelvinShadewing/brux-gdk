/*=============*\
| ACTORS SOURCE |
\*=============*/

#include "main.h"
#include "global.h"
#include "core.h"

void xyLoadActors()
{
	const SQChar *cmd =" \
     \
    ::actor <- {}; \
    ::actlast <- 0; \
     \
    ::Actor <-class{ \
        id = 0; \
        x = 0; \
        y = 0; \
        sprite = 0; \
        shape = 0; \
        frame = 0; \
     \
        constructor(_x, _y){ \
            x = _x; \
            y = _y; \
        }; \
     \
        function run(){ \
            drawSprite(sprite, frame, x, y); \
        }; \
     \
        function destructor(){ \
        }; \
    }; \
     \
    ::newActor <- function(type, x, y){ \
        local na = type(x, y); \
        na.id = actlast; \
        actor[actlast] <- na; \
        actlast++; \
        return na.id; \
    }; \
     \
    ::deleteActor <- function(id){ \
        if(!actor.rawin(id)) return; \
     \
        actor[id].destructor(); \
        delete actor[id]; \
    }; \
     \
    ::countActors <- function(){ \
        print(\"Actor count: \" + actor.len()); \
    }; \
     \
    ::runActors <- function(){ \
        foreach(i in actor) i.run(); \
    }; \
     \
    ::checkActor <- function(id){ \
        return actor.rawin(id); \
    }; \
	 \
	print(\"Imported actors lib.\");";

	SQInteger oldtop = sq_gettop(gvSquirrel);
	sq_compilebuffer(gvSquirrel, cmd, (int)strlen(cmd) * sizeof(SQChar), "actors.nut", 1);
	sq_pushroottable(gvSquirrel);
	sq_call(gvSquirrel, 1, SQFalse, SQTrue);
	sq_settop(gvSquirrel, oldtop);
};
