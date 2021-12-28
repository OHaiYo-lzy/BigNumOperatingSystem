#include <iostream>
#include <fstream>
#include <Windows.h> //only for timing...
#include "Num.h"
using namespace std;

int main(int argc, char const* argv[])
{
    int m = 0;

    while (1)
    {
        system("cls");
        cout << "欢迎" << (m++ > 0 ? "再次" : "") << "来到我的大数运算的计算器" << endl;
        cout << "1.十进制" << endl;
        cout << "2.二进制" << endl;
        cout << "请输入1或2" << endl;
        int key1;
        cin >> key1;
        if (key1 == 1)
        {
            cout << "1.键盘输入" << endl;
            cout << "2.文件输入" << endl;
            cout << "3.随机生成" << endl;
            cout << "请输入1,2或3" << endl;
            int key2;
            cin >> key2;
            if (key2 == 1)
            {

                string s1, s2;
                cout << "请输入第一个十进制大整数：";
                cin >> s1;

                //定义一个字符变量 ,读取用户从键盘输入的运算符
                char op1;
                cout << "请输入要进行的运算：";
                cin >> op1;

                if (op1 != '^')
                {
                    cout << "请输入第二个十进制大整数：";
                    cin >> s2;
                    cout << s1 << " " << op1 << " " << s2 << " = ";
                }

                if (s1.length() < s2.length())
                    swap(s1, s2);
                Num n1 = Num(s1);
                Num n2 = Num(s2);

                switch (op1)
                {
                case '+':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1 + n2;
                    DWORD endTime1 = GetTickCount64();
                    cout << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '-':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1 - n2;
                    DWORD endTime1 = GetTickCount64();
                    cout << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '*':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.multiplyFFT(n2);
                    // Num result = n1.multiply(n2);
                    // Num result = n1 * n2;
                    DWORD endTime1 = GetTickCount64();
                    cout << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '/':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1 / n2;
                    DWORD endTime1 = GetTickCount64();
                    cout << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '^':
                {
                    cout << "请输入需要计算的次幂" << endl;
                    int times;
                    cin >> times;
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.Power(times);
                    DWORD endTime1 = GetTickCount64();
                    cout << s1 << "的" << times << "次结果为" << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                default:
                    break;
                }

                cout << "1.继续运算" << endl;
                cout << "2.退出程序" << endl;
                cout << "请输入1或2" << endl;
                int key3;
                cin >> key3;
                if (key3 == 2)
                    exit(1);
            }
            if (key2 == 2)
            {

                //定义文件输入输出流
                ifstream infile("data.txt", ios::in);
                ofstream outfile2("out_result.txt", ios::app);

                //错误控制
                if (!infile)
                {
                    cerr << "open error!" << endl;
                    exit(1);
                }

                //读取文件数据
                string s3, s4;
                getline(infile, s3);
                getline(infile, s4);
                cout << "文件输入的第一个十进制大整数是：" << s3 << endl;
                cout << "文件输入的第二个十进制大整数是：" << s4 << endl;

                if (s3.length() < s4.length())
                    swap(s3, s4);
                Num n1(s3);
                Num n2(s4);
                char op2;
                cout << "请输入要进行的运算：";
                cin >> op2;

                outfile2 << s3 << " " << op2 << " " << s4 << " = ";
                switch (op2)
                {
                case '+':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1 + n2;
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '-':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1 - n2;
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '*':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.multiplyFFT(n2);
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '/':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1 / n2;
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '^':
                {
                    outfile2 << "请输入需要计算的次幂" << endl;
                    int times;
                    cin >> times;
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.Power(times);
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                default:
                    break;
                }

                cout << "运算结果已输入到文件当中！" << endl
                    << endl;
                cout << "1.继续运算" << endl;
                cout << "2.退出程序" << endl;
                cout << "请输入1或2" << endl;

                int key3;
                cin >> key3;
                if (key3 == 2)
                    exit(1);
            }
            if (key2 == 3)
            {
                string s1, s2;

                int ti;
                cout << "请输入要进行的运算的大整数位数：";
                cin >> ti;

                srand(time(NULL));
                for (int i = 0; i < ti; i++)
                {
                    s1 += to_string(rand() % 10);
                    s2 += to_string(rand() % 10);
                }
                // s1 += to_string(rand() % 10);
                // cout <<"随机生成的大整数为："<< s1 << endl<<"和" << s2 << endl;
                Num n1 = Num(s1);
                Num n2 = Num(s2);

                DWORD startTime1 = GetTickCount64();
                Num result = n1.multiplyFFT(n2);
                DWORD endTime1 = GetTickCount64();

                // Num result = n1.multiply(n2);
                DWORD startTime2 = GetTickCount64();
                Num result1 = n1 * n2;
                DWORD endTime2 = GetTickCount64();

                cout << result << endl;
                cout << "程序运行时间1是：" << endTime1 - startTime1 << "ms" << endl<< endl;
                cout << "程序运行时间2是：" << endTime2 - startTime2 << "ms" << endl<< endl;

                cout << "1.继续运算" << endl;
                cout << "2.退出程序" << endl;
                cout << "请输入1或2" << endl;
                int key3;
                cin >> key3;
                if (key3 == 2)
                    exit(1);
            }
        }
        if (key1 == 2)
        {
            cout << "1.键盘输入" << endl;
            cout << "2.文件输入" << endl;
            cout << "请输入1或2" << endl;

            int key3;
            cin >> key3;

            if (key3 == 1)
            {

                string s1, s2;
                cout << "请输入第一个二进制大整数：";
                cin >> s1;

                //定义一个字符变量 ,读取用户从键盘输入的运算符
                char op3;
                cout << "请输入要进行的运算：";
                cin >> op3;

                if (op3 != '^')
                {
                    cout << "请输入第二个二进制大整数：";
                    cin >> s2;
                    cout << s1 << " " << op3 << " " << s2 << " = ";
                }

                if (s1.length() < s2.length())
                    swap(s1, s2);
                Num n1 = Num(s1);
                Num n2 = Num(s2);

                switch (op3)
                {
                case '+':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_plus(n2);
                    DWORD endTime1 = GetTickCount64();
                    cout << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '-':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_minus(n2);
                    DWORD endTime1 = GetTickCount64();
                    cout << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '*':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_multiply(n2);
                    DWORD endTime1 = GetTickCount64();
                    cout << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '/':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_divide(n2);
                    DWORD endTime1 = GetTickCount64();
                    cout << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '^':
                {
                    cout << "请输入需要计算的次幂" << endl;
                    int times;
                    cin >> times;
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_pow(times);
                    DWORD endTime1 = GetTickCount64();
                    cout << s1 << "的" << times << "次结果为" << result << endl;
                    cout << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                default:
                    break;
                }

                cout << "1.继续运算" << endl;
                cout << "2.退出程序" << endl;
                cout << "请输入1或2" << endl;

                int key3;
                cin >> key3;
                if (key3 == 2)
                {
                    exit(1);
                }
            }

            if (key3 == 2)
            {

                //定义文件输入输出流
                ifstream infile2("data_binary.txt", ios::in);
                ofstream outfile2("out_result_bianry.txt", ios::app);

                //错误控制
                if (!infile2)
                {
                    cerr << "open error!" << endl;
                    exit(1);
                }

                //读取文件数据
                string s3, s4;
                getline(infile2, s3);
                getline(infile2, s4);
                cout << "文件输入的第一个十进制大整数是：" << s3 << endl;
                cout << "文件输入的第二个十进制大整数是：" << s4 << endl;
                if (s3.length() < s4.length())
                    swap(s3, s4);
                Num n1(s3);
                Num n2(s4);
                char op2;
                cout << "请输入要进行的运算：";
                cin >> op2;

                outfile2 << s3 << " " << op2 << " " << s4 << " = ";
                switch (op2)
                {
                case '+':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_plus(n2);
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '-':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_minus(n2);
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '*':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_multiply(n2);
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '/':
                {
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_divide(n2);
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                case '^':
                {
                    outfile2 << "请输入需要计算的次幂" << endl;
                    int times;
                    cin >> times;
                    DWORD startTime1 = GetTickCount64();
                    Num result = n1.binary_pow(times);
                    DWORD endTime1 = GetTickCount64();
                    outfile2 << result << endl;
                    outfile2 << "程序运行时间是：" << endTime1 - startTime1 << "ms" << endl
                        << endl;
                    break;
                }
                default:
                    break;
                } 

                cout << "运算结果已输入到文件当中！" << endl<< endl;
                cout << "1.继续运算" << endl;
                cout << "2.退出程序" << endl;
                cout << "请输入1或2" << endl;

                int key3;
                cin >> key3;
                if (key3 == 2)
                {
                    exit(1);
                }
            }
        }
    }
    system("pause");
    return 0;
}