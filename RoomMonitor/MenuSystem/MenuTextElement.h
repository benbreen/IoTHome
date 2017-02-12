#pragma once

#include <string>

using namespace std;

class MenuTextElement : MenuElement
{
public:
	MenuTextElement(string name, string subText = "")
	{
		_name = name;
		_subText = subText;
	}

	string GetName() override
	{
		return _name;
	}

	string GetSubText()
	{
		return _subText;
	}

private:
	string _name;
	string _subText;
};