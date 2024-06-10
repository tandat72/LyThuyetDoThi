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
int sau_nut1[max][max];
void doc(GRAPH &g)
{
	
	FILE* f;
	f = fopen("D:\\020101058\\Floyd\\dothi.txt", "rt");
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
void Init(GRAPH g)
{
	for(int i=0; i<g.n;i++)
		for(int j=0;j<g.n;j++)
			if(g.a[i][j]>0)
			{
				sau_nut1[i][j]=j;
			}
			else
				sau_nut1[i][j]=-1;
}

void Floyd(GRAPH &g)
{
	Init(g);
	for(int k=0;k<g.n;k++)
		for(int i=0;i<g.n;i++)
			if(g.a[i][k]>0)
			{
				for(int j=0;j<g.n;j++)
					if(g.a[k][j]>0)
				{
				
					if((g.a[i][j]==0 && i!=j) || (g.a[i][j]>g.a[i][k]+g.a[k][j]))
			 		{
						g.a[i][j]=g.a[i][k]+g.a[k][j];
						sau_nut1[i][j]=sau_nut1[i][k];
		     		}
				}
			}
}

void ghiFloyd(GRAPH g)
{
	FILE *f;
	int s=0;
	f = fopen("D:\\020101058\\Floyd\\ketqua.txt","wt");
	if(f == NULL) 
	{
		printf("khong ton tai file Ket Qua \n");
		exit(0);
	}
	if(KT_huong(g)==1)
		fprintf(f,"G la do thi co huong\n");
	else
		fprintf(f,"G la do thi vo huong\n");
	for(int i=0;i<g.n;i++)
		for(int j=0;j<g.n;j++)
			if(g.a[i][j]>0)
	{
		int s,t;
		fprintf(f,"\ndo dai tu %d->%d la:%d",i,j,g.a[i][j]);
		s=i;
		t=j;
		fprintf(f,"duong di:%d",s);
		do{
			s=sau_nut1[s][t];
			fprintf(f,"->%d",s);
		}while(s!=t);
		fprintf(f,"\n");
	}
	fclose(f);
}
int main(){
	GRAPH g;
	doc(g);
	
	
	Floyd(g);
	ghiFloyd(g);
	return 1;
	
}
