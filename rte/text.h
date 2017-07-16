/*===========*\
| TEXT HEADER |
\*===========*/

#ifndef _TEXT_H_
#define _TEXT_H_

class xyFont{
private:
	xySprite* source;
	vector<int> x0, x1;
	char start;
	Uint32 numero;

public:
	xyFont(Uint32 index, char firstchar, Uint8 threshold);
};

#endif
