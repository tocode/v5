#ifndef UICONTAINER_H
#define UICONTAINER_H

#include "UILayout.h"
#include "UIComponent.h"
#include <algorithm>

extern const UIContainerPtr UIROOT;


class UIContainer: public UIComponent, ENABLE_THIS_OF(UIContainer)
{
public:
	DECLARE_POINTER_OF(UIContainer);
	UIContainer(UIContainerPtr father=UIROOT):UIComponent(father),layout(NULL){}
	void Render(CanvasPtr can)
	{
		if (layout)
			layout->LayoutContainer(THIS);
		for (int i=0; i<components.size(); i++)
			components[i]->Render(can);
	}
	void Touch(const UITouch* touch)
	{
		if (layout)
			layout->LayoutContainer(THIS);
		for (int i=0; i<components.size(); i++)
			components[i]->Touch(touch);
	}
	void Attach(UIComponentPtr component)
	{
		component->father = THIS;
		components.push_back(component);
	}
	void Detach(UIComponentPtr component)
	{
		component->father = UIROOT;
		components.erase(std::remove(components.begin(),components.end(),component),components.end());
	}
	void SetLayout(UILayoutPtr layout)
	{
		this->layout = layout;
	}
	friend class UILayout;
public:
	vector<UIComponentPtr>			components;
	UILayoutPtr						layout;
};

DECLARE_POINTER_OF(UIContainer);
DECLARE_WEAK_POINTER_OF(UIContainer);

#endif