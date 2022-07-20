/*
	Да се напише програма на C, която изпълнява команда ls с точно един аргумент.
*/

#include <unistd.h>
#include <stdlib.h>
#include <err.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char* argv[])
{
	char* args[100];
	
	args[0]=malloc(100);
	strcpy(args[0],"ls");
	for (int i = 1; i < argc; i++) {
		args[i]=malloc(20);
		strcpy(args[i],argv[i]);
	}

	if (execvp("ls", args) == -1) {
		err(99, "err execling");
	}

	for(int i=0;i<100;i++)
	{
		free(args[i]);
	}


	exit(0);
}
