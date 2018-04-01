#include "display.h"
#include "pindefs.h"
#include "app.h"

/* Define shift register pins used for seven segment display */
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8

unsigned int key1_state = 0;
unsigned int key2_state = 0;
unsigned int key3_state = 0;

static int key1_listener = 0;
static int key2_listener = 0;
static int key3_listener = 0;

static int last = 0;
unsigned int button_delay = 100;

void setup ()
{
  /* Set DIO pins to outputs */
  pinMode(LATCH_DIO,OUTPUT);
  pinMode(CLK_DIO,OUTPUT);
  pinMode(DATA_DIO,OUTPUT);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  
  pinMode(BUZZ, OUTPUT);
  
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);

  Serial.begin(9600);

  digitalWrite(BUZZ, HIGH);
  appinit(); 
}
 
/* Main program */
void loop()
{
  show();

  int curTime = millis();
  
  if(curTime - last >= button_delay)
  {
    if(key1_listener){
      int key1_curState = digitalRead(KEY1);
    
      if(key1_state != key1_curState){
        button_changed(KEY1);
      }
      
      key1_state = key1_curState;
    }
    
    if(key2_listener){
      int key2_curState = digitalRead(KEY2);
    
      if(key2_state != key2_curState){
        button_changed(KEY2);
      }
      
      key2_state = key2_curState;
    }
    
   if(key3_listener){
      int key3_curState = digitalRead(KEY3);
    
      if(key3_state != key3_curState){
        button_changed(KEY3);
      }
      
      key3_state = key3_curState;
    }
  
    last = curTime;
  }
}

void button_listen(int pin){
  switch(pin){
    case KEY1:
    key1_listener = 1;
    break;
    case KEY2:
    key2_listener = 1;
    break;
    case KEY3:
    key3_listener = 1;
    break;
    default:
    Serial.println("Invalid pin");
  }
}

