#pragma once

#include "MenuElement.h"

#include <vector>
#include <string>

using namespace std;

class MenuListElement : MenuElement
{
public:
	MenuListElement (string listName)
	{
		_Name = listName;
	}

	void AddChild (MenuElement *element)
	{
		//_Children.
	}

	string GetName() override
	{
		return _Name;
	}

private:
	string _Name;
	vector<MenuElement> _Children;
};