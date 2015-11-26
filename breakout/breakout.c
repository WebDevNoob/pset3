// breakout.c
// Computer Science 50
// Problem Set 3

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400
// Paddle Height and Width
#define pHeight 10
#define pWidth 80
// number of rows of bricks
#define ROWS 5
// number of columns of bricks
#define COLS 10
// radius of ball in pixels
#define RADIUS 10
// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void){
    // seed pseudorandom number generator
    srand48(time(NULL));
    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);
    // instantiate bricks
    initBricks(window);
    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);
    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);
    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);
    // number of bricks initially
    int bricks = COLS * ROWS;
    // number of lives initially
    int lives = LIVES;
    // number of points initially
    int points = 0;
    double bRotate = drand48();
    double bSpeedY = 2;
    // keep playing until game over
    waitForClick();
    while (lives > 0 && bricks > 0){
        GEvent mMove = getNextEvent(MOUSE_EVENT);
            if(mMove != NULL){
                if(getEventType(mMove) == MOUSE_MOVED){
                    double x = getX(mMove) - getWidth(paddle) / 2;
                    int y = HEIGHT - (pHeight * 5);
                    setLocation(paddle,x,y); 
                }
            }
        move(ball, bRotate, bSpeedY);
            if(getX(ball) + getWidth(ball) >= getWidth(window)){
                bRotate = -bRotate; 
            }else
            if(getY(ball) <= 0){
                bSpeedY = -bSpeedY;
            }else
            if(getX(ball) <= 0){
                bRotate = -bRotate;
            }else
            if(getY(ball) + getHeight(ball) >= getHeight(window)){
                lives = lives - 1;
                waitForClick();
                setLocation(ball, 190, 290);
                setLocation(paddle, 150, 500);
            }
        GObject object = detectCollision(window, ball);
        if(object == paddle){
            bSpeedY = -bSpeedY; 
        }
        if(object != NULL){
            if(strcmp(getType(object), "GRect") == 0 && object != paddle && object != label){
                removeGWindow(window, object);
                bSpeedY = -bSpeedY;
                points = points + 1;
                updateScoreboard(window, label, points);
                if(points >= (COLS * ROWS)){
                    return 0;
                }
            }
        }
    pause(10); 
    }
    // wait for click before exiting
    waitForClick();
    // game over
    closeGWindow(window);
    return 0;
}
/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window){
    int y = 5;
    int x = 1;
    for(int j = 0; j < COLS; j++){
        for(int i = 0; i < ROWS; i++){
            y = y + 20;
            GRect brick = newGRect(x, y, 36, 10);
            add (window, brick);
            switch(i){
                case 0:
                    setColor(brick, "RED");
                    setFilled(brick, true);
                    break;
                case 1:
                    setColor(brick, "ORANGE");
                    setFilled(brick, true);
                    break;
                case 2:
                    setColor(brick, "GREEN");
                    setFilled(brick, true);
                    break;
                case 3:
                    setColor(brick, "BLUE");
                    setFilled(brick, true);
                    break;
                case 4:
                    setColor(brick, "#1ce1ce");
                    setFilled(brick, true);
                    break;
            }
        }
    x = x + 40;
    y = 5;
    }      
}
/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window){
    GOval ball = newGOval (190, 290, 20, 20);
    add(window, ball);
    setColor(ball, "BLACK");
    setFilled(ball, true);
    return ball;
}
/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect (((WIDTH / 2)-(pWidth / 2)),(HEIGHT - (pHeight * 5)),pWidth, pHeight);
    add(window, paddle);
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    return paddle;
}
/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window){
    GLabel label = newGLabel(" ");
    add(window, label);
    setLocation(label, 100, 100);
    setFont(label, "Arial-12");
    return label;
}
/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);
    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}
/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);
    // for checking for collisions
    GObject object;
    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }
    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }
    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }
    // no collision
    return NULL;
}
