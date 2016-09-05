#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <time.h>


static void print_info(int freq,char *word){
	printf("%-4d %s \n",freq,word);
}
void usage(){
printf("Usage: ./htable-main [Option] <Stdin>\n");
printf("\n");
printf("Perform various operations using a hash table.\n");
printf("By default,words are read from stdin and added to the hash table,\n");
printf("before being printed out alongside their frequencies to stdout\n");
printf("\n");
printf("-c FILENAME  Check spelling of words in FILENAME using words\n");
printf("             from stdin as dictionary.  Print unknown words to\n");
printf("             stdout, timing info & count to stderr (ignore -p)\n");
printf("-d           Use double hashing (linear probing is the default)\n");
printf("-e           Display entire contents of hash table on stderr\n");
printf("-p           Print stats info instead of frequencies & words\n");
printf("-s SNAPSHOTS Show SNAPSHOTS stats snapshots (if -p is used)\n");
printf("-t TABLESIZE Use the first prime >= TABLESIZE as htable size\n");
printf("\n");
printf("-h           Display this message\n");

}

unsigned int first_prime(unsigned int seed){
    unsigned int s=seed;
    int j;	
	
    while(1) 
    {        
	for (j=2; j*j<=s; j++)
        {
            if (s % j == 0) 
            break;
	    else if((j+1)*(j+1) > s )
		return s;
        }
	s++;
    }
	
    return 0;
}




int main(int argc, char ** argv){
clock_t start1,end1;
clock_t start2,end2;

int count=0;
char word[256];

const char *optstring = "c:deps:t:h";
char* cvalue=NULL;
int svalue=10;
unsigned int tvalue=113;
char option;
htable h;
hashing_t method=LINEAR_P;
int eflag=0;
int cflag=0;
int sflag=0;
int pflag=0;
int tflag=0;
while((option = getopt(argc,argv,optstring))!=EOF){
	switch(option){
	case 'c':cflag=1;cvalue=optarg;break; /*indicate a filename*/
	case 'd':method=DOUBLE_H;break; /*apply double hashing*/
	case 'e':eflag=1;break;     /*enable print entire hash table*/
	case 'p':pflag=1;break;
	case 's':sflag=1;svalue=atoi(optarg);break;
	case 't':tflag=1;tvalue=atoi(optarg);break; /*set table size*/
	case 'h':usage();return 0;
	default :usage();return 0;
	}
}

/*if get t parameter, reset table size*/
if(tflag==1)
tvalue=first_prime(tvalue);

h=htable_new(tvalue,method);

start1=clock();
while (getword(word, sizeof word, stdin) != EOF) {
	htable_insert(h, word);
}
end1 = clock();

if(eflag==1){
	htable_print_entire_table(h);
}
if(cflag==1){
	FILE *file;
	file=fopen(cvalue,"r");
	start2=clock();
	while (getword(word, sizeof word, file) != EOF) {
		
		if(htable_search(h, word)==0){
			count++;
			printf("%s\n",word);
		}
	}

	fclose(file);
	end2 =clock();
	
	fprintf(stderr,"Fill time	: %f\n",(end1-start1)/(double)CLOCKS_PER_SEC);	
	fprintf(stderr,"Search time	: %f\n",(end2-start2)/(double)CLOCKS_PER_SEC);	
	fprintf(stderr,"Unknown words	= %d\n", count);	

	
}
else {
	if(pflag==1){
		int tmp=10;
		if(sflag==1)
		htable_print_stats(h,stdout,svalue);
		else htable_print_stats(h,stdout,tmp);
	
	}
	else htable_print(h, print_info);
}

htable_free(h);

return EXIT_SUCCESS;

}
