/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/
#pragma once

#include "Base_Obj.h"
#include "Common_Func.h"

class Text_Obj : public Base_Obj
{
public:
	enum TextColor
	{
		NONE,
		WHITE_TEXT,
		RED_TEXT,
		YELLOW_TEXT
	};
	Text_Obj();
	~Text_Obj();

	void SetText(const string&);

	void SetColor(const int&);

	SDL_Rect CreatGameText(TTF_Font*, SDL_Surface*);

private:
	string text_str;
	SDL_Color text_clor;
};