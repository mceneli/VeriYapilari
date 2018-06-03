//This program read arithmetic Operations from input.txt
//example " a = 2 ; and b = ( 2 * a ) / 2 ; " and calculate the operands with using stack.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// Stack
struct Stack{
    int top;
    unsigned capacity;
    int* array;
};
// This Function creates stack
struct Stack* createStack( unsigned capacity ){
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
	if (!stack) 
        return NULL;

    stack->top = -1;
    stack->capacity = capacity;
	stack->array = (int*) malloc(stack->capacity * sizeof(int));
	if (!stack->array)
        return NULL;
    return stack;
}
// Checks stack for is stack empty
int isEmpty(struct Stack* stack){
    return stack->top == -1 ;
}

char peek(struct Stack* stack){
    return stack->array[stack->top];
}

char pop(struct Stack* stack){
    if (!isEmpty(stack))
        return stack->array[stack->top--] ;
    return '$';
}

void push(struct Stack* stack, char op){
    stack->array[++stack->top] = op;
}

void printStack(struct Stack* stack){
	int i;
	for(i=0;i<=stack->top;i++){
		printf("%c ",stack->array[i]);
	}
}

void printStackInt(struct Stack* stack){
	int i;
	printf("Yigin:\t");
	for(i=0;i<=stack->top;i++){
		printf("%d ",stack->array[i]);
	}
}

// checks is the given character is operand
int isOperand(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9');
}

// returns precedence of a given operator
// Higher returned value means higher precedence
int Prec(char ch){
    switch (ch){
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;
    }
    return -1;
}

void printSonuc(char *a,int *b){
	int l=0;
	while(isOperand(a[l])){
		printf("%c <- %d, ",a[l],b[l]);
		l++;
	}
}

// The main function that converts given infix expression
// to postfix expression. 
int infixToPostfix(char* exp){
    int i, k, j;

    // Creates a stack. Capacity is equal to exp size 
    struct Stack* stack = createStack(strlen(exp));
    if(!stack)
        return -1 ;

    for (i = 0, k = -1; exp[i]; ++i){
        // If the scanned character is an operand, add it to output.
        if (isOperand(exp[i]))
            exp[++k] = exp[i];
        
        // If the scanned character is an ‘(‘, push it to the stack.
        else if (exp[i] == '(')
            push(stack, exp[i]);
        
        // If the scanned character is an ‘)’, pop and output from the stack 
        // until an ‘(‘ is encountered.
        else if (exp[i] == ')'){
            while (!isEmpty(stack) && peek(stack) != '(')
                exp[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return -1; // invalid expression             
            else
                pop(stack);
        }else{
            while (!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
                exp[++k] = pop(stack);
            push(stack, exp[i]);
        }
        printf("    \nAra Cikis: ");
		for(j=0;j<=k;j++){
    	printf("%c",exp[j]);
		}
		printf("    \t\tStack: ");
	
        printStack(stack);
    }

    // pop all operators from the stack
    while (!isEmpty(stack))
        exp[++k] = pop(stack );

    exp[++k] = '\0';
    printf("\nCikis: %s",exp);
}

// The main function that returns value of a given postfix expression
int evaluatePostfix(char* exp,char* a,int* b){
	int l;
    // Creates a stack. Capacity equal to exp size
    struct Stack* stack = createStack(strlen(exp));
    int i;

    if (!stack) return -1;
	// Scan all characters one by one
    for (i = 0; exp[i]; ++i){
    	l=0;
        // If the scanned character is an operand (number here),
        // push it to the stack.
        while(isOperand(a[l]) && a[l]!=exp[i]){l++;}
        if(a[l]==exp[i]){
			push(stack,b[l]);
        }else{
        
        if (isdigit(exp[i]))
            push(stack, exp[i] - '0');
        //  If the scanned character is an operator, pop two
        // elements from stack apply the operator
        else{
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (exp[i]){
            	case '+': push(stack, val2 + val1); break;
            	case '-': push(stack, val2 - val1); break;
            	case '*': push(stack, val2 * val1); break;
            	case '/': push(stack, val2/val1);
            	break;
            }
        }}
    	printf("\n");
    	printStackInt(stack);
    }
    return pop(stack);
}

// Main program
int main(){
    char exp[50];
    char a[50],str[50],*token;
    int  b[50],i,j=0,k=2,in,ci;
    
	for(j=0;j<50;j++){
    	a[j]=NULL;
    	b[j]=NULL;}
    	
	FILE *fd=fopen("input.txt","r");
    if(fd==NULL){
		printf("dosya acilamadi");
		exit(0);
	}
    
    while(!feof(fd)){
	fgets(str, 50, fd);
	token = strtok(str, ";");
    strcpy(exp,token);
    printf("\nOkunan Deger: %s ;",token);
    
	in=0; while(exp[in]){
		if(exp[in]==' '){
			ci=in; while(exp[ci]){
				exp[ci]=exp[ci+1];
				ci++;
			}
			exp[ci]=NULL;
		}
		in++;
	} 
     j=0;k=2;
      while(isOperand(a[j]) && a[j]!=exp[0]){
       j++;
      }
      a[j]=exp[0];
       while(exp[k]){
        exp[k-2]=exp[k];
        k++;
       }
      exp[k-1]=exp[k-2]=NULL;
      infixToPostfix(exp);
      printf("  ve  ");
	  printSonuc(a,b);
      printf("icin;");
      b[j]=evaluatePostfix(exp,a,b);
      printf("\n%c <- %d\n\n",a[j], b[j]);
    }
    
    printf("TOPLAM SONUC\n");
    printSonuc(a,b);
    fclose(fd);
    return 0;
}
