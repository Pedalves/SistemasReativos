#include "event_driven.h"
#include "app.h"
#include "pindefs.h"

unsigned int key1_state = 1;
unsigned int key2_state = 1;
unsigned int key3_state = 1;
unsigned int last = 0;
unsigned int button_delay = 300;

static int key1_listener = 0;
static int key2_listener = 0;
static int key3_listener = 0;
static int led_listener = 0;

static float timerTime = -1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);

  Serial.begin(9600);
  
  appinit();
}

void loop() {
  // put your main code here, to run repeatedly:
  int curTime = millis();

  //Checar led
  if(led_listener){
    led_action(digitalRead(LED_PIN));
  }
  
  //Loop de checar botao
  if(curTime - last >= button_delay)
  {
    if(key1_listener){
      int key1_curState = digitalRead(KEY1);
    
      if(key1_state != key1_curState){
        button_changed(KEY1, key1_curState);
      }
      
      key1_state = key1_curState;
    }
    
    if(key2_listener){
      int key2_curState = digitalRead(KEY2);
    
      if(key2_state != key2_curState){
        button_changed(KEY2, key2_curState);
      }
      
      key2_state = key2_curState;
    }
    
   if(key3_listener){
      int key3_curState = digitalRead(KEY3);
    
      if(key3_state != key3_curState){
        button_changed(KEY3, key3_curState);
      }
      
      key3_state = key3_curState;
    }
  
    last = curTime;
  }
  
  //Checar timer
  if(curTime == timerTime){
    timer_expired();
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

void timer_set(int ms){
  timerTime = ms;
}

void led_listen(){
  led_listener = 1;
}
