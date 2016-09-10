#include <stdio.h>
#include <stdlib.h>
#include "htable.h"
#include "mylib.h"
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*print info:
 * @param freq is frequency of words
 * @param word is the string 
 * static method print word and its frequency of htable*/
static void print_info(int freq,char *word){
	printf("%-4d %s\n",freq,word);
}

/*usage: 
 * print the usage of the program*/
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

/*first prime:return value is the first prime after the input integer
 * @param seed: input integer
 * Given a integer,it will give the first prime after that integer
 * (include itself)*/
unsigned int first_prime(unsigned int seed){
    unsigned int s=seed;
    unsigned int j;	
    /* give a number s, from 2 to sqrt(s), if it is not a prime, 
    * there is a number k that make s%k = 0; otherwise,it is a prime number.
    * */	
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



/*htable main:
 *offer operation as stated in usage()
 * */
int main(int argc, char ** argv){

clock_t start1,end1;
clock_t start2,end2;
/*count the unknow word*/
int count=0;
char word[256];

const char *optstring = "c:deps:t:h";

/*the parameter after -c, filename, string */
char* cvalue=NULL;
/*the parameter after -s, integer*/
int svalue=10;

unsigned int tvalue=113;
char option;
htable h;
hashing_t method=LINEAR_P;

/*flag set, decide the priority 
 * and execution order of the program*/
/*enable -e*/
int eflag=0;
/*enable -c*/
int cflag=0;
/*enable -s*/
int sflag=0;
/*enable -p*/
int pflag=0;
/*enable -t*/
int tflag=0;

/*receive input from user,set up arguments*/
while((option = getopt(argc,argv,optstring))!=EOF){
	switch(option){
	case 'c':cflag=1;cvalue=optarg;break;
	case 'd':method=DOUBLE_H;break; 
	case 'e':eflag=1;break;     
	case 'p':pflag=1;break;
	case 's':sflag=1;svalue=atoi(optarg);break;
	case 't':tflag=1;tvalue=atoi(optarg);break; 
	case 'h':usage();return 0;
	default :usage();return 0;
	}
}


if(tflag==1)
tvalue=first_prime(tvalue);

h=htable_new(tvalue,method);

start1=clock();

while (getword(word, sizeof word, stdin) != EOF) {
	if(htable_insert(h, word)==-1)
	printf("word: %s fail to insert into hash table!\n",word);
	
}
end1 = clock();


if(eflag==1){
	/*print entire table*/
	htable_print_entire_table(h);
}
if(cflag==1){
	
   /*open a file and read the file(decided by -c filename)
   *then search the string in htable
   *if it fails to find the word, 
   *count number increase and print the unknown word to stdout*/
   FILE *file;
   file=fopen(cvalue,"r");
   start2=clock();
   while (getword(word, sizeof word, file) != EOF) {		
	if(htable_search(h, word)==0){
		count++;
		printf("%s\n",word);
	}
   }
    /*close the file*/
   fclose(file);
   end2 =clock();
   /*print statics to std err*/
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


/*free memory*/
htable_free(h);

return EXIT_SUCCESS;

}
