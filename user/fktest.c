#include "lib.h"
void umain()
{
/*	
	writef("start\n");
	int pid = fork();
	int envid = syscall_getenvid();
	writef("myid: %d\n", envid);
	if (pid < 0) {
		writef("fork failed\n");
	}
	else if (pid == 0) {
		writef("I am child\n");
	}
	else writef("I am father\n");
	writef("end: %d\n", envid);
*/
	int a = 0;
	int id = 0;
	int i;
	if ((id = fork()) == 0) {
		
		if ((id = fork()) == 0) {
			
			a += 3;

			for (;;) {
				writef("\t\tthis is child2 :a:%d\n", a);
			}
		}

		a += 2;

		for (;;) {
			writef("\tthis is child :a:%d\n", a);
		}
	}

	a++;

	for (;;) {
		writef("this is father :a:%d\n", a);
	}

}
