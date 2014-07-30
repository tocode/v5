#include "UIComponent.h"
#include "UIContainer.h"

int UIComponent::AbsoluteX()
{
	return Father()->AbsoluteX()+x;
}
int UIComponent::AbsoluteY()
{
	return Father()->AbsoluteY()+y;
}
UIContainerPtr UIComponent::Father()
{
	if (IS_AVAILABLE_WEAK_POINTER(father))
		return UIContainerPtr(father);
	else
		return UIROOT;
}