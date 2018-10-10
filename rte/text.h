/*===========*\
| TEXT HEADER |
\*===========*/

#ifndef _TEXT_H_
#define _TEXT_H_

class xyFont{
private:
	xySprite* source;
	vector<int> cx;
	vector<int> cw;
	Uint32 start;
	Uint32 numero;
	bool mono;

public:
	xyFont(Uint32 index, Uint32 firstchar, Uint8 threshold, bool monospace);
	Uint32 getnum();
	void draw(int x, int y, string text);
};

#endif
