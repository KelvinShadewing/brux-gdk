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

	function step(){
		drawSprite(sprite, frame, x, y);
	};

	function destructor(){
	};
};

::newActor <- function(type, x, y){
	local na = type(x, y);
	na.id = actlast;
	actor[actlast] <- na;
	actlast++;
	return na.id;
};

::deleteActor <- function(id){
	if(!actor.rawin(id)) return;

	actor[id].destructor();
	delete actor[id];
};

::countActors <- function(){
	print("Actor count: " + actor.len());
};

::runActors <- function(){
	foreach(i in actor) i.step();
};

::checkActor <- function(id){
	return actor.rawin(id);
};

//Game Actors
::TestBall <- class extends Actor{
	frame = 0;
	yspeed = 0;

	constructor(_x, _y){
		base.constructor(_x, _y);
		print("Made a ball.");
	};

	function step(){
		yspeed += 0.5;
		y += yspeed;
		if(y > 200) deleteActor(this.id);
		drawSprite(sprMidiP, frame + 104, x, y);
		if(frame < 7) frame += 1;
		else frame = 0;
	};

	function destructor(){
		print("Lost a ball.");
	};
};

::Physical <- class extends Actor{
	function move(_x, _y){
		x += _x;
		y += _y;
	};
};
