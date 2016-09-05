#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "mylib.h"
#include <getopt.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*usage:
 * print the usage of the program*/
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
/*record time info*/
clock_t start1,end1;
clock_t start2,end2;
/*count the unknow word*/
int count=0;
/*the input string from i stream*/
char word[256];

/*optional code*/
const char *optstring = "c:dpf:orh";
/*the parameter after -c, filename, string */
char* cvalue=NULL;
/*the parameter after -f, filename, string */
char* fvalue=NULL;
/*input option*/
char option;
tree b;
/*treetype:default bst*/
tree_t treetype=BST;
/*enable -o*/
int oflag=0;
/*enable -d*/
int dflag=0;
/*enable -c*/
int cflag=0;
/*enable -f*/
int fflag=0;

/*receive input from user,set up arguments*/
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

/*create a tree of type treetype*/
b= tree_new(treetype);

start1=clock();
/*read from stdin,insert into tree*/
while (getword(word, sizeof word, stdin) != EOF) {
	b=tree_insert(b, word);
}
end1 = clock();

if(cflag==1){
	/*open a file and read the file(decided by -c filename)
 	*then search the string in tree
	*if it fails to find the word, count number increase and print the unknown word to stdout*/
	FILE *file;
	file=fopen(cvalue,"r");
	start2=clock();
	while (getword(word, sizeof word, file) != EOF) {
		if(tree_search(b,word)==1){
			printf("%s\n",word);
			count++;	
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
	if(dflag==1){
	/*print out the tree depth*/
	printf("%d\n",tree_depth(b));
	}
	else {if(oflag==1){
				/*create or open a file,
 				* rewrite data to the file 
 				* whose name is defined from input -f parameter 
 				* or by default is tree-view.dot*/
				FILE *fp; 
				if(fflag==1){
					fp=fopen(fvalue, "wb+");

				}else{ 
					fp=fopen("tree-view.dot","ab+");
				}
				/*output to a file*/
				tree_output_dot(b, fp);
				/*close the file*/
				fclose(fp); 

			}
		}
	}

/*free memory*/
tree_free(b);

return 0;

}

