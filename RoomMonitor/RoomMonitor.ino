#pragma once

#include <LiquidCrystal.h>
#include <StandardCplusplus.h>
#include <utility.h>

#include "Util/trace.h"
#include "MenuSystem/MenuSystem.h"
#include "MenuSystem/Renderers/LCD_1602_Renderer.h"


void SetupLCD()
{

}

MenuController* pMenuController;

void SetupMenu(LiquidCrystal* pLcd)
{
	MenuListElement* pRootList = new MenuListElement("Root List");
	pMenuController = new MenuController(pRootList);
	
	LCD_1602_Renderer* lcd = new LCD_1602_Renderer(pLcd, 16, 2);
	pMenuController->AddRenderer(lcd);
}

void setup()
{
	SetupLCD();
	SetupMenu();
}

void loop()
{

}