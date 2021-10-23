#include "Threat_Obj.h"

Threat_Obj::Threat_Obj()
{
	x_val = 0;
	y_val = 0;
	threat_type = NONE;
	rect_.x = SCREEN_W;
	rect_.y = SCREEN_H * 0.7;
	rect_.w = THREAT_W;
	rect_.h = THREAT_H;
}

Threat_Obj::~Threat_Obj()
{
	if (p_Amo_List.size())
	{
		for (int i = 0; i < p_Amo_List.size(); i++)
		{
			Amo_Obj* p_amo = p_Amo_List[i];
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_Amo_List.clear();
	}
}

int Threat_Obj::GetType() const
{
	return threat_type;
}

void Threat_Obj::SetType(const int& type)
{
	threat_type = type;
}

void Threat_Obj::Setx_val(const int& val)
{
	x_val = val;
}

void Threat_Obj::Sety_val(const int& val)
{
	y_val = val;
}

int Threat_Obj::Getx_val() const
{
	return x_val;
}

int Threat_Obj::Gety_val() const
{
	return y_val;
}

int Threat_Obj::GetLife() const
{
	return life;
}

void Threat_Obj::SetLife(const int& val)
{
	life = val;
}

bool Threat_Obj::HandleMove(const int& x_b, const int& y_b)
{
	rect_.x += x_val;
	if (rect_.x <= -THREAT_W)
	{	
		rect_.x = x_b; 
		if (this->GetType() == Threat_Obj::AF1)
		{
			rect_.y = rand() % 540 + 1;
		}
		else
			if (this->GetType() == Threat_Obj::AF2)
			{
				rect_.y = rand() % 320 + 1;
			}
		
		return 1;
	}
	return 0;

}

void Threat_Obj::HandleInputAction(SDL_Event events)
{

}

void Threat_Obj::SetAmoList(vector <Amo_Obj*> Amo_list)
{
	p_Amo_List = Amo_list;

}

vector <Amo_Obj*> Threat_Obj::GetAmoList() const
{
	return p_Amo_List;
}

void Threat_Obj::InitAmo(Amo_Obj* p_amo)
{
	if (p_amo)
	{
		p_amo->Setismove(true);
		p_amo->SetWHAmo(W_Amolazer, H_Amolazer);
		p_amo->Settype(Amo_Obj::THREAT_LAZER1);
		p_amo->SetRect(rect_.x, rect_.y + 31);
		p_amo->Sety_val(3);
		p_amo->Setx_val(-1);
		p_Amo_List.push_back(p_amo);
	}		
}

bool Threat_Obj::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int i = 0; i < p_Amo_List.size(); i++)
	{
		Amo_Obj* p_amo = p_Amo_List[i];
		if (p_amo)
		{
			if (p_amo->Getismove())
			{
				p_amo->ShowCaret(des);
				p_amo->HandleMove(SCREEN_W, SCREEN_H);
			}
			else
			{
				p_amo->Setismove(true);
				p_amo->SetRect(rect_.x, rect_.y + 31);
				if (this->GetType() != p_amo->Gettype())
				{
					if (this->GetType() == Threat_Obj::AF1)
					{
						if (!p_Amo_List[i]->LoadImg(ThreatAmoLazer1))
							return 0;
						p_amo->Settype(Amo_Obj::THREAT_LAZER1);
						p_amo->Sety_val(3);
						p_amo->Setx_val(-1);
					}
					else
					{
						if (!p_amo->LoadImg(ThreatAmoLazer2))
							return 0;
						p_amo->Settype(Amo_Obj::THREAT_LAZER2);
						p_amo->Sety_val(4);
						p_amo->Setx_val(-1);
					}
				}

			}
		}
	}
	return 1;
}

void Threat_Obj::Reset(const int& x_b)
{
	this->SetLife(this->GetType());
	rect_.x = x_b;
	if (this->GetType() == Threat_Obj::AF1)
	{
		rect_.y = rand() % 540 + 1;
	}
	else
		if (this->GetType() == Threat_Obj::AF2)
		{
			rect_.y = rand() % 320 + 1;
		}
}

void Threat_Obj::ResetAmo(Amo_Obj* p_amo)
{
	p_amo->SetRect(rect_.x, rect_.y + 31);
}

void Threat_Obj::RemoveAmo(const int& idx)
{
	if (idx < p_Amo_List.size())
	{
		Amo_Obj* p_amo = p_Amo_List[idx];
		p_Amo_List.erase(p_Amo_List.begin() + idx);
		if (p_amo == NULL)
		{
			delete p_amo;
			p_amo = NULL;
		}
	}
}

bool Threat_Obj::ChangeType(const int& val)
{
	bool chkthreat;
	if (val == AF1)
	{
		chkthreat = this->LoadImg(threat1);
		if (!chkthreat)
			return 0;
		this->SetType(Threat_Obj::AF1);
		this->SetLife(Threat_Obj::AF1);
		this->Setx_val(-(rand() % 2 + 2));
		this->Setisgift(false);
	}
	else
		if (val == AF2)
		{
			chkthreat = this->LoadImg(threat2);
			if (!chkthreat)
				return 0;
			this->SetType(Threat_Obj::AF2);
			this->SetLife(Threat_Obj::AF2);
			this->Setx_val(-2);
			this->Setisgift(true);
		}
	return 1;
}

bool Threat_Obj::Getisgift() const
{
	return isgift;
}

void Threat_Obj::Setisgift(const bool& val)
{
	isgift = val;
}
