#include "pch.h"

#define MaxVertexNum 100 /*��󶥵���Ϊ100*/
#define MAXSIZE 65535 /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
typedef int Vertex;   /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;  /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;  /* ����洢������������Ϊ�ַ��� */

/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V1, V2; /* �����<V1, V2> */
	WeightType Weight; /* Ȩ�� */
};
typedef PtrToENode Edge;

/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv; /* ������ */
	int Ne; /* ����   */
	WeightType G[MaxVertexNum][MaxVertexNum]; /* �ڽӾ��� */
	DataType Data[MaxVertexNum]; /* �涥������� */
	/* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
};
typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */

/* �ڽӵ�Ķ��� */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex Adjv; /* �ڽӵ��±� */
	WeightType Weight; /* ��Ȩ�� */
	PtrToAdjVNode Next;  /* ָ����һ���ڽӵ��ָ�� */
};

/* �����ͷ���Ķ��� */
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;  /* �߱�ͷָ�� */
	DataType Data; /* �涥������� */
	/* ע�⣺�ܶ�����£����������ݣ���ʱData���Բ��ó��� */
} AdjList[MaxVertexNum]; /* AdjList���ڽӱ����� */

typedef struct AdjGNode *PtrToAdjGNode;
struct AdjGNode {
	int Nv; /* ������ */
	int Ne; /* ����   */
	AdjList G; /* �ڽӱ� */
};
typedef PtrToAdjGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */

/*ͼ���ڽӾ�����*/
MGraph CreateMetrixGraph(int VertexNum);
void InsertEdgeToMGraph(MGraph Graph, Edge E);
MGraph BuildMGraph();

/*ͼ���ڽӱ���*/
LGraph CreateLinkGraph(int VertexNum);
void InsertEdgeToLGraph(LGraph Graph, Edge);
LGraph BuildLGraph();



