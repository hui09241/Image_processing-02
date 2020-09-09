#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
int ostu_threshold(float* histogram)
{
    int i=0,j=0,GrayScale=256,threshold;//�Ƕ�256
    float w0,w1,u0tmp,u1tmp,u0,u1,u,deltaTmp,deltaMax=0;

    for(i=0;i<GrayScale;i++)
    {
        histogram[i]=(float)histogram[i]/(512*512);//�����
    }
    for(i=0;i<GrayScale;i++)//i�@���H��
    {
        w0=w1=u0tmp=u1tmp=u0=u1=u=deltaTmp=0;
        for(j=0;j<GrayScale;j++)
        {
                if (j <= i)   //�I������
                {
                    w0 += histogram[j];
                    u0tmp += j * histogram[j];
                }
                else   //�e������
                {
                    w1 += histogram[j];
                    u1tmp += j * histogram[j];
                }
        }
            u0 = u0tmp / w0;
            u1 = u1tmp / w1;
            u = u0tmp + u1tmp;
            deltaTmp = w0 * (u0-u)*(u0-u) + w1 *(u1-u)*(u1-u);//�m�����k
            if (deltaTmp > deltaMax)//�M�w�H��
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
    float grayPixelNum[256]={0};//�Ƕ��ȼ�
    FILE *file = fopen("LENNA (1).bmp", "rb");
    FILE *out = fopen("Lenna_Otsu.bmp", "wb");

    for(int i=0;i<1078;i++)//�ƻs���Y�� bmp��
    {
        a=fgetc(file);//�}���ɮפ���A��fgetc��Ū���ɮפ����r��
        fputc(a,out);//fputc�N�r���g�J�ɮ�
    }
    for(int i=0;i<262144;i++)
    {
        getC=fgetc(file);
        grayPixelNum[getC]++;//�p��Ƕ��Ϲ������ƶq
        bmp[i]=getC;
    }
    thresh=ostu_threshold(grayPixelNum);//��X�H��
    cout<<thresh<<endl;//�T�{�H��
    for(int i=0;i<262144;i++)//�O�_�j���H�ȡA�D�§Y��
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
