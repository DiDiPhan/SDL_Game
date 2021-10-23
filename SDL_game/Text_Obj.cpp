#include "Text_Obj.h"

#undef main

Text_Obj::Text_Obj()
{
	;
}
Text_Obj::~Text_Obj()
{
	;
}

void Text_Obj::SetText(const string& str_val)
{
	text_str = str_val;
}

void Text_Obj::SetColor(const int& val)
{
	if (val == WHITE_TEXT)
	{
		SDL_Color clor = { 255, 255, 255 };
		text_clor = clor;
	}
	else
		if (val == RED_TEXT)
		{
			SDL_Color clor = { 255, 0, 0 };
			text_clor = clor;
		}
		else
			if (val == YELLOW_TEXT)
			{
				SDL_Color clor = { 255, 255, 0 };
				text_clor = clor;
			}

}

SDL_Rect Text_Obj::CreatGameText(TTF_Font* font, SDL_Surface* des)
{
	p_obj_ = TTF_RenderText_Solid(font, text_str.c_str(), text_clor);
	//delete p_obj_;

	SDL_Rect rect = ShowCaret(des);
	SDL_FreeSurface(p_obj_);
	p_obj_ = NULL;
	return rect;
}

