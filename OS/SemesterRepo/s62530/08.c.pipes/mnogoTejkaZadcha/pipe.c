#include <stdlib.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
 #include <unistd.h>
#include <err.h>

int main(void)
{
	int a[2];
	pipe(a);
	pid_t p1=fork();
	if(p1==0)
	{
		close(a[0]);
		dup2(a[1],1);
		if(execlp("cut","cut","-d",":","-f","6","/etc/passwd",(char*)NULL)==-1)
		{
			err(1,"err");
		}
	}
	close(a[1]);
	int b[2];
	pipe(b);
	pid_t p2=fork();
	if(p2==0)
	{
		dup2(a[0],0);
		close(b[0]);
		dup2(b[1],1);
		if(execlp("sort","sort",(char *)NULL)==-1)
		{
			err(1,"er");
		}

	}
	close(a[0]);
	close(b[1]);
	dup2(b[0],0);
	if(execlp("uniq","uniq","-c",(char*)NULL)==-1)
	{
		err(1,"err2");
	}



}

