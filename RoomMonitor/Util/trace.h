#pragma once



#include <stdio.h>
#include <stdarg.h>


void trace(const char * format, ...)
{
	char out_string[64];
	va_list args;
	va_start(args, format);
	vsprintf(out_string, format, args);
	va_end(args);
	Serial.println(out_string);
}