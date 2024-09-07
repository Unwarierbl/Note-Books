# mermaid 语法

## mermaid 类图

抄自 <https://blog.csdn.net/u012787240/article/details/112847071>

类图用于面向对象对于应用结构概念建模, 也用于把具体的模型翻译成程序代码. 类图也可以用于数据建模

### 语法

#### 类结构

顶部代表类名称, 中部代表类成员变量, 底部代表类成员函数

~~~
classDiagram
class BankAccount {
    +String ower
    +Bigdecimal balance
    +deposit(amount)
    +withdraw(amount)
}
~~~

~~~mermaid
classDiagram
class BankAccount {
    +String ower
    +Bigdecimal balance
    +deposit(amount)
    +withdraw(amount)
}
~~~

### 定义类

- 显示声明：<code><font color=Brown>class Animal</font></code>
- 通过关系声明：<code><font color=Brown>Vehicle <|-- Car</font></code>

~~~
classDiagram
class Animal
Vehicle <|-- Car
~~~

~~~mermaid
classDiagram
class Animal
Vehicle <|-- Car
~~~

### 定义类的成员

包括了属性和方法, 还有额外信息

区分方法和属性的决定性符号是 <code><font color=Brown>()</font></code>, 定义类成员有两种办法

- 类外定义

    ~~~
    classDiagram
    class Dog
    Dog : +String name
    Dog : +bark()
    Dog : +eat(food) bool
    ~~~

    ~~~mermaid
    classDiagram
    class Dog
    Dog : +String name
    Dog : +bark()
    Dog : +eat(food) bool
    ~~~

- 类内部定义, 用大括号

~~~
classDiagram
class Dog {
    +String name
    +bark()
    +eat(food) bool
}
~~~

~~~mermaid
classDiagram
class Dog {
    +String name
    +bark()
    +eat(food) bool
}
~~~

### 返回值

返回值在右括号后面添加

### 泛型类型

泛型用<code><font color=Brown>~</font></code>代替两个尖括号

~~~
classDiagram
class Squre~Shape~{
    int id
    List~int~ position
    setPoints(List~int~ points)
    getPoints() List~int~
}
~~~

~~~mermaid
classDiagram
class Squre~Shape~{
    int id
    List~int~ position
    setPoints(List~int~ points)
    getPoints() List~int~
}
~~~

### 可见性

类成员的可见性有四种:

- <code><font color=Brown>+</font></code> public
- <code><font color=Brown>-</font></code> private
- <code><font color=Brown>#</font></code> protected
- <code><font color=Brown>~</font></code> package/internal

还有静态和虚函数

- <code><font color=Brown>\*</font></code> abstract：<code><font color=Brown>someAbstractMethod()*</font></code>
- <code><font color=Brown>\$</font></code> static：<code><font color=Brown>someStaticMethod()$</font></code>

### 定义关系

主要语法

~~~
[classA][Arrow][ClassB]:LabelText
~~~

不同箭头代表的意思:

|                    类型                    |       描述        |
| :----------------------------------------: | :---------------: |
| <code><font color=Brown><¦-–</font></code> | (Inheritance)继承 |
| <code><font color=Brown>*--</font></code>  | (Composition)组合 |
| <code><font color=Brown>o--</font></code>  | (Aggregation)聚合 |
| <code><font color=Brown>--></font></code>  | (Association)关联 |
|  <code><font color=Brown>--</font></code>  |  (Link)实线连接   |
| <code><font color=Brown>..></font></code>  | (Dependency)依赖  |
| <code><font color=Brown>…¦></font></code>  | (Realization)实现 |
|  <code><font color=Brown>..</font></code>  |  (Link)虚线连接   |

~~~
classDiagram
classA <|-- classB : Inheritance
classC *-- classD : Composition
classE o-- classF : Aggregation
classG <-- classH : Association
classI -- classJ : Link
classK <.. classL : Dependency
classM <|.. classN : Realization
classO .. classP : Link
~~~

~~~mermaid
classDiagram
classA <|-- classB : Inheritance
classC *-- classD : Composition
classE o-- classF : Aggregation
classG <-- classH : Association
classI -- classJ : Link
classK <.. classL : Dependency
classM <|.. classN : Realization
classO .. classP : Link
~~~

把箭头反向也可以用

### 多重和乘数关系

一般用在Link关系上, 表示类间的关系

- <code><font color=Brown>0</font></code> 只有 1 个
- <code><font color=Brown>0..1</font></code> 0 个或 1 个
- <code><font color=Brown>1..*</font></code> 1 个或多个
- <code><font color=Brown>\*</font></code> 多个
- <code><font color=Brown>n</font></code> n 个 {n>1}
- <code><font color=Brown>0..n</font></code> 0~n {n>1}
- <code><font color=Brown>1..n</font></code> 1~n {n>1}

样式（也可以在引号内写自己的文本）

~~~
[classA] "cardinality1" [arrow] "cardinality2" [classB]:LabelText
~~~

~~~
classDiagram
Customer "1" --> "*" Ticket
Student "1" --> "1..*" Course
Glaxy --> "many" Star : Contains
~~~

~~~mermaid
classDiagram
Customer "1" --> "*" Ticket
Student "1" --> "1..*" Course
Glaxy --> "many" Star : Contains
~~~

### 类的注解

对类进行文本标识像元信息, 对性质进行清晰的指示, 例如:

- <code><font color=Brown><\<interface>></font></code> 接口类
- <code><font color=Brown><\<abstract>></font></code> 抽象类
- <code><font color=Brown><\<service>></font></code> 服务类
- <code><font color=Brown><\<enumeration>></font></code> 枚举

在单独的行声明:

~~~
classDiagram
class Shape{
    draw()*
}
<<interface>> Shape
~~~

~~~mermaid
classDiagram
class Shape{
    draw()*
}
<<interface>> Shape
~~~

在类内部:

~~~
classDiagram
class Shape{
    <<interface>>
    draw()*
    count()$
    size()
}

class Color{
    <<enumeration>>
    RED
    BLUE
    GREEN
    WHITE
    BLACK
}
~~~

~~~mermaid
classDiagram
class Shape{
    <<interface>>
    draw()*
    count()$
    size()
}

class Color{
    <<enumeration>>
    RED
    BLUE
    GREEN
    WHITE
    BLACK
}
~~~

### 注释

mermaid 注释用%%开头

## mermaid 流程图

抄自
<https://blog.csdn.net/qq_57508808/article/details/136110461>

### 声明图像类型

告诉 Mermaid 下列语法是什么图像
可以用<code><font color=Brown>flowchart</font></code>或<code><font color=Brown>graph</font></code>声明流程图类型

### 声明排列方向

告诉 Mermaid 流程图的排列方向
其中：<code><font color=Brown>L</font></code>代表<code><font color=Brown>Left</font></code>左边、<code><font color=Brown>R</font></code>代表<code><font color=Brown>Right</font></code>右边、<code><font color=Brown>T</font></code>代表<code><font color=Brown>Top</font></code>上面、<code><font color=Brown>B</font></code>代表<code><font color=Brown>Bottom</font></code>下面，顺序为左边的字母到右边的字母

| 顺序字母 | 代表意义 | 顺序字母 | 代表意义 |
| :------: | :------: | :------: | :------: |
|    TB    | 自上而下 |    BT    | 自下而上 |
|    RL    | 从右到左 |    LR    | 从左到右 |

~~~
flowchart TB
    subgraph 从左到右
      direction LR
      声明图像类型1 --> 声明排列方向1 --> 声明图像内容1
    end
    subgraph 从右到左
      direction RL
      声明图像类型2 --> 声明排列方向2 --> 声明图像内容2
    end
    subgraph 上下分明
      direction LR
      subgraph 从上到下
        direction TB
        声明图像类型3 --> 声明排列方向3 --> 声明图像内容3
      end
      subgraph 从下到上
        direction BT
        声明图像类型4 --> 声明排列方向4 --> 声明图像内容4
      end
      从上到下 --> 从下到上
    end
    从左到右 --> 从右到左 --> 上下分明
~~~

~~~mermaid
    flowchart TB
      subgraph 从左到右
        direction LR
        声明图像类型1 --> 声明排列方向1 --> 声明图像内容1
      end
      subgraph 从右到左
        direction RL
        声明图像类型2 --> 声明排列方向2 --> 声明图像内容2
      end
      subgraph 上下分明
        direction LR
        subgraph 从上到下
          direction TB
          声明图像类型3 --> 声明排列方向3 --> 声明图像内容3
        end
        subgraph 从下到上
          direction BT
          声明图像类型4 --> 声明排列方向4 --> 声明图像内容4
        end
        从上到下 --> 从下到上
      end
      从左到右 --> 从右到左 --> 上下分明
~~~

### 声明节点

有两种声明节点的方式
<code><font color=Brown>直接声明</font></code>：直接在<code><font color=Brown>连接声明区域声明节点</font></code>，此时节点名字作为节点内容，节点样式采用默认样式（即<code><font color=Brown>[]</font></code>样式）
<code><font color=Brown>完整声明</font></code>：使用<code><font color=Brown>节点名字[节点内容]</font></code>声明节点，其中的<code><font color=Brown>[]</font></code>代表节点样式，可以改变它以改变节点样式

如采用<code><font color=Brown>完整声明</font></code>则在<code><font color=Brown>连接声明区域</font></code>内以<code><font color=Brown>节点名字</font></code>指代节点

<code><font color=Brown>完整声明</font></code>中的<code><font color=Brown>节点内容</font></code>可以使用<code><font color=Brown>Unicode 字符</font></code>或<code><font color=Brown>Markdown 语法</font></code>

- 使用<code><font color=Brown>Unicode 字符</font></code>时应该将节点内容以<code><font color=Brown>" "</font></code>包裹
- 使用<code><font color=Brown>Markdown 语法</font></code>时应该将节点内容以<code><font color=Brown>"\` `"</font></code>包裹

**每个节点名字都是唯一的!**

~~~
graph TB
    subgraph 直接声明
      direction LR
      普通节点1 --> 普通节点2 --> 普通节点3
    end
    subgraph 完整声明
      普通节点[这是一个普通节点]
      Unicode节点["🐳Unicode节点"]
      Markdown节点["`**第一行**
                    *第二行*
                    ***第三行***`"]
      普通节点 --> Unicode节点 --> Markdown节点
    end
    直接声明 --> 完整声明
~~~

~~~mermaid
graph TB
    subgraph 直接声明
      direction LR
      普通节点1 --> 普通节点2 --> 普通节点3
    end
    subgraph 完整声明
      普通节点[这是一个普通节点]
      Unicode节点["🐳Unicode节点"]
      Markdown节点["`**第一行**
                    *第二行*
                    ***第三行***`"]
      普通节点 --> Unicode节点 --> Markdown节点
    end
    直接声明 --> 完整声明
~~~

### 声明节点形状

在介绍<code><font color=Brown>完整声明</font></code>时有提到过可以自定义节点样式，例如使用<code><font color=Brown>[ ]</font></code>包裹节点内容就代表这个节点是默认样式
我们除了默认样式外，Mermaid 还可以定义其它很多的节点样式

| 节点样式 |  样式语法  | 节点样式 |  样式语法  | 节点样式 | 样式语法  |
| :------: | :--------: | :------: | :--------: | :------: | :-------: |
|   默认   |  \[文本]   |   圆边   |   (文本)   |   胶囊   | (\[文本]) |
|  子程序  | \[\[文本]] |   圆柱   | \[(文本)]  |   圆形   | ((文本))  |
|  六边形  |  {{文本}}  |   棱形   |   {文本}   | 正四边形 | \[/文本/] |
| 反四边形 | [\\文本\\] |  正梯形  | [/文本\\]  |  反梯形  | [\文本/]  |
|   旗帜   |   >文本]   |   双圆   | (((文本))) |          |           |

~~~mermaid
graph TB
    subgraph 1
        direction LR
        默认[默认] --> 子程序[[子程序]] --> 六边形{{六边形}} -->反四边形[\反四边形\] --> 旗帜>旗帜] --> 双圆(((双圆))) --> 正梯形[/正梯形\]
    end
    subgraph 2
        direction LR
        棱形{棱形} --> 圆柱[(圆柱)] --> 圆边(圆边) --> 胶囊([胶囊]) --> 圆形((圆形)) --> 正四边形[/正四边形/] --> 反梯形[\反梯形/]
    end
    1 --> 2
~~~

### 声明节点间的连接

声明节点间的连接使得有关联的节点能被 Mermaid 识别并绘制连接线
声明单个连接语法<code><font color=Brown>A --> B</font></code>能够声明<code><font color=Brown>一条 A 到 B 链接</font></code>
声明多个连接语法<code><font color=Brown>A --> B --> C</font></code>能够声明<code><font color=Brown>A 到 B、B 到 C 共两条链接</font></code>
多个节点聚合声明语法<code><font color=Brown>A & B --> C</font></code>能够对多个节点进行操作<code><font color=Brown>声明 A 到 C、B 到 C 共两条链接</font></code>

~~~
graph LR
    A --单连接声明--> B
    B --多连接声明--> C --多连接声明--> D
    D --多节点聚合--> E & F --多节点聚合--> A
~~~

~~~mermaid
graph LR
    A --单连接声明--> B
    B --多连接声明--> C --多连接声明--> D
    D --多节点聚合--> E & F --多节点聚合--> A
~~~

### 调整链接的长度

在某些情况下，可以大致定义链接的长度而改善 Mermaid 画出的图形
Mermaid 内可以定义链接跨越的级数以调整链接长度
想要跨越多少级数，只需要在正常的连接符号上加入对应数量的<code><font color=Brown>-</font></code>、<code><font color=Brown>.</font></code>、<code><font color=Brown>=</font></code>等符号即可

~~~
graph LR
    subgraph 没调整链接长度之前
      direction TB
      %% A --> B 的链接声明是正常的
      A --> B --> D
      D --> E
      E --> B
    end
    subgraph 调整了链接长度之后
      direction TB
      %% A ---> B 的链接声明多了一个 - 符号
      %% 代表着跨1个级别
      A1 ---> B1 --> D1
      D1 --> E1
      E1 --> B1
    end
    没调整链接长度之前 --调整了A到B的跨级为1--> 调整了链接长度之后
~~~

~~~mermaid
graph LR
    subgraph 没调整链接长度之前
      direction TB
      %% A --> B 的链接声明是正常的
      A --> B --> D
      D --> E
      E --> B
    end
    subgraph 调整了链接长度之后
      direction TB
      %% A ---> B 的链接声明多了一个 - 符号
      %% 代表着跨1个级别
      A1 ---> B1 --> D1
      D1 --> E1
      E1 --> B1
    end
    没调整链接长度之前 --调整了A到B的跨级为1--> 调整了链接长度之后
~~~

### 调整链接的样式

前面举例所使用的链接样式都是-->代表着有向箭头，Mermaid 内还拥有其它很多链接样式

|       链接方式       |                描述                |                示例代码                |
| :------------------: | :--------------------------------: | :------------------------------------: |
|     带箭头的链接     |         带有箭头的直线链接         |                A --> B                 |
|      打开的链接      |         没有箭头的直线链接         |                A --- B                 |
|     链接上的文本     |          在链接上添加文本          |            A -- Text --- B             |
| 带有箭头和文本的链接 |      在带箭头的链接上添加文本      |            A -- Text --> B             |
|       虚线链接       |              虚线链接              |                A -.-> B                |
|   带文本的虚线链接   |          在虚线上添加文本          |            A -. Text .-> B             |
|        粗链接        |             加粗的链接             |                 A == B                 |
|    带文本的粗链接    |          在粗线上添加文本          |             A == Text == B             |
|     看不见的链接     |            不可见的链接            |                A ~~~ B                 |
|      链接的链接      |           同一行多个链接           |     A -- text --> B -- text2 --> C     |
|     节点多个链接     |         同一个节点多个链接         | a --> b & c--> d（a分别到b和c，再到d） |
|     新的箭头类型     |   新的箭头类型，如圆边和交叉边缘   |           A --o B 或 A --x B           |
|      多方向箭头      |             多方向箭头             |          A o--o B 或 A x--x D          |
|     最小链接长度     | 设置链接的最小长度(破折号越多越长) |               A ------ B               |

~~~mermaid
graph LR
A --- B --标签---C --> D --标签--> E <--> F -.-> G -.标签.-> H <-.-> I
~~~

~~~mermaid
graph LR
J ==> K ==标签==> L --o M o--o N --x O x--x P
~~~

### 字符转义

当你要输入特殊字符（与语法相冲突的字符）时，可以使用<code><font color=Brown>" "</font></code>包裹住你的文本，这样就没有关系了
此外 Mermaid 还支持 HTML 的实体（以<code><font color=Brown>&</font></code>表示的字符）

### 子流程图

在流程图的里面可以嵌入子流程图，子流程图内仍旧可以嵌入子流程图
将子流程图当成一个整体看待的话，它的行为和普通节点基本一致

子流程图的声明语法如下

~~~
subgraph 子流程图名字[子流程图文本内容（标题）]
    direction 子流程图方向
    子流程图具体信息
end
~~~

子流程图实例

~~~
graph TB
A[HTML 基础]
subgraph B[HTML 进阶]
    subgraph 属性[各种属性]
            一般属性 --> 特殊属性
    end
    标签 --> 属性 --> 方法
end
C[HTML 深入]
A --> B --> C
~~~

~~~mermaid
graph TB
A[HTML 基础]
subgraph B[HTML 进阶]
    subgraph 属性[各种属性]
            一般属性 --> 特殊属性
    end
    标签 --> 属性 --> 方法
end
C[HTML 深入]
A --> B --> C
~~~
