#include "pch.h"
/**
堆是一种完全二叉树(除最外层，其余层上结点数均达最大值且最外层结点都在左侧)
特性：
1.结构性：用数组表示的完全二叉树
2.有序性：任一结点的关键字是其子树结点的最大(小)值
**/
#define ERROR -1
#define MAXDATA 9999
typedef int ElementType;
typedef struct HNode *Heap;

struct HNode {
	ElementType *Data; /*存储元素的数组*/
	int Size;          /*堆中当前元素个数*/ 
	int Capacity;      /*堆的最大容量*/
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

/*下滤：最大堆建造最大堆*/
void PercDown(MaxHeap MH, int p); 

void BuildMaxHeap(MaxHeap MH);

HuffmanTree CreateHuffmanTree(MinHeap H);
