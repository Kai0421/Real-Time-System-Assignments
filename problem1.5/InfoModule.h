		/********************************************************************************/
		/*	Ren Kai Tam -- R00095982													*/
		/*	Problem 1.5 -- Self Driving Car												*/
		/*	      																		*/
		/*	      																		*/
		/*	InfoModule.h																*/
		/********************************************************************************/

/*
	Memory Module contain information about the car.
*/
#include <types.h>
#define SEAT_NO 4
struct CarInfo{
	 int carDoorClose;
	 int numberOfSeatIsOccupied;
	 int seatBeltFasten[SEAT_NO];
	 int handBrakeIsOff;
	 int carMoving;
};
#define CAR_INFO_SIZE sizeof(struct CarInfo)
#define INFO_MODULE "CarInfoMemory"
#define TRUE 1
#define FALSE 0
