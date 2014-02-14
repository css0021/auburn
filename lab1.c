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
  int processed = 0;
  while (1) {
    printf("%10.3f   Flags = %d - \n ", Now(), Flags);
    if (Flags != 0){ //an event has occured
      int tpFlags = Flags;
      Flags = 0;
      while (tpFlags != 0) {	
	if (checkLSB(tpFlags) == SET) {
		DisplayEvent(*BufferLastEvent[i].msg, &BufferLastEvent[i]);
		Server(&BufferLastEvent[i]);
	}	
	tpFlags = tpFlags >> 1;
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
int checkLSB(int flag) {
	return flag & 1;

}

/***********************************************************************\
* Input : None                                                          *
* Output: None                                                          *
* Function: This must print out the number of Events buffered not yet   *
*           not yet processed (Server() function not yet called)        *
\***********************************************************************/
void BookKeeping(void){
  printf("\n >>>>>> Done\n");
}










