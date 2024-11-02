#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"random_source.h"

enum{
F1=10,
MODE=0x80000000,
A=1103515245,
C=12345,
NMAX=100000
};
double linear_next(RandomSource*s){
	s->base=(s->base*A+C)%MODE;
	return (double)((s->base*1.0) / (1ULL<<31));
}

RandomSource* linear_destroy(RandomSource*s){
free(s->opt);
free(s);
return NULL;

}

RandomSource* random_linear_factory(char*s){
	if(!s){fprintf(stderr,"Incorrect N1\n");exit(1);}
	long long N1=strtoll(s,NULL,F1);

	if(N1<=0){fprintf(stderr,"Incorrect N1\n");exit(1);}
	RandomSource*res=(RandomSource*)calloc(1,sizeof(res));	
	RandomSourceOperations*op=(RandomSourceOperations*)calloc(1,sizeof(op));
	if(!res || !op){
	fprintf(stderr,"Segmentation falt\n");exit(1);}
	res->base=N1%MODE;
	op->next=linear_next;
	op->destroy=linear_destroy;
	res->opt=op;
	return res;
}
