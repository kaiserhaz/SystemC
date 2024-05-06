/**
 * SA-ECG Testbench Script
 */

#include "stdio.h"
#include "systemc.h"

int sc_main(int, char* [])
{
	for(int i=0; i<5; i++)
	{
		printf("__/^\\____");
		system("sleep 1");
	}
	
	printf("\n");
	
	printf("   SA-ECG Module Test   \n");
	
	//sc_start(-1);
	
	system("sleep 2");
	
	return 0;
}