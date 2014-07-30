#ifndef UICOMPONENT_H
#define UICOMPONENT_H

#include "Common.h"

enum UITouchState
{
	TOUCH_DOWN,
	TOUCH_MOVE,
	TOUCH_UP,
	TOUCH_CANCEL
};
struct UITouch
{
	UITouchState		state;
	float				x;
	float				y;
};


#include "Canvas.h"

class UIContainer;
DECLARE_POINTER_OF(UIContainer);
DECLARE_WEAK_POINTER_OF(UIContainer);

extern const UIContainerPtr UIROOT;

class UIComponent
{
public:
	UIComponent(UIContainerPtr father=UIROOT)
	{
		this->father = father;
		x=0;
		y=0;
		width=0;
		height=0;
	}
	virtual void Render(CanvasPtr can) = 0;
	virtual void Touch(const UITouch* touch){}
	virtual int AbsoluteX();
	virtual int AbsoluteY();
	virtual UIContainerPtr Father();
public:
	UIContainerWeakPtr				father;
	int								x;
	int								y;
	int								width;
	int								height;
};

DECLARE_POINTER_OF(UIComponent);





#endif