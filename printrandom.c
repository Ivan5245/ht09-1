

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"random_source.h"
#include <dlfcn.h>



enum{
F1=10,
MODE=0x80000000,
A=1103515245,
C=12345,
NMAX=100000
};



int main(int argc,char*argv[]){
if(argc<3){fprintf(stderr,"To few arguments\n");exit(1);}
long long num=strtol(argv[2],NULL,F1);
void *buf = NULL;
if(num<0 || num>=NMAX){fprintf(stderr,"Incorrect args\n");exit(1);}

void *handle = dlopen(NULL, RTLD_LAZY);

if(!strncmp(argv[1],"linear",sizeof("linear"))){
       if(argc<4){fprintf(stderr,"Incorrect num of args\n");exit(1);}
	buf = dlsym(handle, "random_linear_factory");
       if(buf==0){fprintf(stderr,"Cant upload function\n");exit(1);}
}else if(!strncmp(argv[1],"random",sizeof("random"))){
	if(argc<3){fprintf(stderr,"Incorrect num of args\n");exit(1);}
	buf=dlsym(handle,"random_random_factory");
	if(buf==0){fprintf(stderr,"Cant upload function\n");exit(1);}
}else{
        fprintf(stderr,"Incorrect flag\n");exit(1);
	exit(1);
}



RandomSource*R=(((RandomSource * (*) (const char *) ) buf)(argv[3]));
for(int i=0;i<num ;++i){
	printf("%.10g\n",R->opt->next(R));
}
R->opt->destroy(R);






return 0;
}


