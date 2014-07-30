#ifndef UILAYOUT_H
#define UILAYOUT_H

class UILayout
{
public:
	virtual void LayoutContainer(UIContainerPtr container)=0;
};

DECLARE_POINTER_OF(UILayout);



#endif