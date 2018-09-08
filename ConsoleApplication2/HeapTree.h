#include "pch.h"
/**
����һ����ȫ������(������㣬������Ͻ�����������ֵ��������㶼�����)
���ԣ�
1.�ṹ�ԣ��������ʾ����ȫ������
2.�����ԣ���һ���Ĺؼ������������������(С)ֵ
**/
#define ERROR -1
#define MAXDATA 9999
#define MINDATA -9999

typedef int ElementType;
typedef struct HNode *Heap;
typedef struct HufNode *HufHeap;

struct HNode {
	ElementType *Data; /*�洢Ԫ�ص�����*/
	int Size;          /*���е�ǰԪ�ظ���*/ 
	int Capacity;      /*�ѵ��������*/
};
typedef struct TreeNode *HuffmanTree;
struct TreeNode {
	int Weight;
	HuffmanTree Left, Right;
};
struct HufNode {
	struct TreeNode *Data; /*�洢Ԫ�ص�����*/
	int Size;          /*���е�ǰԪ�ظ���*/ 
	int Capacity;      /*�ѵ��������*/
};
typedef Heap MaxHeap;
typedef HufHeap MinHeap;


bool IsHeapFull(Heap H);
bool IsHeapEmpty(Heap H);

MaxHeap CreateMaxHeap(int MaxSize);
MaxHeap InsertMaxHeap(MaxHeap MH, ElementType X);
ElementType DeleteMaxHeap(MaxHeap H);

/*���ˣ����/С�ѽ���*/
void PercDown(MaxHeap MH, int p); 
void BuildMaxHeap(MaxHeap MH);

/*��С��*/
MinHeap CreateMinHeap(int MaxSize);
MinHeap InsertMinHeap(MinHeap H, HuffmanTree W);
HuffmanTree DeleteMinHeap(MinHeap H);
void PercDownMinHeap(MinHeap HMH, int p);
void BuildMinHeap(MinHeap H);

/*��������*/
HuffmanTree CreateHuffmanTree(MinHeap H);
