/*===========*\
| TEXT HEADER |
\*===========*/

#ifndef _TEXT_H_
#define _TEXT_H_

class xyFont{
private:
	xySprite* source;
	vector<int[2]> x;
	char start;
	Uint32 numero;
	bool monospace;

public:
	xyFont(Uint32 index, char firstchar, Uint8 threshold);
};

#endif
