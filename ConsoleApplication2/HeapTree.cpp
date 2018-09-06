#include "pch.h"
#include "HeapTree.h"
#include <iostream>

using namespace std;
/**
堆的存储
堆可以看成一个二叉树，所以可以考虑使用二叉树的表示方法来表示堆。但是因为堆中元素按照一定的优先顺序排列，因此可以使用更简单的方法——数组——来表示，这样可以节省子节点指针空间，并且可以快速访问每个节点。
**/
/*创建最大堆*/
MaxHeap CreateMaxHeap(int MaxSize) {
	MaxHeap MH = (MaxHeap)malloc(sizeof(struct HNode));
	MH->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
	MH->Size = 0;
	MH->Capacity = MaxSize;
	MH->Data[0] = MAXDATA; /*定义"哨兵"大于堆中所有可能元素的值*/
	return MH;
}

bool IsHeapFull(Heap H) {
	return (H->Size == H->Capacity);
}

/**
堆还可以看成一个完全二叉树，每次总是先填满上一层，再在下一层从左往右依次插入。堆的插入步骤：
	1.将新元素增加到堆的末尾
	2.按照优先顺序，将新元素与其父节点比较，如果新元素小于父节点则将两者交换位置。
	3.不断进行第2步操作，直到不需要交换新元素和父节点，或者达到堆顶
	4.最后通过得到一个最小堆
通过将新元素与父节点调整交换的操作叫做上滤(percolate up)。
**/
bool InsertMaxHeap(MaxHeap MH, ElementType X) {
	/*将元素X插入最大堆中，其中MH-Data[0]已经定义为哨兵*/
	int i;
	if (IsHeapFull(MH)) {
		cout << "最大堆已满" << endl;
	}
	for (i = ++MH->Size; MH->Data[i / 2] < X; i /= 2) {
		MH->Data[i] = MH->Data[i / 2];
	}
	MH->Data[i] = X;
	return MH;
}

bool IsHeapEmpty(Heap H) {
	return (H->Size == 0);
}

/**
https://blog.csdn.net/juanqinyang/article/details/51418629
堆的删除操作与插入操作相反，插入操作从下往上调整堆，而删除操作则从上往下调整堆。
	1.删除堆顶元素(通常是将堆顶元素放置在数组的末尾)
	2.比较左右子节点，将小的元素上调。
	3.不断进行步骤2，直到不需要调整或者调整到堆底。
上述调整的方法称为下滤(percolate down)
**/
ElementType DeleteMaxHeap(MaxHeap MH) {
	if (IsHeapEmpty(MH)) {
		cout << "最大堆已空" << endl;
	}
	int Parent, Child;
	ElementType MaxItem, temp;
	MaxItem = MH->Data[1]; //取出根结点存放的最大值
	/*用最大堆中最后一个元素从要删除结点开始向上过滤下层结点*/
	temp = MH->Data[MH->Size--];
	ElementType last = MH->Data[MH->Size--];
	for (Parent = 1; Parent * 2 <= MH->Size; Parent = Child) {
	/*Parent * 2 <= MH->Size==》判断是否有有儿子*/
		Child = Parent * 2; 
		if (Child != MH->Size && (MH->Data[Child] < MH->Data[Child + 1])) {
			Child++; /*Child指向左右子结点的较大者*/
		}
		if (temp > MH->Data[Child])
			break; /*找到了合适位置*/
		else { //下滤X：移动X到下一层
			MH->Data[Parent] = MH->Data[Child];
		}
	}
	return MaxItem;
}

/*---------建造最大堆-----------*/
void PercDown(MaxHeap MH, int p) {
/*下滤：将MH中以MH->Data[p]为根的子堆调整为最大堆*/
	int Parent, Child;
	ElementType X;
	X = MH->Data[p];
	for (Parent = p; Parent * 2 <= MH->Size; Parent = Child) {
		Child = Parent * 2;
		if (Child != MH->Size && MH->Data[Child] < MH->Data[Child + 1])
			Child++;
		if (X >= MH->Data[Child])
			break;
		else
			MH->Data[Parent] = MH->Data[Child];
	}
	MH->Data[Parent] = X;
}

void BuildMaxHeap(MaxHeap MH) {
/*调整MH->Data[]中的元素，使满足最大堆的有序性*/
/*这里假设所有MH->Size个元素已经存在MH->Data[]中*/
	int i;
	/*从最后一个结点的父结点开始,到根结点1*/
	for (i = MH->Size / 2; i > 0; i--)
		PercDown(MH, i);
}

HuffmanTree CreateHuffmanTree(MinHeap H) {
/*假设H->Size个权值已经存在在H->Data[]->Weight里*/
	return HuffmanTree();
}
