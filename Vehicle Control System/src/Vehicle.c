/*
 ============================================================================
 Name        : Vehicle.c
 Author      : Mostafa Mahmoud Ali
 Version     :
 Copyright   : Your copyright notice
 Description : Source file for Vehicle Control System
 ============================================================================
 */

#include "Vehicle.h"


/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 * Usage:
 *     Initialize all member of the passed Vehicle struct with some random values
 *     by using (Pointer to Struct Vehicle) just for processing the program correctly
 */
void vehicle_Init(Vehicle *ptrVec){
	ptrVec->AC = OFF;
	ptrVec->engine = ON;
	ptrVec->engineTempController = OFF;
	ptrVec->speed = 50;
	ptrVec->engineTemp = 90;
	ptrVec->roomTemp = 35;
}


/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 * Usage:
 *     1) Display Start Menu of the Vehicle Controller System
 *     2) Takes input from the user to know what state will be executed
 *     3) does an indirect recursion process when user want State(B,b) to be executed
 */
void startVehicleMenu(Vehicle *ptrVec) {

	uint8_t input;
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n\n");

	/* Taking input from user which represent the state that will be executed */
	fflush(stdout);
	scanf(" %c", &input);

	switch (input) {
	case 'a':
	case 'A':
		setEngine_ON(ptrVec);      /* Invoking function that responsible for Turing ON the engine --> State(A,a)  */
		break;
	case 'b':
	case 'B':
		setEngine_OFF(ptrVec);     /* Invoking function that responsible for Turing OFF the engine --> State(B,b) */
		break;
	case 'c':
	case 'C':
		quitSystem();                /* Invoking function that responsible for Quit the system --> State(C,c)  */
		break;
	default:
		printf("INVALID STATE\n");
		break;
	}
}


/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 * Usage:
 *     1) Sets Vehicle Engine to ON
 *     2) Displays (Sensors Set Menu) and waits for an answer from user While the engine is ON
 *     3) Sets Vehicle Properties or Turn engine OFF ( BASED on that answer from user )
 *     4) Handles the Vehicle's Special Speed case (30 Km/Hr)
 *     5) Displays Vehicle Information While the engine is ON
 */
void setEngine_ON(Vehicle *ptrVec) {

	ptrVec->engine = ON;
	uint8_t choice;

	while (ptrVec->engine == ON) {

		/* Sensor Set Menu */
		printf("\n");
		printf("a. Turn off the engine \n");
		printf("b. Set the traffic light color \n");
		printf("c. Set the room temperature (Temperature Sensor) \n");

#if WITH_ENGINE_TEMP_CONTROLLER == 1

		printf("d. Set the engine temperature (Engine Temperature Sensor) \n\n");

#endif
		/* Taking input from user which represent the state that will be executed */
		fflush(stdout);
		scanf(" %c", &choice);

		if ((choice == 'a') || (choice == 'A')) {

			setEngine_OFF(ptrVec);   /* Invoking function that responsible for Turing OFF the engine --> State(A,a) */

			return;   /* Quitting from this Function */
		}
		else
			setVehicleProperties(choice, ptrVec); /* Invoking function that responsible for Setting Vehicle Properties -->
			                                         Any State except State(A,a) */

		specialVehicleSpeed(ptrVec);    /* Invoking function that responsible for Handling Vehicle's Special Speed case (30 Km/Hr) */

		displayVehicleInformation(ptrVec);    /* Invoking function that responsible for Displaying Vehicle Information
		                                         While the engine is ON */
	}
}


/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 * Usage:
 *     1) Sets Vehicle Engine to OFF
 *     2) Calls again startVehicleMenu Func. which applies the concept of (Indirect Recursion)
 */
void setEngine_OFF(Vehicle *ptrVec) {

	ptrVec->engine = OFF;
	printf("\nTurn OFF Vehicle Engine\n\n");
	startVehicleMenu(ptrVec);
}


/* Description:
 *     Function that takes no parameters
 * Usage:
 *     Quit The Vehicle Controller System
 */
void quitSystem(void) {
	printf("\nQuit The System\n");
	return;
}


/* Description:
 *     Function that takes (Pointer to Struct Vehicle and uint8_t --> unsigned char) as parameters
 *     Helper Function to setEngine_ON Func.
 * Usage:
 *     1) Sets Vehicle Speed when user chooses State(B,b) from the Sensor Set Menu
 *     2) Sets Room Temperature and AC (Air conditioner) when user chooses State(C,c) from the Sensor Set Menu
 *     3) Sets Engine Temperature and Engine Temperature Controller when user chooses State(D,d) from the Sensor Set Menu
 */
void setVehicleProperties(uint8_t choice, Vehicle *ptrVec) {

	uint8_t color;

	if ((choice == 'b') || (choice == 'B')) {

		printf("Enter the required traffic light color:\n"
				"Red: Enter r \tOrange: Enter o \tGreen: Enter g\n\n");
		fflush(stdout);
		scanf(" %c", &color);
		setSpeed(color, &ptrVec->speed);
	}

	else if ((choice == 'c') || (choice == 'C')) {

		printf("\nEnter the required room temperature:\n");
		fflush(stdout);
		scanf("%hhd", &ptrVec->roomTemp);
		setRoomTemperature_AC(&ptrVec->roomTemp, &ptrVec->AC);
	}

#if WITH_ENGINE_TEMP_CONTROLLER == 1

	else if ((choice == 'd') || (choice == 'D')) {
		printf("\nEnter the required engine temperature:\n");
		fflush(stdout);
		scanf("%hd", &ptrVec->engineTemp);
		setEngine_Temperature_Controller(&ptrVec->engineTemp, &ptrVec->engineTempController);
	}

#endif

}


/* Description:
 *     Function that takes (Pointer to unsigned char and uint8_t --> unsigned char) as parameters
 *     Helper Function to setVehicleProperties Func.
 * Usage:
 *     Sets Vehicle Speed when user choose State(B,b) from the Sensor Set Menu
 *     According to the traffic light data.
 */
void setSpeed(uint8_t trafficLight, uint8_t *speed) {

	switch (trafficLight) {
	case 'g':
	case 'G':
		*speed = GREEN_VS;       /* if traffic light is Green ,Set Vehicle Speed to 100 Km/Hr */
		break;
	case 'o':
	case 'O':
		*speed = ORANGE_VS;      /* if traffic light is Orange ,Set Vehicle Speed to 30 Km/Hr */
		break;
	case 'r':
	case 'R':
		*speed = RED_VS;        /* if traffic light is Red ,Set Vehicle Speed to 0 Km/Hr */
		break;
	default:
		break;
	}
}


/* Description:
 *     Function that takes (Pointer to unsigned char and variable of type enum State ) as parameters
 *     Helper Function to setVehicleProperties Func.
 * Usage:
 *     Sets Room Temperature and AC (Air conditioner) when user chooses State(C,c) from the Sensor Set Menu
 */
void setRoomTemperature_AC(uint8_t *roomTemperture, State *acValue) {

	/* If temperature is less than 10 OR greater than 30 , Turn AC ON and set temperature to 20 */
	if ((*roomTemperture < 10) || (*roomTemperture > 30)) {
		*roomTemperture = 20;
		*acValue = ON;
	}
	else                      /* If temperature is otherwise, Turn AC OFF */
		*acValue = OFF;
}


/* Description:
 *     Function that takes (Pointer to unsigned char and variable of type enum State ) as parameters
 *     Helper Function to setVehicleProperties Func.
 * Usage:
 *     Sets Engine Temperature and Engine Temperature Controller when user chooses State(D,d) from the Sensor Set Menu
 */
void setEngine_Temperature_Controller(uint16_t *engineTemperature, State *tempController) {

	/* If temperature is less than 100 OR greater than 150 , Turn “Engine Temperature Controller” ON and set temperature to 125 */
	if ((*engineTemperature < 100) || (*engineTemperature > 150)) {
		*engineTemperature = 125;
		*tempController = ON;
	}
	else                            /* If temperature is otherwise, Turn “Engine Temperature Controller” OFF */
		*tempController = OFF;
}



/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 *     Helper Function to setEngine_ON Func.
 * Usage:
 *     1) Checks if Vehicle Speed is 30 Km/Hr Or not
 *     2) If Answer is YES , Function sets (AC and Engine Temperature Controller) States to ON
 *        and does some calculations on (Room and Engine) temperatures
 */
void specialVehicleSpeed(Vehicle *ptrVec) {

	if (ptrVec->speed == ORANGE_VS) {

		if (ptrVec->AC == OFF)
			ptrVec->AC = ON;

		ptrVec->roomTemp = ptrVec->roomTemp * (5.0 / 4) + 1;

#if WITH_ENGINE_TEMP_CONTROLLER == 1

		if (ptrVec->engineTempController == OFF)
			ptrVec->engineTempController = ON;

		ptrVec->engineTemp = ptrVec->engineTemp * (5.0 / 4) + 1;

#endif
		}
	else
		return;
}


/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 *     Helper Function to setEngine_ON Func.
 * Usage:
 * Display the current vehicle state after applying 7.a to 7.d
     1) Engine state: ON/OFF.
     2) AC: ON/OFF.
     3) Vehicle Speed.
	 4) Room Temperature.
	 5) Engine Temperature Controller State.
     6) Engine Temperature.
*/
void displayVehicleInformation(Vehicle *ptrVec){

	printf("\n");
	printf((ptrVec->engine == ON) ? "Engine state: ON\n" : "Engine state: OFF\n");
	printf((ptrVec->AC == ON) ? "AC state: ON\n" : "AC state: OFF\n");
	printf("Vehicle Speed: %d Km/Hr\n", ptrVec->speed);
	printf("Room Temperature: %d C\n", ptrVec->roomTemp);

#if WITH_ENGINE_TEMP_CONTROLLER == 1

	printf((ptrVec->engineTempController == ON) ?"Engine Temperature Controller State: ON\n" :
					"Engine Temperature Controller State: OFF\n");
	printf("Engine Temperature: %d C\n", ptrVec->engineTemp);

#endif
}
