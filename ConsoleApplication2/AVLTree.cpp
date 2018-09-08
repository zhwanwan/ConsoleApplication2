#include "pch.h"
#include "AVLTree.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int Max(int a, int b) {
	return a > b ? a : b ;
}

/*求二叉树的高度*/
int GetHeight(AVLTree A) {
	return A == NULL ? -1 : A->Height;
}

/*判断是否平衡*/
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

AVLTree SingleLeftRotation(AVLTree A) { /* 注意：A必须有一个左子结点B */
  /* 将A与B做左单旋，更新A与B的高度，返回新的根结点B */
	AVLTree B = A->Left;
	A->Left = B->Right;
	B->Right = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), A->Height) + 1;
	return B;
}

AVLTree SingleRightRotation(AVLTree A) { /*A必须有一个右子结点B*/
	/*将A与B做右单旋，更新A与B的高度，返回新的根结点B */
	AVLTree B = A->Right;
	A->Right = B->Left;
	B->Left = A;
	A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
	B->Height = Max(GetHeight(B->Left), GetHeight(B->Right)) + 1;
	return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A) { /* 注意：A必须有一个左子结点B，且B必须有一个右子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */

	/* 第一步将B与C做右单旋，C被返回 */
	A->Left = SingleRightRotation(A->Left);
	/* 第二步将A与C做左单旋，C被返回 */
	return SingleLeftRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A) { /* 注意：A必须有一个右子结点B，且B必须有一个左子结点C */
  /* 将A、B与C做两次单旋，返回新的根结点C */

	/*第一步将B与C做左单旋，C被返回*/
	A->Right = SingleLeftRotation(A->Right);
	/*第二步将A与C做右单旋，C被返回*/
	return SingleRightRotation(A);
}

AVLTree CreateAVLTree(ElementType Root) {
	AVLTree A = (AVLTree)malloc(sizeof(struct AVLNode));
	A->Data = Root;
	A->Left = A->Right = NULL;
	A->Height = 0;
	return A;
}

AVLTree Insert(AVLTree T, ElementType X) { /* 将X插入AVL树T中，并且返回调整后的AVL树 */
	cout << endl << "Insert Data: " << X << endl;
	if (!T) { /* 若插入空树，则新建包含一个结点的树 */
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		T->Data = X;
		T->Height = 0;
		T->Left = T->Right = NULL;
	} /* if (插入空树) 结束 */
	else if (X < T->Data) {
		/* 插入T的左子树 */
		T->Left = Insert(T->Left, X);
		/* 如果需要左旋 */
		if (GetHeight(T->Left) - GetHeight(T->Right) == 2)
			if (X < T->Left->Data)
				T = SingleLeftRotation(T);      /* 左单旋 */
			else
				T = DoubleLeftRightRotation(T); /* 左-右双旋 */
	} /* else if (插入左子树) 结束 */
	else if (X > T->Data) {
		/* 插入T的右子树 */
		T->Right = Insert(T->Right, X);
		/* 如果需要右旋 */
		if (GetHeight(T->Left) - GetHeight(T->Right) == -2)
			if (X > T->Right->Data)
				T = SingleRightRotation(T);     /* 右单旋 */
			else
				T = DoubleRightLeftRotation(T); /* 右-左双旋 */
	} /* else if (插入右子树) 结束 */
	/* else X == T->Data，无须插入 */
	/* 别忘了更新树高 */
	T->Height = Max(GetHeight(T->Left), GetHeight(T->Right)) + 1;
	cout << "Height of After Insert: " << T->Height << endl;
	return T;
}
