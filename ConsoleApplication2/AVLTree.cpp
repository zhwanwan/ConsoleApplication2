#include "pch.h"
#include "AVLTree.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int Max(int a, int b) {
	return a > b ? a : b ;
}

/*��������ĸ߶�*/
int GetHeight(AVLTree A) {
	return A == NULL ? -1 : A->Height;
}

/*�ж��Ƿ�ƽ��*/
bool IsBalanced(AVLTree A) {
	if (!A) {
		return true;
	}
	int lh = GetHeight(A->Left);
	int rh = GetHeight(A->Right);
	if (abs(lh - rh) > 1) {
		return false;
	}
	else {
		return IsBalanced(A->Left) && IsBalanced(A->Right);
	}
	return false;
}

AVLTree SingleLeftRotation(AVLTree A) { /* ע�⣺A������һ�����ӽ��B */
  /* ��A��B������������A��B�ĸ߶ȣ������µĸ����B */
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;
	return B;
}

AVLTree SingleRightRotation(AVLTree A) { /*A������һ�����ӽ��B*/
	/*��A��B���ҵ���������A��B�ĸ߶ȣ������µĸ����B */
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), GetHeight(B->Right)) + 1;
	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A) { /* ע�⣺A������һ�����ӽ��B����B������һ�����ӽ��C */
  /* ��A��B��C�����ε����������µĸ����C */

	/* ��һ����B��C���ҵ�����C������ */
	A->Left = SingleRightRotation(A->Left);
	/* �ڶ�����A��C��������C������ */
	return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A) { /* ע�⣺A������һ�����ӽ��B����B������һ�����ӽ��C */
  /* ��A��B��C�����ε����������µĸ����C */

	/*��һ����B��C��������C������*/
	A->Right = SingleLeftRotation(A->Right);
	/*�ڶ�����A��C���ҵ�����C������*/
	return SingleRightRotation(A);
}

AVLTree CreateAVLTree(ElementType Root) {
	AVLTree A = (AVLTree)malloc(sizeof(struct AVLNode));
	A->Data = Root;
	A->Left = A->Right = NULL;
	A->Height = 0;
	return A;
}

AVLTree Insert(AVLTree T, ElementType X) { /* ��X����AVL��T�У����ҷ��ص������AVL�� */
	cout << endl << "Insert Data: " << X << endl;
	if (!T) { /* ��������������½�����һ�������� */
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	} /* if (�������) ���� */
	else if (X < T->Data) {
		/* ����T�������� */
		T->Left = Insert(T->Left, X);
		/* �����Ҫ���� */
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
			if (X < T->Left->Data)
				T = SingleLeftRotation(T);      /* ���� */
			else
				T = DoubleLeftRightRotation(T); /* ��-��˫�� */
	} /* else if (����������) ���� */
	else if (X > T->Data) {
		/* ����T�������� */
		T->Right = Insert(T->Right, X);
		/* �����Ҫ���� */
		if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
			if (X > T->Right->Data)
				T = SingleRightRotation(T);     /* �ҵ��� */
			else
				T = DoubleRightLeftRotation(T); /* ��-��˫�� */
	} /* else if (����������) ���� */
	/* else X == T->Data��������� */
	/* �����˸������� */
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
	cout << "Height of After Insert: " << T->Height << endl;
	return T;
}
