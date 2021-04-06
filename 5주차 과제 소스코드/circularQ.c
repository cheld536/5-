/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
// ť Ÿ�� ����
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();

int main(void)
{
	QueueType *cQ = createQueue();
	element data;
	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");
		printf(" ---- [ �� �� �� ] [ 2018038014] ----\n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {                                                     // �޴����� ����ڷκ��� �Է��� �޴´�
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
   	        freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');                            	// ����ڷκ��� q,Q �� �Է��� �Ǹ� ���α׷��� �����Ѵ�.


	return 1;
}

// ť�� �����Ҵ����� �����ϰ� �ʱ�ȭ �ϴ� �Լ�
QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;																// front�� �ʱⰪ ����
	cQ->rear = 0;																// rear�� �ʱⰪ ����
	return cQ;
}

// �����Ҵ� ���� �Լ�
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

//���� �Լ� (����)
element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


// ���� ���� Ȯ�� �Լ�
int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear)                      // front�� rear�� ������ �������
	{
		printf("���� ť�� ������ϴ�.\n");
		return 1;									// ��
	}
	else return 0; 									// ����
}

/* ��ȭ ���� Ȯ�� �Լ� */
int isFull(QueueType *cQ)
{
	if(((cQ->rear+1)%MAX_QUEUE_SIZE)==cQ->front)				// rear�� MAX_QUEUE_SIZE-1 ��ġ�� ������ ��ȭ����
	{
		printf("���� ť�� �� á���ϴ�.\n");
		return 1;									// ��

	}
	else return 0;									// ����
}


/* ���� ť�� rear�� ���Ҹ� �����ϴ� �Լ�*/
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) 																	// �� �������� ���� �ߴ�
	{										 										// ���� ������ ����ϰ� null���� ��ȯ
		return ;																
	}
																
	else{
		cQ->rear = (cQ->rear +1) % MAX_QUEUE_SIZE;										// rear�� ��ġ�� �������� �̵�
		cQ->queue[cQ->rear] = item; 													// rear�� �ε����� ������ ����
	}
	return;
	
}
/* ���� ť front�� ���Ҹ� �����ϴ� �Լ�*/
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ))																// ť�� �������
	{																			// ���� ������ ��� �ϰ� null�� ��ȯ
		return ;
	}
	cQ->front=(cQ->front+1) % MAX_QUEUE_SIZE;									// front�� ��ġ�� �������� �̵�	
	return cQ->queue[cQ->front];												// queue�� front�� ��ġ�� �̵�
}

// ����ť ��� �Լ�
void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;										
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){														// ť�� ����� ���� ���
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;								

	}
	printf(" ]\n");
}

// ����ť ����� �Լ�
void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {									// i�� front�� ���� �� front ��ġ ���
			printf("  [%d] = front\n", i);						
			continue;											
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);				// ť�� ����ִ� �ε��� ���

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);		// front�� rear�� ��ġ ���
}

