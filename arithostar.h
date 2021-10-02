#include <fstream>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"

// initial interface for instructions
int interface2()
{
    int play_number;
    for (;;)
    {
        Rectangle play21r(500, 250, 300, 40);
        Rectangle rules2r(500, 350, 300, 40);
        Rectangle backlr(500, 450, 300, 40);
        play21r.setColor(COLOR(34,139,34));
        rules2r.setColor(COLOR(34,139,34));
        backlr.setColor(COLOR(34,139,34));
        Text play21(500, 250, " PLAY THE LASSO ARITHO-STAR ");
        Text rules2(500, 350, " RULES AND INSTRUCTIONS ");
        Text backl(500, 450, " BACK TO HOME ");

        int w1 = getClick();
        int x1 = w1 / 65536, y1 = w1 % 65536;

        if (x1 > 350 && x1 < 650 && y1 > 230 && y1 < 270)
        {
            rules2.hide();
            play21.hide();
            rules2r.hide();
            play21r.hide();
            play_number = 2;
            return play_number;
            break;
        }
        else if (x1 > 350 && x1 < 650 && y1 > 330 && y1 < 370)
        {
            rules2.hide();
            play21.hide();
            rules2r.hide();
            play21r.hide();
            Rectangle white(400, 300, 1000, 650);
            white.setColor(COLOR("white"));
            white.setFill(true);

            // rules or instructions started
            Text rulemap1(500, 10, "RULES FOR LASSO ARITHOSTAR GAME (read them carefully):");
            Text rulemap2(500, 50, "The key controls of this game are as follows:");
            Text rulemap3(500, 70, "When t is pressed, throw lasso");
            Text rulemap4(500, 90, "When y is pressed, yank lasso (return to starting point)");
            Text rulemap5(500, 110, "When l is pressed, loop lasso to catch when aything is in range");
            Text rulemap6(500, 130, "When [ is pressed, it decreases the throwing angle of lasso with x axis");
            Text rulemap7(500, 150, "When ] is pressed, it increases the throwing angle of lasso with x axis");
            Text rulemap8(500, 170, "When = is pressed, speed of lasso increases and when - is pressed, speed of lasso decreases.");
            Text rulemap9(500, 190, "When s is pressed, stop the game and show final score");
            Text rulemap10(500, 210, "When q is pressed, quit the game and exit");
            Text rulemap11(500, 255, "1) If you dont collect exact sum (6 for first level and subsequently adding 2 for every next level)");
            Text rulemap12(500, 275, "for that level in the stipulated timecounts for that level (10 for first level and subsequently adding 2 for every next level),");
            Text rulemap13(500, 295, "you will lose one life and have to continue the level again.");
            Text rulemap14(500, 320, "2) In this game, there is a lasso (at starting point) and a big basket which contains +1 and +3 numbers and ");
            Text rulemap15(500, 340, "circular bombs and treasure boxes.");
            Text rulemap16(500, 365, "3) You will see remaining timecounts(time) in top-right corner and lives-count(initiated at 5) in bottom-right corner,");
            Text rulemap17(500, 385, "level number and sum collected (in that level) in bottom-middle and highscore against your name in top-left corner.");
            Text rulemap18(500, 410, "4) You have to collect the numbers or bombs or treasure box by throwing and looping the lasso .");
            Text rulemap19(500, 430, "Whenever you loop and if there is a object in your loop, then it gets collected .");
            Text rulemap20(500, 455, "5) Be careful while collecting bombs.");
            Text rulemap21(500, 475, "If you collect bombs, then you will lose 2 from the total sum.");

            Rectangle treasure(500, 525, 900, 70);
            treasure.setColor(COLOR("yellow")); // special important point about treasure box
            Text rulemap22(500, 500, "6) When you collect a treasure box ( that will pops out in even levels at half timecounts of that level)  : You will get one bonus star.");
            Text rulemap23(500, 550, "7) You will get one star for each next level cleared and your total score will be your final collected stars.");

            Text remember1(500, 580, "!!! REMEMBER: You should not collect extra but just exact. !!!");
            // rules or instructions ended

            Text back2(500, 603, "BACK");
            Rectangle back2r(500, 603, 300, 30);
            back2r.setColor(COLOR(119,136,153));
            for (;;)
            {
                int b = getClick();
                int x2 = b / 65536, y2 = b % 65536;
                if (x2 > 350 && x2 < 650 && y2 > 593 && y2 < 633)
                {
                    back2.hide();
                    back2r.hide();
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

// main game of arithostar
void arithostar(string your_name)
{
    //creating the user score file
    string name = your_name + "A.txt";
    fstream file(name);
    if (!file)
    {
        ofstream file(name);
        file << "00";
    }
    file.close();

    int stars = 0;
    int stepCount = 0;
    float stepTime = STEP_TIME;
    float runTime = 10; // timecounts
    float currTime = 0;
    int min = 6; // compulsory number of balls to be collected for going to next level

    Text ruleTitle(150, 600, "Press 'r' to see rules");
    
    Rectangle rem(500, 20, 1000, 25);
    rem.setColor(COLOR(150,47,240));
    rem.setFill(true);
    Text remember2(500, 20, "     !!! REMEMBER: You should not collect extra but just exact. !!!     ");

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
    sprintf(score, "Highest Score : %02d stars", highest_score);
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

    Line b1(0, PLAY_Y_HEIGHT+35, WINDOW_X + 200, PLAY_Y_HEIGHT+35);
    b1.setColor(COLOR("blue"));

    // for showing number of remaining lives
    char lives[100];
    sprintf(lives, "Lives: %d", lasso.livesShow());
    Text LIVES(900, PLAY_Y_HEIGHT + 50, lives);

    // for command pressed
    string msg("Command: _");
    Text charPressed(PLAY_X_START + 50, PLAY_Y_HEIGHT + 50, msg);

    Text start1(500, 620, "Click on the screen to start!!");
    getClick();
    start1.hide();
    for (int i = 1; i <= 21; i++)
    {
        Text targetp(890, 600, "Target : ");
        Text target(925, 600, min);
        // for showing the final score
        if (lasso.livesShow() == 0 || i == 21 || lasso.livesShow() == 99)
        {
            // add extra stars to total
            stars += lasso.extrastars();

            Turtle t;
            t.forward(-200);
            repeat(5)
            {
                t.forward(400);
                t.left(144);
            }
            t.hide();
            if (stars > highest_score)
            { // Highscore ,if made
                Text high(500, 120, "New High Score !!");
                high.imprint();
            }
            Text r1(500, 250, "Your STAR SCORE");
            Text r2(500, 270, stars);

            // storing new highscore if created
            if (stars > highest_score)
            {
                int zero_var[1] = {0};
                fstream newscore(name);
                newscore << zero_var[0];
                newscore << zero_var[0];
                newscore << stars;
            }
            wait(3);
            r1.hide();
            r2.hide();
            Text thanks(500, 250, "Thanks For Playing");
            wait(3);
            break;
        }
        // for showing the number of level reached
        char level[256];
        sprintf(level, "LEVEL: %d", i);
        Text r(500, 550, level);

        // for number of coins collected in each level
        char coinScoreStr[256];
        sprintf(coinScoreStr, "Target Collected: %d", lasso.getNumCoins());
        Text coinScore(500, 580, coinScoreStr);

        // text for welcoming to next level
        char nameoflevel[256];
        string levelname[20] = {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "Thirteenth", "Fourteenth", "Fifteenth", "Sixteenth", "Seventeenth", "Eighteenth", "Nineteenth", "Twentieth"};
        sprintf(nameoflevel, "WelCome To %s Level !!", levelname[i - 1].c_str());
        Text wlcm(500, 200, nameoflevel);

        Text start2(500, 600, "Click on the screen to start the Level !!");
        getClick();

        start2.hide();
        wlcm.hide();

        // initialising all the Objects
        Coin1 coin1(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta), coin2(coin_speed, coin_angle_deg, coin_ax + 30, coin_ay, paused, rtheta);
        Coin2 coin3(coin_speed, coin_angle_deg, coin_ax + 30, coin_ay, paused, rtheta), coin4(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
        Bomb_s bomb1(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta), bomb2(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
        Treasure_s treasure_s(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);

        if (i % 2 == 0)
        { // treasure box pops out in even levels
            treasure_s.unpause();
        }

        bool counter1 = 0, counter2 = 0;
        float time_counter = 0;
        int gift_counter = 0;

        Rectangle big1(500, 500, 400, 80);
        Rectangle big2(500, 450, 500, 20);
        Rectangle big3(500, 480, 400, 8);
        Rectangle big4(500, 500, 400, 8);
        Rectangle big5(500, 520, 400, 8);

        big1.setColor(COLOR(204,102,0));
        big2.setColor(COLOR(139,188,24));
        big3.setColor(COLOR(102,0,204));
        big4.setColor(COLOR(102,0,204));
        big5.setColor(COLOR(102,0,204));

        big1.setFill(true);
        big2.setFill(true);
        big3.setFill(true);
        big4.setFill(true);
        big5.setFill(true);

        Rectangle title(500, 640, 1000, 50);
        title.setColor(COLOR(150,47,240));
        title.setFill(true);
        Text game(500, 630, "                                                  L A S S O   A R I T H O - S T A R                                                  ");
        title.imprint();
        game.imprint();

        for (;;)
        {
            int runner1 = 0;
            if (currTime > runTime / 2)
            {
                if (!counter2)
                {
                    treasure_s.unpause();
                }
                counter2 = 1;
            }
            if (gift_counter == 1 || currTime > 8)
            {
                if (!counter1)
                {
                    counter1 = 1;
                    treasure_s.resetTreasure_s();
                }
                treasure_s.pause();
            }
            if (lasso.livesShow() == 0)
            { // if lives are exhausted
                Text t(550, 150, "GAME OVER : Your lives are exhausted.");
                wait(2);
                break;
            }
            if (lasso.getNumCoins() == min)
            { // if the target sum is achieved, then for going to next level
                stars++;
                min += 2;
                currTime = 0;
                break;
            }

            //checking if minimum number of coins collected
            if ((runTime > 0) && (currTime > runTime))
            {
                gift_counter = 1;
                currTime = 0;
                // if a level is not completed in its time, then one life is deducted
                lasso.livesDec();
                Text deduct(550, 60, "Ah! You lost one life...");
                wait(2);
            }

            // for showing the time remaining
            int time = int(runTime) - int(currTime);
            int runner2 = 0;
            char *timet;
            sprintf(timet, "Time left: %d", time);
            Text timedisplay(900, 70, timet);

            // condition for the treasure box tools
            // maxranger

            // When t is pressed, throw lasso
            // When y is pressed, yank lasso
            // When l is pressed, loop lasso
            // When [ is pressed, it decreases the throwing angle of lasso with x axis
            // When ] is pressed, it increases the throwing angle of lasso with x axis
            // When - is pressed, speed of lasso decreases
            // When = is pressed, speed of lasso increases
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
                    lasso.check_for_coin1(&coin1);
                    lasso.check_for_coin1(&coin2);
                    lasso.check_for_coin2(&coin3);
                    lasso.check_for_coin2(&coin4);

                    // checking whether the treasure box is in the range of loop
                    lasso.check_for_treasure_s(&treasure_s);

                    // checking whether the bomb is in the range of loop
                    lasso.check_for_bomb_s(&bomb1);
                    lasso.check_for_bomb_s(&bomb2);

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
                case '=':
                    if (lasso.isPaused())
                    {
                        lasso.addSpeed(RELEASE_SPEED_STEP);
                    }
                    break;
                case '-':
                    if (lasso.isPaused())
                    {
                        lasso.addSpeed(-RELEASE_SPEED_STEP);
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
                    Text rule8(500, 180, " When = is pressed, speed of lasso increases ");
                    Text rule9(500, 200, " When - is pressed, speed of lasso decreases ");
                    Text rule10(500, 220, " When s is pressed, stop the game and show final score ");
                    Text rule11(500, 240, " When q is pressed, quit the game and exit ");

                    Text gift(500, 280, "Tip: Collect the treasure box to get a bonus star.");
                    Text end(500, 360, " Press 'y' key and then click on the screen to close this page and continue. ");
                    getClick();
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
            bomb2.Paused();
            if (i % 2 == 0)
            {
                treasure_s.Paused();
            }
            // if moving object reaches y position, then resetting it again for next jump
            coin1.Reset();
            coin2.Reset();
            coin3.Reset();
            coin4.Reset();
            bomb1.Reset();
            bomb2.Reset();
            if (i % 2 == 0)
            {
                treasure_s.Reset();
            }

            sprintf(lives, "Lives: %d", lasso.livesShow());
            LIVES.setMessage(lives);

            sprintf(coinScoreStr, "Target Collected: %d", lasso.getNumCoins());
            coinScore.setMessage(coinScoreStr);

            stepCount++;
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
        treasure_s.pause();
        coin1.resetCoin1();
        coin2.resetCoin1();
        coin3.resetCoin2();
        coin4.resetCoin2();
        treasure_s.resetTreasure_s();

        bomb1.resetbomb_s();
        bomb2.resetbomb_s();

        lasso.yank();

        coin1.unpause();
        coin2.unpause();
        coin3.unpause();
        coin4.unpause();
        treasure_s.unpause();
        bomb1.unpause();
        bomb2.unpause();

        stepCount = 0;
        lasso.resetnumcoins();
        runTime += 2;
    } // End for(;;)
    wait(3);
}