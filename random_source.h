typedef struct RandomSource  RandomSource;


typedef struct RandomSourceOperations{
RandomSource*(*destroy)(RandomSource*);
double (*next)(RandomSource*);
}RandomSourceOperations;


typedef struct RandomSource{
long long base;
RandomSourceOperations*opt;
int fd;
}RandomSource;

