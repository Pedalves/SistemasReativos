#include "alarm_clock.h"
#include "app.h"
#include "pindefs.h"
#include "display.h"

static int hour[]={2,9,5,9};
static int turn_on[]={1,0,0,0};

static int last_show = 0;
static int last_pressed = 0;
static Display* display_clock;
static Display* display_set;
static Display* display_alarm;
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
  int curr = millis();
  
  if(abs(curr - last_show) >= 20)
  {
    for(int i = 3; i >= 0; i--)
    {
      display_clock->setPos(i);
      display_clock->addValue();
      
      if(display_clock->getValue(i))
      {
        break;
      }
      if(i==0)
      {
        i=3;
      }
    }

    if(display_turn->getValue(0))
    {
      bool time_to_wake = true;
  
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

  if(display_turn->getValue(0))
  {
    digitalWrite(LED1, LOW);
  }
  else
  {
    digitalWrite(LED1, HIGH);
  }
  
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
  int curr = millis();
  
  if(abs(curr - last_pressed) >= 300)
  {
    digitalWrite(BUZZ, HIGH);
    switch(p){
      case KEY1:   
        if(mode)
          curr_display->addValue();
        break;
       case KEY2:
        if(mode)
        {
          if(mode == 1)
          {
            if(curr_display->getPos() == 3)
            {
              for(int i = 0; i < 4; i++){
                display_clock->setValue(display_set->getValue(i), i);
              }
            }
          }
          curr_display->nextPos();
        }
        break;
      case KEY3:  
        mode = mode < 4 ? mode + 1 : 0;
        break;
    }

    last_pressed = curr;
  }
}

