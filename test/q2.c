#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void* fact(void* t){
int i,n = *(int *)t;
for(i=n;i>1;i--)
n=n*(i-1);
printf("Factorial of %d = %d\n",*(int*)t,n);
return NULL;
}
int main(){
pthread_t thread_id;
int n,r;
printf("Enter the number : \n");
scanf("%d",&n);
r = pthread_create(&thread_id, NULL, &fact, &n);
if(r!=0){
perror("Error");
exit(EXIT_FAILURE);
}
pthread_exit(0);
}