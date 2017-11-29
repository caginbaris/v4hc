/*
 * EndoksEmbedded Libary
 * File: $Id: fputc_debug.c, 2017/04/20 14:01:11 Serbay Ozkan $
 */
#include <stdio.h>
#include <stm32f7xx.h>

int fputc(int c, FILE *stream)
{
	return(ITM_SendChar(c));
}
