#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"



struct htablerec {
int capacity;
int num_keys;
int *freq_array;
char **string_array;
int *stats;
hashing_t method;
};

unsigned int htable_step(htable h, unsigned int i_key) {
int j=h->capacity;
if(h->method==DOUBLE_H)
return 1 + (i_key % (j- 1));
else if(h->method==LINEAR_P)
return 1;
else printf("hashing undefine");

return 0;
}

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
static unsigned int htable_word_to_int(char *word){
	unsigned int result=0;

	while(*word !='\0'){
	result=(*word++ + 31*result);
	}

	return result;
}


int htable_insert(htable h, char *str){

	int k=0;
	int i=htable_word_to_int(str);
	int j=h->capacity;
	i=abs(i % (j-1));
	
  	i=htable_step(h,i);

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

		if(i>=h->capacity)
		i-=h->capacity;

		k++;
		if(k>=h->capacity){
			 
			 return 0;	
			}		
		}
	}

	if(0==strcmp(h->string_array[i],"")){
		h->string_array[i]=emalloc((strlen(str)+1)*sizeof str[0]);
	
		strcpy(h->string_array[i],str);
		h->freq_array[i]=1;
		h->stats[h->num_keys]=k;
		h->num_keys++;
		return 1;
	}

	if(strcmp(h->string_array[i],str)==0 ){
		
		h->freq_array[i]+=1;
		return h->freq_array[i];	
	}	

	return -1;

}

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

void htable_print(htable h, void (f)(int freq, char*word)){
	int i;
	for(i=0;i<h->capacity;i++){
	if(h->freq_array[i]>0)
	  f(h->freq_array[i],h->string_array[i]);
	}	  
}


int htable_search(htable h, char *str){
	int i=htable_word_to_int(str);
	int k=0;
	int j=h->capacity;
	i=abs( i % (j-1));	

	while(strcmp(h->string_array[i],str)!=0){ 		
	
		i+=htable_step(h,i);

		if(i>=h->capacity)
		i-=h->capacity;

		k++;
		if(k>= h->capacity)
		 return 0;			
	}

	return h->freq_array[i];
}

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
void print_stats_line(htable h, FILE *stream, int percent_full) {
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

