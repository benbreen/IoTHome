#include "MenuController.h"

using namespace std;

MenuController::MenuController(MenuElement *rootElement)
{
	_pRootElement = rootElement;
	_pCurrentElement = rootElement;
}

void MenuController::RegisterMenuElement(MenuElement* pElement)
{
	pElement->OnAddToController(this);
}

bool MenuController::UserBack()
{
	return NavigateBack();
}

bool MenuController::UserSelect()
{
	if (_pCurrentElement)
	{
		if (_pCurrentElement->CanSelect())
		{
			MenuElement* pNewElement = _pCurrentElement->DoNavigateSelect();
			if (pNewElement)
			{
				PushNewElement(pNewElement);
			}
			return true;
		}
	}

	return false;
}

bool MenuController::UserUp()
{
	_pCurrentElement->DoNavigateUp();
}

bool MenuController::UserDown()
{
	_pCurrentElement->DoNavigateDown();
}

void MenuController::AddRenderer(MenuRenderer* pRenderer)
{
	this->_renderers.push_back(pRenderer);
	pRenderer->SetController(this);
	pRenderer->Invalidate(NULL);
}

void MenuController::InvalidateRender(MenuElement* pElement)
{
	for (int i = 0; i < this->_renderers.size(); i++)
	{
		this->_renderers[i]->Invalidate(pElement);
	}
}


// Returns true if navigation successfull.
bool MenuController::NavigateBack()
{
	if (!_pCurrentElement->OnNavigateBack()) return false;

	if (this->_previousElements.size())
	{
		PopPrevElement();
		return true;
	}
	return false;
}

void MenuController::PushNewElement(MenuElement *currentElement)
{
	_pCurrentElement->OnActiveStateChange(ActiveStateChange::LosingFocus, ActiveStateChangeDirection::DrillingDown);
	_previousElements.push(_pCurrentElement);
	_pCurrentElement = currentElement;
	_pCurrentElement->OnActiveStateChange(ActiveStateChange::GainingFocus, ActiveStateChangeDirection::DrillingDown);
}

void MenuController::PopPrevElement()
{
	_pCurrentElement->OnActiveStateChange(ActiveStateChange::LosingFocus, ActiveStateChangeDirection::ReturningBack);
	_pCurrentElement = this->_previousElements.top();
	this->_previousElements.pop();
	_pCurrentElement->OnActiveStateChange(ActiveStateChange::GainingFocus, ActiveStateChangeDirection::ReturningBack);
}