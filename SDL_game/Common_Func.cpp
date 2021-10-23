#include "Common_Func.h"
#include "Text_Obj.h"

//using namespace CommonFunc;

SDL_Surface* CommonFunc::Load_image(string filename)//load anh
{
    SDL_Surface* load_img_ = NULL;
    SDL_Surface* optimize_img = NULL;
    load_img_ = IMG_Load(filename.c_str());
    if (load_img_ != NULL)
    {
        optimize_img = SDL_DisplayFormat(load_img_);
        SDL_FreeSurface(load_img_);
        if (optimize_img != NULL)
        {
            UINT32 color_key = SDL_MapRGB(optimize_img->format, 0, 0xFF, 0xFF);//loai bo ma mau nay(lam trong suot)
            SDL_SetColorKey(optimize_img, SDL_SRCCOLORKEY, color_key);
        }
    }
    return optimize_img;
}

SDL_Rect CommonFunc::Apply_Surface(SDL_Surface* src, SDL_Surface* des, int x, int y)//add anh vao screen; x, y: toa do anh se xuat hien
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, NULL, des, &offset);
    return offset;
}

void CommonFunc::Apply_SurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, clip, des, &offset);
}


bool CommonFunc::CheckCollision(const SDL_Rect& obj1, const SDL_Rect& obj2)
{
    int left_a = obj1.x;
    int right_a = obj1.x + obj1.w;
    int top_a = obj1.y;
    int bottom_a = obj1.y + obj1.h;

    int left_b = obj2.x;
    int right_b = obj2.x + obj2.w;
    int top_b = obj2.y;
    int bottom_b = obj2.y + obj2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;       
}

void CommonFunc::Clean_Up()//giai phong bien toan cuc
{
    SDL_FreeSurface(glo_background);
    SDL_FreeSurface(glo_screen);
}

int CommonFunc::Show_Menu(SDL_Surface* des, TTF_Font* font)
{  
    glo_bkg_menu = Load_image(bkgMenu);
    if (glo_bkg_menu == NULL)
        return 1;

    const int num_item_menu = 5;
    SDL_Rect pos_arr[num_item_menu];
    pos_arr[0].x = 550;
    pos_arr[0].y = 500;

    pos_arr[1].x = 550;
    pos_arr[1].y = 550;

    pos_arr[2].x = 550;
    pos_arr[2].y = 600;

    pos_arr[3].x = 550;
    pos_arr[3].y = 650;

    pos_arr[4].x = 550;
    pos_arr[4].y = 700;

    Text_Obj text_menu[num_item_menu];
    text_menu[0].SetText("Play game");
    text_menu[0].SetColor(Text_Obj::WHITE_TEXT);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("Continue");
    text_menu[1].SetColor(Text_Obj::WHITE_TEXT);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    text_menu[2].SetText("Setting");
    text_menu[2].SetColor(Text_Obj::WHITE_TEXT);
    text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

    text_menu[3].SetText("Help");
    text_menu[3].SetColor(Text_Obj::WHITE_TEXT);
    text_menu[3].SetRect(pos_arr[3].x, pos_arr[3].y);

    text_menu[4].SetText("Exit");    
    text_menu[4].SetColor(Text_Obj::WHITE_TEXT);
    text_menu[4].SetRect(pos_arr[4].x, pos_arr[4].y);

    bool selected[num_item_menu] = { 0, 0, 0, 0, 0 };
    SDL_Event m_event;
    int y_mouse = 0, x_mouse = 0;
    while (true)
    {
        CommonFunc::Apply_Surface(glo_bkg_menu, des, 0, 0);
        for (int i = 0; i < num_item_menu; i++)
        {
            text_menu[i].SetRect(text_menu[i].CreatGameText(font, des));
        }

        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
            {
                SDL_FreeSurface(glo_bkg_menu);
                return 4;
            }
            case SDL_MOUSEMOTION:
            {
                x_mouse = m_event.motion.x;
                y_mouse = m_event.motion.y;

                for (int i = 0; i < num_item_menu; i++)
                {
                    if (CheckFocusWithRect(x_mouse, y_mouse, text_menu[i].GetRect()))
                    {
                        if (selected[i] == 0)
                        {
                            selected[i] = 1;
                            text_menu[i].SetColor(Text_Obj::RED_TEXT); 
                        }
                    }
                    else
                    {
                        if (selected[i] == 1)
                        {
                            selected[i] = 0;
                            text_menu[i].SetColor(Text_Obj::WHITE_TEXT);
                        }
                    }

                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                x_mouse = m_event.button.x;
                y_mouse = m_event.button.y;  
                for (int i = 0; i < num_item_menu; i++)
                {
                    if (CheckFocusWithRect(x_mouse, y_mouse, text_menu[i].GetRect()))
                    {
                        SDL_FreeSurface(glo_bkg_menu);
                        return i;
                    }
                }
                break;
            }
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_FreeSurface(glo_bkg_menu);
                    return 4;
                } 
            default:
                break;
            }
        }
        SDL_Flip(des);
        
    }
    SDL_FreeSurface(glo_bkg_menu);
    return 4;
}

void CommonFunc::Show_Setting(SDL_Surface* des, TTF_Font* font, bool &playsound)
{
    glo_bkg_setting = Load_image(bkgsetting);
    if (glo_bkg_setting == NULL)
        return;

    const int num_item_setting = 2;
    int playsound_ = playsound;
    SDL_Rect pos_arr[num_item_setting];
    pos_arr[0].x = 550;
    pos_arr[0].y = 500;

    pos_arr[1].x = 550;
    pos_arr[1].y = 550;

    Text_Obj text_setting[num_item_setting];
    if (playsound)
        text_setting[0].SetText("Sound(On)");
    else
        text_setting[0].SetText("Sound(Off)");
    text_setting[0].SetColor(Text_Obj::WHITE_TEXT);
    text_setting[0].SetRect(pos_arr[0].x, pos_arr[0].y);


    text_setting[1].SetText("Quit");
    text_setting[1].SetColor(Text_Obj::WHITE_TEXT);
    text_setting[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    bool selected[num_item_setting] = { 0, 0 };
    SDL_Event m_event;
    int y_mouse = 0, x_mouse = 0;
    while (true)
    {
        CommonFunc::Apply_Surface(glo_bkg_setting, des, 0, 0);
        for (int i = 0; i < num_item_setting; i++)
        {
            text_setting[i].SetRect(text_setting[i].CreatGameText(font, des));
        }

        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
            {
                SDL_FreeSurface(glo_bkg_setting);
                return;
            }
            case SDL_MOUSEMOTION:
            {
                x_mouse = m_event.motion.x;
                y_mouse = m_event.motion.y;

                for (int i = 0; i < num_item_setting; i++)
                {
                    if (CheckFocusWithRect(x_mouse, y_mouse, text_setting[i].GetRect()))
                    {
                        if (selected[i] == 0)
                        {
                            selected[i] = 1;
                            text_setting[i].SetColor(Text_Obj::RED_TEXT);
                        }
                    }
                    else
                    {
                        if (selected[i] == 1)
                        {
                            selected[i] = 0;
                            text_setting[i].SetColor(Text_Obj::WHITE_TEXT);
                        }
                    }

                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                x_mouse = m_event.button.x;
                y_mouse = m_event.button.y;
                if (CheckFocusWithRect(x_mouse, y_mouse, text_setting[0].GetRect()))
                {
                    if (playsound_)
                    {
                        playsound_ = 0;
                        text_setting[0].SetText("Sound(Off)");
                    }
                    else
                    {
                        playsound_ = 1;
                        text_setting[0].SetText("Sound(On)");
                    }
                    
                }
                if (CheckFocusWithRect(x_mouse, y_mouse, text_setting[1].GetRect()))
                {
                    SDL_FreeSurface(glo_bkg_setting);
                    return;
                }
                break;
            }
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_FreeSurface(glo_bkg_setting);
                    return;
                }
            default:
                break;
            }
            playsound = playsound_;
            //cout << playsound << "\n";
        }
        SDL_Flip(des);

    }
    SDL_FreeSurface(glo_bkg_setting);
    return;   
}

void CommonFunc::Show_Help(SDL_Surface* des, TTF_Font* font)
{
    glo_bkg_help = Load_image(bkghelp);
    if (glo_bkg_help == NULL)
        return;

    SDL_Rect pos;
    pos.x = 40;
    pos.y = 740;

    Text_Obj text_help;
    text_help.SetText("Quit");
    text_help.SetColor(Text_Obj::WHITE_TEXT);
    text_help.SetRect(pos.x, pos.y);

    bool selected = 0;
    SDL_Event m_event;
    int y_mouse = 0, x_mouse = 0;
    while (true)
    {
        CommonFunc::Apply_Surface(glo_bkg_help, des, 0, 0);
        text_help.SetRect(text_help.CreatGameText(font, des));

        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
            {
                SDL_FreeSurface(glo_bkg_help);
                return; 
            }
            case SDL_MOUSEMOTION:
            {
                x_mouse = m_event.motion.x;
                y_mouse = m_event.motion.y;
                if (CheckFocusWithRect(x_mouse, y_mouse, text_help.GetRect()))
                {
                    if (selected == 0)
                    {
                        selected = 1;
                        text_help.SetColor(Text_Obj::RED_TEXT);
                    }
                }
                else
                {
                    if (selected == 1)
                    {
                        selected = 0;
                        text_help.SetColor(Text_Obj::WHITE_TEXT);
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                x_mouse = m_event.button.x;
                y_mouse = m_event.button.y;
                if (CheckFocusWithRect(x_mouse, y_mouse, text_help.GetRect()))
                {
                    SDL_FreeSurface(glo_bkg_help);
                    return;
                }
                break;
            }
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_FreeSurface(glo_bkg_help);
                    return;
                }
            default:
                break;
            }
        }
        SDL_Flip(des);
    }
    SDL_FreeSurface(glo_bkg_help);
    return;
}

bool CommonFunc::Show_End(SDL_Surface* des, TTF_Font* font, const int& H_s, const int& glo_s)
{
    glo_bkg_gover= Load_image(bkggameover);
    if (glo_bkg_gover == NULL)
        return 0;

    const int num_item = 3;
    SDL_Rect pos_arr[num_item];
    pos_arr[0].x = 500;
    pos_arr[0].y = 390;

    pos_arr[1].x = 500;
    pos_arr[1].y = 450;

    pos_arr[2].x = 40;
    pos_arr[2].y = 740;

    Text_Obj text[num_item];
    string str_score = "YOUR SCORE: " + to_string(glo_s);
    text[0].SetText(str_score);
    text[0].SetColor(Text_Obj::YELLOW_TEXT);
    text[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    str_score = "HIGH SCORE: " + to_string(H_s);
    text[1].SetText(str_score);
    text[1].SetColor(Text_Obj::YELLOW_TEXT);
    text[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    text[2].SetText("Quit");
    text[2].SetColor(Text_Obj::WHITE_TEXT);
    text[2].SetRect(pos_arr[2].x, pos_arr[2].y);

    bool selectedquit = 0;
    SDL_Event m_event;
    int y_mouse = 0, x_mouse = 0;
    TTF_Font* fontscore = TTF_OpenFont(fontgame1.c_str(), 25);
    while (true)
    {
        CommonFunc::Apply_Surface(glo_bkg_gover, des, 0, 0);
        text[0].CreatGameText(fontscore, des);
        text[1].CreatGameText(fontscore, des);
        text[2].SetRect(text[2].CreatGameText(font, des));


        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
            {
                SDL_FreeSurface(glo_bkg_gover);
                return 1;
            }
            case SDL_MOUSEMOTION:
            {
                x_mouse = m_event.motion.x;
                y_mouse = m_event.motion.y;
                if (CheckFocusWithRect(x_mouse, y_mouse, text[2].GetRect()))
                {
                    if (selectedquit == 0)
                    {
                        selectedquit = 1;
                        text[2].SetColor(Text_Obj::RED_TEXT);
                    }
                }
                else
                {
                    if (selectedquit == 1)
                    {
                        selectedquit = 0;
                        text[2].SetColor(Text_Obj::WHITE_TEXT);
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                x_mouse = m_event.button.x;
                y_mouse = m_event.button.y;
                if (CheckFocusWithRect(x_mouse, y_mouse, text[2].GetRect()))
                {
                    return 1;
                }
                break;
            }
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    SDL_FreeSurface(glo_bkg_gover);
                    return 1;
                }
            default:
                break;
            }
        }
        SDL_Flip(des);

    }
    SDL_FreeSurface(glo_bkg_gover);
    return 1;
}

bool CommonFunc::CheckFocusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}
