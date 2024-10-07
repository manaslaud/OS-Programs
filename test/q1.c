#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
void* q1(){
printf("Thread is successfully created\n");
return NULL;
}
int main(){
pthread_t thread_id;
int r;
r = pthread_create(&thread_id, NULL, &q1, NULL);
if(r!=0){
perror("ERROR1");
exit(EXIT_FAILURE);
}
r = pthread_join(thread_id, NULL);
if(r!=0){
perror("ERROR2");
exit(EXIT_FAILURE);
}
pthread_exit(0);
}