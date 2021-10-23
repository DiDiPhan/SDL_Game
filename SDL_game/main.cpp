/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/

#include "Common_Func.h"
#include "Main_Obj.h"
#include "Threat_Obj.h"
#include "Explosion_Obj.h"
#include "Num_Main_Life.h"
#include "Text_Obj.h"
#include "Gift_Obj.h"

#undef main

using namespace CommonFunc;

struct Explosion_data
{
    int x_pos;
    int y_pos;
    int frame;
    int type;
};

bool Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == GA_FAILED)
        return false;

    glo_screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, SCREEN_BPP, SDL_SWSURFACE); /// 1200 x 600 kich thuoc cua so; ma hoa pixel = 32bit
    if (glo_screen == NULL)
        return false;

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == GA_FAILED)
        return false;
    glo_sound_bullet = Mix_LoadWAV(maingun.c_str());
    glo_sound_exp[0] = Mix_LoadWAV(maindie.c_str());
    glo_sound_exp[1] = Mix_LoadWAV(threatdie1.c_str());
    glo_sound_exp[2] = Mix_LoadWAV(threatdie2.c_str());
    if (glo_sound_bullet == NULL || glo_sound_exp[0] == NULL || glo_sound_exp[1] == NULL || glo_sound_exp[2] == NULL)
        return false;
    if (TTF_Init() == GA_FAILED)
        return false;
    glo_font_text1 = TTF_OpenFont(fontgame1.c_str(), 20);
    glo_font_text2= TTF_OpenFont(fontgame2.c_str(), 20);
    if (glo_font_text1 == NULL)
        return false;
    if (glo_font_text2 == NULL)
        return false;
    return true;  
}

void UpdateFile()
{
    ofstream fo;
    fo.open("data.txt");
    fo << "vong$ " << vong;
    fo << "\nNum_Life$ " << Num_Life;
    fo << "\nNow_Score$ " << glo_score;
    fo << "\nH_score$ " << H_score;
    fo << "\nEndGame$ " << EndGame;
}

void reset_val(Main_Obj &hm_obj, Threat_Obj* &p_Threats, vector <Gift_Obj*> &gift, queue <Explosion_data>& Q)
{
    realtime_Num_Threats = 3;
    hm_obj.setx_val(0);
    hm_obj.SetRect(500, 660);
    hm_obj.RemoveAmoList();
    EndGame = 0;
    vong = 1;
    glo_score = 0;
    Num_Life = const_Life;
    for (int i = 0; i < glo_Num_Threats; i++)
    {
        Threat_Obj* p_Threat = (p_Threats + i);
        vector <Amo_Obj*> threat_amo_list = p_Threat->GetAmoList();
        if (p_Threat)
        {
            p_Threat->ChangeType(Threat_Obj::AF1);
            p_Threat->SetRect(SCREEN_W + i * 200, rand() % 540 + 1);
            p_Threat->Setx_val(-3);
            p_Threat->Sety_val(0);
            for (int j = 0; j < threat_amo_list.size(); j++)
                threat_amo_list[j]->SetRect(p_Threat->GetRect());
        }
    }
    while (gift.size())
        gift.erase(gift.begin());
    while (!Q.empty())
    {
        Q.pop();
    }

}

bool printMenu(Main_Obj& hm_obj, Threat_Obj* &p_Threats, vector <Gift_Obj*> &gift, queue <Explosion_data>& Q)//quan li menu
{
    int chkmenu;
    while(true)
    {
        chkmenu = CommonFunc::Show_Menu(glo_screen, glo_font_text1);
        if (chkmenu == 4)//chon exit
        {
            return 0;
        }
        if (chkmenu == 0) //start
        {
            reset_val(hm_obj, p_Threats, gift, Q);
            return 1;
        }
        if (chkmenu == 1)//continue
        {
            //nothing
            if (EndGame == 1)
            reset_val(hm_obj, p_Threats, gift, Q);
            return 1;
        }

        if (chkmenu == 2)//setting
        {
            CommonFunc::Show_Setting(glo_screen, glo_font_text1, playsound);
        }
        if (chkmenu == 3)//help
        {
            CommonFunc::Show_Help(glo_screen, glo_font_text1);
        }
    }
}

int main(int arc, char* argv[])
{
    ifstream fi;
    fi.open("data.txt");

    string S;
    int val;
    while (fi >> S)
    {
        if (S == "vong$")
        {
            fi >> val;
            vong = val;
        }
        else
            if (S == "Num_Life$")
            {
                fi >> val;
                Num_Life = val;
            }
            else
                if (S == "Now_Score$")
                {
                    fi >> val; 
                    glo_score = val;
                }
                else
                    if (S == "H_score$")
                    {
                        fi >> val;
                        H_score = val;
                    }
                    else
                        if (S == "EndGame$")
                        {
                            fi >> val;
                            if (val == 1)
                            {
                                EndGame = 0;
                                vong = 1;
                                glo_score = 0;
                                Num_Life = const_Life;
                            }

                        }

    }
    
    
    srand(time(NULL));
    if (!Init())
        return 0;

    int bckgrd_x = 0;
    glo_background = Load_image(bkg);
    if (glo_background == NULL)
        return 0;

    //tao hien thi mang
    Num_Main_Life MainLife;
    MainLife.Init();
    MainLife.SetClip();

    //tao hien thi diem va diem cao nhat
    Text_Obj score_game;
    score_game.SetColor(Text_Obj::WHITE_TEXT);
    score_game.SetRect(350, 750);

    Text_Obj Hscore_game;
    Hscore_game.SetColor(Text_Obj::WHITE_TEXT);
    Hscore_game.SetRect(600, 750);
      
    //Init main
    Main_Obj human_obj;
    bool chkhm = human_obj.LoadImg(hmmain);
    human_obj.setnumamo(1);
    if (!chkhm)
        return 0;
    human_obj.SetRect(500, 660);

    //Init Explosion
    Explosion_Obj exp_threat;
    bool chkexp = exp_threat.LoadImg(expthreat);
    exp_threat.SetClip();
    if (!chkexp)
        return 0;

    Explosion_Obj exp_main;
    chkexp = exp_main.LoadImg(expmain);
    exp_main.SetClip();
    if (!chkexp)
        return 0;


    //Init threat
    Threat_Obj* p_Threats = new Threat_Obj[glo_Num_Threats];

    for (int i = 0; i < glo_Num_Threats; i++)
    {
        Threat_Obj* p_Threat = (p_Threats + i);
        if (p_Threat)
        {
            bool chkthreat = p_Threat->LoadImg(threat1);
            p_Threat->SetType(Threat_Obj::AF1);
            p_Threat->SetLife(Threat_Obj::AF1);
            p_Threat->Setisgift(false);
            if (!chkthreat)
                return 0;
            p_Threat->SetRect(SCREEN_W + i * 200, rand() % 540 + 1);
            p_Threat->Setx_val(-3);

            Amo_Obj* p_amo = new Amo_Obj();
            bool chkamo = p_amo->LoadImg(ThreatAmoLazer1);
            if (!chkamo)
                return 0;
            p_Threat->InitAmo(p_amo);

        }
    }

    queue <Explosion_data> Queue_frame_explosion; //Luu frame cac vu no

    //Init Gift
    vector <Gift_Obj*> Gift;
    time_t time_of_amo = NULL; // bien luu thoi gian tang them dan

    bool quit = !printMenu(human_obj, p_Threats, Gift, Queue_frame_explosion);
    if (quit)
        return 0;

    //gan mang hien tai cho main
    MainLife.SetNumber(Num_Life);

    //Init button in game
    const int num_button = 2;
    SDL_Rect pos_arr[num_button];
    pos_arr[0].x = 1020;
    pos_arr[0].y = 710;

    pos_arr[1].x = 1020;
    pos_arr[1].y = 750;

    Text_Obj text_in_game[num_button];
    text_in_game[0].SetText("Setting");
    text_in_game[0].SetColor(Text_Obj::WHITE_TEXT);
    text_in_game[0].SetRect(pos_arr[0].x, pos_arr[0].y);


    text_in_game[1].SetText("Quit");
    text_in_game[1].SetColor(Text_Obj::WHITE_TEXT);
    text_in_game[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    bool slctbuttoningame[num_button] = { 0, 0 };
    int y_mouse = 0, x_mouse = 0;



    //Kiem tra thoat chuong trinh
    while (!quit)
    {
        while (SDL_PollEvent(&glo_event))//nhan event di vao
        {
            switch (glo_event.type)
            {
            case SDL_QUIT:
            {
                //todo
                UpdateFile();
                quit = true;
                break;
            }
            case SDL_MOUSEMOTION:
            {
                x_mouse = glo_event.motion.x;
                y_mouse = glo_event.motion.y;
                for (int i = 0; i < num_button; i++)
                {
                    if (CheckFocusWithRect(x_mouse, y_mouse, text_in_game[i].GetRect()))
                    {
                        if (slctbuttoningame[i] == 0)
                        {
                            slctbuttoningame[i] = 1;
                            text_in_game[i].SetColor(Text_Obj::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (slctbuttoningame[i] == 1)
                        {
                            slctbuttoningame[i] = 0;
                            text_in_game[i].SetColor(Text_Obj::WHITE_TEXT);
                        }
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                x_mouse = glo_event.button.x;
                y_mouse = glo_event.button.y;
                if (CommonFunc::CheckFocusWithRect(x_mouse, y_mouse, text_in_game[0].GetRect()))
                {
                    CommonFunc::Show_Setting(glo_screen, glo_font_text1, playsound);
                    slctbuttoningame[0] = 0;
                    text_in_game[0].SetColor(Text_Obj::WHITE_TEXT);
                }
                if (CommonFunc::CheckFocusWithRect(x_mouse, y_mouse, text_in_game[1].GetRect()))
                {
                    quit = !printMenu(human_obj, p_Threats, Gift, Queue_frame_explosion);
                    MainLife.SetNumber(Num_Life);
                    slctbuttoningame[1] = 0;
                    text_in_game[1].SetColor(Text_Obj::WHITE_TEXT);
                }
                break;
            }
            case SDL_KEYDOWN:
                if (glo_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    quit = true;
                }
            default:
                break;
            }
            human_obj.HandleInputAction(glo_event, glo_sound_bullet, playsound);//xu li di chuyen nhan vat main
        }
        //them beckground
        bckgrd_x -= 1;
        Apply_Surface(glo_background, glo_screen, bckgrd_x, 0);
        Apply_Surface(glo_background, glo_screen, bckgrd_x + SCREEN_W, 0);
        if (bckgrd_x <= -SCREEN_W)
            bckgrd_x = 0;    
        text_in_game[0].SetRect(text_in_game[0].CreatGameText(glo_font_text2, glo_screen));
        text_in_game[1].SetRect(text_in_game[1].CreatGameText(glo_font_text2, glo_screen));

        //them mang cho main
        MainLife.ShowLife(glo_screen);


        //them nhan vat chinh
        human_obj.HandleMove();
        human_obj.ShowCaret(glo_screen);
        human_obj.MakeAmo(glo_screen);

        //hien thi gift roi 
        if (Gift.size() > 0)
            for (int i = 0; i < Gift.size(); i++)
            {
                Gift[i]->HandleMove(SCREEN_W, SCREEN_H);
                Gift[i]->ShowCaret(glo_screen);
                if (CheckCollision(human_obj.GetRect(), Gift[i]->GetRect()))
                {
                    if (Gift[i]->Gettype() == Gift_Obj::HEART)
                    {
                        
                        int val = MainLife.GetNumLife();
                        if (val < const_Life)
                            val++;
                        MainLife.SetNumber(val);
                    }
                    else
                        if (Gift[i]->Gettype() == Gift_Obj::AMO)
                        {
                            human_obj.setnumamo(human_obj.getnumamo() + 1);
                            time_of_amo = time(NULL);
                        }

                    Gift.erase(Gift.begin() + i);
                    i--;
                }
                else
                {
                    if (!Gift[i]->Getismove())
                    {
                        if (difftime(time(NULL), Gift[i]->Gettime()) >= Gift[i]->Gettype())
                        {
                            Gift.erase(Gift.begin() + i);
                            i--;
                        }
                    }
                }
            }
        if (human_obj.getnumamo() > 1)
        {
            if (difftime(time(NULL), time_of_amo) >= 10)
            {
                human_obj.setnumamo(1);
            }
        }


        //them threats neu diem cao
        if (glo_score / 50 > realtime_Num_Threats && realtime_Num_Threats < glo_Num_Threats)
        {
            realtime_Num_Threats++;
        }

        //them threats
        for (int i = 0; i < realtime_Num_Threats; i++)
        {
            Threat_Obj* p_Threat = p_Threats + i;
            if (p_Threat)
            {
                p_Threat->ShowCaret(glo_screen);
                if (p_Threat->HandleMove(SCREEN_W, SCREEN_H))
                {
                    p_Threat->SetLife(p_Threat->GetType());
                    //todo
                }
                if (!p_Threat->MakeAmo(glo_screen, SCREEN_W, SCREEN_H))
                    return 0;
                //ko kiem tra va cham giua main va threat

                //kiem tra va cham giua dan cua main va threat
                vector <Amo_Obj*> amo_list = human_obj.GetAmoList();
                for (int j = 0; j < amo_list.size(); j++)
                {
                    Amo_Obj* p_amo = amo_list[j];
                    if (p_amo != NULL)
                    {
                        bool ret_col = CheckCollision(p_amo->GetRect(), p_Threat->GetRect());
                        if (ret_col)
                        {
                            int threatlife = p_Threat->GetLife();
                            if (threatlife > 1)
                            {
                                p_Threat->SetLife(threatlife - 1);
                            }
                            else
                            {
                                if (playsound)
                                {
                                    if (p_Threat->GetType() == Threat_Obj::AF1)
                                    {
                                        Mix_PlayChannel(-1, glo_sound_exp[1], 0);
                                    }
                                    else
                                    {
                                        Mix_PlayChannel(-1, glo_sound_exp[2], 0);
                                    }
                                }

                                //xem set su kien rot vat pham
                                if (p_Threat->Getisgift())
                                {
                                    int rand_val = rand() % 5 + 1; //hihiihihi
                                    if (rand_val == 1)
                                    {
                                        Gift_Obj* p_gift = new Gift_Obj();
                                        p_gift->CreatGift(Gift_Obj::HEART);
                                        p_gift->SetRect(p_Threat->GetRect().x + p_Threat->GetRect().w * 0.5, p_Threat->GetRect().y + p_Threat->GetRect().h * 0.5);
                                        Gift.push_back(p_gift);
                                    }
                                    if (rand_val == 2)
                                    {
                                        Gift_Obj* p_gift = new Gift_Obj();
                                        p_gift->CreatGift(Gift_Obj::AMO);
                                        p_gift->SetRect(p_Threat->GetRect().x + p_Threat->GetRect().w * 0.5, p_Threat->GetRect().y + p_Threat->GetRect().h * 0.5); 
                                        Gift.push_back(p_gift);
                                    }
                                }

                                //tao hieu ung vu no
                                for (int k = 0; k < 4; k++)
                                {
                                    //tim tam cho vu no
                                    int x_pos = p_Threat->GetRect().x + p_Threat->GetRect().w * 0.5 - EXP_W * 0.5;
                                    int y_pos = p_Threat->GetRect().y + p_Threat->GetRect().h * 0.5 - EXP_H * 0.5;
                                    for (int i = 1; i <= 3; i++)
                                    {
                                        Queue_frame_explosion.push({ x_pos, y_pos, k, 0 });
                                    }
                                }
                
                                if (p_Threat->GetType() == Threat_Obj::AF1)
                                {
                                    glo_score += 5;
                                    int rand_val;
                                    if (realtime_Num_Threats < 5)
                                        rand_val = rand() % 10;
                                    else
                                        if (realtime_Num_Threats < 9)
                                            rand_val = rand() % 5;
                                        else
                                            rand_val = rand() % 2;
                                    if (rand_val == 1)
                                    {
                                        p_Threat->ChangeType(Threat_Obj::AF2);
                                    }
                                }
                                else
                                    if (p_Threat->GetType() == Threat_Obj::AF2)
                                    {
                                        glo_score += 10;
                                        if (glo_score < 650)
                                        {
                                            p_Threat->ChangeType(Threat_Obj::AF1);
                                        }
                                        else
                                        {
                                            if (rand() % 6 == 1)
                                                p_Threat->Setisgift(true);
                                            else
                                                p_Threat->Setisgift(false);
                                        }
                                    }
                                p_Threat->Reset(SCREEN_W + i * 200);
                            }
                            human_obj.RevomeAmo(j);
                            break;
                        }
                    }

                }
                
                //kiem tra va cham giua dan theart va main
                vector <Amo_Obj*> threat_amo_list = p_Threat->GetAmoList();
                if (!threat_amo_list.size())
                {
                    Amo_Obj* p_amo = new Amo_Obj();
                    bool chkamo = p_amo->LoadImg(ThreatAmoLazer1);
                    if (!chkamo)
                        return 0;
                    p_Threat->InitAmo(p_amo);
                }
                for (int j = 0; j < threat_amo_list.size(); j++)
                {
                    //cout << j << "\n";
                    Amo_Obj* p_amo = threat_amo_list[j];
                    if (p_amo != NULL)
                    {
                        bool ret_col = CheckCollision(p_amo->GetRect(), human_obj.GetRect());
                        if (ret_col)
                        {
                            p_Threat->RemoveAmo(j);
                            //UpdateFile();
                            if (playsound)
                                Mix_PlayChannel(-1, glo_sound_exp[0], 0);
                            for (int k = 0; k < 4; k++)
                            {
                                //tim tam cho vu no
                                int x_pos = human_obj.GetRect().x + human_obj.GetRect().w * 0.5 - EXP_W * 0.5;
                                int y_pos = human_obj.GetRect().y + human_obj.GetRect().h * 0.5 - EXP_H * 0.5;
                                for (int i = 1; i <= 7; i++)
                                {
                                    Queue_frame_explosion.push({ x_pos, y_pos, k, 1 });
                                }
                            }
                            human_obj.setnumamo(1);
                            if (MainLife.GetNumLife() > 1)
                            {
                                human_obj.SetRect(1, 660);
                                MainLife.Decrease();
                                MainLife.ShowLife(glo_screen);
                                Num_Life = MainLife.GetNumLife();
                                if (SDL_Flip(glo_screen) == -1)
                                {
                                    delete[]p_Threats;
                                    Clean_Up();
                                    SDL_Quit();
                                    return 0;
                                }
                                
                            }
                            else
                            {
                                if (CommonFunc::Show_End(glo_screen, glo_font_text1, H_score, glo_score))
                                {
                                    EndGame = 1;
                                    UpdateFile();
                                    quit = !printMenu(human_obj, p_Threats, Gift, Queue_frame_explosion);
                                    MainLife.SetNumber(const_Life);
                                }
                            }
                        }
                    }
                }
            }
        }
        if (!Queue_frame_explosion.empty())
        {
            Explosion_data tmp = Queue_frame_explosion.front();
            Queue_frame_explosion.pop();
            if (!tmp.type)
            {
                exp_threat.SetFrame(tmp.frame);
                exp_threat.SetRect(tmp.x_pos, tmp.y_pos);
                exp_threat.ShowEx(glo_screen);
                //SDL_Delay(10);
            }
            else
            {
                exp_main.SetFrame(tmp.frame);
                exp_main.SetRect(tmp.x_pos, tmp.y_pos);
                exp_main.ShowEx(glo_screen);
               // SDL_Delay(50);
            }
            if (SDL_Flip(glo_screen) == -1)// khong tim thay viec update anh
                return 0;
        }

        //hien thi quit
        H_score = max(H_score, glo_score); 
        //hien thi diem so
        string str_score = "HIGH SCORE: " + to_string(H_score);
        Hscore_game.SetText(str_score);
        Hscore_game.CreatGameText(glo_font_text2, glo_screen);
        str_score = "SCORE: " + to_string(glo_score);
        score_game.SetText(str_score);
        score_game.CreatGameText(glo_font_text2, glo_screen);
        
        if (SDL_Flip(glo_screen) == -1)// khong tim thay viec update anh
            return 0;
    }
    delete[] p_Threats;
    Clean_Up();
    SDL_Quit();
    return 1;
}
