#pragma once

#include "MenuElement.h"

class MenuController
{
public:
	MenuController(MenuElement *rootElement)
	{
		_pRootElement = rootElement;
		_pCurrentElement = rootElement;
	}

	bool UserBack()
	{

	}

	bool UserSelect()
	{

	}

	bool UserUp()
	{

	}

	bool UserDown()
	{

	}

	void SetCurrentElement(MenuElement *currentElement)
	{
		_pCurrentElement = currentElement;
	}

private:
	MenuElement* _pRootElement;
	MenuElement* _pCurrentElement;
};