#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"
#include "images/endscreen.h"
#include "images/startscreen.h"
#include "images/garbage.h"
#include "images/car.h"
#include "images/checkflag.h"
/* TODO: */
// Include any header files for title screen or exit
// screen images generated by nin10kit. Example for the provided garbage
// image:
// #include "images/garbage.h"

/* TODO: */
// Add any additional states you need for your app. You are not requried to use
// these specific provided states.
enum gba_state {
  START,
  PLAY,
  WIN,
  LOSE,
};

int main(void) {
  /* TODO: */
  // Manipulate REG_DISPCNT here to set Mode 3. //

  REG_DISPCNT = MODE3 | BG2_ENABLE;

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  // Load initial application state
  enum gba_state state = START;
  struct objectPosition racer = {HEIGHT - CAR_HEIGHT, (WIDTH / 2)};
  struct objectPosition flag = {0,0};

  //add array to hold score?
  int timeCount = 0;

  char timeArr[20];
  

  //initialize place to store timer and array in memory to store text

  drawFullScreenImageDMA(startscreen);
  
  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons

    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw





    waitForVBlank();
    switch (state) {
      case START:

        //load start full screen image
        //check for start button press, if so, reset vblank counter and change to play state
        if (KEY_JUST_PRESSED(BUTTON_START, currentButtons, previousButtons))
        {
          fillScreenDMA(BLACK);
          vBlankCounter = 0;
          state = PLAY;
        }
        
        // state = ?
        break;
      case PLAY:

        //snprintf ?? print score at top, do drawString?

        //timeCount = vBlankCounter / 60; 

        //undraw checkered flag image
        //undrawImageDMA(flag.row, flag.column, CHECKFLAG_WIDTH, CHECKFLAG_HEIGHT, checkflag);
        //undraw racer image
        //undrawImageDMA(racer.row, racer.column, CAR_WIDTH, CAR_HEIGHT, car);
        drawRectDMA(racer.row, racer.column, CAR_WIDTH, CAR_HEIGHT, BLACK);

        //cover old count
        drawRectDMA(140, 0, 120, 8, BLACK);
        //
        
      

        
        //move up
        if(KEY_DOWN(BUTTON_UP, currentButtons)) {
          if (racer.row > 0)
          {
            racer.row -= 1;
          }
          
        }

        //move down

        if(KEY_DOWN(BUTTON_DOWN, currentButtons)) {
          if (racer.row < 160 - CAR_HEIGHT)
          {
            racer.row += 1;
          }
          
        }

        //move right
        if(KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
          if (racer.column < WIDTH - CAR_WIDTH)
          {
            racer.column += 1;
          }
          
        }

        //move left
        if(KEY_DOWN(BUTTON_LEFT, currentButtons)) {
          if (racer.column > 0)
          {
            racer.column -= 1;
          }
          
        }

        timeCount = vBlankCounter / 60;
        snprintf(timeArr, 20, "Score - %d", timeCount);
        drawString(140, 0, timeArr, WHITE);

        //draw flag image
        drawImageDMA(flag.row, flag.column, CHECKFLAG_WIDTH, CHECKFLAG_HEIGHT, checkflag);
        //draw racer image
        drawImageDMA(racer.row, racer.column, CAR_WIDTH, CAR_HEIGHT, car);


        //check if won
        if (racer.row == flag.row + CHECKFLAG_HEIGHT)
        {
          drawFullScreenImageDMA(endscreen);
          state = WIN;
        }

        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons))
        {
          drawFullScreenImageDMA(startscreen);
          state = START;
          vBlankCounter = 0;
          racer.row = HEIGHT - CAR_HEIGHT;
          racer.column = (WIDTH / 2);

        }
        
        


        
        
        
        // state = ?
        break;
      case WIN:

        snprintf(timeArr, 20, "Score - %d", timeCount);
        drawString(140, 0, timeArr, WHITE);

        

        //add score printout based off timer value

        //add conditional for start screen select button pressed
        if (KEY_JUST_PRESSED(BUTTON_SELECT, currentButtons, previousButtons))
        {
          drawFullScreenImageDMA(startscreen);
          state = START;
          vBlankCounter = 0;
          racer.row = HEIGHT - CAR_HEIGHT;
          racer.column =(WIDTH / 2);

        }
        

        // state = ?
        break;
      case LOSE:

        // state = ?
        break;
    }

    previousButtons = currentButtons; // Store the current state of the buttons
  }

  UNUSED(previousButtons); // You can remove this once previousButtons is used

  return 0;
}
