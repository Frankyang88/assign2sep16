#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


int first_prime(int seed){
    int s=seed;
	
	
    while(1) 
    {        
	for (int j=2; j*j<=s; j++)
        {
            if (s % j == 0) 
            break;
	    else if((j+1)*(j+1) > s)
		return s;
        }
	s++;
    }
	
    return 0;
}

int main(){
int a;
a = 100;
a=first_prime(a);
printf("%d\n",a);
a = 78;
a=first_prime(a);
printf("%d\n",a);
a = 30;
a=first_prime(a);
printf("%d\n",a);
a = 42;
a=first_prime(a);
printf("%d\n",a);
a = 50;
a=first_prime(a);
printf("%d\n",a);
a = 81;
a=first_prime(a);
printf("%d\n",a);
a = 18;
a=first_prime(a);
printf("%d\n",a);
a = 3;
a=first_prime(a);
printf("%d\n",a);
a = 12;
a=first_prime(a);
printf("%d\n",a);
a = 62;
a=first_prime(a);
printf("%d\n",a);



return 0;

}
