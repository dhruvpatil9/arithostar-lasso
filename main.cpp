#include <cstdio>
#include <cstdlib>
#include <simplecpp>
#include <string>
#include <fstream>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"
#include "arithostar.h"
#include "ballsket.h"

main_program
{
    // for displaying the name of player and creating a separate file for that name
    string your_name, name;
    cout << "Enter Your Name" << endl;
    cin >> your_name;

    initCanvas("Lasso", WINDOW_X + 200, WINDOW_Y + 50);
    int play_number = 0;

    // HOME PAGE consisting of instructions and play button
    for (;;)
    {
        if (play_number == 1 || play_number == 2)
        {
            break;
        }
        Rectangle play1r(500, 250, 300, 40);
        Rectangle play2r(500, 350, 300, 40);
        play1r.setColor(COLOR(255,215,0));
        play2r.setColor(COLOR(255,215,0));
        Text welcome(500, 150, "WELCOME HOME : Click on the buttons to proceed!");
        Text play1(500, 250, " LASSO BALLSKET ");
        Text play2(500, 350, " LASSO ARITHO-STAR ");

        int w = getClick();
        int x1 = w / 65536, y1 = w % 65536;

        if (x1 > 350 && x1 < 650 && y1 > 230 && y1 < 270)
        {
            Rectangle rec(500,325,1000,650);
            rec.setColor(COLOR("white"));
            rec.setFill(true);
            play_number = interface1();
        }

        else if (x1 > 350 && x1 < 650 && y1 > 330 && y1 < 370)
        {
            Rectangle rec(500,325,1000,650);
            rec.setColor(COLOR("white"));
            rec.setFill(true);
            play_number = interface2();
        }
    }

    if (play_number == 1)
    { // Starting the LASSO BALLSKET game  -(BALLSKET- Basket of balls (& bombs) )
        ballsket(your_name);
    }
    else if (play_number == 2)
    { // Starting the LASSO ARITHOSTAR game  -(ARITHO-mathematically + STAR-collecting stars)
        arithostar(your_name);
    }
    return 0;
} // End main_program
