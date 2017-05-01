/*Code Explaination:
There are 2 threads: Child1 and child2
Each thread has a different purpose but both use the commonLEDResource.
Color of commonLEDResource: Red
Thus they are not thread safe as they share a resource.
To make sure there is no conflict, we use semaphore.
Child1: Turn commonLEDResource On Off On Off On Off On Off.
Child2: Turn commonLEDResource On some time and then Off.
This is to ensure that the difference between the threads is visible.
Also, a childLED is also lit when a particular child is being used.
For child1 it is: Orange
For child2 it is: Blue
Used my_delay as HAL_delay was not working.
*/

#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "Board_LED.h"
#define commonLEDResource 2
#define initSemChild1 1
#define initSemChild2 3

void child1(const void *argument);
void child2(const void *argument);

/*Defining the threads*/
osThreadDef (child1, osPriorityNormal, 1, 0);
osThreadDef (child2, osPriorityNormal, 1, 0);
osThreadId child1ID, child2ID;
/*Defining semaphore*/
osSemaphoreDef(sem);
osSemaphoreId semID;
/*Main function*/
void my_delay(int num){
	while(num--);
}

int main()
{
		osKernelInitialize();
		LED_Initialize();//Initialize leds
		semID = osSemaphoreCreate(osSemaphore(sem),1);					//Create Semaphore
		child1ID = osThreadCreate(osThread(child1), NULL);
		child2ID = osThreadCreate(osThread(child2), NULL);
		osKernelStart();//Start threads.
		for(;;){
		//osDelay(1);
	}
}

void child1(const void *argument)
{
	for(;;)//infinite loop
	{ 
		osSemaphoreWait(semID,osWaitForever);	//Obtain sem
		LED_On(initSemChild1);
		my_delay(100000);//1 second on
		LED_On(commonLEDResource);
		my_delay(300000);//1 second on
		LED_Off(commonLEDResource);
		my_delay(300000);//1 second off		
		LED_On(commonLEDResource);
		my_delay(300000);//1 second on
		LED_Off(commonLEDResource);
		my_delay(300000); 
		LED_On(commonLEDResource);
		my_delay(300000);//1 second on
		LED_Off(commonLEDResource);
		my_delay(300000);//1 second off		
		LED_On(commonLEDResource);
		my_delay(300000);//1 second on
		LED_Off(commonLEDResource);
		my_delay(300000); //1 second delay in end
		LED_Off(initSemChild1);
		my_delay(300000); //Turn off child1 sem LED
		osSemaphoreRelease(semID);//Release semaphore
	}	
}
	
	
void child2(const void *argument)
{
	for(;;){
		osSemaphoreWait(semID,osWaitForever);	//Obtain sem
		LED_On(initSemChild2);
		my_delay(100000);// 1 seconds on
		LED_On(commonLEDResource);
		my_delay(1500000);//
		LED_Off(commonLEDResource);
		my_delay(100000); // 1 second delay in the end
		LED_Off(initSemChild2);
		my_delay(100000); // Turn off child1 sem LED
		osSemaphoreRelease(semID);//Release semaphore
	}
}
