#include "alarm_clock.h"
#include "app.h"
#include "pindefs.h"
#include "display.h"

static int hour[]={2,9,5,9};
static int turn_on[]={1,0,0,0};

static unsigned int last_show = 0;
static unsigned int last_pressed = 0;

// Current time
static Display* display_clock;
// Set time
static Display* display_set;
// Set alarm time
static Display* display_alarm;
// Turn on alarm
static Display* display_turn;

static Display* curr_display;

int mode = 0;

void appinit(void){
  button_listen(KEY1);
  button_listen(KEY2);
  button_listen(KEY3);

  
  display_clock = new Display(hour);
  display_set = new Display(hour);
  display_alarm = new Display(hour);
  display_turn = new Display(turn_on);

  curr_display = display_clock;
}

void show(){
  unsigned int curr = millis();

  // update the current time on the clock, if alarm mode is on trigger the buzz if the time to wake has come
  Serial.println(curr - last_show);
  if(curr - last_show >= 60000)
  {
    for(int i = 3; i >= 0; i--)
    {
      display_clock->setPos(i);
      display_clock->addValue();
      
      if(display_clock->getValue(i))
      {
        break;
      }
    }

    // if alarm's on
    if(display_turn->getValue(0))
    {
      bool time_to_wake = true;

      // check if current time is the same as the alarm time
      for(int i = 0; i < 4; i++){
        if(display_clock->getValue(i) != display_alarm->getValue(i))
          time_to_wake = false;
      }

      if(time_to_wake)
      {
        digitalWrite(BUZZ, LOW);
      }
    }    
    
    last_show = millis();
  }

  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);

  // If alarm mode is on the led remains on
  if(display_turn->getValue(0))
  {
    digitalWrite(LED1, LOW);
  }
  else
  {
    digitalWrite(LED1, HIGH);
  }

  // switch the display to show the one that matches if the mode
  switch(mode)
  {
    case 0:
      curr_display = display_clock;
      digitalWrite(LED4, LOW);
      break;
    case 1:
      digitalWrite(LED3, LOW);
      curr_display = display_set;
      break;
    case 3:
      digitalWrite(LED2, LOW);
      curr_display = display_alarm; 
      break;
    case 4:
      digitalWrite(LED1, LOW);
      curr_display = display_turn; 
      break;
    default:
      break;
  }

  curr_display->show();
}

void button_changed(int p){
  unsigned int curr = millis();
  
  if(abs(curr - last_pressed) >= 300)
  {
    switch(p){
      case KEY1: 
        // Add 1 to the current position on the display. if mode 0 turn off the buzz  
        if(mode)
          curr_display->addValue();
        else
          digitalWrite(BUZZ, HIGH);
        break;
       case KEY2:
        // Change de current position on display
        if(mode)
        {
          if(mode == 1)
          {
            // You need to pass through all positions so set the new hour as the current time. If mode 0 trigger the snooze mode
            if(curr_display->getPos() == 3)
            {
              for(int i = 0; i < 4; i++){
                display_clock->setValue(display_set->getValue(i), i);
              }
            }
          }
          curr_display->nextPos();
        }
        else
        {
          // Snooze mode
          if(!digitalRead(BUZZ))
          {
            digitalWrite(BUZZ, HIGH);

            // check if 10 more minutes makes the hour be added by 1
            for(int i = 2; i >= 0; i--)
            {
              display_alarm->setPos(i);
              display_alarm->addValue();
              
              if(display_alarm->getValue(i))
              {
                break;
              }
            }
          }
        }
        break;
      case KEY3:
        // change mode  
        mode = mode < 4 ? mode + 1 : 0;
        break;
    }

    last_pressed = curr;
  }
}

