/*
* postfix.c 
*
*�ڷᱸ�� 5���� ���� 
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

char infixExp[MAX_EXPRESSION_SIZE];     /* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];   /* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];  /* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];      /* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;       /* postfixStack�� top */
int evalStackTop = -1;          /* evalStack�� top */

int evalResult = 0;  /* ��� ����� ���� */

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
        printf("---------------- [ �� �� �� ] [ 2018038014 ] --------------------\n");
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
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
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
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
    if (postfixExp == '\0')
        strncpy(postfixExp, c, 1);
    else
        strncat(postfixExp, c, 1);
}

// ���� ǥ��� ��ȯ �Լ�
void toPostfix()
{
    char* exp = infixExp;                // infixExp�� ���ڸ� �ϳ��� �б� ���� ������
    char temp;                           // temp:  �����ϳ��� �ӽ÷� �����ϱ� ���� ���� x�� ������ �ϴ� �ʹ� �������� �������� �ٲ���ϴ�.
    postfixStack[postfixStackTop] = '\0';    // ���� �ʱ�ȭ


/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
    // exp�� ���ڿ��� ���� ������  

    while (*exp != '\0')
    {
        if (getPriority(*exp) == operand)      // �ǿ����� ó��
        {
            temp = *exp;
            charCat(&temp);  
        }
        else if (getPriority(*exp) == lparen)  // ������ ó�� 
        {
            postfixPush(*exp);
            
        }
        else if (getPriority(*exp) == rparen)		// ������ ��ȣ�� ó���Ѵ�.
        {
            while ((temp=postfixPop()) != '(') {                    
                charCat(&temp);

            }
            postfixPop();
        }

        else
        {
            while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))     //���ÿ� �ִ� �������� �켱������ �� ũ�ų� ������ ����
            {
                temp = postfixPop();
                charCat(&temp);
            }
            postfixPush(*exp);
        }
        exp++; 																			// exp�� �ּҰ��� ���� ���� ���� ���Ҹ� �����ϰ� �Ѵ�.
    }

    while (postfixStackTop != -1) 														// ������ ������ �� ������ pop�Ͽ� ���
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
// �迭�� �ʱ�ȭ �ϴ� �Լ�
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
// ���� ǥ��� ��� �Լ�
void evaluation()
{
     int opr1, opr2, i;    // opr1 , opr2 : ����� ���ڸ� pop�� ������ , i : �ݺ������� ����

   int length = strlen(postfixExp); //���ڿ��� ���̸� ����
   char symbol;                      // �迭�� ���ڰ� ����� �ӽú���
   
   for (i = 0; i < length; i++)
   {
      symbol = postfixExp[i];
      if (getPriority(symbol) == operand) {                // �ǿ����� �̸� 
         evalPush(symbol - '0');                            // ���������� ��ȯ
      }
      else {
         opr2 = evalPop();
         opr1 = evalPop();
         switch (getToken(symbol)) {                        //�����ڿ� ���� ó��
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
   evalResult = evalPop();                                              //���� ���� ����


}
 