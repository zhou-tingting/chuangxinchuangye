实验简介：
=====
Rho.py是用Rho方法寻找SM3碰撞的代码。
截图里面分别是实现4，8，12，16，20，24比特碰撞攻击的结果，随着碰撞位数的增加，攻击时间增长，故当实现28比特及以上攻击时，运行时间很长，在此处没有展示。

实验内容：
====
将所有生成的hash值放入一条链中。随机生成字符串并计算其计算hash值，如果此哈希值已经在链中，说明此时已经成环，找到了碰撞。
函数rho_attack(n)为rho算法函数，f函数为2*x+1。

实验运行结果：
===
![1](https://user-images.githubusercontent.com/109579171/181904398-d032bb61-1c61-444c-a0be-b57eda0e1ed8.png)
![2](https://user-images.githubusercontent.com/109579171/181904401-d7d3076e-3cda-4f83-8b6b-eedace64fc43.png)
![3](https://user-images.githubusercontent.com/109579171/181904403-a316bd06-a465-4013-9725-7104998338b2.png)
![4](https://user-images.githubusercontent.com/109579171/181904405-ea796c4e-2f16-4ba4-be7a-05abec5f1791.png)
![5](https://user-images.githubusercontent.com/109579171/181904410-8a11aa83-f0ac-4d1d-bcbd-1811a1eed53a.png)
![6](https://user-images.githubusercontent.com/109579171/181904412-468ea94a-ae33-4787-ba5b-d32f59e37382.png)
