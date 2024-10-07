#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main(void){
pid_t pid;
pid = fork();
int status;
if(pid==-1){
perror("Error");
exit(EXIT_FAILURE);
}
else if(pid==0){
int n;
printf("Executing child process\n");
printf("Enter a number : ");
scanf("%d",&n);
while(n>1){
printf("%d ",n);
if(n%2==0){
n = n/2;
}
else if(n%2!=0){
n = 3*n+1;
}
}
printf("%d",1);
printf("\n");
}
else{
pid_t i;
i = wait(0);
printf("Wait is over\n");
printf("Exiting the program\n");
}
return 0;
}