/*****************************************************************************\
* Laboratory Exercises COMP 3510                                              *
* Author: Saad Biaz                                                           *
* Date  : January 18, 2014                                                    *
\*****************************************************************************/

/*****************************************************************************\
*                             Global system headers                           *
\*****************************************************************************/


#include "common.h"

/*****************************************************************************\
*                             Global data types                               *
\*****************************************************************************/

float R[8] = {[0 ... 7] = 0}; //response time array
float A[8] = {[0 ... 7] = 0}; //turnaround time array
int processedEvents[8] = {[0 ... 7] = 0};



/*****************************************************************************\
*                             Global definitions                              *
\*****************************************************************************/

#define SET 1
#define CLEAR 0

/*****************************************************************************\
*                            Global data structures                           *
\*****************************************************************************/




/*****************************************************************************\
*                                  Global data                                *
\*****************************************************************************/
float Tinit;
float Tfinal;
float Tdone;
float responseTime;
float turnaroundTime;
int processed;


/*****************************************************************************\
*                               Function prototypes                           *
\*****************************************************************************/


int checkLSB(int flag);
int main (int argc, char **argv);
void Control(void);




/*****************************************************************************\
* function: main()                                                            *
* usage:    Create an artificial environment for embedded systems. The parent *
*           process is the "control" process while children process will gene-*
*           generate events on devices                                        *
*******************************************************************************
* Inputs: ANSI flat C command line parameters                                 *
* Output: None                                                                *
*                                                                             *
* INITIALIZE PROGRAM ENVIRONMENT                                              *
* WHILE JOBS STILL RUNNING                                                    *
*    CREATE PROCESSES                                                         *
*    RUN LONG TERM SCHEDULER                                                  *
*    RUN SHORT TERM SCHEDULER                                                 *
*    DISPATCH NEXT PROCESS                                                    *
\*****************************************************************************/

int main (int argc, char **argv) {

   if (Initialization(argc,argv)){
     Control();
   } 
} /* end of main function */




/***********************************************************************\
 * Input : none                                                          *
 * Output: None                                                          *
 * Function: Monitor Devices and process events                          *
 \***********************************************************************/
void Control(void){
  int i = 0;
  while (1) {
    //printf("%10.3f   Flags = %d - \n ", Now(), Flags);
    if (Flags != 0){ //an event has occured
      int tpFlags = Flags;
      Flags = 0;
      while (tpFlags != 0) {	
	if (checkLSB(tpFlags) == SET) {
		Tinit = Now();
		DisplayEvent(*BufferLastEvent[i].msg, &BufferLastEvent[i]);
		Tfinal = Now();
		Server(&BufferLastEvent[i]);
		Tdone = Now();
		processed++;

	}	
	tpFlags = tpFlags >> 1; //shift right to check the next device
	i++;
      }
      i = 0;
    
     }
   }
 }
  
/**********************************************************************\
 * Input : Flag - number you want to check the LSB of                  *
 * Output : Returns 0 or 1					       *
 * Function : Returns the bitwise AND of the input with 1.             *
\**********************************************************************/
int checkLSB(int flag) {return flag & 1;}


/***********************************************************************\
* Input : None                                                          *
* Output: None                                                          *
* Function: This must print out the number of Events buffered not yet   *
*           not yet processed (Server() function not yet called)        *
\***********************************************************************/
void BookKeeping(void){
	responseTime = Tfinal - Tinit;
	turnaroundTime = Tdone - Tinit;		
	R[BufferLastEvent[i].DeviceID] += responseTime;
	A[BufferLastEvent[i].DeviceID] += turnaroundTime;
	int j = 0;
	float rSum = 0;
	float aSum = 0;
	while (j < 8) {
		rSum += R[j];
		aSum += A[j];
		j++;
	}
	float averageR = (rSum/processed);
	float averageA = (aSum/processed);
	printf("Processed %d events\n", processed);
	printf("The average response time was %10.11f seconds\n", averageR);
	printf("The average turnaround time was %2.3f seconds\n", averageA);

  printf("\n >>>>>> Done\n");
}










