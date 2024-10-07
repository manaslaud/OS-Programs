#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<ctype.h>
char a[26];
void* server(){
printf("Server : \n");
int i;
char p = 'a';
for(i=0;i<26;i++){
a[i] = p;
p++;
}
for(i=0;i<26;i++){
printf("%c ",a[i]);
}
printf("\n");
return NULL;
}
void* client(){
printf("\n");
printf("Client : \n");
int i;
for(i=0;i<26;i++){
printf("%c ",toupper(a[i]));
}
printf("\n");
return NULL;
}
int main(){
pthread_t thread_id;
int r,s;
r = pthread_create(&thread_id, NULL, &server, NULL);
s = pthread_create(&thread_id, NULL, &client, NULL);
if(r!=0 && s!=0){
perror("Error");
exit(EXIT_FAILURE);
}
pthread_exit(0);
}