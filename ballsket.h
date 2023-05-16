#include <fstream>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"

// initial interface for instructions
int interface1()
{
    int play_number;.k.kh.h
    for (;;)
    {
        Rectangle play11r(500, 250, 300, 40);
        Rectangle rules1r(500, 350, 300, 40);
        Rectangle backbr(500, 450, 300, 40);
        play11r.setColor(COLOR(34,139,34));
        rules1r.setColor(COLOR(34,139,34));
        backbr.setColor(COLOR(34,139,34));
        Text play11(500, 250, " PLAY THE LASSO BALLSKET ");
        Text rules1(500, 350, " RULES AND INSTRUCTIONS ");
        Text backb(500, 450, " BACK TO HOME ");

        int w1 = getClick();
        int x1 = w1 / 65536, y1 = w1 % 65536;

        if (x1 > 350 && x1 < 650 && y1 > 230 && y1 < 270)
        {
            rules1.hide();
            play11.hide();
            rules1r.hide();
            play11r.hide();
            play_number = 1;
            return play_number;
            break;
        }

        else if (x1 > 350 && x1 < 650 && y1 > 330 && y1 < 370)
        {
            rules1.hide();
            play11.hide();
            rules1r.hide();
            play11r.hide();
            Rectangle white(400, 300, 1000, 650);
            white.setColor(COLOR("white"));
            white.setFill(true);

            // rules or instructions started
            Text rulemap1(500, 10, "RULES FOR LASSO BALLSKET GAME (read them carefully):");
            Text rulemap2(500, 50, "The key controls of this game are as follows:");
            Text rulemap3(500, 70, "When t is pressed, throw lasso");
            Text rulemap4(500, 90, "When y is pressed, yank lasso (return to starting point)");
            Text rulemap5(500, 110, "When l is pressed, loop lasso to catch when aything is in range");
            Text rulemap6(500, 130, "When [ is pressed, it decreases the throwing angle of lasso with x axis");
            Text rulemap7(500, 150, "When ] is pressed, it increases the throwing angle of lasso with x axis");
            Text rulemap8(500, 170, "When s is pressed, stop the game and show final score");
            Text rulemap9(500, 190, "When q is pressed, quit the game and exit");

            Rectangle g(500, 250, 900, 80);
            g.setColor(COLOR("yellow")); // gift key instructions
            Text rulemap10(500, 220, " When you open the treasure box (by pressing 'g'),(ONCE in every level) you get to activate anyone one from the below tools (benefits):");
            Text rulemap11(500, 240, "MAXRANGER: It maximises(2.5x) your looping range for 8 time counts.");
            Text rulemap12(500, 260, "SPEEDBOOSTER: It increases the speed of lasso for 8 time counts.");
            Text rulemap13(500, 280, "DOUBLEDOOPER: It will double the coins collected for 8 time counts.");

            Text rulemap14(500, 310, "1) If you dont collect minimum number of coins (4 for first level and subsequently adding 1 for every next level)");
            Text rulemap15(500, 330, "for that level in the stipulated timecounts for that level (12 for first level and subsequently adding 2 for every next level),");
            Text rulemap16(500, 350, "you will lose one life and have to continue the level again.");
            Text rulemap17(500, 375, "2) In this game, there is a lasso (at starting point) and a big basket which contains circular coins of smaller size and");
            Text rulemap18(500, 395, "circular bombs of bigger size.                                          ");
            Text rulemap19(500, 420, "3) You will see remaining timecounts(time) in top-right corner and lives-count(initiated at 5) in bottom-right corner,");
            Text rulemap20(500, 440, "level number and coins collected (in that level) in bottom-middle and highscore against your name in top-left corner.");
            Text rulemap21(500, 465, "4) You have to collect the coins by throwing and looping the lasso .");
            Text rulemap22(500, 485, "Whenever you loop and if there is a coin in your loop, then it gets collected and you get one coin.");
            Text rulemap23(500, 510, "5) Be careful while collecting bombs. If you collect bombs, then you will lose 2 coins.");
            Text rulemap24(500, 530, " Your final SCORE will be total of the collected coins in each level. ");
            // rules or instructions ended

            Text back1(500, 613, "BACK");
            Rectangle back1r(500, 613, 300, 30);
            back1r.setColor(COLOR(119,136,153));

            for (;;)
            {
                int b = getClick();
                int x2 = b / 65536, y2 = b % 65536;
                if (x2 > 350 && x2 < 650 && y2 > 593 && y2 < 633)
                {
                    back1.hide();
                    back1r.hide();
                    white.hide();
                    rulemap1.hide();
                    break;
                }
            }
        }

        else if (x1 > 350 && x1 < 650 && y1 > 430 && y1 < 470)
        {
            break;
        }
    }
    return 0;
}

// the main game of ballsket
void ballsket(string your_name)
{
    // creating the user score file
    string name = your_name + "B.txt";
    fstream file(name);
    if (!file)
    {
        ofstream file(name);
        file << "00";
    }
    file.close();

    float stepTime = STEP_TIME;
    float runTime = 12; // timecounts
    float currTime = 0;
    int min = 1; // compulsory number of balls to be collected for going to next level
    Text ruleTitle(150, 600, "Press 'r' to see rules");

    // name of player
    char namedisplay[100];
    sprintf(namedisplay, "Name : %s", your_name.c_str());
    Text name_show(150, 50, namedisplay);

    // displaying the highest score by collecting it from a txt file
    ifstream myfile(name);
    int highest_score;
    myfile >> highest_score;
    myfile.close();
    char score[100];
    sprintf(score, "Highest Score : %02d", highest_score);
    Text scoredisplay(150, 70, score);

    // Draw lasso at start position
    double release_speed = INIT_RELEASE_SPEED;         // m/s
    double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
    double lasso_ax = 0;
    double lasso_ay = LASSO_G;
    bool paused = true;
    bool rtheta = true;
    Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

    paused = true;
    rtheta = true;
    double coin_speed = COIN_SPEED;
    double coin_angle_deg = COIN_ANGLE_DEG;
    double coin_ax = 0;
    double coin_ay = COIN_G;

    Line b1(0, PLAY_Y_HEIGHT + 35, WINDOW_X + 200, PLAY_Y_HEIGHT + 35);
    b1.setColor(COLOR("blue"));

    Rectangle giftk(500, 20, 1000, 25);
    giftk.setColor(COLOR(216, 74, 169));
    giftk.setFill(true);
    Text giftkey(500, 20, "     Press 'g' to open the treasure.(only once in a level)     ");

    // for showing number of remaining lives
    char lives[100];
    sprintf(lives, "Lives: %d", lasso.livesShow());
    Text LIVES(900, PLAY_Y_HEIGHT + 50, lives);

    // for command pressed
    string msg("Command: _");
    Text charPressed(PLAY_X_START + 50, PLAY_Y_HEIGHT + 50, msg);

    // text for tools ,if activated
    Text max_act(500, 80, "MAXRANGER Activated !!");
    Text speed_act(500, 80, "SPEEDBOOSTER Activated !!");
    Text double_act(500, 80, "DOUBLEDOOPER Activated !!");
    max_act.hide();
    speed_act.hide();
    double_act.hide();

    Text start1(500, 630, "Click on the screen to start!!");
    getClick();
    start1.hide();
    for (int i = 1; i <= 21; i++)
    {
        // for showing the final score
        if (lasso.livesShow() == 0 || i == 21 || lasso.livesShow() == 99)
        {
            if (lasso.getfinalscore() > highest_score)
            { // High score ,if made
                Rectangle highscreen1(500, 90, 140, 20);
                highscreen1.imprint();
                Text high(500, 90, "!! New High Score !!");
                high.imprint();
            }
            Rectangle final1(500, 180, 100, 100);
            final1.rotate(PI / 4);
            final1.setColor(COLOR(47, 163, 240));
            Text r1(500, 170, " Your SCORE "); // Final SCORE
            int finalscore = lasso.getfinalscore();
            Text r2(500, 190, finalscore);

            // storing new highscore if created
            if (lasso.getfinalscore() > highest_score)
            {
                int zero_var[1] = {0};
                fstream newscore(name);
                newscore << zero_var[0];
                newscore << zero_var[0];
                newscore << lasso.getfinalscore();
            }

            Rectangle final2(500, 300, 160, 30);
            Text thanks(500, 300, "  Thanks For Playing  ");
            wait(3);
            break;
        }

        // text for welcoming to next level
        char nameoflevel[256];
        string levelname[20] = {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "Thirteenth", "Fourteenth", "Fifteenth", "Sixteenth", "Seventeenth", "Eighteenth", "Nineteenth", "Twentieth"};
        sprintf(nameoflevel, "WelCome To %s Level !!", levelname[i - 1].c_str());
        Text wlcm(500, 200, nameoflevel);

        Text start2(500, 600, "ARE YOU READY? : Click on the screen to start the Level !!");
        getClick();

        start2.hide();
        wlcm.hide();

        // Creating the Basket
        Rectangle big1s(500, 525, 400, 190);
        big1s.setColor(COLOR(204, 204, 0));
        big1s.setFill(true);
        Rectangle big2s(500, 423, 500, 20);
        big2s.setColor(COLOR(107, 146, 172));
        big2s.setFill(true);
        Rectangle smalls1(260, 445, 20, 20);
        smalls1.setColor(COLOR(107, 146, 172));
        smalls1.setFill(true);
        Rectangle smalls2(740, 445, 20, 20);
        smalls2.setColor(COLOR(107, 146, 172));
        smalls2.setFill(true);
        Rectangle smalls3(285, 445, 30, 20);
        smalls3.setColor(COLOR(204, 204, 0));
        smalls3.setFill(true);
        Rectangle smalls4(715, 445, 30, 20);
        smalls4.setColor(COLOR(204, 204, 0));
        smalls4.setFill(true);

        // Iniatialising all the Objects
        Coin coin1(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta), coin2(coin_speed, coin_angle_deg, coin_ax + 30, coin_ay, paused, rtheta), coin3(coin_speed, coin_angle_deg, coin_ax - 30, coin_ay, paused, rtheta), coin4(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
        Bomb bomb1(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta), bomb2(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

        if (i % 2 != 0)
        { // two bombs only when it is a even level
            bomb2.pause();
        }
        int stop_counter = 0;
        float time_counter = 0;

        Rectangle big1(500, 570, 400, 190);
        Rectangle big2(500, 465, 500, 20);
        Rectangle big3(500, 500, 400, 8);
        Rectangle big4(500, 520, 400, 8);
        Rectangle big5(500, 540, 400, 8);
        big1.setColor(COLOR(204, 204, 0));
        big2.setColor(COLOR(107, 146, 172));
        big3.setColor(COLOR("blue"));
        big4.setColor(COLOR("blue"));
        big5.setColor(COLOR("blue"));
        big1.setFill(true);
        big2.setFill(true);
        big3.setFill(true);
        big4.setFill(true);
        big5.setFill(true);
        // Completed Creating the basket

        // for showing the name of game on main screen of game
        Rectangle live_screen1(500, 575, 120, 50);
        live_screen1.setColor(COLOR("white"));
        live_screen1.setFill(true);
        Rectangle live_screen2(500, 640, 1000, 50);
        live_screen2.setColor(COLOR(216, 74, 169));
        live_screen2.setFill(true);
        Text game(500, 630, "                                                  L A S S O   B A L L S K E T                                                  ");
        live_screen2.imprint();
         game.imprint();
         
        // for showing the target required to complete to go to next level
        char target[256];
        sprintf(target, "Target Coins : %d", min);
        Text targetS(900, PLAY_Y_HEIGHT + 100, target);

        // for showing the number of level reached
        char level[256];
        sprintf(level, "LEVEL: %d", i);
        Text r(500, 560, level);

        // for number of coins collected in each level
        char coinScoreStr[256];
        sprintf(coinScoreStr, "Coins Collected: %d", lasso.getNumCoins());
        Text coinScore(500, 590, coinScoreStr);

        for (;;)
        {
            if (lasso.livesShow() == 0)
            { // If lives are exhausted then the game ends from here
                Text t(500, 150, "GAME OVER : Your lives are exhausted.");
                wait(2);
                break;
            }
            //checking if minimum number of coins collected
            if (currTime > runTime)
            {
                currTime = 0;
                if (lasso.getNumCoins() >= min)
                {
                    max_act.hide();
                    speed_act.hide();
                    double_act.hide();
                    time_counter = 0;
                    lasso.restoreTool_act();
                    min += 1;
                    break;
                }
                else
                { // if a level is not completed in its time, then one life is deducted
                    lasso.livesDec();
                    Text deduct(500, 60, "Ah! You lost one life...");
                    wait(2);
                }
            }

            // for showing the time counts remaining
            int time = int(runTime) - int(currTime);
            char *timet;
            sprintf(timet, "Time left: %d", time);
            Text timedisplay(900, 70, timet);

            // condition for the treasure box tools
            if (lasso.checkonce())
            {
                // maxranger
                if (lasso.valueofmax_act())
                {
                    max_act.show();
                    time_counter += stepTime;
                }
                // speedbooster
                if (lasso.valueofspeed_act())
                {
                    speed_act.show();
                    time_counter += stepTime;
                }
                // doubledooper
                if (lasso.valueofdouble_act())
                {
                    double_act.show();
                    time_counter += stepTime;
                }
                if (time_counter > 8)
                {
                    max_act.hide();
                    speed_act.hide();
                    double_act.hide();
                    time_counter = 0;
                    lasso.restoreTool_act();
                }
            }
            // When t is pressed, throw lasso
            // When y is pressed, yank lasso
            // When l is pressed, loop lasso when the coin or bomb is in range
            // When [ is pressed, it decreases the throwing angle of lasso with x axis
            // When ] is pressed, it increases the throwing angle of lasso with x axis
            // When r is pressed, show rules
            // When s is pressed, stop the game and show final score
            // When q is pressed, quit the game and exit

            // Main starting
            XEvent e;
            bool pendingEv = checkEvent(e);
            if (pendingEv)
            {
                char c = charFromEvent(e);
                msg[msg.length() - 1] = c;
                charPressed.setMessage(msg);
                switch (c)
                {
                case 't':
                    lasso.unpause();
                    break;
                case 'y':
                    lasso.yank();
                    break;
                case 'l':
                    lasso.loopit();
                    // checking whether the coin is in the range of loop
                    lasso.check_for_coin(&coin1);
                    lasso.check_for_coin(&coin2);
                    lasso.check_for_coin(&coin3);
                    lasso.check_for_coin(&coin4);

                    // checking whether the bomb is in the range of loop
                    lasso.check_for_bomb(&bomb1);
                    lasso.check_for_bomb(&bomb2);

                    wait(STEP_TIME * 5);
                    break;
                case '[':
                    if (lasso.isPaused())
                    {
                        lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);
                    }
                    break;
                case ']':
                    if (lasso.isPaused())
                    {
                        lasso.addAngle(+RELEASE_ANGLE_STEP_DEG);
                    }
                    break;
                case 'r':
                {
                    Rectangle s(500, 325, 1000, 650);
                    s.setColor(COLOR("yellow"));
                    s.setFill(true);
                    // in-game short rules
                    Text rule2(500, 50, " The key controls of this game are as follows: ");
                    Text rule3(500, 80, " When t is pressed, throw lasso ");
                    Text rule4(500, 100, " When y is pressed, yank lasso (return to starting point) ");
                    Text rule5(500, 120, " When l is pressed, loop lasso to catch when aything is in range ");
                    Text rule6(500, 140, " When [ is pressed, it decreases the throwing angle of lasso with x axis ");
                    Text rule7(500, 160, " When ] is pressed, it increases the throwing angle of lasso with x axis ");
                    Text rule8(500, 180, " When s is pressed, stop the game and show final score ");
                    Text rule9(500, 200, " When q is pressed, quit the game and exit ");
                    Text rule10(500, 220, "When 'g' is pressed, you open the treasure box.");
                    Text end(500, 320, " Press 'c' key and then click on the screen to close this page and continue. ");
                    getClick();
                }
                break;
                case 'g': // gift key
                    if (stop_counter == 0)
                    {
                        lasso.yank();
                        lasso.open_the_treasure();
                        stop_counter = 1;
                    }
                    break;
                //stopping or quitting the game
                case 's':
                    lasso.ending();
                    break;
                case 'q':
                    exit(0);
                default:
                    break;
                }
            }
            if (lasso.livesShow() == 99)
            {
                break;
            }
            lasso.nextStep(stepTime);

            // if lasso gets paused then for next interation , unpause it
            coin1.Paused();
            coin2.Paused();
            coin3.Paused();
            coin4.Paused();
            bomb1.Paused();
            if (i % 2 == 0)
            {
                bomb2.Paused();
            }
            // if moving object reaches y position, then resetting it again for next jump
            coin1.Reset();
            coin2.Reset();
            coin3.Reset();
            coin4.Reset();
            bomb1.Reset();
            if (i % 2 == 0)
            {
                bomb2.Reset();
            }

            sprintf(lives, "Lives: %d", lasso.livesShow());
            LIVES.setMessage(lives);

            sprintf(coinScoreStr, "Coins Collected: %d", lasso.getNumCoins());
            coinScore.setMessage(coinScoreStr);

            currTime += stepTime;

            wait(stepTime);
        }
        //restarting the moving object for new level
        coin1.pause();
        coin2.pause();
        coin3.pause();
        coin4.pause();
        bomb1.pause();
        bomb2.pause();
        coin1.resetCoin();
        coin2.resetCoin();
        coin3.resetCoin();
        coin4.resetCoin();

        bomb1.resetbomb();
        bomb2.resetbomb();

        lasso.yank();

        coin1.unpause();
        coin2.unpause();
        coin3.unpause();
        coin4.unpause();
        bomb1.unpause();
        if (i % 2 == 0)
        {
            bomb2.unpause();
        }

        lasso.resetnumcoins();
        runTime += 2;
    } // End for(;;)

    wait(3);
} // End lasso ballsket