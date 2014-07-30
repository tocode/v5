#ifndef VLAYOUT_H
#define VLAYOUT_H

#include "UILayout.h"
#include "UIContainer.h"

class VLayout: public UILayout
{
public:
	void LayoutContainer(UIContainerPtr container)
	{
		float height_sum = 0;
		for (int i=0; i<container->components.size(); i++)
			height_sum += container->components[i]->height;
		float space = (container->height-height_sum)/(container->components.size()+1);
		if (space<0) space=0;

		float pos=space;
		for (int i=0; i<container->components.size(); i++)
		{
			container->components[i]->y = pos;
			pos+=container->components[i]->height;
			pos+=space;
		}
	}

};

DECLARE_POINTER_OF(VLayout);

#endif