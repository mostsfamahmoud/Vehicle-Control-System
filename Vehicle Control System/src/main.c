/*
 ============================================================================
 Name        : main.c
 Author      : Mostafa Mahmoud Ali
 Version     :
 Copyright   : Your copyright notice
 Description : Main Function of Vehicle Control System Project
 ============================================================================
 */

#include "Vehicle.h"

int main(void) {

	Vehicle v1;

	vehicle_Init(&v1);
	
	printf("============= PS: Upper & Lower-case characters are accepted =============\n\n");

	startVehicleMenu(&v1);

	return EXIT_SUCCESS;
}
