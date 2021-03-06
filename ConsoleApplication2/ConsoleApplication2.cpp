// ConsoleApplication2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

//
#include "pch.h"
#include <iostream>
#include <time.h>
#include "Tree.h"
#include "AVLTree.h"
#include "Graph.h"
using namespace std;

void PreOrder(BTree BT); /*先序非递归遍历*/
void InOrder(BTree BT); /*中序非递归遍历*/
void PostOrder1(BTree BT); /*后续非递归遍历1*/
void PostOrder2(BTree BT); /*后续非递归遍历2*/

void Visit(Vertex V) {
	cout << "正在访问顶点: " << V << endl;
}

int main() {
/**
	//树的遍历
	BTree BT = CreateBinTree(0);
	BTree p1 = addTreeNode(BT, 1, 0);
	BTree p2 = addTreeNode(BT, 2, 1);
	for (int i = 3; i <= 20; i++) {
		if (i % 2 == 1) {
			p1 = addTreeNode(p1, i, i % 2);
		}
		else {
			p2 = addTreeNode(p2, i, i % 2);
		}
	}
	cout << "先序1：" << endl;
	PreOrderTraversal(BT);
	cout << endl << "先序2：" << endl;
	PreOrder(BT);
	cout << endl << "中序1：" << endl;
	InOrderTraversal(BT);
	cout << endl << "中序2：" << endl;
	InOrder(BT);
	cout << endl << "后序1：" << endl;
	PostOrderTraversal(BT);
	cout << endl << "后序2：" << endl;
	PostOrder1(BT);
	cout << endl << "层次1：" << endl;
	LevelOrderTraversal(BT);
**/
/**
	//AVL树
	AVLTree A = NULL;
	A = Insert(A, 1);
	A = Insert(A, 3);
	A = Insert(A, 5);
	A = Insert(A, 7);
	A = Insert(A, 9);
	cout << endl << "树高：" << GetHeight(A) << endl;
**/
/**
	//图的邻接矩阵--广度优先遍历(BFS)
	MGraph Graph = BuildMGraph();
	Vertex S = 0;
	void(*f)(Vertex) = Visit;
	BFS(Graph, S, f);
**/
/**
	//图的邻接表--深度优先遍历(DFS)
	LGraph Graph = BuildLGraph();
	Vertex S = 0;
	void(*f)(Vertex) = Visit;
	DFS(Graph, S, f);
**/

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

