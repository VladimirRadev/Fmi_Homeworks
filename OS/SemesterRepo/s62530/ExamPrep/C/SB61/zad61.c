#include <err.h>
#include <stdio.h>
  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
 #include <unistd.h>
#include <stdint.h>
typedef struct __attribute__((packed))
{
	uint32_t uid;//4
	uint16_t reserved1;//2
	uint16_t reserverd2;//2
	uint32_t sessionStart;//4
	uint32_t sessionEnd;//4

} userInfo_t;
int main(const int argc, const char* argv[])
{
	if(argc!=2)
	{
		errx(1,"Program must take an argument in this format ");
	}
	int fd=open(argv[1],O_RDONLY);
	if(fd==-1)
		{
			err(2,"Program couldn't open %s for reading",argv[1]);
		}
	struct stat file_stat;
	if(stat(argv[1],&file_stat)==-1)
	{
		err(3,"Couldn't stat file %s",argv[1]);
	}
//long int max=(long int) ( 16384 * 16);

	userInfo_t userInfo;
	double userInfoCount=(double)((double)file_stat.st_size / (double)sizeof(userInfo));
	double avgSessions=0.0;
	double dispersion=0.0;
	//userInfo_t userInfo;

	//masiva realno trqbva da pazi ne 10k a trqbva pazi uint32 max chisla v koito vseki unique user da si pazi maksimalnata sesiq
	//
	long long uniqUsrMaxSession[1000]={-1};


	for(unsigned int i=0;i<userInfoCount;i++)
	{
		if(read(fd,&userInfo,sizeof(userInfo))!=sizeof(userInfo))
			{
				err(5,"Couldn't read userInfo");
			}
		if(userInfo.sessionStart >= userInfo.sessionEnd)
		{
			err(6,"Invalid info about unix times");
		}
		avgSessions+=(double)((userInfo.sessionEnd-userInfo.sessionStart)/userInfoCount);
		if (uniqUsrMaxSession[userInfo.uid] == -1)
		{
			uniqUsrMaxSession[userInfo.uid]=0;
		}
		if(uniqUsrMaxSession[userInfo.uid] < (int)(userInfo.sessionEnd-userInfo.sessionStart))
		{
			uniqUsrMaxSession[userInfo.uid]=(int)(userInfo.sessionEnd-userInfo.sessionStart);
		}
	}
//	printf ("kur");
	
	if(lseek(fd,0,SEEK_SET)==-1)
	{
		err(7,"couldn't seek set back to 0 on file: %s",argv[1]);
	}

	for(unsigned int  i=0;i<userInfoCount;i++)
	{
			if(read(fd,&userInfo,sizeof(userInfo))!=sizeof(userInfo))
			{
				err(5,"Couldn't read userInfo");
			}
			double xi= (double)(((userInfo.sessionEnd - userInfo.sessionStart) - avgSessions) * ((userInfo.sessionEnd - userInfo.sessionStart) - avgSessions));
			dispersion+=(double)(xi/userInfoCount);
	}


	for (unsigned int i=0;i<1000;i++)
	{
		if((double)(uniqUsrMaxSession[i] * uniqUsrMaxSession[i]) > dispersion)
		{
			printf("UID: %d , maxLenghtSession: %lld\n",i,uniqUsrMaxSession[i]);
		}
	}
	
	close(fd);


}
