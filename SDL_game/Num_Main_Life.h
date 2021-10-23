/*/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/
#pragma once

#include "Common_Func.h"
#include "Base_Obj.h"

const int HEART_W = 30;
const int HEART_H = 30;

class Num_Main_Life : public Base_Obj
{
public:
	Num_Main_Life();
	~Num_Main_Life();

	void SetNumber(const int&);
	void SetClip();
	void AddPos(const int&);
	void ShowLife(SDL_Surface*);
	void Init();
	void SetFrame(const int&);
	void ShowHeart(SDL_Surface*);
	void Decrease();
	int GetNumLife(); 
private:
	int num_life;
	int frame;
	vector <int> pos_list;
	SDL_Rect clip[2];

};