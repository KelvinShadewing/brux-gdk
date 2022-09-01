/*=============*
| ACTORS SOURCE |
\*=============*/

#include "main.h"
#include "global.h"
#include "core.h"

/*
 # Actor standard lib is embedded in the RTE so
 # that users do not need to include actors.nut
 # in every project. Using actors.nut is still
 # an option for anyone wanting to modify the
 # functionality.
\*/

void xyLoadActors() {
	const SQChar *cmd = R"rew(::actor <- {}
	::actlast <- 0

	::Actor <-class{
		id = 0
		x = 0.0
		y = 0.0
		persistent = false

		constructor(_x, _y, _arr = null) {
			x = _x
			y = _y
		}

		function run() {
		}

		function destructor() {
		}

		function colist(name) {
			/*Add self to new list in actor table*/
			/*Useful if actor needs to identify as more than one thing*/
			if(!actor.rawin(name)) actor.name <- {}
			actor[name][id] <- this
		}
	}

	::newActor <- function(type, x, y, arr = null) {
		local na = type(x, y, arr)
		na.id = actlast
		actor[actlast] <- na
		if(!actor.rawin(typeof na)) actor[typeof na] <- {}
		actor[typeof na][actlast] <- na
		actlast++
		return na.id
	}

	::deleteActor <- function(id) {
		if(!actor.rawin(id)) return

		local cat = typeof actor[id]
		delete actor[cat][id]; actor[id].destructor()
		delete actor[id]
	}

	::deleteAllActors <- function(ignorePersistent = false) {
		local didFind = true

		while(didFind) {
			didFind = false
			foreach(key, i in actor) {
				if(typeof i == "table") continue

				if(!i.persistent || ignorePersistent) {
					didFind = true
					deleteActor(key)
				}
			}
		}
	}

	::countActors <- function() {
		local c = 0
		foreach(i in actor) {
			if(typeof i != "table") c++
		}
		return c
	}

	::runActors <- function() {
		foreach(i in actor) {
			if(typeof i != "table") i.run()
		}
	}

	::checkActor <- function(id) {
		return actor.rawin(id)
	}

	print("Imported actors lib."))rew";

	SQInteger oldtop = sq_gettop(gvSquirrel);
	sq_compilebuffer(gvSquirrel, cmd, (int)strlen(cmd) * sizeof(SQChar), "actors.nut", 1);
	sq_pushroottable(gvSquirrel);
	sq_call(gvSquirrel, 1, SQFalse, SQTrue);
	sq_settop(gvSquirrel, oldtop);
};
