#include<stdio.h>
#include<stdbool.h>
#include<math.h>
#include<stdlib.h>
#define MAX 100
/*WAP to convert a given infix expression to its equivalent postfix form 
and print the value obtained after evaluating the postfix expression so obtained*/

//global stuff...
char infix[MAX], postfix[MAX];
char stack[MAX];
int top = -1;

bool isEmpty(){
    if(top == -1) return true;
    else          return false;
}

bool isFull(){
    if(top == MAX-1) return true;
    else             return false;
}

void push(char data){
    if(isFull()){
        printf("stack overflow!!\n");
        exit(1);
    }
    else{
        top++;
        stack[top] = data;
    }
}
char pop(){
    if(isEmpty()){
        printf("stack underflow!!\n");
        exit(2);
    }
    else{
        char retVal = stack[top];
        top--;
        return retVal;
    }
}

int precedence(char symbol){  //precedence checking function
    switch(symbol){
    case '^' :
        return 3;
    case '*' :
    case '/' :
        return 2;
    case '+' :
    case '-' :
        return 1;
    default  :
        return 0;
    }
}

void infixToPostfix(){

    int i = 0, k = 0;
    char sym;

    //1. main.....................................................................................................

    while(infix[i] != '\0'){ //scanning the infix expression form L to R

        sym = infix[i];

        if(sym == ' ' || sym == '\t'){i++; continue;}  //to bypass spaces and tabs

        if(sym >= '0' && sym <= '9' ||
           sym >= 'a' && sym <= 'z' ||
           sym >= 'A' && sym <= 'Z'){                  //CASE1 -> when sym is an operand
            postfix[k++] = sym;
        }
        else if(sym == '('){                           //CASE2 -> when sym is '(' 
            push(sym);
        }
        else if(sym == ')'){                           //CASE3 -> when sym is ')'
            while(!isEmpty() && stack[top] != '('){
                postfix[k++] = pop();
            }
            pop(); /*to discard '('*/
        }
        else{                                          //CASE4 -> when sym is an operator
            while (!isEmpty() && stack[top] != '(' && precedence(sym) <= precedence(stack[top])) {
                postfix[k++] = pop();
            }
            push(sym);
        }
        i++;
    }

    //2. casualty chek...........................................................................................

    while(top > -1) postfix[k++] = pop();

    //3. the null ritual...........................................................................................

    postfix[k++] = '\0';
}

void evaluatePostfix(){

    int i = 0;

    while(postfix[i] != '\0'){

        if(postfix[i] >= '0' && postfix[i] <= '9'){
            push(postfix[i]-'0');                   /**1 step solution for all ascii anomalies**/
        }
        else{
            int rightOp, leftOp;
            rightOp = pop();
            leftOp = pop();

            if     (postfix[i] == '+')  push(leftOp + rightOp);
            else if(postfix[i] == '-')  push(leftOp - rightOp);
            else if(postfix[i] == '*')  push(leftOp * rightOp);
            else if(postfix[i] == '/')  push(leftOp / rightOp);
            else                                                /*when operator is '^' */
                push(pow(leftOp, rightOp));
        }

        i++;
    }
}

int main(){
  
    //getting the infix expr.
    printf("enter the infix expression   : ");
    gets(infix);

    //converting it to postfix form
    infixToPostfix();
    printf("\npostfix form               : ");
    puts(postfix);

    //evaluating the postfix expr. so obtained
    evaluatePostfix();
    printf("\nvalue of the above postfix expression        : %d", stack[top]);
    printf("\n------------------------------------------------------------------------\n");

    return 0;
}
