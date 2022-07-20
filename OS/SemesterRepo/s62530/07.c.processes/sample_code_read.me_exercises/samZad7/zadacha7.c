 #include <stdio.h>
#include <err.h>
#include <sys/wait.h>
 #include <sys/types.h>
       #include <unistd.h>
#include <stdlib.h>
  #include <unistd.h>

int main(const int argc, const char* argv[])
{
   if(argc!=4)
   {
     errx(1,"The program has to take 3 arguments\n");
   }

   for(int i=1;i<argc;i++)
   {
	   pid_t a = fork();
	   int status;
	   if(a==-1)
	   {
		   err(1,"fork");
	   }

	   if(a>0)
	   {	
		if(wait(&status)==-1)
		{

			err(1,"err while waiting\n");
		}
		printf("%d %d\n",i,WEXITSTATUS(status));
	   }
	   else
	   {
		if(execlp(argv[i],(char *)NULL)==-1)
		{
			err(1,"exec err\n");
		}

	   }




   }


}

