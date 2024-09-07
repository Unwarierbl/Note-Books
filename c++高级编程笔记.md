# C++ 高级编程学习笔记

## 1 C++和标准库速成

### 1.1 c++基础知识

#### 1.1.11 三向比较运算符

三向比较运算符： ***<=>***
返回类枚举类型，定义在 ***\<compare>*** 和 std 名称空间中。如果操作数是整数类型，则结果时所谓的强排序，并且可以是以下之一。

- ***strong_ordering***::less  不用解释啦
- strong_ordering::greater
- strong_ordering::equal

如果操作数是浮点类型，结果是一个偏序。

- ***partial_ordering***::less
- partial_ordering::greater
- partial_ordering::equivalent
- partial_ordering::unordered：如果有一个操作数是非数字或者两个操作数都是非数字

以下是它的用法的示例：

~~~c++
int i{11};

strong_ordering result{i <=> 0};
if (result == strong_ordering::less) {
    cout << "less" << endl;
}
if (result == strong_ordering::greater) {
    cout << "greater" << endl;
}
if (result == strong_ordering::equal) {
    cout << "equal" << endl;
}
~~~

还有一种弱排序，这是可以选择的另一种排序类型，以针对你自己的类型实现三向比较。

- ***weak_ordering***::less
- weak_ordering::greater
- weak_ordering::equivalent

最后，\<compare> 提供命名的比较函数来解释排序结果。这些函数是 std::is_eq()、is_neq()、is_lt()、is_lteq() 以及 is_gteq()。

#### 1.1.13  属性

属性是一种将可选的和/或特定于编译器产商的信息添加到源代码中的机制。在 C++ 对属性进行标准化之前，编译器缠上决定了如何指定此类信息，例如 \_\_attribute__ 和\_\_declspec 等。从 C++11 开始，通过使用双方括号 \[[attribute]] 对属性进行标准化的支持。
C++ 标准定义了几个在函数上下文中有用的标准属性。

1. ***\[[nodiscard]]***
    \[[nodiscard]] 属性可用于有一个返回值的函数，以使编译器在该函数被调用却没有对返回的值进行任何处理时发出警告。以下是一个例子。

    ~~~c++
    [[nodiscard]] int func()
    {
        return 42;
    }

    int main()
    {
        func();
    }
    ~~~

    编译器将会发出警告。
    例如，此特性可用于返回错误代码的函数。通过将 \[[nodiscard]] 属性添加到此类函数中，卒后无代码就无法被忽视。
    更笼统地说，\[[nodiscard]] 属性可用于类、函数和枚举。
    从 C++20 开始，可以字符串形式为 \[[nodiscard]] 属性提供一个原因，例如：

    ~~~c++
    [[nodiscard("Some explanation")]] int func();
    ~~~

2. ***\[[maybe_unused]]***
    \[[maybe_unused]] 属性可用于禁止编译器在未使用某些内容时发出警告，如下例所示：

    ~~~c++
    int func(int param1, int param2)
    {
        return 42;
    }
    ~~~

    如果将编译器警告级别设置的足够高，则此函数定义将导致两个编译器警告。
    通过使用 \[[maybe_unused]]，可以阻止此类警告。

    ~~~c++
    int func(int param1, [[maybe_unused]] int param2)
    {
        return 42;
    }
    ~~~

    在这种情况下，第二个参数标记有禁止其警告的属性。现在，编译器仅对 param1 发出警告。
    \[[maybe_unused]] 属性可用于类和结构体、非静态数据成员、联合、typedef、类型别名、变量、函数、枚举以及枚举值。

3. ***\[[noreturn]]***
    向函数添加 \[[noreturn]] 属性意味着它永远不会将控制权返回给调用点。通常，函数要么导致某种终止（进程终止或线程终止），要么引发异常。使用此属性，编译器可以避免发出某些警告或错误，因为它现在可以更多地来哦姐该函数的用途。
4. ***\[[deprecated]]***
    \[[deprecated]]可用于将某些内容标记为以弃用，这意味着仍可以使用它，但不鼓励使用。此属性接受一个可选参数，该参数可用于解释不赞成使用的原因。如以下示例所示：

    ~~~c++
    [[deprecated("Unsafe method, please use xyz")]] void func();
    ~~~

    如果使用了已弃用的函数，将会收到编译错误或警告。

5. \[likely] 和 \[[unlikely]]
    这个不需要知道了

#### 1.1.15 std::array

C++ 有一种固定大小的特殊容器 std::array，这种容器在 <array> 头文件种定义。它基本上是对 C 风格的数组进行了简单包装。
用 std::array 替代 C 风格的数组会带来很多好处。它总是知道自身大小；不会自动转换为指针，从而避免了某些类型的 bug；具有迭代器，可方便地遍历元素。详见第 17章迭代器。
array 容器的用法如下：

~~~c++
array<int, 3> arr{9, 8, 7};
cout << format("Array size = {}", arr.size() << endl);
cout << format("2nd element = {}", arr[1]) << endl;
~~~

C++ 支持所谓的类模板参数推导（CTAD），详见第 12 章。这可以避免为某些类模板指定尖括号之间的模板类型。CTAD 仅在初始化时起作用，因为编译器使用此初始化自动推导模板类型。这适用于 std::array，如下所示：

~~~c++
array arr{9, 8, 7};
~~~

#### 1.1.16 std::vector

标准库提供了多个不同的非固定大小容器，可用于存储信息。std::vector 就是此类容器的一个示例，它在 \<vector> 声明，用一种更灵活和安全的机制取代 C风格数组的概念。用户不需要担心内存的管理，因为 vector 将自动分配足够的内存来存放其元素。vector 是动态的，意味着可在运行时添加和删除元素。容器详见第 18 章。下面演示 vector 的基本功能。

~~~c++
vector<int> myVector{11, 22};

myVector.push_back(33);
myVector.push_back(44);

cout << format("lst element: {}", myVector[0]) << endl;
~~~

myVector 被声明为 vector\<int>。vector 是一个泛型容器，几乎可容纳任何类型的对象，但是 vector 中的所有元素不许是同一类型，在尖括号内指定这个类型。模板详见第 12 章和 26 章。
与 std::array 相同，vector 类模板支持 CTAD，允许按下列方式定义 myVector。

~~~c++
vector myVector{11, 22};
~~~

再次说明，需要初始化器才能使 CTAD 正常工作。以下是非法的：

~~~c++
vector myVector;
~~~

为向 vector 中添加元素，可使用 push_back() 方法。可使用类似数组的语法（即 operator\[]）访问各个元素。

#### 1.1.17 std::pair

std::pair 类模板定义在 \<utility> 中。它可将两个不同类型的值组合在一起。可通过 first 和 second 公共数据成员访问这些值。这是一个例子：

~~~c++
pair<double, int> myPair{1.23, 5};
cout << format("{} {}", myPair.first, myPair.second);
~~~

pair 也支持 CTAD，示例略。

#### 1.1.18 std::optional

在 \<optional> 中定义的 std::optional 保留特定类型的值，或者不包含任何值。
基本上，如果想要允许值是可选的，则可以将 optional 用于函数的参数。如果函数可能返回可可能不返回某些内容，则通常也将 optional 用作函数的返回类型。这消除了从函数中返回“特殊”值的需要，例如 nullptr、end()、-1，EOF 之类的。它还消除了将函数编写为返回代表成功或失败的布尔值的需求，同时将函数的实际结果存储在作为输出参数传递给函数的实参中（类型为对非 const 的引用的参数）。
optional 类型是一个类模板，因此必须在简括号之间指定所需的实际类型，如 optional\<int>。
这是一个返回 optional 的函数的例子：

~~~c++
optional<int> getData(bool giveIt)
{
    if (giveIt) {
        return 42;
    }
    return nullopt;
}
~~~

可以按下列方式调用这个函数：

~~~c++
optional<int> data1{getData(true)};
optional<int> data2{getData(false)};
~~~

可以用 has_value() 方法判断一个 optional 是否有值，或简单地将 optional 用在 if 语句中。

~~~c++
cout << "data1.has_value = " << data1.has_value() << endl;
if (data2) {
    cout << "data2 has a value." << endl;
}
~~~

如果 optional 有值，可以使用 value() 或解引用运算符访问它。

~~~c++
cout << "data1.value = " << data1.value() << endl;
cout << "data2.value = " << *data1 << endl;
~~~

如果对一个空的 optional 使用 value()，将抛出 std::has_optional_access 异常。
value_or() 可以用来返回 optional 的值，如果 optional 为空，则返回指定的值。

~~~c++
cout << "data2.value = " << data2.value_or(0) << endl;
~~~

注意，不能将引用保存在 optional 中，所以 optional\<T&> 是无效的。但是，可以将指针保存在 optional 中。

#### 1.1.19 结构化绑定

结构化绑定允许绑定多个变量，这些变量使用数组、结构图、pair 或元组中的元素以初始化。
例如，假设有下面的数组：

~~~c++
array values{11, 22, 33};
~~~

可声明 3 个变量 x、y 和 z，像下面这样使用数组中的 3 个值进行初始化。注意，必须为结构化绑定使用 auto 关键字。例如，不能用 int 替代auto。

~~~c++
auto [x, y, z]{values};
~~~

使用结构化绑定声明的变量必须与右侧表达式中的值数量匹配。
如果所有非静态成员都是公有的，也可将结构化绑定用于结构体。例如：

~~~c++
struct Point
{
    double m_x, m_y, m_z;
};
Point point;
point.m_x = 1.0;
point.m_y = 2.0;
point.m_z = 3.0;
auto [x, y, z]{point};
~~~

正如最后一个例子，以下代码将 pair 中的元素分解为单独的变量：

~~~c++
pair myPair{"hello", 5};
auto [theString, theInt]{myPair};
cout << format("theString: {}", theString) << endl;
cout << format("theInt: {}", theInt) << endl;
~~~

通过使用 auto& 或 const auto& 代替 auto，还可以使用结构化绑定语法创建一组对非 const 的引用或 const 引用。

#### 1.1.20 循环

C++ 提供了四种循环结构

1. while 循环
2. do/while 循环
3. for 循环
4. 基于区间的 for 循环
   这种循环允许方便的迭代容器中的元素，可用于C风格的数组、初始化列表，也可用于具有返回迭代器的 begin() 和 end() 函数的类型，例如 std::array、std::vector 等。演示如下：

   ~~~c++
    void demo()
    {
        std::array<int, 4> arr = {1, 2, 3, 4};
        for (int i : arr) {
            std::cout << i << std::endl;
        }
    }
   ~~~

#### 1.1.21 初始化列表

初始化列表在 ***\<initializer_list>*** 头文件中定义，利用初始化列表，可轻松编写能接受可变数量参数的函数。演示如下：

~~~c++
#include <initializer_list>

using namespace std;

int makeSum(initializer_list<int> lst)
{
    int total = 0;
    for (int value : lst) {
        total += value;
    }
    return total;
}
~~~

makeSum() 函数接受一个整形类型的初始化列表作为参数，可按如下方式使用该函数：

~~~c++
int a = makeSum({1, 2, 3});
int b = makeSum({10, 20, 30, 40, 50, 60});
~~~

此处函数必须都是整数，否则会报错。

#### 1.1.25 统一初始化

在 C++11 之前，各类型的初始化并非总是统一的。例如：

~~~c++
struct CircleStruct
{
    int    x, y;
    double radius;
};
class CircleClass
{
private:
    int    m_x, m_y;
    double m_radius;
public:
    CircleClass(int x, int y, double radius)
        : m_x{x}
        , m_y{y}
        , m_radius{radius}
    {}
};
~~~

在 C++11 之前，CircleStruct 类型变量和 CircleClass 类型变量的初始化是不同的。

~~~c++
CircleStruct myCircle1 = {10, 10, 2.5};
CircleClass  myCircle2{10, 10, 2.5};
~~~

对于结构体版本，可使用 {...} 语法。然而，对于类版本，需要使用函数符号 (...) 调用构造函数。
自 C++11 以后，允许一律使用 {...} 语法初始化类型，如下所示。

~~~c++
CircleStruct myCircle3 = {10, 10, 2.5};
CircleClass  myCircle4 = {10, 10, 2.5};
~~~

定义 myCircle4 时将自动调用 CircleClass 的构造函数。甚至等号也是可选的。因此下面的代码与前面的代码等价：

~~~c++
CircleStruct myCircle5{10, 10, 2.5};
CircleClass  myCircle6{10, 10, 2.5};
~~~

使用统一初始化并不局限于结构和类，它还可用于初始化 C++ 中的任何内容。例如：

~~~c++
int a = 3;
int b{3};
int c = {3};
int d{3};
~~~

统一初始化还可用于对变量进行零初始化，只需要指定一对空的大括号。例如：

~~~c++
int e{};
~~~

使用统一初始化的一个优点时可以阻止窄化（narrowing）。当使用旧式风格的赋值语法初始化变量时，C++ 隐式地执行窄化。例如：

~~~c++
void func(int i)
{
    /* ... */
}

int main()
{
    int x = 3.14;
    func(x);
}
~~~

在 main() 的两行代码中，C++ 在对 x 赋值或调用 func() 之前，会自动将 3.14 截断为 3。在任何情况下，窄化转换都不应该被忽视，因为它们可能会引起细微的错误。使用统一初始化。如果编译器完全支持 C++11 标准，x 的赋值和 func() 的调用都会生成编译错误。
如果需要窄化转换，建议使用准则支持库（GSL）中提供的 gsl::narrow_cast() 函数。
统一初始化还可用来初始化动态分配的数组：

~~~c++
int* myArray = new int[4]{0, 1, 2, 3};
~~~

从 C++20 开始，可以省略数组的大小 4.
统一初始化还可在构造函数初始化器中初始化类成员数组：

~~~c++
class myClass
{
private:
    int m_array[4];

public:
    myClass()
        : m_array{0, 1, 2, 3}
    {}
};
~~~

统一初始化还可用于标准库容器，如 std::vector。

>**注意：**
>考虑到所有这些好处，建议使用统一初始化，而不是使用赋值语法初始化变量。

**指派初始化器.**

C++20 引入了指派初始化器，以使用它们的名称初始化所谓聚合的数据成员。聚合类型时满足以下限制的数组类型的对象或结构或类的对象：仅 public 数据成员、无用户声明或继承的构造函数、无虚函数和无虚基类、private 或 protected 的基类（见第 10 章）。指派初始化器以点开头，后跟数据成员的名称。指派初始化的顺序的必须与数据成员的声明顺序相同。不允许混合使用指派初始化器和非指派初始化器。未使用指派初始化器初始化的任何数据成员都将使用其默认值进行初始化，这意味着：

- 拥有类内初始化器的数据成员会得到该值。
- 没有类内初始化器的数据成员会被零初始化。

如下所示：

~~~c++
struct Employee
{
    char firstInitial;
    char lastInitial;
    int  employeeNUmber;
    int  salary{75000};
};
~~~

在前面，这种 Employee 结构是使用如下的统一初始化语法初始化的：

~~~c++
Employee anEmployee{'J', 'D', 42, 80000};
~~~

使用指派初始化器，可以被写成这样：

~~~c++
Employee anEmployee{.firstInitial   = 'J',   //
                    .lastInitial    = 'D',
                    .employeeNUmber = 42,
                    .salary         = 80000};
~~~

使用指派初始化器的好处是，与使用统一初始化语法相比，它更容易理解指派初始化器正在初始化的内容。
使用指派初始化器，如果对某些成员的默认值感到满意，则可以跳过它们的初始化。
如果使用统一初始化语法，这是不可以的。
使用指派初始化器的最后一个好处是，当新成员被添加到数据结构时，使用指派初始化器的现有代码将继续器作用。新的数据成员将使用其默认值进行初始化。

#### 1.1.27 const 的用法

基本上，关键字 const 是 constant 的缩写，它博爱是某些内容保持不变。编译器通过将任何试图将其更改的行为标记为错误，用来保证此需求。此外，启用优化后，编译器可以利用此知识生成更好的代码。

1. const 修饰类型
    - const 与指针
        存在一个简单的规则：const 关键字作用于其直接左侧的内容。
        >**注意**
        >有另一个易于记忆的规则，可以用于读懂复杂的变量声明：从右向左读。例如，int \* const ip 从右到左读取，得到 “ip 是指向 int 的 const 的指针。”另外，int const * ip 读为 “ip 是指向 const int 的指针”、而 const int \* ip 读为 “ip 是指向 int 常量的指针”。

    - 使用 const 保护参数
2. const 方法
    略。
    > **注意：**
    > 为了遵循 const-correctness 原则，建议将不改变对象的任何数据成员的成员函数声明为 const。与非 const 成员函数也被称为赋值函数（mutator）相对，这些成员函数书也称为检查器（inspector）。

#### 1.1.28 constexpr 关键字

C++ 一直有常量表达式的概念，即在编译器求值的表达式，在某些情况下，必须使用常量表达式。例如，定义数组时，数组的大小需要为常量表达式。由于此限制，以下代码在 C++ 中无效。

~~~c++
const int getArraySize()
{
    return 32;
}

int main()
{
    int myArray[getArraySize()];
}
~~~

使用 constexpr 关键字，getArraySize() 函数可以被重定义，允许在常量表达式用调用它。

~~~c++
constexpr int getArraySize()
{
    return 32;
}

int main()
{
    int myArray[getArraySize()];
}
~~~

将函数声明为 constexpr 对函数的功能施加了很多限制，因为编译器必须能够在编译时对函数求值。例如，允许 constexpr 函数调用其他 constexpr 函数，但不允许调用任何非 constexpr 函数。这样的函数不允许有任何副作用，也不能引发任何异常。

#### 1.1.29 consteval 关键字

上一节的 constexpr 关键字指定函数可以在编译期执行，但不能保证一定在编译期执行，采用以下 constexpr 函数：

~~~c++
constexpr double inchToMm(double inch)
{
    return inch * 25.4;
}
~~~

如果按以下方式调用，则会在编译时满足对函数求值。

~~~c++
constexpr double const_inch{6.0};
constexpr double mml{inchToMm(const_inch)};
~~~

然而，如果按以下方式调用，函数将不会在编译期被求值，而是在运行时！

~~~c++
double dynamic_inch{8.0};
double mm2{inchToMm(dynamic_inch)};
~~~

如果确实希望保证始终在编译时对函数求值，则需要使用 C++20 的 consteval 关键字将函数转换为所谓的立即函数（immediate function）。可以按照如下方式更改 inchToMm() 函数：

~~~c++
consteval double inchToMm(double inch)
{
    return inch * 25.4;
}
~~~

现，对 inchToMm() 的第一次调用仍然可以正常编译，并且可以在编译期进行求值。但是，第二个调用现在会导致编译错误，因为无法在编译期对其进行求值。

#### 1.1.26 指针和动态内存

1. 堆栈和堆
   堆栈帧是为每个函数分配的独立的内存空间，在堆栈上分配内存的变量不需要由程序员释放内存（删除）。
   堆使与当前函数或堆栈帧无关的内存区域。如果想在函数调用结束仍然保存其中声明的变量，可将变量放在堆中。必须确保释放（删除）在堆上分配的任何内存，这个过程不会自动完成，除非使用智能指针。
2. 使用指针
3. 动态分配和数组
   使用 ***new[]*** 操作符可给数组分配内存
   使用完后，应使用 ***delete[]*** 操作符释放内存。
   delete 后的方括号表明删除的是一个数组。
   （应避免使用C中的 malloc() 和 free()）
4. 空指针常量
   ***nullptr*** 是 NULL 的 char* 版本。
   用 nullptr 来替代 NULL
5. 智能指针
   （详见第 7 章）
   C++有两种最重要的智能指针：***std::unique_ptr*** 和 ***std::shared_ptr***。
   使用 ***std::make_unique<>()*** 和 ***std::make_shared<>()*** 创建智能指针。
   - unique_ptr 代表的是专属所有权，即由 unique_ptr 管理的内存，只能被一个对象持有。所以，unique_ptr **不支持复制和赋值**，如下

        ~~~c++
        auto w  = std::make_unique<Widget>();
        auto w2 = w;   // 编译错误
        ~~~

        因此，unique_ptr 只支持**移动**，如下

        ~~~c++
        auto w  = std::make_unique<Widget>();
        auto w2 = std::move(w);   // w2 获得内存所有权，w 此时等于 nullptr
        ~~~

   - shared_ptr 代表的是共享所有权，即多个 shared_ptr 可以共享一块内存，因此shared_ptr 是支持复制的。如下：

        ~~~c++
        auto w = std::make_shared<Widget>();
        {
            auto w2 = w;
            cout << w.use_count() << endl;   // 2
        }
        cout << w.use_count() << endl;   // 1
        ~~~

        同时，shared_ptr 也支持移动。从语义上看，移动是所有权的传递。如下：

        ~~~c++
        auto w  = std::make_shared<Widget>();
        auto w2 = std::move(w);   // 此时 w 等于 nullptr，w2.use_count() 等于 1
        ~~~

#### 1.1.30 引用

C++ 中的引用（reference）时另一种变量的别名。对引用的所有修改都会更改其引用的变量的值。可以将引用视为隐式指针，它省去了获取变量地址和解引用指针的麻烦。另外，可以将引用视为原始变量的另一个名称。可以创建独立的引用变量，在类中使用引用数据成员，接受引用作为函数和方法的参数，并从函数和方法返回引用。

1. 引用变量

    引用变量必须在创建时被初始化，例如：

    ~~~c++
    int  x{3};
    int& xRef{x};
    ~~~

    给类型附加一个 &，则指示相应的变量是一个引用。它仍然像正常变量一样被使用，但是在幕后，它实际上是指向原始变量的指针。
    不允许在类定义外声明一个引用而不对其进行初始化。

    >**警告：**
    >引用变量必须总是在创建时被初始化。

    **修改引用**
    引用始终指向它初始化时的那个变量，引用一旦创建便无法更改。
    示例略
    >**警告：**
    >一旦将引用初始化为特定变量，就无法将引用更改为引用另一个变量。只能更改引用所指向的变量的值。

    **const 引用**
    应用于引用的 const 通常比应用于指针的 const 容易。首先，引用默认是 const，因为不能更改它们的指向。因此，不需要显式标记它们为 const。其次，无法创建对引用的引用，因此通常只有一个间接引用级别。获得多个间接级别的唯一方法是创建对指针的引用。
    因此，当 C++ 程序员提起 const 引用时，他们的意思是这样的：

    ~~~c++
    int       z;
    const int zRef{z};
    zRef = 4;   // 无法编译
    ~~~

    通过将 const 应用于 int&，可以阻止对 zRef 的赋值，如上所示。类似于指针，const int& zRef 等价于 int const& zRef，但是请注意，将 zRef 标记为 const 对 z 无效。仍然可以通过直接更改 z 的值而不是通过引用来更改 z 的值。
    不能创建对未命名值的引用，例如整数字面量，除非该引用值是 const 值。在下面的示例中，unnameRef1 会编译失败，因为它是对非 const 的引用，却指向了一个常量。那以为着可以更改常数 5 的值，这没有任何意义。unnameRef2 之所以有效，是因为它是 const 引用，因此不能编写例如 unnameRef2 = 7 这样的代码。

    ~~~c++
    int&       unnameRef1{5};   // 无法编译
    const int& unnmaeRef2{5};   // 编译通过
    ~~~

    临时对象也是如此。不能为临时对象创建一个非 const 的引用，但是 const 引用时可以的。例如，假设具有以下返回 std::string 对象的函数：

    ~~~c++
    string getString()
    {
        return "Hello World!";
    }
    ~~~

    可以为 getString() 的结果创建一个 const 引用，该引用将使临时 std::string 对象保持生命周期，直到该引用超出作用域。

    ~~~c++
    string&       string1{getString()};   // 无法编译
    const string& string2{getString()};   // 编译通过
    ~~~

    **指针的引用和引用的指针**
    可以创建对任何类型的引用，包括指针类型。这是对指向 int 的指针的引用的示例：

    ~~~c++
    int*  intP{nullptr};
    int*& ptrRef{intP};
    ptrRef  = new int;
    *ptrRef = 5;
    ~~~

    语义很简单：ptrRef 是对 intP 的引用，intP 是对 int 的指针。修改 ptrRef 会更改 intP。
    取一个引用的地址与取该引用所指向的变量的地址得到的结果使相同的。

    ~~~c++
    int  x{3};
    int& xRef{x};
    int* xPtr{&xRef};
    *xPtr = 100;
    ~~~

    最后要注意，不能声明对引用的引用或对引用的指针。例如，int&& 和 int&* 都是不允许的。

    **结构化绑定和引用**
    前面介绍过结构化绑定。给出了如下的例子：

    ~~~c++
    pair myPair{"hello", 5};
    auto [theString, theInt]{myPair};
    ~~~

    引用和 const 变量也可以与结构化绑定一起使用。示例如下：

    ~~~c++
    auto& [theString, theInt]{myPair};
    const auto& [theString, theInt]{myPair};
    ~~~

2. 引用数据成员
    类的数据成员可以是引用。如前所述，引用不能不指向其他变量而存在，并且不可以更改引用指向的变量。因此，引用数据成员不能在类构造函数的函数体内部进行初始化，必须在所谓的构造函数初始化器中进行初始化。

    >**警告：**
    >引用必须始终在创建时被初始化。通常，引用是在声明时创建的，但是引用数据成员需要在类的构造函数初始化器中初始化。

3. 引用作为函数参数
    C++程序员通常不使用独立的引用变量或引用数据成员，引用的最常见用途是用于函数的参数。默认的参数传递语义是值传递（pass-by-value）：函数接收其参数的副本。修改这些参数后，原始实参保持不变。栈中变量的指针经常在 C 语言中使用，以允许函数修改其他栈帧中的变量。通过对指针解引用，函数可以修改表示该变量的内存，即使该变量不在当前的栈帧中。这种方法的问题在于，它将指针负载的语法带入了原本简单的任务。
    相对于向函数传递指针，C++ 提供了一种更好的机制，称为引用传递（pass-by-reference），参数是引用而不是指针。以下是 addOne() 的两种实现，第一种对传入的变量没有影响，因为它是值传递的，因此该函数将接收传递给它的值的副本。第二种使用引用，因此更改了原始变量。

    ~~~c++
    void addOne(int i)
    {
        i++;
    }

    void addOne(int& i)
    {
        i++;
    }
    ~~~

    调用具有整形引用参数的 addOne() 的函数的语法与调用具有整型参数的 addOne() 函数没有区别。
    这是另一个引用派上用场的例子，这是一个简单的交换函数，用于交换两个 int 类型的值。

    ~~~c++
    void swap(int& first, int& second)
    {
        int temp{first};
        first  = second;
        second = temp;
    }
    ~~~

    当有一个指针但函数或方法只能接收引用时，就会产生一个常见的难题。在这种情况下，可以通过对指针解引用将其“转换”为引用。该操作提供了指针所指向的值，编译器随后使用该值初始化引用参数。例如，可以像这样调用 swap()：

    ~~~c++
    int  x{5}, y{6};
    int *xp{&x}, *yp{&y};
    swap(*xp, *yp);
    ~~~

    最后，如果函数需要返回一个复制成本高昂的类的对象，函数接收一个对该类的非 const 引用的输出参数，此后进行修改，而非直接返回对象。这是防止从函数返回对象时创建副本从而导致性能损失的推荐方法。
    因此，我们有以下规则：

    >警告：
    >从函数返回对象的推荐方法时通过值返回，而不是使用一个输出函数。

    **const 引用传递**
    const 引用的参数的主要目的是效率，当将值传递给函数时，便会生成一个完整副本。传递引用时，实际只是传递指向原始对象的指针，因此计算机无需生成副本。通过 const 引用传递，可以做到二者兼顾：不生成副本，并且无法改变原始变量。当处理对象时，const 引用变得更重要，因为对象可能很大。并且对其进行复制可能会产生有害的副作用。示例略。

    **值传递和引用传递**
    当要修改参数并希望那些更改能够作用于传给函数的变量时，需要通过引用传递。但是，不应将引用传递的使用局限于那些情况。引用传递避免将实参复制到函数，从而提供了两个附加好处：

    - 效率：复制大型的对象可能花费很长时间，引用传递只是将该对象的一个引用传给了函数
    - 支持：不是所有的类都允许值传递

    如果像利用这些好处，但又不想修改原始对象，则应该将参数标记为 const，从而可以传递 const 引用。

4. 引用作为返回值
    函数也可以返回引用。当然，只有在函数终止后返回的引用所指向的变量继续存在的情况下，才可以使用此方法。

    >**警告：**
    >切勿返回作用域为函数内部的局部变量的引用，例如在函数结束时将被销毁的自动分配的栈上变量。

5. 在引用与指针之间抉择
    引用使程序更简介，更易于理解。他们也比指针安全，因为没有空引用，并且不需要显式解引用，因此不会遇到与指针相关的任何解引用错误。
    大多数时候，可以使用引用而不是指针。与指向对象的指针相同，对对象的引用也支持所谓的多态性，详见第 10 章。
    但是，某些情况下需要使用指针。一种情况是需要更改其指向的位置时。第二种情况是，指针是 optional 的，即当它可以是 nullptr 时。
    应避免使用原始指针，而使用所谓的智能指针（详见第 7 章），这是转换所有权的推荐方法。
    考虑将一个整数数组分为两个数组的函数：分别存放奇数和偶数。该函数不知道源数组中的偶数或奇数个数，因此它应在检查源数组后为目标动态分配内存。它还应返回两个新数组的大小。总共有 4 项要返回：指向两个新数组的指针以及两个新数组的大小。显然，必须使用引用传递。规范的 C 的写法如下所示：

    ~~~c++
    void separateOddsAndEvens(const int arr[], size_t size, int** odds, size_t* numOdds, int** evens,
                              size_t* numEvens)
    {
        *numOdds = *numEvens = 0;
        for (size_t i = 0; i < size; ++i) {
            if (arr[i] % 2 == 1) {
                ++(*numOdds);
            }
            else {
                ++(*numEvens);
            }
        }

        *odds  = new int[*numOdds];
        *evens = new int[*numEvens];

        size_t oddPos = 0, evenPos = 0;
        for (size_t i = 0; i < size; ++i) {
            if (arr[i] % 2 == 1) {
                (*odds)[oddPos++] = arr[i];
            }
            else {
                (*evens)[evenPos++] = arr[i];
            }
        }
    }
    ~~~

    该函数的最后 4 个参数是“引用”参数。若要更改它们引用的值，separateOddAndEvens() 必须对它们解引用，这回导致函数体内的语法丑陋。此外，当调用 separateOddAndEvens() 时，必须传递两个指针的地址，以便函数可以更改实际的指针，并传递两个 size_t 的地址，以便函数可以更改实际的 size_t。还要注意，调用方要负责删除由 separateOddAndEvens() 创建的两个数组。
    使用示例略。
    可以使用引用编写相同的函数，以获得真正的引用传递语义。

    ~~~c++
    void separateOddsAndEvens(const int arr[], size_t size, int*& odds, size_t& numOdds, int*& evens,
                              size_t& numEvens)
    {
        numOdds = numEvens = 0;
        for (size_t i = 0; i < size; ++i) {
            if (arr[i] % 2 == 1) {
                ++numOdds;
            }
            else {
                ++numEvens;
            }
        }

        odds  = new int[numOdds];
        evens = new int[numEvens];

        size_t oddPos = 0, evenPos = 0;
        for (size_t i = 0; i < size; ++i) {
            if (arr[i] % 2 == 1) {
                odds[oddPos++] = arr[i];
            }
            else {
                evens[evenPos++] = arr[i];
            }
        }
    }
    ~~~

    在这种情况下，参数 odds 和 evens 是对 int\* 的引用。separateOddAndEvens() 无需解引用就可以修改函数的实参 int*（引用传递）。相同的逻辑适用于 numOdds 和 numEvens，它们是对 size_ts 的引用，使用此版本的函数，不在需要传递指针或 size_ts 的地址。引用参数会自动处理。使用示例略。
    即使使用引用参数已经不使用指针干净得多，但建议避免使用动态分配的数组。例如，使用标准库容器 vector。

    ~~~c++
    void separateOddAndEvens(const vector<int>& arr, vector<int>& odds, vector<int>& evens)
    {
        for (int i : arr) {
            if (i % 2 == 1) {
                odds.push_back(i);
            }
            else {
                evens.push_back(i);
            }
        }
    }
    ~~~

    使用示例依然略。
    使用向量的版本已经比使用指针或引用的版本好得多，但是正如之前所建议的那样，应尽可能避免使用输出参数。如果一个函数需要返回一些东西，它应该直接返回而不是使用输出参数。如果 object 是局部变量、函数参数或临时值，return object 格式的声明将会触发返回值优化（RVO）。此外，如果对象是局部变量，命名返回值优化（NRVO）将会生效。RVO 和 NRVO 都是复制省略（copy elision）的形式，使从函数中返回对象非常高效。使用复制省略功能，编译器可以避免复制从函数返回的对象，这构成零复制值传递语义。
    以下版本的 separateOddsAndEvens() 返回一个简单的包含两个 vector 的结构体，而并不是接收两个输出向量作为参数。它也使用了 C++20 的指派初始化。

    ~~~c++
    struct OddsAndEvens
    {
        vector<int> odds, evens;
    };

    OddsAndEvens separateOddAndEvens(const vector<int>& arr)
    {
        vector<int> odds, evens;
        for (int i : arr) {
            if (i % 2 == 1) {
                odds.push_back(i);
            }
            else {
                evens.push_back(i);
            }
        }
        return OddsAndEvens{.odds = odds, .evens = evens};
    }
    ~~~

    >**注意：**
    >不要使用输出参数，如果一个函数需要返回某些东西，直接按值返回即可。

#### 1.1.31 const_cast()

在 C++ 中，每个变量都有特定的类型。在某些情况下，有可能将一种类型的变量转换为另一种类型的变量。为此，C++ 提供了 5 种类型的转换：***const_cast()***、***static_cast()***、***reinter_cast()***、***dynamic_cast()*** 和 ***std::bit_cast()***（自 C++20 起）。其他类型的转换详见第 10 章。
const_cast() 可以使用它为变量添加或取消 const 属性。理论上，不需要 const 转换，如果变量是 const，应该保持 const。但在实际中，有时会遇到这样的情况：一个函数指定接收 const 参数，然后这个参数将在接收非 const 参数的函数中使用，并且可以确定后者不会修改其非 const 参数。“正确”的解决方案使使 const 在程序中一直保持，但这并不总是可行的，尤其是在使用第三方库的情况下。因此，有时需要舍弃变量的 const 属性，但是只有在确定所调用的函数不会修改该对象时，才应该这样做。否则，除了重构程序外，别无选择。这是一个例子：

~~~c++
void ThirdPartyLibraryMethod(char* str);

void f(const char* str)
{
    ThirdPartyLibraryMethod(const_cast<char*>(str));
}
~~~

此外，标准库提供了一个名为 ***std::as_const()*** 的辅助方法，该方法定义在 \<utility> 中，该方法接收一个引用参数，返回它的 const 引用版本。基本上，as_const(obj) 等价于 const_cast\<const T&>(obj)，其中 T 是 obj 的类型。与使用 const_cast() 相比，使用 as_const() 可以使代码更短，更易读。基本用法如下：

~~~c++
string str("C++");

const string& constStr{as_const(str)};
~~~

#### 1.1.32 异常

C++ 是一种非常灵活的语言，但并不是非常安全。编译器允许编写改变随机内存地址或者尝试除以 0 的代码（计算机无法处理无穷大的数值）。异常（exceptions）就是试图增加一个安全等级的语言特性。
异常伴随着一些新术语。当某段代码检测到异常时，就会抛出（throw）一个异常，另一段代码会捕获（catch）这个异常并执行恰当的操作。下例给出一个名为 divideNumbers() 的函数，如果调用者传递给分母的值为 0，就会抛出一个异常。使用 std::invalid_argument 时需要 ***\<stdexcept>***。

~~~c++
double divideNumbers(double numerator, double denominator)
{
    if (denominator == 0) {
        throw invalid_argument{"分母不能为 0。"};
    }
    return numerator / denominator;
}
~~~

当执行 throw 行时，函数将立刻结束而不会返回值。如果调用者将函数调用放到 try/catch 块中，就可以捕获异常并进行处理，如下面的代码所示。第 14 章详细介绍异常处理。注意，建议**通过 const 引用捕获异常**。还要注意，所有标准库异常类都有一个名为 ***what()*** 的方法，该方法返回一个字符串，其中包含对该异常的简要说明。

~~~c++
try {
    cout << divideNumbers(2.5, 0.5) << endl;
    cout << divideNumbers(2.3, 0) << endl;
    cout << divideNumbers(4.5, 2.5) << endl;
}
catch (const invalid_argument& exception) {
    cout << format("Exception caught: {}", exception.what()) << endl;
}
~~~

第一次调用正常返回，结果会输出给用户。第二次调用会抛出一个异常，不会返回值，第三次调用不会执行，因为第二次调用抛出了一个异常，导致程序跳转到 catch 块。

C++ 的异常非常灵活，为正确使用异常，需要理解抛出异常时栈变量的行为，必须正确捕获并处理必要的异常。另外，如果需要在异常中包含有关错误的更多信息，则可以编写自己的异常类型。最后，C++ 编译器不会强迫你捕获所有可能发生的异常。如果代码从不捕获异常但是引发了异常，则该程序将终止。详见第 14 章。

#### 1.1.35 类型推断

类型推断有两个关键字：***auto*** 和 ***decltype***

1. 关键字 auto
    auto 有多种完全不同的含义：
   - 推断函数的返回类型
   - 结构化绑定
   - 推断表达式的类型
   - 推断非类型模板参数的类型，见第 12 章
   - decltype(auto)，见第 12 章
   - 其他语法
   - 通用 lambda 表达式，见第 18 章
  始终要记住，auto **去除**了引用和 const 限定符，从而会建立**副本**，如果不需要副本，可使用 ***auto&*** 或 ***const auto&***
2. 关键字 decltype
   关键字 decltype 把表达式作为实参，计算出该表达式的类型。例如：

    ~~~c++
    int         x = 123;
    decltype(x) y = 456;
    ~~~

   auto 与 decltype 的区别在于，decltype 未去除引用和 const 限定符。

## 2 使用 string 和 string_view

### 2.1 动态字符串

#### 2.1.2 字符串字面量

代码中如 "hello world" 等是一个字符串字面量（string literal），因为这个字符串以值的形式写出，而不是变量。
字符串字面量的类型为 “n 个 const char 的数组”，所以这些变量的类型应为 ***const char\****。

- 原始字符串字面量
原始字符串字面量（raw string literal）是可横跨多行代码的字符串字面量，不需要嵌入的双引号。原始字符串字面量以 ***R"\(*** 开头，以 ***)*** 结尾。
- 宽字符字面量（wchar_t 字符串）
宽字符串支持 Unicode 字符来扩大表示范围。wchar_t 是字符类型，可容纳类 Unicode 字符，而且通常比 char（1 字节）更大。宽字符字面量要加上前缀 ***L***

#### 2.1.3 C++ std::string 类

string 类在 ***\<string>*** 头文件中定义
详细可参阅标准库参考资源和附录 B。
***c_str()*** 返回 const char*，***data()*** 返回 char*。
***to_string()*** 函数可将数值转换为字符串。

#### 2.1.4 std::string_view 类

该类在 ***\<string_view>*** 头文件中定义。string_view 基本上就是 const string& 的简单替代品，但不会产生开销。缺少 c_str() 接口，但 data() 是可以用的。
无法从 string_view 隐式构建一个 string。要么使用一个显式的 string 构造函数，要么使用 string_view::data() 成员。

- std::string_view 字面量
    可使用标准的用户定义的字面量 ***sv***，将字符串字面量解释为 std::string_view。例如：

    ~~~c++
    auto sv = "My string_view"sv;
    ~~~

    标准的用户定义的字面量 sv 需要 using namespace std::string_view_literals;或 ***using namespace std***。

## 3 编码风格

### 3.2 为代码编写文档

反正要多写注释就是了。

### 3.3 分解

分解(decomposition) 指将代码分为小段。理想状态下，每个函数或方法都应该只完成一个任务。任何非常复杂的子任务都应该分解为独立的函数或方法。

#### 3.3.1 通过重构分解

重构(refactoring) 指重新构建代码的结构。详细参考附录B 列出的重构书籍。

- 增强抽象的技术
  - 封装字段：将字段设置为私有，使用获取器和设置器方法访问它们。
  - 让类型通用：创建更通用的类型，以更好地共享代码。
- 分割代码以使其更合理的技术
  - 提取方法：将大方法的一部分转换为便于理解的新方法
  - 提取类：将现有类的部分代码转移到新类中。
- 增强代码名称和位置的技巧
  - 移动方法或字段：移动到更合适的类或源文件中
  - 重命名方法或字段：改为更能体现其作用的名称
  - 上移(pull up)：在 OOP 中，移到基类中。
  - 下移(push down)：在 OOp 中，移到派生类中。

重构代码时，必须依靠测试框架来捕获可能引入的缺陷。详见第 26 章。

#### 3.3.2 通过设计来分解

如果使用模块分解，可将以后编写的部分代码放在模块、方法或函数中。
仍然建议在编写代码之前设计程序。

### 3.4 命名

编译器有几个命名规则：

- 名称不能以数字开头。
- 包含两个下划线的名称（例如 my__name）是保留名称，不应当使用。
- 以下划线开头的名称（例如 _Name）是保留名称，不应当使用。

#### 3.4.1 选择恰当的名称

一些适当和不当的名称

| 适当的名称                           | 不当的名称                                    |
| ------------------------------------ | --------------------------------------------- |
| sourceName、destination 区别两个对象 | thing1、thing2 太笼统                         |
| gSettings 表明全局身份               | globalUserSpecificSettingsAndPreferences 太长 |
| mNameCounter 表明了数据成员身份      | mNC 太简单，太模糊                            |
| calculateMarigoldOffset() 简单，明确 | doAction() 太宽泛，不准确                     |
| mTypeString 赏心悦目                 | typeSTR256 只有计算机才会喜欢的名称           |
| mWelshRarebit 好的内部玩笑           | mIHateLarry 不恰当的内部玩笑                  |
| errorMEssage 描述性名称              | String 非描述性名称                           |
| sourceFile、destinationFile 无缩写   | srcFile、dstFile 缩写                         |

#### 3.4.2 命名约定

1. 计数器
    编程时，经常把变量 “i” 和 “j” 用作计数器，使用二维数据时，将 row 和 column 用作索引会更容易。有些人也喜欢使用 outerLoopIndex 和 innerLoopIndex 等计数器。
2. 前缀
    一些可用的前缀

    | 前缀     | 实例名称                                  | 前缀的字面意思             | 用法               |
    | -------- | ----------------------------------------- | -------------------------- | ------------------ |
    | m m_     | mData m_data                              | 成员”                      | 类的数据成员       |
    | s ms ms_ | sLookupTable msLookupTable ms_lookupTable | “静态”                     | 静态变量或数据成员 |
    | k        | kMaximumLength                            | “konstant”，德语表示的常量 | 常量值             |
    | b is     | bCompleted isCompleted                    | “布尔值”                   | 表示布尔值         |
    | n mNum   | nLines mNumLines                          | “数字”                     | 数据成员也是计数器 |

3. 匈牙利表示法
4. 获取器和设置器
    如果类中包含数据成员，例如 mStatus，习惯上会通过获取器 getStatus() 和设置器 setStatus() 访问这个成员。要访问布尔数据成员，通常将 is 用作前缀，例如 isRunning()。
5. 大写
    在 C++ 中，函数和方法通常将首字母大写（看个人喜好）。大写字母可用于为类和数据成员名指明单词的边界。
6. 把常量放在名称空间中
    建议将常量放到不同的名称空间中。另一个更好的方法是使用枚举器。

## 6 设计可重用代码

### 6.1 重用哲学

- 编写一次，经常使用
- 尽量避免代码重复
- DRY（Don't Repeat Yourself，不要重写自己写过的代码）

### 6.2 如何设计可重用代码

可重用代码有两个主要目标。首先，代码必须**通用**，可用于稍有不同的目的或不同的应有程序域。涉及特定应用程序细节的组件很难被其他程序重用。
其次，可重用代码还应该**易于使用**，不需要花费大量时间去理解它们的接口或功能。
将**库**“递交”给客户的方法也很重要。可以源代码形式递交，这样客户只需要将源代码整合到他们的项目中。另一种选择时递交一个静态库，客户将该库连接到他们的应用程序；也可以给 Windows 客户递交一个动态链接库（***DLL***），给 Linux 客户递交一个共享对象（***.so***）。这些递交方式会对编写库的方式施加额外限制。
对于设计可重用代码而言，最重要的策略是**抽象**。当设计代码时，应该将**接口**和**实现**明确分离。这种分离使代码容易使用，主要是因为客户使用功能时，不需要理解内部实现细节。
抽象将代码分为接口和实现。首先，应该恰当的设计代码结构。使用什么样的类层次结构？应该使用模板吗？如何将代码分割为子系统？其次，必须设计接口，这是库或代码的“入口”，程序员用这个入口访问程序提供的功能。

#### 6.2.1 使用抽象

接口和实现的明确分离可杜绝用户以不希望的方式使用库，而这些方式可能导致意想不到的行为和bug。
**当设计界面时，不要向客户公开实现细节。**
有时为将某个接口返回的信息传递给其他接口，库要求客户代码保存这些信息。这一信息有时叫做**句柄**(***handle***)，经常用来跟踪某些特定的实例，这些实例调用时的状态需要被记住。如果库的设计需要句柄，不要公开句柄的内部情况。可将句柄放入某个**不透明类**，程序员不能“直接访问这个类的内部数据成员，也不能通过公有的获取器或设置器来访问”。
不要要求客户代码改变句柄内部的变量。
抽象非常重要，应该贯穿于整个设计。在左除任何决定时，都应该确保满足抽象原则。将自己摆在客户的位置，判断是否需要接口的内部实现知识。这样将很少（甚至永远不）违背这个原则。

#### 6.2.2 构建理想的重用代码

在开始设计时就应该考虑重用，在所有的级别上都需要考虑，从单个函数、类乃至整个库或框架。在下文中，所有这些不同的级别称为**组件**。下面的策略有助于恰当的组织代码，注意所有这些策略都关注代码的**通用性**。设计可重用代码的另一方面是提供**易用性**。

1. 避免组合不相干的概念或者逻辑上独立的概念
当设计组件时，应该关注单个任务或一组任务，即“高聚合”，也称为 SRP(Single Responsibility Principle,单一责任原则)。不要把无关概念组合在一起。
即使设计的代码并不是专门用来重用的，也应该记住这一策略。整个程序本身很少会被重用，但是程序的片段或子系统可直接组合到其他用用程序中，也可以稍作变动后用于大致相同的环境。因此，设计程序时，应将逻辑独立的功能放到不同的组件中，以便在其他程序中使用。其中的每个组件都应当有明确定义。
   - 将程序分为逻辑子系统
    将子系统设计为可单独重用的分离组件，即“**低耦合**”。例如，如果设计一款网络游戏，应该将网络和图形用户界面放在独立的子系统中，这样就可以重用一个组件，而不会涉及另一个组件。
   - 用类层次结构分离逻辑概念
    除了将程序分为逻辑子系统以外，在类级别上应该避免将无关概念组合在一起。（详细说明去看书）。
    与类级别一样，还应该避免在任何设计级别组合不相关的概念，也就是说，要追求“高聚合”。例如，在方法级别，一个方法不应该执行逻辑上无关的事项，不应当混合突变（设置）和审查（获取）等。
   - 用聚合分离逻辑概念
    第 5 章讨论了聚合。为完成特定功能，对象会包含其他对象。当不适合使用继承方法时，可以使用聚合分离没有关系的功能或者有关系但独立的功能。
    （详细去看书）
   - 消除用户界面的依赖性
    去看第 4 章。
2. 对泛型数据结构和算法使用模板
    （去看书）
3. 提供恰当的检测和安全措施
    （书书书）
4. 扩展性
    （书书书书）

## 7 内存管理

### 7.1 使用动态内存

#### 7.1.2 分配与释放

1. 使用 new 和 delete
    要分配一块内存，可调用 new，并提供需要空间的变量的类型。new 返回指向那个内存的指针，如果忽略了 new 的返回值，或这个指针变量离开了作用域，那么这块内存就被孤立了，因为无法再访问这块内存。这也成为**内存泄露**。
    建议在释放指针的内存后，将指针重新设置为 nullptr。这样就不会在无意中使用一个指向已释放内存的指针。
2. 关于 malloc() 函数
    new 相比 malloc() 的主要好处在于，new 不仅分配内存，还构建对象（调用相应的构造函数）。
    类似的差异存在于 free() 函数和 delete 运算符之间。使用 free() 时，不会调用对象的析构函数。使用 delete 时，将调用析构函数来恰当的清理对象。
    在 C++ 中不应该使用 malloc() 和 free() 函数。只使用 new 和 delete 运算符。
3. 当内存分配失败时
   （去看第 14 章）

#### 7.1.3 数组

数组将多个同一类型的变量封装在一个索引访问的变量中。

1. 基本类型的数组
    在堆栈上分配 5 个 int 型数字的局部数组的声明如下所示：

    ~~~c++
    int myArray[5];
    ~~~

    在堆栈上声明数组时，数组的大小必须是编译时一直的常量值。
    在堆上声明数组没有什么不同，只是需要通过一个指针引用数组的位置。代码如下所示：

    ~~~c++
    int* myArrayPtr = new int[5];
    ~~~

    对 new[] 的每次调用都应与 delete[] 调用配对，以清理内存。例如：

    ~~~c++
    delete[] myArrayPtr;
    myArrayPtr = nullptr;
    ~~~

    把数组放在堆中的好处在于可在运行时通过动态内存指定数组的大小。但是不能把它和动态数组混为一谈。数组本身不是动态的，因为一旦被分配，数组的大小就不会改变。动态内存允许在运行时指定分配的内存块的大小，但它不会自动调整其大小以容纳数据。
    不要在 C++ 中使用 ***realloc()***。这个函数很危险。

2. 对象的数组
    略。
3. 删除数组
    通过数组版本的 new(new[]) 分配内存时，必须通过数组版本的 delete(delete[]) 释放相应的内存。
4. 多维数组
    - 多维堆栈数组
    - 多维堆数组
    下面的函数正确的分配了二维数组的内存：

    ~~~c++
    char** allocateCharacterBoard(size_t xDimension, size_t yDimension)
    {
        char** myArray = new char*[xDimension];
        for (size_t i = 0; i < xDimension; i++) {
            myArray[i] = new char[yDimension];
        }
        return myArray;
    }
    ~~~

    释放数组的代码如下：

    ~~~c++
    void releaseCharacterBoard(char** myArray, size_t xDimension)
    {
        for (size_t i = 0; i < xDimension; i++) {
            delete[] myArray[i];
        }
        delete[] myArray;
    }
    ~~~

    综上所述，不要使用旧式的 C 风格数组，应该用 C++标准库容器，例如 std::array、std::vector 等。

#### 7.3.1 指针运算

如果声明一个指向 int 的指针，然后将这个指针递增 1，那么这个指针在内存中向前移动 1 个 int 的大小，而不是 1 个字节。此类操作对数组最有用。
指针运算的另一个有用应用是减法运算。将一个指针减去另一个同类型的指针，得到的是两个指针之间指针指向的类型的元素个数，而不是两个指针之间字节数的绝对值。

### 7.4 智能指针

智能指针可帮助管理动态分配的内存，这是避免内存泄漏建议采用的技术。
应将 unique_ptr 用作默认智能指针。仅当真正需要共享资源时，才使用 shared_ptr。
永远不要将资源分配结果指定给普通指针。无论使用哪种资源分配方法，都应当立即将资源指针存储在智能指针 unique_ptr 或 shared_ptr 中，或其他 RAII 类（资源获取即初始化）。

#### 7.4.1 unique_ptr

1. 创建 unique_ptrs
    作为经验总结，总是将动态分配的对象保存在堆栈的 unique_ptr 实例中。
    创建 unique_ptr 有两种方式，例如：

    ~~~c++
    auto               mySimplePtr = make_unique<Simple>();
    unique_ptr<Simple> mySimpleSmartPtr(new Simple());
    ~~~

    建议使用 ***make_unique()***，这样代码更便于读取。
2. 使用 unique_ptrs
    这个标准智能指针最大的一个亮点是：用户不需要学习大量的新语法，就可以获得巨大好处。像标准指针一样，仍可以使用 \* 或 -> 对智能指针进行解引用。
    ***get()*** 方法可用于直接访问底层指针。这可将指针传递给需要普通指针的函数。
    ***reset()*** 可释放 unique_ptr 的底层指针，并可根据需要将其改成另一个指针。
    ***release()*** 可断开 unique_ptr 与底层指针的连接。release() 方法返回资源的底层指针，然后将智能指针设置为 nullptr。
    由于 unique_ptr 代表唯一拥有权，因此无法复制它。使用 ***std::move()*** 实用工具（见第 9 章），可使用移动语义将一个 unique_ptr 移到另一个。这用于显式移动所有权,如下所示：

    ~~~c++
    class Foo
    {
    public:
        Foo(unique_ptr<int> data)
            : mData(move(data))
        {}

    private:
        unique_ptr<int> mData;
    };

    void demo()
    {
        auto myIntSmartPtr = make_unique<int>(42);
        Foo  f(move(myIntSmartPtr));
    }
    ~~~

3. unique_ptr 和 C 风格数组
    unique_ptr 适用于存储动态分配的旧式 C 风格数组。如下例：

    ~~~c++
    auto myvariableSizedArray = make_unique<int[]>(10);
    ~~~

    即便如此，也建议使用标准容器库。
4. 自定义 deleter
    如下：

    ~~~c++
    int* malloc_int(int value)
    {
        int* p = (int*)malloc(sizeof(int));
        *p     = value;
        return p;
    }

    unique_ptr<int, decltype(free)*> myIntSmartPtr(malloc_int(42), free);
    ~~~

这段代码使用 malloc_int() 给整数分配内存，unique_ptr 调用标准的 free() 函数来释放内存。慢慢理解吧。

#### 7.4.2 shared_ptr

shared_ptr 的用法与 unique_ptr 类似。
**总是**使用 ***make_shared()*** 来创建 shared_ptr。
与 unique_ptr 一样， shared_ptr 也支持 get() 和 reset() 方法，唯一区别是，当调用 reset() 时，由于引用计数，仅在最后的 shared_ptr 销毁或重置时，才释放底层资源。注意，shared_ptr 不支持 release()。可使用 ***use_count()*** 来检索共享同一资源的 shared_ptr 实例数量。
shared_ptr 自定义 deleter 方法如下：

~~~c++
shared_ptr<int> myIntSmartPtr(malloc_int(42), free);
~~~

不必将自定义 deleter 的类型指定为模板类型参数，这比 unique_ptr 的自定义 deleter 更简便。

1. 强制转换 shared_ptr
    可用于强制转换 shared_ptrs 的函数是 const_pointer_cast()、dynamic_pointer_cast() 和 static_pointer_cast()。C++17 后又添加了 reinterpret_pointer_cast()，详见第 11 章。
2. 引用计数的必要性
    略。
    即使有两个指向同一个对象的 shared_Ptr，对象也只销毁一次。
3. **别名**
    shared_ptr 支持所谓的别名。即允许一个 shared_ptr 与另一个 shared_ptr 共享一个指针（拥有的指针），但指向不同的对象（存储的指针）。例如，这可用于使用一个 shared_ptr 指向一个对象的成员，同时拥有该对象本身。例如：

    ~~~c++
    class Foo
    {
    public:
        Foo(int value)
            : mData(value)
        {}
        int mData;
    };

    auto foo      = make_shared<Foo>(42);
    auto aliasing = shared_ptr<int>(foo, &foo->mData);
    ~~~

    当两个 shared_ptr(foo 和 aliasing) 都销毁时，才销毁 Foo 对象。
    “拥有的指针”用于引用计数；当对指针解引用或调用它的 get()时，将返回“存储的指针”。

#### 7.4.3 weak_ptr

weak_ptr 类与 shared_ptr 模板有关。weak_ptr 可包含由 shared_ptr 管理的资源的引用。 weak_ptr 不拥有这个资源，所以不能阻止 shared_ptr 释放资源。weak_ptr 销毁时（例如离开作用域）不会销毁它指向的资源；然而，它可用于判断资源是否已经被关联的shared_ptr  释放了。weak_ptr 的构造函数要求将另一个 shared_ptr 或另一个 weak_ptr 作为参数。为了访问 weak_ptr 中保存的指针，需要将 weak_ptr 转换为 shared_ptr。这有两个方法：

- 使用 weak_ptr 实例的 ***lock()*** 方法。这个方法返回一个 shared_ptr。如果同时释放了与 weak_ptr 关联的 shared_ptr，返回的 shared_ptr 使 nullptr。
- 创建一个新的 shared_ptr 实例，将 weak_ptr 作为 shared_ptr 构造函数的参数。如果释放了与 weak_ptr 关联的 shared_ptr，将抛出 std::bad_weak_ptr 异常。

#### 7.4.4 移动语义

详见第 9 章。

#### 7.4.5 enable_shared_from_this

std::enable_shared_from_this 混入类允许对象上的方法给自身安全的返回 shared_ptr 或 weak_ptr。（混入类详见第 28 章）
enable_shared_form_this 混入类给类添加了以下两个方法：

- ***shared_from_this***：返回一个 shared_ptr，它共享对象的所有权。
- ***weak_from_this***：返回一个 weak_ptr，它跟踪对象的所有权。

这是一项高级功能，以下是简单演示：

~~~c++
class Foo : public enable_shared_from_this<Foo>
{
public:
    shared_ptr<Foo> getPointer() { return shared_from_this(); }
};

int main()
{
    auto ptr1 = make_shared<Foo>();
    auto ptr2 = ptr1->getPointer();
}
~~~

注意，仅当对象的指针已经存储在 shared_ptr 时，才能使用对象上的 shared_from_this()。下面的实现是完全错误的：

~~~c++
class Foo : public enable_shared_from_this<Foo>
{
public:
    shared_ptr<Foo> getPointer() { return shared_ptr<Foo>(this); }
};
~~~

如果像前面那样为 main() 使用相同的代码，该实现将会导致双重删除。

### 7.5 常见的内存陷阱

每个内存泄漏或错误指针都有微妙的差别，没有解决所有内存问题的灵丹妙药，但有一些常见类型的问题是可以检测和解决的。

#### 7.5.1 分配不足的字符串

与 C 风格字符串相关的最常见问题是分配不足。
有三种方法用于解决可能的分配不足问题。按照优先级降序排列，这三种方法为：

1. 使用 C++ 风格的字符串，它可自动处理与连接字符串关联的内存。
2. 不要将缓冲区分配为全局变量或分配在堆栈上，而是分配在堆上。当剩余内存空间不足时，分配一个新缓冲区，它大到至少能保存当前内容加上新内存块的内容，将原来缓冲区的内容复制到新缓冲区，将新内容追加到后面，然后删除原来的缓冲区。

#### 7.5.2 访问内存越界

指针只不过是一个内存地址，因此指针可能指向内存中的任何一个位置。例如，考虑一个 C 风格的字符串，它不小心丢失了 '\0' 终止字符。一个函数视图将字符串填满字符，但实际上可能会继续在字符串后面填充。
写入数组尾部后面的内存产生的 bug 称为缓冲区溢出错误。使用像 C++ string 和 vector 这样的高级结构有助于避免产生一些和 C 风格字符串和数组相关的 bug。

#### 7.5.3 内存泄漏

通过智能指针避免内存泄露是解决这个问题的首选方法。

1. 通过 Visual C++ 在 Windows 中查找和修复内存泄漏
2. 在 Linux 中通过 ***Valgrind*** 查找并修复修复内存泄漏
    太复杂啦暂略。

#### 7.5.4 双重删除和无效指针

通过 delete 释放某个指针关联的内存时，这个内存就可以由程序的其他部分使用了。然而，无法禁止再次使用这个指针，这个指针成为悬挂指针。双重删除也是一个问题。如果第二次在同一个指针上执行 delete 操作，程序可能会释放重新分配给另一个对象的内存。
如果不按推荐的方式使用智能指针而是使用普通指针，至少在释放指针关联的内存后，将指针设置为 nullptr。这样能防止不小心两次删除同一个指针个使用无效的指针。注意，在 nullptr 指针上调用 delete 是**允许**的，只是这样没有任何效果。

## 8 熟悉类和对象

### 8.2 编写类

#### 8.2.1 类定义

1. 类的成员
    类可有许多成员。成员可以是成员函数（方法、构造函数或析构函数），也可以是成员变量（也成为数据成员）、成员枚举、类型别名和嵌套类等。
2. 访问控制
    类中的每个方法和成员都可用三种访问说明符之一来说明：***public***、***protected*** 或 ***private***。访问说明符将应用于其后声明的所有成员，直到遇到另一个访问说明符。
    类的默认访问说明符是 private：在第一个访问说明符之前声明的所有成员的访问都是私有的。
    与类类似，C++ 中的结构体（struct）也可以拥有方法。实际上，唯一的区别就是结构的默认访问说明符是 public。
    如果只需要一组可供公共访问的数据成员，没有方法或方法数量很少，习惯上用 struct 替代 class。
    以下总结了这三种访问说明符的含义
    - public：任何代码都可调用对象的 public 成员函数或者访问 public 数据成员
        想让客户使用的行为（方法），访问 private 和 protected 数据成员的方法
    - protected：类的任意成员函数都可调用 protected 成员函数或者访问    protected 数据成员。派生类的成员函数可访问基类的 protected 成员
        不想让客户使用的“帮助”方法
    - private：只有这个类的成员函数可调用 private 成员函数并访问 private 数据成员。派生类的成员函数不能访问基类的 private 成员。
        **所有对象都应默认为 private**，尤其是数据成员。如果只允许派生类访问它们，就可以提供受保护的获取器和设置器，如果希望客户能访问它们，就可以提供公有的获取器和设置器。
3. 声明顺序
    可使用任何顺序声明成员和访问控制符。当然，为清晰起见，最好将 public、protected 和 private 声明分组，并在这些声明内将成员函数和数据成员分组。
4. 类内成员初始化器
    可直接在类定义中初始化成员变量。

#### 8.2.2 定义方法

与编写独立函数的原型和定义类似，必须编写方法的原型和定义。注意，类定义必须在方法定义之前。通常类定义在头文件中，方法定义在包含头文件的源文件中。
定义方法时，在方法名前都出现了类名和两个冒号：
***::*** 称为域解析运算符。再此环境中，这个语法告诉编译器，要定义的方法是哪个类的一部分。此外还要注意，定义方法时，不要重复使用访问说明符。

1. 访问数据成员
    略，就是用 set 和 get 方法。
2. 调用其他方法
    略，就是用函数重载
3. this 指针
    略，懂得都懂。

#### 8.2.3 使用对象

1. 堆栈中的对象
    略。
2. 堆中的对象
    略。

### 8.3 对象的生命周期

#### 8.3.1 创建对象

1. 编写构造函数
    构造函数**没有返回类型**，可以有也可以没有参数，没有参数的构造函数称为默认构造函数。许多情况下，必须提供默认构造函数。
2. 使用构造函数
    构造函数用来创建对象并初始化其值。在基于堆栈和堆分配时可以使用构造函数。
    略啦。
3. 提供多个构造函数
    再略。
4. 默认构造函数
    如果没有指定任何构造函数，编译器将自动生成无参构造函数。然而，如果声明了默认构造函数或其他构造函数，编译器就不会再自动生成默认构造函数。
    - 显式的默认构造函数
        在 C++03 或更早版本中，如果类需要一些接受参数的显式构造函数，还需要一个什么都不做的默认构造函数。
        为了避免手动编写空的默认构造函数，可按如下方法编写类的定义：

        ~~~c++
        class SpreadsheetCell
        {
        public:
            SpreadsheetCell() = default;
            SpreadsheetCell(double initialValue);
            SpreadsheetCell(std::string_view initialValue);
        };
        ~~~

    - 显式删除构造函数
        如果一个类只有静态方法，没有任何构造函数，也不想让编译器生成默认构造函数。在此情况下可以显式删除默认构造函数：

        ~~~c++
        class MyClass
        {
        public:
            MyClass() = delete;
        };
        ~~~

5. 构造函数初始化器
    C++ 提供了另一种在构造函数中初始化数据成员的方法，叫做构造函数初始化器或 ctor-initializer。如下例：

    ~~~c++
    SpreadsheetCell::SpreadsheetCell(double initialValue)
        : mValue(initialValue)
    {}
    ~~~

    这个列表出现在构造函数参数列表和构造函数体的左大括号之间，以冒号开始，由逗号间隔。列表中的每个元素都使用函数符号、统一的初始化语法、调用基类构造函数，或者委托构造函数以初始化某个数据成员。
    这个方法是在创建数据成员时，为其调用构造函数。这样做效率比在后面赋值高。
    如果类的数据成员是具有默认构造函数的类的对象，则不必在 ctor-initializer 中显式初始化对象。
    而如果类的数据成员是没有默认构造函数的类的对象，则必须在 ctor-initializer 中显式初始化对象。
    某些数据成员必须在 ctor-initializer 中或使用类内初始化器进行初始化。

    | 数据类型                       | 说明                                                                           |
    | ------------------------------ | ------------------------------------------------------------------------------ |
    | const 数据成员                 | const 变量创建后无法对其正确赋值，必须在创建时提供值                           |
    | 没有默认构造函数的对象数据成员 | C++ 尝试用默认构造函数初始化成员对象。如果不存在默认构造函数，就无法初始化它们 |
    | 没有默认构造函数的基类         | 见第 10 章                                                                     |

    使用 ctor-initializer  初始化数据成员的顺序如下：**按照类定义中声明的顺序**。

6. 复制构造函数
    复制构造函数，允许所创建的对象是另一个对象的精确副本。如果没有编写复制构造函数，C++ 会自动生成一个，用源对象中相应数据成员的值初始化新对象的每个数据成员。如果数据成员是对象，初始化意味着调用它们的复制构造函数。
    复制构造函数采用源对象的 **const 引用**作为参数
    多数情况下，不需要亲自编写复制构造函数。
    可将复制构造函数定义为显式默认或显式删除
    通过删除复制构造函数，将不再复制对象。这可用于禁止按值传递对象。

7. 初始化列表构造函数
    初始化列表构造函数（initializer-list constructors）将 std::initializer_list\<T> 作为第一个参数，并且没有任何其他参数（或者其他参数具有默认值）。在使用 std::initializer+list\<T> 模板之前，必须包含 \<initializer> 头文件。
    示例如下：

    ~~~c++
    #include <initializer_list>
    #include <stdexcept>
    #include <vector>
    #include <iostream>

    using namespace std;

    class EvenSequence
    {
    public:
        EvenSequence(initializer_list<double> args)
        {
            if (args.size() % 2 != 0) {
                throw invalid_argument("initializer_list should"
                                       "contain even number of elements.");
            }
            mSequence.reserve(args.size());
            for (const auto& value : args) {
                mSequence.push_back(value);
            }
        }

        void dump() const
        {
            for (const auto& value : mSequence) {
                cout << value << ", ";
            }
            cout << endl;
        }
    private:
        vector<double> mSequence;
    };
    ~~~

8. 委托构造函数
    委托构造函数（delegating constructors）允许构造函数调用同一个类的其他构造函数。然而，这个调用不能放在构造函数体内，而必须放在构造函数初始化器中，且必须是列表中唯一的成员初始化器。
    示例如下：

    ~~~c++
    SpreadsheetCell::SpreadsheetCell(string_view initialValue)
        : SpreadsheetCell(stringToDouble(initialValue))
    {}
    ~~~

    当使用委托构造函数时，要注意避免出现构造函数的递归。

9. 总结编译器生成的构造函数
    略。
    注意默认构造函数和复制构造函数之间缺乏对称性。只要没有显式定义复制构造函数，编译器就会自动生成一个。另一方面，只要定义了任何构造函数，编译器就不会生成默认构造函数。
    可通过将构造函数定义为显式默认或显式删除来影响自动生成的默认构造函数和默认复制函数。
    构造函数的最后一种类型是**移动构造函数**，用于实现移动语义。详见第 9 章。

#### 8.3.2 销毁对象

当销毁对象时，会发生两件事：调用对象的析构函数，释放对象占用的内存。

#### 8.3.3 对象赋值

在 C++ 中，“复制”只在初始化对象时发生。如果一个已经具有值的对象被改写，更精确的术语是“赋值”。
因此，C++ 为所有的额类提供了执行赋值的方法，这个方法叫做**赋值运算符（assignment operator）**，名称是 operator=，因为实际上是为类重载了=运算符。
注意区分复制赋值运算符和**移动赋值运算符**。

1. 声明赋值运算符
    示例：

    ~~~c++
    class SpreadsheetCell
    {
    public:
        SpreadsheetCell& operator=(const SpreadsheetCell& rhs);
    };
    ~~~

    赋值运算符与复制构造函数类似，采用了源对象的 **const 引用**。在此情况下，将源对象称为 ***rhs***，代表等号的“右边”（随便都好啦），调用赋值运算符的对象在等号的左边。
    与复制构造函数不同的是，复制运算符返回对象的**引用**。原因是赋值可以链接在一起，如下所示：

    ~~~c++
    myCell = anotherCell = aThirdCell;
    ~~~

    实际上可让赋值运算符返回任意类型，包括 void，然而应该返回调用对象的引用，因为客户希望这样。

2. 定义赋值运算符
    在 C++ 中允许将对象的值赋给自身。当唯一数据成员是基本类型时，这并不重要。但当类具有动态分配的内存或其他资源时，必须将自赋值考虑在内。为阻止此类问题发生，赋值运算符通常在方法开始时检测自赋值，如果发现自赋值，则立即返回。

    ~~~c++
    SpreadsheetCell& SpreadsheetCell::operator=(const SpreadsheetCell& rhs)
    {
        if (this == &rhs) {
            return *this;
        }
    }
    ~~~

    this 指针指向执行方法的对象，因此 *this 就是对象本身。编译器将返回一个对象的引用，从而与声明的返回值匹配。如果不是自赋值，就必须对每个成员赋值，最后返回 \*this。

3. 显式地默认或删除赋值运算符
    略。

#### 8.3.5 复制和赋值的区别

略。

## 9 精通类与对象

### 9.1 友元

C++ 允许某个类将其他类、其他类的成员函数或非成员函数声明为**友元（friend）**，友元可以访问类的 protected、private 数据成员和方法。
示例略。
注意类需要知道其他哪些类、方法或函数希望成为友元；类、方法或函数不能将自身声明为其他类的友元并访问这些类的非公有名称。
friend 类和方法很容易被滥用；友元可以违反封装的原则，将类的内部暴露给其他类或函数。因此，只有在特定的情况下才应该使用它们。

### 9.2 对象中的动态内存分配

#### 9.2.2 使用析构函数释放内存

析构函数与类（和构造函数）同名，名称的前面有一个**波浪号（~）**。析构函数没有参数，并且只能有一个析构函数。析构函数永远不应抛出异常。
析构函数释放在构造函数中分配的内存。

#### 9.2.3 处理复制和赋值

拷贝构造函数和赋值构造函数中必须进行深层复制。也就是说，它们不能只复制指针数据成员，必须复制指针所指向的实际数据。
无论什么时候，在类中动态分配内存后，都应该**编写自己的拷贝构造函数和赋值运算符**，以提供深层的内存复制。
需要一种全有或全无的机制：要么全部成功，要么该对象保持不变。为实现这个能安全处理异常的运算符，要使用 **“复制和交换”惯用方法**，可以给对象添加一个 ***swap()*** 方法，还需要一个非成员函数的 swap() 版本。在 \<utility> 中的 std::swap() 提供。
示例如下：

~~~c++
Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
    Spreadsheet temp{rhs};
    swap(temp);
    return *this;
}
~~~

“复制和交换”的惯用方法：

- 第一阶段**创建一个临时副本**。这不修改对象的状态，因此，如果在这个阶段发生异常，不会出现问题。
- 第二阶段使用***swap()*** 函数，将创建的临时副本与当前对象交换。swap() **永远不会抛出异常**。
- 第三阶段销毁临时对象以清理内存。

如果不使用“复制和交换”惯用方法，那么就使用上面赋值的检查。

#### 9.2.4 使用移动语义处理移动

对象的移动语义需要实现移动构造函数和移动复制运算符。移动将内存和其他资源的所有权从一个对象移动到另一个对象。

1. 右值引用
    在 C++ 中，左值（lvalue）是可获取其地址的一个量，经常出现在赋值语句的左边。
    右值引用是一个对右值（rvalue）的引用。这是一个当右值是临时对象或使用 ***std::move()*** 显式移动时才适用的概念。
    函数可将 ***&&*** 作为参数说明的一部分（例如 type&& name），以指定右值引用参数。
    可使用 std::move() 强迫编译器调用方法的右值引用版本。move() 做的唯一的事就是将左值转换为右值，也就是说，它不做任何实际的移动。
2. 实现移动语义
    移动语义是通过右值引用实现的。为了对类增加移动语义，需要实现移动构造函数和移动赋值运算符，同时需要使用 **noexcept 限定符**标记。因为如果实现了移动语义，标准库容器会移动存储的对象，且确保不抛出异常。
    示例略。
    移动语义都将动态分配的内存所有权从源对象移动到新对象，将源对象的成员指针设置为空指针，以防源对象的析构函数释放这块内存。
    在移动实现中可包含一个自我赋值检查。
    定义在 \<utility> 中的 ***std::exchange()***，可以用一个新的值替代原来的值，并返回原来的值。

   - 使用 std::exchange
    在实现移动赋值运算符时，exchange() 十分有用。可以让代码更简介，如下：

        ~~~c++
        void Spreadsheet::moveFrom(Spreadsheet& src) noexcept
        {
            m_name   = exchange(src.m_width, 0);
            m_height = exchange(src.m_height, 0);
            m_cells  = exchange(src.m_cells, nullptr);
        }
        ~~~

   - 用交换方式实现移动构造函数和移动赋值运算符
    略。

3. 测试移动操作
    略。
4. 使用移动语义实现交换函数
    略，但需要记住。
5. 在返回语句中使用 std::move()
    当从函数中返回一个局部变量或参数时，只要写 return object; 就可以了，不要使用 std::move()。
6. 向函数传递参数的最佳方法
    为左值和右值优化方法总需要实现两个重载。而最好的办法是，**始终使用 const 引用参数来传递对象**，以避免任何不必要的复制。但是，书里还是建议使用**值传递**。随便啦。。。
    对于函数本身将复制的参数，更倾向于值传递，但**仅当该参数属于支持移动语义的类型**时。否则，请使用 const引用参数。

### 9.3 与方法有关的更多内容

#### 9.3.1 static 方法

与数据成员类似，方法有时会应用于全部类对象而不是单个对象。可以编写 static 和数据成员。一个类中如果方法没有访问特定对象的信息，可以将这个方法设置为 ***static***，示例略。
注意 static 方法不属于特定对象，因此**没有 this 指针**。当用某个特定对象调用 static 方法时，static 方法不会访问这个对象的非 static 数据成员。实际上，static 方法就像普通函数，区别在于它可以访问类的 private 和 protected 的 static 成员。如果同一类型的其他对象对于 static 方法可见（例如**传递了对象的指针或引用**作为参数），那么 static 方法也可以访问其他对象的 private 和 protected 的非 static 数据成员。

#### 9.3.2 const方法

const 对象的值不能改变。如果使用 const 对象、const 对象的引用和指向 const 对象的指针，编译器将不允许调用对象的任何方法，除非这些方法保证不改变任何数据成员。为了保证方法不改变数据成员，可以用 ***const*** 关键字标记方法本身。
const 的工作原理时将方法内用到的数据成员都标记为 const 引用，因此如果试图修改数据成员，编译器会报错。
**不能将 static 方法声明为 const**，因为这是多余的。静态方法没有类的实例，因此不可能改变内部的值。
非 const 对象可调用 const 方法和非 const 方法。然而，**const 对象只能调用 const 方法**。
应该养成习惯，**将不修改对象的所有方法声明为 const**，这样就可在程序中使用 const 对象的引用。注意 const 对象也会被销毁，它们的析构函数也会被调用，因此不应该将析构函数标记为 const。

**mutable 数据成员**：
有时编写的方法“逻辑上”时 const 方法，但是碰巧改变了对象的数据成员。这个改动对于用户可见的数据没有任何影响，但严格来说确实做了改动，因此编译器不允许将这个方法声明为 const。
解决方法是将类中的这个会被修改的变量设置为 ***mutable***，告诉编译器在 const()方法中允许改变这个值。示例如下：

~~~c++
class SpreadsheetCell
{
private:
    double         m_value{0};
    mutable size_t m_numAccess{0};
};
~~~

#### 9.3.3 方法重载

介绍略。

1. 基于 const 的重载
    可根据 const 重载方法。也就是说，可以编写两个名称相同、参数也相同的方法，其中一个是 const，另一个不是。如果是 const 对象，就调用 const 方法；如果是非 const 对象，就调用非 const 方法。
    通常情况下，const 版本和非 const 版本的实现是一样的。为避免代码重复，可使用 Scott Meyer 的 const_cast 模式。例如，Spreadsheet 类有一个 getCellAt() 方法，该方法返回 SpreadsheetCell 的非 const 引用。可添加 const 重载版本，它返回 SpreadsheetCell 的 const 引用。

    ~~~c++
    class Spreadsheet
    {
    public:
        Spreadsheet&       getCellAt(size_t x, size_t y);
        const Spreadsheet& getCellAt(size_t x, size_t y) const;
    };
    ~~~

    对于 Scott Meyer 的 ***const_cast()*** 模式，可像往常一样实现 const 版本，此后通过适当转换，传递对 const 版本的调用，以实现非 const 版本。如下所示：

    ~~~c++
    const Spreadsheet& Spreadsheet::getCellAt(size_t x, size_t y) const
    {
        verifyCoordinate(x, y);
        return m_cells[x][y];
    }

    Spreadsheet& Spreadsheet::getCellAt(size_t x, size_t y)
    {
        return const_cast<SpreadsheetCell>(as_const(*this).getCellAt(x, y));
    }
    ~~~

    使用 ***std::as_const()***（在 \<utility> 中定义）将 ***\*this*** 转换为 const Spreadsheet&，调用 getCellAt() 的 const 版本，它返回 const SpreadsheetCell&，然后使用 ***const_cast()***，将其转换为非 const 的 SpreadsheetCell&。
    有了这两个重载的 getCellAt()，现在可在 const 和非 const 的 Spreadsheet 对象上调用 getCellAt()。
    这种方法可以省去很多代码。

2. 显式删除重载
    重载方法可被显式删除，可以用这种方法禁止调用具有特定参数的成员函数。示例略。
3. 引用限定方法
    可以对类的非临时和临时实例调用普通类方法。假设有以下类：

    ~~~c++
    class TextHolder
    {
    public:
        TextHolder(string text)
            : m_text{move(text)} {};
        const string& getText() const { return m_text; }

    private:
        string m_text;
    };
    ~~~

    毫无疑问，可以在 TextHolder 的非临时实例上调用 getText()方法。例如：

    ~~~c++
    TextHolder textHolder{"Hello World"};
    cout << textHolder.getText() << endl;
    ~~~

    然而，getText() 也可被临时实例调用。

    ~~~c++
    cout << TextHolder{"Hello World"}.getText() << endl;
    cout << move(textHolder).getText() << endl;
    ~~~

    可以显式指定能够调用某个方法的实例类型，无论是临时实例还是非临时实例。这是通过向方法添加一个所谓的**引用限定符（ref-qualifier）** 来实现的。如果只应在非临时实例上调用方法，则在方法头之后添加一个 ***&*** 限定符。类似的，如果只应在临时实例上调用方法，则要添加一个 ***&&*** 限定符。
    下面修改的 TextHolder 类通过对返回 m_text 的 const 引用来实现 & 限定的 getText()。另一方面，&& 限定的 getText() 返回对 m_text 的右值引用，以便可以将 m_text 移出 TextHolder。例如，如果希望从临时 TextHolder 实例检索文本，则着可能更有效。

    ~~~c++
    class TextHolder
    {
    public:
        TextHolder(string text)
            : m_text{move(text)} {};
        const string& getText() const& { return m_text; }
        string&&      getText() && { return move(m_text); }

    private:
        string m_text;
    };
    ~~~

    假设有以下调用：

    ~~~c++
    TextHolder textHolder{"Hello World"};
    cout << textHolder.getText() << endl;

    cout << TextHolder{"Hello World"}.getText() << endl;
    cout << move(textHolder).getText() << endl;
    ~~~

    第一个对 getText() 的调用使用了 & 限定符重载，第二个和第三个使用了 && 限定符重载。

#### 9.3.4 内联方法

（粤嵌老师陈景佳讲的挺详细了，略吧）
如果编写了内联方法，应该将方法与其所在的类的定义放在统一文件中。
>高级 C++编译器不要求把内联方法的定义和类定义放在同个文件中。例如，Microsoft Visual C++ 支持链接时代码生成，会自动将较小的函数内联，哪怕这些函数没有声明为内联的或者没有在头文件中定义，也同样如此。GCC 和 Clang 具有类似的功能。

#### 9.3.5 默认参数

C++ 中，默认参数与方法重载类似。在原型中可为函数或方法指定默认值。如果用户指定了这些参数，默认值会被忽略；如果用户忽略的这些参数，将会使用默认值。
但是存在一个限制：只能从**最右边**的参数开始提供**连续**的默认参数列表，否则编译器将无法用默认参数匹配缺失的参数。默认参数可用于函数，方法和构造函数。
所有参数都有默认值的构造函数等同于默认构造函数。如果试图同时声明默认构造函数，以及具有多个参数并且所有参数都有默认值的构造函数，编译器会报错。

### 9.4 不同的数据成员类型

C++ 为数据成员提供了多种选择。除了在类中简单的声明数据成员外，还可创建 static 数据成员（类的所有对象共享）、const 数据成员、引用数据成员、const 引用数据成员和其他成员。本节解释这些不同类型的数据成员。

#### 9.4.1 静态数据成员

有时让类的所有对象都包含某个变量的副本是没必要的。数据成员可能只对类有意义，而每个对象都拥有其副本是不合适的。C++用 ***static*** 数据成员解决了这个问题。static 数据成员属于类但并**不是对象的数据成员**，可将 static 数据成员当作类的全局变量。如下所示：

~~~c++
class Spreadsheet
{
private:
    static size_t ms_counter;
};
~~~

不仅要在类定义中列出 static 类成员，还需要再源文件中为其**分配内存**，通常是定义类方法的那个**源文件**。在此还可初始化 static 成员，但注意与普通的变量和数据成员不同，默认情况下它们会初始化为 0。static 指针会初始化为 nullptr。下面是为 ms_counter 分配空间并初始化为 0 的代码：

~~~c++
size_t Spreadsheet::ms_counter;
~~~

静态数据成员默认情况下初始化为 0，但如果需要，可将它们显式的初始化为 0，如下所示：

~~~c++
size_t Spreadsheet::ms_counter{0};
~~~

这行代码在函数或方法**外部**，与声明全局变量非常类似。

1. 内联变量
    略了哈，使用 inline 关键字
2. 在类方法内访问静态数据成员
    在类方法内部，可以像使用普通数据成员那样使用静态数据成员。示例略。
3. 在方法外访问静态数据成员
    访问控制限定符适用于 static 数据成员。略略略

#### 9.4.2 const static 数据成员

类中的数据成员可声明为 const，意味着在创建并初始化后，数据成员的值不能再改变。如果某个常量只适用于类，应该使用 static const（或 const static）数据成员，也成为类常量，而不是全局常量。可在类定义中定义和初始化整形和枚举类型的 static const 数据成员，而不需要将其指定为内联变量。

#### 9.4.3 引用数据成员

示例就略了。
如果在类中定义了一个引用成员，如果不指向某些事物，引用将无法存在，因此在构造函数的初始化器中必须给这个成员指定一个值。
在拷贝构造函数中也必须初始化这个引用成员。默认拷贝构造函数会委托给非拷贝构造函数（初始化引用成员），因此将自动处理。
记住，在初始化一个引用后，不能改变它指向对象，因此无法在赋值运算符中对引用赋值。这意味着根据使用情形，可能无法为具有引用数据成员的类提供赋值运算符。如果属于这种情况，通常将**赋值运算符标记为删除**。
最后，引用数据成员也可被标记为 const。

### 9.5 嵌套类

类定义不仅可包含成员函数和数据成员，还可编写嵌套类和嵌套结构体、声明类型别名或者创建枚举类型。类中声明的一切内容都具有类作用域。如果声明的内容是 public 的，那么可在类外使用 Class:: 作用域解析语法访问。
可在类的定义中提供另一个类定义。示例就略了。
普通的访问控制也适用于嵌套类定义。如果声明了一个 private 或 protected 嵌套类，这个类只能在外围类（outer class，即包含它的类）中使用。嵌套的类有权访问外围类中的**所有 private 或 protected 成员**，而外围类却只能访问嵌套类中的 public 成员。

### 9.6 类内的枚举类型

枚举类型也可作为类的数据成员。示例就略了。

### 9.7 运算符重载

#### 9.7.1 示例：为 SpreadsheetCell 实现加法

具体去看书，这里只抄一些大概

1. 首次尝试：add 加法
    可像下面这样声明并定义 SpreadsheetCell 类的 add() 方法

    ~~~c++
    class SpreadsheetCell
    {
    public:
        SpreadsheetCell add(const SpreadsheetCell& cell) const;
    };
    ~~~

    这个方法将两个单元格相加，返回第三个新的单元格，其值为前两个单元格的和。将这个方法声明为 const，并把 const SpreadsheetCell 的引用作为参数，原因是 add() 不改变任意一个原始单元格。实现略。

2. 第二次尝试：将 operator+ 作为方法重载
    C++ 允许编写自己的加号版本，以正确地处理类，称为加运算符。为此可编写一个名为 operator+ 地方法，如下所示：

    ~~~c++
    class SpreadsheetCell
    {
    public:
        SpreadsheetCell operator+(const SpreadsheetCell& cell) const;
    };
    ~~~

    实现略。
    operator+ 只是个名称，就像 foo 或 add 一样。当C++编译器分析一个程序，遇到运算符（例如，+、-、= 或 <<）时，就会试着查找名为 operator+、operator-、operator= 或 operator<<，且具有适当参数的函数或方法。
    注意，用作 operator+ 参数的对象类型并不一定要与编写 operator+ 的类相同。
    此外还要注意，可任意指定 operator+ 的返回值类型。但应该遵循最不让人诧异的原则，也就是说，operator+ 的返回值通常应该是用户期望的。

    **隐式转换**

    一旦编写前面所示的 operator+，不仅可将两个单元格相加，还可将单元格与 string_view、double 或 int 值相加。

    ~~~c++
    SpreadsheetCell myCell{4}, aThirdCell;
    string          str{"hello"};
    aThirdCell = myCell + string_view{str};
    aThirdCell = myCell + 5.6;
    aThirdCell = myCell + 4;
    ~~~

    上面的代码之所以可运行，是应为编译器会试着查找合适的 operator+，而不是只查找指定类型的那个 operator+。为找到 operator+，编译器还试图查找合适的**类型转化**。SpreadsheetCell 类拥有**转换构造函数**（见第 8 章），可以将 double 或 string_view 转换为 SpreadsheetCell。在上例中当编译器看到 SpreadsheetCell 试图与 double 值相加时，发现了用 double 值作为参数的 SpreadsheetCell 构造函数，就会构建一个**临时**的 SpreadsheetCell 对象，传递给 operator+。
    由于必须创建临时对象，隐式使用构造函数的效率不高。为避免与 double 值相加时隐式地使用构造函数，可编写第二个 operator+。

3. 第三次尝试：全局 operator+
    隐式转换允许使用 operator+ 方法将 SpreadsheetCell 对象与 int 和 double 值相加。然而，这个运算符不具有互换性。
    当 SpreadsheetCell 对象在运算符的左边时，隐式转换正常运行，但在右边时无法运行。加法时可交换的，因此这里存在错误。问题在于必须在 SpreadsheetCell 对象上调用 operator+ 方法，对象必须在 operator+ 的左边。这是C++语言定义的方式。
    然而，如果用不局限于某个特定对象的**全局 operator+ 函数**替换类内的 operator+ 方法，就可以正常运行。

#### 9.7.2 重载算术运算符

理解了如何编写 operator+，剩余的基本算术运算符就变得简单了，+、- 和 * 的声明就略了，提一下 /。
对于 operator/ 而言，唯一棘手指出是记着检查除数是否为 0，如果检测到除数为 0，该方法将抛出异常。

~~~c++
SpreadsheetCell operator/(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    if (rhs.getValue() == 0) {
        throw invalid_argument{"Divide by zero."};
    }
    return SpreadsheetCell{lhs.getValue() / rhs.getValue()};
}
~~~

**重载简写算术运算符**：

除了基本算术运算符外，C++还提供了简写运算符，例如 += 和 -=。必须**显式的重载简写运算符**。这些运算符与基本运算符不同，它们会改变运算符左边的对象，而不是创建一个新对象。此外还有一个微妙差别，它们生成的结果是对**被修改对象的引用**，这一点与赋值运算符相似。
简写算术运算符的左边总要有一个对象，因此应该将其**作为方法**而不是全局函数。

~~~c++
class SpreadsheetCell
{
public:
    SpreadsheetCell& operator+=(const SpreadsheetCell& rhs);
    SpreadsheetCell& operator-=(const SpreadsheetCell& rhs);
    SpreadsheetCell& operator*=(const SpreadsheetCell& rhs);
    SpreadsheetCell& operator/=(const SpreadsheetCell& rhs);
};
~~~

下面是 operator+= 的实现，其他的与此类似

~~~c++
SpreadsheetCell& SpreadsheetCell::operator+=(const SpreadsheetCell& rhs)
{
    set(getValue() + rhs.getValue());
    return *this;
}
~~~

简写算术运算符是对基本算术运算符和赋值运算符的结合。
如果既有某个运算符的普通版本，又有简写版本，建议**基于简写版本实现普通版本**，以避免代码重复。例如：

~~~c++
SpreadsheetCell operator+(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    auto result{lhs};   // 拷贝左值
    result += rhs;
    return result;
}
~~~

#### 9.7.3 重载比较运算符

在 C++20 标准之后，比较运算符有了很多变化。
与基本算术运算符一样，6 个 C++20 之前的比较运算符应该是全局函数，这样就可以在运算符的左侧和右侧参数上使用隐式转换。比较运算符都返回 bool。当然，也可以更改返回类型，但不建议这样做。
6 个基本比较运算符为：***==***、***<***、***>***、***!=***、***<=*** 和 ***>=***。示例略。
当类中的数据成员较多时，比较每个数据成员可能比较痛苦。然而，当实现了 == 和 < 之后，可以根据这两个运算符编写其他比较运算符。例如：

~~~c++
bool operator>=(const SpreadsheetCell& lhs, const SpreadsheetCell& rhs)
{
    return !(lhs < rhs);
}
~~~

用这种方式，需要编写 6 个单独的函数来支持 7 个比较运算符，这只是为了相互比较两个 SpreadsheetCell。使用当前实现的 6 个比较函数，可以将 SpreadsheetCell 与 double 进行比较，因为 double 参数隐式转换为 SpreadsheetCell。如前所述，这种隐式转换可能效率低下，因为必须创建临时对象。与前面的 operator+ 一样，可以通过显式实现与 double 进行比较的函数来避免这种情况。对于每个操作符\<op>，将需要多个重载。
如果需要支持所有的比较运算符，这将写很多重读的代码。
现在切换一下，C++20 简化了向类中添加对比较运算符的支持。首先，对于 C++20，实际上建议将operator== 实现为类的成员函数，而不是全局函数。还要注意，添加 ***\[[nodiscard]]*** 属性是个好主意，这样操作符的结果就不会被忽略。例如：

~~~c++
[[nodiscard]] bool operator==(const SpreadsheetCell& rhs) const;
~~~

在 C++20 中，单个的 operator-- 重载就可以使下面的比较生效。

~~~c++
if (myCell == 10) {
    cout << "myCell == 10\n";
}
if (10 == myCell) {
    cout << "10 == myCell\n";
}
~~~

诸如 10\==myCell 的表达式由 C++20 编译器重写为 myCell==10，可以为其调用 operator\== 成员函数。此外，通过实现 operator\==，C++20 会自动添加对 != 的支持。
接下来，要实现对全套比较运算符的支持，在 C++20 中，只需要实现一个额外的重载运算符，operator<=>。一旦类由运算符 == 和 <=> 的重载，C++20 就会自动为所有 6 个比较运算符提供支持！对于 SpreadsheetCell 类，运算符 <=> 如下所示：

~~~c++
[[nodiscard]] std::partial_ordering operator<=>(const SpreadsheetCell& rhs) const;
~~~

>注意，C++20 编译器不会根据 <=> 重写 == 或 !=。这样做是为了避免性能问题，因为 operator== 的显式实现通常比使用 <=> 更高效。

存储在 SpreadsheetCell 中的值是 double 类型的。请记住，第 1 章提到过，浮点类型只有偏序，这就是重载返回 std::partial_ordering 的原因。实现非常简单:

~~~c++
partial_ordering SpreadsheetCell::operator<=>(const SpreadsheetCell& rhs) const
{
    return getValue() <=> rhs.getValue();
}
~~~

通过实现 operator<=>，C++20 可以自动提供对>、<、<= 和 >= 的支持，通过将使用这些运算符的表达式重写为使用 <=> 的。例如，诸如 myCell<aThirdCell 的表达式会自动重写为与 std::is_lt(myCell<=>aThirdCell) 等价的内容，其中 is_lt() 是一个命名的比较函数，见第 1 章。
所以，只需要实现 operator== 和 operator<=>，SpreadsheetCell 类就可以支持所有的比较运算符。
由于 SpreadsheetCell 类支持从 double 到 SpreadsheetCell 的隐式转换，因此也支持以下比较：
如果可以显式地将 operator<=> 设置为默认，作者建议这样做，而不是自己实现它。通过编译器为你编写，它将与新添加或修改地数据成员保持同步。如果自己实现运算符，则无论何时添加数据成员或更改现有数据成员，都需要记住更新 operator<=> 的实现。如果编译器没有自动生成 operator==，则以上内容对其也适用。
只有当 operator== 和 <=> 使用定义操作符的类类型的 const 引用作为参数时，才可能显式将 operator== 和 <=> 设置为默认。例如，以下操作不起作用：

~~~c++
[[nodiscard]] auto operator<=>(double) const = default;
~~~

>注意
>在C++2- 中为了添加所有 6 个不计较运算符的支持：
>
> - 如果一个默认的 operator<=> 适用于你的类，那么只需要一行代码来显式地将默认运算符 <=> 作为一个方法。在某些情况下，你可能还需要显式地将 operator== 设置为默认。
>
> - 否则，需要作为方法重载 operator== 和 <=> 地实现
>不需要手动实现其他的比较运算符

#### 9.7.4 创建具有运算符重载的类型

略。

### 9.8 创建稳定的接口

理解了在 C++ 中编写类的所有语法后，回顾第 5 章和第 6 章的设计原则会对此有所帮助。在C++ 中，类是主要的抽象单元，应将**抽象原则**应用到类，尽可能分离接口和实现。确切来说，应该**将所有数据成员设置为 private**，并提供相应的**获取器**和**设置器**方法。

**使用接口类和实现类**.
注意，书中使用了 C++20 的模块，我想试着把它改为不用模块的版本。todo...

即使提前进行估算并采用最佳设计原则，C++ 语言本质上对抽象原则也并不友好。其语法要求将 public 接口和 private（或 protected）数据成员及方法放在一个类定义中，从而将类的某些内部实现细节向客户公开。这种做法的缺点在于，如果不得不在类中加入新的非 public 方法或数据成员，所有的客户代码都必须重新编译，对于较大项目而言这是负担。

可创建清晰的接口，并隐藏所有实现细节，从而得到稳定的接口。但这样做有点繁杂。
基本原则是为想编写的每个类都定义两个类：**接口类**和**实现类**。实现类于不采用这种方法编写的类相同，接口类给出了**与实现类一样的 public 方法**，但只有一个数据成员：**指向实现类对象的一个指针**。这称为 ***pimpl idiom***（**私有实现惯用方法**，也称为**柴郡猫技术**）或 bridge 模式，接口类方法的实现只是调用实现类对象的等价方法。这样做的结果是无论实现如何改变，都不会影响 public 接口类，从而降低了重新编译的可能。当有且只有实现改变时，使用接口类的客户并不需要重新编译。注意只有在单个数据成员是实现类的指针时，这个方法才有效。如果它是按值传递的数据成员，在实现类的定义改变时，客户代码必须重新编译。
以下将方法应用到 Spreadsheet 类，这是头文件

~~~c++
#ifndef SPREADSHEET_H
#define SPREADSHEET_H


#include <cstddef>
#include <memory>

// using namespace std;

class SpreadsheetCell;

class SpreadsheetApplication
{};

class Spreadsheet
{
public:
    static const size_t MaxHeight{100};
    static const size_t MaxWidth{100};

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;


public:
    Spreadsheet(const SpreadsheetApplication& theApp, size_t width = MaxWidth,
                size_t height = MaxHeight);
    Spreadsheet(const Spreadsheet& src);
    Spreadsheet(Spreadsheet&&) noexcept;
    ~Spreadsheet();

    Spreadsheet& operator=(const Spreadsheet& rhs);
    Spreadsheet& operator=(Spreadsheet&&) noexcept;

    void             setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
    SpreadsheetCell& getCellAt(size_t x, size_t y);

    size_t getId() const;

    void swap(Spreadsheet& other) noexcept;
};

void swap(Spreadsheet& first, Spreadsheet& second) noexcept;

#endif
~~~

实现类 Impl 是一个 private 嵌套类，因为只有 Spreadsheet 需要用到这个实现类。Spreadsheet 现**只包含一个数据成员**：指向 Impl 实例的指针。public 方法与原来的 Spreadsheet 相同。
嵌套的 Spreadsheet::Impl 类定义在 spreadsheet 实现文件中。Impl 类不应该导出，因为它应该**对用户隐藏起来**。Spreadsheet.cpp 实现文件的开头如下所示：

~~~c++
#include "Spreadsheet.h"

#include "SpreadsheetCell.h"

#include <algorithm>
#include <format>
#include <stdexcept>
#include <utility>

using namespace std;

class Spreadsheet::Impl
{
private:
    const size_t      m_id{0};
    size_t            m_width{0};
    size_t            m_height{0};
    SpreadsheetCell** m_cells{nullptr};

    const SpreadsheetApplication& m_theApp;

    static inline size_t ms_counter{0};



public:
    Impl(const SpreadsheetApplication& theApp, size_t width, size_t height);
    Impl(const Impl& src);
    Impl(Impl&&) noexcept = default;
    ~Impl();
    Impl& operator=(const Impl& rhs);
    Impl& operator=(Impl&&) noexcept = default;

    void             setCellAt(size_t x, size_t y, const SpreadsheetCell& cell);
    SpreadsheetCell& getCellAt(size_t x, size_t y);

    size_t getId() const;

    void swap(Impl& other) noexcept;

private:
    void verifyCoordinate(size_t x, size_t y) const;
};

Spreadsheet::Impl::Impl(const SpreadsheetApplication& theApp, size_t width, size_t height)
    : m_id{ms_counter++}
    , m_width{min(width, Spreadsheet::MaxWidth)}
    , m_height{min(height, Spreadsheet::MaxHeight)}
    , m_theApp{theApp}
{
    m_cells = new SpreadsheetCell*[m_width];
    for (size_t i{0}; i < m_width; i++) {
        m_cells[i] = new SpreadsheetCell[m_height];
    }
}
// 其余省略
~~~

Impl 类具有与 Spreadsheet 类几乎相同的接口。对于方法实现，需要记住 Impl 是一个嵌套类，因此，需要将作用域指定为 Spreadsheet::Impl。因此，对于构造函数，它变成了 Spreadsheet::Impl::Impl(...)。
现在，Spreadsheet 类有一个指向实现类的 unique_ptr，Spreadsheet 类需要一个用户声明的析构函数。我们**不需要对这个析构函数进行任何处理**，可在文件中设置 ***=default***，如下所示：

~~~c++
Spreadsheet::~Spreadsheet() = default;
~~~

事实上，它**必须在实现文件中而不是直接在类定义中默认**。原因是 Impl 类仅在 Spreadsheet 类定义中声明，也就是说，编译器知道某个地方将有一个 Spreadsheet::Impl 类，但此时它还不知道定义。因此，不能在类定义中设置默认析构函数，因为这样编译器将尝试使用尚未定义的 Impl 类的析构函数。在这种情况下，将其他方法设置为默认时也是如此，例如移动构造函数和移动赋值运算符。

Spreadsheet 方法（例如 setCellAt() 和 getCellAt()）的实现只是**将请求传递给底层的 Impl 对象**：

~~~c++
void Spreadsheet::setCellAt(size_t x, size_t y, const SpreadsheetCell& cell)
{
    m_impl->setCellAt(x, y, cell);
}

SpreadsheetCell& Spreadsheet::getCellAt(size_t x, size_t y)
{
    return m_impl->getCellAt(x, y);
}
~~~

Spreadsheet 的构造函数必须**创建一个新的 Impl 实例**来完成这个任务

~~~c++
Spreadsheet::Spreadsheet(const SpreadsheetApplication& theApp, size_t width, size_t height)
{
    m_impl = make_unique<Impl>(theApp, width, height);
}

Spreadsheet::Spreadsheet(const Spreadsheet& src)
{
    m_impl = make_unique<Impl>(*src.m_impl);
}
~~~

拷贝构造函数看上去有点奇怪，因为需要从源 Spreadsheet 复制底层的 Impl。由于拷贝构造函数采用一个指向 Impl 的引用而不是指针，因此**为了获取对象本身**，必须**对 m_Impl 指针解除引用**，以得到它的对象。

Spreadsheet 赋值运算符必须采用类似方式传递到底层的 Impl 的赋值

~~~c++
Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs)
{
    *m_impl = *rhs.m_impl;
    return *this;
}
~~~

赋值运算符的第一行看上去有点奇怪。Spreadsheet 赋值运算符需要传递对 Impl 赋值运算符的调用，而这个运算符只有在复制直接对象时才会执行。通过对 m_impl 指针解除引用，会**强制使用直接对象赋值**，从而**调用 Impl 的赋值运算符**。

swap() 函数用于交换单独的数据成员：

~~~c++
void Spreadsheet::swap(Spreadsheet& other) noexcept
{
    std::swap(m_impl, other.m_impl);
}
~~~

真正将接口和实现分离的技术功能强大。应该去适应它。支持这种方法最有力的论据不是将接口分离的美感，而是类的实现改变后答复缩短构建时间。一个类不使用 pimpl idiom 时，对实现类的更改将导致漫长的构建过程。例如，给类定义增加数据成员时，将触发使用这个类的其他所有源文件的重新构建。而使用 pimpl idiom，可以修改实现类的定义，只要公共接口保持不变，就不会触发长时间构建过程。

## 10 揭秘继承技术

### 10.1 使用继承构建类

#### 10.1.2 重写方法

从某个类继承的主要原因是为了添加或替换功能。在许多情况下，可能选哟替换或重写某个方法来修改类的行为。

1. 关键字 ***virtual***
    在 C++ 中，重写（override）方法有一点别扭，因为必须使用关键字 virtual。只有基类中声明为 virtual 的方法才能被派生类正确的重写。关键字 virtual 出现在方法声明的开头。
    派生类也是如此，如果想进一步在派生类中重写它们，相应的方法也应该标记为 virtual。
    示例略。
2. 重写方法的语法
    为了重写某个方法，需要在派生类的定义中重新声明这个方法，就像在基类中声明的那样，但是需要添加关键字 ***override***，并从 派生类中删除关键字 virtual。
    示例还是略。
    注意，在方法定义中，不需要再方法名前重复使用关键字 virtual。
    如果需要的话，可以在重写方法的前面你添加关键字 virtual，但这样做是多余的。
    一旦将方法或析构函数标记为 virtual，它们在所有派生类中就一直是 virtual，即使在派生类中删除了 virtual 关键字，也是如此。
3. 客户对重写方法的看法
    示例依然略。
    如前所述，指针或引用可指向某个类或其派生类的对象。对象本身“知道”自己所属的类，因此只要这个方法声明为 virtual，就会自动调用对应的方法。如果**在基类中省略了 virtual 关键字，重写功能将无法正确的运行**。
    记住，即使基类的引用或指针知道这实际上是一个派生类，也无法访问没有在基类中定义的，定义在派生类中的方法或成员。
    非指针或非引用对象无法正确处理派生类的特征信息。可将 Derived 对象转换为 Base 对象，或将 Derived 对象赋值给 Base 对象，因为 Derived 对象也是 Base 对象。然而，此时这个对象将**丢失派生类的所有信息**。

    ~~~c++
    Derived myDerived;
    Base    assignedObject{myDerived};
    assignedObject.somMethod();
    ~~~

    为记住这个看上去有点奇怪的行为，可考虑对象在内存中的状态。将 Base 对象当作占据了一块内存的盒子。Derived 对象是稍微大一点的盒子，因为它拥有 Base 对象的一切，还添加了一点内容。对于指向 Derived 对象的引用或指针，这个盒子并没有变——只是可以用新的方法访问它。然而，如果将 Derived 对象转换为 Base 对象，就会为了适应小的盒子而扔掉 Derived 类中全部的“独有特征”。

    >注意
    >当基类的指针或引用指向派生类对象时，派生类保留其数据成员和重写的方法。但是通过类型转换将派生类对象转换为基类对象时，就会**丢失其独有特征**。重写方法和数据丢失称为**截断**（slicing）。

4. ***override*** 关键字
    override 关键字的使用时可选的，但强烈推荐使用。如果没有 override 关键字，可能会偶然创建一个新的虚方法，而不是重写基类的方法。
    示例就略了。
5. virtual 的真相
    如果方法不是 virtual，也可以试着重写这个方法，但是这样做会导致微妙的错误。
    **隐藏而不是重写**
    下面的代码显示了一个基类和一个派生类，每个类都有一个方法。派生类试图重写基类的方法，但是在基类中没有将这个方法声明为 virtual。

    ~~~c++
    class Base
    {
    public:
        void go() { cout << "go() called on Base" << endl; }
    };

    class Derived : public Base
    {
    public:
        void go() { cout << "go() cassel on Derived" endl; }
    };
    ~~~

    试着用 Derived 对象调用 go() 方法好像没有问题。

    ~~~c++
    Derived myDerived;
    myDerived.go();
    ~~~

    正如与其的那样，这个调用的结果是 “go() called on Derived”。然而，由于这个方法不是 virtual，因此实际上**没有被重写**。相反，Derived 类创建了一个新的方法，名称也是 go()，这个方法与 Base 类的 go() 方法完全没有关系。为证实这一点，只需要用 Base 指针或引用调用这个方法。

    ~~~c++
    Derived myDerived;
    Base&   ref{myDerived};
    red.go();
    ~~~

    我们可能希望输出的是 “go() called on Derived”，但实际上，输出的是 “go() called on Base”。这是因为 ref 变量是一个Base 类型的引用，因为此处省略了 virtual 关键字。当调用 go() 方法时，只是执行了 Base 类中的 go() 方法。由于不是虚方法，因此不要考虑派生类是否重写了这个方法。

    >警告：
    >试图重写非虚方法将会“隐藏”基类定义的方法，并且重写的这个方法只能在派生类环境中使用。

    **如何实现 virtual**
    为理解如何避免隐藏方法，需要了解 virtual 关键字的真正作用。C++ 在编译类时，会创建一个包含类中所有方法的二进制对象。在非虚情况下，将控制交给正确方法的代码是硬编码，此时会根据编译器的类型调用对应的方法。这称为静态绑定（static binding），也成为早绑定（early binding）。
    如果方法声明为 virtual，会使用名为**虚表**（vtable）的特定内存区域来调用正确的实现。每个具有一个或多个虚方法的类都具有一张虚表，这种类的每个对象都包含指向虚表的指针，这个虚表包含指向虚方法实现的指针。通过这种方法，当使用某个对象调用方法时，指针也进入虚表，然后根据实际的对象类型在运行期执行正确版本的方法。着称为动态绑定（dynamic binging）或晚绑定（late binding）。
    示例略
    **使用 virtual 的理由**
    要调用虚方法，程序需要执行一项附加操作，即对指向要执行的适当代码的指针解除引用。在多数情况下这样做会轻微地影响性能。但是，在多数应用程序中，很难察觉到使用虚方法和不使用虚方法所带来的性能上的差别。
    **析构函数都应该声明为 virtual**。原因是，如果析构函数未声明为 virtual，很容易在销毁对象时不释放内存。唯一允许不把析构函数声明为 virtual 的例外情况是，**类被标记为 final**。
    例如，派生类使用的内存在构造函数中动态分配，在析构函数中释放。如果不调用析构函数，这块内存将无法释放。类似的，如果派生类具有一些成员，这些成员在类的实例销毁时自动删除，如 std::unique_ptr，那么如果从未调用析构函数，将不会删除这些成员。
    实例略。

    >注意：
    >如果在析构函数中什么都不做，只想把它设置为 virtual，可显式的设置 “***=default***”

    注意从 C++11 开始，如果类具有用户声明的析构函数，就不会生成赋值构造函数和拷贝运算符。基本上，一旦有了用户声明的析构函数，C++ 的 5 法则就会开始执行。在此类情况下，如果仍然需要编译器生成的复制构造函数、拷贝赋值运算符、移动构造函数和移动赋值运算符，可将它们显式地设置为默认（=default）。

    >警告：
    >除非有特别原因，或者类被标记为 final，否则强烈建议**将所有方法（包括析构函数、构造函数除外）声明为 virtual**，构造函数不需要，也无法声明为 virtual，因为在创建对象时没总会明确地指定类。

6. 禁用重写
    除了将实体类标记为 final，C++ 还允许将**方法标记为 final**。这意味着无法在派生类中重写这个方法。

### 10.3 利用父类

编写派生类时，需要知道父类和派生类之间的交互方式。创建顺序、构造函数链和类型转换都是潜在的 bug 来源。

#### 10.3.1 父类构造函数

对象并不是突然建立起来的，创建对象时必须同时创建父类和包含于其中的对象。C++ 定义了如下的创建顺序：

1. 如果某个类具有基类，则执行基类的默认构造函数。除非在 ctor-initializer 中调用了基类构造函数，此时调用这个构造函数而不是默认构造函数。
2. 类的非静态数据成员**按照声明的顺序**创建。
3. 执行该类的构造函数

可递归使用这些规则。如果有祖父类，祖父类就在父类之前初始化，以此类推。
示例略。
注意，基类的构造函数是自动调用的。C++ 将自动调用父类的默认构造函数（如果存在的话）。如果父类的默认构造函数不存在，或者存在默认构造函数但希望使用其他构造函数，可在构造函数初始化器（constructor initializer）中像初始化数据成员那样链接（chain）构造函数。比如，下面的代码显式了没有默认构造函数的 Base 版本。相关版本的 Derived 必须显式地告诉编译器如何调用 Base 构造函数，否则代码无法编译。

~~~c++
class Base
{
public:
    Base(int i) {}
};

class Derived : public Base
{
public:
    Derived()
        : Base{7}
    { /* 其余省略 */
    }
}
~~~

从派生类向基类传递构造函数的参数很正常，毫无问题，但是无法传递数据成员。如果这么做，代码可以编译，但是记住**在调用基类构造函数之后才会初始化数据成员**。如果将数据成员作为参数传递给父类构造函数，数据成员不会初始化。

>警告：
>虚方法的行为在构造函数中是不同的，如果派生类重写了基类中的虚方法，从**基类构造函数中调用虚方法**，就会**调用虚方法的基类实现而不是派生类中的重写版本**。

#### 10.3.2 父类的析构函数

由于析构函数没有参数，因此始终可自动调用父类的析构安徽念书。析构函数的调用顺序刚好于构造函数相反：

1. 调用类的析构函数
2. 销毁类的数据成员，销毁顺序与创建的顺序相反
3. 如果有父类，调用父类的析构函数

也可递归使用这些规则。链的最底层成员总是第一个被销毁。示例还是略，但是记住，所有析构函数都应该声明为 virtual，这一点非常重要。

>警告：
>将所有析构函数声明为 virtual！编译器生成的默认析构函数不是virtual，因此应该定义自己（或显式设置为默认）的虚析构函数，至少在父类中应该这样做。
---
>警告：
>与构造函数一样，在析构函数中调用虚方法时，虚方法的行为将有所不同。如果派生类重写了基类中的虚方法，在基类的析构函数中调用该方法，会执行该方法的基类实现，而不是派生类的重写版本。

#### 10.3.3 使用父类方法

在派生类中重写方法时，将有效替换原始方法。然而，方法的父类版本任然存在，任然可以使用这些方法。
示例略。反正就是用作用域解析。

#### 10.3.4 向上转型和向下转型

如前所述，对象可转换为父类对象，或者赋值给父类。示例如下：

~~~c++
Derived myDerived;
Base    myBase{myDerived};   // 截断
~~~

这种情况下会导致截断。然而，如果派生类对基类的指针或引用赋值，则不会产生截断。

~~~c++
Base& myBase{myDerived};   // 不会截断
~~~

这是通过基类使用派生类的正确途径，也称为向上转型（upcasting）。这也是让方法和函数使用类的引用而不是直接使用类对象的原因。通过使用引用，派生类在传递时没有发生截断。

>警告：
>当向上转型时，使用基类指针或引用以避免截断

将基类转换为派生类也称为向下转型（downcasting），专业的 C++ 程序员不通常赞成这种转换，因为无法保证对象实际上属于派生类，也因为向下转型是不好的设计。示例略。
向下转型有时是必需的，在可控环境中可充分利用这种转换。然而，如果打算进行向下转型，应该使用 dynamic_cast()，以使用对象内建的类型信息，拒绝没有意义的类型转换。这种内建信息通常驻留在虚表中，这意味着 dynamic_cast() 只能用于具有虚表的对象，即至少有一个虚编号的对象。如果针对某个指针的 dynamic_cast() 失败，这个指针的值就是 nullptr，而不是指向某个无意义的数据。如果针对对象引用的 dynamic_cast() 失败，将抛出 std::bad_cast 异常。详见本章最后一节。
示例如下：

~~~c++
void lessPresumptuous(Base* base)
{
    Derived* myDerived{dynamic_cast<Derived*>(base)};
    if (myDerived != nullptr) {
        // TODO
    }
}
~~~

记住，向下转型通常是设计不良的标志。为避免使用向下转型，应当反思，并修改谁。比如，lessPresumptuous() 函数实际上只能用于 Derived 类的对象，因此不应当接受 Base 类的指针，而应接受 Derived 类的指针。这样就不需要向下转型了。如果函数用于从 Base 类继承的不同派生类，而应考虑使用多态性的解决方案，如下所述。

>警告：
>仅在必要的情况下才使用向下转型，一定要使用 dynamic_cast()。

### 10.4 继承与多态性

在理解了派生类与父类的关系后，就可以用最有力的方式使用继承——多态性（polymorphism）。第 5 章种说过，多态性可以互换地使用具有相同父类的对象，并用对象替换父类对象。

#### 10.4.2 设计多态性的电子表格单元格

电子表格单元格需要可以存储 double 型或 string_view 型的数据成员。为此设计 DoubleSpreadsheetCell 和 StringSpreadsheetCell 类，这两个类地位等同，并有共同的父类 SpreadsheetCell。如下所示

~~~mermaid
classDiagram
class  SpreadsheetCell
class  DoubleSpreadsheetCell
class  StringSpreadsheetCell

SpreadsheetCell <|-- StringSpreadsheetCell
SpreadsheetCell <|-- DoubleSpreadsheetCell
~~~

上图所示的设计显示了让 SpreadsheetCell 层次结构具有多态性的方法。由于 DoubleSpreadsheetCell 和 StringSpreadsheetCell 都从统一个父类 SpreadsheetCell 继承，总其他代码的视角，它们是可以互换的。实际上这意味着：

- 两个派生类都支持由基类定义的统一接口（方法集）
- 使用 SpreadsheetCell 对象的代码可调用接口种的任何方法，而不需要知道着个单元格是 StringSpreadsheetCell 还是 DoubleSpreadsheetCell。
- 由于虚方法的特殊能力，会根据对象所属的类调用接口中每个方法的正确实例
- 其他数据结构可通过引用父类类型，包含一组多类型的单元格

#### 10.4.3 SpreadsheetCell 基类

当设计基类时，应该考虑派生类之间的关系。根据这些关系，看提取共有特性并将其放到父类中。比如，字符串单元格和双精度单元格的共同点在于都包含单个数据块。由于数据来自用户，并最终显示给用户。可以把这个值设置为字符串，并作为字符串来获取。这些行为就是用来组成基类的共享功能。

1. 初次尝试
    SpreadsheetCell 基类负责定义所有派生类支持的行为。在本例中，所有单元格都需要将值设置为字符串。此外，所有单元格都需要将当前值返回为字符串。基类定义中声明了这些方法，以及显式设置为默认的虚析构函数，但没有数据成员。

    ~~~c++
    class SpreadsheetCell
    {
    public:
        virtual ~SpreadsheetCell() = default;
        virtual void        set(std::string_view value);
        virtual std::string getString() const;
    };
    ~~~

    当开始编写这个类的.cpp文件时，很快就会遇到问题。由于电子表格单元的基类既不包含 double 也不包含 string 类型的数据成员，如何实现这个类呢？更宽泛地讲，如何定义这样一个父类，这个父类声明了派生类支持的行为，但是并不定义这些行为的实现。
    可能的方法之一是为这些行为实现“什么都不做”的功能。比如，调用 SpreadsheetCell 基类的 set() 方法将没有任何效果，因为基类没有任何成员需要设置。然而这种方法仍然存在问题。理想情况下，基类不应该由实例。调用 set() 方法应该总是有效，因为总是会基于 DoubleSpreadsheetCell 或 StringSpreadsheetCell 调用这个方法。好的解决方案应该强制执行这一限制。
2. 纯虚方法和抽象基类
    纯虚方法（pure virtual methods）在类定义中显式说明该方法不需要定义。如果将某个方法设置为纯虚方法，就是告诉编译器当前类中不存在这个方法的定义。具有至少一个纯虚方法的类称为抽象类，因为这个类不能被实例化。编译器会强制接受这个事实：如果某个类包含一个或多个纯虚方法，就无法构建这种类型的对象。
    采用专门的语法指定纯虚方法：方法声明后紧接着 =0.不需要编写任何代码。

    ~~~c++
    class SpreadsheetCell
    {
    public:
        virtual ~SpreadsheetCell()                      = default;
        virtual void        set(std::string_view value) = 0;
        virtual std::string getString() const           = 0;
    };
    ~~~

    现在基类成了抽象类，无法创建 SpreadsheetCell 对象，下面的代码将无法编译。

    ~~~c++
    SpreadsheetCell cell;
    ~~~

    然而，一旦实现了 StringSpreadsheetCell 类，下面的代码就可成功编译，原因在于实例化了抽象基类的派生类。

    ~~~c++
    unique_ptr<SpreadsheetCell> cell(new StringSpreadsheetCell{});
    ~~~

    >注意：
    >抽象类提供了一种禁止其他代码直接实例化对象的方法，而它的派生类可以实例化对象。

    注意。不需要实现 SpreadsheetCell 类。所有方法都是纯虚方法，析构函数显式地设置为默认。

#### 10.4.4 独立的派生类

编写 StingSpreadsheetCell 和 DoubleSpreadsheetCell 类只需要实现父类中定义的功能。由于想让客户实现并使用字符串单元格和双精度单元格，因此单元格不可以是抽象的——必须实现从父类继承的所有纯虚方法。如果派生类没有实现从父类继承的所有纯虚方法，那么派生类也是抽象的，客户就不能实例化派生类的对象。

1. StringSpreadsheetCell 类的定义
    编写 StringSpreadsheetCell 类定义的第一步是从 SpreadsheetCell 类继承。书中需要导入模块，咱就导入头文件。
    第二部是重写继承的纯虚方法，此次不将其设置为 0。
    最后一步是为字符串单元格添加一个私有数据成员 m_value，在其中存储实际单元格数据。这个数据成员是 std::optional（见第 1 章）。通过 optional 类型，可以确认是否没有设置单元格的值或单元格的值设为空字符串。

    ~~~c++
    class StringSpreadsheetCell : public SpreadsheetCell
    {
    private:
        std::optional<std::string> m_value;

    public:
        void set(std::string_view value) override;

        std::string getString() const override;
    };
    ~~~

2. StringSpreadsheetCell 的实现
    set() 方法十分简单，因为内部表示已经是一个字符串。getString() 方法必须考虑到 m_value 的类型是 optional，可能不具有值。如果 m_value 不具有值，getString() 将返回一个默认字符串，本例中是空字符串，可以使用 std::optional 的 value_or() 方法对此进行简化。使用 `m_value.value_or("")`，如果 m_value 包含实际的值，将返回相应的值，否则将返回空值。

    ~~~c++
    void        set(std::string_view value) override { m_value = value; }
    std::string getString() const override { return m_value.value_or(""); }
    ~~~

3. DoubleSpreadsheetCell 类的定义和实现
    双精度版本遵循类似的模式，但具有不同的逻辑。除了基类的 set() 方法以 string_view 作为参数之外，还提供了新的 set() 方法以允许用户使用双精度设置其值。两个新的 private static 方法用于字符串和双精度的互相转换，反之亦然。与 StringSpreadsheetCell 相同，这个类也有一个 m_value 数据成员，此时这个成员的类型是 optional\<double>。

    ~~~c++
    class DoubleSpreadsheetCell : public SpreadsheetCell
    {
    private:
        std::optional<double> m_value;

    public:
        virtual void set(double value);
        void         set(std::string_view value) override;
        std::string  getString() const override;

    private:
        static std::string doubleToString(double value);
        static double      stringToDouble(std::string_view value);
    };
    ~~~

    以双精度作为参数的 set() 方法简单明了。string_view 版本使用了 private static 方法 stringToDouble()。getString() 方法返回存储的双精度作为字符串；如果未存储任何值，则返回一个空字符串。它使用 std::optional 的 has_value() 方法来查询 optional 是否具有实际值。如果具有值，则使用 value() 方法获取。

    ~~~c++
    virtual void set(double value) { m_value = value; }
    void         set(std::string_view value) override { m_value = stringToDouble(value); }
    std::string  getString() const override
    {
        return (m_value.has_value() ? doubleToString(m_value.value()) : "");
    }
    ~~~

    可以看到，在层次结构中实现电子表格单元格的主要优点是代码更加简单。每个对象都以自我为中心，只执行各自的功能。

#### 10.4.5 利用多态性

现在 SpreadsheetCell 参差结构与具有多态性，客户代码可利用多态性提供的种种好处。下面的测试程序显式了这些功能。
为演示多态性，测试程序声明了一个具有 3 个 SpreadsheetCell 指针的矢量，记住由于 SpreadsheetCell 是一个抽象类，因此不能创建此种类型的对象。然而，仍然可以使用 SpreadsheetCell 的指针或引用，因为它实际上指向的是其中一个抽象类。由于是父类型 SpreadsheetCell 的矢量，因此可以任意存储两个派生类。这意味着矢量元素可以是 StringSpreadsheetCell 或 DoubleSpreadsheetCell。

~~~c++
vector<unique_ptr<SpreadsheetCell>> cellArray;
~~~

矢量的前两个元素指向新建的 StringSpreadsheetCell，第三个元素指向一个新的 DoubleSpreadsheetCell。

~~~c++
cellArray.push_back(make_unique<StringSpreadsheetCell>());
cellArray.push_back(make_unique<StringSpreadsheetCell>());
cellArray.push_back(make_unique<DoubleSpreadsheetCell>());
~~~

现在矢量包含了多类型数据，基类声明的任何方法都可以应用到矢量中的对象。代码只是使用了 SpreadsheetCell 指针——编译器在编译期不知道对象的实际类型是什么。然而，由于这两个类是 SpreadsheetCell 的派生类，因此必须支持 SpreadsheetCell 的方法。
剩下的使用示例略了。

#### 10.4.5 考虑将来

SpreadsheetCell 层次结构的新视线从面向对象设计的观点来看当然是一个进步。但是，对实际的电子表格程序来说，这个类层次结构还不够充分，主要有以下几个原因：
首先，即使不考虑改进设计，现在仍然缺少一个功能：将某个单元格类型转换为其他类型。由于将单元格分为两类，单元格对象的结合变得更松散。为提供将 DoubleSpreadsheetCell 转换为 StringSpreadsheetCell 的功能，应添加一个转换构造函数（或类型构造函数），这个构造函数类似于复制构造函数，但参数不是对同类对象的引用，而是对同级类对象的引用。另外注意，现在必须声明一个默认构造函数，可将其显式设置为默认，因为一旦自行声明仍和构造函数，编译器将停止生成。

~~~c++
class StringSpreadsheetCell : public SpreadsheetCell
{
public:
    StringSpreadsheetCell() = default;
    StringSpreadsheetCell(const DoubleSpreadsheetCell& cell)
        : m_value{cell.getString()}
    {}
// 余下省略
}
~~~

通过转换构造函数，可以方便地用 DoubleSpreadsheetCell 创建 StringSpreadsheetCell。然而不要将其与指针或引用的类型混淆，**类型转换无法将一个指针或引用转换为同级的另一个指针或引用**，除非按照第 15 章讲述的方法重载类型转换运算符。

>**警告：**
>在层次结构中，总可以向上转型，有时也可以向下转型。通过改变类型转换运算符的行为，或者使用 ***reinterpret_cast\<>***（不推荐采用这些方法），就可以在层次结构中进行类型转换。

其次，如何为单元格实现运算符重载是一个很有趣的问题，在此有几种可能的解决方案，其中一种方案是：针对每个单元格组合，实现每个运算符的重载版本，由于只有两个派生类，因此这样做并不难。可编写一个 operator+ 函数，将两个双精度单元格相加，将两个字符串单元格相加，将双精度单元格与字符串单元格相加。另一种方案是给出一种通用表示，前面的实现已将字符串作为标准化的通用类型表示。通过这种通用表示，一个 operator+ 函数就可以处理所有情况。假定两个单元格相加的结果始终是字符串单元格，那么一个在 StringSpreadsheetCell 中的可能的实现如下所示：

~~~c++
StringSpreadsheetCell operator+(const StringSpreadsheetCell& lhs, const StringSpreadsheetCell& rhs)
{
    StringSpreadsheetCell newCell;
    newCell.set(lhs.getString() + rhs.getString());
    return newCell;
}
~~~

只要编译器可将特定的单元格转换为 StringSpreadsheetCell，这个运算符就可以运行。考虑前面的示例，StringSpreadsheetCell 构造函数采用 DoubleSpreadsheetCell 作为参数，如果这是 operator+ 运行的唯一方法，那么编译器将自动执行转换。这意味着下面的代码可以运行，尽管 operator+ 被显式地用于 StringSpreadsheetCell。

~~~c++
DoubleSpreadsheetCell myDbl;
myDbl.set(8.4);
StringSpreadsheetCell result{myDbl + myDbl};
~~~

当然，相加的结果实际上并不是将数字相加，而是将双精度单元格转换为字符串单元格，然后将字符串相加。

### 10.5 多重继承

多重继承通常被认为是面向对象编程中一种复杂且不必要的部分。作者说自己判断这是否有用。

#### 10.5.1 从多个类继承

从语法角度看，定义具有多个父类的类很简单。为此，只需要在声明类名分别列出基类。

~~~c++
class Baz : public Foo, public Bar
{ /* 省略 */
};
~~~

由于列出了多个父类，Baz 对象具有如下特性：

- Baz 对象支持 Foo 和 Bar 类的 public 方法，并且包含这两个类的数据成员。
- Baz 类的方法有权访问 Foo 和 Bar 类的 protected 数据成员和方法。
- Baz 对象可以向上转型为 Foo 或 Bar 对象。
- 创建新的 Baz 对象将自动调用 Foo 和 Bar 类的默认构造函数，并按照类定义中列出的类顺序进行。
- 删除 Baz 对象将自动调用 Foo 和 Bar 类的析构函数，调用顺序与类在类定义中顺序正好相反。

~~~mermaid
classDiagram

class Dog
class Bird
class DogBird

Dog <|-- DogBird
Bird <|-- DogBird
~~~

示例略。
使用就具有多个父类的类对象与使用具有单个父类的类对象没什么不同。实际上，客户代码甚至不需要知道这个类有两个父类。需要关心的只是这个类支持的属性和行为。在此情况下，子类支持父类的所有 public 方法。

#### 10.5.2 名称冲突和歧义基类

多重继承崩溃的场景并不难想象，下面的示例显示了一些必须要考虑的边缘情况。

1. 名称歧义
    如果 Dog 类和 Bird 类都有一个 eat() 方法，会发生什么？由于 Dog 类和 Bird 类毫不相干，eat() 方法的一个版本无法重写另一个版本——在派生类 DogBird 中这两个方法都存在。
    只要客户代码不调用 eat() 方法，就不会出现问题。尽管有两个版本的 eat() 方法，但 DogBird 类仍然可以正确编译，然而，如果客户代码试图调用 DogBird 类的 eat() 方法，编译器将报错，指出对 eat() 方法的调用有歧义。编译器不知道该调用哪个版本。示例代码略。
    为了消除歧义，可使用 dynamic_cast() 显式地将对象向上转型（本质上是向编译器隐藏多余的方法版本），也可以使用歧义消除语法。下面的代码显示了调用 eat() 方法的 Dog 版本的两种方案：

    ~~~c++
    dynamic_cast<Dog&>(myConfuseAnimal).eat();
    myConfuseAnimal.Dog::eat();
    ~~~

    使用与访问父类方法相同的语法（:: 运算符），派生类的方法本身可以显式地为同名的方法消除歧义。比如，DogBIrd 类可以定义自己的 eat() 方法，从而消除其他代码中的歧义错误。在方法内部，可以判断调用哪个父类版本：

    ~~~c++
    class DogBird : public Dog, public Bird
    {
    public:
        void eat() override { Dog::eat(); }
    };
    ~~~

    另一种防止歧义错误的方式是使用 using 语句显式指定，在 DogBird 类中应继承哪个版本的 eat() 方法，如下面的 DogBird 类定义所示。

    ~~~c++
    class DogBird : public Dog, public Bird
    {
    public:
        using Dog::eat;
    };
    ~~~

2. 歧义基类
    另一种引起歧义的情况是从同一个类继承两次。例如，如果处于某种原因 Bird 类从 Dog 类继承，DogBird 类的代码将无法编译，因为 Dog 变成了歧义基类。
    示例略。
    多数歧义基类的情况或者是人为的 “what-if” 示例引起的，或者是由于类层次结构的混乱引起的。下图显示了前面示例中的类图（没有哈），并指出了歧义。

    ~~~mermaid
    classDiagram

    class Dog
    class Bird
    class DogBird

    Dog <|-- Bird
    Bird <|-- DogBird
    Dog <|-- DogBird
    ~~~

    数据成员也可以引起歧义。如果 Dog 和 Bird 类具有同名的数据成员，当客户代码试图访问这个成员时，就会发生歧义错误。
    多个父类本身也可能有共同的父类。例如，Bird 和 Dog 类可能都是 Animal 类的派生类，如下图所示。

    ~~~mermaid
    classDiagram

    class Animal
    class Dog
    class Bird
    class DogBird

    Animal <|-- Dog
    Animal <|-- Bird
    Dog <|-- DogBird
    Bird <|-- DogBird
    ~~~

    C++ 允许这种类型的类层次结构，尽管这样存在着名称歧义。例如，如果 Animal 类还有一个公有方法 sleep()，DogBird 对象无法调用这个方法，因为编译器不知道该调用 Dog 类继承的版本还是 Bird 类继承的版本。
    使用“菱形”类层次结构的最佳方法是**将最顶部的类设置为抽象类，将所有方法都设置为纯虚方法**。由于类只声明方法而不提供定义，在基类中没有方法可以调用，因此在这个层次上就没有歧义。
    下例实现了菱形类层次结构，其中有一个每个派生类都必须定义的纯虚方法 eat()。DogBird 类仍然必须显式说明使用哪个父类的 eat() 方法，但是 Dog 和 Bird 类引起歧义的原因是它们具有相同的方法，而不是因为从同一个类继承。

    ~~~c++
    #include <iostream>

    using namespace std;

    class Animal
    {
    public:
        virtual void eat() = 0;
    };

    class Dog : public Animal
    {
    public:
        virtual void bark() { cout << "Woof!" << endl; }
        void         eat() override { cout << "The dog ate." << endl; }
    };

    class Bird : public Animal
    {
    public:
        virtual void bark() { cout << "Chirp!" << endl; }
        void         eat() override { cout << "The bird ate." << endl; }
    };

    class DogBird : public Dog, public Bird
    {
    public:
        using Dog::eat;
    };
    ~~~

    虚基类是处理菱形类层次结构中顶部类的更好方法，将在本章最后讲述。

3. 多重继承的用途
    为什么程序员要在代码中使用多重继承？多重继承最直接的用例就是定义一个既“是一个”事物，又“是一个”其他事物的类对象。第 5 章已经说过，遵循这个模式的实际对象很难恰当地转换为代码。
    多重继承最简单有力的用途就是实现混入（mix-in）类。混入类的介绍在第 5 章，更多详细在第 32 章“整合设计技术和框架”。
    使用多重继承的另一个原因是给基于组件的类建模。第 5 章给出了飞机模拟示例，Airplane 类有引擎、机身、控制系统和其他组件。尽管 Airplane 类的典型实现是将这些组件当作独立的数据成员，但也可以使用多重继承。飞机类可从引擎、机身、控制系统继承，从而有效地获得这些组件的行为和属性。建议不要使用这种类型的代码，这将“有一个”关系与继承混淆了，而继承用于“是一个”关系。推荐的解决方案是让 Airplane 类包含 Engine、Fuselage 和 Controls 类型的数据成员。

### 10.6 有趣而晦涩的继承问题

扩展类引发了多种问题。类的哪些特征可以改变。类的哪些特征可以改变，哪些不能改变？什么是非公共继承？什么是虚基类？下面将回答这些问题。

#### 10.6.1 修改重写方法的返回类型

重写某个方法的主要原因是为了修改方法的实现。然而，有时是为了修改方法的其他特征，比如返回类型。
根据经验，重写方法要使用与基类一致的方法声明（或方法原型）。实现可以改变，但原型保持不变。
然而事实未必总是如此，在 C++ 中，如果原始的返回类型是某个类的指针或引用，重写的方法可将返回类型改为派生类的指针或引用。这种类型称为协变返回类型（covariant return types）。如果基类和派生类处于平行层次结构（parallel hierarchy）中，使用这个特性可以带来便利。平行层次结构是指，一个类层次结构与另一个类层次结构没有相交，但是存在联系。
例如，考虑樱桃果园的模拟程序。可使用两个类层次结构模拟不同但明显相关的实际对象。第一个是 Cherry 类层次结构，Cherry 基类有一个 BingCherry 的派生类。与此类似，另一个类层次结构的基类为 CherryTree，派生类为 BingCherryTree。下图显示了这两个类层次结构。

~~~mermaid
classDiagram

class Cherry
class BingCherry
class CherryTree
class BingCherryTree

Cherry <|-- BingCherry
CherryTree <|-- BingCherryTree
~~~

现在假定 CherryTree 类有一个虚方法 pick()，这个虚方法从樱桃树上获取一个樱桃：

~~~c++
Cherry* CherryTree::pick()
{
    return new Cherry{};
}
~~~

>**注意：**
>为了演示如何更改返回类型，本例未返回智能指针，而是返回普通指针。本节结尾将解释其中的原因。当然，调用者应当在智能指针（而非普通指针）中立即存储结果。

在 BingCherryTree 派生类中，要重写这个方法。或许 BingCherry 在摘下来时需要擦拭（作者说请允许我们这么说）。由于 BingCherry 也是Cherry，在下例中，方法的原型保持不变，而方法却被重写。BingCherry 指针被自动转换为 Cherry 指针。注意，这个实现使用 unique_ptr 确保当 polish() 抛出异常时，没有泄漏内存。

~~~c++
Cherry* BingCherryTree::pick()
{
    auto theCherry{make_unique<BingCherry>()};
    theCherry->polish();
    return theCherry.release();
}
~~~

上面的实现非常好。然而，由于 BingCherryTree 类始终返回 BIngCherry 对象，因此可通过修改返回类型，向这个类的潜在用户指明这一点，如下所示：

~~~c++
BingCherry*BingCherryTree::pick()
{
    auto theCherry{make_unique<BingCherry>()};
    theCherry->polish();
    return theCherry.release();
}
~~~

下面的示例显式了 BingCherryTree:;pick() 方法的用法。printType() 是基类 Cherry 的虚方法，有 BingCherryTree 派生类的重写，用于输出 cherry 的类型。

~~~c++
BingCherryTree     theTree;
unique_ptr<Cherry> theCherry{theTree.pick()};
theCherry->printType();
~~~

为判断能否修改重写方法的返回类型，可以考虑已有代码是否能够继续运行，这里称为里氏替换原则（LSP）。在上例中，修改返回类型没有问题，因为假定 pick() 方法总是返回 Cherry\* 的代码仍然可以成功编译并正常运行。由于 BingCherry 也是 Cherry，因此根据 CherryTree 版本的 pick() 返回值调用的任何方法，仍然可以基于 BingCherryTree 版本的 pick() 返回值进行调用。
不能将返回类型修改为完全不相关的类型，例如 void*。下面的代码无法编译：

~~~c++
void* BingCherryTree::pick()
{}   // 编译不通过
~~~

这段代码会导致编译错误。
如前所述，这个示例正用普通指针替代智能指针。将 unique_ptr 用作返回类型时，这不能用于本例。假设 CherryTree::pick() 方法返回 unique_ptr\<Cherry>，如下所示：

~~~c++
unique_ptr<Cherry> CherryTree::pick()
{
    return make_unique<Cherry>();
}
~~~

此时，无法将 BingCherry::pick() 方法的返回类型改成 unique_ptr\<BingCherry>。下面的代码无法编译：

~~~c++
unique_ptr<BingCherry> CherryTree::pick() override   // 编译不通过
{
    /* ... */
}
~~~

愿意在于 unique_ptr 是类模板。创建了 unique_ptr 类模板的两个实例 unique_ptr\<Cherry> 和 unique_ptr\<BingCherry>。这两个实例是完全不同的类型，完全无关，无法更改重写方法的返回类型来返回完全不同的类型。

#### 10.6.2 派生类中添加虚基类方法的重载

可以向派生类中添加虚基类方法的新重载。也就是说，可以使用新原型在派生类中添加虚方法的重载，但继续继承基类版本。该技术使用 using 声明将方法的基类定义显式包含在派生类中。实例如下：

~~~c++
class Base
{
public:
    virtual void someMethod();
};

class Derived : public Base
{
public:
    using Base::someMethod;           // 显式地继承基类的版本
    virtual void someMethod(int i);   // 添加一个新的继承方法
    virtual void someOtherMethod(int i);
};
~~~

>**注意：**
>对于派生类和基类同名的方法，具有不同参数列表的情况很少见。

#### 10.6.3 继承的构造函数

上一节提到，可以在派生类中使用 using 关键字显式地包含基类中定义的方法。这适用于普通类方法，也适用于构造函数。考虑以下 Base 和 derived 类定义：

~~~c++
#include <string>

class Base
{
public:
    virtual ~Base() = default;
    Base()          = default;
    Base(std::string_view str);
};

class Derived : public Base
{
public:
    Derived(int i);
};
~~~

只能用提供的 Base 构造函数构建 Base 对象，要么是默认构造函数，要么是包含 string_view 参数的构造函数。另外，只能用 Derived 构造函数创建 Derived 对象，这个构造函数需要一个整数作为参数。不能使用 Base 类中接收 string_view 的构造函数构建 Derived 对象，例如：

~~~c++
Base    base{"Hello"};
Derived derived1{1};
Derived derived2{"Hello"};   // 编译不通过
Derived derived2;            // 编译不通过
~~~

如果喜欢使用基于 string_view 的 Base 构造函数构建 Derived 对象，可在 Derived 类中显式地继承 Base 构造函数，如下所示：

~~~c++
class Derived : public Base
{
public:
    using Base::Base;
    Derived(int i);
};
~~~

**using 语句从父类继承除默认构造函数外的其他所有构造函数**，现在可通过下面两种方法构建 Derived 对象。

~~~c++
Derived derived1{1};
Derived derived2{"Hello"};
Derived derived2;
~~~

当然，Derived 类可以从所有 Base 类中继承构造函数，而不定义任何构造函数。实例如下：

~~~c++
class Base
{
public:
    virtual ~Base() = default;
    Base()          = default;
    Base(std::string_view str);
    Base(float f);
};

class Derived : public Base
{
public:
    using Base::Base;
};
~~~

可以如下创建 Derived 类的实例：

~~~c++
Derived derived1{"Hello"};
Derived derived2{1.23f};
Derived derived3;
~~~

1. 隐藏继承的构造函数
    定义的构造函数可与从 Base 类继承的构造函数有相同的参数列表。与所有的重写一样，此时 Derived 类的构造函数的优先级高于继承的构造函数。在下例中，Derived 类使用 using 关键字，继承了 Base 类中除默认构造函数外的其他所有构造函数。然而，由于 Derived 类定义了一个使用浮点数作为参数的构造函数，从 Base 类继承的使用浮点数作为参数的构造函数被重写。

    ~~~c++
    class Base
    {
    public:
        virtual ~Base() = default;
        Base()          = default;
        Base(std::string_view str);
        Base(float f);
    };

    class Derived : public Base
    {
    public:
        using Base::Base;
        Derived(float f);   // 隐藏了基类的方法
    };
    ~~~

    根据这个定义，可用下面的代码创建 Derived 对象：

    ~~~c++
    Derived derived1{"Hello"};   // 通过，调用基类方法
    Derived derived2{1.23f};     // 通过，调用 Derived 的方法
    Derived derived3;            // 通过，调用基类方法
    ~~~

    使用 using 自居从基类继承构造函数有一些限制。

    - 当从基类继承构造函数时，会继承除默认构造函数外的其他全部构造函数，不能只是继承基类构造函数的一个子集。
    - 当继承构造函数时，无论 using 声明位于哪个访问规范下，都将使用与基类中相同的访问规范来继承。

2. 继承的构造函数和多重继承
    第二个限制于多重继承有关。如果一个基类的某个构造函数与另一个基类的构造函数具有相同的参数列表，就不可能从基类继承构造函数，因为那样会导致歧义。为解决这个问题，Derived 类必须显式地定义冲突的构造函数。例如，下面的 Derived 类试图继承 Base1 和 Base2 基类的所有构造函数，这鬼导致编译错误，因为使用浮点是作为参数的构造函数存在歧义。

    ~~~c++
    class Base1
    {
    public:
        virtual ~Base1() = default;
        Base1()          = default;
        Base1(float f);
    };

    class Base2
    {
    public:
        virtual ~Base2() = default;
        Base2()          = default;
        Base2(std::string_view str);
        Base2(float f);
    };

    class Derived : public Base1, public Base2
    {
    public:
        using Base1::Base1;
        using Base2::Base2;
        Derived(char c);
    };

    int main()
    {
        Derived d{1.2f};   // 错误
    }
    ~~~

    Derived 类定义中的第一条 using 语句继承了 Base1 类的构造函数。这意味着 Derived 类具有如下构造函数：

    ~~~c++
    Derived{float f};
    ~~~

    Derived 类定义中的第二条 using 子句试图继承 Base2 类的全部构造函数。然而，这会导致编译错误，因为这意味着 Derived 类拥有第二个 Derived(float f) 构造函数。为解决这个问题，可在 Derived 类中显式声明冲突的构造函数，如下所示。

    ~~~c++
    class Derived : public Base1, public Base2
    {
    public:
        using Base1::Base1;
        using Base2::Base2;
        Derived(char c);
        Derived(float f);
    };
    ~~~

    现在，Derived 类显式地声明了一个采用浮点数作为参数的构造函数。从而解决了歧义问题。如果愿意，在 Derived 类中显式声明的使用浮点数作为参数的构造函数仍然可以在 ctor-initializer 中调用 Base1 和 Base2 构造函数，如下所示：

    ~~~c++
    Derived::Derived(float f)
        : Base1{f}
        , Base2{f}
    {}
    ~~~

3. 数据成员的初始化
    当使用继承的构造函数时，要确保所有成员变量都正确地初始化。比如，考虑下面 Base 和 Derived 类的新定义。这个示例没有正确地初始化 m_int 数据成员，在任何情况下这都是一个严重错误。

    ~~~c++
    class Base
    {
    private:
        std::string m_str;

    public:
        virtual ~Base() = default;
        Base(std::string_view str)
            : m_str{str}
        {}
    };

    class Derived : public Base
    {
    private:
        int m_int;

    public:
        using Base::Base;
        Derived(int i)
            : Base{""}
            , m_int{i}
        {}
    };
    ~~~

    可采用如下方法创建一个 Derived 对象：

    ~~~c++
    Derived s1{2};
    ~~~

    这条语句将调用 Derived(int i) 构造函数，这个构造函数将初始化 Derived 类的 m_int 数据成员，并调用 Base 构造函数，用空字符串初始化 m_str 数据成员。
    由于 Derived 类继承了 BAse 构造函数，还可按下面的方式创建一个 Derived 对象：

    ~~~c++
    Derived s2{"Hello World"};
    ~~~

    这条语句调用从 Base 类继承的构造函数。然而，从 Base 类继承的构造函数只初始化了 Base 类的 m_str 成员变量，没有初始化 Derived 类的 m_int 成员变量，m_int 处于未初始化状态。通常不建议这么做。
    解决方法时使用类内成员初始化器，第 8 章已讨论此特性。以下代码使用类内成员初始化器将 m_int初始化为 0。Derived(int i) 构造函数仍可修改这一初始化行为，将 m_int初始化为 参数 i 的值。

    ~~~c++
    class Derived : public Base
    {
    private:
        int m_int{0};

    public:
        using Base::Base;
        Derived(int i)
            : Base{""}
            , m_int{i}
        {}
    };
    ~~~

#### 10.6.4 重写时的特殊情况

当重写方法时，需要注意几种特殊情况。本节将列出可能遇到的一些情况。

1. 静态基类方法
    在 C++ 中，不能重写静态方法。对于多数情况而言，知道这一点就足够了。然而，在此需要了解一些推论。
    首先，方法不可能既是静态的又是虚的。出于这个原因，试图重写一个静态方法并不能得到预期的结果。如果派生类中存在的静态方法与基类中的静态方法同名，实际上这是两个独立的方法。
    下面的代码显示了两个类，这两个类都有一个名为 beStatic() 的静态方法。这两个方法毫无关系。

    ~~~c++
    class BaseStatic
    {
    public:
        static void beStatic() { cout << "BaseStatic being static." << endl; }
    };

    class DerivedStatic : public BaseStatic
    {
    public:
        static void beStatic() { cout << "DerivedStatic keepin' it static." << endl; }
    };
    ~~~

    由于静态方法属于类，因此调用两个类的同名方法时，将调用各自的方法。

    ~~~c++
    BaseStatic::beStatic();
    DerivedStatic::beStatic();
    ~~~

    输出略，调用各自方法。
    用类名访问这些方法时一切都很正常。当设计对象时，这一行为就不是那么明显。在 C++ 中，可以使用对象调用静态方法，但由于方法是静态的，因此没有 this 指针，也无法访问对象本身，使用对象调用静态方法，等价于使用 classname::method() 调用静态方法。回到前面的示例，可以编写如下代码，但结构令人惊讶。

    ~~~c++
    DerivedStatic myDerivedStatic;
    BaseStatic&   ref{myDerivedStatic};
    myDerivedStatic.beStatic();
    ref.beStatic();
    ~~~

    对 beStatic() 的第一次调用显然调用了 DerivedStatic 版本，因为调用它的对象被显式地声明为 DerivedStatic 对象。第二次调用的运行方式可能并非预期的那样。这个对象是一个 BaseStatic 引用，但指向的是一个 DerivedStatic 对象。在此情况下，会调用 BaseStatic 版本的 beStatic()。原因是当调用静态方法时，C++ 不关心对象实际上是什么，只关心编译期的类型。在此情况下，该类型为指向 BaseStatic 对象的引用。
    输出结果略。

    >**注意：**
    >静态方法属于定义它的类，而不属于特定的对象。当类中的方法调用静态方法时，所调用的版本是通过正常的名称解析来决定的。当使用对象调用时，对象实际上并不涉及调用，只是用来判断编译期的类型。

2. 重载基类方法
    当指定名称和一组参数以重写某个方法时，编译器隐式地隐藏基类中同名的所有其他实例。想法为：如果重写类给定名称的某个方法，可能是想重写所有的同名方法，只是忘记这么做了，因此应该作为错误处理。这是有意义的，可以这么考虑——为什么要修改方法的某些版本而不修改其他版本呢？考虑下面的 Derived 类，它重写了一个方法，而没有重写相关的同级重载方法。

    ~~~c++
    class Base
    {
    public:
        virtual ~Base() = default;
        virtual void overload() { cout << "Base's overload()" << endl; }
        virtual void overload(int i) { cout << "Base's overload(int i)" << endl; }
    };

    class Derived : public Base
    {
    public:
        void overload() override { cout << "Derived's overload()" << endl; }
    };
    ~~~

    如果试图用 Derived 对象调用以 int 值作为参数的 overload() 版本，代码将无法编译，因为没有显式地重写这个方法。

    ~~~c++
    Derived myDerived;
    myDerived.overload(2);   // 编译不通过
    ~~~

    然而，使用 Derived 对象访问该版本的方法是可行的。只需要使用指向 Base 对象的指针或引用。

    ~~~c++
    Derived myDerived;
    Base&   ref{myDerived};
    ref.overload(7);
    ~~~

    在 C++ 中，隐藏未实现的重载方法只是表象。显式声明为子类型实例的对象无法使用这些方法，但可将其转换为积累类型，以使用这些方法。
    如果指向改变一个方法，可以使用 using 关键字避免重载该方法的所有版本。在下面的代码中，Derived 类定义中使用了从 Base 类继承的一个 overload() 版本，并显式地重写了另一个版本。

    ~~~c++
    class Derived : public Base
    {
    public:
        using Base::overload;
        void overload() override { cout << "Derived's overload()" << endl; }
    };
    ~~~

    using 子句存在一定风险。假定在 Base 类中添加了第三个 overload()，本来应该在 Derived 类中重写这个方法。但由于使用了 using 子句，在派生类中没有重写这个方法不会被当作错误，Derived 类显式地说明“接收父类其他所有的重载方法”。

    >**警告：**
    >为了避免歧义 bug，应该重写所有版本的重载方法。

3. 基类的 private 方法
    重写 private 方法当然没有问题。记住方法的访问说明符会判断谁可以调用这些方法。派生类无法调用父类的 private 方法，并不意味着无法重写这个方法。实际上，在 C++ 中，重写 private 方法是一种常见模式。这种模式允许派生类定义自身的“独特性”，在基类中会引用这种独特性，注意 Java 和 C# 允许重写 public 和 protected 方法，但不能重写 private 方法。
    例如，下面的类是汽车模拟程序的一部分，根据汽油消耗量和剩余的燃料计算汽车可以形式的里程。getMilesLeft() 是所谓的模板方法。通常，模板方法都不是虚方法。模板方法通过在基类中定义一些算法的骨架，并调用虚方法来完成相关信息的查询。在子类中，可以重写这些虚方法，并修改相关算法而不会真正修改基类中已定义的算法。

    ~~~c++
    class MileEstimator
    {
    public:
        virtual ~MileEstimator() = default;
        int          getMilesLeft() const { return getMilePerGallon() * getMilesLeft(); }
        virtual void setGallonsLeft(int gallons) { m_gallonsLeft = gallons; }
        virtual int  getGallonsLeft() const { return m_gallonsLeft; }

    private:
        int         m_gallonsLeft{0};
        virtual int getMilePerGallon() const { return 20; }
    };
    ~~~

    getMilesLeft() 方法根据两个方法的返回结果执行计算。下面的代码使用 MilesEstimator 计算两加仑汽油可以行驶的里程：

    ~~~c++
    MileEstimator myMilesEstimator;
    myMilesEstimator.setGallonsLeft(2);
    cout << format("Normal estimator can go {} more miles.", myMilesEstimator.getMilesLeft())
         << endl;
    ~~~

    代码输出结果略。
    为让这个模拟程序更加有趣，可引入不同类型的车辆，或许是效率更高的汽车。现有的 MIleEstimator 假定所有的汽车燃烧一加仑的汽油可以跑 20 公里，这个值是从一个单独的方法返回的，因此派生类可以重写这个方法。下面就是这样一个派生类：

    ~~~c++
    class EfficientCarMileEstimator : public MileEstimator
    {
    private:
        int getMilesPerGallon() const override { return 35; }
    };
    ~~~

    通过重写这个 private 方法，新类完全修改了没有更改的现有 public 方法的行为。基类中的 getMileLeft() 方法将自动调用private getMilesPerGallon() 方法的重写版本。下面是一个使用新类的示例：

    ~~~c++
    EfficientCarMileEstimator myEstimator;
    myEstimator.setGallonsLeft(2);
    cout << format("Efficient estimator can go {} more miles.", myEstimator.getMilesLeft()) << endl;
    ~~~

    输出结果略。
    >**注意：**
    >重写 private 或 protected 方法可在不做重大改动的情况下改变类的某些特性。

4. 基类方法具有默认参数
    派生类与基类可以具有不同的默认参数，但使用的参数取决于声明的变量类型，而不是底层的对象。下面是一个简单的派生类示例，派生类在重写的方法中提供了不同的默认参数。

    ~~~c++
    class Base
    {
    public:
        virtual ~Base() = default;
        virtual void go(int i = 2) { cout << "Base's go with i=" << i << endl; }
    };

    class Derived : public Base
    {
    public:
        void go(int i = 7) override { cout << "Derived' go with i=" << i << endl; }
    };
    ~~~

     如果调用 Derived 对象的 go()，将执行 Derived 版本的 go()，默认参数为 7。如果调用 Base 对象的 go()，将执行 Base 版本的 go()，默认参数为 2.然而（有些怪异），如果使用实际指向 Derived 对象的 Base 指针或 Base 引用调用 go()，将调用 Derived 版本的 go()，但实际使用 Base 版本的默认参数 2。下面的示例显示了这种行为：

    ~~~c++
    Base    myBase;
    Derived myDerived;
    Base&   myBaseReferenceToDerived{myDerived};

    myBase.go();
    myDerived.go();
    myBaseReferenceToDerived.go();
    ~~~

    代码的输出结果略。
    产生这种行为的原因是 C++ 根据表达式的编译期类型（而非运行期类型）绑定默认参数。在 C++ 中，**默认参数不会被“继承”**。如果上面的 Derived 类没有像父类那样提供默认参数，就用新的非零参数版本重载 go() 方法。

    >**注意：**
    >**当重写具有默认参数的方法时，也应该提供默认参数，这个参数的值应该与基类版本相同**。建议使用命名的常量作为默认值，这样可在派生类中使用同一个命名的常量。

5. 基类方法具有不同的访问级别
    可以采用两种方法修改方法的访问级别——可以加强限制，也可放宽限制。在 C++ 中，这两种方法的意义都不大，但是这么做也是有合理原因的。
    为加强某个方法（或数据成员）的限制，有两种方法。一种方法是修改整个基类的访问说明符，本章后面将讲述这种方法。另一种是在派生类种重新定义访问限制，下面的 Shy 类演示了这种方法：

    ~~~c++
    class Gregarious
    {
    public:
        virtual void talk() { cout << "gregarious says hi!" << endl; }
    };

    class Shy : public Gregarious
    {
    protected:
        void talk() override { cout << "Shy reluctantly says hello." << endl; }
    };
    ~~~

    Shy 类种 protected 版本的 talk() 方法适当地重写 Gregarious::talk() 方法。任何客户代码试图使用 Shy 对象调用 talk() 都会导致编译错误。

    ~~~c++
    Shy myShy;
    myShy.talk();   // 编译错误，不可访问
    ~~~

    然而，这个方法并不是完全受保护的。可使用 Gregarious 引用或指针访问 protected 方法。

    ~~~c++
    Shy        myShy;
    Gregarious ref{myShy};
    ref.talk();
    ~~~

    输出略。
    这说明在派生类中将方法设置为 protected 实际上是重写了这个方法（因为可以正确地调用这个方法的派生类版本），此外还证明如果基类将方法设置为 public，就无法完整地强制访问 protected 方法。

    >**注意：**
    >无法（也没有很好的理由）限制访问基类的 public 方法。

    ---

    >**注意：**
    >上例重新定义了派生类中的方法，因为它希望显示另一条消息。如果不希望修改实现，指向改变方法的访问级别，首选方法是在具有所需访问级别的派生类定义中添加 using 语句。

    在派生类中放宽访问限制就比较容易（也更有意义）。最简单的方法是提供一个 public 方法来调用基类的 protected 方法，如下所示：

    ~~~c++
    class Secret
    {
    protected:
        virtual void dontTell() { cout << "I'll never tell." << endl; }
    };

    class Blabber : public Secret
    {
    public:
        virtual void tell() { dontTell(); }
    };
    ~~~

    调用 Blabber 对象的 public 方法 tell() 的客户代码可有效地访问 Secret 类的 protected 方法。当然，这并未整整改变 dontTell() 的访问级别，只是提供了访问这个方法的公共方式。
    也可在 Blabber 派生类中显式地重写 dontTell()，并将这个方法设置为 public。这样做比降低访问级别更有意义，因为当使用基类指针或引用时，可以清楚地表明发生的事情。例如，假定 Blabber 类实际上将 dontTell() 方法设置为 public：

    ~~~c++
    class Blabber : public Secret
    {
    public:
        void dontTell() override { cout << "I'll tell all!" << endl; }
    };
    ~~~

    现在调用 Blabber 对象 的 dontTell() 方法：

    ~~~c++
    Blabber myBlabber;
    myBlabber.dontTell();   // Outputs "I'll tell all!"
    ~~~

    如果不想更改重写方法的实现，只想更改访问级别，可使用 using 子句。例如：

    ~~~c++
    class Blabber : public Secret
    {
    public:
        using Secret::dontTell;
    };
    ~~~

    这也允许调用 Blabber 对象的 dontTell() 方法，但这一次，输出将会是“ I'll never
     tell”。

    ~~~c++
    myBlabber.dontTell();   // Outputs "I'll never tell!"
    ~~~

    然而，在上述情况下，基类中的 protected 方法仍然时受保护的，因为使用 Secret 指针或引用调用 Secret 类的 dontTell() 方法将无法通过编译。

    ~~~c++
    Blabber myBlabber;
    Secret& ref{myBlabber};
    Secret* ptr{&myBlabber};
    ref.dontTell();    // 编译不通过
    ptr->dontTell();   // 编译不通过
    ~~~

    >**注意：**
    >修改方法访问级别的唯一真正有用的方式是对 protected 方法提供较宽松的访问限制。

#### 10.6.5 派生类中的复制构造函数和赋值运算符

第 9 章讲过，在类中使用动态内存分配时，提供复制构造函数和赋值运算符是良好的编程习惯。当定义派生类时，必须注意复制构造函数和 operator=。
如果派生类没有任何需要使用非默认复制构造函数或 operator= 的特殊数据（通常是指针），无论基类是否有这类数据，都不需要它们。如果派生类省略了复制构造函数或 operator=，派生了中指定的数据成员就使用默认的复制构造函数或 operator=，基类中的数据成员使用基类的复制构造函数或 operator=。
另外，如果在派生类中制定了复制构造函数，就需要显式地链接到父类的复制构造函数，下面的代码演示了这一内容。如果不这么做，将使用默认构造函数（不是复制构造函数！）初始化对象的父类部分。

~~~c++
class Base
{
public:
    virtual ~Base() = default;
    Base()          = default;
    Base(const Base& src){};
};

class Derived : public Base
{
public:
    Derived() = default;
    Derived(const Derived& src)
        : Base{src}
    {}
};
~~~

与此类似，如果派生类重写了 operator=，则几乎总是需要调用父类版本的 operator=。唯一的例外是因为某些奇怪的原因，在赋值时指向给对象的一部分赋值。下面的代码显示了如何在派生类中调用父类的赋值运算符。

~~~c++
Derived& Derived::operator=(const Derived& rhs)
{
    if (&rhs == this) {
        return *this;
    }
    Base::operator=(rhs);   // 调用父类的赋值运算符
    return *this;
}
~~~

>**警告：**
>如果派生类不指定自己的复制构造函数或 operator=，基类的功能将继续运行，否则，就需要显式引用基类版本。

---

>**注意：**
>如果在继承层次结构中需要复制功能，专业 C++ 开发人员惯用的做法时实现多态 clone() 方法，因为不能完全依靠标准复制构造函数和复制运算符类满足需要。第 12 章“使用模板编写泛型代码”将讨论多态的 clone() 方法。

#### 10.6.6 运行期类型工具

相对于其他面向对象语言，C++ 以编译期为主。如前所述，重写方法时可行的，这是由于方法和实现之间的间隔，而不是由于对象有关于自身所属类的内建信息。
然而在 C++ 中，有些特性提供了对象的运行期视角。这些特性通常归属于一个名为运行期类型信息（Run Time Type Information, RTTI）的特性集。RTTI 提供了许多有用的特性，用于判断对象所属的类。其中一个特性时本章前面说过的 dynamic_cast()，可以在 OO 层次结构中进行安全的类型转换，本章前面讨论过这一点。如果使用类上的 dynamic_cast()，但没有虚表，即没有虚方法，将导致编译错误。
RTTI 的第二个特性是 typeid 运算符，这个运算符可在运行期查询对象，从而判别对象的类型。大多数情况下，不应该使用 typeid，因为最好用虚方法处理基于对象类型运行的代码。下面的代码使用了 typeid，根据对象的类型输出消息。

~~~c++
#include <iostream>
#include <typeinfo>

using namespace std;

class Animal
{
public:
    ~Animal() = default;
};
class Dog : public Animal
{};
class BIrd : public Animal
{};

void speak(const Animal& animal)
{
    if (typeid(animal) == typeid(Dog)) {
        cout << "Woff!" << endl;
    }
    else if (typeid(animal) == typeid(BIrd)) {
        cout << "Chirp!" << endl;
    }
}
~~~

一旦看到这样的代码，就应该立即考虑用虚方法重新实现该功能。在此情况下，更好的实现是在 Animal 类中声明一个 speak() 虚方法。Dog 类会重写这个方法，输出“Woof!”；Bird 类也会重写这个方法，输出“Chirp!”。这种方式更适合面向对象程序，会将与对象有关的功能给予这些对象。

>**警告：**
>类至少有一个虚方法（即类具有一张虚函数表），typeid 运算符才能正常运行。另外，typeid 运算符也亏从实参中取出引用和 const 限定符。

typeid 运算符的主要价值之一在于日志记录和调试。下面的代码将 typeid 用于日志记录。logObject() 函数将“可记录”对象作为参数。设计是这样的：任何可记录的对象都从 Loggable 类中继承，都支持 getLogMessage() 方法。


~~~c++
class Loggable
{
public:
    virtual ~Loggable()                       = default;
    virtual std::string getLogMessage() const = 0;
};

class Foo : public Loggable
{
public:
    std::string getLogMessage() const override { return "Hello logger."; }
};

void logObject(const Loggable& loggableObject)
{
    cout << typeid(loggableObject).name() << ": ";
    cout << loggableObject.getLogMessage() << endl;
}
~~~

logObject() 函数首先将对象所属类的名称写道输出流，随后是日志信息。这样以后阅读日志时，就可以看出文件每一行涉及的对象。输出结果略。

>**注意：**
>如果不是为了日志记录或调试而使用 typeid，应该考虑用虚方法替代 typeid。

#### 10.6.7 非 public 继承

在前面的所有示例中，总是用 public 关键字列出父类。父类是否可以是 private 或 protected？实际上可以这样做，尽管二者并不像 public 那样普遍。如果没有为父类指定任何访问说明符，就说明是类的 private 继承、结构的 public 继承。
将父类的关系声明为 protected，意味着在派生类中，基类的所有 public 方法和数据成员都称为受保护的。与此类似，指定 private 继承意味着基类的所有 public、protected 方法和数据成员在派生类中都成为私有的。
使用这种方法统一降低父类的访问级别有许多原因，但多数原因都是层次结构的设计缺陷。有些程序员滥用这一语言特性，经常与多重继承一起实现类的“组件”。不是让 Airplane 类包含引擎数据成员和机身数据成员，而将 Airplane 类作为 protected 引擎和 protected 机身。这样，对于客户代码来说，Airplane 对象看上去并不像引擎或机身（因为一切都是受保护的），但在内部可以使用引擎和机身的功能。

>**注意：**
>非 public 继承很少见，建议慎用这一特性，因为多数程序员并不熟悉它。

#### 10.6.8 虚基类

本章前面学习了歧义父类，当多个基类拥有公共父类时，就会发生这种情况，如图所示。

~~~mermaid
classDiagram
class Animal
class Dog
class Bird
class DogBird

Animal <|-- Dog
Animal <|-- Bird
Dog <|-- DogBird
Bird <|-- DogBird
~~~

建议的解决方案是让共享的父类本省没有任何自有功能。这样就永远无法调用这个类的方法，因此也就不存在歧义。
如果希望被共享的父类拥有自己的功能，C++ 提供了另一种机制来解决这个问题。如果被共享的基类是一个虚基类（virtual base class），就不存在歧义。以下代码在 Animal 基类中添加了 sleep() 方法，并修改了 Dog 和 Bird 类，从而将 Animal 作为虚基类继承。如果不使用 virtual 关键字，用 DogBird 对象调用 sleep() 会产生歧义，从而导致编译错误。因为 DogBird 对象有 Animal 类的两个子对象，一个来自 Dog 类，另一个来自 Bird 类。然而，如果 Animal 被作为虚基类，DogBird 对象就只有 Animal 类的一个子对象，因此调用 sleep() 也就不存在歧义。

~~~c++
#include <iostream>

using namespace std;

class Animal
{
public:
    virtual void eat() = 0;
    virtual void sleep() { cout << "zzzzz...." << endl; }
};

class Dog : public virtual Animal
{
public:
    virtual void bark() { cout << "Woof!" << endl; }
    void         eat() override { cout << "The dog ate." << endl; }
};

class Bird : public virtual Animal
{
public:
    virtual void chirp() { cout << "Chirp!" << endl; }
    void         eat() override { cout << "The bird ate." << endl; }
};

class DogBird : public Dog, public Bird
{
public:
    void eat() override { Dog::eat(); }
};

int main()
{
    DogBird myConfusedAnimal;
    myConfusedAnimal.sleep();
}
~~~

>**注意：**
>虚基类是在类层次结构中避免歧义的好办法。唯一的缺点是许多 C++ 程序员不熟悉这个概念。

### 10.7 类型转换

第 1 章介绍了 C++ 中的基本类型，而第 8~10 章介绍了使用类编写自定义的类型。本届将探讨如何将一种类型转换为另一种类型。
C++ 提供了 5 种特定的强制类型转换：const_cast()、static_cast()、reinterpret_cast()、dynamic_cast() 和 std::bit_cast()（从 C++20 开始）。const_cast() 在第一章进行了讨论。第 1 章还介绍了 static_cast()，用于在某些基本类型之间进行转换，但在继承的上下文中，还有更多内容要介绍。监狱已经能够熟练地编写类并了解类的继承，现在仔细研究这些强制类型转换。
注意，旧的 C 风格的强制类型转换仍可以在 C++ 中使用，并且仍在现有代码库中广泛使用。C 风格的强制类型转换涵盖了所有 4 中 C++ 强制类型转换，因此它们更容易出错，因为要实现的目标并不总是很明显，并且最终可能会带来意想不到的结果。强烈建议仅在新代码中使用 C++ 风格的强制转换，因为它们更安全，并且在代码中在语法上更加突出。

#### 10.7.1 static_cast()

可以使用 static_cast() 执行语言直接支持的显式转换。比如，如果编写一个算术表达式，需要将 int 转换为 double 以避免整数除法，则可以使用 static_cast()。在本例中，只对 i 使用 static_cast() 就足够了，因为这回事两个操作数中的一个变成双精度，从而确保 C++ 执行浮点数除法。

~~~c++
int    i{3};
int    j{4};
double result{static_cast<double>(i) / j};
~~~

还可以使用 static_cast() 执行显式转换，这是用户定义的构造函数或转换例程允许的。比如，如果类 A 有一个接受 B 对象的构造函数，则可以使用 static_cast() 将 B 对象转换为 A 对象。但是，在大多数情况下，需要这种行为时，编译器会自动执行转换。
static_cast() 的另一个用途是在继承层次结构中执行向下强制转换，示例如下：

~~~c++
Base*    b{nullptr};
Derived* d{new Derived{}};
b = d;
d = static_cast<Derived*>(b);

Base     base;
Derived  derived;
Base&    br{derived};
Derived& dr{static_cast<Derived&>(br)};
~~~

这些强制类型转换既可以使用指针也可以使用引用。它们不使用对象。
注意，使用 static_cast() 的强制类型转换不会执行运行期类型检查，它们允许将任何 Base 指针转换为 Derived 指针，或是将 Base 引用转换为 Derived 引用。即使在运行期，Base 实际上不是 Derived 也是如此。比如编译并执行以下代码，但使用指针 d 可能会导致潜在的灾难性故障，包括在对象边界之外进行内存覆盖。

~~~c++
Base*    b{new Base{}};
Derived* d{static_cast<Derived*>(b)}
~~~

要在运行期检查时安全地执行转换，请使用 dynamic_cast()，本章稍后对此进行说明。
static_cast() 不是万能的。不能将一种类型的指针 static_cast() 转换为另一种不相关类型的指针；如果没有可用的转换构造函数，则无法将一种类型的对象直接 static_cast() 转换为另种类型的对象；不能将常量类型的 static_cast() 转换为非常量类型；不能将指针 static_cast() 转换为整数。基本上，根据 C++ 的类型规则，不能做任何没有意义的事情。

#### 10.7.2 reinterpret_cast()

与 static_cast() 相比，reinterpret_cast() 的功能更强大，同时安全性也更低。可以使用它执行 C++ 类型规则中在技术上不允许的某些强制转换，但在某些情况下，这对程序员来说可能是由意义的。比如，即使类型不相关，也可以将一种类型的引用强制转换为对另一种类型的引用。同样，可以将指针类强制转换为任何其他指针类型，即使它们与继承层次结构无关。这通常用于将指针强制转换为 void\* 类型的指针。这可以隐式完成，因此不需要显式强制转换。但是，将 void* 强制转换回正确类型的指针需要 reinterpret_cast()。void\* 类型的指针只是指向内存中的某个位置。没有类型信息与 void\* 类型的指针相关联。示例如下：

~~~c++
class X
{};
class Y
{};

int main()
{
    X  x;
    Y  y;
    X* xp{&x};
    Y* yp{&y};

    xp = reinterpret_cast<X*>(yp);
    void* p{xp};
    xp = reinterpret_cast<X*>(p);
    X& xr{x};
    Y& yr{reinterpret_cast<Y&>(x)};
}
~~~

reinterpret_cast() 并非万能；它对可以转换为什么有很多限制。这些限制在本书不会进一步讨论，因为建议谨慎使用这些类型的强制类型转换。通常，应谨慎使用 reinterpret_cast()，因为它允许在不执行任何类型检查的情况下进行转换。

>**警告：**
>还可以使用 reinterpret_cast() 将指针转换为整数类型并返回。但是，只能将指针转换为足够容纳它的整数类型。比如，如果使用 reinterpret_cast() 将 64 位指针强制转换为 32 位整数，会导致编译错误。

#### 10.7.3 std::bit_cast()

C++ 20 引入了 std::bit_cast()，它定义在 \<bit> 中。这是标准库中唯一的强制类型转换；其他强制转换是 C++ 语言本身的一部分。bit_cast() 与 reinterpret_cast() 类似，但它会创建一个指定目标类型的新对象，并按位从源对象复制到此新对象。它有效地将源对象的位解释为目标对象的位。bit_cast() 要求源对象和目标对象的大小相同，并且两者都是可复制的。示例如下：

~~~c++
float asFloat{1.23f};
auto  asUint{bit_cast<unsigned int>(asFloat)};
if (bit_cast<float>(asUint) == asFloat) {
    cout << "Roundtrip success." << endl;
}
~~~

>**注意：**
>蒲绒可复制类型是，组成对象的底层字节可以复制到一个新组中（比如 char），如果数组的数据随后被复制回对象，则该对象将保持其原始值。

bit_cast() 的一个用例是普通可复制类型的二进制 I/O。比如，可以将此类型的各个字节写入文件。当文件读回到内存时，可以使用 bit_cast() 正确地解释从文件中读取的字节。

#### 10.7.4 dynamic_cast()

dynamic_cast() 提供了对继承层次结构中的强制转换的运行期检查。可以使用它强制转换指针或引用。dynamic_cast() 在运行期检查底层对象的运行期类型信息。如果强制转换无效，dynamic_cast() 将返回空指针（对于指针），或者抛出 std::bad_cast 异常（对于引用）。
比如，假设有以下类层次结构：

~~~c++
class Base
{
public:
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    virtual ~Derived() = default;
};
~~~

下main的示例演示了 dynamic_cast() 的正确使用：

~~~c++
Base*    b;
Derived* d{new Derived{}};
b = d;
d = dynamic_cast<Derived*>(b);
~~~

下面对于引用的 dynamic_cast() 将抛出异常：

~~~c++
class Base
{
public:
    virtual ~Base() = default;
};

class Derived : public Base
{
public:
    virtual ~Derived() = default;
};

int main()
{
    Base*    b;
    Derived* d{new Derived{}};
    b = d;
    d = dynamic_cast<Derived*>(b);

    Base    base;
    Derived derived;
    Base&   br{base};
    try {
        Derived& dr{dynamic_cast<Derived&>(br)};
    }
    catch (const bad_cast&) {
        cout << "Bad cast!" << endl;
    }
}
~~~

注意，可以使用 static_cast() 或 reinterpret_cast() 在继承层次上执行相同的强制转换。与 dynamic_cast() 的区别在于：dynamic_cast() 执行运行期（动态）类型检查，而 static_cast() 和 reinterpret_cast() 则执行强制转换，即使转换的类型是错误的。
请记住，运行期的类型信息存储在对象的 vtable 中。因此，要使用 dynamic_cast()，类中必须至少具有一个虚方法。如果类没有 vtable，尝试使用 dynamic_cast() 会导致编译错误。

#### 10.7.5 类型转换小结

下表总结了在不同情况下应使用的强制类型转换。

| 场景                                                                       | 类型转换                              |
| -------------------------------------------------------------------------- | ------------------------------------- |
| 移除 const 属性                                                            | const_cast()                          |
| 语言支持的显式强制转换（比如，将 int 转换为 double，将 int 转换为 bool）） | static_cast()                         |
| 用户定义的构造函数或转换函数支持的显式强制转换                             | static_cast()                         |
| 一个类的对象转换为另一个（无关）类的对象                                   | bit_cast()                            |
| 在同一继承层次结构中，一个类的指针转换为另一个类的指针                     | 建议 dynamic_cast()，或 static_cast() |
| 在同一继承层次结构中，一个类的指针转换为另一个类的引用                     | 建议 dynamic_cast()，或 static_cast() |
| 指向一种类型的指针转换为指向其他不相关类型的指针                           | reinterpret_cast()                    |
| 一种类型的引用转换为其他不相关的类型的引用                                 | reinterpret_cast()                    |
| 指向函数的指针转换为指向函数的指针                                         | reinterpret_cast()                    |

## 11 零碎的工作

### 11.1 模块

#### 11.1.1 模块接口文件

模块接口文件，是为模块提供的功能定义的接口。模块接口文件通常以 .cppm  作为扩展名。模块接口以声明开头，声明该文件正在定义一个具有特定名称的模块。这称为模块声明。模块的名称可以是任何有效的 C++ 标识符。名称中可以包含点（.），但不能以点（.）开头或结尾，也不能在一行中包含多个点（.）。
模块需要显示地声明要导出的内容，即当用户代码导入模块时，哪些内容应该时可见的。使用 export 关键字从模块中导出实体（比如类、函数、常量、其他模块等）。任何没有从模块中导出的内容，只在该模块中可见。所有导出实体的集合称为模块接口。
下面是一个名为 Person.cppm 的模块接口文件的示例，它定义了 person 模块，并导出了 person 类。注意它导入了 \<string> 提供的功能。

~~~c++
#ifdef WRITE_IN_VSCODE //这个是自己写的，因为 vscode 不支持模块的代码补全
#include <string>
#endif

export module person;

import <string>;

export class Person
{
public:
    Person(std::string firstName, std::string lastName)
        : m_firstName{std::move(firstName)}
        , m_lastName{lastName} {};

    const std::string& getFirstName() const { return m_firstName; }
    const std::string& getLastName() const { return m_lastName; }

private:
    std::string m_firstName;
    std::string m_lastName;
};
~~~

可以通过以下方式导入 Person 模块，来使用 Person 类（test.cpp）

~~~c++
#ifdef WRITE_IN_VSCODE
#include <iostream>
#include <string>

#include <Person.ixx>
#endif

import person;
import <iostream>;
import <string>;

using namespace std;

int main()
{
    Person person{"Kole", "Webb"};
    cout << person.getLastName() << ", " << person.getLastName() << endl;
}
~~~

所有的 C++ 头文件（比如 \<iostream>、\<vector>、\<string> 等），都是所谓的可导入头文件，可以通过 import 声明导入。正如第 1 章介绍的，C++ 中可用的 C 的头文件不能保证是可导入的。为了安全起见，在 C 的头文件中使用 #include 替换 import 声明。这样的 #include 指令应该放在所谓的全局模块片段中，它必须出现在任何命名模块的声明之前，以匿名模块的声明开始，全局模块片段之恩包含预处理指令，比如 #include。这样的全局模块片段和注释是唯一允许出现在命名模块声明之前的内容。比如，如果需要使用 C 的头文件 \<cstddef> 中的功能，可以如下所示：

~~~c++
module;
#include <cstddef>

export module person;

import <string>;

export class Person
{
    /* 其余省略 */
};
~~~

在标准术语中，从已命名模块声明到文件末尾的所有内容称为模块权限。
几乎所有内容都可以从模块导出，只要它有一个名称。比如类定义、函数原型、类枚举类型、using 声明和指令、名称空间等。如果使用 export 关键字显式导出名称空间，则该名称空间中的所有内容也将自动导出。比如，下面的代码片段导出整个 DataModel 名称空间；因此，没有必要显示地导出单个类和类型别名：

~~~c++
export module datamodel;
import <vector>;
export namespace DataModel {
class Person
{ /*  */
};
class Address
{ /*  */
};
using Persons = std::vector<Person>;
}   // namespace DataModel
~~~

还可以使用导出块（export block）导出整个声明块。示例如下：

~~~c++
export
{
    namespace DataModel {
    class Person
    { /*  */
    };
    class Address
    { /*  */
    };
    using Persons = std::vector<Person>;
    }   // namespace DataModel
}
~~~

#### 11.1.2 模块实现文件

一个模块可以被拆分为一个模块接口文件和一个或多个模块实现文件。模块实现文件通常以 .cpp 作为扩展名。可以自由决定将哪些实现移到模块实现文件中，以及将哪些实现留在模块接口文件中。一种选择是将所有函数和方法实现移到模块实现文件中，而将其他函数和方法的实现移到实现文件中。这里有很大的灵活性。
模块实现文件中同样包含一个已命名模块的声明，用于指定实现所针对的模块，但没有 export 关键字。比如，可以将前面的 person 模块拆分为接口和实现文件，如下所示。下面是模块接口文件：

~~~c++
#ifdef WRITE_IN_VSCODE
#include <string>
#endif

export module person;

import <string>;

export class Person
{
public:
    Person(std::string firstName, std::string lastName);
    const std::string& getFirstName() const;
    const std::string& getLastName() const;

private:
    std::string m_firstName;
    std::string m_lastName;
};
~~~

实现现在位于模块实现文件 Person.cpp 中：

~~~c++
#ifdef WRITE_IN_VSCODE
#include <Person.ixx>
#endif

module person;

using namespace std;

Person::Person(string firstName, string lastName)
    : m_firstName{move(firstName)}
    , m_lastName{move(lastName)}
{}

const string& Person::getFirstName() const
{
    return m_firstName;
}

const string& Person::getLastName() const
{
    return m_lastName;
}
~~~

注意，实现文件没有 person 模块的导入声明。module person 的声明隐式包含 import person 的声明。还要注意的是，实现文件中没有 \<string> 的导入声明，即使它在方法的实现中使用了 std::string。正是由于隐式的 import person，并且因为这个实现文件是同一个 person 模块的一部分，所以它隐式地从模块接口文件中继承了 \<string> 的导入声明。与之相反，向 test.cpp 文件添加 import person 的声明并不会隐式地继承 \<string> 的导入声明，因为 test.cpp 不是 person 模块的一部分。关于这一点还有很多展开的，这是即将到来的“可见性与可访问性”章节的主题。

>**注意：**
>模块接口和模块实现中的导入声明都必须位于文件的顶部，在已命名模块声明之后，但需要在任何其他声明之前。

类似于模块接口文件，如果需要在模块实现文件中，使用 #include 指令导入已有的头文件，则应该将他们放在全局模块片段中，并使用与模块接口文件相同的语法。

>**警告：**
>模块实现问价不能导出任何内容，只有模块接口文件可以。

#### 11.1.3 从实现中分离接口

当使用头文件哎而不是模块时，强烈建议只把声明放在头文件（.h）中，并将所有实现移到源文件（.cpp）中。原因之一时可以缩短编译时间。如果将实现放在头文件中，任何的代码变更，哪怕是修改注释，都需要重新编译包含该头文件的其他所有源文件，对于某些头文件，这可能会影响整个代码库，导致整个程序完全编译。将实现放到源文件中，在不涉及头文件的情况下，对这些实现进行更改，这样只需要重新编译单个源文件。
模块的工作方式时不同的。模块接口（module interface）仅由类定义、函数原型等组成，虽然这些实现在模块接口文件中，但模块接口中不包含任何函数或方法的实现。因此，只要变更不涉及到模块接口的部分，变更模块接口中的函数/方法的实现是不需要重新编译该模块的，比如函数头（函数名、参数列表和返回类型），但有两个例外，使用 inline 关键字标记的函数或方法和模板的定义。对于这两者，编译器需要在编译使用它们的用户代码时知道其完整实现。因此，内联函数/方法或模板定义的任何变更都可能引发用户代码的重新编译。

>**注意：**
>当头文件中的类定义中包含方法的实现，那么这些方法是隐式的内联，尽管没有使用 inline 关键字标识它们。对于在模块接口文件中的类定义里的方法来说，却又不一样了。如果要变成内联方法，就需要使用 inline 关键字显式标识它们。

尽管从技术上讲，不再需要将接口从实现中分离，但在某些情况下，作者仍建议这么做。其主要目的是创建整洁和易读的接口。只要不会模糊接口和不会增加用户快速掌握公共接口提供的内容的难度，函数的实现就可以保留在接口中。例如，如果一个模块有一个规模很大的公共接口，那么最好不要使用模糊的接口实现，这样可以更好地了解所提供的内容。尽管如此，规模小的 getter 和 setter 函数仍然可以保留在接口中，因为不会影响接口的可读性。
将接口从实现中分离可以通过几种方式实现。一种是将模块拆分为接口文件和实现文件，如上一节所讨论的。另一种是在单个模块的接口文件中拆分接口和实现。例如，下面是定义在单个模块接口文件（person.cppm）中的 Person 类，但该类的实现是从接口中分离的。

~~~c++
#ifdef WRITE_IN_VSCODE
#include <string>
#endif

export module person;

import <string>;

export class Person
{
public:
    Person(std::string firstName, std::string lastName);
    const std::string& getFirstName() const;
    const std::string& getLastName() const;

private:
    std::string m_firstName;
    std::string m_lastName;
};


Person::Person(std::string firstName, std::string lastName)
    : m_firstName{std::move(firstName)}
    , m_lastName{std::move(lastName)}
{}

const std::string& Person::getFirstName() const
{
    return m_firstName;
}

const std::string& Person::getLastName() const
{
    return m_lastName;
}
~~~

#### 可见性和可访问性

正如前面介绍的，当在不属于 person 模块的另一个源文件（比如 test.cpp 文件）中导入 person 模块时，不会隐式地从 person 模块的接口文件中继承 \<string> 的导入声明。因此，如果在 test.cpp 中没有显式导入 \<string>，那么 std::string 是不可见的，这意味着以下代码将无法正常编译。

~~~c++
import person;

int main()
{
    std::string        str;   // 编译不通过
    Person             person{"Kole", "Webb"};
    const std::string& lastName{person.getLastName()};   // 编译不通过
}
~~~

尽管如此，即使在 test.cpp 中没有显式导入 \<string>，下面的代码也可以正常工作。

~~~c++
    const auto& lastName{person.getLastName()};
    auto        length{lastName.length()};
~~~

为什么会这样呢？在 C++ 中，实体的可见性（visibility）和可访问性（reachability）是有区别的。通过导入 person 模块，\<string> 中的功能变得可访问，但并不可见；可访问类的成员函数自动变得可见。所有这些都意味着可以使用 \<string> 中的某些功能，比如使用自动类型推断（auto type deduction）和调用 length() 等方法，将 getLastName() 的结果存储在变量中。
为了使 std::string 名称在 test.cpp 中可见，需要显式导入 \<string>。当想要使用（比如下面代码中的运算符 <<）时，这样的显式导入是必要的。这是因为运算符 << 不是 std::string 的方法，而是只有通过导入 \<string> 才可见的非成员函数。

~~~c++
cout << person.getLastName() << endl;
~~~

#### 11.1.5 子模块

C++ 标准中并没有描述子模块（submodule）；但是，标准允许在模块名中使用符号点（.），这就可以在任何想要的层次结构中构建模块。比如，之前的章节给出的名称空间 DataModel 示例如下：

~~~c++
#ifdef WRITE_IN_VSCODE
#include <vector>
#endif

export module DataModel;
import <vector>;

export namespace DataModel {
class Person
{ /*  */
};

class Address
{ /*  */
};

using Persons = std::vector<Person>;
};   // namespace DataModel
~~~

类 Person 和类 Address 都位于名称空间 DataModel 和模块 datamodel 中。这可以通过定义两个子模块来重新进行构造：datamodel.person 和 datamodel.address。子模块 datamodel.person 的模块接口文件如下：

~~~c++
export module datamodel.person;

export namespace DataModel {
class Person
{ /*  */
};
};   // namespace DataModel
~~~

下面是子模块 datamodel.address 的模块接口文件：

~~~c++
export module datamodel.address;

export namespace DataModel {
class Address
{ /*  */
};
};   // namespace DataModel
~~~

最后，模块 datamodel 的定义如下。它导入并立即导出两个子模块：

~~~c++
#ifdef WRITE_IN_VSCODE
#include <vector>

#include "datamodel.address.ixx"
#include "datamodel.person.ixx"
#endif

export module datamodel;
export import datamodel.person;
export import datamodel.address;

import <vector>;

export namespace DataModel {
using Persons = std::vector<Person>;
}
~~~

当然，子模块中类的方法实现也可以放入模块实现文件中。比如，假设类 Address 有一个默认构造函数，它只打印一条语句到标准输出流中；这个实现可以放在文件 datamodel.address.cpp 中：

~~~c++
#ifdef WRITE_IN_VSCODE
#include <iostream>

#include "datamodel.address.ixx"
#endif

module datamodel.address;
import <iostream>;
using namespace std;

DataModel::Address::Address()
{
    cout << "Address::Address()" << endl;
}
~~~

使用子模块构造代码的好处是：用户可以导入一次他们想要使用的模块特定部分或全部内容。例如，如果用户只对类 Address 的使用感兴趣，那么下面的 import 声明就足够了。

~~~c++
import datamodel.address;
~~~

另一方面，如果客户端代码需要访问模块 datamodel 中的所有内容，那么下面的导入声明是最简单的。

~~~c++
import datamodel;
~~~

#### 11.1.6 模块划分

另一种构建模块的方法是将它们拆分到单独的分区中。子模块和分区之间的区别是：子模块的构造对模块的用户来说是可见的，允许用户有选择地只导入想要使用的子模块。另一方面，分区用于在内部构造模块。分区不对模块的用户公开。在模块接口分区文件（module interface partition file）中声明的所有分区，最终必须又主模块接口文件导出。一个模块通常只有一个这样的主模块接口文件，那就是包含导出模块名称声明的接口文件。
模块分区名创建时使用冒号将模块名和分区名分隔开，分区名可以是任何合法的标识符。例如，前一节中的 DataMOdel 模块可以使用分区而不是子模块来重新构造。下面是在模块接口分区文件 datamodel.person.cppm 的 person 分区：

~~~c++
export module datamodel:person;

export namespace DataModel {
class Person
{ /* ... */
};
};   // namespace DataModel
~~~

下面是包含默认构造函数的 address 分区：

~~~c++
export module datamodel:address;

export namespace DataModel {
class Address
{
public:
    Address();
    /* ... */
};
};   // namespace DataModel
~~~

但是，将实现文件与分区结合使用时需要注意：只有一个具特定分区名称的文件。因此，以下声明开头的实现文件的格式是不正确的。

~~~c++
module datamodel:address;
~~~

相反，可以将 address 分区的实现放在 datamodel 模块的实现文件中，示例如下：

~~~c++
#ifdef WRITE_IN_VSCODE
#include <iostream>

#include "datamodel.ixx"
#endif

module datamodel;
import <iostream>;
using namespace std;
DataModel::Address::Address()
{
    cout << "Address::Address()" << endl;
}
~~~

多个文件不能具有相同多的分区名称。因此，具有多个相同分区名的模块接口文件是非法的，并且对于模块接口分区文件中声明的实现，也不能出现在具有相同分区名的实现文件中。相反，只需要将这些实现放在模块的实现文件中即可。
需要记住的重点是，在编写分区结构中的模块时，每个模块接口的分区最终都必须由主模块接口文件直接或间接导出。要导入分区，只需要指定（以冒号作为分隔）分区名称，比如 import:person。而 import datamodel:person 这样的则是非法的。记住，分区不会对模块的用户公开。分区只能在内部构造模块。因此，用户不能导入特定的分区；只能导入整个模块。分区只能在模块内部导入，因此在冒号之前指定模块名称是多余的（也是非法的）。下面是 datamodel 模块的主模块接口文件：

~~~c++
export module datamodel;
export import :person;
export import :address;

import <vector>;

export namespace DataModel {
using Persons = std::vector<Person>;
}
~~~

这个分区结构的 datamodel 模块可以按以下方式使用：

~~~c++
import datamodel;
int main()
{
    DataModel::Address a;
}
~~~

>**注意：**
>分区用于在内部构造模块。分区在模块外部不可见。因此，模块的用户无法导入特定的分区；只能导入整个模块。

前面已经解释过模块名称声明中隐式包括导入名称声明，但分区不是这样做的。
比如 datamodel:person 分区没有隐式导入 datamodel 的声明。在本例中，甚至不允许在 datamodel:person 接口文件中显式导入 datamodel。因为这样做将导致循环依赖：datamodel 接口文件中包含 import:person 的声明，而 datamodel:person 接口分区文件中包含 import datamodel 声明。
要打破这种循环依赖关系，可以将 datamodel:person 分区需要的功能从 datamodel 接口文件中转移至另一个分区，随后通过 datamodel:person 接口分区文件和 datamodel 接口文件导入该分区。

**实现分区**：

分区不需要在模块的接口分区文件中声明，但可以在模块的实现分区文件（扩展名为 .cpp 的常规源码文件）中声明。这种情况下，它是实现分区，有时也称为内部分区。主模块的接口文件不会导出这样的分区。
例如，假设具有以下 math 主模块的接口文件（math.cppm）

~~~c++
export module math;
export namespace Math {
double superLog(double z, double b);
double lerchZeta(double lambda, double alpha, double s);
};   // namespace Math
~~~

进一步假设，math 函数的实现需要一些辅助函数，这些辅助函数不能被模块导出。实现分区是放置此类辅助函数的理想场所。下面在名为 ath_helpers.cpp 的文件中定义了这类实现分区：

~~~c++
module math:details;
double someHelperFunction(double a)
{
    return /*  */;
}
~~~

其他的 math 模块实现文件可以通过导入此类实现分区来访问这些辅助函数。比如，math 模块的实现文件（math.cpp）可能如下所示：

~~~c++
module math;
import :details;
double Math::superLog(double z, double)
{
    return /* ... */;
}
double Math::lerchZeta(double lambda, double alpha, double s)
{
    return /*  */;
}
~~~

当然，只有当多个其他源文件都使用这些辅助函数的情况下，将实现分区与辅助函数一起使用才会有效果。

#### 11.1.7 头文件单元

导入模块时，可以使用导入声明，示例如下：

~~~c++
import person;
~~~

如果由遗留代码，比如定义 Person 类的 person.h 头文件，则可以通过将其转换为适当的模块（person.cppm）进行模块化，并导入声明使其对用户代码可用。但是，有时不能模块化这类头文件。也许对于还不支持模块的编译器，Person 类应该保持可用。或者 person.h 头文件是不能修改的第三方库的一部分。在这种情况下，可以如下所示，直接导入头文件：

~~~c++
import "person.h"
~~~

有了这样的声明，person.h 头文件中的所有内容都将隐式导出。此外，头文件中定义的宏对于用户代码可见，但实际模块中却并非如此。
相比 #include 头文件，导入头文件可以提高构建效率，因为 person.h 头文件将隐式转换为模块，因此只需要编译一次，而不是在源文件中 #include 头文件时每次都进行编译。因此，它可以作为支持所谓的预编译头文件的标准化方式，而不是使用依赖于编译器的预编译头文件的支持。
对于每个命名头文件的导入声明，编译器必须创建一个模块，该模块具有类似于头文件定义的导入接口。这称为头文件单元。此过程取决于编译器，因此请参阅编译器的文档，了解如何使用头文件单元。

### 11.2 头文件

在介绍 C++20 的模块之前，头文件被用作一种为子系统或代码段提供接口的机制。第 1 章简要介绍了头文件。基本上，头文件最常见的用法时用于声明在其他地方定义的函数。函数声明告诉编译器如何调用函数，声明形参的数量和类型，以及函数的返回类型。定义则包含该函数的实际代码。在 C++ 中，声明通常放入头文件中，扩展名为 .h；而定义通常放入源文件中，扩展名为 .cpp。本书在任何地方都将使用 C++20 的模块，但本节将会简要讨论使用头文件时一些复杂的情况，比如避免重复定义和循环依赖，因为在系统一六代码中可能会遇到这些问题。

#### 11.21 重复定义

假设 A.h 包含 Logger.h 头文件，Logger.h 头文件定义了 Logger 类；B.h 也包含了 Logger.h。如果具有一个名为 App.cpp 的源文件，其中同时包含 A.h 和 B.h，将会得到 Logger 类的重复定义，因为 Logger.h 头文件包含在 A.h 和 B.h 中。
这种重复定义的问题可以通过一种称为包含保护（也称为头文件保护）的机制来避免。下面的代码段显示了具有包含保护的 Logger.h 头文件。在每个头文件的开头，#ifndef 指令检查是否有某个标识符没有被定义。如果标识符已定义，那么编译器将会跳转至匹配的 #endif （通常将其放置在文件的末尾）。如果没有定义标识符，将会继续定义该标识符，以便跳过同一文件的后续包含。

~~~c++
#ifndef LOGGER_H
#define LOGGER_H

class Logger
{ /* ... */
};

#endif
~~~

另外，现在几乎所有的编译器都支持 #pragma once 指令，它取代了 include 保护指令。在头文件的开头放置 #pragma once，可以确保它只会被导入一次，从而避免了由于多次包含头而导致的重复定义。示例如下：

~~~c++
#pragma once

class Logger
{ /* ... */
};
~~~

#### 11.2.2 循环依赖

避免头文件问题的另一个工具是前向声明（forward declaration）。如果需要引用一个类，但不能包含它的头文件（比如，它严重依赖于正在编写的类），则可以（通过前向声明）告诉百年一起该类存在，而不需要通过 #include 提供正式的定义。当然，不能再代码中实际使用该类，因为版一起对它还一无所知，只知道已命名的类将所有内容链接在一起后存在于内存中。但仍然可以在代码中，通过指针和引用来引用前向声明的类。还可以声明按值返回的此类前向声明的类，或者声明一个函数，该函数的参数按值传递，类型为前向声明的类。当然，对于定义了函数的代码和调用该函数的任何代码，都需要包含正确定义了前向声明的类的头文件。
比如，假设 Logger 类使用另一个名为 Preferences 的类来跟踪用户的设置。Preferences 类可能反过来使用 Logger 类，因此会具有循环依赖关系，而且不能通过包含保护来解决。在这种情况下，需要使用前向声明。在下面的代码中，Logger.h 头文件使用了 Preferences 类的前向声明，因此可以在不包含其头文件的情况下，引用 Preferences 类。

~~~c++
#pragma once

#include <string_view>

class Preferences;

class Logger
{
public:
    void setPreferences(const Preferences& prefs);
    void logError(std::string_view error);
};
~~~

建议尽可能在头文件中使用前向声明，而不是包含其他头文件。这么做可以减少编译和重新百衲衣的时间，因为它打破了当前头文件对其他头文件的依赖。当然，实现文件还是需要包含正确的头文件，即已前向声明的类型头文件；否则，它将无法通过编译。

#### 11.2.3 查询头文件是否存在

若要查询某个头文件是否存在，请使用 \__has_include("filename) 或 __has_include(\<filename>) 预处理常量表达式。如果头文件已经存在，则返回值为1，否则为 0。例如，在 C++17 完全批准使用 \<optional> 头文件之前，某些编译器已经在 \<experimental/optional> 中具有初步版本。可以使用 \__has_include() 检查这两个头文件中那一个系统中可用：

~~~c++
#if __has_include(<optional>)
    #include <optional>
#elif __has_include(<experimental/optional>)
    #include <experimental/optional>
#endif
~~~

### 11.3 核心语言特性的特性测试宏

跳过。

### 11.4 static 关键字

在 C++ 中，static 关键字有多种用法，这些用法之间好像没有关系。“重载”关键字的部分原因是为了比卖你在语言中引入新的关键字。

#### 11.4.1 静态数据成员和方法

可以声明类的静态数据成员和方法。与非静态数据成员不同，静态数据成员不是对象的一部分。相反，这个数据成员只有一个副本，这个副本存在于类的任何对象之外。
静态方法与此类似，位于类层次（而不是对象层次）。静态方法不会在某个特定对象的上下文中执行；因此，它没有隐式的 this 指针。但这也意味着静态方法不能被标记为 const。
可见前第 9 章。

#### 11.4.2 静态链接

在介绍用于链接的 static 关键字之前，首先需要理解 C++ 中的链接概念。C++ 的每个源文件都是单独编译的，编译得到的目标文件会彼此链接。C++ 源文件中的每个名称（包括函数和全局变量）都具有外部或内部的链接。外部链接意味着这个名称在其他源文件中也有效。内部链接（也称为静态链接）意味着在其他源文件中无效。默认情况下，函数和全局变量都具有外部链接，但是，可以在声明前面加上 static 关键字来指定内部（或静态）链接。比如，假设有两个源文件：FirstFile.cpp 和 AnotherFile.cpp。下面的代码是 FirstFile.cpp：

~~~c++
void f();

int main()
{
    f();
}
~~~

注意，这个文件提供了函数 f() 的原型，但没有显式给出定义。下面的代码是 AnotherFile.cpp：

~~~c++
import <iostream>;

void f();

void f()
{
    std::cout << "f\n";
}
~~~

这个文件提供函数 f() 的原型和定义。注意，在两个不同的文件中为同一个函数编写原型是合法的。如果将原型放在头文件中，并且每个源文件中都用 #include 包含这个头文件，那么预处理器就会自动在每个源文件中给出函数原型。在下面的示例中，不使用头文件。过去使用偷吻加的原因是，它是更易于维护（并保持同步）原型的一个副本，但是从 C++20 开始，使用模块时建议不要使用头文件。
这些源文件中都可以成功编译，并且程序链接也没有问题：因为 f() 具有外部链接，main() 可以从其他文件调用它。
但是，假设对 AnotherFile.cpp 中的函数 f() 的原型应用了 static 关键字。注意，不需要在函数 f() 的定义前重复 static 关键字。只要它位于函数名称的第一个实例之前，就不需要重复它。

~~~c++
import <iostream>;

static void f();

void f()
{
    std::cout << "f\n";
}
~~~

现在，每个源文件都可以正确编译，但是链接时却失败了，这是因为函数 f() 具有内部（静态）链接，从而是的 FirstFile.cpp 中无法使用这个函数。如果在源文件中定义了静态方法但是没有使用它，有些编译器会给出警告（指出这些方法不应该是静态的，因为其他文件可能会用到它们）。
将 static 用于内部链接的另一种方式是使用匿名的名称空间。将变量或函数封装到一个没有名字的名称空间中，而不是使用 static 关键字，示例如下：

~~~c++
import <iostream>;

namespace {
void f();

void f()
{
    std::cout << "f\n";
}
}   // namespace
~~~

在同一源文件中，可在声明匿名名称空间之后的任何位置访问名称空间中的项，但不能在其他源文件中访问。这一语义与 static 关键字相同。

>**警告：**
>要获得内部链接，建议使用匿名的名称空间，而不要使用 static 关键字。

**extern 关键字**.

extern 关键字好像是 static 关键字的反义词，将它后面的名称指定为外部链接，在某些情况下可以使用这种方法。例如，默认情况下，const 和 typedef 具有内部链接，可以使用 extern 使其变为外部链接。但是 extern 有一点复杂。当指定某个名称为 extern 时，编译器会将这条语句当作声明，而不是定义。对于变量，这意味着编译器不会为其分配空间。必须为这个变量提供单独的，而不是使用 extern 关键字的定义行。例如，下面是 AnotherFile.cpp 中的内容：

~~~c++
extern int x;
int        x{3};
~~~

或者，可以在 extern 语句中初始化 x，然后将其作为声明和定义。

~~~c++
extern int x{3};
~~~

在这种情况下，extern 不是非常有用，因为默认情况下，x 具有外部链接。当另一个源文件 FirstFile.cpp 使用 x 时，才会真正使用到 extern：

~~~c++
import <iostream>;

extern int x;

int main()
{
    std::cout << x << std::endl;
}
~~~

本例中 FirstFile.cpp 使用了 extern 声明，因此可以使用 x。编译器需要知道 x 的声明之后，才能在 main() 中使用它。然而，如果在声明 x 时没有使用 extern 关键字，编译器会认为这是一个定义，并为 x 分配空间，从而导致链接失败（因为有两个全局作用域的 x 变量）。使用 extern 关键字，就可以在多个源文件中全局访问这个变量。

>**警告：**
>不建议使用全局变量，全局变量令人困惑且容易出错，尤其是在大型程序中。请明智地使用它们！

#### 11.4.3 函数中的静态变量

在 C++ 中，static 关键字的最终目的是创建离开和进入作用域时都可保留值的局部变量。函数中的静态变量就像只能在函数内部访问的全部变量。静态变量最常见的用法是“记住”某个函数是否执行了特定的初始化操作。比如，下面代码就是用了这一技术：

~~~c++
void performTask()
{
    static bool initialized{false};
    if (!initialized) {
        cout << "initializing" << endl;
        initialized = true;
    }
}
~~~

但是，静态变量容易让人迷惑，在构建代码时通常有更好的方法，以避免使用静态变量。在这种情况下，了一边写一个类，用构造函数执行所需的初始化操作。

>**注意：**
>比卖你使用单独的静态变量，为了维持状态可以改用对象。

但有时，它们十分有用。一个示例是实现 Meyer 的单例设计模式，详见第33 章。

>**注意：**
>performTask() 的实现不是线程安全的；它包含一个竟态条件。在多线程环境中，需要使用原子或其他机制来同步多个线程。关于线程的详细讨论在第 27 章。

#### 11.4.4 非局部变量的初始化顺序

在结束静态数据成员和全局变量的主题之前，请考虑这些变量的初始化顺序。在 main() 开始之前，将初始化程序中的所有全局变量和静态类数据成员。对于给定源文件中的变量，按照它们在源文件中出现的顺序进行初始化。例如，在下面的示例中，Demo::x 一定会在 y 之前初始化。

~~~c++
class Demo
{
public:
    static int x;
};
int Demo::x{3};
int y{4};
~~~

然而，C++ 没有提供规范，用以说明在不同源文件中初始化非局部变量的顺序。如果在某个源文件中有一个全局变量，在另一个源文件中有一个全局变量 y，无法知道哪个全局变量将首先初始化。通常，不需要关注这一规范的缺失，但如果某个全局变量或静态变量依赖于另一个变量，就可能引发问题。对象的初始化意味着调用构造函数，全局对象的构造函数可能会访问另一个全局对象，并假定另一个全局对象已经构建。如果这两个全局对象在不同的源文件中声明，就不能指望一个全局对象在零个全局对象之前构建，也无法控制它们的初始化顺序。不同编译器可能有不同的初始化顺序，即使同一编译器的不同版本也可能如此，甚至在项目中添加另一源文件也可能影响初始化顺序。

>**警告：**
>在不同源文件中，非局部白能量的初始化顺序是不确定的。

#### 11.4.5 非局部变量的销毁顺序

非局部变量的销毁顺序与其初始化顺序相反。对于不同源文件中的非局部变量，初始化的顺序是不确定的，这意味着其销毁的顺序也是不确定的。

### 11.5 C 的实用工具

一些晦涩的 C 特性在 C++ 中也可以用。本节研究其中的两个特性：变长参数列表（variable-length-argument lists）和预处理器宏（preprocessor macros）。

#### 11.5.1 边长参数列表

本节将介绍旧的 C 风格的边长参数列表。需要知道它们是如何工作的，因为可能会在遗留代码中看到它们。然而，在新的代码中，应该通过变参模板使用类型安全的边长参数列表，变参模板将在第 26 章“高级模板”中进行介绍。对于 \<cstdio> 中的 C 函数 printf()，可以使用任意数量的参数来调用它。

~~~c++
printf("int %d\n", 5);
printf("String %s and int %d\n", "hello", 5);
printf("Many ints: %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5);
~~~

C/C++ 提供了语法和一些实用宏，用于编写具有可变数量的函数。这些函数通常看起来很像 printf()，尽管并非经常需要，但偶尔需要这个特性。例如，假设想编写一个快速调试的函数，如果设置了调试标记，这个函数向 stderr 输出字符串，但如果没有设置调试标记，就什么都不做。于 printf() 一样，这个函数应该能接收任意数目和任意类型的参数并输出字符串。这个函数的简单实现如下所示：

~~~c++
#include <cstdarg>
#include <cstdio>

bool debug{false};

void debugOut(const char* str, ...)
{
    va_list ap;
    if (debug) {
        va_start(ap, str);
        vfprintf(stderr, str, ap);
        va_end(ap);
    }
}
~~~

首先，注意 debugOut() 函数的原型包含一个具有类型和名称的参数 str，之后是省略号（...），这代表任意数目和类型的参数。如果要访问这些参数，必须使用\<cstdarg> 中定义的宏。声明一个 va_list 类型的变量，并调用 va_start() 对其进行初始化。va_start() 的第二个参数必须是参数类表中最右边的已命名变量。所有具有变长参数列表的函数都至少需要一个已命名的参数。debugOut() 函数只是将列表传递给 vfprintf()（\<cstdio> 中的标准函数）。vfprintf() 的调用返回时，debugOut() 调用 va_end() 来终止对变长参数列表的访问。在调用 va_start() 之后，必须总是调用 va_end()，以确保函数结束后，堆栈处于稳定的状态。
函数 debugOut() 的用法如下：

~~~c++
debug = true;
debugOut("int %d\n", 5);
debugOut("String %s and int %d\n", "hello", 5);
debugOut("Many ints: %d, %d, %d, %d, %d\n", 1, 2, 3, 4, 5);
~~~

1. 访问参数
    如果想要访问实际参数，那么可以使用 va_arg()；它接收 va_list 作为第一个参数，以及需要解析的参数的类型作为第二参数。但是，如果不提供显示的方法，就无法知道参数列表的结尾是什么。例如，可以将第一个参数作为参数个数的计数。或者，当参数是一组指针时，可以要求最后一个指针是 nullptr。方法很多，但对于程序员来说，所有方法都很麻烦。
    下面的示例演示了这种技术，其中调用者在第一个已命名参数中指定了所提供参数的数目。函数接收任意数目的 int 参数，并将其输出。

    ~~~c++
    void printInts(size_t num, ...)
    {
        va_list ap;
        va_start(ap, num);
        for (size_t i{0}; i < num; ++i) {
            int temp{va_arg(ap, int)};
            cout << temp << " ";
        }
        va_end(ap);
        cout << endl;
    }
    ~~~

    可以按以下方式调用 printInts()。注意，第一个参数将指定后面整数的数目。

    ~~~c++
    printInts(5, 5, 4, 3, 2, 1);
    ~~~

2. 为什么不应该使用 C 风格的边长参数列表
    访问 C 风格的变长参数列表并不十分安全。从 printInts() 函数可以看出，这种方法存在以下风险：

    - **不知道参数的数目。**在 printInts() 中，必须信任调用者传递了与第一个参数指定的数目相等的参数。在 debugOut() 中，必须相信调用者在字符数组之后传递的参数数目与字符数组中的格式代码一致。
    - **不知道参数的类型。**va_arg() 接收一种类型，用来解释当前的值，然而，可让 va_arg() 将这个值解释为任意类型，无法验证正确的类型。

>**警告：**
>避免使用 C 风格的变长参数列表。使用第 1 章介绍的初始化列表时，最好传入 std::array 或者值矢量；对于类型安全的变长参数列表，可以使用变参模板，这一主题将在第 22 章讲述。

#### 11.5.2 预处理器宏

可使用 C++ 预处理器宏，这与函数有点类似。下面是一个示例：

~~~c++
#define SQUARE(x) ((x) * (x))

int main()
{
    cout << SQUARE(5) << endl;
    return 0;
}
~~~

宏是 C 遗留下来的特性，非常类似于内联函数，但不执行类型检测。在调用宏时，预处理器会自动使用扩展式替换。预处理器并不会真正地应用函数调用语义，这一行为可能导致无法预测的结果。例如，如果用 2+3 而不是 5 调用 SQUARE 宏，考虑一下会发生什么，如下所示。

~~~c++
cout << SQUARE(2 + 3) << endl;
~~~

SQUARE 宏的计算结果应为 25，结果确实如此。然而，如果在宏定义中省略部分圆括号，这个宏看上去是这样的：

~~~c++
#define SQUARE(x) (x * x)
~~~

现在，调用 SQUARE(2 + 3) 的结果是 11，而不是 25！注意宏只是自动扩展，而不考虑函数调用语义。这意味着在宏中，x 被替换为 2+3，扩展式是：

~~~c++
cout << SQUARE(2 + 3 * 2 + 3) << endl;
~~~

按照正确的操作顺序，这行代码首先执行乘法，然后是加法，结果是 11 而不是 25。
宏还会影响性能，假定按如下方式调用 SQUARE 宏：

~~~c++
cout << SQUARE(veryExpensiveFunctionCallToComputeNumber()) << endl;
~~~

预处理把它替换为：

~~~c++
cout << ((veryExpensiveFunctionCallToComputeNumber()) *
         (veryExpensiveFunctionCallToComputeNumber()))
     << endl;
~~~

现在，这个开销很大的函数调用了两次。这是避免使用宏的另一个原因。
宏还会导致调试问题，因为编写的代码并非编译器看到的代码或者调试工具中显示的代码（因为预处理的查找和替换功能）。为此，**应该全部用内联函数替换宏**。在这里详细讲述宏，只是因为相当多的 C++ 代码使用了 宏，为了阅读并维护这些代码，应该理解宏。

>注意：
>大多数编译器可将经过预处理器处理的源代码输出到某个文件。使用这个文件可以观察预处理器是如何处理文件的。例如，使用 MSVC 时需要使用 /P 选项，使用 GCC 时，可以使用 -E 选项。

## 12 利用模板编写泛型代码

C++ 不仅支持面向对象编程，还支持泛型编程（generic programming）。根据第 6 章“设计可重用代码”的讨论，泛型编程的目的时编写可重用的代码。在 C++ 中，泛型编程的基本工具是模板。尽管从严格意义上说，模板并不是一个面向对象的特性，但模板可与面向对象编程结合使用，从而产生强大的作用。
本章列出了满足第 6 章讨论的一般性设计原则所需的编码细节，第 22 章“高级模板”将讨论一些高级模板特性。

### 12.1 模板概述

面向过程编程泛型中主要的编程单元式过程或函数。主要使用的是函数，因为函数可用于编写不依赖特定值的算法，从而可重用很多不同的值。例如，C++ 中的 sqrt() 函数计算调用者指定的值的平方跟。只能计算一个数字（例如 4）的平方根的函数没有什么实际用途，sqrt() 函数是基于参数编写的，参数实际上是一个占位符，可表示调用者传入的任何数值。用计算机科学家的话来说，就是用函数参数化值。
面向对象编程范式中添加了对象的概念，对象将相关的数据和行为组织起来，但它并没有改变函数和方法参数化值的方式。
模板将参数化的概念推进了一步，不仅允许参数化值，还允许参数化类型。C++ 中的类型不仅包括基本类型，例如 int 和 double，还包括用户定义的类，例如 SpreadsheetCell 和 CherryTree。使用模板，不仅可编写不依赖特定值的代码，还能编写不依赖那些值类型的代码。例如，不需要为保存int、Car 和 SpreadsheetCell 而编写不同的堆栈类，但可以编写一个堆栈的类定义，这个类定义可用于任何类型。
尽管模板是一个令人惊叹的语言特性，但由于 C++ 模板的语法令人费解，很多程序员会选择忽略或避免使用模板。不过，每个程序员至少需要知道如何使用模板，因为程序库（例如 C++ 标准库）中广泛使用了模板。
这一章讲解 C++ 中的模板支持，重点讲述模板在标准库中的使用。在学习过程中，可以学会一些有用的细微特性，除了标准库之外，还可以在程序中使用这些特性。

### 12，2 类模板

类模板定义了一个类，其中，将一些变量的类型、方法和返回类型和/或方法的参数类型指定为参数。类模板主要用于容器，或用于保存对象的数据结构。本节使用一个 Grid 容器作为示例。为了让这些例子长度合理，且足够简单地演示特定的知识点，本章不同的小节会向 Grid 容器添加一些特性，这些特性在接下来的几个章节将不会被用到，

#### 编写类模板

假设想要一个通用的棋盘类，可将其用作对象棋棋盘、跳棋棋盘、井字棋棋盘或其他任何二维的棋盘。为让这个棋盘通用，这个棋盘应该能保存象棋棋子、跳棋棋子、井字棋棋子或其他任何游戏类型的棋子。

1. 编写不使用模板的代码
    如果不使用模板，编写通用棋盘最好的方法是采用多态技术，保存通用的 GamePiece 对象，然后，可让每种游戏的棋子继承 GamePiece 类。例如，在象棋游戏中，ChessPiece 可以是 GamePiece 的派生类，通过多态技术，既能保存 GamePiece 的 GameBoard，也能保存 ChessPiece。GameBoard 可以复制，所以 GameBoard 需要能复制 GamePiece。这个实现利用了多态技术，因此一种解决方案是给 GamePiece 基类添加纯虚方法 clone()，它的派生类必须实现 clone()，并返回一个具体的 GamePiece 的副本。GamePiece 基类如下：

    ~~~c++
    export class GamePiece
    {
    public:
        virtual ~GamePiece()                             = default;
        virtual std::unique_ptr<GamePiece> clone() const = 0;
    };
    ~~~

    GamePiece 是一个抽象基类。ChessPiece 等具体类派生于它，并实现了 clone() 方法。

    ~~~c++
    class ChessPiece : public GamePiece
    {
    public:
        std::unique_ptr<GamePiece> clone() const override
        {
            return std::make_unique<ChessPiece>(*this);
        }
    };
    ~~~

    GameBoard 的实现使用 unique_ptr 矢量组中的矢量来存储 GamePiece。

    ~~~c++
    export class GameBoard
    {
    public:
        explicit GameBoard(size_t width = DefaultWidth, size_t height = DefaultHeight);
        GameBoard(const GameBoard& src);
        virtual ~GameBoard() = default;
        GameBoard& operator=(const GameBoard& rhs);

        GameBoard(GameBoard&& src)            = default;
        GameBoard& operator=(GameBoard&& src) = default;

        std::unique_ptr<GamePiece>&       at(size_t x, size_t y);
        const std::unique_ptr<GamePiece>& at(size_t x, size_t y) const;

        size_t getWidth() const { return m_width; }
        size_t getHeight() const { return m_height; }

        static const size_t DefaultWidth{10};
        static const size_t DefaultHeight{10};

        void swap(GameBoard& other) noexcept;

    private:
        void verifyCoordinate(size_t x, size_t y) const;

        std::vector<std::vector<std::unique_ptr<GamePiece>>> m_cells;

        size_t m_width{0}, m_height{0};
    };
    ~~~

    在这个实现中，at() 返回指定位置的棋子的引用，而不是返回棋子的副本。GameBoard 作为一个二维数组的抽象，它应给出实际对象的索引，而不是给出对象的副本，以提供数组访问语义。客户代码不应存储这个引用将来使用，因为它可能是无效的；相反，应该在使用返回的引用之前调用 at()。这遵循了标准库中 std::vector 类的设计原理。

    >**注意：**
    >GameBoard 类的这个实现提供了 at() 的两个版本，一个版本返回引用，另一个版本返回 const 引用。

    下面是方法的定义。注意，这个方法为赋值运算符使用了“复制和交换”惯用语法，还使用 Scott Meyer 的 const_cast() 模式来避免代码重复，第 9 章讨论了这些主题。

    ~~~c++
    #ifdef WRITE_IN_VSCODE
    #    include "GameBoard.ixx"
    
    #    include <format>
    #    include <stdexcept>
    #    include <utility>
    #endif
    
    module game_board;
    
    import <format>;
    import <stdexcept>;
    import <utility>;
    
    using namespace std;
    
    GameBoard::GameBoard(size_t width, size_t height)
        : m_width{width}
        , m_height{height}
    {
        m_cells.resize(m_width);
        for (auto& column : m_cells) {
            column.resize(m_height);
        }
    }
    
    GameBoard::GameBoard(const GameBoard& src)
        : GameBoard{src.m_width, src.m_height}
    {
        for (size_t i{9}; i < m_width; i++) {
            for (size_t j{0}; i < m_height; j++) {
                if (src.m_cells[i][j]) {
                    m_cells[i][j] = src.m_cells[i][j]->clone();
                }
            }
        }
    }
    
    void GameBoard::verifyCoordinate(size_t x, size_t y) const
    {
        if (x >= m_width) {
            throw std::out_of_range{std::format("{} must be less than {}.", x, m_width)};
        }
        if (y >= m_height) {
            throw std::out_of_range{std::format("{} must be less than {}.", y, m_height)};
        }
    }
    
    void GameBoard::swap(GameBoard& other) noexcept
    {
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
        std::swap(m_cells, other.m_cells);
    }
    
    void swap(GameBoard& first, GameBoard& second) noexcept
    {
        first.swap(second);
    }
    
    GameBoard& GameBoard::operator=(const GameBoard& rhs)
    {
        GameBoard temp{rhs};
        swap(temp);
        return *this;
    }
    
    const unique_ptr<GamePiece>& GameBoard::at(size_t x, size_t y) const
    {
        verifyCoordinate(x, y);
        return m_cells[x][y];
    }
    
    unique_ptr<GamePiece>& GameBoard::at(size_t x, size_t y)
    {
        return const_cast<unique_ptr<GamePiece>&>(as_const(*this).at(x, y));
    };
    ~~~

    这个 GameBoard 类可以很好地完成任务。

    ~~~c++
    GameBoard chessBoard{8, 8};
    auto      pawn{std::make_unique<ChessPiece>()};
    chessBoard.at(0, 0) = std::move(pawn);
    chessBoard.at(0, 1) = std::make_unique<ChessPiece>();
    chessBoard.at(0, 1) = nullptr;
    ~~~

2. 模板 Grid 类
3. 使用 Grid 模板

## 16 C++标准库概述

### 16.2 C++标准库概述

#### 16.2.1 字符串

（参见第 2 章）
C++在 ***\<string>*** 头文件提供内建的 string 类。
还提供在 ***\<string_view>*** 中定****义的 string_view 类，这是各类字符串表示的只读视图，可用于简单替换 const string&

#### 16.2.2 正则表达式

（参见第 19 章）
***\<regex>*** 头文件中提供了正则表达式

#### 16.2.3 I/O流

（参见第 13 章）
I/O功能在如下几个头文件中定义：

- \<fstream>
- \<iomanip>
- \<ios>
- \<iosfwd>
- \<iostream> \<istream> \<ostream>
- \<sstream>
- \<streambuf>
- \<strstream>

#### 16.2.4 智能指针

（参见第 7 章）
智能指针在 ***\<memory>*** 头文件中定义

- unique_ptr
- shared_ptr
- week_ptr

#### 16.2.6 数学工具

暂略

#### 16.2.12 函数对象

（参见第 18 章，18 章还详细论述标准库算法）
实现函数调用运算符的类称为函数对象

#### 16.2.13 文件系统

（参见第 20 章）
所有内容在 ***\<filesystem>*** 头文件中定义，位于 std::filesytstem 名称空间。

#### 16.2.16 标准整数类型

（参见第30章）
***\<cstdint>*** 头文件定义了大量标准整数类型，如 int8_t 和 int64_t 等

#### 16.2.17 容器

1. vector
    非固定大小容器
2. list
3. forward_list
4. deque
5. array
    基本上是对C风格数组进行了简单包装，有固定大小
6. queue
7. priority_queue
8. stack
9. set 和 multiset
10. map 和 multimap
11. 无序关联容器/哈希表
    - unordered_map
    - unordered_multimap
    - unordered_set
    - unordered_multiset
12. bitset

#### 16.2.18 算法

（参见第 17、18 章）
泛型算法，适用于大部分不同类型的容器
除非特别声明，否则这些算法都在 **\<algorithm>** 头文件中定义  

迭代器
| 函数名              | 概要                                              |
| ------------------- | ------------------------------------------------- |
| begin()、end()      | 返回序列第一个和最后一个元素的非 const 迭代器     |
| cbegin()、cend()    | 返回序列第一个和最后一个元素的 const 迭代器       |
| rbegin()、rend()    | 返回序列第一个和最后一个元素的反向非 const 迭代器 |
| crbegin()、cerend() | 返回序列第一个和最后一个元素的反向 const 迭代器   |

1. 非修改顺序算法
    查找元素的序列，返回一些有关元素的信息。因为是非修改类的算法，所以这些算法不会改变序列中元素的值或顺序
    **搜索算法**
    | 算法名称          | 算法概要                                                                     |
    | ----------------- | ---------------------------------------------------------------------------- |
    | adjacent_find()   | 查找有两个连续元素或匹配谓词的第一个实例                                     |
    | find()、find_if() | 查找第一个匹配值或使谓词返回 true 的元素                                     |
    | find_first_of()   | 与 find() 类似，只是同时搜索多个元素中的某个元素                             |
    | find_if_not()     | 查找第一个使谓词返回 false 的元素                                            |
    | find_end()        | 在序列中查找最后一个匹配另一个序列的子序列，这个子序列的元素和谓词指定的一致 |
    | search()          | 功能同上，不过在序列中查找第一个匹配另一个序列的子序列                       |
    | search_n()        | 查找前 n 个等于某个给定值或根据某个谓词和那个值相关的连续函数                |

    **比较算法**
    | 算法名称                  | 算法概要                                                       |
    | ------------------------- | -------------------------------------------------------------- |
    | equal()                   | 检查相应元素是否相等或匹配谓词，以判断两个序列是否相等         |
    | mismatch()                | 返回每个序列中第一个出现的和其他序列中同一位置元素不匹配的元素 |
    | lexicographical_compare() | 略，去看书                                                     |

    **计数算法**

    | 算法名称           | 算法概要                                                                    |
    | ------------------ | --------------------------------------------------------------------------- |
    | all_of()           | 如果序列为空，或谓词对序列所有元素都返回 true，则返回 true，否则返回 false  |
    | any_of()           | 如果谓词对序列中的至少一个元素返回 true，则返回 true，否则返回 false        |
    | none_of()          | 如果序列为空，或谓词对序列所有元素都返回 false，则返回 true，否则返回 false |
    | count() count_if() | 计算匹配某个值或使谓词返回 true的元素个数                                   |
