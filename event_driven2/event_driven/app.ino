#include "event_driven.h"
#include "app.h"
#include "pindefs.h"

int buttonOnePressed = 10000;
int buttonTwoPressed = 20000;

float led_delay = 1000;
float last_led_time = 0;

void appinit(void){
  button_listen(KEY1);
  button_listen(KEY2);
  led_listen();
}

void button_changed(int p, int v){
  if (abs(buttonOnePressed - buttonTwoPressed) < 100)
  {
    digitalWrite(LED_PIN, HIGH);
    while(1);
  }
  
  switch(p){
    case KEY1:
    led_delay = led_delay/2;
    buttonOnePressed = millis();
    break;
    case KEY2:
    led_delay = led_delay*2;
    buttonTwoPressed = millis();
    break;
    case KEY3:
    break;
  }
}

void timer_expired(void){
  digitalWrite(LED_PIN, HIGH);
  while(1);
}

void change_speed(float multiplier){
  led_delay /= multiplier;
}

void led_action(int state){
  int curTime = millis();
  if(curTime - last_led_time >= led_delay)
  {
    digitalWrite(LED_PIN, !state); 
    last_led_time = curTime;
  }
}

