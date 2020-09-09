#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
int ostu_threshold(float* histogram)
{
    int i=0,j=0,GrayScale=256,threshold;//灰階256
    float w0,w1,u0tmp,u1tmp,u0,u1,u,deltaTmp,deltaMax=0;

    for(i=0;i<GrayScale;i++)
    {
        histogram[i]=(float)histogram[i]/(512*512);//直方圖
    }
    for(i=0;i<GrayScale;i++)//i作為閾值
    {
        w0=w1=u0tmp=u1tmp=u0=u1=u=deltaTmp=0;
        for(j=0;j<GrayScale;j++)
        {
                if (j <= i)   //背景部分
                {
                    w0 += histogram[j];
                    u0tmp += j * histogram[j];
                }
                else   //前景部分
                {
                    w1 += histogram[j];
                    u1tmp += j * histogram[j];
                }
        }
            u0 = u0tmp / w0;
            u1 = u1tmp / w1;
            u = u0tmp + u1tmp;
            deltaTmp = w0 * (u0-u)*(u0-u) + w1 *(u1-u)*(u1-u);//σ平方算法
            if (deltaTmp > deltaMax)//決定閾值
            {
                deltaMax = deltaTmp;
                threshold = i;
            }

    }
    return threshold;
}
int main()
{
    char a;
    int bmp[262144]={0},getC,thresh;//bmp  256 * 256 * 4 = 262144 bytes
    float grayPixelNum[256]={0};//灰階值數
    FILE *file = fopen("LENNA (1).bmp", "rb");
    FILE *out = fopen("Lenna_Otsu.bmp", "wb");

    for(int i=0;i<1078;i++)//複製標頭檔 bmp的
    {
        a=fgetc(file);//開啟檔案之後，用fgetc來讀取檔案中的字元
        fputc(a,out);//fputc將字元寫入檔案
    }
    for(int i=0;i<262144;i++)
    {
        getC=fgetc(file);
        grayPixelNum[getC]++;//計算灰階圖像素的數量
        bmp[i]=getC;
    }
    thresh=ostu_threshold(grayPixelNum);//算出閾值
    cout<<thresh<<endl;//確認閾值
    for(int i=0;i<262144;i++)//是否大於閾值，非黑即白
    {
        if(bmp[i] < thresh)
            fputc(0,out);
        else
            fputc(255,out);
    }
    fclose(file);
    fclose(out);

    return 0;
}
