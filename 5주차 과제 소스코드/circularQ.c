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
// 큐 타입 선언
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
		printf(" ---- [ 김 윤 희 ] [ 2018038014] ----\n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {                                                     // 메뉴에서 사용자로부터 입력을 받는다
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

	}while(command != 'q' && command != 'Q');                            	// 사용자로부터 q,Q 가 입력이 되면 프로그램을 종료한다.


	return 1;
}

// 큐를 동적할당으로 선언하고 초기화 하는 함수
QueueType *createQueue()
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;																// front의 초기값 설정
	cQ->rear = 0;																// rear의 초기값 설정
	return cQ;
}

// 동적할당 해제 함수
int freeQueue(QueueType *cQ)
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

//삽입 함수 (문자)
element getElement()
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


// 공백 상태 확인 함수
int isEmpty(QueueType *cQ)
{
	if(cQ->front == cQ->rear)                      // front와 rear이 같으면 공백상태
	{
		printf("원형 큐는 비었습니다.\n");
		return 1;									// 참
	}
	else return 0; 									// 거짓
}

/* 포화 상태 확인 함수 */
int isFull(QueueType *cQ)
{
	if(((cQ->rear+1)%MAX_QUEUE_SIZE)==cQ->front)				// rear이 MAX_QUEUE_SIZE-1 위치에 있으면 포화상태
	{
		printf("원형 큐는 꽉 찼습니다.\n");
		return 1;									// 참

	}
	else return 0;									// 거짓
}


/* 원형 큐의 rear에 원소를 삽입하는 함수*/
void enQueue(QueueType *cQ, element item)
{
	if(isFull(cQ)) 																	// 꽉 차있으면 삽입 중단
	{										 										// 오류 문구를 출력하고 null값을 반환
		return ;																
	}
																
	else{
		cQ->rear = (cQ->rear +1) % MAX_QUEUE_SIZE;										// rear의 위치를 다음으로 이동
		cQ->queue[cQ->rear] = item; 													// rear의 인덱스에 데이터 보관
	}
	return;
	
}
/* 원형 큐 front에 원소를 삭제하는 함수*/
void deQueue(QueueType *cQ, element *item)
{
	if(isEmpty(cQ))																// 큐가 비었으면
	{																			// 오류 문구를 출력 하고 null값 반환
		return ;
	}
	cQ->front=(cQ->front+1) % MAX_QUEUE_SIZE;									// front의 위치를 다음으로 이동	
	return cQ->queue[cQ->front];												// queue를 front의 위치로 이동
}

// 원형큐 출력 함수
void printQ(QueueType *cQ)
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;										
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){														// 큐에 저장된 값을 출력
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;								

	}
	printf(" ]\n");
}

// 원형큐 디버깅 함수
void debugQ(QueueType *cQ)
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {									// i와 front가 같을 때 front 위치 출력
			printf("  [%d] = front\n", i);						
			continue;											
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);				// 큐에 들어있는 인덱스 출력

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);		// front와 rear의 위치 출력
}

