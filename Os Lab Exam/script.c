 #include<unistd.h>
 #include<fcntl.h>
 #include<sys/types.h>
 #include<sys/stat.h>
 int main(){
 	int fd,fd1,n;
     char buf[50];
     n=read(0,buf,50);
     fd1=open("test3.txt",O_CREAT|O_WRONLY,0642);
     write(fd1,buf,n);
}