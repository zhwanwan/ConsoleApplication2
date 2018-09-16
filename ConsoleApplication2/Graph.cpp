#include "pch.h"
#include "Graph.h"
#include <iostream>

using namespace std;

bool Visited[MaxVertexNum] = { false }; /*定义全局变量*/

VQueue CreateQueue(){
	VQueue Q = (VQueue)malloc(sizeof(struct QuNode));
	Q->Front = Q->Rear = NULL;
	return Q;
}

bool IsQueueEmpty(VQueue Q) {
	return Q->Front == NULL;
}

void AddQueue(VQueue Q, Vertex V) {
	VPosition temCell;
	temCell = (VPosition)malloc(sizeof(struct VNode));
	temCell->Data = V;
	temCell->Next = NULL;
	if (IsQueueEmpty(Q)) {
		Q->Front = Q->Rear = temCell;
	}
	else {
		Q->Rear->Next = temCell;
		Q->Rear = temCell;
	}
}

Vertex DeleteQueue(VQueue Q) {
	VPosition FrontCell;
	Vertex FrontElem;
	if (IsQueueEmpty(Q)) {
		cout << "队列空" << endl;
		return NULL;
	}
	else {
		FrontCell = Q->Front;
		FrontElem = FrontCell->Data;
		if (Q->Front == Q->Rear) {
			Q->Front = Q->Rear = NULL;
		}
		else {
			Q->Front = Q->Front->Next;
		}
		free(FrontCell);
		return FrontElem;
	}
}

MGraph CreateMetrixGraph(int VertexNum) {
/* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V, W;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接矩阵 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = MAXSIZE;
	return Graph;
}

void InsertEdgeToMGraph(MGraph Graph, Edge E) {
	/* 插入边 <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* 若是无向图，还要插入边<V2, V1> */
	Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMGraph() {
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	cout << "输入顶点数：";
	cin >> Nv; /* 读入顶点个数 */
	Graph = CreateMetrixGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */ 
	cout << endl << "输入边数：";
	cin >> Graph->Ne;  /* 读入边数 */
	if (Graph->Ne > 0) { /* 如果有边 */
		E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
		/* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
		for (i = 0; i < Graph->Ne; i++) {
			cout << "输入：V1 V2 Weight " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;
			/* 注意：如果权重不是整型，Weight的读入格式要改 */
			InsertEdgeToMGraph(Graph, E);

		}
	}
	/* 如果顶点有数据的话，读入数据 */
	for (V = 0; V < Graph->Nv; V++)
		cin >> Graph->Data[V];
	return Graph; 
}

LGraph CreateLinkGraph(int VertexNum) {
/* 初始化一个有VertexNum个顶点但没有边的图 */
	Vertex V;
	LGraph Graph;
	Graph = (LGraph)malloc(sizeof(struct AdjGNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接表头指针 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;
	return Graph;
}

void InsertEdgeToLGraph(LGraph Graph, Edge E) {
	PtrToAdjVNode NewNode;
	/* 插入边 <V1, V2> */
    /* 为V2建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->Adjv = E->V2;
	NewNode->Weight = E->Weight;
	/* 将V2插入V1的表头 */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	/* 若是无向图，还要插入边 <V2, V1> */
	/* 为V1建立新的邻接点 */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->Adjv = E->V1;
	NewNode->Weight = E->Weight;
	/* 将V1插入V2的表头 */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildLGraph() {
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	/* 读入顶点个数 */
	cout << "输入顶点数：";
	cin >> Nv;
	Graph = CreateLinkGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */ 
	/* 读入边数 */
	cout << "输入边数：";
	cin >> Graph->Ne;
	if (Graph->Ne > 0) {
		E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */ 
		for (i = 0; i < Graph->Ne; i++) {
			cout << "输入：V1 V2 Weight " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;  /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
			InsertEdgeToLGraph(Graph, E);
		}
	}
	/* 如果顶点有数据的话，读入数据 */
	for (V = 0; V < Graph->Nv; V++)
		cin >> Graph->G[V].Data;
	return Graph;
}



void DFS(LGraph Graph, Vertex V, void(*f)(Vertex)) {
/* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
	PtrToAdjVNode W;
	f(V); /* 访问第V个顶点 */
	Visited[V] = true; /* 标记V已访问 */
	for (W = Graph->G[V].FirstEdge; W; W = W->Next) {
		if (!Visited[W->Adjv]) /* 若W->AdjV未被访问 */
			DFS(Graph, W->Adjv, f); /* 则递归访问之 */
	}
}

/**
IsEdge(Graph,V,W)检查<V,W>是否是Graph中的一条边，即W是否V的邻接点
此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。
例如对有权图, 如果不存在的边被初始化为MAXSIZE, 则函数实现如下:
**/
bool IsEdge(MGraph Graph, Vertex V, Vertex W) {
	return Graph->G[V][W] < MAXSIZE ? true : false;
}

void BFS(MGraph Graph, Vertex S, void(*f)(Vertex)) {
/* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
	VQueue Q;
	Vertex V, W;
	Q = CreateQueue(); /*创建空队列*/
	/* 访问顶点S：此处可根据具体访问需要改写 */
	f(S);
	Visited[S] = true; /* 标记S已访问 */
	AddQueue(Q, S); /* S入队列 */
	while (!IsQueueEmpty(Q)) {
		V = DeleteQueue(Q);
		for (W = 0; W < Graph->Nv; W++) {
			if (!Visited[W] && IsEdge(Graph, V, W)) {
				f(W); /* 访问顶点W */
				Visited[W] = true; /* 标记W已访问 */
				AddQueue(Q, W); /* W入队列 */
			}
		}
	}
}


