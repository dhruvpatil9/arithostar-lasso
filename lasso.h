#ifndef _LASSO_H_
#define _LASSO_H_

#include "MovingObject.h"
#include "coin.h"

//#define WINDOW_X 1200
//#define WINDOW_Y 960
#define WINDOW_X 800
#define WINDOW_Y 600

#define STEP_TIME 0.05

#define PLAY_X_START 100
#define PLAY_Y_START 0
#define PLAY_X_WIDTH (WINDOW_X - PLAY_X_START)
#define PLAY_Y_HEIGHT (WINDOW_Y - 100)

#define LASSO_X_OFFSET 100
#define LASSO_Y_HEIGHT 100
#define LASSO_BAND_LENGTH LASSO_X_OFFSET
#define LASSO_THICKNESS 5

#define COIN_GAP 1

#define RELEASE_ANGLE_STEP_DEG 5
#define MIN_RELEASE_ANGLE_DEG 0
#define MAX_RELEASE_ANGLE_DEG (360 - RELEASE_ANGLE_STEP_DEG)
#define INIT_RELEASE_ANGLE_DEG 45

#define RELEASE_SPEED_STEP 20
#define MIN_RELEASE_SPEED 0
#define MAX_RELEASE_SPEED 200
#define INIT_RELEASE_SPEED 110

#define COIN_SPEED 120
#define COIN_ANGLE_DEG 90

#define LASSO_G 30
#define COIN_G 30

#define LASSO_SIZE 10
#define LASSO_RADIUS 35
#define COIN_SIZE 5

class Lasso : public MovingObject
{
  double lasso_start_x;
  double lasso_start_y;
  double release_speed;
  double release_angle_deg;
  double lasso_ax;
  double lasso_ay;

  // Moving parts
  Circle lasso_circle;
  Circle lasso_loop;

  // Non-moving parts
  Line lasso_band;
  Circle lasso_band1,lasso_band2;

  // State info
  bool lasso_looped;
  Coin *the_coin;
  Bomb *bomblast1;
  Coin1 *the_coin1;
  Coin2 *the_coin2;
  Treasure_s *treasure_gift;
  Bomb_s *bomblast;

  // current game info
  int num_coins;
  int final_score;
  int currentLives;
  int extrastar;

  void initLasso();
public:
  Lasso(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed;
    release_angle_deg = angle_deg;
    lasso_ax = argax;
    lasso_ay = argay;
    initLasso();
  }
  // all functions under the Lasso class
  
  bool Dist(double obj_x,double obj_y,double range);
  void draw_lasso_band();
  void yank();
  void loopit();
  void nextStep(double t);
  void addAngle(double angle_deg);
  void addSpeed(double speed);
  void subSpeed(double speed);
  void resetnumcoins();
  void livesDec();
  void ending();

// for the tools activation
  bool checkonce();
  void restoreTool_act();
  bool valueofspeed_act();
  bool valueofmax_act();
  bool valueofdouble_act();

   
  // for ballsket
  void open_the_treasure();
  void check_for_coin(Coin *coin);
  void check_for_bomb(Bomb *coin);

  // for arithostar
  void check_for_treasure_s(Treasure_s *coin);
  void check_for_coin1(Coin1 *coin);
  void check_for_coin2(Coin2 *coin);
  void check_for_bomb_s(Bomb_s *coin);

  int getNumCoins() { return num_coins; }
  int livesShow() { return currentLives; }
  int extrastars() { return extrastar; }
  int getfinalscore() { return final_score; }

}; // End class Lasso

#endif