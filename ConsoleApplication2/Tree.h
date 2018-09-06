#include "pch.h"
#define LEFTCHILD 0
#define RIGHTCHILD 1
#define ERROR NULL
typedef int ElementType;
typedef struct TreeNode *BinTree;
typedef BinTree BTree;
struct TreeNode {
	ElementType Data;
	BTree LeftChildTree;
	BTree RightChildTree;
};
typedef struct LinkNode *LNode;
typedef LNode QPosition;
typedef struct QNode *Queue;
struct QNode {
	QPosition Front, Rear;
};
struct LinkNode {
	BTree PTree;
	QPosition Next;
};

Queue CreateQue();
bool IsQEmpty(Queue Q);
bool AddQue(Queue Q, BTree X);
BTree DeleteQue(Queue Q);

BTree CreateBinTree(ElementType Root);
bool IsBinTreeEmpty(BTree BT);
BTree addTreeNode(BTree P, ElementType X, int ChildPos);
void PreOrderTraversal(BTree BT);
void InOrderTraversal(BTree BT);
void PostOrderTraversal(BTree BT);
void LevelOrderTraversal(BTree BT);
