#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
int maximum,minimum;
int n;
int average;
int arr[100];
void* maxi() {
maximum=arr[0];
for (int i=1;i<n;i++) {
if (maximum<arr[i]) {
maximum=arr[i];
}
}
printf("Thread for maximum is created successfully\n");
printf("maximum is %d \n",maximum);
return NULL;
}
void* mini() {
minimum=arr[0];
for (int i=1;i<n;i++) {
if (minimum>arr[i]) {
minimum=arr[i];
}
}
printf("Thread for minimum is created successfully\n");
printf("minimum is %d \n",minimum);
return NULL;
}
void* avge() {
for (int i=0;i<n;i++) {
average+=(arr[i]);
}
average=average/n;
printf("Thread for average is created successfully\n");
printf("average is %d \n",average);
return NULL;
}
int main() {
pthread_t thread_id1,thread_id2,thread_id3;
int res;
printf("Enter no of Values: ");
scanf("%d",&n);
for (int i=0;i<n;i++) {
scanf("%d",&arr[i]);
}
res=pthread_create(&thread_id1,NULL,&maxi,NULL);
if (res!=0) {
perror("ERROR");
exit(EXIT_FAILURE);
}
res=pthread_create(&thread_id2,NULL,&mini,NULL);
if (res!=0) {
perror("ERROR");
exit(EXIT_FAILURE);
}
res=pthread_create(&thread_id3,NULL,&avge,NULL);
if (res!=0) {
perror("ERROR");
exit(EXIT_FAILURE);
}
pthread_exit(0);
}