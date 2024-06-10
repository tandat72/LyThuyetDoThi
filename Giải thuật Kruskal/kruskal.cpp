#include<process.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#define max 100
typedef struct
{
	int n;
	int a[max][max];
}GRAPH;
typedef struct
{
	int v;
	int w;
}EDGE;
EDGE T[max];
int nT;
EDGE IstEdge[max*(max-1)/2];
int lblvertex[max];
int nlbl;
int valueMin[max];
int nEdgeCount;
int nhan [100];
int soTPLT;
void doc(GRAPH &g)
{
	
	FILE* f;
	f = fopen("D:\\020101058\\G1.txt", "rt");
	if (f == NULL){
		printf("Khong mo duoc file G1.txt\n");
		exit(0);
	}
	fscanf(f, "%d", &g.n);
	int i, j;
	for (i=0; i<g.n; i++){
		for (j=0; j<g.n; j++){
			fscanf(f, "%d", &g.a[i][j]);
		}	
	}
		fclose(f);
}
int KiemTraHopLe(GRAPH g){
	for (int i=0; i<g.n; i++)
		if (g.a[i][i] != 0)
			return 0;
	return 1;	
}
int KT_huong(GRAPH g)
{
	int i, j;
	for (i=0; i<g.n; i++){
		for (j=i+1; j<g.n; j++)
			if (g.a[i][j] != g.a[j][i])
				return 1;
	}
	return 0;
}
void vistit(GRAPH g,int i,int labels)
{
	nhan[i]=labels;
	for(int j=0; j <g.n;j++)
		if(nhan[j]==0 && (g.a[i][j] != 0))
			vistit(g,j,labels);
}
void XetLienThong(GRAPH g)
{
	for(int i=0; i<g.n;i++)
		nhan[i] =0;
	    soTPLT=0;
	for (int i=0;i<g.n; i++)
		if (nhan[i]==0){
			soTPLT++;
			 vistit(g, i, soTPLT);
		}	 
}
void InitListEdge(GRAPH &g)
{
	nEdgeCount = 0;
	for(int i = 0; i<g.n; i++)
		for (int j=i+1; j<g.n; j++)
		if (g.a[i][j] != 0)
		{
			IstEdge[nEdgeCount].v = i;
			IstEdge[nEdgeCount].w = j;	
			nEdgeCount++;		
		}
		else
		{
			if (g.a[j][i] != 0)
			{
				IstEdge[nEdgeCount].v = j;
				IstEdge[nEdgeCount].w = i;	
				nEdgeCount++;		
			}
		}
}
void SortListEdge(GRAPH &g)
{
	EDGE tam;
	for(int i = 0; i<nEdgeCount-1; i++)
		for (int j=i+1; j<nEdgeCount; j++)
		if(g.a[IstEdge[i].v][IstEdge[i].w]>g.a[IstEdge[j].v][IstEdge[j].w])
		{
			tam = IstEdge[i];
			IstEdge[i] = IstEdge[j];
			IstEdge[j] = tam;
		}
}
bool IsCircle(int idx, GRAPH g)
{
	if(lblvertex[IstEdge[idx].v]==lblvertex[IstEdge[idx].w])
		return true;
	else
	{
			if(lblvertex[IstEdge[idx].v]<lblvertex[IstEdge[idx].w])
			{
				for(int i = 0; i<g.n; i++)
					if(lblvertex[i]==lblvertex[IstEdge[idx].w])
					lblvertex[i]=lblvertex[IstEdge[idx].v];
			}
			else
			{
				for(int i = 0; i<g.n; i++)
					if(lblvertex[i]==lblvertex[IstEdge[idx].v])
					lblvertex[i]=lblvertex[IstEdge[idx].w];
			}
	}
	return false;
}
void Kruskal(GRAPH g)
{
	nT=0;
	nlbl=0;
	for(int i=0;i<g.n;i++)
		lblvertex[i]=i;
	int eMinIndex=0;
	while(nT<g.n-1)
	{
		if(eMinIndex < nEdgeCount)
		{
			if(IsCircle(eMinIndex,g)==false)
			{
				T[nT]=IstEdge[eMinIndex];
				valueMin[nT]=g.a[IstEdge[eMinIndex].v][IstEdge[eMinIndex].w];
				nT++;
			}
			eMinIndex++;
		}
		else
		{
			break;
		}
	}
}
void ghiKruskal(GRAPH g)
{
	FILE *f;
	int s = 0;
	f = fopen("D:\\020101058\\kqg1.txt","wt");
	if(f == NULL) 
	{
		printf("khong ton tai file kqg1.txt\n");
		exit(0);
	}
	if(KT_huong(g)==1)
		fprintf(f,"G la do thi co huong\n");
	else
		fprintf(f,"G la do thi vo huong\n");
	for(int i=0;i<nT;i++)
		fprintf(f,"%d,%d", T[i].v+1,T[i].w+1);
	for(int j = 0;j<g.n;j++)
		s=s+valueMin[j];
	fprintf(f,"\nDo dai cay khung nho nhat:%d",s);
	fclose(f);
}
int main(){
	GRAPH g;
	doc(g);
	XetLienThong(g);
	if(KiemTraHopLe(g)==1)
	{
		if(soTPLT==1)
		{
			InitListEdge(g);
			SortListEdge(g);
			Kruskal(g);
			ghiKruskal(g);
		}
		else
			printf("G khong lien thong nen khong co cay khung nho nhat");
	}
	else
	printf("Do thi G khong hop le\n");
	return 1;
}
