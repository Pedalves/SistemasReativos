#include "event_driven.h"
#include "app.h"
#include "pindefs.h"


void appinit(void){
  button_listen(KEY1);
  timer_set(5000);
}

void button_changed(int p, int v){
  if(v){
    digitalWrite(LED_PIN, LOW);
  }
  else{
    digitalWrite(LED_PIN, HIGH);
  }
  
  Serial.println(v);
}

void timer_expired(void){
  digitalWrite(LED_PIN, HIGH);
  while(1);
}

