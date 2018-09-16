#include "pch.h"
#include "Graph.h"
#include <iostream>

using namespace std;

bool Visited[MaxVertexNum] = { false }; /*����ȫ�ֱ���*/

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
		cout << "���п�" << endl;
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
/* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V, W;
	MGraph Graph;
	Graph = (MGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӾ��� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = MAXSIZE;
	return Graph;
}

void InsertEdgeToMGraph(MGraph Graph, Edge E) {
	/* ����� <V1, V2> */
	Graph->G[E->V1][E->V2] = E->Weight;
	/* ��������ͼ����Ҫ�����<V2, V1> */
	Graph->G[E->V2][E->V1] = E->Weight;
}

MGraph BuildMGraph() {
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	cout << "���붥������";
	cin >> Nv; /* ���붥����� */
	Graph = CreateMetrixGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
	cout << endl << "���������";
	cin >> Graph->Ne;  /* ������� */
	if (Graph->Ne > 0) { /* ����б� */
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */
		/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
		for (i = 0; i < Graph->Ne; i++) {
			cout << "���룺V1 V2 Weight " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;
			/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
			InsertEdgeToMGraph(Graph, E);

		}
	}
	/* ������������ݵĻ����������� */
	for (V = 0; V < Graph->Nv; V++)
		cin >> Graph->Data[V];
	return Graph; 
}

LGraph CreateLinkGraph(int VertexNum) {
/* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
	Vertex V;
	LGraph Graph;
	Graph = (LGraph)malloc(sizeof(struct AdjGNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* ��ʼ���ڽӱ�ͷָ�� */
	/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
	for (V = 0; V < Graph->Nv; V++)
		Graph->G[V].FirstEdge = NULL;
	return Graph;
}

void InsertEdgeToLGraph(LGraph Graph, Edge E) {
	PtrToAdjVNode NewNode;
	/* ����� <V1, V2> */
    /* ΪV2�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->Adjv = E->V2;
	NewNode->Weight = E->Weight;
	/* ��V2����V1�ı�ͷ */
	NewNode->Next = Graph->G[E->V1].FirstEdge;
	Graph->G[E->V1].FirstEdge = NewNode;
	/* ��������ͼ����Ҫ����� <V2, V1> */
	/* ΪV1�����µ��ڽӵ� */
	NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
	NewNode->Adjv = E->V1;
	NewNode->Weight = E->Weight;
	/* ��V1����V2�ı�ͷ */
	NewNode->Next = Graph->G[E->V2].FirstEdge;
	Graph->G[E->V2].FirstEdge = NewNode;
}

LGraph BuildLGraph() {
	LGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;
	/* ���붥����� */
	cout << "���붥������";
	cin >> Nv;
	Graph = CreateLinkGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
	/* ������� */
	cout << "���������";
	cin >> Graph->Ne;
	if (Graph->Ne > 0) {
		E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */ 
		for (i = 0; i < Graph->Ne; i++) {
			cout << "���룺V1 V2 Weight " << endl;
			cin >> E->V1 >> E->V2 >> E->Weight;  /* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
			InsertEdgeToLGraph(Graph, E);
		}
	}
	/* ������������ݵĻ����������� */
	for (V = 0; V < Graph->Nv; V++)
		cin >> Graph->G[V].Data;
	return Graph;
}



void DFS(LGraph Graph, Vertex V, void(*f)(Vertex)) {
/* ��VΪ��������ڽӱ�洢��ͼGraph����DFS���� */
	PtrToAdjVNode W;
	f(V); /* ���ʵ�V������ */
	Visited[V] = true; /* ���V�ѷ��� */
	for (W = Graph->G[V].FirstEdge; W; W = W->Next) {
		if (!Visited[W->Adjv]) /* ��W->AdjVδ������ */
			DFS(Graph, W->Adjv, f); /* ��ݹ����֮ */
	}
}

/**
IsEdge(Graph,V,W)���<V,W>�Ƿ���Graph�е�һ���ߣ���W�Ƿ�V���ڽӵ�
�˺�������ͼ�Ĳ�ͬ����Ҫ����ͬ��ʵ�֣��ؼ�ȡ���ڶԲ����ڵıߵı�ʾ������
�������Ȩͼ, ��������ڵı߱���ʼ��ΪMAXSIZE, ����ʵ������:
**/
bool IsEdge(MGraph Graph, Vertex V, Vertex W) {
	return Graph->G[V][W] < MAXSIZE ? true : false;
}

void BFS(MGraph Graph, Vertex S, void(*f)(Vertex)) {
/* ��SΪ��������ڽӾ���洢��ͼGraph����BFS���� */
	VQueue Q;
	Vertex V, W;
	Q = CreateQueue(); /*�����ն���*/
	/* ���ʶ���S���˴��ɸ��ݾ��������Ҫ��д */
	f(S);
	Visited[S] = true; /* ���S�ѷ��� */
	AddQueue(Q, S); /* S����� */
	while (!IsQueueEmpty(Q)) {
		V = DeleteQueue(Q);
		for (W = 0; W < Graph->Nv; W++) {
			if (!Visited[W] && IsEdge(Graph, V, W)) {
				f(W); /* ���ʶ���W */
				Visited[W] = true; /* ���W�ѷ��� */
				AddQueue(Q, W); /* W����� */
			}
		}
	}
}


