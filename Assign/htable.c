#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"

/*htable structure*/
struct htablerec {
int capacity;
int num_keys;
int *freq_array;
char **string_array;
int *stats;
hashing_t method;
};


/*static method declaration*/
static void print_stats_line(htable h, FILE *stream, int percent_full); 

/*hashfunc1:
 * the first hashfunction used in the htable*/
static unsigned int hashfunc1(htable h, int i){
	return abs(i%(h->capacity));
}


/*htable step:
 * hash table step methods linear hashing or double hashing are different in steps*/
unsigned int htable_step(htable h, unsigned int i_key) {
int j=h->capacity;
if(h->method==DOUBLE_H)
return (i_key % (j- 1));
else if(h->method==LINEAR_P)
return 1;
else printf("hashing undefine");

return 0;
}

/* htable free:
 * free the htable , statistics,freq array and string array
 * certainly free htable's inner variables before releasing htable itself*/
void htable_free(htable h){
	int i;

	
	for(i=0;i<h->capacity;i++){
		if(h->freq_array[i]>0)
		free(h->string_array[i]);
	}
	free(h->stats);
	free(h->freq_array);
	free(h->string_array);
	free(h);
}

/*htable word to int:
 * method covert a string to a integer*/
static unsigned int htable_word_to_int(char *word){
	unsigned int result=0;

	while(*word !='\0'){
	result=(*word++ + 31*result);
	}

	return result;
}

/*htable insert:*/
int htable_insert(htable h, char *str){

	int k=0;
	int i=htable_word_to_int(str);

	/*calculate the first address of hash function*/
	i=hashfunc1(h,i);
	
	/*compare the key with that in hashtable, 
 	* 1)if the cell is unoccupied, insert key into this address
 	* set collision as 0,increase key number by 1, set key freq as 1
 	* 2)if the key is the same as that in hashtable
 	* increase the related freq by 1 and return the key's frequency
 	* 3)while loop, it will take a step to another address, 
 	* try to find an address that it is unoccupied or it host the same key
 	* if it fails for the same number as its capacity, it will break automatically and stop
 	* if it find the expected cell, it will break and do other operation as explained below*/
	if(strcmp(h->string_array[i],"")==0){
		h->string_array[i]=emalloc((strlen(str)+1)*sizeof str[0]);
	
		strcpy(h->string_array[i],str);
		h->freq_array[i]=1;
		h->stats[h->num_keys]=0;
		h->num_keys++;
		return 1;
	}
	else if(strcmp(h->string_array[i],str)==0 ){
		
		h->freq_array[i]+=1;
		return h->freq_array[i];	
	}			
	else {
		while(1){
		
		if(0==strcmp(h->string_array[i],"")){
			break;
			
		}
		if(strcmp(h->string_array[i],str)==0){
			break;
		}

		i+=htable_step(h,i);

		i = i%(h->capacity-1);

		k++;
		if(k>=h->capacity){
			 
			 return -1;	
			}		
		}
	}

	/* if find a unoccupied place, insert the key into the new address 
 	* record the number of collision and set up word frequency,increase key number*/
	if(0==strcmp(h->string_array[i],"")){
		h->string_array[i]=emalloc((strlen(str)+1)*sizeof str[0]);
	
		strcpy(h->string_array[i],str);
		h->freq_array[i]=1;
		h->stats[h->num_keys]=k;
		h->num_keys++;
		return 1;
	}

	/*compare input key with that in hashtable 
 	* if they are the same,related frequency increase by 1 
 	* and return its frequency */
	if(strcmp(h->string_array[i],str)==0 ){
		
		h->freq_array[i]+=1;
		return h->freq_array[i];	
	}	

	return -1;

}


/*create a htable, initiate the related variables and memory allocation*/
htable htable_new(int capacity,hashing_t method){
	
	int i;
	htable result=malloc(sizeof *result);
	result->capacity = capacity;
	result-> num_keys= 0;

	result->string_array= emalloc(capacity * sizeof (char*));
	result->freq_array =  emalloc(capacity * sizeof result->freq_array[0]);
	result->stats	   = emalloc(capacity*sizeof(int));
	for(i=0;i<capacity;i++){

	result->string_array[i]="";
	result->freq_array[i]=0;
	result->stats[i]=0;

	}
	
	result->method=method;	
	return result; 
}

/*print the word's frequency and the word*/
void htable_print(htable h, void (f)(int freq, char*word)){
	int i;
	for(i=0;i<h->capacity;i++){
	if(h->freq_array[i]>0)
	  f(h->freq_array[i],h->string_array[i]);
	}	  
}


/*htable_search:
 * search a string in the htable, the similar operation as insertion 
 *if find the input string,return its frequency otherwise return 0*/
int htable_search(htable h, char *str){
	int i=htable_word_to_int(str);
	int k=0;

	i=hashfunc1(h, i);	

	while(strcmp(h->string_array[i],str)!=0){ 		
	
		i+=htable_step(h,i);
		
		
		i=i%(h->capacity-1);

		/*k is a counter. If the programs fail to find the string after a certain number of trials,
 		*it will break out. Here the trials are limited to the table's capacity*/
		k++;
		if(k>= h->capacity)
		 return 0;			
	}

	return h->freq_array[i];
}

/*htable print entire table:
 * print out the hash table position,frequency ,statistics and string*/
void htable_print_entire_table(htable h){
int i;

printf("  Pos  Freq  Stats  Word\n");
printf("--------------------------------------\n");
for(i=0;i<h->capacity;i++)
fprintf(stderr,"%5d %5d %5d   %s\n",i,h->freq_array[i],h->stats[i],h->string_array[i]);
}

/* These functions should be added to your htable.c file */


/**
 * Prints out a table showing what the following attributes were like
 * at regular intervals (as determined by num_stats) while the
 * hashtable was being built.
 *
 * @li Percent At Home - how many keys were placed without a collision
 * occurring.
 * @li Average Collisions - how many collisions have occurred on
 *  average while placing all of the keys so far.
 * @li Maximum Collisions - the most collisions that have occurred
 * while placing a key.
 *
 * @param h the hashtable to print statistics summary from.
 * @param stream the stream to send output to.
 * @param num_stats the maximum number of statistical snapshots to print.
 */
void htable_print_stats(htable h, FILE *stream, int num_stats) {

   int i;

   fprintf(stream, "\n%s\n\n", 
           h->method == LINEAR_P ? "Linear Probing" : "Double Hashing"); 
   fprintf(stream, "Percent   Current   Percent    Average      Maximum\n");
   fprintf(stream, " Full     Entries   At Home   Collisions   Collisions\n");
   fprintf(stream, "-----------------------------------------------------\n");
   for (i = 1; i <= num_stats; i++) {
      print_stats_line(h, stream, 100 * i / num_stats);
   }
   fprintf(stream, "-----------------------------------------------------\n\n");
}

/**
 * Prints out a line of data from the hash table to reflect the state
 * the table was in when it was a certain percentage full.
 * Note: If the hashtable is less full than percent_full then no data
 * will be printed.
 *
 * @param h - the hash table.
 * @param stream - a stream to print the data to.
 * @param percent_full - the point at which to show the data from.
 */
static void print_stats_line(htable h, FILE *stream, int percent_full) {
   int current_entries = h->capacity * percent_full / 100;
   double average_collisions = 0.0;
   int at_home = 0;
   int max_collisions = 0;
   int i = 0;

   if (current_entries > 0 && current_entries <= h->num_keys) {
      for (i = 0; i < current_entries; i++) {
         if (h->stats[i] == 0) {
            at_home++;
         } 
         if (h->stats[i] > max_collisions) {
            max_collisions = h->stats[i];
         }
         average_collisions += h->stats[i];
      }
    
      fprintf(stream, "%4d %10d %10.1f %10.2f %11d\n", percent_full, 
              current_entries, at_home * 100.0 / current_entries,
              average_collisions / current_entries, max_collisions);
   }
}

