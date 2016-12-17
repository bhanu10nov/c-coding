/**
 * @file    server.c
 * @author  Bhanu Jha(bhanujha@gmail.com)
 * @brief   server code depicting usage of dbus
 */

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "calc-generated.h"
#define SUCESS 0
#define FAILURE -1
int exportgdbusiface();
int exportgdbusinface()
{
	NetCorpSampleCalc *mycalc_object;
	mycalc_object =	net_corp_sample_calc_skeleton_new();
	if (NULL != mycalc_object) {
		return SUCESS;
	} else {
		return FAILURE;
	}
}

int main(int argc, char *argv[])
{
	fprintf(stdout,"Server program\n");

	if (SUCESS != exportgdbusiface()) {
		return FAILURE;
	}
	
	return SUCESS;
}
