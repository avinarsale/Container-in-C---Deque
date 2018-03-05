/*anarsal1 - Avinash Narsale*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#ifndef DEQUE_H
#define DEQUE_H
#define Deque_DEFINE(t)               \
                          \
struct Deque_##t##_Iterator;        \
                          \
/*container*/                           \
typedef struct Deque_##t                          \
{                          \
	t * dataArray;                          \
	int head;                          \
	int tail;                           \
	int maxSize;                           \
	int currentSize;                          \
	char type_name[sizeof("Deque_"#t)];                          \
	void (*push_back)(struct Deque_##t*, t);                          \
	void (*push_front)(struct Deque_##t*, t);                          \
	t& (*front)(struct Deque_##t*);                          \
	t& (*back)(struct Deque_##t*);                          \
	void (*pop_front)(struct Deque_##t*);                          \
	void (*pop_back)(struct Deque_##t*);                          \
	t& (*at)(struct Deque_##t* q1, int index);                          \
	void (*clear)(struct Deque_##t*);                          \
	bool (*empty)(struct Deque_##t*);                          \
	int (*size)(struct Deque_##t*);                          \
	void (*dtor)(struct Deque_##t*);                          \
	bool (*comparator) (const t &dq1, const t &dq2);                          \
	void (*sort)(struct Deque_##t*, Deque_##t##_Iterator, Deque_##t##_Iterator);                          \
	Deque_##t##_Iterator (*begin)(struct Deque_##t*);                          \
	Deque_##t##_Iterator (*end)(struct Deque_##t*);                          \
}Deque_##t;                          \
                          \
/*iterator*/                           \
typedef struct Deque_##t##_Iterator                          \
{                          \
	int head;                          \
	int tail;                          \
	int index;                          \
	int maxSize;                          \
	int currentSize;                          \
	int endFlag=0;                          \
	void (*inc) (Deque_##t##_Iterator *);                          \
	void (*dec) (Deque_##t##_Iterator *);                          \
	t& (*deref) (Deque_##t##_Iterator *);                          \
	t* currentElement;                          \
	t* headElement;                          \
	t* tailElement;                          \
}Deque_##t##_Iterator;                          \
                          \
/*struct for sort*/                          \
typedef struct Deque_##t##_sort                          \
{                          \
   t dataElement;                       \
   bool (*comparator) (const t &dq1, const t &dq2);                      \
}Deque_##t##_sort;                          \
                          \
void inc(struct Deque_##t##_Iterator * dqItr)                          \
{                          \
	if(dqItr->endFlag == 0)                          \
	{                          \
		if (dqItr->index == (dqItr->maxSize-1))                          \
		{                          \
			dqItr->index= (dqItr->index+1)%dqItr->maxSize;                          \
			dqItr->currentElement = dqItr->currentElement-(dqItr->maxSize-1);                          \
		}                          \
		else                          \
		{                          \
			dqItr->index= (dqItr->index+1)%dqItr->maxSize;                          \
			dqItr->currentElement++;                          \
		}                          \
	}                          \
	else                          \
	{                          \
		dqItr->index = dqItr->head;                          \
		dqItr->currentElement = dqItr->headElement;                          \
		dqItr->endFlag = 0;                          \
	}                          \
}                          \
                          \
void dec(struct Deque_##t##_Iterator * dqItr)                          \
{                          \
	if(dqItr->endFlag == 0)                          \
	{                          \
		if (dqItr->index == 0)                          \
		{                          \
			dqItr->index= (dqItr->index-1)%dqItr->maxSize;                          \
			dqItr->currentElement = dqItr->currentElement+(dqItr->maxSize-1);                          \
		}                          \
		else                          \
		{                          \
			dqItr->index= (dqItr->index-1)%dqItr->maxSize;                          \
			dqItr->currentElement--;                          \
		}                          \
	}                          \
	else                          \
	{                          \
		dqItr->index = dqItr->tail;                          \
		dqItr->currentElement = dqItr->tailElement;                          \
		dqItr->endFlag = 0;                          \
	}                          \
}                          \
                          \
t& deref(Deque_##t##_Iterator * dqItr)                          \
{                          \
	return *(dqItr->currentElement);                          \
}                          \
                          \
Deque_##t##_Iterator begin(Deque_##t* dq)                          \
{                          \
	Deque_##t##_Iterator tempItr;                          \
	tempItr.head= dq->head;                          \
	tempItr.tail= dq->tail;                          \
	tempItr.index= dq->head;                          \
	tempItr.maxSize= dq->maxSize;                          \
	tempItr.currentSize= dq->currentSize;                          \
	tempItr.headElement = &(dq->dataArray[dq->head]);                          \
	tempItr.tailElement = &(dq->dataArray[dq->tail]);                          \
	tempItr.currentElement = &(dq->dataArray[dq->head]);                          \
	tempItr.inc = &inc;                          \
	tempItr.dec = &dec;                          \
	tempItr.deref = &deref;                          \
	return tempItr;                          \
}                          \
                          \
Deque_##t##_Iterator end(Deque_##t* dq)                          \
{                          \
	Deque_##t##_Iterator tempItr;                          \
	tempItr.head= dq->head;                          \
	tempItr.tail= dq->tail;                          \
	tempItr.index=0;                          \
	tempItr.maxSize= dq->maxSize;                          \
	tempItr.currentSize= dq->currentSize;                          \
	tempItr.endFlag=1;                          \
	tempItr.headElement = &(dq->dataArray[dq->head]);                          \
	tempItr.tailElement = &(dq->dataArray[dq->tail]);                          \
	tempItr.currentElement = NULL;                          \
	tempItr.inc = &inc;                          \
	tempItr.dec = &dec;                          \
	tempItr.deref = &deref;                          \
	return tempItr;                          \
}                          \
                          \
void push_back(struct Deque_##t* dq, t inData)                          \
{                          \
	if (dq->head == -1)                          \
	{                          \
		dq->head = 0;                          \
		dq->tail = 0;                          \
		dq->dataArray[dq->tail] = inData;                          \
	}                          \
	else if (dq->currentSize < dq->maxSize)                       \
	{                          \
		dq->tail = (dq->tail+1)%dq->maxSize;                          \
		dq->dataArray[dq->tail] = inData;                          \
	}                          \
	else                          \
	{                          \
		dq->maxSize = dq->maxSize * 2;                          \
		t * tempArray = (t*)malloc(dq->maxSize * sizeof(t));                          \
		int dqHead;                 \
		int tempHead = dq->head;                          \
		for (dqHead = dq->head; dqHead != dq->tail; dqHead = (dqHead+1)%(dq->maxSize / 2))                          \
		{                          \
			tempArray[tempHead++] = dq->dataArray[dqHead];                          \
		}                          \
		tempArray[tempHead] = dq->dataArray[dqHead];                          \
		dq->tail = tempHead;                         \
		free(dq->dataArray);                   \
		dq->dataArray = tempArray;                          \
		dq->tail = (dq->tail+1)%dq->maxSize;                          \
		dq->dataArray[dq->tail] = inData;                          \
	}                          \
	dq->currentSize++;                          \
}                          \
                          \
void pop_back(struct Deque_##t* dq)                          \
{                          \
	if (dq->head != -1)                          \
	{                          \
		if (dq->head == dq->tail)                          \
		{                          \
			dq->head = -1;                          \
			dq->tail = -1;                          \
		}                          \
		else                          \
		{                          \
			dq->tail = (dq->tail-1+dq->maxSize)%dq->maxSize;                          \
		}                          \
		dq->currentSize--;                          \
	}                          \
}                          \
	                          \
void push_front(struct Deque_##t* dq, t inData)                          \
{                          \
	if (dq->head == -1)                          \
	{                          \
		dq->head = 0;                          \
		dq->tail = 0;                          \
		dq->dataArray[dq->tail] = inData;                          \
	}                          \
	else if (dq->currentSize < dq->maxSize-1)                          \
	{                          \
		dq->head = (dq->head-1+dq->maxSize)%dq->maxSize;                          \
		dq->dataArray[dq->head] = inData;                          \
	}                          \
	else                          \
	{                          \
		dq->maxSize = dq->maxSize * 2;                          \
		t * tempArray = (t*)malloc(dq->maxSize * sizeof(t));                          \
		int dqHead;                          \
		int tempHead = dq->head;                          \
		for (dqHead = dq->head; dqHead != dq->tail; dqHead = (dqHead+1)%(dq->maxSize/2))                          \
		{                          \
			tempArray[tempHead++] = dq->dataArray[dqHead];                          \
		}                          \
		tempArray[tempHead] = dq->dataArray[dqHead];                          \
		dq->tail = tempHead;                          \
		free(dq->dataArray);                         \
		dq->dataArray = tempArray;                          \
		dq->head = (dq->head-1+dq->maxSize)%dq->maxSize;                          \
		dq->dataArray[dq->head] = inData;                          \
	}                          \
	dq->currentSize++;                          \
}                          \
                          \
void pop_front(struct Deque_##t* dq)                     \
{                          \
	if (dq->head != -1)                          \
	{                          \
		if (dq->head == dq->tail)                          \
		{                          \
			dq->head = -1;                          \
			dq->tail = -1;                          \
		}                          \
		else                          \
		{                          \
			dq->head = (dq->head+1)%dq->maxSize;                          \
		}                          \
		dq->currentSize--;                          \
	}                          \
}                          \
                          \
bool Deque_##t##_equal(struct Deque_##t dq1, struct Deque_##t dq2)                          \
{                          \
	if (dq1.currentSize == dq2.currentSize)                          \
	{                          \
		int start=0;                          \
		while (start < dq1.currentSize)                          \
		{                          \
			if((dq1.comparator(dq1.dataArray[(dq1.head+start)%(dq1.maxSize)], dq2.dataArray[(dq2.head+start)%(dq2.maxSize)]) || \
				dq1.comparator(dq2.dataArray[(dq2.head+start)%(dq2.maxSize)], dq1.dataArray[(dq1.head+start)%(dq1.maxSize)]))!=false)                           \
			{                          \
				return false;                          \
			}                          \
			start++;                          \
		}                          \
		return true;                          \
	}                          \
	return false;                          \
}                          \
                          \
bool Deque_##t##_Iterator_equal (Deque_##t##_Iterator dqItr1, Deque_##t##_Iterator dqItr2)                          \
{                          \
	if(dqItr1.index == (dqItr2.tail+1)%(dqItr2.maxSize))                          \
	{                          \
		return true;                          \
	}                          \
	else                          \
	{                          \
		return false;                          \
	}                          \
}                          \
                          \
bool Deque_##t##_Iterator_equalSort (Deque_##t##_Iterator dqItr1, Deque_##t##_Iterator dqItr2)                          \
{                          \
	if(dqItr1.index == dqItr2.index)                          \
	{                          \
		return true;                          \
	}                          \
	else                          \
	{                          \
		return false;                          \
	}                          \
}                          \
                          \
t& front(Deque_##t* dq)                          \
{                          \
	return dq->dataArray[dq->head];                          \
}                          \
                          \
t& back(Deque_##t* dq)                          \
{                          \
	return dq->dataArray[dq->tail];                          \
}                          \
                          \
t& at(struct Deque_##t* dq, int index)                          \
{                          \
	return (dq->dataArray[(dq->head+index)%(dq->maxSize)]);                          \
}                          \
                          \
void dtor(struct Deque_##t* dq)                          \
{                          \
	free(dq->dataArray);                          \
	dq->dataArray = NULL;                          \
}                          \
                          \
void clear(struct Deque_##t* dq)                          \
{                          \
	dq->head = -1;                         \
	dq->tail = -1;                         \
	dq->maxSize = 0;                         \
	memset(dq->dataArray, 0, sizeof(t)*dq->maxSize);                          \
}                          \
                          \
int size(struct Deque_##t* dq)                          \
{                          \
	return dq->currentSize;                           \
}                          \
                          \
bool empty(struct Deque_##t* dq)                           \
{                          \
	if (dq->tail == -1)	                          \
	{                           \
		return true;                           \
	}                          \
	else                           \
	{                           \
		return false;                           \
	}                          \
}                          \
                          \
int sort_##t##_compare(const void * a, const void * b)                          \
{                          \
	Deque_##t##_sort *dqs1 = (Deque_##t##_sort *)a;                          \
	Deque_##t##_sort *dqs2 = (Deque_##t##_sort *)b;                          \
	int return_value=0;                          \
	if(dqs1->comparator(dqs1->dataElement,dqs2->dataElement))                          \
	{                          \
		return_value=-1;                          \
	}                          \
	else if (dqs1->comparator(dqs2->dataElement,dqs1->dataElement))                          \
	{                          \
		return_value=1;                          \
	}                           \
	else                           \
	{                          \
		return_value=0;                          \
	}                          \
	return return_value;                          \
}                          \
                          \
void sort(struct Deque_##t *dq,Deque_##t##_Iterator beginPoint,Deque_##t##_Iterator endPoint)                          \
{                            \
	int count=0;                    \
	int start=0;                    \
	for (Deque_##t##_Iterator it = beginPoint;!Deque_##t##_Iterator_equalSort(it, endPoint); it.inc(&it))                     \
	{                        \
		count++;                        \
	}                       \
	Deque_##t##_sort dqsort[count];       \
	for (Deque_##t##_Iterator it = beginPoint;!Deque_##t##_Iterator_equalSort(it, endPoint); it.inc(&it))                     \
	{                        \
		dqsort[start].dataElement=it.deref(&it);                        \
		dqsort[start].comparator=dq->comparator;							\
		start++;            \
	}                        \
    qsort(dqsort,count,sizeof(Deque_##t##_sort),sort_##t##_compare);                       \
	t * tempArray = (t*)malloc(count * sizeof(t));                  \
	int j=0;               \
	for (Deque_##t##_Iterator it = beginPoint;!Deque_##t##_Iterator_equalSort (it, endPoint); it.inc(&it))                \
	{                          \
		(it.deref(&it))=dqsort[j++].dataElement;                 \
	}                          \
	free(tempArray);				                            \
}                          \
                          \
void  Deque_##t##_ctor(struct Deque_##t* dq, bool (*fp) (const t &dq1, const t &dq2))                          \
{                          \
	dq->dataArray = (t*)malloc(sizeof(t)*2);                          \
	strcpy(dq->type_name,"Deque_"#t);                          \
	dq->head = -1;                          \
	dq->tail = -1;                          \
	dq->currentSize = 0;                          \
	dq->maxSize = 2;                          \
                          \
	dq->size = &size;                          \
	dq->empty= &empty;                          \
	dq->push_back =  &push_back;                          \
	dq->comparator=*fp;                          \
	dq->push_front =  &push_front;                          \
	dq->front = &front;                          \
	dq->back = &back;                          \
	dq->pop_front =  &pop_front;                          \
	dq->pop_back =  &pop_back;                          \
	dq->clear =  &clear;                          \
	dq->begin = &begin;                          \
	dq->end = &end;                          \
	dq->at = &at;                          \
	dq->dtor =  &dtor;                          \
	dq->sort = &sort;                          \
}
#endif