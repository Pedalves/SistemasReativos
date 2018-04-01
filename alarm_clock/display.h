#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>

class Display {
public:
	Display(int* maxValue);
	~Display();
 
  void show();

  void setPos(int pos);
	void nextPos();
  int getPos();
 
  void addValue();
  void setValue(int value, int pos);
  int getValue(int pos);
  
private:
	void _writeNumberToSegment(byte Segment, byte Value);

	int* _maxValue;
	int _currValue[4];
	
	int _pos;
};

#endif // DISPLAY_H
