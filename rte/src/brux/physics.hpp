//
// Created by peter on 6/13/20.
//

#ifndef BRUX_GDK_PHYISICS_H
#define BRUX_GDK_PHYISICS_H

#ifdef DO_NOT_INCLUDE // Not to be compiled.

#include <chipmunk.h>
#include <vector>

class Physics
{
public:
	Physics();
	static int ChipMonkHelloWorld();
	void sceneStep();
	~Physics();
	cpBody *AddSimpleCircle(void * userData, cpFloat radius,cpFloat mass, cpVect pos);
	cpBody *AddSimpleBox(void * userData, cpFloat width, cpFloat height, cpFloat mass, cpVect pos);
	void AddLineSegment(cpVect start, cpVect end);
private:
	cpVect gravity;
	cpSpace *space;
	cpFloat timeStep;
	std::vector<cpBody*>  bodylist;
	std::vector<cpShape*> shapelist;
};

#endif

#endif //BRUX_GDK_PHYISICS_H
