#include <simplecpp>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
using namespace simplecpp;

//Checking the distance between the lasso centre and the object position
bool Lasso::Dist(double obj_x, double obj_y, double range)
{
  double lasso_x = getXPos();
  double lasso_y = getYPos();
  double xdiff = (lasso_x - obj_x);
  double ydiff = (lasso_y - obj_y);
  double distance = sqrt((xdiff * xdiff) + (ydiff * ydiff));
  return (distance < range);
}

void Lasso::draw_lasso_band()
{
  double len = (release_speed / MAX_RELEASE_SPEED) * LASSO_BAND_LENGTH;
  double arad = release_angle_deg * PI / 180.0;
  double xlen = len * cos(arad);
  double ylen = len * sin(arad);
  lasso_band.reset(lasso_start_x, lasso_start_y, (lasso_start_x - (len-20)*cos(arad)), (lasso_start_y + (len-20)*sin(arad)));
  lasso_band.setThickness(LASSO_THICKNESS);
  lasso_band2.reset((lasso_start_x - xlen), (lasso_start_y + ylen),20);
  lasso_band1.reset((lasso_start_x - xlen), (lasso_start_y + ylen),21);
} // End Lasso::draw_lasso_band()

void Lasso::initLasso()
{ // initialising the lasso and some of the variables
  lasso_start_x = (PLAY_X_START + LASSO_X_OFFSET);
  lasso_start_y = (PLAY_Y_HEIGHT - LASSO_Y_HEIGHT);
  lasso_circle.reset(lasso_start_x, lasso_start_y, LASSO_SIZE);
  lasso_circle.setColor(COLOR("black"));
  lasso_circle.setFill(true);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE / 2);
  lasso_loop.setColor(COLOR("red"));
  lasso_loop.setFill(true);
  addPart(&lasso_circle);
  addPart(&lasso_loop);
  lasso_looped = false;

  the_coin = NULL;
  bomblast1 = NULL;
  final_score = 0;

  the_coin1 = NULL;
  the_coin2 = NULL;
  treasure_gift = NULL;
  bomblast = NULL;
  num_coins = 0;
  currentLives = 5;
  extrastar = 0;

  lasso_band.setColor(COLOR("green"));
  lasso_band2.setColor(COLOR("yellow"));
  lasso_band2.setFill(true);
  draw_lasso_band();
} // End Lasso::initLasso()

int count = 0, add = 1;
bool speed_act = 0, max_act = 0, double_act = 0, check = 0;
double range = LASSO_RADIUS;

bool Lasso::checkonce()
{
  return check;
}
void Lasso::restoreTool_act()
{ // for deactivating any tool that is activated
  speed_act = 0;
  max_act = 0;
  double_act = 0;
  add = 1;
  range = LASSO_RADIUS;
  check = 0;
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  release_speed = 110;
  yank();
}
// for speedbooster activation
bool Lasso::valueofspeed_act()
{
  return speed_act;
}
// for maxranger activation
bool Lasso::valueofmax_act()
{
  return max_act;
}
// for doubledooper activation
bool Lasso::valueofdouble_act()
{
  return double_act;
}
// lives deduction
void Lasso::livesDec()
{
  currentLives--;
}
// this idea is for quitting the game and getting the score
void Lasso::ending()
{
  currentLives = 99;
}
//for resetting the coin number for showing levels //
void Lasso::resetnumcoins()
{
  num_coins = 0;
}

// returning to starting point
void Lasso::yank()
{
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
  lasso_loop.reset(lasso_start_x, lasso_start_y, LASSO_SIZE / 2);
  lasso_loop.setFill(true);
  lasso_looped = false;
} // End Lasso::yank()

//opening the loop for catching
void Lasso::loopit()
{
  // Already looped
  lasso_loop.reset(getXPos(), getYPos(), range);
  lasso_loop.setFill(false);
  lasso_looped = true;
}
// End Lasso::loopit()

void Lasso::addAngle(double angle_deg) // For changing the angle between lasso and the horizontal line
{
  release_angle_deg += angle_deg;
  if (release_angle_deg < MIN_RELEASE_ANGLE_DEG)
  {
    release_angle_deg = MIN_RELEASE_ANGLE_DEG;
  }
  if (release_angle_deg > MAX_RELEASE_ANGLE_DEG)
  {
    release_angle_deg = MAX_RELEASE_ANGLE_DEG;
  }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addAngle()

void Lasso::addSpeed(double speed) // Adding speed
{
  release_speed += speed;
  if (release_speed < MIN_RELEASE_SPEED)
  {
    release_speed = MIN_RELEASE_SPEED;
  }
  if (release_speed > MAX_RELEASE_SPEED)
  {
    release_speed = MAX_RELEASE_SPEED;
  }
  bool paused = true, rtheta = true;
  reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
} // End Lasso::addSpeed()

void Lasso::nextStep(double stepTime)
{
  draw_lasso_band();
  MovingObject::nextStep(stepTime);
  if (getYPos() > PLAY_Y_HEIGHT)
  {
    yank();
  }
} // End Lasso::nextStep()

// Check For Normal Coins whether they are in range of loop
void Lasso::check_for_coin(Coin *coinPtr)
{
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();

  if (this->Dist(coin_x, coin_y, range))
  {
    the_coin = coinPtr;
    num_coins += add;
    final_score += add;
    Text caught(500, 45, "You catched a coin.");
    wait(1);
    coinPtr->resetCoin();
    caught.hide();
  }
}

// For opening the treasure box by pressing 'g' key
void Lasso::open_the_treasure()
{
  Rectangle screen(500, 325, 1000, 650);
  screen.setColor(COLOR("white"));
  screen.setFill(true);

  Rectangle gift(500, 100, 90, 40), line1(500, 100, 5, 40), line2(500, 100, 5, 90);
  line2.rotate(PI / 2);
  gift.setColor(COLOR(64,111,240));
  gift.setFill(true);
  line1.setColor(COLOR(219,98,38));
  line1.setFill(true);
  line2.setColor(COLOR(219,98,38));
  line2.setFill(true);

  Text congo(500, 150, "You have opened the treasure box.");
  Text select(500, 180, "Choose the tool you want to activate.");
  Text maxranger(250, 300, "MAXRANGER");
  Text speedbooster(750, 300, "SPEEDBOOSTER");
  Text doubledooper(500, 400, "DOUBLEDOOPER");
  Rectangle maxr(250, 300, 200, 40);
  Rectangle speedr(750, 300, 200, 40);
  Rectangle doubler(500, 400, 200, 40);
  maxr.setColor(COLOR(151,32,112));
  speedr.setColor(COLOR(151,32,112));
  doubler.setColor(COLOR(151,32,112));

  for(;;){
  int g = getClick();
  int x = g / 65536, y = g % 65536;
  if (x > 150 && x < 350 && y > 280 && y < 320)
  { // maxranger
    bool paused = true, rtheta = true;
    reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
    range = LASSO_RADIUS * 2.5;
    max_act = 1;
    check = 1;
    break;
  }
  else if (x > 650 && x < 850 && y > 280 && y < 320)
  { // speedbooster
    bool paused = true, rtheta = true;
    reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
    release_speed = 160;
    speed_act = 1;
    check = 1;
    yank();
    break;
  }
  else if (x > 400 && x < 600 && y > 380 && y < 420)
  { // doubledooper
    bool paused = true, rtheta = true;
    reset_all(lasso_start_x, lasso_start_y, release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);
    add = 2;
    double_act = 1;
    check = 1;
    break;
  }
  }
}

// Check For Bomb whether they are in range of loop
void Lasso::check_for_bomb(Bomb *coinPtr)
{
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  if (this->Dist(coin_x, coin_y, range))
  {
    bomblast1 = coinPtr;
    if (num_coins > 2)
    {
      num_coins = num_coins - 2;
      final_score -= 2;
    }
    else
    {
      final_score -= num_coins;
      num_coins = 0;
      Text caughtbomb(500, 55, "Ouch! You catched a bomb.");
      wait(1);
      coinPtr->resetbomb();
      caughtbomb.hide();
    }
  }
}
// End Lasso::check_for_coin()

// Check For number +1 whether it is in range of loop
void Lasso::check_for_coin1(Coin1 *coinPtr)
{
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  if (this->Dist(coin_x, coin_y, range))
  {
    the_coin1 = coinPtr;
    num_coins++;
    Text caught(500, 45, "You catched a +1.");
    wait(1);
    coinPtr->resetCoin1();
    caught.hide();
  }
}

// Check For number +3 whether it is in range of loop
void Lasso::check_for_coin2(Coin2 *coinPtr)
{
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  if (this->Dist(coin_x, coin_y, range))
  {
    the_coin2 = coinPtr;
    num_coins += 3;
    Text caught(500, 45, "You catched a +3.");
    wait(1);
    coinPtr->resetCoin2();
    caught.hide();
  }
}

// Check For Special Treasure (bonus star) Coin whether it is in range of loop
void Lasso::check_for_treasure_s(Treasure_s *coinPtr)
{
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  if (this->Dist(coin_x, coin_y, range))
  {
    treasure_gift = coinPtr;
    Rectangle screen(500, 160, 400, 40);
    screen.setColor(COLOR("white"));
    screen.setFill(true);
    Text congo(500, 150, "Hurray!! You collected the treasure box.");
    Text addstar(500, 170, "You get an extra star.");
    extrastar++;
    wait(1);
    treasure_gift->getAttachedTo(this);
    coinPtr->resetTreasure_s();
  }
}

// Check For Bomb whether they are in range of loop
void Lasso::check_for_bomb_s(Bomb_s *coinPtr)
{
  double coin_x = coinPtr->getXPos();
  double coin_y = coinPtr->getYPos();
  if (this->Dist(coin_x, coin_y, range))
  {
    bomblast = coinPtr;
    if (num_coins > 2)
    {
      num_coins = num_coins - 2;
    }
    else
    {
      final_score -= num_coins;
      num_coins = 0;
      Text caughtbomb(500, 55, "Ouch! You catched a bomb.");
      wait(1);
      bomblast->getAttachedTo(this);
      coinPtr->resetbomb_s();
      caughtbomb.hide();
    }
  }
}
