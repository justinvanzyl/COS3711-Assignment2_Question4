# COS3711-Assignment2_Question4
Assignment task to implement concurrency in C++ with Qt

Instructions:
Write a class named PrimeFinder, capable of running as a thread, to find prime numbers between two given numbers. Write a GUI application that allows a user to enter start and end numbers as well as the number of threads to use (maximum 4). When Start is clicked, the task should be divided into the required number of parts, the required number of PrimeFinder threads started, and the primes displayed in an appropriate window (per thread) as they are found. This is to be done without using QtConcurrent – you are to manage the threads yourself, and clean up after the threads have completed their work. This means that you should be able to change the start, end, and number of thread numbers and click Start again without the program crashing or producing strange results. Also, you should handle a user closing the application (closeEvent) before the threads have completed running so that the threads can tidy up after themselves before the application is closed.

![example](/images/screen.png?raw=true)
The above screenshot is only an example, and you can design the graphical user interface as you wish as long as it satisfies the above requirements.
Do not use the old-style threading given in Ezust; rather follow the recommended approach discussed in the Learning Units/TL102.
