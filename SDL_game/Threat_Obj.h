/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/
#pragma once

#include "Common_Func.h"
#include "Base_Obj.h"
#include "Amo_Obj.h"

using namespace std;

#define THREAT_W 80
#define THREAT_H 33

class Threat_Obj : public Base_Obj
{
public:
	enum Threat_Type
	{
		NONE = 0,
		AF1 = 1,
		AF2 = 3
	};
	Threat_Obj();
	~Threat_Obj();

	int GetType() const;
	void SetType(const int&);

	void HandleInputAction(SDL_Event);
	bool HandleMove(const int&, const int&);

	void Setx_val(const int&);
	void Sety_val(const int&);

	int Getx_val() const;
	int Gety_val() const;

	void SetLife(const int&);
	int GetLife() const;
	void SetAmoList(vector <Amo_Obj*>);
	vector <Amo_Obj*> GetAmoList() const;
	void InitAmo(Amo_Obj*);
	bool MakeAmo(SDL_Surface*, const int&, const int&);

	void Reset(const int&);
	void ResetAmo(Amo_Obj*);
	void RemoveAmo(const int&);

	bool ChangeType(const int&);

	void Setisgift(const bool&);
	bool Getisgift() const;
private:
	int x_val;
	int y_val;
	int life;
	int threat_type;
	bool isgift; // cho phep roi vat pham

	vector <Amo_Obj*> p_Amo_List;
};
