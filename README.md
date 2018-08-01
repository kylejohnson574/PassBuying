# PassBuying

Windows:

Use solution PassBuying.sln.
Solution is a windows 10 x64 build. If using an older compiler then changes to the solution
will be needed. 

LINUX:

A CMake file is given. To Build:
	1. cmake ./
	2. make all

To Run:
	1. ./gccPASSBUYING
	
	
OVERALL:

CodeLayout.jpg gives an overview of the code structure. There is a command line interface that
is used for emulation testing of the core code. Startup requires an input for the type of 
transportation that will be emulated for that session. Then the main menu give 4 options.

1. Buy-> The buy menu gives the option to buy the two type of passes. Also allows the user
	to renew a monthly pass or add money to a per ride pass.
2. Use-> The use menu allows the user to use a monthly pass or a per ride pass under the command
	use. There is also the option to check the validity of a monthly pass and the balance of 
	a per ride pass.
3. Debug-> This will dumb the current contents of the DB (PassQueue) for each type of pass. 

4. Exit-> Exit will exit the system after calling the cleanup routines. 