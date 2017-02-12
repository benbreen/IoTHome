#pragma once

#include "MenuElement.h"

class MenuElement;
class MenuController;

class MenuRenderer
{
	friend class MenuController;
public:
	MenuRenderer() {}

	virtual void Invalidate(MenuElement* pElement)
	{
		_isValid = false;
	}
protected:
	bool _isValid = false;
	MenuController *_pController;

private:
	void SetController(MenuController* pController)
	{
		_pController = pController;
	}
};