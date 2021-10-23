/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/
#pragma once

#include "Common_Func.h"
#include "Base_Obj.h"

#define W_Heart 30
#define H_Heart 30
#define W_Amo 30
#define H_Amo 30

class Gift_Obj : public Base_Obj
{
public:
	enum Gift_Type // gia tri tuong duong thoi gian ton tai
	{
		NONE,
		HEART = 3,
		AMO = 4
	};
	Gift_Obj();
	~Gift_Obj();
	void CreatGift(int Gifttype);
	void HandleInputAction(SDL_Event, SDL_Rect);
	void HandleMove(const int, const int);

	int Gettype() const;
	void Settype(const int&);

	bool Getismove() const;
	void Setismove(bool is_move_);

	void SetWHGift(const int&, const int&);

	void Setx_val(const int&);
	void Sety_val(const int&);

	void Settime(const time_t&);
	time_t Gettime() const;
private:
	int x_val;
	int y_val;
	bool is_move;
	int gift_type;
	time_t time_;
};