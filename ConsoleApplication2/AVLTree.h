#include "pch.h"

typedef int ElementType;
typedef struct AVLNode *Position;
typedef Position AVLTree; // AVLÊ÷ÀàÐÍ
struct AVLNode {
	ElementType Data;
	AVLTree Left;
	AVLTree Right;
	int Height;
};

ElementType Max(int a, int b);

int GetHeight(AVLTree A);

bool IsBalanced(AVLTree A);

AVLTree SingleLeftRotation(AVLTree A);

AVLTree SingleRightRotation(AVLTree A);

AVLTree DoubleLeftRightRotation(AVLTree A);

AVLTree DoubleRightLeftRotation(AVLTree A);

AVLTree CreateAVLTree(ElementType Root);

AVLTree Insert(AVLTree T, ElementType X);