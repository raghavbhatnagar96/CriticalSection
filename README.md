# CriticalSection
There are 2 threads: Child1 and child2
Each thread has a different purpose but both use the commonLEDResource.
Color of commonLEDResource: Red.
Thus they are not thread safe as they share a resource.
To make sure there is no conflict, we use semaphore.
Child1: Turn commonLEDResource On Off On Off On Off On Off.
Child2: Turn commonLEDResource On some time and then Off.
This is to ensure that the difference between the threads is visible.
Also, a childLED is also lit when a particular child is being used.
For child1 it is: Orange.
For child2 it is: Blue.
Used my_delay as HAL_delay was not working.
