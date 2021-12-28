#pragma once
#include <iostream>
#include <string>

using namespace std;

class Num
{
private:
    //用于建立单向链表的单位结点
    class Node
    {
    public:
        int val;
        Node* next;
        //构造函数以初始化结点
        Node(int v, Node* n = 0)
        {
            val = v;
            next = n;
        }
    };
    Node* head;
    //用于保存Num对象大小，也即大数的长度
    int size;

public:
    //三种初始化构造函数
    Num(/* args */);
    Num(const string& s);
    Num(const Num& num);
    //析构
    ~Num();
    int getSize() const;

    //赋值，重载了等号
    Num& operator=(const Num& num);

    //十进制的加减乘除平方运算，通过重载运算符号来实现
    Num& operator+=(const Num& num);
    Num& operator-=(const Num& num);
    Num& operator*=(const Num& num);
    Num operator+(const Num& num);
    Num operator-(const Num& num);
    Num operator*(const Num& num);
    Num operator/(const Num& num);

    //二进制的加减乘除平方运算
    Num binary_plus(const Num& num);
    Num binary_minus(const Num& num);
    Num binary_multiply(const Num& num);
    Num binary_divide(const Num& num);
    Num binary_pow(int times);

    //一些功能函数：

    /// <summary>
    /// 在大数前添加一个结点
    /// </summary>
    /// <param name="number">添加的节点值为number</param>
    void appendNode(int number);

    /// <summary>
    /// 删除大数的最前端的所有0
    /// </summary>
    void delete_0();

    /// <summary>
    /// 将大数乘10的x次方，二进制中为2的x次
    /// </summary>
    /// <param name="x">需要*10的次数</param>
    void Mul10(const int& x);

    /// <summary>
    /// 将大数除以10的x次方，二进制中为2的x次
    /// </summary>
    /// <param name="x">需要/10的次数</param>
    void Div10(const int& x);

    /// <summary>
    /// 将大数逆转存储
    /// </summary>
    void reverse();

    /// <summary>
    /// 获取大数的第一位数据
    /// </summary>
    /// <returns></returns>
    int lastdata();

    //一些大数之间的比较运算
    bool operator<(const Num& num) const;
    bool operator>(const Num& num) const;
    bool operator>=(const Num& num) const;
    bool operator==(const Num& num) const;
    bool operator<=(const Num& num) const;

    //基于预处理的乘法
    Num multiply(const Num& num);

    // FFT
    Num multiplyFFT(const Num& num);

    //次幂
    Num Power(int times);

    //友元函数，重载<<符号
    friend ostream& operator<<(ostream& os, const Num& num);
};
