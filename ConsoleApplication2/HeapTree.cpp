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
	2.��������˳�򣬽���Ԫ�����丸�ڵ�Ƚϣ������Ԫ��С�ڸ��ڵ������߽���λ�á�
	3.���Ͻ��е�2��������ֱ������Ҫ������Ԫ�غ͸��ڵ㣬���ߴﵽ�Ѷ�
	4.���ͨ���õ�һ����С��
ͨ������Ԫ���븸�ڵ���������Ĳ�����������(percolate up)��
**/
bool InsertMaxHeap(MaxHeap MH, ElementType X) {
	/*��Ԫ��X���������У�����MH-Data[0]�Ѿ�����Ϊ�ڱ�*/
	int i;
	if (IsHeapFull(MH)) {
		cout << "��������" << endl;
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
	}
	int Parent, Child;
	ElementType MaxItem, temp;
	MaxItem = MH->Data[1]; //ȡ��������ŵ����ֵ
	/*�����������һ��Ԫ�ش�Ҫɾ����㿪ʼ���Ϲ����²���*/
	temp = MH->Data[MH->Size--];
	ElementType last = MH->Data[MH->Size--];
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

void BuildMaxHeap(MaxHeap MH) {
/*����MH->Data[]�е�Ԫ�أ�ʹ�������ѵ�������*/
/*�����������MH->Size��Ԫ���Ѿ�����MH->Data[]��*/
	int i;
	/*�����һ�����ĸ���㿪ʼ,�������1*/
	for (i = MH->Size / 2; i > 0; i--)
		PercDown(MH, i);
}

HuffmanTree CreateHuffmanTree(MinHeap H) {
/*����H->Size��Ȩֵ�Ѿ�������H->Data[]->Weight��*/
	return HuffmanTree();
}
