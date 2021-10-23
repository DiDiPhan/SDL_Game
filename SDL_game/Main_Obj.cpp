#include "Main_Obj.h"


Main_Obj::Main_Obj()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = W_Main;
	rect_.h = H_Main;
	x_val = 0;
	y_val = 0; 
}

Main_Obj::~Main_Obj()
{
	//Nothing
}

void Main_Obj::HandleInputAction(SDL_Event events, Mix_Chunk* sound, const bool& playsound)
{
	if (events.type == SDL_KEYDOWN)
	{
		switch(events.key.keysym.sym)
		{
		case SDLK_SPACE:
		{
			if (playsound)
				Mix_PlayChannel(-1, sound, 0);
			Amo_Obj* p_amo = new Amo_Obj();
			p_amo->Creat(Amo_Obj::LAZER);
			if (numamo == 1)
			{
				p_amo->SetRect(this->rect_.x + 40, this->rect_.y);
				p_Amo_List.push_back(p_amo);
			}
			if (numamo == 2)
			{	
				p_amo->SetRect(this->rect_.x + 25, this->rect_.y);
				p_Amo_List.push_back(p_amo);
				Amo_Obj* p_amo2 = new Amo_Obj();
				p_amo2->Creat(Amo_Obj::LAZER);
				p_amo2->SetRect(this->rect_.x + 55, this->rect_.y);
				p_Amo_List.push_back(p_amo2);
			}
			if (numamo >= 3)
			{
				p_amo->SetRect(this->rect_.x + 15, this->rect_.y);
				p_Amo_List.push_back(p_amo);

				Amo_Obj* p_amo2 = new Amo_Obj();
				p_amo2->Creat(Amo_Obj::LAZER);
				p_amo2->SetRect(this->rect_.x + 40, this->rect_.y);
				p_Amo_List.push_back(p_amo2);

				Amo_Obj* p_amo3 = new Amo_Obj();
				p_amo3->Creat(Amo_Obj::LAZER);
				p_amo3->SetRect(this->rect_.x + 65, this->rect_.y);
				p_Amo_List.push_back(p_amo3);
			}
			break;
		}
		/*case SDLK_UP:
			y_val -= H_Main_Move_val;
			break;
		case SDLK_w:
			y_val -= H_Main_Move_val;
			break;
		case SDLK_DOWN:
			y_val += H_Main_Move_val;
			break;
		case SDLK_s:
			y_val += H_Main_Move_val;
			break;*/
		case SDLK_RIGHT:
			x_val += W_Main_Move_val;
			break;
		case SDLK_d:
			x_val += W_Main_Move_val;
			break;
		case SDLK_LEFT:
			x_val -= W_Main_Move_val;
			break;
		case SDLK_a:
			x_val -= W_Main_Move_val;
			break;

		default:
			break;
		}
	}
	else 
		if (events.type == SDL_KEYUP)
		{
			switch (events.key.keysym.sym)
			{
			/*case SDLK_UP:
				y_val += H_Main_Move_val;
				break;
			case SDLK_w:
				y_val += H_Main_Move_val;
				break;
			case SDLK_DOWN:
				y_val -= H_Main_Move_val;
				break;
			case SDLK_s:
				y_val -= H_Main_Move_val;
				break;*/
			case SDLK_RIGHT:
				x_val -= W_Main_Move_val;
				break;
			case SDLK_d:
				x_val -= W_Main_Move_val;
				break;
			case SDLK_LEFT:
				x_val += W_Main_Move_val;
				break;
			case SDLK_a:
				x_val += W_Main_Move_val;
				break;

			default:
				break;
			}
		}
}

void Main_Obj::HandleMove()
{
	if (rect_.x + x_val > 0 && rect_.x + x_val + W_Main < SCREEN_W)
		rect_.x += x_val;

	//if (rect_.y + y_val > 0 && rect_.y + y_val + H_Main < SCREEN_H)
	//	rect_.y += y_val;
}

void Main_Obj::MakeAmo(SDL_Surface* des)
{
	for (int i = 0; i < p_Amo_List.size(); i++)// print cac vien dan
	{
		Amo_Obj* p_amo = p_Amo_List[i];
		if (p_amo != NULL)
		{
			if (p_amo->Getismove())
			{
				p_amo->ShowCaret(des);
				p_amo->HandleMove(SCREEN_W, SCREEN_H);
			}
			else
			{
				p_Amo_List.erase(p_Amo_List.begin() + i);
				delete p_amo;
				p_amo = NULL;
				i--;

			} 
		}
	}
}


void Main_Obj::SetAmoList(vector <Amo_Obj*> Amo_list)
{
	p_Amo_List = Amo_list;
}

vector <Amo_Obj*>  Main_Obj::GetAmoList() const
{
	return p_Amo_List;
}

void Main_Obj::RevomeAmo(const int& idx)
{
	//for (int i = 0; i < p_Amo_List.size(); i++)
	//{
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
	//}
}

void Main_Obj::RemoveAmoList()
{
	while (p_Amo_List.size())
	{
		if (p_Amo_List[0] != NULL)
		{
			Amo_Obj* p_amo = p_Amo_List[0];
			p_Amo_List.erase(p_Amo_List.begin());
			if (p_amo == NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
	}
}

void Main_Obj::setx_val(const int& val)
{
	x_val = val;
}

void Main_Obj::sety_val(const int& val)
{
	y_val = val;
}

void Main_Obj::setnumamo(const int& val)
{
	numamo = val;
}

int Main_Obj::getnumamo() const
{
	return numamo;
}
