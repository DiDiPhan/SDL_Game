/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/
#pragma once

#include "Common_Func.h"
#include "Base_Obj.h"

#define W_Amolazer 10
#define H_Amolazer 10

class Amo_Obj : public Base_Obj
{
public:
	enum Amo_Type
	{
		NONE,
		LAZER,
		THREAT_LAZER1,
		THREAT_LAZER2
	};
	Amo_Obj();
	~Amo_Obj();
	void Creat(const int&);
	void HandleInputAction(SDL_Event, SDL_Rect);
	void HandleMove(const int, const int);

	int Gettype() const;
	void Settype(const int&);

	bool Getismove() const;
	void Setismove(bool is_move_);

	void SetWHAmo(const int&, const int&);

	void Setx_val(const int&);
	void Sety_val(const int&);
private:
	int x_val;
	int y_val;
	bool is_move;
	int amo_type;
};