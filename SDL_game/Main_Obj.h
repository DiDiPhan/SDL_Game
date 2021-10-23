#pragma once

#include "Common_Func.h"
#include "Base_Obj.h"
#include "Amo_Obj.h"

using namespace std;
/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/
#define W_Main 80
#define H_Main 46

const int H_Main_Move_val = H_Main / 20;
const int W_Main_Move_val = W_Main / 8;

class Main_Obj : public Base_Obj
{
public:
	Main_Obj();
	~Main_Obj();
	void HandleInputAction(SDL_Event, Mix_Chunk*, const bool&);
	void HandleMove();

	void MakeAmo(SDL_Surface*);

	void SetAmoList(vector <Amo_Obj*>);
	vector <Amo_Obj*> GetAmoList() const;
	void RevomeAmo(const int&);
	void RemoveAmoList();

	void setx_val(const int&);
	void sety_val(const int&);

	void setnumamo(const int&);
	int getnumamo() const;
private:
	int x_val;
	int y_val;
	int numamo;
	vector <Amo_Obj*> p_Amo_List;
};