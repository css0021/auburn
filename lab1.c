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

#define FLAG1 1
#define FLAG2 2
#define FLAG3 4
#define FLAG4 8
#define FLAG5 16
#define FLAG6 32
#define FLAG7 64
#define FLAG8 128



/*****************************************************************************\
*                            Global data structures                           *
\*****************************************************************************/




/*****************************************************************************\
*                                  Global data                                *
\*****************************************************************************/




/*****************************************************************************\
*                               Function prototypes                           *
\*****************************************************************************/

int main (int argc, char **argv);
void Control(void);
bool check_bit(int flag);
void clear_flag(int& device);




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

inline bool check_bit(int flag, int bit) {
	return flag  & (1 << bit)
}

inline void clear_flag(int device, int& flags) {
	flags &= ~(1 << device);
}


/***********************************************************************\
 * Input : none                                                          *
 * Output: None                                                          *
 * Function: Monitor Devices and process events                          *
 \***********************************************************************/
void Control(void){
  int i;
  Status LastStatus=0;
  while (1) {
    printf("%10.3f   Flags = %d - \n ", Now(), Flags);
    sleep(1); // Just to slow down to have time to see Flags
    if (Flags != LastStatus){ //an event has occured
      LastStatus = Flags;
      int temp = Flags;
      Flags = 0;
      if (temp & (1 << 0) == 1) { //device 0
	DisplayEvent(*BufferLastEvent[0].msg, &BufferLastEvent[0]);
	Server(&BufferLastEvent[0]);
	temp &= ~(1 << 0);
      }
      else if (temp & (1 << 1) == 1) { //device 1

	DisplayEvent(*BufferLastEvent[1].msg, &BufferLastEvent[1]);
	Server(&BufferLastEvent[1]);
	//printf("%d\n", temp);
	Flags &= ~(1 << 0);

      }
      else printf("aiojdad");
      //else if (temp & (1 << 2) == 1) {

	//DisplayEvent(*BufferLastEvent[2].msg, &BufferLastEvent[2]);
      

	//Server(&BufferLastEvent[2]);
      //}
      printf("\n >>>>>>>>>  >>> When: %10.3f  Flags = %d\n", Now(),
	     Flags);
	/*
      switch(Flags) {
	
	 case 0:
	      DisplayEvent(*BufferLastEvent[0].msg, &BufferLastEvent[0]);
	      Server(&BufferLastEvent[0]);
              Flags = 0;
	      break;

	  case 1:
              i = log2(Flags);
	      DisplayEvent(*BufferLastEvent[i].msg, &BufferLastEvent[i]);
	      Server(&BufferLastEvent[i]);
              Flags = 0;
	      break;
          case 2:
	      i = log2(Flags);
	      DisplayEvent(*BufferLastEvent[i].msg, &BufferLastEvent[i]);
	      Server(&BufferLastEvent[i]);
              Flags = 0;
	      break;

          case 4:
 	      i = log2(Flags);
	      DisplayEvent(*BufferLastEvent[i].msg, &BufferLastEvent[i]);
	      Server(&BufferLastEvent[i]);
              Flags = 0;
	     
	      break;

	  case 8:
 	      i = log2(Flags);
	      DisplayEvent(*BufferLastEvent[i].msg, &BufferLastEvent[i]);
	      Server(&BufferLastEvent[i]);
              Flags = 0;
	      break;

	  case 16:
              i = log2(Flags);
	      DisplayEvent(*BufferLastEvent[i].msg, &BufferLastEvent[i]);
	      Server(&BufferLastEvent[i]);
              Flags = 0;
	      
	      break;

	 

      }
     */
    }
	
 
  }
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










