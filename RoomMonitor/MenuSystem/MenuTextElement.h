#pragma once

#include <string>

using namespace std;

class MenuTextElement : MenuElement
{
public:
	MenuTextElement(string name, string subText = "")
	{

	}

	string GetName() override
	{

	}

private:
	string _name;
	string _subText;
};