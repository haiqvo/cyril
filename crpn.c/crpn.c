/* 
 * File:   main.c
 * Author: Hai Vo
 *
 * Created on October 23, 2012, 11:42 PM
 */
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
/*
 * 
 */
int main(int argc, char** argv) {
    #define STACK_SIZE 16
    #define EMPTY (-1)
    double stack[STACK_SIZE];
    int top = EMPTY;
    
    assert (argc == 1);
    printf ("%s:\n", argv[0]);
    for(;;){
        char buffer[4096];
        int scanct = scanf ("%4095s", buffer);
        if(scanct == EOF) {
            printf("EOF\n");
            break;
        }
        assert (scanct == 1);
        size_t length = strlen(buffer);
        
        if (buffer[0] == '#') {
            scanf ("%4095[^\n]", buffer);
            continue;
        }
        
        char *endptr = NULL;
        double temp = strtod (buffer, &endptr);
        int i;
        if(*endptr == '\0') {      
            ++top;
            if(top>15){
                printf("Stack Overflow\n", errno);
            }else{
            stack[top] = temp;
            }
            //printf("this is the top:%s\n", top);
            //printf ("%22.15g %4ld \"%s\"\n", top, length, buffer);
        }else { 
            
            switch(buffer[0]){
                case '+':
                    if(top-1<0){
                        printf("Stack Underflow", errno);
                    }
                        stack[top-1] = stack[top]+stack[top-1];
                        top--;
                        break;
                case '-':
                    if(top-1<0){
                        printf("Stack Underflow", errno);
                    }
                        stack[top-1] = stack[top]-stack[top-1];
                        top--;
                        break;
                case '*':
                    if(top-1<0){
                        printf("Stack Underflow", errno);
                    }
                        stack[top-1] = stack[top]*stack[top-1];
                        top--;
                        break;
                case '/':
                    if(top-1<0){
                        printf("Stack Underflow", errno);
                    }
                        stack[top-1] = stack[top]/stack[top-1];
                        top--;
                        break;
                case '~':
                        for(i = 15; i>=0; i--){
                            stack[i] = 0;
                        }
                        top = EMPTY;
                        break;
                case ';':
                        for(i = top; i>=0; i--){
                            printf("%22.15g \n", stack[i]);
                        }
                        break;
                default:
                        printf("improper command\n", errno);
                        break;
                
            }
            //printf ("%-22s %4ld \"%s\", endptr->\"%s\"\n",
            //        "not numeric", length, buffer, endptr);  
        }
    }

    return (EXIT_SUCCESS);
}

