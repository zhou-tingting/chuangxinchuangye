实验内容
====
Impl Merkle Tree following RFC6962

运行指导
===
Merkle Tree.cpp为实现代码，可以直接在VS2019上运行

主要函数说明
====
define New_Merkle_Node(tree, depth)//用于创建新节点的宏函数  
void print_Merkletree(Merkletree* tree, int high)//打印Merkletree  
uint hash(char* string1, char* string2)//计算字符串的hash值  
uint hash_nodes(uint n1, uint n2)//计算两个旧节点生成的新节点的哈希值  
Merkletree* last_node(Merkletree* tree)//找Merkletree最后一个节点  
Merkletree* find_Empty_Node(Merkletree* tree)//寻找可插入的空节点  
Merkletree* Creat_Merkle_Tree(Merkletree* tree, char** s, int n)//根据RFC6962要求创建Merkletree  
char** divide_string(char* str, int* number)//字符串分割  
void delete_tree(Merkletree* tree)//删除Merkletree

参考文献
====
https://blog.csdn.net/Ciellee/article/details/108073025  

运行结果
====
![IFYI)N_WS07G{ 8ET35SRUQ](https://user-images.githubusercontent.com/109579171/181785885-ceb14cb2-f72d-44b6-8d35-c8440a2bc685.png)
