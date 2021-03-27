////////////
// ACTORS //
////////////

//Main
::actor <- {};
::actlast <- 0;

::Actor <-class{
	id = 0;
	x = 0;
	y = 0;
	sprite = 0;
	shape = 0;
	frame = 0;

	constructor(_x, _y){
		x = _x;
		y = _y;
	};

	function run(){
		drawSprite(sprite, frame, x, y);
	};

	function destructor(){
	};
};

::newActor <- function(type, x, y){
	local na = type(x, y);
	na.id = actlast;
	actor[actlast] <- na;
	if(!actor.rawin(typeof na)) actor[typeof na] <- {};
	actor[typeof na][actlast] <- na;
	actlast++;
	return na.id;
};

::deleteActor <- function(id){
	if(!actor.rawin(id)) return;

	local cat = typeof actor[id];
	delete actor[cat][id];
	actor[id].destructor();
	delete actor[id];
};

::countActors <- function(){
	print("Actor count: " + actor.len());
};

::runActors <- function(){
	foreach(i in actor) i.run();
};

::checkActor <- function(id){
	return actor.rawin(id);
};
