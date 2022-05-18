#include <stdio.h>
#include <unistd.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <stdint.h>
#include <err.h>
int main()
{
	const char* etcPasswd="/etc/passwd";
	int fdEtc=open(etcPasswd,O_RDONLY);
	if(fdEtc==-1)
	{
		err(1,"Couldn't open /etc/passwd file \n");
	}
	int fdDest=open("passwdCp",O_WRONLY | O_TRUNC | O_CREAT , 0644);
	if(fdDest==-1)
	{
		err(1,"Couldn't create copy of passwdCp and open it after \n");
	}

	char c;
	uint32_t read_size=0,write_size=0;
	while((read_size=read(fdEtc,&c,1)) > 0)
	{
		if(c==':')
		{
			c='?';
		}
		write_size=write(fdDest,&c,read_size);
		if(write_size == (uint32_t)-1)
		{
			err(1,"Couldn't write in passwdCp");
		}


	}
	if(read_size == (uint32_t)-1)
	{
		err(1,"Couldn't read data from copied passwd in current dir\n");			
	}
	close(fdEtc);
	close(fdDest);




}

