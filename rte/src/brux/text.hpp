/*===========*\
| TEXT HEADER |
\*===========*/

#ifndef _TEXT_H_
#define _TEXT_H_

class xyFont
{
private:
	xySprite* source;
	std::vector<int> cx;
	std::vector<int> cw;
	Uint32 start;
	Uint32 numero;
	bool mono;
	int kern; //Kerning can be negative since some fonts need to overlap a bit

public:
	xyFont(Uint32 index, Uint32 firstchar, Uint8 threshold, bool monospace, int _kern);
	Uint32 getnum();
	void draw(int x, int y, std::string text);
};

#endif
