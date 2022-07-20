#include<err.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdint.h>

struct trinity{
	char name[8];
	uint32_t off;
	uint32_t len;
}__attribute__((packed));

int main(const int argc, const char* argv[]){
	if(argc != 2){
		errx(1,"Input error.");
	}
	int fd;
	fd = open(argv[1],O_RDONLY);
	if(fd == -1){
		err(2,"Error in open.");
	}
	struct stat fs;
	if(fstat(fd,&fs) == -1){
		err(3,"Error in stat.");
	}
	if(fs.st_size % sizeof(struct trinity) != 0){
		errx(4,"Error in file structure.");
	}
	int n = fs.st_size/sizeof(struct trinity);
	if(n>8){
		errx(5,"Error, file too big.");
	}
	int a[2];
	if(pipe(a) == -1){
		err(6,"Error in pipe.");
	}
	pid_t ch;
	for(int i = 0; i < n; i++){
		ch = fork();
		if(ch == -1){
			err(7,"Error in fork.");
		}
		if(ch == 0)
			break;
	}
	if(ch == 0){
		close(a[0]);
		uint16_t r=0;
		struct trinity tbuf;
		if(read(fd,&tbuf,sizeof(tbuf)) != sizeof(tbuf)){
			err(8,"Error in reading from input.");
		}
		int fd1 = open(tbuf.name,O_RDONLY);
		if(fd1 == -1){
			err(2,"Error open in child.");
		}
		//check fd1 file structure
		if(lseek(fd1,tbuf.off*sizeof(uint16_t),SEEK_SET) == -1){
			err(9,"Error in lseek.");
		}
		for(uint32_t i = 0; i < tbuf.len; i++){
			uint16_t b;
			if(read(fd1,&b,sizeof(uint16_t)) != sizeof(uint16_t)){
				err(8,"Error in read.");
			}
			r ^= b;
		}
		if(write(a[1],&r,sizeof(uint16_t)) != sizeof(uint16_t)){
			err(10,"Error in write.");
		}
		exit(0);
	}
	close(a[1]);
	uint16_t result=0;
	for(int i = 0; i < n; i++){
		uint16_t c;
		if(read(a[0],&c,sizeof(uint16_t)) != sizeof(uint16_t)){
			err(8,"Error from reading from pipe.");
		}
		result ^= c;
	}
	fprintf(stdout,"%04x\n",result);
	exit(0);
}

