/*===========*\
| TEXT HEADER |
\*===========*/

#ifndef _TEXT_H_
#define _TEXT_H_

void xyDrawText(float x, float y, const char* text, Uint32 font, Uint32 color, int halign, int valign);	//Draw a string of text
Uint32 xyOpenFont(const char* filename, Uint32 size);														//Create a new font from a file
void xyCloseFont(Uint32 font);																		//Delete a font

#endif