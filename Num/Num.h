#pragma once
#include <iostream>
#include <string>

using namespace std;

class Num
{
private:
    //���ڽ�����������ĵ�λ���
    class Node
    {
    public:
        int val;
        Node* next;
        //���캯���Գ�ʼ�����
        Node(int v, Node* n = 0)
        {
            val = v;
            next = n;
        }
    };
    Node* head;
    //���ڱ���Num�����С��Ҳ�������ĳ���
    int size;

public:
    //���ֳ�ʼ�����캯��
    Num(/* args */);
    Num(const string& s);
    Num(const Num& num);
    //����
    ~Num();
    int getSize() const;

    //��ֵ�������˵Ⱥ�
    Num& operator=(const Num& num);

    //ʮ���ƵļӼ��˳�ƽ�����㣬ͨ���������������ʵ��
    Num& operator+=(const Num& num);
    Num& operator-=(const Num& num);
    Num& operator*=(const Num& num);
    Num operator+(const Num& num);
    Num operator-(const Num& num);
    Num operator*(const Num& num);
    Num operator/(const Num& num);

    //�����ƵļӼ��˳�ƽ������
    Num binary_plus(const Num& num);
    Num binary_minus(const Num& num);
    Num binary_multiply(const Num& num);
    Num binary_divide(const Num& num);
    Num binary_pow(int times);

    //һЩ���ܺ�����

    /// <summary>
    /// �ڴ���ǰ���һ�����
    /// </summary>
    /// <param name="number">��ӵĽڵ�ֵΪnumber</param>
    void appendNode(int number);

    /// <summary>
    /// ɾ����������ǰ�˵�����0
    /// </summary>
    void delete_0();

    /// <summary>
    /// ��������10��x�η�����������Ϊ2��x��
    /// </summary>
    /// <param name="x">��Ҫ*10�Ĵ���</param>
    void Mul10(const int& x);

    /// <summary>
    /// ����������10��x�η�����������Ϊ2��x��
    /// </summary>
    /// <param name="x">��Ҫ/10�Ĵ���</param>
    void Div10(const int& x);

    /// <summary>
    /// ��������ת�洢
    /// </summary>
    void reverse();

    /// <summary>
    /// ��ȡ�����ĵ�һλ����
    /// </summary>
    /// <returns></returns>
    int lastdata();

    //һЩ����֮��ıȽ�����
    bool operator<(const Num& num) const;
    bool operator>(const Num& num) const;
    bool operator>=(const Num& num) const;
    bool operator==(const Num& num) const;
    bool operator<=(const Num& num) const;

    //����Ԥ����ĳ˷�
    Num multiply(const Num& num);

    // FFT
    Num multiplyFFT(const Num& num);

    //����
    Num Power(int times);

    //��Ԫ����������<<����
    friend ostream& operator<<(ostream& os, const Num& num);
};
