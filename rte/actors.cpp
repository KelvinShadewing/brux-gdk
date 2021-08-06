/*=============*\
| ACTORS SOURCE |
\*=============*/

#include "main.h"
#include "global.h"
#include "core.h"

/*\
 # Actor standard lib is embedded in the RTE so
 # that users do not need to include actors.nut
 # in every project. Using actors.nut is still
 # an option for anyone wanting to modify the
 # functionality.
\*/

void xyLoadActors() {
	const SQChar *cmd =" \
	 \
	::actor <- {}; \
	::actlast <- 0; \
	 \
	::Actor <-class{ \
		id = 0; \
		x = 0.0; \
		y = 0.0; \
		sprite = 0; \
		frame = 0.0; \
	 \
		constructor(_x, _y){ \
			x = _x; \
			y = _y; \
		}; \
	 \
		function run(){ \
		}; \
	 \
		function destructor(){ \
		}; \
		\
		function colist(name) { \
			/*Add self to new list in actor table*/\
			/*Useful if actor needs to identify as more than one thing*/\
			if(!actor.rawin(name)) actor.name <- {}\
			actor[name][id] <- this\
		}\
	}; \
	 \
	::newActor <- function(type, x, y){\n\
		local na = type(x, y);\n\tna.id = actlast;\n\
		actor[actlast] <- na;\n\
		if(!actor.rawin(typeof na)) actor[typeof na] <- {};\n\
		actor[typeof na][actlast] <- na;\n\
		actlast++;\n\
		return na.id;\n\
	};\n\
	\n\
	::deleteActor <- function(id){\n\
	\tif(!actor.rawin(id)) return;\n\
	\n\
	\tlocal cat = typeof actor[id];\n\
	\tdelete actor[cat][id];\n\tactor[id].destructor();\n\
	\tdelete actor[id];\n\
	}; \
	 \
	::countActors <- function() {\n\
		local c = 0; \
		foreach(i in actor) {\n\
			if(typeof i != \"table\") c++; \n\
		}\n\
		return c;\n\
	};\n\
	 \
	::runActors <- function(){ \
		foreach(i in actor) {\n\
			if(typeof i != \"table\") i.run(); \
		}\
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
