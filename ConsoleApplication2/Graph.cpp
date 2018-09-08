#include "pch.h"
#include "Graph.h"
#include <iostream>

using namespace std;

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
			cin >> E->V1 >> E->V2 >> E->Weight;  /* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
			InsertEdgeToLGraph(Graph, E);
		}
	}
	/* ������������ݵĻ����������� */
	for (V = 0; V < Graph->Nv; V++)
		cin >> Graph->G[V].Data;
	return Graph;
}
