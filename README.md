## c++ study
#### 求数组长度
如果sizeof(数组名)的调用有两种情况：
1. 数组作为参数压栈，并作为参数传入 sizeof(数组名) ：计算出来的值实际上是指针的长度。
2. 数组是在当前的函数中定义，随后作为参数 传入 sizeof(数组名) ： 计算出来的值是整个数组的长度。但是如果当数组作为函数的参数进行传递时，该数组自动退化为同类型的指针。
```c++
int a[] = {1,4,8,5,9,3};
int len = sizeof(a)/sizeof(a[0]);
```
#### 指针
- 基本用法
```c++
//作用:利用指针访问数组元素
int arr[] = {1, 2, 3, 4};
int *a = arr;
```
在C语言中的数组本质上其实也是指针，即：*a 等同于 a[]。
a表示a对应的存储单元中的数据。&a表示a对应的存储单元的地址。
*a表示：要求a对应的存储单元中的数据一定是另一个存储单元的地址。*a表示另一个存储单元中的数据。
- 指针数组 数组指针
```c++
int *p[4];  //定义一个指针数组，该数组中每个元素是一个指针，每个指针指向哪里就需要程序中后续再定义
int (*p)[4];  //定义一个数组指针，该指针指向含4个元素的一维数组（数组中每个元素是int型）()优先级高
```
#### 冒泡排序
```c++
//作用:利用指针作函数的参数，可以修改实参的值。
void sort(int *a, int n){
    //冒泡排序
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-1-i;j++){
            if(a[j]>a[j+1])
                swap(a[j],a[j+1]);
        }
}
```
#### 结构体
- 结构体指针
   作用：通过指针访问结构体中的成员
   利用操作符->可以通过结构体指针访问结构体属性
```c++
struct Student s1;
struct Student *p = &s1;
p->score = 10;
```
- 结构体数组
```c++
struct Student s1;
student s[100];
s[0].name = "yan";
```
- 结构体示例
```c++
//struct 结构体名 变量名 = （成员1值，成员2值…)
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
```
#### new运算符
在堆区开辟数据
利用new创建的数据，会返回该数据对应类型的指针
new [] 一个对象数组时，需要保存数组的维度，C++ 的做法是在分配数组空间时多分配了 4 个字节的大小来
专门保存数组的大小，在 delete [] 时就可以取出这个保存的数，就知道了需要调用析构函数多少次了
```c++
int *pa = new int[10];//new int(10)就是创建一个存放整型的空间存10
delete[] pa;//释放数组的时候要加[]
```
#### 引用
- 作用1:给变量起别名
语法：数据类型 &别名 = 原名
引用必须初始化——告诉它它是谁的别名
引用在初始化之后，不可以改变
本质：引用的本质在c++内部实现是一个指针常量,引用一旦被初始化之后就不能更改。
```c++
int a1 = 0;
int &b1 = a1;  //a和b操作的是同一块内存
```
- 引用 作用2:做函数参数
作用：函数传参时，可以利用引用让形参修饰实参
优点：可以简化指针修改实参（传址）把地址传进去，然后用*运算取地址的内容
```c++
//指针
int ref = 0;
ChangeRef(&ref);
void ChangeRef(int *ref);
//引用
int ref = 0;
changeRef(ref)
void ChangeRef(int &ref);
```
#### 字符串
- C-风格字符串
C语言风格的处理方式是将字符串置于字符数组中，每个字符位于一个数组元素之中，并且以空字符(’\0’)结尾。
```c++
char greeting[5] = {'H','e','l','l','o'}; //这是一个字符数组
char greeting[6] = {'H','e','l','l','o','\0'}; //这是一个字符串
```
- 字符串的初始化
  C++ 编译器会在初始化数组时，自动把 ‘\0’ 放在字符串的末尾
```c++
char greeting[] = "Hello";
```
初始化字符数组后可修改声明的字符数组中的字符，
也可重新写入，但写入后原来的字符数组中的值消失
```c++
char a[] = "hello";
cin>>a;
```
- 作为局部变量的字符数组不能直接返回，而字符指针可以 
- 调用者也不能用数组来接受返回值，要用指针来接，否则会报异常
```c++
//错误
char* fork_user_name(){
    char name[] = "zcy";
    return name;
}
//正确
char* fork_user_name2(){
    char *name = "zcy";
    return name;
}

char *str = fork_user_name2();
```
首先我们要知道，常量是放在数据段里面的。 局部变量 name 保存在栈中
字符串的值是一个常量，保存在常量区。即便函数返回了，数据段里面的常量数据也还不会消亡
它会直到程序结束才会消失，其内存空间直到程序运行结束才会被释放。
所以，返回的地址是一个实际存在的有效地址。


- next数组
```c++
  int* get_next(char str[]){
      int i=0,j=-1;
      int *next = new int[strLen(str)+1];
      next[0] = -1;
      while (i<strLen(str)){
          if(str[i]==str[j]||j==-1){
              i++;
              j++;
              next[i]=j;
          } else
              j = next[j];
      }
      return next;
  }
```
next数组的随着i指针的更新而更新<br>
i指针更新有两种情况：<br>
第一种是第一个字符就失配 j = -1    第二种是字符出现匹配i指针后移<br>
a b a a b c<br>
第一次循环j=-1;<br>
i j 指针同时会后移 next[1] = 0   i从第二个字符开始，j从第一个字符开始比较<br>
a b a a b c <br>
&nbsp;&nbsp;&nbsp;a b a a b c
第二次循环<br>
失配 j = next[0] (-1) 模式串滑动 i++ next[2] = 0; j++<br>
a b a a b c<br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;a b a a b c<br>
第三次循环<br>
第一个字符匹配 i++ j++  next[3]= 1 第二个字符失配 j回到next[j]的位置<br>

- 一些常用函数

| 序号 | 函数 |                            功能 |
| --- |:---:|------------------------------:|
|1|strcpy(s1,s2)|              复制字符串 s2 到字符串 s1 |
|2|strcat(s1,s2)|          连接字符串 s2 到字符串 s1 的末尾 |
|3|strlen(s1)|                  返回字符串 s1 的长度 |
|4|strcmp(s1,s2)|                  返回s1与s2的比较结果 |
|5|strchr(s1,ch)|  返回一个指针，指向字符串s1中字符ch的第一次出现的位置 |
|6|strstr(s1,s2)|    返回一个指针，指向字符串s1中s2的第一次出现的位置 |
#### 函数
- 默认参数
在c++中函数形参列表中的形参是可以有默认值的。
语法：返回值类型 函数名(参数=默认值)
注意事项：如果某个位置已经有了默认参数，那么从这个位置往后都要有默认参数
- 常量引用
在函数参数中，使用常量引用非常重要
因为函数有可能接受临时对象，而且同时需要禁止对所引用对象的一切修改
```c++
int test() {
    return 1;
}
void fun(int &x) {

}
int main()
{
    int m = 1;
    fun(m);         // ok
    fun(1);         // error
    fun(test());    // error
    return 0;
}
```
- 函数返回值
函数返回值时会产生一个临时变量作为函数返回值的副本，而返回引用时不会产生值的副本
注意千万不要返回局部对象的引用
<br/>
1、返回函数的参数，该参数也是一个引用
```c++
const string &shorterString(const string &s1,const string &s2){
    return s1.size()<s2.size()?s1:s2;
}
```
2、返回 this 指向的对象 this指针
```c++
//这里返回值如果是Person，就创建了一个新的对象
Person& PersonAddPerson(Person &p)
{
    this->age += p.age;
    return *this;
}
```
- 数组作为参数的传递
当数组作为参数传递到函数时，形参直接是数组的头地址（也就是数组下标为0的地址）
实参直接用数组的名字，这样经过函数可以改变外部数组的值
```c++
//可以改变外部数组的值
//声明方式
void BubbleSort(int R[], int n){
  *******
}
//调用方式
BubbleSort(R, n);
```
#### 类
- new
注意：使用默认构造函数的时候，不要加(),编译器会认为这是一个函数的声明
```c++
Person p1; //无参
Person p2 = Person(10); //有参
//隐式转换法
Person p4 = 10;//相当与Person p4 = Person(10);
```
- 拷贝构造函数
如果用户定义有参构造函数，C++不再提供默认无参构造，但是会提供默认拷贝构造
如果用户定义拷贝构造函数，C++不会再提供其他构造函数

默认情况下，C++编译器至少给一个类添加三个函数
默认构造函数(无参、函数体为空)
默认析构函数(无参、函数体为空)
默认拷贝函数构造函数，对属性值拷贝
```c++
//Person的拷贝构造函数调用
Person(const Person& p)
{
    m_Age = p.m_Age;
}
```
- 静态的成员函数
静态的成员函数可以访问静态的成员变量，不可以访问非静态的成员变量
通过类名也可以访问
```c++
Person::func();
```
- 继承
继承的语法——class 子类 :继承方式 父类 
继承方式一共有三种：公共继承 保护继承 私有继承
父类中的隐私权限成员，子类访问不到
```c++
class Java : public BasePage
```

子类继承父类后，当创建子类时，也会调用父类的构造函数。
先构造父类，再构造子类
先析构子类，再析构父类

当子类与父类出现同名的成员。
访问子类同名成员，直接访问即可
访问父类同名成员，需要加作用域 son.Base::m_A
- 多态
动态多条满足条件
1.有继承关系
2.子类重写父类的虚函数 virtual void speak() 实现地址晚绑定

在多态中，通常父类汇中虚函数的实现是毫无意义的，主要都是调用子类重写的内容。
因此可以将虚函数改为纯虚函数。 当类中有了纯虚函数，这个类也称为抽象类。
```c++
virtual void func() = 0;//注意:不要忘掉virtual! 纯虚函数

AbstractCalculator* abc = new AddCalculator;//父类指针指向子类对象
abc->m_Num1 = 10;
abc->m_Num2 = 10;
abc->getResult();
//堆区数据，手动开辟手动释放
delete abc;
```

#### 友元
友元的目的就是让一个函数或者类 访问另一个类中的私有元素
友元的关键字——friend
- 1、全局函数做友元
```c++
//就是将此函数在类的最上面写一个声明，前面加一个friend。
void goodGay(){

}
class Building{
    friend void goodGay();
};
```
- 2、类做友元
```c++
//一个类在另一个中friend class xx。
class GoodGay{
  public:
    GoodGay();
  public:
    Building* building; //在前面先声明一下 class Building;
};

class Building{
  //GoodGay是Building类的好朋友，可以访问其私有属性
  friend class GoodGay;
};
```
- 3、成员函数做友元 指定类
```c++
friend void GoodGay::visit();
```