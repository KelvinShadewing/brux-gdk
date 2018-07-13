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
	char start;
	Uint32 numero;
	bool mono;

public:
	xyFont(Uint32 index, char firstchar, Uint8 threshold, bool monospace);
	void draw(int x, int y, string text);
};

#endif
