#include "coin.h"
#include "lasso.h"
#include <stdlib.h>

// Coin specifications
void Coin::initCoin()
{
  coin_start_x = (PLAY_X_START + WINDOW_X) / 2;
  coin_start_y = PLAY_Y_HEIGHT;
  const char *colours[3] = {"blue", "red", "black"};
  int x[6] = {420, 450, 480, 400, 380, 550};
  coin_circle1.reset(x[rand() % 6], coin_start_y, COIN_SIZE);
  coin_circle1.setColor(COLOR(colours[rand() % 3]));
  coin_circle1.setFill(true);
  addPart(&coin_circle1);
}
void Coin::resetCoin()
{
  int coinspeed[5] = {120, 150, 140, 100, 80};
  double coin_speed = coinspeed[rand() % 5];
  int angle[7] = {80, 85, 90, 95, 100, 60, 45};
  double coin_angle_deg = angle[rand() % 7];
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}
void Coin::Paused()  // for checking the pause condition and work according to it
{
  this->nextStep(0.05);
  if (this->isPaused())
  {
    this->unpause();
  }
}
void Coin::Reset()  // if the object has reached the horizontal line then relaunch it upwards 
{
if (this->getYPos() > PLAY_Y_HEIGHT)
{
  this->resetCoin();
}
this->unpause();
}

// Bomb specifications
void Bomb::initbomb()
{
  coin_start_x = (PLAY_X_START + WINDOW_X) / 2;
  coin_start_y = PLAY_Y_HEIGHT;
  int x[6] = {420, 450, 480, 400, 380, 550};
  int t = x[rand() % 6];
  coin_circle3.reset(t, coin_start_y, COIN_SIZE * 2);
  cross1.reset(t, coin_start_y, 2, COIN_SIZE * 2);
  cross2.reset(t, coin_start_y, 2, COIN_SIZE * 2);
  coin_circle3.setColor(COLOR("red"));
  coin_circle3.setFill(true);
  cross1.rotate(PI / 4);
  cross2.rotate(-PI / 4);
  cross1.setFill(true);
  cross2.setFill(true);
  addPart(&coin_circle3);
  addPart(&cross1);
  addPart(&cross2);
}
void Bomb::resetbomb()
{
  int coinspeed[5] = {120, 150, 140, 100, 80};
  double coin_speed = coinspeed[rand() % 5];
  int angle[7] = {80, 85, 90, 95, 100, 60, 45};
  double coin_angle_deg = angle[rand() % 7];
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}
void Bomb::Paused()  // for checking the pause condition and work according to it
{
  this->nextStep(0.05);
  if (this->isPaused())
  {
    this->unpause();
  }
}
void Bomb::Reset()  // if the object has reached the horizontal line then relaunch it upwards 
{
if (this->getYPos() > PLAY_Y_HEIGHT)
{
  this->resetbomb();
}
this->unpause();
}

// Coin1 specifications
void Coin1::initCoin1()
{
  coin_start_x = (PLAY_X_START + WINDOW_X) / 2;
  coin_start_y = PLAY_Y_HEIGHT;
  int x[6] = {430, 470, 490, 410, 390, 530};
  int rand1 = x[rand() % 6];
  text_1.reset(rand1, coin_start_y, "1");
  addPart(&text_1);
}
void Coin1::resetCoin1()
{
  int coinspeed[5] = {120, 150, 140, 100, 80};
  double coin_speed = coinspeed[rand() % 5];
  int angle[5] = {80, 85, 90, 95, 100};
  double coin_angle_deg = angle[rand() % 5];
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}
void Coin1::Paused()  // for checking the pause condition and work according to it
{
  this->nextStep(0.05);
  if (this->isPaused())
  {
    this->unpause();
  }
}
void Coin1::Reset()  // if the object has reached the horizontal line then relaunch it upwards 
{
if (this->getYPos() > PLAY_Y_HEIGHT)
{
  this->resetCoin1();
}
this->unpause();
}

// Coin2 specifications
void Coin2::initCoin2()
{
  coin_start_x = (PLAY_X_START + WINDOW_X) / 2;
  coin_start_y = PLAY_Y_HEIGHT;
  int x[6] = {450, 420, 480, 510, 390, 540};
  int rand3 = x[rand() % 6];
  text_3.reset(rand3, coin_start_y, "3");
  addPart(&text_3);
}
void Coin2::resetCoin2()
{
  int coinspeed[5] = {120, 150, 140, 100, 80};
  double coin_speed = coinspeed[rand() % 5];
  int angle[5] = {80, 85, 90, 95, 100};
  double coin_angle_deg = angle[rand() % 5];
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}
void Coin2::Paused()  // for checking the pause condition and work according to it
{
  this->nextStep(0.05);
  if (this->isPaused())
  {
    this->unpause();
  }
}
void Coin2::Reset()  // if the object has reached the horizontal line then relaunch it upwards 
{
if (this->getYPos() > PLAY_Y_HEIGHT)
{
  this->resetCoin2();
}
this->unpause();
}

// specifications of special Treasure (bonus star) coin like angle and colors
void Treasure_s::initTreasure_s()
{
  coin_start_x = (PLAY_X_START + WINDOW_X) / 2;
  coin_start_y = PLAY_Y_HEIGHT;
  int x[6] = {440, 460, 470, 410, 490, 520};
  int t = x[rand() % 6];
  r.reset(t, coin_start_y, 20, 15);
  l1.reset(t, coin_start_y, 2, 15);
  l2.reset(t, coin_start_y, 2, 20);
  l2.rotate(PI / 2);
  r.setColor(COLOR("blue"));
  r.setFill(true);
  l1.setColor(COLOR("red"));
  l1.setFill(true);
  l2.setColor(COLOR("red"));
  l2.setFill(true);
  addPart(&r);
  addPart(&l1);
  addPart(&l2);
}
void Treasure_s::resetTreasure_s()
{
  double coin_speed = 130;
  int angle[5] = {80, 85, 90, 95, 100};
  double coin_angle_deg = angle[rand() % 5];
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}
void Treasure_s::Paused()  // for checking the pause condition and unpause according to it
{
  this->nextStep(0.05);
  if (this->isPaused())
  {
    this->unpause();
  }
}
void Treasure_s::Reset() // if the object has reached PLAY_Y_HEIGHT then relaunch it upwards 
{
if (this->getYPos() > PLAY_Y_HEIGHT)
{
  this->resetTreasure_s();
}
this->unpause();
}

// Bomb_s specifications
void Bomb_s::initbomb_s()
{
  coin_start_x = (PLAY_X_START + WINDOW_X) / 2;
  coin_start_y = PLAY_Y_HEIGHT;
  int x[6] = {375, 465, 505, 495, 425, 545};
  int t = x[rand() % 6];
  coin_circle3.reset(t, coin_start_y, COIN_SIZE * 2);
  cross1.reset(t, coin_start_y, 2, COIN_SIZE * 2);
  cross2.reset(t, coin_start_y, 2, COIN_SIZE * 2);
  coin_circle3.setColor(COLOR("red"));
  coin_circle3.setFill(true);
  cross1.rotate(PI / 4);
  cross2.rotate(-PI / 4);
  cross1.setFill(true);
  cross2.setFill(true);
  addPart(&coin_circle3);
  addPart(&cross1);
  addPart(&cross2);
}
void Bomb_s::resetbomb_s()
{
  int coinspeed[5] = {120, 150, 140, 100, 80};
  double coin_speed = coinspeed[rand() % 5];
  int angle[5] = {80, 85, 90, 95, 100};
  double coin_angle_deg = angle[rand() % 5];
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}
void Bomb_s::Paused()  // for checking the pause condition and work according to it
{
  this->nextStep(0.05);
  if (this->isPaused())
  {
    this->unpause();
  }
}
void Bomb_s::Reset() // if the object has reached the horizontal line then relaunch it upwards 
{
if (this->getYPos() > PLAY_Y_HEIGHT)
{
  this->resetbomb_s();
}
this->unpause();
}