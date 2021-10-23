#include "Amo_Obj.h"


Amo_Obj::Amo_Obj()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val = 0;
	y_val = 0;
	is_move = false;
	amo_type = NONE;
}

Amo_Obj::~Amo_Obj()
{
	//notthing;
}

void Amo_Obj::Creat(const int& val)
{
	Settype(val);;
	SetWHAmo(W_Amolazer, H_Amolazer);
	LoadImg(Amolazer);

	Setismove(true);
	Sety_val(-7);
	Setx_val(-1);
}

void Amo_Obj::HandleInputAction(SDL_Event events, SDL_Rect rect)
{

}

void Amo_Obj::HandleMove(const int x_b, const int y_b)
{
	rect_.y += y_val;
	rect_.x += x_val;
	if (rect_.y < 0 || rect_.x < 0 || rect_.y > SCREEN_H - 90 || rect_.x > SCREEN_W)
	{
		is_move = false;
	}
}


int Amo_Obj::Gettype() const
{
	return amo_type;
}

void Amo_Obj::Settype(const int& type)
{
	amo_type = type;
}

bool Amo_Obj::Getismove() const
{
	return is_move;
}

void Amo_Obj::Setismove(bool is_move_)
{
	is_move = is_move_;
}

void Amo_Obj::SetWHAmo(const int& W, const int& H)
{
	rect_.w = W;
	rect_.h = H;
}

void Amo_Obj::Setx_val(const int& val)
{
	x_val = val;
}

void Amo_Obj::Sety_val(const int& val)
{
	y_val = val;
}

