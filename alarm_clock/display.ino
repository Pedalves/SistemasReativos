#include "display.h"

/* Define shift register pins used for seven segment display */
#define LATCH_DIO 4
#define CLK_DIO 7
#define DATA_DIO 8
 
/* Segment byte maps for numbers 0 to 9 */
static const byte SEGMENT_MAP[] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0X80,0X90};
/* Byte maps to select digit 1 to 4 */
static const byte SEGMENT_SELECT[] = {0xF1,0xF2,0xF4,0xF8};


Display::Display(int* maxValue){
	this->_maxValue = maxValue;
	this->_pos = 0;

  for(int i = 0; i < 4; i++){
    this->_currValue[i] = 0;
  }
}

void Display::show(){
  for(int i = 0; i < 4; i++){
    _writeNumberToSegment(i, this->_currValue[i]);
  }
}

void Display::nextPos(){
	this->_pos = this->_pos < 3 ? this->_pos + 1 : 0;
}

void Display::addValue(){
	this->_currValue[this->_pos] = this->_currValue[this->_pos] < this->_maxValue[this->_pos] ? this->_currValue[this->_pos] + 1 : 0;
  _writeNumberToSegment(this->_currValue[this->_pos], this->_pos);
}

Display::~Display(){}

void Display::_writeNumberToSegment(byte Segment, byte Value){
	digitalWrite(LATCH_DIO,LOW);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_MAP[Value]);
  shiftOut(DATA_DIO, CLK_DIO, MSBFIRST, SEGMENT_SELECT[Segment] );
  digitalWrite(LATCH_DIO,HIGH);
}



