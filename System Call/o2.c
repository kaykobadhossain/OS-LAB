#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(){
        int fd,fd1,n;
        char buf[50];
        fd=open("text.txt",O_RDONLY);
        n=read(fd,buf,50);
        fd1=open("test2.txt",O_CREAT|O_WRONLY,0642);
        write(fd1,buf,n);
}
