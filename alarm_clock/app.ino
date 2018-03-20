#include "alarm_clock.h"
#include "app.h"
#include "pindefs.h"


void appinit(void){
  button_listen(KEY1);
  timer_set(5000);
}

void button_changed(int p, int v){
  if(v){
    digitalWrite(LED1, LOW);
  }
  else{
    digitalWrite(LED1, HIGH);
  }
  
  Serial.println(v);
}

void timer_expired(void){
  digitalWrite(LED1, HIGH);
  while(1);
}

