# IR

## 3AC 三地址码

    等号右边只有一个操作符

## SSA 静态单赋值

    变量新名字 传播用 每个变量定义一次

![1706340963247](image/IR/1706340963247.png)

## Control Flow Analysis 控制流分析

    Control Flow Graph CFG 控制流程图

## Basic  Blocks BB

    Basic blocks (BB) are maximal sequences of consecutive three-address instructions with the properties thatIt can be entered only at the beginning, i.e., the first instruction in the blockIt can be exited only at the end, i.e., the last instruction in the block

    基本块(BB)是连续三地址指令的最大序列，其性质为它只能在开头输入，即在块中的第一条指令它只能在结束时退出，即块中的最后一条指令

## 一个完整的CFG

    ![1706345172045](image/IR/1706345172045.png)

# Data Flow Analysis

## Overview

    Preliminaries of Data Flow Analysis

    Reaching Definitions Analysis

    Live Variables Analysis

    Available Expressions Analysis

## Preliminaries of Data Flow Analysis

### Input and Output States 输入输出状态

* 每一条IR的执行，都会使状态从**输入状态**变成新的**输出状态**
* 输入/输出状态与语句前/后的 **program point（PP）** 相关联。

![image-20210917153822357](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-26f62fefb6662fff27b76ed64df6ba4998095196%2Fimage-20210917153822357.png?alt=media)

![image-20210917154034546](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-e4e6efafc77ecffb5a11fc63c8d5d11266853a16%2Fimage-20210917154034546.png?alt=media)

在数据流分析中，我们会把每一个PP关联一个数据流值，代表在该点中可观察到的抽象的程序状态。

### 关于转移方程约束的概念

分析数据流有前向和后向两种：

![image-20210917162309404](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-95ba87a6a6b9f96ad96720a815248b63af270a8b%2Fimage-20210917162309404.png?alt=media)

### 关于控制流约束的概念

每条语句 s 都会使程序状态发生改变。

B 的输出自然是其输入在经过多次转换后得到的状态。

而 B 的输入要根据数据流分析的需求，对其前驱应用合适的 meet operator 进行处理。后向分析时亦然。

![image-20210917162405362](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-bb7568945f4ad9ae77dae209ca69940f118a7ef7%2Fimage-20210917162405362.png?alt=media)

![](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-804a01f3dd7fc1bc438366fc39732975b1075eb7%2Fimage-20210917162747257.png?alt=media)

### 不会涉及到的概念

* 函数调用 Method Calls
* 我们将分析的是过程本身中的事情，即 Intra-procedural。而过程之间的分析，将在 Inter-procedural Analysis 中介绍
* 变量别名 Aliases
* 变量不能有别名。有关问题将在指针分析中介绍。

## Reaching Definitions Analysis 到达定值分析

#### 基本概念

* 假定 x 有定值 d ( **definition** )，如果存在一个路径，从紧随 d 的点到达某点 p，并且此路径上面没有 x 的其他定值点，则称 x 的定值 d 到达 ( **reaching** ) p。
* 如果在这条路径上有对 x 的其它定值，我们说变量 x 的这个定值 d 被杀死 ( **killed** ) 了

![image-20210917163542130](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-27c24dee014299bc90a54ca370d2f0be7f189460%2Fimage-20210917163542130.png?alt=media)

到达定值可以用来分析未定义的变量。例如，我们在程序入口为各变量引入一个 dummy 定值。当程序出口的某变量定值依然为 dummy，则我们可以认为该变量未被定义。

对于一条赋值语句 D: v = x op y，该语句生成了 v 的一个定值 D，并杀死程序中其它对变量 v 定义的定值。

#### 到达定值中的数据流值

* 程序中所有变量的定值。
* 可以用一个 bit vector 来定义，有多少个赋值语句，就有多少个位。

  ![image-20210917164337106](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-636d998c52ac0af273e0132ee266eb2776960a6a%2Fimage-20210917164337106.png?alt=media)

#### 到达定值的转移方程

![image-20210917165027657](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-3e295f6a541acdebfa6723be3fef4767d341be4a%2Fimage-20210917165027657.png?alt=media)

* 从入口状态删除 kill 掉的定值，并加入新生成的定值。
* v = x op y，gen v, kill 其它所有的 v

#### 到达定值的数据流处理

![image-20210917165047931](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-bf27d0171f4c1a2154ef4ca5a32a314f3ef365bc%2Fimage-20210917165047931.png?alt=media)

* 任何一个前驱的变量定值都表明，该变量得到了定义。

#### 到达定值的算法

![image-20210917165459729](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-d75a2f21a7d73c7b77647552e1d4d8c2b05df0d8%2Fimage-20210917165459729.png?alt=media)

这是一个经典的迭代算法。

* 首先让所有BB和入口的OUT为空。因为你不知道 BB 中有哪些定值被生成。
* 当任意 OUT 发生变化，则分析出的定值可能需要继续往下流动，所需要修改各 BB 的 IN 和 OUT。
* 先处理 IN，然后再根据转移完成更新 OUT。
* 在 gen U (IN - kill) 中，kill 与 gen 相关的 bit 不会因为 IN 的改变而发生改变，而其它 bit 又是通过对前驱 OUT 取并得到的，因此其它 bit 不会发生 0 -> 1 的情况。所以，OUT 是不断增长的，而且有上界，因此算法最后必然会停止。
* 因为 OUT 没有变化，不会导致任何的 IN 发生变化，因此 OUT 不变可以作为终止条件。我们称之为程序到达了不动点（Fixed Point）

## Live Variables Analysis 活跃变量分析

#### 基本概念

* 变量 x 在程序点 p 上的值是否会在某条从 p 出发的路径中使用
* 变量 x 在 p 上活跃，当 且仅存在一条从 p 开始的路径，该路径的末端使用了 x，且路径上没有对 x进行覆盖。
* 隐藏了这样一个含义：在被使用前，v 没有被重新定义过，即没有被 kill 过。

![image-20210917171457003](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-8028408e55824acb82318de3596fed265fae7c92%2Fimage-20210917171457003.png?alt=media)

这个算法可以用于寄存器分配，当一个变量不会再被使用，那么此变量就可以从寄存器中腾空，用于新值的存储。

#### 活跃变量中的数据流值

* 程序中的所有变量
* 依然可以用 bit vector 来表示，每个 bit 代表一个变量

![image-20210917171825938](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-c32987d8974af375601fbedbadf9a35d64c40355%2Fimage-20210917171825938.png?alt=media)

#### 活跃变量的转移方程和控制流处理

![image-20210917184215918](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-dbcba96308e24d66f22932ced97046ce3e2a3da3%2Fimage-20210917184215918.png?alt=media)

* 一个基本块内，若 v = exp, 则 def v。若 exp = exp op v，那么 use v。一个变量要么是 use，要么是 def，根据 def 和 use 的先后顺序来决定。
* **考虑基本块 B 及其后继 S。若 S 中，变量 v 被使用，那么我们就把 v 放到 S 的 IN 中，交给 B 来分析。**
* 因此对于活跃变量分析，其控制流处理是 OUT[B] = IN[S]。
* 在一个块中，若变量 v 被使用，那么我们需要添加到我们的 IN 里。而如果 v 被定义，那么在其之上的语句中，v 都是一个非活跃变量，因为没有语句再需要使用它。
* 因此对于转移方程，IN 是从 OUT 中删去重新定值的变量，然后并上使用过的变量。需要注意，如果同一个块中，变量 v 的 def 先于 use ，那么实际上效果和没有 use 是一样的。

#### 活跃变量的算法

![image-20210917185149738](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-4d4897f46f36ce3ecdbdaa59735ddec022fb04a0%2Fimage-20210917185149738.png?alt=media)

* 我们不知道块中有哪些活跃变量，而且我们的目标是知道在一个块开始时哪些变量活跃，因此把 IN 初始化为空。
* 初始化的判断技巧：may analysis 是空，must analysis 是 top。

## Available Expression Analysis 可用表达式分析

#### 基本概念

* x + y 在 p 点可用的条件：从流图入口结点到达 p 的每条路径都对 x + y 求了值，且在最后一次求值之后再没有对 x 或 y 赋值

可用表达式可以用于全局公共子表达式的计算。也就是说，如果一个表达式上次计算的值到这次仍然可用，我们就能直接利用其中值，而不用进行再次的计算。

#### 可用表达式分析中的数据流值

* 程序中的所有表达式
* bit vector 中，一个 bit 就是一个表达式

![image-20210917193557643](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-e74207dd3eb120f43b9c7d62ac9d79ecedc5c711%2Fimage-20210917193557643.png?alt=media)

#### 可用表达式的转移方程和控制流处理

![image-20210917200639739](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-924d909bf930d008c395ca66c917a4456c1f3fb2%2Fimage-20210917200639739.png?alt=media)

* 我们要求无论从哪条路径到达 B，表达式都应该已经计算，才能将其视为可用表达式，因此这是一个 must analysis。
* 注意到图中，两条不同的路径可能会导致表达式的结果最终不一致。但是我们只关心它的值能不能够再被重复利用，因此可以认为表达式可用。
* v = x op y，则 gen x op y。当 x = a op b，则任何包含 x 的表达式都被 kill 掉。若 gen 和 kill 同时存在，那么以最后一个操作为准。
* 转移方程很好理解，和到达定值差不多。但是，由于我们是 must analysis，因此控制流处理是取交集，而非到达定值那样取并集。

#### 可用表达式的算法

![image-20210917201617719](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-24e381cf0c32e0bf6899805c5af235154203bd01%2Fimage-20210917201617719.png?alt=media)

* 注意此时的初始化：一开始确实无任何表达式可用，因此OUT[entry]被初始化为空集是自然的。但是，其它基本块的 OUT 被初始化为全集，这是因为当 CFG 存在环时，一个空的初始化值，会让取交集阶段直接把第一次迭代的 IN 设置成 0，无法进行正确的判定了。
* 如果一个表达式从来都不可用，那么OUT[entry]的全 0 值会通过交操作将其置为 0，因此不用担心初始化为全 1 会否导致算法不正确。

## 总结

![image-20210917202539780](https://3744927830-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F-MJC1RRYQ991XoNX219t%2Fuploads%2Fgit-blob-f7d238c672f33055777343e79965af4258c83e86%2Fimage-20210917202539780.png?alt=media)

## 划重点

* 三种数据流分析
* 到达定值
* 活跃变量
* 可用表达式
* 三种数据流分析的区别和联系
* 知道迭代算法，以及算法能停机的原因
