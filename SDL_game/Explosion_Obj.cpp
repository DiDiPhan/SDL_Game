#include "Explosion_Obj.h"

Explosion_Obj::Explosion_Obj()
{

}

Explosion_Obj::~Explosion_Obj()
{

}

void Explosion_Obj::SetClip()
{
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = EXP_W;
	clip[0].h = EXP_H;

	clip[1].x = EXP_W;
	clip[1].y = 0;
	clip[1].w = EXP_W;
	clip[1].h = EXP_H;

	clip[2].x = EXP_W * 2;
	clip[2].y = 0;
	clip[2].w = EXP_W;
	clip[2].h = EXP_H;

	clip[3].x = EXP_W * 3;
	clip[3].y = 0;
	clip[3].w = EXP_W;
	clip[3].h = EXP_H;
}

void Explosion_Obj::SetFrame(const int& fr)
{
	frame = fr;
}

void Explosion_Obj::ShowEx(SDL_Surface* des)
{
	if (frame > 3)
	{
		frame = 0;
	}
	CommonFunc::Apply_SurfaceClip(this->p_obj_, des, &clip[frame], rect_.x, rect_.y);	 
}