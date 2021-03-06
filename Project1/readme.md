
#### 引言
本项目是针对《数据结构、算法与应用C++语言描述》第二版（美国Sartaj Sahni编著，王立柱 刘志红译）一书，跟随书中的知识点系统性学习和回顾数据结构。
数据对象：是一组实例或值；  
数据结构：是一个数据对象，同时这个对象的实例以及构成实例的元素都存在中而联系，而且这些联系由相关的函数来规定。  

#### 第五、六章 线性表
本章主要引入的数据结构概念有：  
* 抽象数据类型和相应的C++抽象类；  
* 线性表；  
* 边长数组和数组容量倍增；  
* 数组描述；  
* 数据结构迭代器。  
本章新增的C++概念有：  
* 抽象类  
* 迭代器  

##### 1 性能测量
 * 内存比较  
 在数组描述的线性表中，当数组满时，数组长度加倍，当数组空间占有率不足25%时，数组长度要减半。因此，具有n个元素的线性表可以存储在一个长度介于n和4n之间的数组中，当用链表来
 描述线性表时，n个元素正好分配n个节点空间，每个节点空间有两个域，因此，链表描述需要n个元素空间和n个指针空间。  
 所以：n个元素的线性表，每个元素需要s个字节，那么数组描述需要的字节数在`ns`和`4ns`之间，而链表描述需要的字节数是`n(s+4)`。  
 在选择线性表的描述方法时，空间需求上的差别不是决定性因素。  
 * 运行时间比较  
 在时间需求方面:  `get`函数：`chain<T>::get`比`arrayList<T>::get`要慢得多，前者是`O(listSize)`，后者是`O(1)`;   
 `indexOf`函数，`chain<T>::indexOf`用时大概是`arrayList<T>::indexOf`的6倍;  
 在平均情况下，插入和删除操作，链表的用时大约分别是数组的33倍和46倍。  
 * 其他  
 尽管链表描述的线性表表现不好，但是在若干线性表的应用中，它比数组描述的线性表更有效。比如，把多个表合并为一个表等。

 
##### 2 箱子排序
即排序问题中的计数排序

##### 3 并查集（union-find）
* 等价类  
 > 假定一个具有n个元素的集合`U=1,2,...,n`和一个具有`r`个关系的集合`R=(i1,j1),(i2,j2),...(ir,jr)`。关系`R`是一个**等价关系**，当且仅当如下条件为真：  
 > * 对于所有的`a∈U`，有`(a,a)∈R`时（关系是自反的）。  
 > * `(a,b)∈R`,当且仅当`(b,a)∈R`（关系是对称的）。  
 > * 若`(a,b)∈R`,且`(b,c)∈R`，则有`(a,c)∈R`（关系是传递的）。  
 在给出等价关系`R`时，我们常常会忽略其中的某些数对，这些数对可以应用自反性、对称性、传递性得到。  
 **如果`(a,b)∈R`。则元素`a`和`b`是等价的。**  

所谓等价类，是指相互等价的元素的最大集合。“最大”以为这不存在在类以外的元素与类内部的元素等价。因为一个元素只能属于一个等价类，等价关系吧集合`U`划分为不相交的等价类。  

* 在线等价类  
 初始时有n个元素，每个元素都属于一个独立的等价类。需要执行以下的操作：  
 1、`combine(a,b)`，把包含a和b的等价类合并成一个等价类；  
 2、`find(theElement)`，确定元素theElement在哪一个类，目的是对给定的两个元素，确定是否属于同一个类，它对同一个类的元素返回相同的结果，而对不同类的元素，返回不同的结果。  

* 并查集  
 本部分主要考虑在线等价类问题，这类问题通常又称为并查集问题。
* 应用实例  
**机器调度问题**  
 某工厂有一台机器能够执行n个任务，任务i的开始时间为整数ri，截止时间为整数di，设计一个调度的直观方法如下：  
  1、按开始时间的非递增次序对任务进行排序 ；  
  2、按开始时间的非递增次序考察任务，对于每个任务，确定一个空闲时间段，这个时间段在截止时间之前，但与截止时间最接近。如果这个空闲实现段位于任务的开始时间之前，则分配失败，
 否则就把这个时间段分配给该任务。  
**布线问题**  
 一个电路由构建、管脚和电线构成，每根电线连接一对管脚，两个管脚a和b是电子等价当且仅当有一根电线直接连接a和b，或者存在一个管脚序列`i1,i2,...,ik`，使得在管脚对序列`a,i1;i1,i2;i2,i3;...;i(k-1),i(k);i(k),b`
 中，每一对管脚均有电线直接连接。一个网络net是指由电子等价的管脚所构成的最大集合。“最大”是指不存在网络外的管脚与网络内的管脚电子等价。  
 对于在线网络搜索问题，起始时有一组管脚的集合，没有电线，然后要执行如下操作：  
  1、增加一根连接a和b的电线；  
  2、搜索包含管脚a的网络。搜索的目的是确定两个管脚是否属于同一网络。

* 并查集解决方案
 * 1、第一种并查集解决方案  
  使用一个数组`equivClass`，且令`equivClass[i]`为包含元素i的等价类。初始化、合并及搜索的方法如程序6-19所示。  
  时间复杂度：通常执行一次初始化、u次合并和f次查找，时间复杂度为O(n+u*n+f)  
 * 2、第二种并查集解决方案  
  如果一个等价类对应一个链表，那么合并操作的时间复杂度就可以降低，因为在一个等价类中，可以沿着链表的指针找到所有的元素，而不必去检查所有的equivClass的值。
  事实上，如果知道每一个等价类的大小，我们可以选择较小的类来改变equivClass的值，从而加快合并速度。通过使用整型指针就可以快速访问元素e的节点，我们采用如下约定：  
   > * `equivNode`是一个结构，具有数据成员`equivClass、size、next`；  
   > * 类型为equivNode的数组`node[1:n]`用于描述n和元素，每个元素都有一个对应的等价类链表；  
   > * `node[e].equivClass` 既是函数find(e)的返回值，也是一个整型指针，该指针指向等价类 `node[e].equivClass`的链表的首节点；  
   > * 只有e是链表的首节点，才定义`node[e].size`，这是，`node[e].size`表示从`node[e]`开始的链表的节点个数；  
   > * `node[e].next`给出了包含节点e的链表的下一个节点，以为节点从1至n编号，所以可以用0来表示空指针NULL。
  时间复杂度：通常执行一次初始化、u次合并和f次查找，时间复杂度为O(n+u*logu+f)  

#### 第七章 数组与矩阵
##### 1 数组  
 * 抽象数据类型  
  一个数组的每一个实例都是形如（索引，值）的数对集合，其中任意两个数对的索引都不相同。有关数组的操作如下：  
  > * 取值——对一个给定的索引，取对应数对中的值；
  > * 存值——把一个新数对加到数对集合中。如果已存在一个索引相同的数对，就用新数对覆盖。

##### 2 矩阵
 一个m*n的矩阵是一个m行、n列的表，m和n是矩阵的维数。常见的操作有矩阵转置、矩阵相加、矩阵相乘。  
 * 行主映射，映射函数：`map(i,j) = i * columns + j`，其中`columns`表示数组的列数。
##### 3 特殊矩阵
 * 对角矩阵：`if i != j, M(i,j) = 0;`  
 * 三对角矩阵：`if |i - j| > 1, M(i, j) = 0;`  
 * 下三角矩阵：`if i < j, M(i, j) = 0;`  
 * 上三角矩阵：`if i > j, M(i, j) = 0;`  
 * 对称矩阵：`M(i, j) = M(j, i)`.
##### 4 稀疏矩阵
 一个m*n的矩阵，如果大多数元素都是0，则称为稀疏矩阵，一个矩阵如果不是稀疏的，就称为稠密矩阵。该部分着重分析非0区域不规则的稀疏矩阵。  
 * 用单个线性表描述  
	> 为了重建矩阵结构，必须记录每个非0元素的行号和列号，因此数组元素需要三个域：row（矩阵元素所在行）、col（矩阵元素所在列）和value（矩阵元素的值）。  
	为此定义丁姐matrixTerm，使其具有三个数据成员，整型row、col和T类型value。  
 * 用多个线性表描述  
   > 如果把每一行的非0元素用一个线性表存储，就得到描述稀疏矩阵的另一种方法。  
##### 5 性能比较
 类sparseMatrix和linkedMatrix对空间的需求近似，然而对前者可以改进，减少33%的空间，但是没有减少运行时间。linkedMatrix方法虽然比sparseMatrix方法慢，
 但是比2DArray方法；sparseMatrix方法与2DArray方法比，时间减少的程度比较显著，矩阵加法和转置的时间大约是后者的1/20.  

#### 第十章 跳表和散列
 跳表：增加了额外的向前指针的链表叫做跳表。它采用随机技术来决定链表的哪些节点应增加向前指针，以及增加多少个指针。基于这种随机技术，跳表的查找、插入、删除的平均
 时间复杂度都是`O(logn)`，然而，最坏的情况下的时间复杂度是`O(n)`.  
 散列：用来查找、插入、删除的另一种随机方法。与跳表相比，它把操作时间提高到`O(1)`，但最坏情况下的时间仍然是`O(n)`。  
 有序数组、有序链表、跳表、哈希表的渐进性能汇总  
 表10.1 有序数组、有序链表、跳表、哈希表的渐进性能最坏情况    

 | 方法 |  查找|插入   |删除  |
 |--|--|--|--|
 | 有序数组 | O(logn) |  O(n) |O(n)  |
 |有序链表  | O(n) | O(n) | O(n) |
 | 跳表 | O(n)| O(n)| O(n)|
 | 哈希表 | O(n)| O(n)| O(n)|


 表10.2 有序数组、有序链表、跳表、哈希表的渐进性能平均情况  

 | 方法 |  查找|插入   |删除  |
 |--|--|--|--|
 | 有序数组 | O(logn) |  O(n) |O(n)  |
 |有序链表  | O(n) | O(n) | O(n) |
 | 跳表 | O(logn)| O(logn)| O(logn)|
 | 哈希表 | O(1)| O(1)| O(1)|

##### 1 字典 
 字典是由一些形如`(k,v)`的数对所组成的集合，其中k是关键字，v是与关键字k对应的值，反之也可以，任意两个数对，其关键字都不等。  
 有关字典的操作有：
  > * 确定字典是否为空;
  > * 确定字典有多少数对；
  > * 寻找一个指定了关键字的数对；
  > * 插入一个数对；
  > * 删除一个指定了关键字的数对。  
  * **抽象数据类型**
 抽象数据类型 Dictionary
 {
 	实例
		关键字各不相同的一组数据对
	操作
		empty():返回true，当且仅当字典为空
		size():返回字典的数对个数
		find(k):返回关键字为k的数对
		insert(p):插入数对p
		erase(k):删除关键字为k的数对
 }
 * **线性表描述**
  字典可以保存在线性表`(p0,p1,...)`中，其中pi是字典中按关键字递增次序排列的数对。为了适应这种表示方式，可以定义两个类`sortedArrayList`和`sortedChain`，分别
  表示用数组描述线性表和用链表描述线性表。  
##### 2 跳表  
 > 增加了向前指针的链表叫做跳跃表，简称跳表。跳表是一个随机化的数据结构，实质上是一种可以进行二分查找的有序链表。跳表在原有的有序链表上面增加了多级索引，通过索引
 来实现快递查找。跳表不仅能提高搜索性能，同时还能提高插入、删除操作的性能。  
 对n个数对而言，0级链表包括所有数对，1级链表每2个数对取一个，2级链表每4个数对取一个，i级链表每2^i^个数对取一个。一个数对属于i级链表，当且仅当它属于0~i级链表，但不属于i+1级链表。
 * 跳表的结构体  
  >  跳表结构的头节点需要有足够的指针域，以满足最大链表级数的构建需要，而尾结点不需要指针域。每个存有数对的节点都有一个存储数对的element域和个数大于自身级数的指针域。

 * 跳表的类  
  (1)类的数据成员  
  | 数据成员 | 意义 |  
|--|--|
| float cutoff | 用来确定层数 |  
| int levels | 当前最大的非空链表 |  
| int dSize | 字典的数对个数 |  
| int maxLevel | 允许的最大链表层数 |  
| K  tailKey | 最大关键字 |  
| skipNode<K, E>* headerNode | 头节点指针 |  
| skipNode<K, E>* tailNode | 尾结点指针 |  
| skipNode<K, E>** last | last[i]表示i层的最后节点 |  
(2) 类的构造函数  



