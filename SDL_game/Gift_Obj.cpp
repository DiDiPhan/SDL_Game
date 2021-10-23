#include "Gift_Obj.h"


Gift_Obj::Gift_Obj()
{
	rect_.x = 0;
	rect_.y = 0;
	x_val = 0;
	y_val = 0;
	is_move = false;
	gift_type = NONE;
}

Gift_Obj::~Gift_Obj()
{
	//notthing;
}

void Gift_Obj::CreatGift(int val)
{
	x_val = 0;
	y_val = 2;
	is_move = true;
	gift_type = val;
	if (val == HEART)
	{
		rect_.w = W_Heart;
		rect_.h = H_Heart;
		LoadImg(giftheart);
	}
	else
		if (val == AMO)
		{
			rect_.w = W_Amo;
			rect_.h = H_Amo;
			LoadImg(giftamo);
		}
}

void Gift_Obj::HandleInputAction(SDL_Event events, SDL_Rect rect)
{

}

void Gift_Obj::HandleMove(const int x_b, const int y_b)
{
	if (is_move)
	{
		rect_.y += y_val;
		rect_.x += x_val;
		if (rect_.y > SCREEN_H - 120 || rect_.x > SCREEN_W)
		{
			this->Settime(time(NULL));
			is_move = false;
		}
	}
}


int Gift_Obj::Gettype() const
{
	return gift_type;
}

void Gift_Obj::Settype(const int& type)
{
	gift_type = type;
}

bool Gift_Obj::Getismove() const
{
	return is_move;
}

void Gift_Obj::Setismove(bool is_move_)
{
	is_move = is_move_;
}

void Gift_Obj::SetWHGift(const int& W, const int& H)
{
	rect_.w = W;
	rect_.h = H;
}

void Gift_Obj::Setx_val(const int& val)
{
	x_val = val;
}

void Gift_Obj::Sety_val(const int& val)
{
	y_val = val;
}

void Gift_Obj::Settime(const time_t& val)
{
	time_ = val;
}

time_t Gift_Obj::Gettime() const
{
	return time_;
}

