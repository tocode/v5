#ifndef UIROOT_H
#define UIROOT_H

#include "UIComponent.h"
#include "UIContainer.h"

class UIRoot: public UIContainer
{
public:
	UIRoot():UIContainer(NULL) {}
	int AbsoluteX()
	{
		return 0;
	}
	int AbsoluteY()
	{
		return 0;
	}
};




#endif