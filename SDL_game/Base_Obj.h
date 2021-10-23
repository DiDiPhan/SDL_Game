/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/
#pragma once

#include "Common_Func.h"

class Base_Obj
{
protected:
	SDL_Rect rect_;
	SDL_Surface* p_obj_;
public:
	Base_Obj();
	~Base_Obj();
	SDL_Rect ShowCaret(SDL_Surface*);
	bool LoadImg(const string);
	void SetRect(const int&, const int&);
	void SetRect(const SDL_Rect&);
	SDL_Rect GetRect() const;
	SDL_Surface* Get_obj();

};