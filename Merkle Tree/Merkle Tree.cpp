#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned int uint;
typedef struct MerkleTreeNode
{
	struct MerkleTreeNode* left;
	struct MerkleTreeNode* right;
	struct MerkleTreeNode* parent;
	uint level;//当前节点的树深度
	uint data;
	char* str;
}Merkletree;

//用于创建新节点的宏函数
#define New_Merkle_Node(tree, depth){\
	tree = (Merkletree *)malloc(sizeof(Merkletree));\
	tree->left = NULL;\
	tree->right = NULL;\
	tree->parent = NULL;\
	tree->level = (uint)depth;\
	tree->data = 0;\
	tree->str = NULL;\
}
//打印Merkletree
void print_Merkletree(Merkletree* tree, int high)
{
	Merkletree* p = tree;
	int i;
	if (p == NULL)
		return;
	if (p->left == NULL && p->right == NULL)
	{
		for (int i = 0; i < high - p->level; i++)
			printf("\t");

		printf("-->%s\n", p->str);
	}
	else
	{
		print_Merkletree(tree->left, high);
		printf("\n");
		for (i = 0; i < high - p->level; i++)
			printf("\t");
		printf("-->%-6d\n", p->data);
		print_Merkletree(tree->right, high);
	}
}
//计算字符串的hash值
uint hash(char* string1, char* string2)
{
	uint tmp = 3, hash = 0;

	if (string1 != NULL)
		while (*string1 != '\0' && *string1 != 0)
		{
			hash = hash * tmp + *string1;
			string1++;
		}

	if (string2 != NULL)
		while (*string2 != '\0' && *string2 != 0)
		{
			hash = hash * tmp + *string2;
			string2++;
		}
	return hash & 0x7FFFFFFF;
}

uint hash_nodes(uint n1, uint n2)
{
	uint tmp = 7, hash = 0;
	hash = n1 + n2;
	hash *= tmp;
	return hash & 0x7FFFFFFF;
}
//找Merkletree最后一个节点
Merkletree* last_node(Merkletree* tree)
{
	Merkletree* p = tree, * tmp;
	if (p->left == NULL && p->right == NULL)
		return p;
	else if (p->right == NULL && p->left != NULL)
		return last_node(p->left);
	else if (p->right != NULL)
		return last_node(p->right);
}

Merkletree* find_Empty_Node(Merkletree* tree)
{
	Merkletree* p = tree->parent;
	while (p->left != NULL && p->right != NULL && p->parent != NULL)
		p = p->parent;
	if (p->parent == NULL && p->left != NULL && p->right != NULL)
		return NULL;
	else
		return p;
}

Merkletree* Creat_Merkle_Tree(Merkletree* tree, char** s, int n)
{
	Merkletree* node, * tmp, * p;
	int i;
	if (n == 0)
	{
		printf("初始化完成!\n");
		return tree;
	}
	else
	{
		New_Merkle_Node(node, 0);
		node->str = (char*)malloc(strlen(*s) + 1);
		memset(node->str, '\0', strlen(*s) + 1);
		for (int i = 0; i < strlen(*s); i++)
			node->str[i] = (*s)[i];
		if (tree == NULL)
		{
			New_Merkle_Node(tree, 1);
			tree->left = node;
			node->parent = tree;
			tree->data = hash(tree->left->str, tree->right == NULL ? NULL : tree->right->str);
			tree = Creat_Merkle_Tree(tree, s + 1, n - 1);
		}
		else
		{
			p = find_Empty_Node(last_node(tree));
			if (p != NULL)
			{
				if (p->left->left == NULL && p->right == NULL)
				{
					p->right = node;
					node->parent = p;
					p->data = hash(p->left->str, p->right == NULL ? NULL : p->right->str);
				}
				else
				{
					i = p->level - 1;
					New_Merkle_Node(tmp, i);
					p->right = tmp;
					tmp->parent = p;
					p = p->right;
					i = p->level - 1;
					while (i > 0)
					{
						New_Merkle_Node(tmp, i);
						p->left = tmp;
						tmp->parent = p;
						p = p->left;
						i--;
					}
					p->left = node;
					node->parent = p;
					p->data = hash(p->left->str, p->right == NULL ? NULL : p->right->str);
				}
			}
			else
			{
				tmp = tree;
				New_Merkle_Node(tree, tmp->level + 1);
				tree->left = tmp;
				tmp->parent = tree;
				New_Merkle_Node(tmp, tree->level - 1);
				tree->right = tmp;
				tmp->parent = tree;
				p = tree->right;
				i = p->level - 1;
				while (i > 0)
				{
					New_Merkle_Node(tmp, i);
					p->left = tmp;
					tmp->parent = p;
					p = p->left;
					i--;
				}
				//叶子节点赋值
				p->left = node;
				node->parent = p;
				p->data = hash(p->left->str, p->right == NULL ? NULL : p->right->str);
			}
			if (p != tree)
			{
				p = p->parent;
				while (p != tree)
				{
					p->data = hash_nodes(p->left->data, p->right == NULL ? 0 : p->right->data);
					p = p->parent;
				}
				p->data = hash_nodes(p->left->data, p->right == NULL ? 0 : p->right->data);
			}
			tree = Creat_Merkle_Tree(tree, s + 1, n - 1);
		}
	}
}

char** divide_string(char* str, int* number)
{
	char* p = str, * tmp = str, ** result, ** res;
	int num = 0, i;
	while (*p != '\0')
	{
		if (*p == ',' || *p == '.' || *p == '!' || *p == '?' || *p == ';')
		{
			num += 2;
			tmp = p + 1;
		}
		else if (*p == ' ')
		{
			if (p - tmp == 0)
				tmp = p + 1;
			else
			{
				num += 1;
				tmp = p + 1;
			}
		}
		p++;
	}
	if (p - tmp > 0)
		num += 1;
	result = (char**)malloc(sizeof(char*) * num);
	res = result;
	tmp = str;
	p = str;
	while (*p != '\0')
	{
		if (*p == ',' || *p == '.' || *p == '!' || *p == '?' || *p == ';')
		{
			*res = (char*)malloc(sizeof(char) * (p - tmp + 1));
			memset(*res, '\0', p - tmp + 1);
			for (i = 0; i < p - tmp; i++)
				(*res)[i] = *(tmp + i);
			res++;
			*res = (char*)malloc(sizeof(char) * 2);
			memset(*res, '\0', 2);
			(*res)[0] = *p;
			res++;
			p++;
			tmp = p;
		}
		else if (*p == ' ')
		{
			if (p - tmp == 0)
			{
				p++;
				tmp = p;
			}
			else
			{
				*res = (char*)malloc(sizeof(char) * (p - tmp + 1));
				memset(*res, '\0', p - tmp + 1);
				for (i = 0; i < p - tmp; i++)
					(*res)[i] = *(tmp + i);
				res++;
				p++;
				tmp = p;
			}
		}
		else
			p++;
	}
	if (p - tmp > 0)
	{
		*res = (char*)malloc(sizeof(char) * (p - tmp + 1));
		memset(*res, '\0', p - tmp + 1);
		for (i = 0; i < p - tmp; i++)
			(*res)[i] = *(tmp + i);
	}
	*number = num;
	return result;
}
void delete_tree(Merkletree* tree)
{
	if (tree->level == 0)
	{
		free(tree->str);
		free(tree);
	}
	else
	{
		if (tree->left != NULL)
			delete_tree(tree->left);
		if (tree->right != NULL)
			delete_tree(tree->right);
		free(tree);
	}
}

int main()
{
	int m;
	char** str;
	Merkletree* tree = NULL;
	char message[] = "I love CST.I'm writing a Merkle tree!";
	str = divide_string(message, &m);
	tree = Creat_Merkle_Tree(tree, str, m);
	if (tree != NULL)
	{
		printf("\nMerkle Tree:\n");
		print_Merkletree(tree, tree->level);
		printf("\n\n");
	}
	delete_tree(tree);
	return 0;
}