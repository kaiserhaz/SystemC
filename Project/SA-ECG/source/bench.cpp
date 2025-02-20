/**
 * @file bench.cpp
 *
 * @brief SystemC entry point for SA-ECG project.
 * 
 * -- Versioning Info --
 *
 * v0.0 :  :
 *
 * @copyright
 * Copyright 2024 British Malaysian Institute, Universiti Kuala Lumpur.
 * 
 * Written by Muhammad Haziq Kamarul Azman a.k.a. Kaiser Haz.
 *******************************************************************************************
 */

// Libs
#include "stdio.h"
#include "systemc.h"

/**
 * SystemC main
 */
int sc_main(int argc, char* argv[])
{
	for(int i=0; i<8; i++)
		printf("__/^\\____");
	
	printf("\n");
	
	printf("   SA-ECG Module Testbench   \n");
	
	//sc_start(-1);
	
	system("sleep 2");
	
	return 0;
}