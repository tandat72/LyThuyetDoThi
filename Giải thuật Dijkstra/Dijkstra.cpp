#include<process.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#define max 100
#define MAXINT 32767
typedef struct
{
	int n;
	int a[max][max];
}GRAPH;
int nT; 
int T[max]; 
int DODAI[max]; 
int NHAN[max]; 
int nhan[100];
int dinhdau;
int soTPLT;
void doc(GRAPH &g)
{
	
	FILE* f;
	f = fopen("D:\\020101058\\Dijkstra\\dothi.txt", "rt");
	if (f == NULL){
		printf("Khong mo duoc file Do Thi.txt\n");
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
int KT_huong(GRAPH g)
{
	int i,j;
	for(i=0;i<g.n;i++){
		for(j=i+1; j<g.n; j++)
			if(g.a[i][j] != g.a[j][i])
			return 1;
	}
	return 0;
}
void Init(GRAPH g,int dinhdau)
{
	for(int i=0; i<g.n;i++)
	{
		T[i]=1;
		DODAI[i]=MAXINT;
		NHAN[i]=-1;
	}
	DODAI[dinhdau]=0;
}

void DIJKSTRA(GRAPH g,int dinhdau)
{
	int min,v,j=0;
	Init(g,dinhdau);
	while(j<g.n)
	{
		min=MAXINT;
		v=-1;
		for(int i=0;i<g.n;i++)
		if(T[i]!=0 && DODAI[i]<min)
		{
			min=DODAI[i];
			v=i;
		}
		if(v==-1) break;
		T[v]=0;
		for(int k=0;k<g.n;k++)
			if(g.a[v][k]!=0 && DODAI[k]> DODAI[v]+ g.a[v][k])
			{
				DODAI[k]=DODAI[v]+g.a[v][k];
				NHAN[k]=v;
			}
			j++;
	}
}

void ghiDijkstra(GRAPH g, int dinhdau)
{
	int a,j,dao[max],k;
	FILE *f;
	int s=0;
	f = fopen("D:\\020101058\\Dijkstra\\ketqua.txt","wt");
	if(f == NULL) 
	{
		printf("khong ton tai file Ket Qua \n");
		exit(0);
	}
	if(KT_huong(g)==1)
		fprintf(f,"G la do thi co huong\n");
	else
		fprintf(f,"G la do thi vo huong\n");
	for(int i=0;i<g.n;i++){
	if(NHAN[i]!=-1)
	{
		k=0;
		a=dinhdau;
		j=i;
		dao[0]=j;
		do{
			k++;
			j=NHAN[j];
			dao[k]=j;
		}while(j!=a);
		fprintf(f,"\nchieu dai tu %d->%d la:%d",a,i,DODAI[i]);
		fprintf(f," chu trinh:%d",dao[k]);
		for(int n=k-1;n>=0;n--)
			fprintf(f,"->%d",dao[n]);
		fprintf(f,"\n");
	}
	else
		if(DODAI[i]!=0)
			fprintf(f,"\nkhong co duong di tu %d->%d\n",dinhdau,i);
   }
	fclose(f);
}
int main(){
	GRAPH g;
	doc(g);
	printf("Nhap dinh dau: ");
	scanf("%d",&dinhdau);
	
	DIJKSTRA(g,dinhdau);
	ghiDijkstra(g,dinhdau);
	return 1;
	
}
