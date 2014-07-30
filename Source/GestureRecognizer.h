#ifndef GESTURERECOGNIZER_H
#define GESTURERECOGNIZER_H

#include "UIComponent.h"
#include "Signal.h"

class GestureRecognizer
{
public:
	GestureRecognizer()
	{
		last_move.x=0;
		last_move.y=0;
	}
	void Touch(const UITouch* touch)
	{
		if ( touch->x < x || touch->x > x+w || touch->y < y || touch->y > y+h ) return;
		
		if ( touch->state == TOUCH_DOWN )
			if (TouchDown)
				TouchDown();
		
		if ( touch->state == TOUCH_UP ) 
			if (TouchUp)
				TouchUp();

		if ( touch->state == TOUCH_MOVE )
		{
			if (last_move.x!=0 && last_move.y!=0)
				if (TouchMove)
					TouchMove(touch->x-last_move.x,touch->y-last_move.y);
			last_move = *touch;
		}

	}
	std::function<void ()>					TouchDown;
	std::function<void ()>					TouchUp;
	std::function<void (int dx,int dy)>		TouchMove;
	std::function<void ()>					Zoom;
	float x;
	float y;
	float w;
	float h;
private:
	UITouch									last_move;

};

DECLARE_POINTER_OF(GestureRecognizer);

#endif