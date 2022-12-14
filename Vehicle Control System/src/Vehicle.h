/*
 ============================================================================
 Name        : Vehicle.h
 Author      : Mostafa Mahmoud Ali
 Version     :
 Copyright   : Your copyright notice
 Description : Header file for Vehicle Control System
 ============================================================================
 */


#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <stdio.h>
#include <stdlib.h>

/******************************* STANDARD TYPES ********************************/

typedef enum{
	FALSE,
	TRUE
} boolean;

typedef unsigned char         uint8_t;          //           0 .. 255
typedef unsigned short        uint16_t;         //           0 .. 65535
typedef unsigned long         uint32_t;         //           0 .. 4294967295
typedef unsigned long long    uint64_t;         //       0 .. 18446744073709551615

typedef signed char           sint8_t;          /*        -128 .. +127             */
typedef signed short          sint16_t;         /*      -32768 .. +32767           */
typedef signed long           sint32_t;         /* -2147483648 .. +2147483647      */
typedef signed long long      sint64_t;         /* -9223372036854775808 .. 9223372036854775807 */
typedef float                 float32;
typedef double                float64;

/***************************** PROJECT-RELATED DATA TYPES *****************************/

typedef enum{
	OFF,ON
} State;

typedef enum{
	RED_VS = 0,
	ORANGE_VS = 30,
	GREEN_VS = 100
}VehicleSpeed;

typedef struct{
	State engine;
	State AC;
	uint8_t speed;
	uint8_t roomTemp;
	State engineTempController;
	uint16_t engineTemp;
}Vehicle;


/* Bonus Requirement:
 * Create #define WITH_ENGINE_TEMP_CONTROLLER,
 * if this #define is 1 then compile/run the code lines that are related to the “Engine Temperature Controller"
 */
#define WITH_ENGINE_TEMP_CONTROLLER      1

/**************************** FUNCTION PROTOTYPES ****************************/

/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 * Usage:
 *     Initialize all member of the passed Vehicle struct with some random values
 *     by using (Pointer to Struct Vehicle) just for processing the program correctly
 */
void vehicle_Init(Vehicle *ptrVec);


/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 * Usage:
 *     1) Display Start Menu of the Vehicle Controller System
 *     2) Takes input from the user to know what state will be executed
 *     3) does an indirect recursion process when user want State(B,b) to be executed
 */
void startVehicleMenu(Vehicle *ptrVec);


/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 * Usage:
 *     1) Sets Vehicle Engine to ON
 *     2) Displays (Sensors Set Menu) and waits for an answer from user While the engine is ON
 *     3) Sets Vehicle Properties or Turn engine OFF ( BASED on that answer from user )
 *     4) Handles the Vehicle's Special Speed case (30 Km/Hr)
 *     5) Displays Vehicle Information While the engine is ON
 */
void setEngine_ON(Vehicle *ptrVec);


/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 * Usage:
 *     1) Sets Vehicle Engine to OFF
 *     2) Calls again startVehicleMenu Func. which applies the concept of (Indirect Recursion)
 */
void setEngine_OFF(Vehicle *ptrVec);


/* Description:
 *     Function that takes no parameters
 * Usage:
 *     Quit The Vehicle Controller System
 */
void quitSystem(void);


/* Description:
 *     Function that takes (Pointer to Struct Vehicle and uint8_t --> unsigned char) as parameters
 *     Helper Function to vehicleEngine_ON Func.
 * Usage:
 *     1) Sets Vehicle Speed when user choose State(B,b) from the Sensor Set Menu
 *     2) Sets Room Temperature and AC (Air conditioner) when user choose State(C,c) from the Sensor Set Menu
 *     3) Sets Engine Temperature and Engine Temperature Controller when user choose State(D,d) from the Sensor Set Menu
 */
void setVehicleProperties(uint8_t choice, Vehicle *ptrVec);


/* Description:
 *     Function that takes (Pointer to unsigned char and uint8_t --> unsigned char) as parameters
 *     Helper Function to setVehicleProperties Func.
 * Usage:
 *     Sets Vehicle Speed when user choose State(B,b) from the Sensor Set Menu
 *     According to the traffic light data.
 */
void setSpeed(uint8_t trafficLight, uint8_t *speed);


/* Description:
 *     Function that takes (Pointer to unsigned char and variable of type enum State ) as parameters
 *     Helper Function to setVehicleProperties Func.
 * Usage:
 *     Sets Room Temperature and AC (Air conditioner) when user choose State(C,c) from the Sensor Set Menu
 */
void setRoomTemperature_AC(uint8_t *roomTemperture, State *acValue);


/* Description:
 *     Function that takes (Pointer to unsigned char and variable of type enum State ) as parameters
 *     Helper Function to setVehicleProperties Func.
 * Usage:
 *     Sets Engine Temperature and Engine Temperature Controller when user chooses State(D,d) from the Sensor Set Menu
 */
void setEngine_Temperature_Controller(uint16_t *engineTemperature, State *tempController);


/* Description:
 *     Function that takes (Pointer to Struct Vehicle) as a parameter
 *     Helper Function to setEngine_ON Func.
 * Usage:
 *     1) Checks if Vehicle Speed is 30 Km/Hr Or not
 *     2) If Answer is YES , Function sets (AC and Engine Temperature Controller) States to ON
 *        and does some calculations on (Room and Engine) temperatures
 */
void specialVehicleSpeed(Vehicle *ptrVec);


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
void displayVehicleInformation(Vehicle *ptrVec);

#endif /* VEHICLE_H_ */
