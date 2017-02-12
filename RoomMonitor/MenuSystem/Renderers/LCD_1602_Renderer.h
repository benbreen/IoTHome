// Renderer for 1602 LCD

#pragma once

#include <LiquidCrystal.h>

#include "../MenuSystem.h"

class LCD_1602_Renderer : public MenuRenderer
{
public:
	LCD_1602_Renderer(LiquidCrystal* pLCD, unsigned short nCols, unsigned short nRows)
	{
		_pLCD = pLCD;
		_nRows = nRows;
		_nCols = nCols;
	}

	void Invalidate(MenuElement* pElement) override
	{
		string type = pElement->GetType();
		if (type == "LIST")
		{
			MenuListElement* pList = static_cast<MenuListElement*>(pElement);
		}
	}

private:
	LiquidCrystal* _pLCD;
	unsigned short _nRows;
	unsigned short _nCols;

	void RenderListElement(MenuListElement* listElement)
	{

	}
};