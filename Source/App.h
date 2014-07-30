#ifndef APP_H
#define APP_H

class UITouch;

class App
{
public:
	virtual void Initialize() = 0;
	virtual void Display() = 0;
	virtual void KeyDown(int key) {}
	virtual void MoveTo(int x,int y) {}
	virtual void Touch(UITouch* touch){}
	virtual void Cleanup() {}
};






#endif