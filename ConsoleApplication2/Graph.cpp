#include "pch.h"
#include "Graph.h"
#include "Tree.h"
#include <iostream>

using namespace std;

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
			cin >> E->V1 >> E->V2 >> E->Weight;  /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
			InsertEdgeToLGraph(Graph, E);
		}
	}
	/* 如果顶点有数据的话，读入数据 */
	for (V = 0; V < Graph->Nv; V++)
		cin >> Graph->G[V].Data;
	return Graph;
}

void Visit(Vertex V) {
	printf("正在访问顶点%d\n", V);
}

void DFS(LGraph Graph, Vertex V, void(*Visit)(Vertex)) {
/* 以V为出发点对邻接表存储的图Graph进行DFS搜索 */
	PtrToAdjVNode W;
	Visit(V); /* 访问第V个顶点 */
	Visited[V] = true; /* 标记V已访问 */
	for (W = Graph->G[V].FirstEdge; W; W = W->Next) {
		if (!Visited[W->Adjv]) /* 若W->AdjV未被访问 */
			DFS(Graph, W->Adjv, Visit); /* 则递归访问之 */
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

void BFS(MGraph Graph, Vertex S, void(*Visit)(Vertex)) {
	
}
