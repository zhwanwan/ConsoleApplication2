#include "pch.h"

#define MaxVertexNum 100 /*最大顶点数为100*/
#define MAXSIZE 65535 /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;   /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;  /* 边的权值设为整型 */
typedef char DataType;  /* 顶点存储的数据类型设为字符型 */

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V1, V2; /* 有向边<V1, V2> */
	WeightType Weight; /* 权重 */
};
typedef PtrToENode Edge;

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
	int Nv; /* 顶点数 */
	int Ne; /* 边数   */
	WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
	DataType Data[MaxVertexNum]; /* 存顶点的数据 */
	/* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */

/* 邻接点的定义 */
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode {
	Vertex Adjv; /* 邻接点下标 */
	WeightType Weight; /* 边权重 */
	PtrToAdjVNode Next;  /* 指向下一个邻接点的指针 */
};

/* 顶点表头结点的定义 */
typedef struct Vnode {
	PtrToAdjVNode FirstEdge;  /* 边表头指针 */
	DataType Data; /* 存顶点的数据 */
	/* 注意：很多情况下，顶点无数据，此时Data可以不用出现 */
} AdjList[MaxVertexNum]; /* AdjList是邻接表类型 */

typedef struct AdjGNode *PtrToAdjGNode;
struct AdjGNode {
	int Nv; /* 顶点数 */
	int Ne; /* 边数   */
	AdjList G; /* 邻接表 */
};
typedef PtrToAdjGNode LGraph; /* 以邻接表方式存储的图类型 */

/*图的邻接矩阵构造*/
MGraph CreateMetrixGraph(int VertexNum);
void InsertEdgeToMGraph(MGraph Graph, Edge E);
MGraph BuildMGraph();

/*图的邻接表构造*/
LGraph CreateLinkGraph(int VertexNum);
void InsertEdgeToLGraph(LGraph Graph, Edge);
LGraph BuildLGraph();



