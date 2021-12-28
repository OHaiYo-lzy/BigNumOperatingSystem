#include "Num.h"
#include "Utils.h"
#include <fstream>
#include <cstring>
#include <cmath> //for log and cos
using namespace std;

/// <summary>
/// 无参数的构造函数
/// </summary>
Num::Num(/* args */)
{
    head = NULL;
    size = 0;
}

/// <summary>
/// 通过string来初始化大数Num
/// 该链表为逆向构造的一个数，方便进行加减操作
/// </summary>
/// <param name="s"></param>
Num::Num(const string& s)
{
    head = nullptr;
    size = 0;
    for (int i = 0; i < s.size(); i++)
    {
        //解决2，123和34-234等格式问题
        if (s[i] == ',' || s[i] == '-')
            continue;
        size++;
        head = new Node(s[i] - '0', head);
    }
}

/// <summary>
/// 拷贝构造
/// </summary>
/// <param name="num">被拷贝大数</param>
Num::Num(const Num& num)
{
    size = num.size;
    head = NULL;
    Node* cur = num.head, * temp = head;
    while (cur)
    {
        if (!head)
        {
            head = new Node(cur->val, NULL);
            temp = head;
        }
        else
        {
            temp->next = new Node(cur->val, NULL);
            temp = temp->next;
        }
        cur = cur->next;
    }
}

/// <summary>
/// 赋值，重载=
/// </summary>
Num& Num::operator=(const Num& num)
{
    if (this == &num)
        return *this;
    this->~Num();
    size = num.size;
    head = NULL;
    Node* cur = num.head, * temp = head;
    while (cur)
    {
        if (!head)
        {
            head = new Node(cur->val, NULL);
            temp = head;
        }
        else
        {
            temp->next = new Node(cur->val, NULL);
            temp = temp->next;
        }
        cur = cur->next;
    }
    return *this;
}

/// <summary>
/// 析构函数
/// </summary>
Num::~Num()
{
    size = 0;
    while (head)
    {
        Node* temp = head->next;
        delete head;
        head = temp;
    }
    head = NULL;
}

/// <summary>
/// 获取大数位数
/// </summary>
/// <returns>大数的位数</returns>
int Num::getSize() const
{
    return size;
}

/// <summary>
/// 将大数乘10的x次方，二进制中为2的x次
/// </summary>
/// <param name="x">需要*10的次数</param>
void Num::Mul10(const int& x)
{
    if (x == 0)
        return;

    for (int i = 0; i < x; ++i)
    {
        //往前面添x个0
        head = new Node(0, head);
        size++;
    }
}

/// <summary>
/// 将大数除以10的x次方，二进制中为2的x次
/// </summary>
/// <param name="x">需要/10的次数</param>
void Num::Div10(const int& x)
{
    //往前面删x个位
    if (x != 0)
    {
        for (int i = 0; i < x; ++i)
        {
            Node* temp = head->next;
            delete head;
            head = temp;
            size--;
        }
    }
    else
    {
        return;
    }
}

/// <summary>
/// 大整数的逆向存储
/// </summary>
void Num::reverse()
{
    Node* he = head;
    Node* pre, * cur, * nex;
    pre = he;
    cur = he->next;
    while (cur)
    {
        nex = cur->next;
        cur->next = pre;
        pre = cur;
        cur = nex;
    }
    he->next = NULL;
    he = pre;
    head = he;
    // head = pre;
}

/// <summary>
/// 得到链表最后一个节点的数值
/// </summary>
/// <returns>最后一个节点的数值</returns>
int Num::lastdata()
{
    Node* he = head;
    //遍历到链表最后一个节点
    while (he->next != NULL)
        he = he->next;
    return he->val;
}

/// <summary>
/// 删除整数前面的无效的0
/// </summary>
void Num::delete_0()
{
    this->reverse();
    Node* he = head;
    //如果链表的第一位为0，且链表的长度不为1，删除链表的头结点
    while (he && he->val == 0 && size != 0)
    {
        he = he->next;
        size--;
    }
    this->reverse();
    return;
}

/// <summary>
/// 十进制加法
/// 对本身对象进行操作，从最低位开始依次相加
/// </summary>
/// <param name="num">加数</param>
Num& Num::operator+=(const Num& num)
{
    Node* pa = head, * pb = num.head;
    while (pa || pb)
    {
        int b = 0;
        if (pb)
        {
            b = pb->val;
            pb = pb->next;
        }
        pa->val += b;
        //进位操作
        if (pa->val > 9)
        {
            //若下一个节点不为空（即较高位不为空）则直接进位
            if (pa->next != NULL)
            {
                pa->next->val++;
            }
            //如果需要产生新的位数
            else
            {
                pa->next = new Node(1, NULL);
                size++;
            }
            pa->val -= 10;
        }
        pa = pa->next;
    }
    return *this;
}

/// <summary>
/// 十进制加法
/// </summary>
/// <param name="num">加数</param>
/// <returns></returns>
Num Num::operator+(const Num& num)
{
    Num ans(*this);
    return ans += num;
}

/// <summary>
/// 判断是否相等
/// </summary>
/// <param name="num">比较数</param>
/// <returns>true/false</returns>
bool Num::operator==(const Num& num) const
{
    //如果长度不相等，直接输出
    if (size != num.size)
    {
        return false;
    }
    //遍历比较大小
    Node* pa = head;
    Node* pb = num.head;
    while (pa && pb)
    {
        if (pa->val != pb->val)
        {
            return false;
        }
        pa = pa->next;
        pb = pb->next;
    }
    return true;
}

/// <summary>
/// 十进制减法
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
Num Num::operator-(const Num& num) //十进制减法
{
    //如果两数相等，直接返回0
    if (num == *this)
    {
        this->~Num();
        return Num(string(1, '0'));
    }
    else
    {
        //新的链表存放相减得到的数，需要先将所有节点的值置为0
        Num ans(string(size, '0'));
        Node* b1 = num.head;
        Node* a1 = this->head;
        Node* pans = ans.head;

        for (; a1 != NULL && b1 != NULL; a1 = a1->next)
        {
            //如果同一位上，a的数值大于等于b的数值
            if (a1->val >= b1->val)
            {
                pans->val = pans->val + a1->val - b1->val;
            }
            else
            {
                //该位加10，相减
                pans->val = pans->val + a1->val + 10 - b1->val;
                //下一位减1
                ((pans->next)->val)--;
            }

            b1 = b1->next;
            pans = pans->next;
        }
        //若有剩余，则将剩下的节点连接到ans中
        for (; a1 != NULL && pans != NULL; a1 = a1->next)
        {
            pans->val = pans->val + a1->val;
            pans = pans->next;
        }
        //删除多余的0
         //ans.delete_0();
        return ans;
    }
}

/// <summary>
/// 重载-=符号
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
Num& Num::operator-=(const Num& num)
{
    *this = *this - num;
    return *this;
}

/// <summary>
/// 普通乘法，用两次遍历
/// </summary>
/// <param name="num">乘数</param>
/// <returns></returns>
Num Num::operator*(const Num& num)
{
    Num res(string(size + num.size, '0'));
    Node* pr = res.head, * temp;
    for (Node* pa = head; pa != NULL; pa = pa->next)
    {
        int carry = 0;
        temp = pr;
        for (Node* pb = num.head; pb != NULL; pb = pb->next, pr = pr->next)
        {
            int temp = pa->val * pb->val + carry + pr->val;
            pr->val = temp % 10;
            carry = temp / 10;
        }
        pr->val += carry;
        pr = temp->next;
    }

    return res;
}

/// <summary>
/// 基于预处理的乘法，基于一篇论文的复现
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
Num Num::multiply(const Num& num)
{
    /* Num aux[10] = { Num(), Num(string(1, '1')) * num, Num(string(1, '2')) * num,
                   Num(string(1, '3')) * num, Num(string(1, '4')) * num, Num(string(1, '5')) * num,
                   Num(string(1, '6')) * num, Num(string(1, '7')) * num, Num(string(1, '8')) * num,
                  Num(string(1, '9')) * num };
    */

    Num aux[10];
    aux[0] = Num(string(1, '0'));
    aux[1] = Num(string(1, '1')) * num;
    aux[2] = Num(string(1, '2')) * num;
    aux[3] = Num(string(1, '3')) * num;
    aux[4] = Num(string(1, '4')) * num;
    aux[5] = Num(string(1, '5')) * num;
    aux[6] = Num(string(1, '6')) * num;
    aux[7] = Num(string(1, '7')) * num;
    aux[8] = Num(string(1, '8')) * num;
    aux[9] = Num(string(1, '9')) * num;

    /*aux[1] = num;
    aux[2] = aux[1] + num;
    aux[3] = aux[2] + num;
    aux[4] = aux[3] + num;
    aux[5] = aux[4] + num;
    aux[6] = aux[5] + num;
    aux[7] = aux[6] + num;
    aux[8] = aux[7] + num;
    aux[9] = aux[8] + num;*/

    Num res(string(size + num.size, '0'));
    int i = 0;
    Num temp;
    for (Node* pa = head; pa != NULL; pa = pa->next, i++)
    {
        temp = aux[pa->val];
        if (i)
        {
            temp.Mul10(i);
        }
        res += temp;
    }
    return res;
}

/// <summary>
/// 重载 < 符号
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
bool Num::operator<(const Num& num) const
{
    //比较长度
    if (size < num.size)
        return true;
    else if (size > num.size)
        return false;

    //对于个位数的优化
    if (num.size == 1)
    {
        return this->head->val < num.head->val;
    }

    //转置比较
    Num a(*this), b(num);
    a.reverse();
    b.reverse();
    Node* head1 = a.head;
    Node* head2 = b.head;
    //逐位比较
    while (head1 != NULL)
    {
        if (head1->val < head2->val)
        {
            return 1;
        }

        if (head1->val > head2->val)
        {
            return 0;
        }

        head1 = head1->next;
        head2 = head2->next;
    }
    //直到最后一位都相同，那么两个大整数相同，返回0
    return 0;
}

//一些比较符号的重载
bool Num::operator>=(const Num& num) const
{
    return !(*this < num);
}

bool Num::operator<=(const Num& num) const
{
    return *this < num || *this == num;
}

bool Num::operator>(const Num& num) const
{
    return !(*this <= num);
}

/// <summary>
/// 重载 << 符号
/// </summary>
/// <param name="os"></param>
/// <param name="num"></param>
/// <returns></returns>
ostream& operator<<(ostream& os, const Num& num)
{
    bool z = false;
    Num::Node* temp = num.head;
    string s(num.size, '0');
    for (int i = num.size - 1; i >= 0; --i)
    {
        s[i] = temp->val + '0';
        temp = temp->next;
    }

    int n = 0;
    while (s[n] == '0')
        n++;
    if (n == s.size())
        s = "0";
    else
        s = s.substr(n);

    bool t = true;
    int q = (int)s.size();
    int j = (int)s.size() - 1;
    if (z)
    {
        while (j > q && s[j] == '0')
            j--;
        if (j == q)
            j--;
    }
    for (int i = 0; i <= j; ++i)
    {
        //每三位输出 ，符号
        if (t && (q - i) % 3 == 0 && i != 0)
            os << ",";
        os << s[i];
    }
    os << endl;
    return os;
}

/// <summary>
/// 除法操作我们使用被除数减去除数乘以若个干10进行
/// 比如58除以5 首先用58 - 50 = 8 然后商加10 然后用8 - 5 = 3 商加1 由于3比5小，
/// 就不进行操作了 最终结果为11
/// </summary>
/// <param name="num">除数</param>
/// <returns>商</returns>
Num Num::operator/(const Num& num)
{
    // cout << size << " " << num.size << endl;
    if (size < num.size)
    {
        return Num(string(1, '0'));
    }

    Num a(*this), b(num);
    int La = size, Lb = num.size;

    //除被数和除数的位数之差
    int t = La - Lb;
    int tt = t;
    //将除数扩大10^t倍
    // b.Mul10(t);
    int ans = 0;
    for (int j = 0; j <= tt; j++)
    {
        Num temp = b;
        if (t != 0)
        {
            temp.Mul10(t--);
        }
        //如果被除数比除数大继续减
        int time = 0;
        while (temp <= a)
        {
            // cout << "a:" << a << "temp:" << temp;
            a = a - temp;
            // cout << "a:" << a << "temp:" << temp;
            time++;
            a.delete_0();
        }

        // cout <<"time:"<< time << endl;
        ans = ans * 10 + time;
        // cout << "ans:"<<ans << endl;
    }
    return Num(to_string(ans));
}

/// <summary>
/// 快速傅里叶变换乘法
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
Num Num::multiplyFFT(const Num& num)
{
    memset(res, 0, sizeof(res));
    memset(rea, 0, sizeof(rea));
    memset(ina, 0, sizeof(ina));
    memset(reb, 0, sizeof(reb));
    memset(inb, 0, sizeof(inb));

    len1 = size;
    len2 = num.size;

    // lent取二者中最大值
    lent = (len1 > len2 ? len1 : len2);

    // len取值为大于二者的最小的2的整数次幂
    len = 1;
    while (len < lent)
        len <<= 1;
    len <<= 1;

    Node* pa = head;
    Node* pb = num.head;

    //遍历两个大整数将数值存储到rea和reb数组当中，将虚部赋值0.0
    for (int i = 0; i < len; i++)
    {

        if (i < len1)
        {
            rea[i] = (double)(pa->val);
            pa = pa->next;
        }

        if (i < len2)
        {
            reb[i] = (double)(pb->val);
            pb = pb->next;
        }
        ina[i] = inb[i] = 0.0;
    }

    //求出a、b的点值表示法
    FFT(rea, ina, len, 0);
    FFT(reb, inb, len, 0);

    //求出c的点值表示法,卷积
    for (int i = 0; i < len; i++)
    {
        double rec = rea[i] * reb[i] - ina[i] * inb[i];
        double inc = rea[i] * inb[i] + ina[i] * reb[i];
        rea[i] = rec;
        ina[i] = inc;
    }
    // 计算傅里叶逆变换
    FFT(rea, ina, len, 1);

    // rea和reb除以len的阶乘
    for (int i = 0; i < len; i++)
    {
        rea[i] /= len;
        ina[i] /= len;
    }

    //取整数
    for (int i = 0; i < len; i++)
    {
        res[i] = (int)(rea[i] + 0.5);
    }
    //进位
    for (int i = 0; i < len; i++)
    {
        res[i + 1] += res[i] / 10, res[i] %= 10;
    }

    //跳过前置的多余0
    lenres = len1 + len2 + 2;
    while (res[lenres] == 0 && lenres > 0)
        lenres--;

    //循环将数组读入ans结果当中
    string ans = "";
    for (int i = lenres; i >= 0; i--)
        ans += to_string(res[i]);

    return Num(ans);
}

/// <summary>
/// 十进制，重载了*=操作符
/// 实际调用FFT之后再赋值
/// 意外发现这个有时候还比multipltFFT快
/// </summary>
/// <param name="num">乘数</param>
/// <returns>乘法结果</returns>
Num& Num::operator*=(const Num& num)
{
    Num ans = this->multiplyFFT(num);
    *this = ans;
    return *this;
}

/// <summary>
/// 十进制的次幂运算
/// 实际上调用了times次的FFT乘法
/// </summary>
/// <param name="times">次幂数</param>
/// <returns>次幂结果</returns>
Num Num::Power(int times)
{
    Num ans(*this);
    for (int i = 1; i < times; i++)
    {
        ans = ans.multiplyFFT(*this);
    }
    return ans;
}

/// <summary>
/// 在链表尾部追加指定数据
/// </summary>
/// <param name="number">需要添加的数据</param>
void Num::appendNode(int number)
{
    Node* he = head;
    Node* p1 = new Node(number);

    //若链表为空，添加的该节点为头结点
    if (head == NULL)
    {
        he = p1;
        he->next = NULL;
        head = he;
        return;
    }

    //否则，添加的节点为尾节点
    else
    {
        //遍历链表，直到指针指向链表的最后一个节点
        while (he->next != NULL)
            he = he->next;

        he->next = p1;

        // p1即为该链表的尾节点
        p1->next = NULL;
    }
    return;
}

/// <summary>
/// 二进制的加法
/// 仍然是加-进位的原始做法，原理同加法，不再赘述了
/// </summary>
/// <param name="num">加数</param>
/// <returns>加法结果</returns>
Num Num::binary_plus(const Num& num)
{
    Num ans(string(size + 1, '0'));
    Node* a1 = this->head;
    Node* b1 = num.head;
    Node* thu = ans.head;

    //遍历对应位数相加
    for (; b1 != NULL; a1 = a1->next, b1 = b1->next)
    {
        int sum = thu->val + a1->val + b1->val;
        //进位操作
        if (sum >= 2)
        {
            thu->val = sum % 2;
            //在链表尾部追加指定数据
            if (thu->next == NULL)
                ans.appendNode(1);
            else
                thu->next->val++;
        }
        else
        {
            thu->val = sum;
        }
        thu = thu->next;
    }
    //剩余位数的处理
    for (; a1 != NULL; a1 = a1->next)
    {
        thu->val = thu->val + a1->val;
        //进位
        if (thu->val == 2)
        {
            thu->val -= 2;
            if (thu->next == NULL)
            {
                //在头添加相应值的结点
                ans.appendNode(1);
            }
            else
            {
                thu->next->val++;
            }
        }
        thu = thu->next;
    }
    return ans;
}

/// <summary>
/// 二进制的减法，原理同加法，不再赘述
/// </summary>
/// <param name="num">减数</param>
/// <returns>减法结果</returns>
Num Num::binary_minus(const Num& num)
{
    //相同则返回0
    if (num == *this)
    {
        return Num(string(1, '0'));
    }
    else
    {
        Num ans(string(size, '0'));
        Node* thu = ans.head;
        Node* a1 = this->head;
        Node* b1 = num.head;

        //遍历对应位数相减
        for (; b1 != NULL;)
        {
            if (thu->val + a1->val >= b1->val)
            {
                thu->val = thu->val + a1->val - b1->val;
            }
            else
            {
                //需要补位
                thu->val = thu->val + a1->val + 2 - b1->val;
                thu->next->val--;
            }
            b1 = b1->next;
            // if (b1 != NULL){
            a1 = a1->next;
            thu = thu->next;
            //}
        }
        //多余位数的处理，继续进行补位等
        for (; a1 != NULL; a1 = a1->next)
        {
            if (thu->val + a1->val < 0)
            {
                //需要补位
                thu->val = thu->val + a1->val + 2;
                if (thu->next)
                    thu->next->val--;
            }
            else
            {
                thu->val = thu->val + a1->val;
            }
            if (thu->next)
                thu = thu->next;
        }
        return ans;
    }
}

/// <summary>
/// 二进制乘法
/// </summary>
/// <param name="num">乘数</param>
/// <returns>乘法结果</returns>
Num Num::binary_multiply(const Num& num)
{
    //如果有一个乘数为0，则返回0
    if (size == 0 || num.size == 0)
    {
        return Num(string(1, '0'));
    }
    else
    {
        Node* b1 = num.head;
        Num pa = Num(string(size * num.size, '0'));
        //定义进位
        int carry = 0;
        Num temp(*this);
        //遍历乘数
        for (int i = 0; b1 != NULL; b1 = b1->next)
        {
            //遇到1则乘以对应的次幂
            if (b1->val == 1)
            {
                temp.Mul10(carry);
                carry = 0;
                //加到结果当中
                pa = pa.binary_plus(temp);
            }
            carry++;
        }
        pa.delete_0();
        return pa;
    }
}

/// <summary>
/// 二进制的除法
/// </summary>
/// <param name="num">除数</param>
/// <returns>商</returns>
Num Num::binary_divide(const Num& num)
{
    Num ans[2];
    //如若两数相等，则返回1
    if (*this == num)
    {
        return Num(string(1, '1'));
    }
    //如若被除数小于除数，则返回0
    if (size == 0 || size < num.size || *this < num)
    {
        return Num(string(1, '0'));
    }
    //除数为0则退出
    if (num.size == 0)
    {
        cout << "除数为0！" << endl;
        cout << "程序将终止...";
        exit(1);
    }

    Num a(*this), b(num);
    //确定n为两者之差
    int n = size - num.size;

    string re = "";

    //原理其实同十进制，只是处理更方便了
    for (; n >= 0; n--)
    {
        Num pbb = b;
        pbb.Mul10(n);
        if (pbb <= a)
        {
            // cout << "a:" << a << "pbb:" << pbb;
            a = a.binary_minus(pbb);
            // cout << "a:" << a << "pbb:" << pbb << endl;
            re += "1";
            a.delete_0();
        }
        else
        {
            re += "0";
        }
    }
    Num res(re);
    return res;
}

/// <summary>
/// 二进制的次幂函数
/// 通过调用times次二进制乘法实现
/// </summary>
/// <param name="times">次幂数</param>
/// <returns>次幂结果</returns>
Num Num::binary_pow(int times)
{
    Num ans(*this);
    for (int i = 1; i < times; i++)
    {
        ans = ans.binary_multiply(*this);
    }
    return ans;
}