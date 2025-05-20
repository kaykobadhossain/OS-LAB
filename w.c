#include<unistd.h>
int main(){
	int n;
	char b[50];
	n=read(0,b,50);
	write(1,b,n);
}
