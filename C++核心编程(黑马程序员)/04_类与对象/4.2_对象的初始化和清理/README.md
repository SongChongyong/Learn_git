### 4.2 对象的初始化和清理

*  生活中我们买的电子产品都基本会有出厂设置，在某一天我们不用时候也会删除一些自己信息数据保证安全
*  C++中的面向对象来源于生活，每个对象也都会有初始设置以及 对象销毁前的清理数据的设置。





#### 4.2.1 构造函数和析构函数

对象的**初始化和清理**也是两个非常重要的安全问题

​	一个对象或者变量没有初始状态，对其使用后果是未知

​	同样的使用完一个对象或变量，没有及时清理，也会造成一定的安全问题



c++利用了**构造函数**和**析构函数**解决上述问题，这两个函数将会被编译器自动调用，完成对象初始化和清理工作。

对象的初始化和清理工作是编译器强制要我们做的事情，因此如果**我们不提供构造和析构，编译器会提供**

**编译器提供的构造函数和析构函数是空实现。**



* 构造函数：主要作用在于创建对象时为对象的成员属性赋值，构造函数由编译器自动调用，无须手动调用。
* 析构函数：主要作用在于对象**销毁前**系统自动调用，执行一些清理工作。





**构造函数语法：**`类名(){}`

1. 构造函数，没有返回值也不写void
2. 函数名称与类名相同
3. 构造函数可以有参数，因此可以发生重载
4. 程序在调用对象时候会自动调用构造，无须手动调用,而且只会调用一次





**析构函数语法：** `~类名(){}`

1. 析构函数，没有返回值也不写void
2. 函数名称与类名相同,在名称前加上符号  ~
3. 析构函数不可以有参数，因此不可以发生重载
4. 程序在对象销毁前会自动调用析构，无须手动调用,而且只会调用一次



```C++
#include<iostream>
using namespace std;

class Person
{
public:
    /* 构造函数，进行初始化操作:
        1. 构造函数，没有返回值也不写void
        2. 函数名称与类名相同
        3. 构造函数可以有参数，因此可以发生重载
        4. 程序在调用对象时候会自动调用构造，无须手动调用,而且只会调用一次
    */
    Person()
    {
        cout << "Person的构造函数调用" << endl;
    }

    /*析构函数，进行清理操作:
        1. 析构函数，没有返回值也不写void
        2. 函数名称与类名相同,在名称前加上符号  ~
        3. 析构函数不可以有参数，因此不可以发生重载
        4. 程序在对象销毁前会自动调用析构，无须手动调用,而且只会调用一次
    */
    ~Person()
    {
        cout << "Person的析构函数调用" << endl;
    }

};

void test01()
{
    Person p;  
    /* 栈上的数据，test01函数中仅仅是创建了一个Person的对象
         1. 调用时会自动调用构造函数
         2. test01执行完毕后，释放这个对象,程序在对象销毁前会自动调用析构函数
    */
}

int main() {
    
    test01();

    return 0;
}

/*
Person的构造函数调用
Person的析构函数调用
*/
```

(代码见:  [01_构造函数和析构函数.cpp](./01_构造函数和析构函数.cpp))



#### 4.2.2 构造函数的分类及调用

两种分类方式：

​	按参数分为： 有参构造和无参构造

​	按类型分为： 普通构造和拷贝构造

三种调用方式：

​	括号法

​	显示法

​	隐式转换法



**示例：**

```C++
#include<iostream>
using namespace std;

//1、构造函数分类
// 按照参数分类分为 有参和无参构造   无参又称为默认构造函数
// 按照类型分类分为 普通构造和拷贝构造

class Person {
public:
    //无参（默认）构造函数
    Person() {
        cout << "无参构造函数!" << endl;
    }
    //有参构造函数
    Person(int a) {
        age = a;
        cout << "有参构造函数!" << endl;
    }
    //拷贝构造函数
    Person(const Person& p) {
        age = p.age;
        cout << "拷贝构造函数!" << endl;
    }
    //析构函数
    ~Person() {
        cout << "析构函数!" << endl;
    }
public:
    int age;
};

//2、构造函数的调用
//调用无参构造函数
void test01() {
    Person p; //调用无参构造函数
}

//调用有参的构造函数
void test02() {

    //2.1  括号法，常用
    Person p1(10);
    //注意1：调用无参构造函数不能加括号，如果加了编译器认为这是一个函数声明
    //Person p2();

    //2.2 显式法
    Person p2 = Person(10); 
    Person p3 = Person(p2);
    //Person(10)单独写就是匿名对象  当前行结束之后，马上析构

    //2.3 隐式转换法
    Person p4 = 10; // Person p4 = Person(10); 
    Person p5 = p4; // Person p5 = Person(p4); 

    //注意2：不能利用拷贝构造函数初始化匿名对象 编译器认为是对象声明
    //Person p5(p4);   // 编译器认为定义了一个p5类对象，其中的参数为p4
}

int main() {

    // test01();
    test02();

    return 0;
}

/*
有参构造函数!
有参构造函数!
拷贝构造函数!
有参构造函数!
拷贝构造函数!
析构函数!
析构函数!
析构函数!
析构函数!
析构函数!
*/
```

(代码见: [02_构造函数的分类及调用.cpp](./02_构造函数的分类及调用.cpp))





#### 4.2.3 拷贝构造函数调用时机

C++中拷贝构造函数调用时机通常有三种情况

* 使用一个已经创建完毕的对象来初始化一个新对象
* 值传递的方式给函数参数传值
* 以值方式返回局部对象



**示例：**

```C++
class Person {
public:
    Person() {
        cout << "无参构造函数!" << endl;
        mAge = 0;
    }
    Person(int age) {
        cout << "有参构造函数!" << endl;
        mAge = age;
    }
    Person(const Person &p) {
        cout << "拷贝构造函数!" << endl;
        mAge = p.mAge;
    }
    //析构函数在释放内存之前调用
    ~Person() {
        cout << "析构函数!" << endl;
    }
public:
    int mAge;
};

//1. 使用一个已经创建完毕的对象来初始化一个新对象
void test01() {

    Person man(20);         //p对象已经创建完毕
    Person newman(man);     //调用拷贝构造函数
    Person newman2 = man;   //拷贝构造

    //Person newman3;
    //newman3 = man;       //不是调用拷贝构造函数，赋值操作
}

//2. 值传递的方式给函数参数传值
//相当于Person p1 = p;
void doWork(Person p1) {}
void test02() {
    Person p;                //无参构造函数
    doWork(p);
}

//3. 以值方式返回局部对象
Person doWork2()
{
    Person p1;
    cout << (int *)&p1 << endl;
    return p1;
}

void test03()
{
    Person p = doWork2();
    cout << (int *)&p << endl;
}


int main() {

    //test01();
    //test02();
    test03();

    return 0;
}

/*
当main函数中调用test01()时，运行结果：
有参构造函数!
拷贝构造函数!
拷贝构造函数!
析构函数!
析构函数!
析构函数!

当main函数中调用test02()时，运行结果：
无参构造函数!
拷贝构造函数!
析构函数!
析构函数!

当main函数中调用test03()时，运行结果(这里编译器不同，结果可能不同，这是g++5.5编译结果)：
无参构造函数!
0x7ffd4091c4e4
0x7ffd4091c4e4
析构函数!

对于test03()，使用拷贝构造函数实现值方式返回局部对象，老师运行结果：
无参构造函数!
0x7ffd4091c4e4
拷贝构造函数!
析构函数!
0x7ffd4091c4...    -- 一个不同的地址
析构函数!
*/
```

(代码见: [03_拷贝构造函数调用时机.cpp](./03_拷贝构造函数调用时机.cpp))





#### 4.2.4 构造函数调用规则

默认情况下，c++编译器至少给一个类添加3个函数

1．默认构造函数(无参，函数体为空)

2．默认析构函数(无参，函数体为空)

3．默认拷贝构造函数，对属性进行值拷贝



构造函数调用规则如下：

* **如果用户定义有参构造函数，c++不在提供默认无参构造，但是会提供默认拷贝构造**


* **如果用户定义拷贝构造函数，c++不会再提供其他构造函数**



示例：

```C++
#include<iostream>
using namespace std;

class Person {
public:
    // //不提供无参（默认）构造函数
    // Person() {
    //     cout << "无参构造函数!" << endl;
    // }

    //有参构造函数
    Person(int a) {
        age = a;
        cout << "有参构造函数!" << endl;
    }
    //拷贝构造函数
    Person(const Person &p) {
        age = p.age;
        cout << "拷贝构造函数!" << endl;
    }
    //析构函数
    ~Person() {
        cout << "析构函数!" << endl;
    }
public:
    int age;
};

void test01()
{
    Person p1(18);
    //如果不写拷贝构造，编译器会自动添加拷贝构造，并且做浅拷贝操作
    Person p2(p1);

    cout << "p2的年龄为： " << p2.age << endl;
}

void test02()
{
    //如果用户提供有参构造，编译器不会提供默认构造，会提供拷贝构造
    // Person p1;         //此时如果用户自己没有提供默认构造，会出错
    Person p2(10);     //用户提供的有参
    Person p3(p2);     //此时如果用户没有提供拷贝构造，编译器会提供

    //如果用户提供拷贝构造，编译器不会提供其他构造函数
    // Person p4;         //此时如果用户自己没有提供默认构造，会出错
    Person p5(10);     //此时如果用户自己没有提供有参，会出错
    Person p6(p5);     //用户自己提供拷贝构造
}

int main() {

    //test01();
    test02();

    return 0;
}
/*
当main函数中调用test01()时，运行结果：
有参构造函数!
拷贝构造函数!
p2的年龄为： 18
析构函数!
析构函数!

当main函数中调用test02()时，运行结果：
有参构造函数!
拷贝构造函数!
有参构造函数!
拷贝构造函数!
析构函数!
析构函数!
析构函数!
析构函数!
*/
```

(代码见: [04_构造函数调用规则.cpp](./04_构造函数调用规则.cpp))





#### 4.2.5 深拷贝与浅拷贝

深浅拷贝是面试经典问题，也是常见的一个坑

**浅拷贝**：简单的赋值拷贝操作

**深拷贝**：在堆区重新申请空间，进行拷贝操作



**示例：**

```C++
#include<iostream>
using namespace std;

class Person {
public:
    //无参（默认）构造函数
    Person() {
        cout << "无参构造函数!" << endl;
    }
    //有参构造函数
    Person(int age ,int height) {
        
        cout << "有参构造函数!" << endl;

        m_age = age;
        m_height = new int(height);
        
    }
    //拷贝构造函数  
    Person(const Person& p) {
        cout << "拷贝构造函数!" << endl;
        //如果不利用深拷贝在堆区创建新内存，会导致浅拷贝带来的重复释放堆区问题
        m_age = p.m_age;
        // m_height = p.m_height;         // 浅拷贝，出现内存重复释放，error
        m_height = new int(*p.m_height);  // 深拷贝
    }

    //析构函数
    ~Person() {
        cout << "析构函数!" << endl;
        // 析构函数，可以将堆区开辟的数据做释放操作
        if (m_height != NULL)
        {
            delete m_height;
            m_height = NULL;
        }
    }
public:
    int m_age;
    int* m_height;
};

void test01()
{
    Person p1(18, 180);

    Person p2(p1);

    cout << "p1的年龄： " << p1.m_age << " 身高： " << *p1.m_height << endl;
    cout << "p2的年龄： " << p2.m_age << " 身高： " << *p2.m_height << endl;
}

int main() {
    test01();

    return 0;
}
/*
有参构造函数!
拷贝构造函数!
p1的年龄： 18 身高： 180
p2的年龄： 18 身高： 180
析构函数!
析构函数!
*/
```

(代码见: [05_深拷贝与浅拷贝.cpp](./05_深拷贝与浅拷贝.cpp))



![深拷贝与浅拷贝.png](../../assets/深拷贝与浅拷贝.png)

**编译器默认实现的拷贝函数(浅拷贝)**：

```c++
    //拷贝构造函数  
    Person(const Person& p) {
        //如果不利用深拷贝在堆区创建新内存，会导致浅拷贝带来的重复释放堆区问题
        m_age = p.m_age;
        m_height = p.m_height;
    }
```

对这个拷贝构造函数，test01(()中通过`Person p2(p1);`构造p2时，p2的m_Height地址和p1的一样(如上图左半部分，&m_Height都是0x0011)，在代码执行过程中，自动调用析构函数时，先释放p2内存，直接将0x0011内存释放，在释放p1时，就没有内存释放，而是重复释放，出现error。



**深拷贝构造函数**：

```c++
    //拷贝构造函数  
    Person(const Person& p) {
        //如果不利用深拷贝在堆区创建新内存，会导致浅拷贝带来的重复释放堆区问题
        m_age = p.m_age;
        m_height = new int(*p.m_height);
    }
```

利用深拷贝在堆区创建新内存，test01(()中通过`Person p2(p1);`构造p2时，p2的m_Height地址会重新申请一块(如&m_Height都是0x0022)，这样析构函数释放内存的时候就不会重复释放了。



> **总结：如果属性有在堆区开辟的，一定要自己提供拷贝构造函数，防止浅拷贝带来的问题**









#### 4.2.6 初始化列表



**作用：**C++提供了初始化列表语法，用来初始化属性

**语法：**`构造函数()：属性1(值1),属性2（值2）... {}`

**示例：**

```C++
#include<iostream>
using namespace std;

class Person {
public:
    ////传统方式初始化
    //Person(int a, int b, int c) {
    //	m_A = a;
    //	m_B = b;
    //	m_C = c;
    //}

    //初始化列表方式初始化
    // 语法： 构造函数()：属性1(值1),属性2（值2）... {}
    Person(int a, int b, int c) :m_A(a), m_B(b), m_C(c) {}

    void PrintPerson() {
        cout << "mA:" << m_A << endl;
        cout << "mB:" << m_B << endl;
        cout << "mC:" << m_C << endl;
    }
private:
    int m_A;
    int m_B;
    int m_C;
};

int main() {
    Person p(10, 20, 30);
    p.PrintPerson();

    return 0;
}
/*
mA:10
mB:20
mC:30
*/
```

(代码见: [06_初始化列表.cpp](./06_初始化列表.cpp))





#### 4.2.7 类对象作为类成员

C++类中的成员可以是另一个类的对象，我们称该成员为对象成员



例如：

```C++
class A {}
class B
{
    A a；
}
```

B类中有对象A作为成员，A为对象成员



那么当创建B对象时，A与B的构造和析构的顺序是谁先谁后？

- 构造的顺序是 ：先调用对象成员的构造，再调用本类构造
- 析构顺序与构造相反





**示例：**

```C++
#include<iostream>
#include<string>
using namespace std;

class Phone
{
public:
    Phone(string name)
    {
        m_PhoneName = name;
        cout << "Phone构造函数" << endl;
    }

    ~Phone()
    {
        cout << "Phone析构函数" << endl;
    }

    string m_PhoneName;

};


class Person
{
public:

    //初始化列表可以告诉编译器调用哪一个构造函数
    // 第二个属性m_Phone(pName)相当于： Phone m_Phone = pName，这样一种隐式转换法调动构造函数Phone()
    Person(string name, string pName) :m_Name(name), m_Phone(pName)
    {
        cout << "Person构造函数" << endl;
    }

    ~Person()
    {
        cout << "Person析构函数" << endl;
    }

    void playGame()
    {
        cout << m_Name << " 使用" << m_Phone.m_PhoneName << " 牌手机! " << endl;
    }

    string m_Name;
    Phone m_Phone;

};
void test01()
{
    //当类中成员是其他类对象时，我们称该成员为 对象成员
    //构造的顺序是 ：先调用对象成员的构造，再调用本类构造
    //析构顺序与构造相反
    Person p("张三" , "苹果X");
    p.playGame();
}


int main() {
    test01();

    return 0;
}
/*
Phone构造函数
Person构造函数
张三 使用苹果X 牌手机! 
Person析构函数
Phone析构函数
*/
```

(代码见 : [07_类对象作为类成员.cpp](./07_类对象作为类成员.cpp))





#### 4.2.8 静态成员

静态成员就是在成员变量和成员函数前加上关键字static，称为静态成员

静态成员分为：

*  静态成员变量
   *  所有对象共享同一份数据
   *  在编译阶段分配内存
   *  类内声明，类外初始化
*  静态成员函数
   *  所有对象共享同一个函数
   *  静态成员函数只能访问静态成员变量





**示例1 ：**静态成员变量

```C++
#include<iostream>
using namespace std;

class Person
{
    
public:

    static int m_A; //静态成员变量

    //静态成员变量特点：
    //1 在编译阶段分配内存
    //2 类内声明，类外初始化
    //3 所有对象共享同一份数据

private:
    static int m_B; //静态成员变量也是有访问权限的
};

// 静态成员初始化（静态成员类内声明，类外初始化）
int Person::m_A = 10;
int Person::m_B = 10;

void test01()
{
    // 静态成员变量，不属于某个对象上，所有对象都共享同一份数据
    // 静态成员变量两种访问方式
    //1、通过对象
    Person p1;
    p1.m_A = 100;
    cout << "p1.m_A = " << p1.m_A << endl;

    Person p2;
    p2.m_A = 200;

    cout << "p1.m_A = " << p1.m_A << endl;     //static int m_A数据共享，对对象p1和p2都一样
    cout << "p2.m_A = " << p2.m_A << endl;

    //2、通过类名 -- static int m_A数据共享，对对象p1和p2都一样，因此直接通过类名+对象名就可以访问
    cout << "m_A = " << Person::m_A << endl;


    //cout << "m_B = " << Person::m_B << endl; //私有权限访问不到
}

int main() {
    test01();

    return 0;
}
/*
p1.m_A = 100
p1.m_A = 200
p2.m_A = 200
m_A = 200
*/
```

(代码见: [08_静态成员变量.cpp](./08_静态成员变量.cpp))



**示例2：**静态成员函数

```C++
#include<iostream>
using namespace std;

class Person
{

public:

    //静态成员函数特点：
    //1 程序共享一个函数
    //2 静态成员函数只能访问静态成员变量
    
    static void func()
    {
        cout << "static func()调用" << endl;
        m_A = 100;
        //m_B = 100; //错误，不可以访问非静态成员变量，无法区分是哪个对象的m_B
    }

    static int m_A;    //静态成员变量
    int m_B;           //非静态成员变量
private:

    //静态成员函数也是有访问权限的
    static void func2()
    {
        cout << "static func2()调用" << endl;
    }
};

// 初始化静态成员变量m_A
int Person::m_A = 10;

void test01()
{
    //静态成员变量两种访问方式

    //1、通过对象
    Person p1;
    p1.func();

    //2、通过类名
    Person::func();

    //Person::func2(); //私有权限访问不到
}

int main() {
    test01();

    return 0;
}
/*
static func()调用
static func()调用
*/
```

(代码见: [09_静态成员函数.cpp](./09_静态成员函数.cpp))



