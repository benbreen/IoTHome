#pragma once

#include <string>

#include "MenuController.h"

using namespace std;

enum ActiveStateChange
{
	GainingFocus,
	LosingFocus
};

enum ActiveStateChangeDirection
{
	DrillingDown,
	ReturningBack
};

class MenuController;
class MenuRenderer;

// Abstract Class
class MenuElement
{
	friend class MenuController;
public:
	MenuElement();

	virtual string GetName() = 0;
	virtual bool CanSelect() = 0;
	virtual string GetType() = 0;

	// Should be called as a result of user actions
	// e.g. pressing buttons, rotary encoder, etc.
	virtual void DoNavigateUp();

	virtual void DoNavigateDown();

	virtual MenuElement* DoNavigateSelect(); // Return item to drill into or NULL for no drill
	virtual bool OnNavigateBack(); // Return false to block navigating backward

	virtual void OnActiveStateChange(ActiveStateChange state, ActiveStateChangeDirection direction); // Called when the element becomes active

protected:
	MenuController* GetController();
	virtual void InvalidateRender();

private:
	MenuController* _pController;
	void OnAddToController(MenuController *pController);
};
