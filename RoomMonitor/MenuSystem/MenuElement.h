#pragma once

#include <string>

using namespace std;

// Abstract Class
class MenuElement
{
public:
	virtual string GetName() = 0;
	virtual bool CanDrill() = 0;
};