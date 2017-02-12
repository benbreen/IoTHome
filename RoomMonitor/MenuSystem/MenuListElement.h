#pragma once

#include "MenuElement.h"

#include <vector>
#include <string>

using namespace std;

class MenuListElement : public MenuElement
{
public:
	MenuListElement (string listName)
	{
		_name = listName;
		_highlightedItem = -1;
		_continuousLoop = false;
	}

	void AddChild (MenuElement *element)
	{
		_children.push_back(element);
		if (_highlightedItem == -1) SetHighlightedItem(0);
	}

	string GetName() override
	{
		return _name;
	}

	string GetType() override
	{
		return "LIST";
	}

	size_t Length()
	{
		return _children.size();
	}

	bool CanSelect() override
	{
		if (Length() && this->_highlightedItem >=0) return true;
		else return false;
	}

	void ContinuousLoop(bool isContinuous)
	{
		_continuousLoop = isContinuous;
	}

	// Handle user input
	void DoNavigateUp() override
	{
		if (_children.empty()) return;
		else if (_highlightedItem == -1) SetHighlightedItem(0);
		else if (_highlightedItem == 0)
		{
			if (_continuousLoop) SetHighlightedItem(_children.size() - 1);
			else { /* do nothing*/ }
		}
		else SetHighlightedItem(_highlightedItem - 1);
	}

	void DoNavigateDown() override
	{
		if (_children.empty()) return;
		else if (_highlightedItem == -1) SetHighlightedItem(0);
		else if (_highlightedItem == _children.size() -1)
		{
			if (_continuousLoop) SetHighlightedItem(0);
			else { /* do nothing*/ }
		}
		else SetHighlightedItem(_highlightedItem + 1);
	}

	MenuElement* DoNavigateSelect() override
	{
		if (_highlightedItem >= 0) return _children[_highlightedItem];
		else return NULL;
	}

	void SetHighlightedItem(int item)
	{
		_highlightedItem = item;
	}

	void OnActiveStateChange(ActiveStateChange state, ActiveStateChangeDirection direction)
	{
		// If we are drilling into the menu, reset highlight to default
		if (state == ActiveStateChange::GainingFocus && direction == ActiveStateChangeDirection::DrillingDown)
		{
			if (!_children.empty()) SetHighlightedItem(0);
			else SetHighlightedItem(-1);
		}
	}

private:
	string _name;
	vector<MenuElement*> _children; // All menu items
	int _highlightedItem; // The currently highlighted menu item (-1 if nothing highlighted)
	bool _continuousLoop; // True if scrolling past the bottom of the menu jumps back to first item and vice versa
};