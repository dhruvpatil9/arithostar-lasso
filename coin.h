#ifndef _COIN_H_
#define _COIN_H_

#include "MovingObject.h"

// for creating Coin
class Coin : public MovingObject
{
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle1;

public:
  Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed - 60;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }
  void initCoin();
  void resetCoin();
  void Paused();
  void Reset();

}; // End class Coin

// for creating bomb
class Bomb : public MovingObject
{
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle3;
  Rectangle cross1, cross2;

public:
  Bomb(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed - 60;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initbomb();
  }
  void initbomb();
  void resetbomb();
  void Paused();
  void Reset();
}; // End class Bomb

// for creating +1 coin
class Coin1 : public MovingObject
{
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Text text_1;

public:
  Coin1(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed - 60;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin1();
  }
  void initCoin1();
  void resetCoin1();
  void Paused();
  void Reset();

}; // End class Coin1

// for creating +3 coin
class Coin2 : public MovingObject
{
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Text text_3;

public:
  Coin2(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed - 60;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin2();
  }
  void initCoin2();
  void resetCoin2();
  void Paused();
  void Reset();

}; // End class Coin2

// for creating treasure box(or coin)
class Treasure_s : public MovingObject
{
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Rectangle r, l1, l2;

public:
  Treasure_s(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed - 60;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initTreasure_s();
  }
  void initTreasure_s();
  void resetTreasure_s();
  void Paused();
  void Reset();
}; // End class Treasure_s

// for creating bomb 
class Bomb_s : public MovingObject
{
  double coin_start_x;
  double coin_start_y;
  double release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle3;
  Rectangle cross1, cross2;

public:
  Bomb_s(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta)
  {
    release_speed = speed - 60;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initbomb_s();
  }
  void initbomb_s();
  void resetbomb_s();
  void Paused();
  void Reset();
}; // End class Bomb_s

#endif