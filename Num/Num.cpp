#include "Num.h"
#include "Utils.h"
#include <fstream>
#include <cstring>
#include <cmath> //for log and cos
using namespace std;

/// <summary>
/// �޲����Ĺ��캯��
/// </summary>
Num::Num(/* args */)
{
    head = NULL;
    size = 0;
}

/// <summary>
/// ͨ��string����ʼ������Num
/// ������Ϊ�������һ������������мӼ�����
/// </summary>
/// <param name="s"></param>
Num::Num(const string& s)
{
    head = nullptr;
    size = 0;
    for (int i = 0; i < s.size(); i++)
    {
        //���2��123��34-234�ȸ�ʽ����
        if (s[i] == ',' || s[i] == '-')
            continue;
        size++;
        head = new Node(s[i] - '0', head);
    }
}

/// <summary>
/// ��������
/// </summary>
/// <param name="num">����������</param>
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
/// ��ֵ������=
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
/// ��������
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
/// ��ȡ����λ��
/// </summary>
/// <returns>������λ��</returns>
int Num::getSize() const
{
    return size;
}

/// <summary>
/// ��������10��x�η�����������Ϊ2��x��
/// </summary>
/// <param name="x">��Ҫ*10�Ĵ���</param>
void Num::Mul10(const int& x)
{
    if (x == 0)
        return;

    for (int i = 0; i < x; ++i)
    {
        //��ǰ����x��0
        head = new Node(0, head);
        size++;
    }
}

/// <summary>
/// ����������10��x�η�����������Ϊ2��x��
/// </summary>
/// <param name="x">��Ҫ/10�Ĵ���</param>
void Num::Div10(const int& x)
{
    //��ǰ��ɾx��λ
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
/// ������������洢
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
/// �õ��������һ���ڵ����ֵ
/// </summary>
/// <returns>���һ���ڵ����ֵ</returns>
int Num::lastdata()
{
    Node* he = head;
    //�������������һ���ڵ�
    while (he->next != NULL)
        he = he->next;
    return he->val;
}

/// <summary>
/// ɾ������ǰ�����Ч��0
/// </summary>
void Num::delete_0()
{
    this->reverse();
    Node* he = head;
    //�������ĵ�һλΪ0��������ĳ��Ȳ�Ϊ1��ɾ�������ͷ���
    while (he && he->val == 0 && size != 0)
    {
        he = he->next;
        size--;
    }
    this->reverse();
    return;
}

/// <summary>
/// ʮ���Ƽӷ�
/// �Ա��������в����������λ��ʼ�������
/// </summary>
/// <param name="num">����</param>
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
        //��λ����
        if (pa->val > 9)
        {
            //����һ���ڵ㲻Ϊ�գ����ϸ�λ��Ϊ�գ���ֱ�ӽ�λ
            if (pa->next != NULL)
            {
                pa->next->val++;
            }
            //�����Ҫ�����µ�λ��
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
/// ʮ���Ƽӷ�
/// </summary>
/// <param name="num">����</param>
/// <returns></returns>
Num Num::operator+(const Num& num)
{
    Num ans(*this);
    return ans += num;
}

/// <summary>
/// �ж��Ƿ����
/// </summary>
/// <param name="num">�Ƚ���</param>
/// <returns>true/false</returns>
bool Num::operator==(const Num& num) const
{
    //������Ȳ���ȣ�ֱ�����
    if (size != num.size)
    {
        return false;
    }
    //�����Ƚϴ�С
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
/// ʮ���Ƽ���
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
Num Num::operator-(const Num& num) //ʮ���Ƽ���
{
    //���������ȣ�ֱ�ӷ���0
    if (num == *this)
    {
        this->~Num();
        return Num(string(1, '0'));
    }
    else
    {
        //�µ�����������õ���������Ҫ�Ƚ����нڵ��ֵ��Ϊ0
        Num ans(string(size, '0'));
        Node* b1 = num.head;
        Node* a1 = this->head;
        Node* pans = ans.head;

        for (; a1 != NULL && b1 != NULL; a1 = a1->next)
        {
            //���ͬһλ�ϣ�a����ֵ���ڵ���b����ֵ
            if (a1->val >= b1->val)
            {
                pans->val = pans->val + a1->val - b1->val;
            }
            else
            {
                //��λ��10�����
                pans->val = pans->val + a1->val + 10 - b1->val;
                //��һλ��1
                ((pans->next)->val)--;
            }

            b1 = b1->next;
            pans = pans->next;
        }
        //����ʣ�࣬��ʣ�µĽڵ����ӵ�ans��
        for (; a1 != NULL && pans != NULL; a1 = a1->next)
        {
            pans->val = pans->val + a1->val;
            pans = pans->next;
        }
        //ɾ�������0
         //ans.delete_0();
        return ans;
    }
}

/// <summary>
/// ����-=����
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
Num& Num::operator-=(const Num& num)
{
    *this = *this - num;
    return *this;
}

/// <summary>
/// ��ͨ�˷��������α���
/// </summary>
/// <param name="num">����</param>
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
/// ����Ԥ����ĳ˷�������һƪ���ĵĸ���
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
/// ���� < ����
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
bool Num::operator<(const Num& num) const
{
    //�Ƚϳ���
    if (size < num.size)
        return true;
    else if (size > num.size)
        return false;

    //���ڸ�λ�����Ż�
    if (num.size == 1)
    {
        return this->head->val < num.head->val;
    }

    //ת�ñȽ�
    Num a(*this), b(num);
    a.reverse();
    b.reverse();
    Node* head1 = a.head;
    Node* head2 = b.head;
    //��λ�Ƚ�
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
    //ֱ�����һλ����ͬ����ô������������ͬ������0
    return 0;
}

//һЩ�ȽϷ��ŵ�����
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
/// ���� << ����
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
        //ÿ��λ��� ������
        if (t && (q - i) % 3 == 0 && i != 0)
            os << ",";
        os << s[i];
    }
    os << endl;
    return os;
}

/// <summary>
/// ������������ʹ�ñ�������ȥ��������������10����
/// ����58����5 ������58 - 50 = 8 Ȼ���̼�10 Ȼ����8 - 5 = 3 �̼�1 ����3��5С��
/// �Ͳ����в����� ���ս��Ϊ11
/// </summary>
/// <param name="num">����</param>
/// <returns>��</returns>
Num Num::operator/(const Num& num)
{
    // cout << size << " " << num.size << endl;
    if (size < num.size)
    {
        return Num(string(1, '0'));
    }

    Num a(*this), b(num);
    int La = size, Lb = num.size;

    //�������ͳ�����λ��֮��
    int t = La - Lb;
    int tt = t;
    //����������10^t��
    // b.Mul10(t);
    int ans = 0;
    for (int j = 0; j <= tt; j++)
    {
        Num temp = b;
        if (t != 0)
        {
            temp.Mul10(t--);
        }
        //����������ȳ����������
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
/// ���ٸ���Ҷ�任�˷�
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

    // lentȡ���������ֵ
    lent = (len1 > len2 ? len1 : len2);

    // lenȡֵΪ���ڶ��ߵ���С��2����������
    len = 1;
    while (len < lent)
        len <<= 1;
    len <<= 1;

    Node* pa = head;
    Node* pb = num.head;

    //������������������ֵ�洢��rea��reb���鵱�У����鲿��ֵ0.0
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

    //���a��b�ĵ�ֵ��ʾ��
    FFT(rea, ina, len, 0);
    FFT(reb, inb, len, 0);

    //���c�ĵ�ֵ��ʾ��,���
    for (int i = 0; i < len; i++)
    {
        double rec = rea[i] * reb[i] - ina[i] * inb[i];
        double inc = rea[i] * inb[i] + ina[i] * reb[i];
        rea[i] = rec;
        ina[i] = inc;
    }
    // ���㸵��Ҷ��任
    FFT(rea, ina, len, 1);

    // rea��reb����len�Ľ׳�
    for (int i = 0; i < len; i++)
    {
        rea[i] /= len;
        ina[i] /= len;
    }

    //ȡ����
    for (int i = 0; i < len; i++)
    {
        res[i] = (int)(rea[i] + 0.5);
    }
    //��λ
    for (int i = 0; i < len; i++)
    {
        res[i + 1] += res[i] / 10, res[i] %= 10;
    }

    //����ǰ�õĶ���0
    lenres = len1 + len2 + 2;
    while (res[lenres] == 0 && lenres > 0)
        lenres--;

    //ѭ�����������ans�������
    string ans = "";
    for (int i = lenres; i >= 0; i--)
        ans += to_string(res[i]);

    return Num(ans);
}

/// <summary>
/// ʮ���ƣ�������*=������
/// ʵ�ʵ���FFT֮���ٸ�ֵ
/// ���ⷢ�������ʱ�򻹱�multipltFFT��
/// </summary>
/// <param name="num">����</param>
/// <returns>�˷����</returns>
Num& Num::operator*=(const Num& num)
{
    Num ans = this->multiplyFFT(num);
    *this = ans;
    return *this;
}

/// <summary>
/// ʮ���ƵĴ�������
/// ʵ���ϵ�����times�ε�FFT�˷�
/// </summary>
/// <param name="times">������</param>
/// <returns>���ݽ��</returns>
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
/// ������β��׷��ָ������
/// </summary>
/// <param name="number">��Ҫ��ӵ�����</param>
void Num::appendNode(int number)
{
    Node* he = head;
    Node* p1 = new Node(number);

    //������Ϊ�գ���ӵĸýڵ�Ϊͷ���
    if (head == NULL)
    {
        he = p1;
        he->next = NULL;
        head = he;
        return;
    }

    //������ӵĽڵ�Ϊβ�ڵ�
    else
    {
        //��������ֱ��ָ��ָ����������һ���ڵ�
        while (he->next != NULL)
            he = he->next;

        he->next = p1;

        // p1��Ϊ�������β�ڵ�
        p1->next = NULL;
    }
    return;
}

/// <summary>
/// �����Ƶļӷ�
/// ��Ȼ�Ǽ�-��λ��ԭʼ������ԭ��ͬ�ӷ�������׸����
/// </summary>
/// <param name="num">����</param>
/// <returns>�ӷ����</returns>
Num Num::binary_plus(const Num& num)
{
    Num ans(string(size + 1, '0'));
    Node* a1 = this->head;
    Node* b1 = num.head;
    Node* thu = ans.head;

    //������Ӧλ�����
    for (; b1 != NULL; a1 = a1->next, b1 = b1->next)
    {
        int sum = thu->val + a1->val + b1->val;
        //��λ����
        if (sum >= 2)
        {
            thu->val = sum % 2;
            //������β��׷��ָ������
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
    //ʣ��λ���Ĵ���
    for (; a1 != NULL; a1 = a1->next)
    {
        thu->val = thu->val + a1->val;
        //��λ
        if (thu->val == 2)
        {
            thu->val -= 2;
            if (thu->next == NULL)
            {
                //��ͷ�����Ӧֵ�Ľ��
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
/// �����Ƶļ�����ԭ��ͬ�ӷ�������׸��
/// </summary>
/// <param name="num">����</param>
/// <returns>�������</returns>
Num Num::binary_minus(const Num& num)
{
    //��ͬ�򷵻�0
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

        //������Ӧλ�����
        for (; b1 != NULL;)
        {
            if (thu->val + a1->val >= b1->val)
            {
                thu->val = thu->val + a1->val - b1->val;
            }
            else
            {
                //��Ҫ��λ
                thu->val = thu->val + a1->val + 2 - b1->val;
                thu->next->val--;
            }
            b1 = b1->next;
            // if (b1 != NULL){
            a1 = a1->next;
            thu = thu->next;
            //}
        }
        //����λ���Ĵ����������в�λ��
        for (; a1 != NULL; a1 = a1->next)
        {
            if (thu->val + a1->val < 0)
            {
                //��Ҫ��λ
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
/// �����Ƴ˷�
/// </summary>
/// <param name="num">����</param>
/// <returns>�˷����</returns>
Num Num::binary_multiply(const Num& num)
{
    //�����һ������Ϊ0���򷵻�0
    if (size == 0 || num.size == 0)
    {
        return Num(string(1, '0'));
    }
    else
    {
        Node* b1 = num.head;
        Num pa = Num(string(size * num.size, '0'));
        //�����λ
        int carry = 0;
        Num temp(*this);
        //��������
        for (int i = 0; b1 != NULL; b1 = b1->next)
        {
            //����1����Զ�Ӧ�Ĵ���
            if (b1->val == 1)
            {
                temp.Mul10(carry);
                carry = 0;
                //�ӵ��������
                pa = pa.binary_plus(temp);
            }
            carry++;
        }
        pa.delete_0();
        return pa;
    }
}

/// <summary>
/// �����Ƶĳ���
/// </summary>
/// <param name="num">����</param>
/// <returns>��</returns>
Num Num::binary_divide(const Num& num)
{
    Num ans[2];
    //����������ȣ��򷵻�1
    if (*this == num)
    {
        return Num(string(1, '1'));
    }
    //����������С�ڳ������򷵻�0
    if (size == 0 || size < num.size || *this < num)
    {
        return Num(string(1, '0'));
    }
    //����Ϊ0���˳�
    if (num.size == 0)
    {
        cout << "����Ϊ0��" << endl;
        cout << "������ֹ...";
        exit(1);
    }

    Num a(*this), b(num);
    //ȷ��nΪ����֮��
    int n = size - num.size;

    string re = "";

    //ԭ����ʵͬʮ���ƣ�ֻ�Ǵ����������
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
/// �����ƵĴ��ݺ���
/// ͨ������times�ζ����Ƴ˷�ʵ��
/// </summary>
/// <param name="times">������</param>
/// <returns>���ݽ��</returns>
Num Num::binary_pow(int times)
{
    Num ans(*this);
    for (int i = 1; i < times; i++)
    {
        ans = ans.binary_multiply(*this);
    }
    return ans;
}