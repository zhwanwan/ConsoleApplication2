#include "pch.h"
/**
����һ����ȫ������(������㣬������Ͻ�����������ֵ��������㶼�����)
���ԣ�
1.�ṹ�ԣ��������ʾ����ȫ������
2.�����ԣ���һ���Ĺؼ������������������(С)ֵ
**/
#define ERROR -1
#define MAXDATA 9999
typedef int ElementType;
typedef struct HNode *Heap;

struct HNode {
	ElementType *Data; /*�洢Ԫ�ص�����*/
	int Size;          /*���е�ǰԪ�ظ���*/ 
	int Capacity;      /*�ѵ��������*/
};
typedef Heap MaxHeap;
typedef Heap MinHeap;

typedef struct TreeNode *HuffmanTree;
struct TreeNode {
	int Weight;
	HuffmanTree Left, Right;
};

MaxHeap CreateMaxHeap(int MaxSize);

bool IsHeapFull(Heap H);

bool InsertMaxHeap(MaxHeap MH, ElementType X);

bool IsHeapEmpty(Heap H);

ElementType DeleteMaxHeap(MaxHeap H);

/*���ˣ����ѽ�������*/
void PercDown(MaxHeap MH, int p); 

void BuildMaxHeap(MaxHeap MH);

HuffmanTree CreateHuffmanTree(MinHeap H);
