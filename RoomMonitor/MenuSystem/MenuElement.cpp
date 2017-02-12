#include "MenuElement.h"

using namespace std;


MenuElement::MenuElement()
{
}

// Should be called as a result of user actions
// e.g. pressing buttons, rotary encoder, etc.
void MenuElement::DoNavigateUp()
{
	this->_pController->NavigateBack();
}

void MenuElement::DoNavigateDown()
{
	/*To be overridden as needed */
}

MenuElement* MenuElement::DoNavigateSelect()
{

}

bool MenuElement::OnNavigateBack()
{
	return true;
}

void MenuElement::OnActiveStateChange(ActiveStateChange state, ActiveStateChangeDirection direction)
{
} 

MenuController* MenuElement::GetController()
{
	return _pController;
}

void MenuElement::InvalidateRender()
{
	this->GetController()->InvalidateRender(this);
}

void MenuElement::OnAddToController(MenuController *pController)
{
	_pController = pController;
}

