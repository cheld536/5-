/*
* postfix.c 
*
*자료구조 5주차 과제 
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20


typedef enum {
    lparen = 0,
    rparen = 9,
    times = 7,
    divide = 6,
    plus = 5,
    minus = 4,
    operand = 1
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];     /* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];   /* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];  /* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];      /* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;       /* postfixStack용 top */
int evalStackTop = -1;          /* evalStack용 top */

int evalResult = 0;  /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
    char command;

    do {
        printf("----------------------------------------------------------------\n");
        printf("               Infix to Postfix, then Evaluation               \n");
        printf("----------------------------------------------------------------\n");
        printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
        printf("----------------------------------------------------------------\n");
        printf("---------------- [ 김 윤 희 ] [ 2018038014 ] --------------------\n");
        printf("----------------------------------------------------------------\n");
        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
        case 'i': case 'I':
            getInfix();
            break;
        case 'p': case 'P':
            toPostfix();
            break;
        case 'e': case 'E':
            evaluation();
            break;
        case 'd': case 'D':
            debug();
            break;
        case 'r': case 'R':
            reset();
            break;
        case 'q': case 'Q':
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q');

    return 1;
}

void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop()
{
    char x;
    if (postfixStackTop == -1)
        return '\0';
    else {
        x = postfixStack[postfixStackTop--];
    }
    return x;
}

void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

int evalPop()
{
    if (evalStackTop == -1)
        return -1;
    else
        return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s", infixExp);
}

precedence getToken(char symbol)
{
    switch (symbol) {
    case '(': return lparen;
    case ')': return rparen;
    case '+': return plus;
    case '-': return minus;
    case '/': return divide;
    case '*': return times;
    default: return operand;
    }
}

precedence getPriority(char x)
{
    return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
    if (postfixExp == '\0')
        strncpy(postfixExp, c, 1);
    else
        strncat(postfixExp, c, 1);
}

// 후위 표기식 전환 함수
void toPostfix()
{
    char* exp = infixExp;                // infixExp의 문자를 하나씩 읽기 위한 포인터
    char temp;                           // temp:  문자하나를 임시로 저장하기 위한 변수 x를 쓸려고 하니 너무 직관성이 떨어져서 바꿨습니다.
    postfixStack[postfixStackTop] = '\0';    // 스텍 초기화


/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
    // exp의 문자열이 끝날 때까지  

    while (*exp != '\0')
    {
        if (getPriority(*exp) == operand)      // 피연산자 처리
        {
            temp = *exp;
            charCat(&temp);  
        }
        else if (getPriority(*exp) == lparen)  // 연산자 처리 
        {
            postfixPush(*exp);
            
        }
        else if (getPriority(*exp) == rparen)		// 오른쪽 괄호를 처리한다.
        {
            while ((temp=postfixPop()) != '(') {                    
                charCat(&temp);

            }
            postfixPop();
        }

        else
        {
            while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))     //스택에 있는 연산자의 우선순위가 더 크거나 같으면 저장
            {
                temp = postfixPop();
                charCat(&temp);
            }
            postfixPush(*exp);
        }
        exp++; 																			// exp의 주소값을 증가 시켜 다음 원소를 접근하게 한다.
    }

    while (postfixStackTop != -1) 														// 스택이 공백이 될 때까지 pop하여 출력
    {
        temp = postfixPop();
        charCat(&temp);
    }


}

void debug()
{
    printf("\n---DEBUG\n");
    printf("infixExp =  %s\n", infixExp);
    printf("postExp =  %s\n", postfixExp);
    printf("eval result = %d\n", evalResult);

    printf("postfixStack : ");
    for (int i = 0; i < MAX_STACK_SIZE; i++)
        printf("%c  ", postfixStack[i]);

    printf("\n");

}
// 배열을 초기화 하는 함수
void reset()
{
    infixExp[0] = '\0';
    postfixExp[0] = '\0';

    for (int i = 0; i < MAX_STACK_SIZE; i++)
        postfixStack[i] = '\0';

    postfixStackTop = -1;
    evalStackTop = -1;
    evalResult = 0;
}
// 후위 표기식 계산 함수
void evaluation()
{
     int opr1, opr2, i;    // opr1 , opr2 : 연산될 숫자를 pop한 변수들 , i : 반복문제어 변수

   int length = strlen(postfixExp); //문자열의 길이를 저장
   char symbol;                      // 배열의 문자가 저장될 임시변수
   
   for (i = 0; i < length; i++)
   {
      symbol = postfixExp[i];
      if (getPriority(symbol) == operand) {                // 피연산자 이면 
         evalPush(symbol - '0');                            // 정수형으로 변환
      }
      else {
         opr2 = evalPop();
         opr1 = evalPop();
         switch (getToken(symbol)) {                        //연산자에 따라서 처리
         case plus: evalPush(opr1 + opr2); 
            break;
         case minus: evalPush(opr1 - opr2); 
            break;
         case times: evalPush(opr1 * opr2); 
            break;
         case divide: evalPush(opr1 / opr2); 
            break;
         default:
             break;
         }
      }
   }
   evalResult = evalPop();                                              //계산된 값을 저장


}
 