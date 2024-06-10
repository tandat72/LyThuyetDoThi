#include<process.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#define max 100

typedef struct{
	int n;
	int a[max][max];
}Graph;

typedef struct{
	int v;
	int w;	
}EDGE;
EDGE T[max];
int nT;
int lblvertex[max];
int nlbl;
int valueMin[max];
int nhan[100];
int soTPLT;

void doc(Graph &g){
	FILE *f;
	f = fopen("D:\\020101058\\dothiprim.txt","rt");
	if(f==NULL){
		printf("Khong ton tai file dothi.txt\n");
		exit(0);
	}
	
	fscanf(f,"%d",&g.n);
	
	for(int i=0; i<g.n; i++){
		for(int j=0; j<g.n; j++){
			fscanf(f,"%d",&g.a[i][j]);
		}
	}
	
	fclose(f);
}

int kiemtrahople (Graph g){
	for(int i=0; i<g.n; i++)
		if(g.a[i][i] != 0)
			return 0;
	return 1;
	
}

int kt_huong(Graph g){
	for(int i=0; i<g.n; i++){
		for(int j=i+1; j<g.n; j++)
			if(g.a[i][j] != g.a[i][j])
				return 1;	
	}
	return 0;
}

void vistit (Graph g, int i, int labels){
	nhan[i] = labels;
	for(int j=0; j<g.n; j++)
		if(nhan[j] ==0 && (g.a[i][j] != 0))
			vistit(g,j,labels);
}

void xetLienthong (Graph g){
	for(int i=0; i<g.n; i++)
		nhan[i] = 0;
	soTPLT = 0;
	for(int i = 0; i<g.n; i++)
		if(nhan[i] == 0){
			soTPLT++;
			vistit(g,i,soTPLT);
		}
}

//void ghi(Graph g){
//	FILE *f;
//	f = fopen("D:\\Kq.txt","wt");
//	if(f == NULL){
//		printf("Khong ton tai file TPLT_out\n");
//		exit(0);
//	}
//	if(kt_huong(g) == 1)
//		fprintf(f,"G la do thi co huong\n");
//	else
//		fprintf(f,"G la do thi vo huong\n");
//	if(soTPLT == 1)
//		fprintf(f,"\nG lien thong\n");
//	else fprintf(f,"\nG khong lien thong ma chi chua thanh phan lien thong\n");
//	
//	fprintf(f,"\nso thanh phan lien thong: %d\n",soTPLT);
//	for(int i = 0; i < soTPLT; i++){
//		fprintf(f,"\nthanh phan thu %d: ", i+1);
//		
//		for(int j = 0; j < g.n; j++){
//			if(nhan[j] == i+1){
//				fprintf(f,"%d", j+1);
//			}
//		}
//		fprintf(f,"\n");
//	}
//	fclose(f);
//}

void prim(Graph g){
	int tam = 0;
	nT = 0;
	for(int i = 0; i < g.n; i++)
		lblvertex[i] = 0;
	
	lblvertex[0] = 1;
	while(nT < g.n-1){
		EDGE edgeMin;
		int nMinWeight = -1;
		
		for(int w=0; w < g.n; w++){
			if(lblvertex[w]==0){
				for(int v=0; v<g.n; v++){
					if(lblvertex[v]!=0 && (g.a[v][w]!=0 || g.a[w][v]!=0)){
						if(nMinWeight < 0 || g.a[v][w]<nMinWeight){
							edgeMin.v=v;
							edgeMin.w=w;
							nMinWeight=g.a[v][w];
						}
					}
				}
			}
		}
		T[nT]=edgeMin;	
		valueMin[nT]=nMinWeight;
		nT++;
		lblvertex[edgeMin.w] = 1;
	}
}

void ghiprim(Graph g){
	FILE *f;
	int s=0;
	f = fopen("D:\\020101058\\ketqua-prim-nhonhat.txt","wt");
	if(f == NULL){
		printf("Khong ton tai file PRIM_out\n");
		exit(0);
	}
	if(kt_huong(g) == 1)
		fprintf(f,"G la do thi vo huong\n");
	else
		fprintf(f,"G la do thi co huong\n");
	for(int i = 0; i < nT; i++)
		fprintf(f,"{%d,%d}"  , T[i].v,T[i].w);
	for(int j = 0; j < g.n; j++)
		s=s+valueMin[j];
	fprintf(f,"\ndo dai cay khung nho nhat: %d",s);
	fclose(f);
}


int main(){
	Graph g;
	doc(g);
	xetLienthong(g);
	if(kiemtrahople(g) == 1){
		if(soTPLT == 1){
			xetLienthong(g);
			prim(g);
			ghiprim(g);
		}
		else
			printf("G khong lien thong nen khong co cay khung nho nhat");
	}
	else
		printf("do thi G khong hop le\n");
		return 1;
	getch();
}












