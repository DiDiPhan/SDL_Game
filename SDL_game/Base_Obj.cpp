#include "Base_Obj.h"


Base_Obj::Base_Obj()
{
	rect_.x = 0;
	rect_.y = 0;
	p_obj_ = NULL;
}

Base_Obj::~Base_Obj()
{
	if (p_obj_ != NULL)//co the da delete trong Cleanup
		SDL_FreeSurface(p_obj_);
}

SDL_Rect Base_Obj::GetRect() const
{
	return rect_;
}

SDL_Surface* Base_Obj::Get_obj()
{
	return p_obj_;
}

SDL_Rect Base_Obj::ShowCaret(SDL_Surface* des)
{
	if (p_obj_ != NULL)
	{
		return CommonFunc::Apply_Surface(p_obj_, des, rect_.x, rect_.y);
	}
}

bool Base_Obj::LoadImg(const string file_name)
{
	p_obj_ = CommonFunc::Load_image(file_name);
	if (p_obj_ == NULL)
		return false;
	return true;
}

void Base_Obj::SetRect(const int& x, const int& y)
{
	rect_.x = x;
	rect_.y = y;
}

void Base_Obj::SetRect(const SDL_Rect& rect)
{
	rect_ = rect;
}


