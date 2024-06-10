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
int nhan[100];
int soTPLT;
void doc(GRAPH &g)
{
	FILE *f;
	f=fopen("D:\\020101058\\dothilienthong.txt","rt");
	if(f==NULL)
	{
		printf("Khong ton tai File dothi.txt \n");
		exit(0);
	}
	fscanf(f,"%d",&g.n);
	for(int i=0; i<g.n; i++)
	{
		for(int j=0;j<g.n;j++)
		{
			fscanf(f,"%d",&g.a[i][j]);
		}
	}
	
	fclose(f);
}
int kiemTRahople(GRAPH g)
{
	for(int i=0;i<g.n;i++)
	    if(g.a[i][i]!=0)
        	return 0;
	return 1;
}
int kt_huong(GRAPH g)
{
	for(int i=0;i<g.n;i++)
	{
		for(int j=i+1;j<g.n;j++)
		   if(g.a[i][j]!=g.a[j][i])
		       return 1;//la do thi co huong
	}
	return 0;//la do thi vo huong
}
void vistit(GRAPH g,int i,int labels)
{
	nhan[i]=labels;
	for(int j=0;j<g.n;j++)
	   if(nhan[j]==0 && (g.a[i][j] != 0 || g.a[j][i]!=0))
	      vistit(g,j,labels);
}
void XetLienThong(GRAPH g)
{
	for(int i=0; i<g.n; i++)
	   nhan[i] = 0;
	soTPLT=0;
	for(int i=0; i<g.n; i++)
	   if(nhan[i] == 0)
	   {
	    	soTPLT++;
	    	vistit(g,i,soTPLT);
	   }
}
void ghi(GRAPH g)
{
	FILE *f;
	f=fopen("D:\\020101058\\ketqua-lienthong.txt","wt");
	if(f==NULL)
	{
		printf("Khong ton tai file TPLT_out\n");
		exit(0);
	}
	if(kt_huong(g)==1)
	   fprintf(f,"G la do thi co huong\n");
	else
	   fprintf(f,"G la do thi vo huong\n");
	if(soTPLT == 1)
	   fprintf(f,"\nG lien thong\n");
	else fprintf(f,"\nG khong lien thong ma chi chua thanh phan lien thong\n");
	fprintf(f,"\nso thanh phan lien thong:%d\n",soTPLT);
	for(int i=0;i<soTPLT;i++)
	{
		fprintf(f,"\nthanh phan thu %d: ",i+1);
		for(int j=0;j<g.n;j++)
		{
			if(nhan[j]==i+1)
			{
				fprintf(f,"%d",j+1);
			}
		}
		fprintf(f,"\n");
	}
	fclose(f);
}
int main()
{
	GRAPH g;
	doc(g);
	if(kiemTRahople(g)==1)
	{
		XetLienThong(g);
		ghi(g);
	}
	else
	printf("do thi G khong hop le");
}
