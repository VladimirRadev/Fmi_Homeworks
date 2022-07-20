#include <stdint.h>
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <string.h>
typedef struct __attribute__((packed)) header{
	char magicWord[3];
	uint32_t ram_size;
} header_t;

typedef struct __attribute__((packed)) command{
		uint8_t opcode;
		int64_t opr1;
		int64_t opr2;
		int64_t opr3;
} command_t;
typedef struct __attribute__((packed)) oprAttributes {
		int fd;
		header_t* header;
		command_t* command;
		int64_t* ram_cells;
		bool* setIndexes;
} oprAttributes_t;

bool validHeader(header_t* head)
{
	char test[4];
	strcpy(test,head->magicWord);
	if(strcmp(test,"ORC")==0)
	{
		return 1;
	}
	return 0;

}

//set (tar , val)
void set(oprAttributes_t* oprAtt)
{
	if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in set: tar= %ld",oprAtt->command->opr1);
	}
	oprAtt->ram_cells[oprAtt->command->opr1]=oprAtt->command->opr2;
	oprAtt->setIndexes[oprAtt->command->opr1]=true;


	//printf("%ld %ld \n",oprAtt->ram_cells[oprAtt->command->opr1],oprAtt->command->opr2);
}

//load (to ,from_ptr)

void load(oprAttributes_t* oprAtt)
{
	if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in load: to= %ld",oprAtt->command->opr1);
	}

		if(oprAtt->command->opr2 < 0  || oprAtt->command->opr2 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in load: from_ptr= %ld",oprAtt->command->opr2);
	}

	//lA=ram[from_ptr]
	int64_t loadAddress=oprAtt->ram_cells[oprAtt->command->opr2];

	if(loadAddress<0 || loadAddress >= oprAtt->header->ram_size || loadAddress > UINT32_MAX)
	{
		errx(1,"ram[from_ptr] is not a valid address ( has to be in : [0,ram_size)");
	}

	if ( oprAtt->setIndexes[loadAddress]==false)
	{
		errx(1,"tried to read from unset address in load operation:  %ld \n",loadAddress);
	}
	//ram[to]=ram[ram[from_ptr]]
	oprAtt->ram_cells[oprAtt->command->opr1]=oprAtt->ram_cells[loadAddress];
	oprAtt->setIndexes[oprAtt->command->opr1]=true;

	//printf("ram[to]=ram[ram[from_ptr]] %ld %ld\n",oprAtt->ram_cells[oprAtt->command->opr1],oprAtt->ram_cells[loadAddress]);

}

//out (v)
void out(oprAttributes_t* oprAtt)
{
		if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in out: v= %ld",oprAtt->command->opr1);
	}

		if(oprAtt->setIndexes[oprAtt->command->opr1]==false)
		{
			errx(1,"Tried to read unset data in out ->  given index v : %ld\n",oprAtt->command->opr1);
		}


		//stdout<<ram[v]
		if(write(1,&oprAtt->ram_cells[oprAtt->command->opr1],sizeof(oprAtt->ram_cells[oprAtt->command->opr1]))==-1)
		{
			//printf("%d %ld\n",oprAtt->fd,oprAtt->ram_cells[oprAtt->command->opr1]);
			err(2,"Error while writing on stdout in out operation\n");
		}
		
}


//store (to_ptr,from)
//
//
void store(oprAttributes_t* oprAtt)
{
		if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in store: to_ptr= %ld",oprAtt->command->opr1);
	}

		if(oprAtt->command->opr2 < 0  || oprAtt->command->opr2 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in store: from= %ld",oprAtt->command->opr2);
	}

	if(oprAtt->setIndexes[oprAtt->command->opr1]==false)
	{
		errx(1,"(store) Tried to read unset value at index(to_ptr arg): %ld\n",oprAtt->command->opr1);
	}

		if(oprAtt->setIndexes[oprAtt->command->opr2]==false)
	{
		errx(1,"(store)Tried to read unset value at index(from arg): %ld\n",oprAtt->command->opr2);
	}
	//storeAddress=ram[to_ptr]
	int64_t storeAddress=oprAtt->ram_cells[oprAtt->command->opr1];

	if(storeAddress < 0 || storeAddress >= (int64_t)oprAtt->header->ram_size)
	{
		errx(1,"Invalid index provided in store: ram[to_ptr]= %ld",storeAddress);
	}

	//ram[ram[to_ptr]]=ram[from]
	oprAtt->ram_cells[storeAddress]=oprAtt->ram_cells[oprAtt->command->opr2];
	
	oprAtt->setIndexes[storeAddress]=true;
	
}

//jmp(idx)
//
//
void jmp(oprAttributes_t* oprAtt)
{	
		if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in jmp: idx= %ld",oprAtt->command->opr1);
	}
	
		if(oprAtt->setIndexes[oprAtt->command->opr1]==false)
		{
				errx(1,"(jmp) Tried to read unset value at index(idx arg): %ld\n",oprAtt->command->opr1);
	}
		//to = ram[idx]
		int64_t jmpToCommand=oprAtt->ram_cells[oprAtt->command->opr1];
		int64_t dest=sizeof(header_t) + jmpToCommand*sizeof(command_t);
		//printf("%ld\n",dest);
		if(lseek(oprAtt->fd,dest,SEEK_SET)==-1)
		{
			err(2,"Lseek seek set error in jmp operation -> jmp to index=%ld\n",dest);
		}
		command_t nextCom;
		if(read(oprAtt->fd,&nextCom,sizeof(nextCom))<=0)
		{
			errx(1,"Invalid index of command in jmp operation ( ram[idx] excced max command's index)");
		}
		if(lseek(oprAtt->fd,-sizeof(command_t),SEEK_CUR)==-1)
		{
			err(2,"Couldn't returned to the last command in jmp operation\n");
		}


}


//sgz(v)
//
//
void sgz(oprAttributes_t* oprAtt)
{
	
		if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in sgz: v= %ld",oprAtt->command->opr1);
	}
	
		if(oprAtt->setIndexes[oprAtt->command->opr1]==false)
		{
				errx(1,"(sgz) Tried to read unset value at index(v arg): %ld\n",oprAtt->command->opr1);
	}

		//ram[v] >? 0
	if(oprAtt->ram_cells[oprAtt->command->opr1] > 0)
	{	
		//if sgz is the last command in a file and the above condition is true, i determine that as a not error state

		//47) sgz 2
		//.../end of commands/
		//

		if(lseek(oprAtt->fd,+sizeof(command_t),SEEK_CUR)==-1)
		{
			err(2,"lseek seek cur err in sgz operation\n"); 
		}


	}
}

//add (res,v1,v2);
//
//
void add(oprAttributes_t* oprAtt)
{
	if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in add: res= %ld",oprAtt->command->opr1);
	}

		if(oprAtt->command->opr2 < 0  || oprAtt->command->opr2 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in add: v1= %ld",oprAtt->command->opr2);
	}
	if(oprAtt->command->opr3 < 0  || oprAtt->command->opr3 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in add: v2= %ld",oprAtt->command->opr3);
	}





//v1 i v2 must be set
		if(oprAtt->setIndexes[oprAtt->command->opr2]==false)
		{
				errx(1,"(add) Tried to read unset value at index(v1 arg): %ld\n",oprAtt->command->opr2);
	}

		if(oprAtt->setIndexes[oprAtt->command->opr3]==false)
		{
				errx(1,"(add) Tried to read unset value at index(v2 arg): %ld\n",oprAtt->command->opr3);
	}


		oprAtt->ram_cells[oprAtt->command->opr1]=oprAtt->ram_cells[oprAtt->command->opr2] + oprAtt->ram_cells[oprAtt->command->opr3];

		oprAtt->setIndexes[oprAtt->command->opr1]=true;

}

//mul(res,v1,v2)
//
//
void mul(oprAttributes_t* oprAtt)
{
		if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in mul: res= %ld",oprAtt->command->opr1);
	}

		if(oprAtt->command->opr2 < 0  || oprAtt->command->opr2 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in mul: v1= %ld",oprAtt->command->opr2);
	}
	if(oprAtt->command->opr3 < 0  || oprAtt->command->opr3 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in mul: v2= %ld",oprAtt->command->opr3);
	}





//v1 i v2 must be set
		if(oprAtt->setIndexes[oprAtt->command->opr2]==false)
		{
				errx(1,"(mul) Tried to read unset value at index(v1 arg): %ld\n",oprAtt->command->opr2);
	}

		if(oprAtt->setIndexes[oprAtt->command->opr3]==false)
		{
				errx(1,"(mul) Tried to read unset value at index(v2 arg): %ld\n",oprAtt->command->opr3);
	}


		oprAtt->ram_cells[oprAtt->command->opr1]=oprAtt->ram_cells[oprAtt->command->opr2] * oprAtt->ram_cells[oprAtt->command->opr3];

		oprAtt->setIndexes[oprAtt->command->opr1]=true;

}


//div(res,v1,v2)
//
//
void div_func(oprAttributes_t* oprAtt)
{
	if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in div: res= %ld",oprAtt->command->opr1);
	}

	if(oprAtt->command->opr2 < 0  || oprAtt->command->opr2 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in div: v1= %ld",oprAtt->command->opr2);
	}
	if(oprAtt->command->opr3 < 0  || oprAtt->command->opr3 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in div: v2= %ld",oprAtt->command->opr3);
	}





//v1 i v2 must be set
		if(oprAtt->setIndexes[oprAtt->command->opr2]==false)
		{
				errx(1,"(div) Tried to read unset value at index(v1 arg): %ld\n",oprAtt->command->opr2);
	}

		if(oprAtt->setIndexes[oprAtt->command->opr3]==false)
		{
				errx(1,"(div) Tried to read unset value at index(v2 arg): %ld\n",oprAtt->command->opr3);
	}


		if(oprAtt->ram_cells[oprAtt->command->opr3]==0)
		{
			errx(1,"(div) Deviding by zero ! ");
		}

		oprAtt->ram_cells[oprAtt->command->opr1]=oprAtt->ram_cells[oprAtt->command->opr2] / oprAtt->ram_cells[oprAtt->command->opr3];

		oprAtt->setIndexes[oprAtt->command->opr1]=true;


}

//mod(res,v1,v2)
//
//
void mod(oprAttributes_t* oprAtt)
{
	if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in mod: res= %ld",oprAtt->command->opr1);
	
	}

	if(oprAtt->command->opr2 < 0  || oprAtt->command->opr2 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in mod: v1= %ld",oprAtt->command->opr2);
	}
	if(oprAtt->command->opr3 < 0  || oprAtt->command->opr3 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in mod: v2= %ld",oprAtt->command->opr3);
	}





//v1 i v2 must be set
		if(oprAtt->setIndexes[oprAtt->command->opr2]==false)
		{
				errx(1,"(mod) Tried to read unset value at index(v1 arg): %ld\n",oprAtt->command->opr2);
	}

		if(oprAtt->setIndexes[oprAtt->command->opr3]==false)
		{
				errx(1,"(mod) Tried to read unset value at index(v2 arg): %ld\n",oprAtt->command->opr3);
	}


		if(oprAtt->ram_cells[oprAtt->command->opr3]==0)
		{
			errx(1,"(mod) Deviding by zero ! ");
		}

		oprAtt->ram_cells[oprAtt->command->opr1]=oprAtt->ram_cells[oprAtt->command->opr2] % oprAtt->ram_cells[oprAtt->command->opr3];

		oprAtt->setIndexes[oprAtt->command->opr1]=true;

}


//sleep(v)
//
//
void sleep_func(oprAttributes_t* oprAtt)
{
		if(oprAtt->command->opr1 < 0  || oprAtt->command->opr1 >= (int64_t) oprAtt->header->ram_size)

	{
		errx(1,"Invalid index provided in sleep: v= %ld",oprAtt->command->opr1);
	
	}

		if(oprAtt->setIndexes[oprAtt->command->opr1]==false)
		{
				errx(1,"(sleep) Tried to read unset value at index(v arg): %ld\n",oprAtt->command->opr1);
	}
		
		//oprAtt->ram_cells[oprAtt->command->opr1]
		if(oprAtt->ram_cells[oprAtt->command->opr1] < 0)
		{
			errx(1,"(sleep) The value at ram[v] is %ld, can't sleep negative miliseconds\n",oprAtt->ram_cells[oprAtt->command->opr1]);
		}
		
		//printf("%ld mil\n",oprAtt->ram_cells[oprAtt->command->opr1]);
		sleep(oprAtt->ram_cells[oprAtt->command->opr1]/1000);
}



void findCommand(oprAttributes_t* oprAtt)
{
	// set (tar,val)
	if(oprAtt->command->opcode==0x95)
	{
		//call set func
		set(oprAtt);
		
	}
	// nop ()
	else if(oprAtt->command->opcode==0x00)
	{
		return;	
	}
	// load (to,from_ptr)
	else if(oprAtt->command->opcode==0x5d)
	{
		load(oprAtt);
	}
	// out (v)
	else if(oprAtt->command->opcode==0xc1)
	{
		out(oprAtt);
	}
	// store (to_ptr,from)
	else if(oprAtt->command->opcode==0x63)
	{
		store(oprAtt);
	}
	// jmp (idx)
	else if(oprAtt->command->opcode==0x91)
	{
		jmp(oprAtt);
	}
	// sgz (v)
	else if(oprAtt->command->opcode==0x25)
	{
		sgz(oprAtt);
	}
	// add (res,v1,v2)
	else if(oprAtt->command->opcode==0xAD)
	{
		add(oprAtt);
	}
	// mul (res,v1,v2)
	else if(oprAtt->command->opcode==0x33)
	{
		mul(oprAtt);
	}
	// div (res,v1,v2)
	else if(oprAtt->command->opcode==0x04)
	{
		div_func(oprAtt);
	}
	// mod (res,v1,v2)
	else if(oprAtt->command->opcode==0xB5)
	{
		mod(oprAtt);
	}
	// sleep (v)
	else if(oprAtt->command->opcode==0xBF)
	{
		sleep_func(oprAtt);
	}
	// wrong command inserted
	else 
	{	
		errx(1,"Command with invalid opcode occured!...  the wrong opcode:%d \n",oprAtt->command->opcode);
	}
}


int main(const int argc,const char* argv[])
{
	if(argc!=2)
	{
		errx(1,"Program must take only one argument! \n");
	}
	struct stat statFile;
	int fd=open(argv[1],O_RDONLY);
	if(fd==-1)
	{
		err(2,"Program couldn't open the file\n");
	}
	stat(argv[1],&statFile);
	
	if(!(statFile.st_size >= (long int)sizeof(header_t) && (statFile.st_size - 7)% 25 == 0) )
	{
		errx(1,"Program wasn't in right format ( 7 bytes for header and 25 bytes for each command\n");
	}
	


	header_t header;
	if(read(fd,&header,sizeof(header))!=sizeof(header))
	{
		err(2,"Program couldn't read header\n");
	}
	//printf("%s %d\n",header.magicWord,header.ram_size);
	if(validHeader(&header))
	{
		errx(1,"Header wasn't in right format ( magicWord had to be ORC )");
	}

	//printf("%ld\n",sizeof(command_t));
	
	int64_t* ram_cells =(int64_t*)malloc((int64_t)(header.ram_size*sizeof(int64_t)));
	if(ram_cells==NULL)
	{
		err(2,"Program couldn't allocate memory for ram_cells arr \n");
	}
	bool* setIndexes=(bool*)malloc((int64_t)(header.ram_size*sizeof(int64_t)));
	if(setIndexes==NULL)
	{
		err(2,"Program couldn't allocate memory for setIndexes arr \n");
	}
	if(memset(setIndexes,(bool)0,(int64_t)(header.ram_size*sizeof(int64_t)))==NULL)
	{
		err(2,"Error while initializing setIndexes arr with falses\n");
	}

	command_t command;
	int rd=0;
	
	oprAttributes_t oprAtt;
	oprAtt.fd=fd;
	oprAtt.header=&header;
	oprAtt.command=&command;
	oprAtt.ram_cells=ram_cells;
	oprAtt.setIndexes=setIndexes;
	while((rd=read(fd,&command,sizeof(command)))==sizeof(command))
	{
	//	printf("%d %ld %ld %ld\n",command.opcode,command.opr1,command.opr2,command.opr3);
		findCommand(&oprAtt);	
	}
	if(rd==-1)
	{
		err(2,"Program couldn't read a command\n");
	}




	free(ram_cells);
	free(setIndexes);
	close(fd);



}

