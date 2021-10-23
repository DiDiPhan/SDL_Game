/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/
#pragma once

#include "Common_Func.h"
#include "Base_Obj.h"

const int EXP_W = 165;
const int EXP_H = 165;

class Explosion_Obj : public Base_Obj
{
private:
	int frame;
	SDL_Rect clip[4];
public:
	Explosion_Obj();
	~Explosion_Obj();
	void SetClip();
	void SetFrame(const int&);
	void ShowEx(SDL_Surface*);
};