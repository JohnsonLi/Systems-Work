#include <stdio.h>
#include <string.h>

int mystrlen( char *source ){
	int counter = 0;
	while(*source++){
		counter++;
	}
	return counter;
}

char *mystrncat(char *dest, char *source, int n){
	int enddest = mystrlen(dest);
	int counter = 0;
	while(counter <  n){
		dest[enddest++] = source[counter++];
	}
	dest[strlen(dest)] = 0;
	return dest;
}

char *mystrcat(char *dest, char *source){
	return mystrncat(dest, source, mystrlen(source));
}

char *mystrncpy(char *dest, char *source, int n){
	int counter = 0;
	while(counter <  n){
		dest[counter++] = source[counter];
	}
	dest[strlen(dest)] = 0;
	return dest;
}

char *mystrcpy(char *dest, char *source){
    mystrncpy(dest, source, mystrlen(source))
}

//char *mystrchr( char *s, char c ){
//	while(*s){
//		printf("%d\n", c);
//		if(*s++ == c){
//			return s;
//		}
//	}
//	return NULL;
//} //DOES NOT WORK IDK HOW TO FIX

int main(){
    char str1[50] = "doggo";
    char str2[50] = "abcdefghijk";
    printf("length of %s: %d\n", str1, mystrlen(str1));
    printf("strntest of dest:%s src:%s result:%s \n", str1, str2, mystrncat(str1, str2, 5));
    return 0;
}
