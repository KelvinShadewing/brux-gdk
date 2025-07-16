//  Brux - Actors
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

/*=============*
| ACTORS SOURCE |
\*=============*/

#include "brux/main.hpp"
#include "brux/global.hpp"
#include "brux/core.hpp"

/*
 # Actor standard lib is embedded in the RTE so
 # that users do not need to include actors.nut
 # in every project. Using actors.nut is still
 # an option for anyone wanting to modify the
 # functionality.
\*/

void xyLoadActors() {
	const char* cmd = R"rew(::actor <- {}
	::__actlast__ <- 0;
	::__actor_delete_list__ <- [];

	::Actor <-class{
		id = 0;
		x = 0.0;
		y = 0.0;
		persistent = false;

		constructor(_x, _y, _arr = null) {
			x = _x;
			y = _y;
		};

		function run() {
		};

		function destructor() {
		};

		function colist(name) {
			/*Add self to new list in actor table*/
			/*Useful if actor needs to identify as more than one thing*/
			if(!actor.rawin(name)) actor.name <- {};
			actor[name][id] <- this;
		};
	};

	::newActor <- function(type, x, y, arr = null) {
		local na = type(x, y, arr);
		na.id = __actlast__;
		actor[__actlast__] <- na;
		if(!actor.rawin(typeof na))
			actor[typeof na] <- {};
		actor[typeof na][__actlast__] <- na;
		__actlast__++;
		return na.id;
	};

	::__deleteActor_true__ <- function(id) {
		if(!actor.rawin(id))
			return;

		local cat = typeof actor[id];
		delete actor[cat][id];
		actor[id].destructor();
		delete actor[id];
	};

	::deleteActor <- function(id) {
		if(!(id in actor))
			return;
		if(typeof actor[id] == "table")
			return;

		__actor_delete_list__.push(id);
		// actor[id] = false;
	}

	::deleteAllActors <- function(ignorePersistent = false) {
		if(ignorePersistent) {
			actor.clear();
			return;
		}

		local didFind = true;

		if(actor.len() == 0)
			return;

		while(didFind) {
			didFind = false;
			foreach(key, i in actor) {
				if(typeof i == "table") continue;

				if(("persistent" in i && !i.persistent)) {
					didFind = true;
					__deleteActor_true__(key);
				}
			}
		}
	};

	::countActors <- function() {
		local c = 0;
		foreach(i in actor) {
			if(typeof i != "table")
				c++;
		}
		return c;
	};

	::runActors <- function() {
		foreach(i in actor) {
			if(typeof i != "table" && "run" in i && typeof i.run == "function")
				i.run();
		}

		for(local i = 0; i < __actor_delete_list__.len(); i++) {
			__deleteActor_true__(__actor_delete_list__[i]);
		}
		__actor_delete_list__.clear();
	};

	::checkActor <- function(id) {
		if(!(id in actor) || actor[id] == false)
			return false;
		if(typeof id == "string")
			return actor.rawin(id) && actor[id].len() > 0;
		if(typeof id == "integer")
			return actor.rawin(id);
	};

	print("Imported actors lib."))rew";

	ssq::Script script = gvSquirrel.compileSource(cmd, "actors.nut");
	gvSquirrel.run(script);
}
