#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int my_strlen( char *source ){
    
    int counter = 0;
    while(*source++){
        counter++;
    }
    return counter;

}

char * my_strncpy(char *dest, char *source, int n){

	int counter = 0;
	while(counter <  n && source[counter]){
		dest[counter++] = source[counter];
	}

    int i;
    for(i = counter; i <= n; i++){
        dest[i] = 0;
    }
	// dest[strlen(dest)] = 0; strncpy doesnt auto null terminate

	return dest;

}

char *my_strcpy(char *dest, char *source){
    dest[strlen(source)] = 0;
    my_strncpy(dest, source, strlen(source));
}

char * my_strncat( char *dest, char *source, int n){

    int start_point = strlen(dest);

    int i;
    for (i = 0; i < n && source[i]; i++){
        dest[start_point + i] = source[i];
    }

    dest[strlen(dest) + n + 1] = 0;

    return dest;

}

int my_strcmp( char *s1, char *s2 ){

    int i = 0;
    while(s1[i]){
        if(s1[i] != s2[i]){
            return s1[i] - s2[i];
        }
        i++;
    }
    return s1[i] - s2[i];

}

char * my_strchr( char *s, char c ) {
    
    while(*s++){
        if(*s == c){
            return s;
        }
    }

    return 0;

}

int main(){

    char a[25] = "cat";
    char b[25] = "dog";
    char c[25] = "catdog";

    printf("s1: [%s]\n", a);
    printf("s2: [%s]\n", b);
    printf("s3: [%s]\n", c);
    printf("\n");
    
    printf("---------------------------\n");
    printf("Testing strlen(s3):\n");
    printf("[standard]: [%ld]\n", strlen(c));
    printf("[mine]: [%d]\n", my_strlen(c));
    printf("\n");
    printf("Testing strlen(s3):\n");
    printf("[standard]: [%ld]\n", strlen(a));
    printf("[mine]: [%d]\n", my_strlen(a));
    printf("---------------------------\n");
    printf("\n");

    printf("---------------------------\n");
    printf("Testing strcpy(s2, s1):\n");
    printf("[standard]: [%s]\n", strcpy(b, a));
    strcpy(b, "dog"); // reset s2
    printf("[mine]: [%s]\n", my_strcpy(b, a));
    strcpy(b, "dog"); // reset s2
    printf("\n");
    printf("Testing strcpy(s3, s2):\n");
    printf("[standard]: [%s]\n", strcpy(c, b));
    strcpy(c, "catdog"); // reset s3
    printf("[mine]: [%s]\n", my_strcpy(c, b));
    strcpy(c, "catdog"); // reset s3
    printf("---------------------------\n");
    printf("\n");

    printf("---------------------------\n");
    printf("Testing strncat(s1, s3, 3):\n");
    printf("[standard]: [%s]\n", strncat(a, c, 3));
    strcpy(a, "cat"); // reset s1
    printf("[mine]: [%s]\n", my_strncat(a, c, 3));
    strcpy(a, "cat"); // reset s1
    printf("\n");
    printf("Testing strncat(s1, s2, 2):\n");
    printf("[standard]: [%s]\n", strncat(a, b, 2));
    strcpy(a, "cat"); // reset s1
    printf("[mine]: [%s]\n", my_strncat(a, b, 2));
    strcpy(a, "cat"); // reset s1
    printf("---------------------------\n");
    printf("\n");

    printf("---------------------------\n");
    printf("Testing strncmp(\"ab\", \"abc\"):\n");
    printf("[standard]: [%d]\n", strcmp("ab", "abc"));
    printf("[mine]: [%d]\n", my_strcmp("ab", "abc"));
    printf("\n");
    printf("Testing strncmp(\"abc\", \"ab\"):\n");
    printf("[standard]: [%d]\n", strcmp("abc", "ab"));
    printf("[mine]: [%d]\n", my_strcmp("abc", "ab"));
    printf("\n");
    printf("Testing strncmp(\"abc\", \"abc\"):\n");
    printf("[standard]: [%d]\n", strcmp("abc", "abc"));
    printf("[mine]: [%d]\n", my_strcmp("abc", "abc"));
    printf("---------------------------\n");
    printf("\n");

    printf("---------------------------\n");
    printf("Testing strchr(s1, 'o'):\n");
    printf("[standard]: [%s]\n", strchr(a, 'o'));
    printf("[mine]: [%s]\n", my_strchr(a, 'o'));
    printf("\n");
    printf("Testing strchr(s3, d):\n");
    printf("[standard]: [%s]\n", strchr(c, 'd'));
    printf("[mine]: [%s]\n", my_strchr(c, 'd'));
    printf("---------------------------\n");

    return 0;
}