/*Tran Truong Phu Tuc - 20520345 - UIT
  Co chia se voi Nguyen Thanh Trong - 20520330
  Ho tro hinh anh Nguyen Thanh Trong*/
#pragma once

#include <Windows.h>
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <time.h>
#include <ctime>
#include <vector>
#include <dos.h>
#include <conio.h>
#include <algorithm> 
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <fstream>
#include <queue>

#undef main

using namespace std;

const int SCREEN_W = 1200;
const int SCREEN_H = 789;
const int SCREEN_BPP = 32;
const int const_Life = 5;
const string data = "data.txt";
const string bkg = "background.png";
const string bkgMenu = "backgroundmenu.png";
const string bkghelp = "backgroundhelp.png";
const string bkgsetting = "backgroundsetting.png";
const string bkggameover = "backgroundgameover.png";
const string hmmain = "xt.png";//ma mau background hunman la 0, 255, 255 -> HEX(0x00, 0xFF, 0xFF) 
const string threat1 = "threat_af1.png";
const string threat2 = "threat_af2.png";
const string Amolazer = "Amolazer1.png";
const string ThreatAmoLazer1 = "Amolazer2.png";
const string ThreatAmoLazer2 = "Amolazer3.png";
const string expthreat = "exp_threat.png";
const string expmain = "exp_main.png";
const string heart = "heart.png";
const string giftheart = "gift_heart.png";
const string giftamo = "gift_amo.png";
const string fontgame1 = "ITCKRIST.ttf";
const string fontgame2 = "04B_30__.ttf";
const string maindie = "main_die.wav";
const string maingun = "main_gun.wav";
const string threatdie1 = "threat_die1.wav";
const string threatdie2 = "threat_die2.wav";

static SDL_Surface* glo_screen = NULL;
static SDL_Surface* glo_background = NULL;
static SDL_Event glo_event;
static SDL_Surface* glo_bkg_help = NULL;
static SDL_Surface* glo_bkg_setting = NULL;
static SDL_Surface* glo_bkg_menu = NULL;
static SDL_Surface* glo_bkg_gover = NULL;
static TTF_Font* glo_font_text1 = NULL;
static TTF_Font* glo_font_text2 = NULL;
static long glo_score = 0;
static long H_score;
static int Num_Life = 5;
static int vong = 1;
static int EndGame = 0;
static int glo_Num_Threats = 15;
static int realtime_Num_Threats = 3;
static bool playsound = 1;
const int GA_FAILED = -1;

static Mix_Chunk* glo_sound_bullet;
static Mix_Chunk* glo_sound_exp[3];

namespace CommonFunc
{
    SDL_Surface* Load_image(string);//load anh
    SDL_Rect Apply_Surface(SDL_Surface*, SDL_Surface*, int, int);//add anh vao screen; x, y: toa do anh se xuat hien
    void Apply_SurfaceClip(SDL_Surface*, SDL_Surface*, SDL_Rect*, int, int);
    bool CheckCollision(const SDL_Rect&, const SDL_Rect&);//kiem tra va cham
    void Clean_Up();//giai phong bien toan cuc
    int Show_Menu(SDL_Surface*, TTF_Font*); 
    void Show_Setting(SDL_Surface*, TTF_Font*, bool&);
    void Show_Help(SDL_Surface*, TTF_Font*);
    bool Show_End(SDL_Surface*, TTF_Font*, const int&, const int&);
    bool CheckFocusWithRect(const int&, const int&, const SDL_Rect&);
}
