#include "pch.h"
#include "HeapTree.h"
#include <iostream>

using namespace std;
/**
�ѵĴ洢
�ѿ��Կ���һ�������������Կ��Կ���ʹ�ö������ı�ʾ��������ʾ�ѡ�������Ϊ����Ԫ�ذ���һ��������˳�����У���˿���ʹ�ø��򵥵ķ����������顪������ʾ���������Խ�ʡ�ӽڵ�ָ��ռ䣬���ҿ��Կ��ٷ���ÿ���ڵ㡣
**/
/*��������*/
MaxHeap CreateMaxHeap(int MaxSize) {
	MaxHeap MH = (MaxHeap)malloc(sizeof(struct HNode));
	MH->Data = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
	MH->Size = 0;
	MH->Capacity = MaxSize;
	MH->Data[0] = MAXDATA; /*����"�ڱ�"���ڶ������п���Ԫ�ص�ֵ*/
	return MH;
}

bool IsHeapFull(Heap H) {
	return (H->Size == H->Capacity);
}

/**
�ѻ����Կ���һ����ȫ��������ÿ��������������һ�㣬������һ������������β��롣�ѵĲ��벽�裺
	1.����Ԫ�����ӵ��ѵ�ĩβ
	2.��������˳�򣬽���Ԫ�����丸�ڵ�Ƚϣ������Ԫ�ش��ڸ��ڵ������߽���λ�á�
	3.���Ͻ��е�2��������ֱ������Ҫ������Ԫ�غ͸��ڵ㣬���ߴﵽ�Ѷ�
	4.���ͨ���õ�һ������
ͨ������Ԫ���븸�ڵ���������Ĳ�����������(percolate up)��
**/
/*T (N) = O ( log N )*/
MaxHeap InsertMaxHeap(MaxHeap MH, ElementType X) {
	/*��Ԫ��X���������У�����MH-Data[0]�Ѿ�����Ϊ�ڱ�*/
	int i;
	if (IsHeapFull(MH)) {
		cout << "��������" << endl;
		return MH;
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
�ѵ�ɾ���������������෴����������������ϵ����ѣ���ɾ��������������µ����ѡ�
	1.ɾ���Ѷ�Ԫ��(ͨ���ǽ��Ѷ�Ԫ�ط����������ĩβ)
	2.�Ƚ������ӽڵ㣬��С��Ԫ���ϵ���
	3.���Ͻ��в���2��ֱ������Ҫ�������ߵ������ѵס�
���������ķ�����Ϊ����(percolate down)
**/
ElementType DeleteMaxHeap(MaxHeap MH) {
	if (IsHeapEmpty(MH)) {
		cout << "�����ѿ�" << endl;
		return NULL;
	}
	int Parent, Child;
	ElementType MaxItem, temp;
	MaxItem = MH->Data[1]; //ȡ��������ŵ����ֵ
	/*�����������һ��Ԫ�ش�Ҫɾ����㿪ʼ���Ϲ����²���*/
	temp = MH->Data[MH->Size--];
	for (Parent = 1; Parent * 2 <= MH->Size; Parent = Child) {
	/*Parent * 2 <= MH->Size==���ж��Ƿ����ж���*/
		Child = Parent * 2; 
		if (Child != MH->Size && (MH->Data[Child] < MH->Data[Child + 1])) {
			Child++; /*Childָ�������ӽ��Ľϴ���*/
		}
		if (temp > MH->Data[Child])
			break; /*�ҵ��˺���λ��*/
		else { //����X���ƶ�X����һ��
			MH->Data[Parent] = MH->Data[Child];
		}
	}
	MH->Data[Parent] = temp;
	return MaxItem;
}

/*---------��������-----------*/
void PercDown(MaxHeap MH, int p) {
/*���ˣ���MH����MH->Data[p]Ϊ�����Ӷѵ���Ϊ����*/
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

void PercDownMinHeap(MinHeap H, int p) {
	int Parent, Child;
	HuffmanTree X;
	X = &H->Data[p];
	for (Parent = p; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if (Child != H->Size && H->Data[Child].Weight > H->Data[Child + 1].Weight)
			Child++;
		if (X->Weight <= H->Data[Child].Weight)
			break;
		else
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = *X;
}

void BuildMaxHeap(MaxHeap MH) {
/*����MH->Data[]�е�Ԫ�أ�ʹ�������ѵ�������*/
/*�����������MH->Size��Ԫ���Ѿ�����MH->Data[]��*/
	int i;
	/*�����һ�����ĸ���㿪ʼ,�������1*/
	for (i = MH->Size / 2; i > 0; i--)
		PercDown(MH, i);
}

MinHeap CreateMinHeap(int MaxSize){
	//MinHeap H = (MinHeap)malloc(sizeof(struct HufNode));
	MinHeap H = (MinHeap)calloc(1,sizeof(HufNode));
	H->Size = 0;
	H->Capacity = MaxSize;
	//H->Data = (TreeNode *)malloc((MaxSize + 1) * sizeof(TreeNode));
	H->Data = (TreeNode *)calloc((MaxSize + 1),sizeof(TreeNode));
	H->Data[0].Weight = MINDATA;
	return H;
}

MinHeap InsertMinHeap(MinHeap H, HuffmanTree W) {
	if (H->Size == H->Capacity) {
		cout << "��С������" << endl;
		return H;
	}
	int i;
	for (i = ++H->Size; H->Data[i / 2].Weight > W->Weight; i /= 2) {
		H->Data[i].Weight = H->Data[i / 2].Weight;
	}
	H->Data[i] = *W;
	return H;
}

HuffmanTree DeleteMinHeap(MinHeap H) {
	if (H->Size == 0) {
		cout << "��С���ѿ�!" << endl;
		return NULL;
	}
	int Parent, Child;
	HuffmanTree MinItem, temp;
	MinItem = &H->Data[1];
	temp = &H->Data[H->Size--];
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;
		if (Child != H->Size && H->Data[Child].Weight > H->Data[Child + 1].Weight) {
			Child++;
		}
		if (temp->Weight < H->Data[Child].Weight)
			break;
		else
			H->Data[Parent] = H->Data[Child];
	}
	H->Data[Parent] = *temp;
	return MinItem;
}

void BuildMinHeap(MinHeap H) {
	int i;
	for (i = H->Size / 2; i > 0; i++) {
		PercDownMinHeap(H, i);
	}
}

/**
���������Ķ��壺
��Ȩ·������(WPL)�� ���������n��Ҷ�ӽ�㣬ÿ��Ҷ�ӽ���
��Ȩֵ wk���Ӹ���㵽ÿ��Ҷ�ӽ��ĳ���Ϊ lk����ÿ��Ҷ�ӽ�
��Ĵ�Ȩ·������֮�͡�
���Ŷ��������������: WPL��С�Ķ�����

���������Ĺ��죺
ÿ�ΰ�Ȩֵ��С�����ö������ϲ�
**/
HuffmanTree CreateHuffmanTree(MinHeap H) {
/*����H->Size��Ȩֵ�Ѿ�������H->Data[]��*/
	int i;
	HuffmanTree HT;
	BuildMinHeap(H);
	for (i = 1; i < H->Size; i++) {
		HT = (HuffmanTree)malloc(sizeof(TreeNode));
		HT->Left = DeleteMinHeap(H);
		HT->Right = DeleteMinHeap(H);
		HT->Weight = HT->Left->Weight + HT->Right->Weight;
		InsertMinHeap(H, HT);
	}
	HT = DeleteMinHeap(H);
	return HT;
}
