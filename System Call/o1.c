#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(){
	int fd,n;
	char buf[50];
	fd=open("text.txt",O_RDONLY);
	n=read(fd,buf,10);
	write(1,buf,10);
}
