#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "mylib.h"
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <time.h>


void usage(){
printf("Usage: ./tree-main [Option]... <Stdin>\n");
printf("\n");
printf("Perform various operations using a binary tree.\n");
printf("By default,words are read from stdin and added to the hash table,\n");
printf("before being printed out alongside their frequencies to stdout\n");
printf("\n");
printf("-c FILENAME  Check spelling of words in FILENAME using words\n");
printf("             from stdin as dictionary.  Print timing and unknown words to\n");
printf("             stderr(ignore -d & -o)\n");
printf("-d           only print the tree depth(ignore -o)\n");
printf("-f FILENAME  write DOT output to FILENAME(if -o given)\n");
printf("-o           Output the tree in DOT form to file 'tree-view.dot'\n");
printf("-r 	     Make the tree and RBT (the default is a BST)\n");
printf("-h           Display this message\n");

}


int main(int argc, char ** argv){
clock_t start1,end1;
clock_t start2,end2;

int count=0;
char word[256];

const char *optstring = "c:dpf:orh";
char* cvalue=NULL;
char* fvalue=NULL;
char option;
tree b;
tree_t treetype=BST;
int oflag=0;
int dflag=0;
int cflag=0;
int fflag=0;

while((option = getopt(argc,argv,optstring))!=EOF){
	switch(option){
	case 'c':cflag=1;cvalue=optarg;break; /*indicate a filename*/
	case 'd':dflag=1;break; /*print tree depth*/
	case 'o':oflag=1;break;     /*tree dot output*/
	case 'f':fflag=1;fvalue=optarg;break;/*indicate output file name*/
	case 'r':treetype= RBT;break; /*set tree type*/
	case 'h':usage();return 0;
	default :usage();return 0;
	}
}

b= tree_new(treetype);

start1=clock();
while (getword(word, sizeof word, stdin) != EOF) {
	b=tree_insert(b, word);
}
end1 = clock();

if(cflag==1){
	FILE *file;
	file=fopen(cvalue,"r");
	start2=clock();
	while (getword(word, sizeof word, file) != EOF) {
		if(tree_search(b,word)==1){
			printf("%s\n",word);
			count++;	
		}
	}
	fclose(file);
	end2 =clock();
	fprintf(stderr,"Fill time	: %f\n",(end1-start1)/(double)CLOCKS_PER_SEC);	
	fprintf(stderr,"Search time	: %f\n",(end2-start2)/(double)CLOCKS_PER_SEC);	
	fprintf(stderr,"Unknown words	= %d\n", count);		
}
else {
	if(dflag==1){
	printf("%d\n",tree_depth(b));
	}
	else {if(oflag==1){
				FILE *fp; 
				if(fflag==1){
					fp=fopen(fvalue, "wb+");

				}else{ 
					fp=fopen("tree-view.dot","ab+");
				}

				tree_output_dot(b, fp);
				fclose(fp); 

			}
		}
	}

tree_free(b);

return 0;

}

