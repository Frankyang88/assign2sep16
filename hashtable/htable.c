#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htable.h"
#include "mylib.h"



struct htable {
int capacity;
int key_num;
int *freq_array;
char **string_array;
};

static unsigned int htable_step(htable h, unsigned int i_key) {
int j=h->capacity;
return 1 + (i_key % (j- 1));
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

htable htable_new(int capacity){
	

	htable result=malloc(sizeof result);
	result->capacity = capacity;
	result-> key_num= 0;

	result->string_array= emalloc(capacity * sizeof (char*));
	result->freq_array =  emalloc(capacity * sizeof result->freq_array[0]);
		
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



