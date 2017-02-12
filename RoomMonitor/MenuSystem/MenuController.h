#pragma once

#include <stack>
#include <vector>

#include "MenuElement.h"
#include "MenuRenderer.h"

using namespace std;

class MenuElement;

class MenuController
{
public:
	MenuController(MenuElement *rootElement);

	void RegisterMenuElement(MenuElement* pElement);

	bool UserBack();

	bool UserSelect();

	bool UserUp();
	bool UserDown();

	// Returns true if navigation successfull.
	bool NavigateBack();

	void AddRenderer(MenuRenderer* pRenderer);
	void InvalidateRender(MenuElement* pElement);

private:
	MenuElement* _pRootElement;
	MenuElement* _pCurrentElement;
	stack<MenuElement*> _previousElements;
	vector<MenuRenderer*> _renderers;

	void PushNewElement(MenuElement *currentElement);
	void PopPrevElement();
};