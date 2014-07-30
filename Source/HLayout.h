#ifndef HLAYOUT_H
#define HLAYOUT_H

#include "UILayout.h"
#include "UIContainer.h"

class HLayout: public UILayout
{
public:
	void LayoutContainer(UIContainerPtr container)
	{
		float width_sum = 0;
		for (int i=0; i<container->components.size(); i++)
			width_sum += container->components[i]->width;
		float space = (container->width-width_sum)/(container->components.size()+1);
		if (space<0) space=0;

		float pos=space;
		for (int i=0; i<container->components.size(); i++)
		{
			container->components[i]->x = pos;
			pos+=container->components[i]->width;
			pos+=space;
		}
	}
public:
	float left_space;
};

DECLARE_POINTER_OF(HLayout);

#endif