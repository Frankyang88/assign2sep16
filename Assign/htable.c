#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"



struct htablerec {
int capacity;
int key_num;
int *freq_array;
char **string_array;
int *stats;
hashing_t method;
};

static unsigned int htable_step(htable h, unsigned int i_key) {
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
	free(h->freq_array);
	for(i=0;i<h->capacity;i++)
	free(h->string_array[i]);

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

	i=abs( i % j);
	
  	i=htable_step(h,i);

	if(h->string_array[i]==NULL){
		h->string_array[i]=emalloc((strlen(str)+1)*sizeof str[0]);
	
		strcpy(h->string_array[i],str);
		h->freq_array[i]=1;
		h->key_num++;
		return 1;
	}
	else if(strcmp(h->string_array[i],str)==0 ){
		
		h->freq_array[i]+=1;
		return h->freq_array[i];	
	}			
	else {
		while(1){
	
		if(h->string_array[i]==NULL)
		break;
		if(strcmp(h->string_array[i],str)==0)
		break;

		i+=htable_step(h,i);

		if(i>=h->capacity)
		i-=h->capacity;

		k++;
		if(k> h->capacity)
		 return 0;			
		}
	}
	if(h->string_array[i]==NULL){
		h->string_array[i]=emalloc((strlen(str)+1)*sizeof str[0]);
	
		strcpy(h->string_array[i],str);
		h->freq_array[i]=1;
		h->key_num++;
		return 1;
	}

	if(strcmp(h->string_array[i],str)==0 ){
		
		h->freq_array[i]+=1;
		return h->freq_array[i];	
	}	

	return 2;

}

htable htable_new(int capacity,hashing_t method){
	
	int i;
	htable result=malloc(sizeof *result);
	result->capacity = capacity;
	result-> key_num= 0;

	result->string_array= emalloc(capacity * sizeof (char*));
	result->freq_array =  emalloc(capacity * sizeof result->freq_array[0]);
	for(i=0;i<capacity;i++){

	result->string_array[i]=NULL;
	result->freq_array[i]=0;

	}
	
	result->method=method;	
	result->stats=emalloc(capacity*sizeof(result->stats[0]));

	return result; 
}

void htable_print(htable h, FILE *stream){
	int i;
	for(i=0;i<h->capacity;i++){
	if(h->freq_array[i]>0)
	  fprintf(stream," %d times of words: %s\n",h->freq_array[i],h->string_array[i]);	
	}
}


int htable_search(htable h, char *str)
	{
	int i=htable_word_to_int(str);
	int k=0;
	int j=h->capacity;
	i=abs( i % j);	

	while(h->string_array[i]!=NULL && strcmp(h->string_array[i],str)!=0){ 		
	
		i+=htable_step(h,i);

		if(i>=h->capacity)
		i-=h->capacity;

		k++;
		if(k>= h->capacity)
		 return 0;			
	}

	return h->freq_array[i];
}



