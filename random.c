#include"random_source.h"
#include<stdlib.h>
#include<stddef.h>
#include<fcntl.h>
#include<stdio.h>
#include<limits.h>
#include<unistd.h>
double rand_next(RandomSource*s){
	unsigned long long res;
        if(read(s->fd,&res,sizeof(res))!=sizeof(res)){
	fprintf(stderr,"Cant read file");exit(1);}	
	return (res*1.0)/ULLONG_MAX;	
}
RandomSource* rand_destroy(RandomSource*s){
free(s->opt);
close(s->fd);
free(s);

return NULL;
}

RandomSource*random_random_factory(const char*s){
int fd=open("/dev/urandom",O_RDONLY);
if(fd==-1){fprintf(stderr,"Can't open dev\n");exit(1);}
RandomSourceOperations*op=(RandomSourceOperations*)calloc(1,sizeof(op));
op->next=rand_next;
op->destroy=rand_destroy;
RandomSource*res=(RandomSource*)calloc(1,sizeof(res));
res->opt=op;
res->fd=fd;
return res;
}







