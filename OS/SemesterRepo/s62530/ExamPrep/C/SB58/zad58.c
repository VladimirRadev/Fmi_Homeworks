
      /* void qsort(void *base, size_t nmemb, size_t size,
                  int (*compar)(const void *, const void *));

				  */

#include <stdint.h>
  #include <sys/stat.h>
     #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

#include <err.h>
    #include <stdlib.h>
  #include <unistd.h>
#include <stdio.h>
int comp(const void* a , const void* b);
int comp(const void* a, const void* b)
{
	uint32_t* a_=((uint32_t*)a);
	uint32_t* b_=((uint32_t*)b);
	if(*a_ > *b_)
	{
		return 1;
	}
	else if(*a_ < *b_)
	{
		return -1;
	}
	else
	{
		return 0;
	}	    
}
//ne e reshena podrobno a samo za upr predi izpit
int main(const int argc,const char* argv[])
{
	if(argc!=3)
	{
		err(1,"k");	
	}
	
	int fdInp=open(argv[1],O_RDONLY);
	if(fdInp==-1)
	{
		err(2,"w");
	}

	struct stat fdInp_stat;
	stat(argv[1],&fdInp_stat);
	if(fdInp_stat.st_size > 4194304)
	{
		err(3,"too large");
	}
	if(fdInp_stat.st_size % 4 != 0 )
	{
		err(4,"not devideed 4");
	}
	
	int halfSize=(fdInp_stat.st_size/4) / 2;
	uint32_t* lhsArr=(uint32_t*)malloc(halfSize * sizeof(uint32_t));
	if(lhsArr==NULL)
	{
		err(5,"Malloc err lhs");
	}

	int rd=0;
	if((rd=read(fdInp,lhsArr,sizeof(uint32_t)*halfSize)) != sizeof(uint32_t) * halfSize)
	{
		err(6,"rd lhs");
	}
	
	

	qsort(lhsArr,halfSize,sizeof(uint32_t),comp);


	int temp1=open("t1",O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(temp1==-1)
		{
			err(7,"temp1 didn';t open");
		}
	int wr=0;
	if((wr=write(temp1,lhsArr,sizeof(uint32_t)*halfSize))  !=  sizeof(uint32_t)*halfSize)
	{
		if(wr==-1)
		{
			err(8,"COulnd't write in lhsArr");
		}
	}

	free(lhsArr);


	int halfSize2=(fdInp_stat.st_size/4) - halfSize;
	uint32_t* rhsArr=(uint32_t*)malloc(halfSize2 * sizeof(uint32_t));
	if(rhsArr==NULL)
	{
		err(5,"Malloc err rhs");
	}

	rd=0;
	if((rd=read(fdInp,rhsArr,sizeof(uint32_t)*halfSize2)) != sizeof(uint32_t) * halfSize2)
	{
		err(6,"rd lhs 2 ");
	}
	
	

	qsort(rhsArr,halfSize2,sizeof(uint32_t),comp);


	int temp2=open("t2",O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(temp2==-1)
		{
			err(7,"temp2 didn';t open");
		}
	wr=0;
	if((wr=write(temp2,rhsArr,sizeof(uint32_t)*halfSize2))  !=  sizeof(uint32_t)*halfSize2)
	{
		if(wr==-1)
		{
			err(8,"COulnd't write in rhsArr");
		}
	}
	
	free(rhsArr);


	int r1=0,r2=0;

	lseek(temp1,0,SEEK_SET);
	lseek(temp2,0,SEEK_SET);

	int sorted=open(argv[2],O_CREAT | O_TRUNC | O_RDWR , S_IRUSR | S_IWUSR);
	if(sorted==-1)
	{
		err(5,"cOULDN'T open sort");
	}
	uint32_t b1,b2;
	while( (r1=read(temp1,&b1,sizeof(b1))) == sizeof(b1) && (r2=read(temp2,&b2,sizeof(b2))) ==sizeof(b2))
	{
		
		if(b1<=b2)
		{
			if(write(sorted,&b1,sizeof(b1))!=sizeof(b1))
			{
				err(2,"coludlnd write in sorted b1 ");
			}
			lseek(temp2,-sizeof(uint32_t),SEEK_CUR);
			continue;
		}
		else
		{
			if(write(sorted,&b2,sizeof(b2))!=sizeof(b2))
			{
				err(2,"coludlnd write in sorted b2 ");
			}
			lseek(temp1,-sizeof(uint32_t),SEEK_CUR);
			continue;
		}
	}



	if(r1==-1 || r2==-1)
	{
		err(2,"Couldn't read r1 and r2");
	}
	
	if(r1==sizeof(b1))
	{
		if(write(sorted,&b1,sizeof(b1))!=sizeof(b1))
		{
			err(2,"Couldn't wirti in sorted ");
		}
	}


	while((r2=read(temp2,&b2,sizeof(b2)))==sizeof(b2))
	{
			if(write(sorted,&b2,sizeof(b2))!=sizeof(b2))
		{
			err(2,"Couldn't wirti in srted ");
		}

	}
	if(r2==-1)
	{
	err(1,"couldn't read r2");
	}

		while((r1=read(temp1,&b1,sizeof(b1)))==sizeof(b1))
	{
			if(write(sorted,&b1,sizeof(b1))!=sizeof(b1))
		{
			err(2,"Couldn't wirti in srted ");
		}

	}
	if(r1==-1)
	{
	err(1,"couldn't read r1");
	}


	unlink("t1");
	unlink("t2");


	close(fdInp);
	close(temp1);
	close(temp2);
	close(sorted);





}

