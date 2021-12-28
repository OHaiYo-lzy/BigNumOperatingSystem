#pragma once
#include "Num.h"
#define N 350000
const double pi = 3.141592653;

/// <summary>
/// ���ֵ�ֵ�Ƚ�����string��֮��Ĵ�С
/// </summary>
/// <param name="a">��1</param>
/// <param name="b">��2<param>
/// <returns></returns>
bool cmp(const string &a, const string &b)
{
    if (a.size() < b.size())
        return true;
    else if (a.size() > b.size())
        return false;
    else
        return a < b;
}

/// <summary>
/// ��������doubleֵ
/// </summary>
void Swap(double &x, double &y)
{
    double t = x;
    x = y;
    y = t;
}

/// <summary>
/// ��תһ��int���͵�����
/// </summary>
/// <param name="x"></param>
/// <param name="len"></param>
/// <returns></returns>
int rev(int x, int len)
{
    int ans = 0;
    for (int i = 1; i <= len; i++)
    {
        ans <<= 1;
        ans |= x & 1;
        x >>= 1;
    }
    return ans;
}

/// <summary>
/// fft�������ԭ����ʽ��n��n�η�����ֵ
/// </summary>
/// <param name="reA">ʵ��</param>
/// <param name="inA">�鲿</param>
/// <param name="n"></param>
/// <param name="flag">��־</param>
double rea[N], ina[N], reb[N], inb[N], ret[N], intt[N];
int i, len1, len2, lent, lenres, len;
int res[N >> 1];
void FFT(double *reA, double *inA, int n, int flag)
{
    int j, k;
    int lgn = log((double)n) / log((double)2);
    for (int i = 0; i < n; i++) //��������
    {
        j = rev(i, lgn);
        if (j > i)
        {
            Swap(reA[i], reA[j]);
            Swap(inA[i], inA[j]);
        }
    }

    for (int s = 1; s <= lgn; s++)
    {
        int m = (1 << s);
        double reWm = cos(2 * pi / m), inWm = sin(2 * pi / m);
        if (flag)
            inWm = -inWm;
        for (k = 0; k < n; k += m)
        {
            double reW = 1.0, inW = 0.0;
            for (int j = 0; j <= m / 2 - 1; j++)
            {
                int tag = k + j + m / 2;
                double reT = reW * reA[tag] - inW * inA[tag];
                double inT = reW * inA[tag] + inW * reA[tag];
                double reU = reA[k + j], inU = inA[k + j];
                reA[k + j] = reU + reT;
                inA[k + j] = inU + inT;
                reA[tag] = reU - reT;
                inA[tag] = inU - inT;
                double reWt = reW * reWm - inW * inWm;
                double inWt = reW * inWm + inW * reWm;
                reW = reWt;
                inW = inWt;
            }
        }
    }
}