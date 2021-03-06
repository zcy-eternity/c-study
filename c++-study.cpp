#include<iostream>

using namespace std;

//struct 结构体名 变量名 = （成员1值，成员2值…)
typedef struct Student{
    string name;
    int age;
    int score;
}student;

typedef struct Hero{
    string name;
    int age;
    string categories;
}Hero;
//创建5个人并按年龄排序
int study2(){
    Hero hero[5] = {{"欣南",20,"火"},
                    {"东杉",24,"木"},
                    {"北淼",23,"水"},
                    {"坤中",18,"土"},
                    {"西昭",22,"金"},};
    int len = sizeof(hero)/sizeof(hero[0]);
    for(int i=0;i<len-1;i++)
        for(int j=0;j<len-1-i;j++){
            if(hero[j].age>hero[j+1].age){
                swap(hero[j],hero[j+1]);
            }
        }
    for(int i=0;i<len;i++){
        cout<<hero[i].name <<hero[i].age<<hero[i].categories<<endl;
    }
    return 0;
}
int study() {
    //作用:利用指针访问数组元素
    int arr[] = {1, 2, 3, 4};
    int *a = arr;

    //在C语言中的数组本质上其实也是指针，即：*a 等同于 a[]。
    //a表示a对应的存储单元中的数据。&a表示a对应的存储单元的地址。
    //*a表示：要求a对应的存储单元中的数据一定是另一个存储单元的地址。*a表示另一个存储单元中的数据。

    //结构体指针
    //作用：通过指针访问结构体中的成员
    //利用操作符->可以通过结构体指针访问结构体属性
    struct Student s1;
    struct Student *p = &s1;
    p->score = 10;
    student s[100];
    s[0].name = "yan";
//  new运算符 在堆区开辟数据
//  利用new创建的数据，会返回该数据对应类型的指针

//   new [] 一个对象数组时，需要保存数组的维度，C++ 的做法是在分配数组空间时多分配了 4 个字节的大小，
//   专门保存数组的大小，在 delete [] 时就可以取出这个保存的数，就知道了需要调用析构函数多少次了。

    int *pa = new int[10];//new int(10)就是创建一个存放整型的空间存10
    delete[] pa;//释放数组的时候要加[]

//    int *p[4];  //定义一个指针数组，该数组中每个元素是一个指针，每个指针指向哪里就需要程序中后续再定义了。
//    int (*p)[4];  //定义一个数组指针，该指针指向含4个元素的一维数组（数组中每个元素是int型）。

//    引用 作用1:给变量起别名
//    语法：数据类型 &别名 = 原名
//    引用必须初始化——告诉它它是谁的别名
//    引用在初始化之后，不可以改变
//    本质：引用的本质在c++内部实现是一个指针常量,引用一旦被初始化之后就不能更改。
    int a1 = 0;
    int &b1 = a1;  //a和b操作的是同一块内存

//    引用 作用2:做函数参数
//    作用：函数传参时，可以利用引用让形参修饰实参
//    优点：可以简化指针修改实参（传址）把地址传进去，然后用*运算取地址的内容
//    int ref = 0;
//    ChangeRef(&ref);
//    void ChangeRef(int* ref);
//    ------------------------------
//    int ref = 0;
//    changeRef(ref)
//    void ChangeRef(int& ref);

//    在c++中函数形参列表中的形参是可以有默认值的。
//    语法：返回值类型 函数名(参数=默认值)
//    注意事项：如果某个位置已经有了默认参数，那么从这个位置往后都要有默认参数

//    在函数参数中，使用常量引用非常重要。因为函数有可能接受临时对象，而且同时需要禁止对所引用对象的一切修改
//    int test() {
//        return 1;
//    }
//    void fun(int& x) {
//
//    }
//    int main()
//    {
//        int m = 1;
//        fun(m);         // ok
//        fun(1);         // error
//        fun(test());    // error
//        return 0;
//    }

//    函数返回值时会产生一个临时变量作为函数返回值的副本，而返回引用时不会产生值的副本
//    注意千万不要返回局部对象的引用
//    1、引用函数的参数，当然该参数也是一个引用
//    const string &shorterString(const string &s1,const string &s2)
//    {
//        return s1.size()<s2.size()?s1:s2;
//    }
//    2、返回 this 指向的对象 this指针
//    这里返回值如果是Person，就创建了一个新的对象
//    Person& PersonAddPerson(Person &p)
//    {
//        this->age += p.age;
//        return *this;
//    }
//    注意：使用默认构造函数的时候，不要加(),编译器会认为这是一个函数的声明
//    Person p1; 无参
//    Person p2 = Person(10); 有参
//    隐式转换法
//    Person p4 = 10;//相当与Person p4 = Person(10);

//    如果用户定义有参构造函数，C++不再提供默认无参构造，但是会提供默认拷贝构造
//    如果用户定义拷贝构造函数，C++不会再提供其他构造函数
//    Person(const Person& p)
//    {
//        m_Age = p.m_Age;
//        Person的拷贝构造函数调用
//    }

//    默认情况下，C++编译器至少给一个类添加三个函数
//    默认构造函数(无参、函数体为空)
//    默认析构函数(无参、函数体为空)
//    默认拷贝函数构造函数，对属性值拷贝

//    静态的成员函数可以访问静态的成员变量，不可以访问非静态的成员变量
//    通过类名也可以访问
//    Person::func();

//    友元的目的就是让一个函数或者类 访问另一个类中的私有元素
//    友元的关键字——friend
//    友元的三种实现：

//    1、全局函数做友元
//    就是将此函数在类的最上面写一个声明，前面加一个friend。
//    void goodGay(){
//
//    }
//    class Building{
//        friend void goodGay();
//    };

//    2、类做友元
//    一个类在另一个中friend class xx。
//    class GoodGay{
//    public:
//        GoodGay();
//    public:
//        Building* building; //在前面先声明一下 class Building;
//    };
//
//    class Building{
//        //GoodGay是Building类的好朋友，可以访问其私有属性
//        friend class GoodGay;
//    };
//    3、成员函数做友元 指定类
//    friend void GoodGay::visit();

//    继承 class Java : public BasePage
//    继承的语法——class 子类 :继承方式 父类 继承方式一共有三种：公共继承 保护继承 私有继承
//    父类中的隐私权限成员，子类访问不到

//    子类继承父类后，当创建子类时，也会调用父类的构造函数。
//    先构造父类，再构造子类
//    先析构子类，再析构父类

//    当子类与父类出现同名的成员。
//    访问子类同名成员，直接访问即可
//    访问父类同名成员，需要加作用域 son.Base::m_A

//    在多态中，通常父类汇中虚函数的实现是毫无意义的，主要都是调用子类重写的内容。
//    因此可以将虚函数改为纯虚函数。 当类中有了纯虚函数，这个类也称为抽象类。
//    virtual void func() = 0;//注意:不要忘掉virtual!

//动态多条满足条件
//
//1.有继承关系
//2.子类重写父类的虚函数 virtual void speak() 实现地址晚绑定
// 	AbstractCalculator* abc = new AddCalculator;//父类指针指向子类对象
//	abc->m_Num1 = 10;
//	abc->m_Num2 = 10;
//	abc->getResult();
//	//堆区数据，手动开辟手动释放
//	delete abc;


};


//作用:利用指针作函数的参数，可以修改实参的值。
void sort(int *a, int n){
    //冒泡排序
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-1-i;j++){
            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
        }
}

int main(){
    int a[] = {1,4,8,5,9,3};
    int len = sizeof(a)/sizeof(a[0]);
    sort(a,len);
    for(int i=0;i<len;i++)
        cout<<a[i]<<" ";
    cout<<endl;
    study2();
    return 0;
}