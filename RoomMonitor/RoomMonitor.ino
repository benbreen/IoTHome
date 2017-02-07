// 
//   FILE:  dht11_test1.pde
// PURPOSE: DHT11 library test sketch for Arduino
//

#include <utility.h>
#include <unwind-cxx.h>
#include <system_configuration.h>
#include <StandardCplusplus.h>
#include "MenuSystem/MenuListElement.h"

void trace(const char * format, ...)
{
	char out_string[64];
	va_list args;
	va_start(args, format);
	vsprintf(out_string, format, args);
	va_end(args);
	Serial.println(out_string);
}

//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
	return 1.8 * celsius + 32;
}

// fast integer version with rounding
//int Celcius2Fahrenheit(int celcius)
//{
//  return (celsius * 18 + 5)/10 + 32;
//}


//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
	return celsius + 273.15;
}

// dewPoint function NOAA
// reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
// reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double dewPoint(double celsius, double humidity)
{
	// (1) Saturation Vapor Pressure = ESGG(T)
	double RATIO = 373.15 / (273.15 + celsius);
	double RHS = -7.90298 * (RATIO - 1);
	RHS += 5.02808 * log10(RATIO);
	RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / RATIO))) - 1);
	RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1);
	RHS += log10(1013.246);

	// factor -3 is to adjust units - Vapor Pressure SVP * humidity
	double VP = pow(10, RHS - 3) * humidity;

	// (2) DEWPOINT = F(Vapor Pressure)
	double T = log(VP / 0.61078);   // temp var
	return (241.88 * T) / (17.558 - T);
}

// delta max = 0.6544 wrt dewPoint()
// 6.9 x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity)
{
	double a = 17.271;
	double b = 237.7;
	double temp = (a * celsius) / (b + celsius) + log(humidity*0.01);
	double Td = (b * temp) / (a - temp);
	return Td;
}

/* Setup DHT11 --------------------------------- */
#include "dht11.h"

dht11 DHT11;

#define DHT11PIN 7

void setup_temp()
{

	trace("DHT11 TEST PROGRAM ");
	trace("LIBRARY VERSION: ");
	trace(DHT11LIB_VERSION);
}


/* Setup 1602 LCD ------------------- */
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 10, 9);

void setup_lcd()
{
	// set up the LCD's number of columns and rows:
	lcd.begin(16, 2);
	// Print a message to the LCD.
	lcd.print("zzzzz");
}

void print_lcd(int line_no, char * ostring)
{
	lcd.setCursor(0, line_no);
	bool end = false;
	for (int i = 0; i < 16; i++)
	{
		if (!end)
		{
			if (ostring[i] == '\0')
			{
				end = true;
				ostring[i] = ' ';
			}
		}
		else
		{
			ostring[i] = ' ';
		}
	}
	ostring[16] = '\0';
	lcd.print(ostring);
	trace("LCD Print (Line: %d): %s", line_no, ostring);
}

#include <stdio.h>
#include <stdarg.h>

void printf_lcd(int row, const char* format, ...)
{
	char out_string[32];
	va_list args;
	va_start(args, format);
	vsprintf(out_string, format, args);
	va_end(args);
	print_lcd(row, out_string);
}

/* Setup Encoder ------------------*/

#define encoder0PinA  2
#define encoder0PinB  3

volatile unsigned int encoder0Pos = 0;
volatile unsigned long lastMovement = 0L;

void setup_encoder() {
	pinMode(encoder0PinA, INPUT);
	digitalWrite(encoder0PinA, HIGH);       // turn on pull-up resistor
	pinMode(encoder0PinB, INPUT);
	digitalWrite(encoder0PinB, HIGH);       // turn on pull-up resistor

	attachInterrupt(0, doEncoderA, CHANGE);
	attachInterrupt(1, doEncoderB, CHANGE);
}

#define JUMP_THRES 100L
bool CheckJump()
{
	unsigned long time = millis();
	if (time <= lastMovement)
	{
		lastMovement = time;
		return false;
	}
	if (time - lastMovement > JUMP_THRES)
	{
		lastMovement = time;
		return false;
	}
	lastMovement = time;
	return true;
}

void doEncoderA() {
	if (CheckJump()) return;
	// look for a low-to-high on channel A
	if (digitalRead(encoder0PinA) == HIGH) {
		// check channel B to see which way encoder is turning
		if (digitalRead(encoder0PinB) == LOW) {
			encoder0Pos = encoder0Pos + 1;         // CW
		}
		else {
			encoder0Pos = encoder0Pos - 1;         // CCW
		}
	}
	else   // must be a high-to-low edge on channel A                                       
	{
		// check channel B to see which way encoder is turning  
		if (digitalRead(encoder0PinB) == HIGH) {
			encoder0Pos = encoder0Pos + 1;          // CW
		}
		else {
			encoder0Pos = encoder0Pos - 1;          // CCW
		}
	}
	analogWrite(13, encoder0Pos);
}


void doEncoderB() {
	if (CheckJump()) return;
	// look for a low-to-high on channel B
	if (digitalRead(encoder0PinB) == HIGH) {
		// check channel A to see which way encoder is turning
		if (digitalRead(encoder0PinA) == HIGH) {
			encoder0Pos = encoder0Pos + 1;         // CW
		}
		else {
			encoder0Pos = encoder0Pos - 1;         // CCW
		}
	}
	// Look for a high-to-low on channel B
	else {
		// check channel B to see which way encoder is turning  
		if (digitalRead(encoder0PinA) == LOW) {
			encoder0Pos = encoder0Pos + 1;          // CW
		}
		else {
			encoder0Pos = encoder0Pos - 1;          // CCW
		}
	}
	analogWrite(13, encoder0Pos);
}
/*------------------------------------*/

void setup()
{
	analogWrite(13, 32);
	Serial.begin(115200);
	setup_temp();
	setup_lcd();
	setup_encoder();
	
}

int mini_pause = 1000;

int i = 0;
void loopa()
{
	char buffer[32];
	sprintf(buffer, "Count: %d", i);
	printf_lcd(0, "READ OK");
	printf_lcd(1, buffer);
	i++;
}

int lastPos = 0;
void loop()
{
	

	if (encoder0Pos != lastPos)
	{
		trace("Encoder: %d", encoder0Pos);
		lastPos = encoder0Pos;
	}

	int chk = DHT11.read(DHT11PIN);

	switch (chk)
	{
	case DHTLIB_OK:
		printf_lcd(0, "READ OK");
		printf_lcd(1, "");
		delay(mini_pause);
		break;
	case DHTLIB_ERROR_CHECKSUM:
		trace("Checksum error");
		printf_lcd(0, "Checksum error");
		return;
	case DHTLIB_ERROR_TIMEOUT:
		trace("Time out error");
		printf_lcd(0, "Time out error");
		return;
	default:
		trace("Unknown error");
		printf_lcd(0, "Unknown error");
		return;
	}

	printf_lcd(0, "Humidity: ");
	printf_lcd(1, "%d%%", DHT11.humidity);
	delay(mini_pause);

	printf_lcd(0, "Temperature (C):");
	printf_lcd(1, "%d", DHT11.temperature);
	delay(mini_pause);

	printf_lcd(0, "Temperature (F): ");
	printf_lcd(1, "%d", (int)Fahrenheit(DHT11.temperature));
	delay(mini_pause);

	printf_lcd(0, "Temperature (K): ");
	printf_lcd(1, "%d", (int)Kelvin(DHT11.temperature));
	delay(mini_pause);

	printf_lcd(0, "Dew Point (C): ");
	printf_lcd(1, "%d", (int)dewPoint(DHT11.temperature, DHT11.humidity));
	delay(mini_pause);

	printf_lcd(0, "Dew Point Q (C): ");
	printf_lcd(1, "%d", (int)dewPointFast(DHT11.temperature, DHT11.humidity));
	delay(mini_pause);
	
}
//
// END OF FILE
//