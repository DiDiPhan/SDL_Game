#include "Num_Main_Life.h"

Num_Main_Life::Num_Main_Life()
{

}

Num_Main_Life::~Num_Main_Life()
{

}

void Num_Main_Life::SetClip()
{
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = HEART_W;
	clip[0].h = HEART_H;

	clip[1].x = HEART_W;
	clip[1].y = 0;
	clip[1].w = HEART_W;
	clip[1].h = HEART_H;
}


void Num_Main_Life::SetNumber(const int& val)
{
	num_life = val;
}

void Num_Main_Life::AddPos(const int& xpos)
{
	pos_list.push_back(xpos);
}

void Num_Main_Life::ShowLife(SDL_Surface* des)
{
	this->SetFrame(0);
	this->rect_.y = 740;
	for (int i = 0; i < num_life; i++)
	{

		rect_.x = pos_list[i];
		this->ShowHeart(des);
	}
	this->SetFrame(1);
	for (int i = num_life; i < pos_list.size(); i++)
	{

		rect_.x = pos_list[i];
		this->ShowHeart(des);
	}

}

void Num_Main_Life::Init()
{
	LoadImg(heart);
	//SetNumber(Num_Life);
	//cerr << Num_Life;
	if (pos_list.size() > 0)
	{
		pos_list.clear();
	}

	AddPos(20);
	AddPos(60);
	AddPos(100);
	AddPos(140);
	AddPos(180);
}

void Num_Main_Life::SetFrame(const int& fr)
{
	frame = fr;
}

void Num_Main_Life::ShowHeart(SDL_Surface* des)
{

	CommonFunc::Apply_SurfaceClip(this->p_obj_, des, &clip[frame], rect_.x, rect_.y + 10);
}

void Num_Main_Life::Decrease()
{
	num_life--;
}

int Num_Main_Life::GetNumLife()
{
	return num_life;
}
 