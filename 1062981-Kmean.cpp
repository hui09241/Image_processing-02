#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
int bmp[512][512]={{0}},kmean[512][512]={0};
void k_means(int Image[512][512],int cluster[512][512],int K){//課本
        int i,j,k,T,EN;
        int **Cents,**tmpcts,*NCP,**data_points;
        long double Error,Dm,Dn,Min,Dis,*lmindis;
        EN=0;
        for(i=0;i<512;i++)
            for(j=0;j<512;j++)
        {
            if(Image[i][j]==0)//前ostu結果黑色是0而課本是1

                EN++;
        }
        data_points=new int *[EN];
        for(i=0;i<EN;i++)
            data_points[i]=new int[2];
        int z;
        z=0;
        for(i=0;i<512;i++)
            for(j=0;j<512;j++)
        {
            if(Image[i][j]==0)
            {
                data_points[z][0]=i;
                data_points[z][1]=j;
                z++;
            }
        }
        Cents=new int*[K+1];
        tmpcts= new int*[K+1];
        for(int i=1;i<=K;i++)
        {
            Cents[i]=new int[2];
            tmpcts[i]=new int [2];
        }
        int v;
        srand(time(NULL));//亂數
        for(i=1;i<=K;i++)
        {
            v=rand();
            Cents[i][0]=data_points[v][0];
            Cents[i][1]=data_points[v][1];
        }
        NCP=new int[K+1];
        lmindis=new long double [K+1];
        Dm=0x7fffffff;
        Error=0.005;
        do{
            for(i=1;i<=K;i++)
            {
                lmindis[i]=0;
                tmpcts[i][0]=0;
                tmpcts[i][1]=1;
                NCP[i]=0;
            }
            for(i=0;i<512;i++)
                for(j=0;j<512;j++)
            {
                if(Image[i][j]==0)
                {
                    Min=0x7fffffff;
                    for(k=1;k<=K;k++)
                    {
                        Dis=sqrt((i-Cents[k][0])*(i-Cents[k][0])+(j-Cents[k][1])*(j-Cents[k][1]));
                        if(Min>Dis)
                        {
                            Min=Dis;
                            cluster[i][j]=k;
                        }
                    }
                    T=cluster[i][j];
                    NCP[T]++;
                    lmindis[T]+=Min;
                    tmpcts[T][0]+=i;
                    tmpcts[T][1]+=j;
                }
            }
            for(i=1;i<=K;i++)
            {
                if(NCP[i]>0)
                {
                    Cents[i][0]=tmpcts[i][0]/NCP[i];
                    Cents[i][1]=tmpcts[i][1]/NCP[i];
                }
            }
            Dn=Dm;
            Dm=0;
            for(i=1;i<=K;i++)
                Dm+=lmindis[i];

            Dm/=EN;
        }while(((Dn-Dm)/Dm)>Error);
}
int main()
{
    char a;
    FILE *file = fopen("Lenna_Otsu.bmp", "rb");
    FILE *kout = fopen("Lenna_Kmeans.bmp", "wb");

    for(int i=0;i<1078;i++)//複製標頭檔 bmp的
    {
        a = fgetc(file);
        fputc(a,kout);
    }
    for(int i=0;i<512;i++)
        for(int j=0;j<512;j++){
            bmp[i][j]=fgetc(file);
            kmean[i][j]=bmp[i][j];
        }
    k_means(bmp,kmean,4);
    for(int i=0;i<512;i++){//將不同群的像素分配成1.2.3...
        for(int j=0;j<512;j++){
            if(bmp[i][j]==0){
                if(kmean[i][j]==1)
                    fputc(0,kout);
                else if(kmean[i][j]==2)
                    fputc(50,kout);
                else if(kmean[i][j]==3)
                    fputc(100,kout);
                else if(kmean[i][j]==4)
                    fputc(150,kout);
            }
            else
                fputc(255,kout);
        }
    }
     fclose(kout);

    fclose(file);

}
