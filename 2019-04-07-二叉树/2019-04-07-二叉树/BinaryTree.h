#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//二叉树的初始化
typedef struct Node {
	struct Node *left;
	struct Node *right;
	char value;
}	Node;


// 遍历的思路
//前序遍历
int count = 0;
void PreorderCount(Node *root) {
	if (root != NULL) {
		// 根
		count++;
		PreorderCount(root->left);
		PreorderCount(root->right);
	}
}

// 子问题的思路
//求结点个数
int NodeSize(Node *root) {
	if (root == NULL) {
		return 0;
	}
	else if (root->left == NULL && root->right == NULL) {
		// 可选分支
		return 1;
	}
	else {
		// 本质是后序遍历，左右根
		int left = NodeSize(root->left);
		int right = NodeSize(root->right);
		return left + right + 1;
	}
}
//叶子结点个数（不算根）
int LeafSize(Node *root) {
	if (root == NULL) {
		return 0;
	}
	else if (root->left == NULL && root->right == NULL) {
		// 必须带着
		return 1;
	}
	else {
		// 本质是后序遍历
		int left = LeafSize(root->left);
		int right = LeafSize(root->right);
		return left + right;
	}
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
//求二叉树高度
int Height(Node *root) {
	if (root == NULL) {
		return 0;
	}

	int left = Height(root->left);
	int right = Height(root->right);

	return MAX(left, right) + 1;
}
//第k级结点个数
int KLevelSize(Node *root, int k) {
	if (root == NULL) {
		return 0;
	}

	if (k == 1) {
		// 隐含着 root 不是空树
		return 1;
	}

	int left = KLevelSize(root->left, k - 1);
	int right = KLevelSize(root->right, k - 1);

	return left + right;
}
//构建二叉树
Node * CreateNode(char value) {
	Node * node = (Node *)malloc(sizeof(Node));
	node->value = value;
	node->left = node->right = NULL;
	return node;
}
//二叉树中查找v是否存在，返回对应结点
Node * Find(Node *root, char v) {
	if (root == NULL) {
		return NULL;	// 一
	}

	if (root->value == v) {
		return root;	// 二
	}

	Node *result = Find(root->left, v);
	if (result != NULL) {
		return result;	// 三
	}
	
	result = Find(root->right, v);
	if (result != NULL) {
		return result;	// 四
	}

	return NULL;		// 五
}
//创建二叉树
Node * CreateTestTree() {
	Node *a = CreateNode('A');
	Node *b = CreateNode('B');
	Node *c = CreateNode('C');
	Node *d = CreateNode('D');
	Node *e = CreateNode('E');
	Node *f = CreateNode('F');
	Node *g = CreateNode('G');
	Node *h = CreateNode('H');

	a->left = b; a->right = c;
	b->left = d; 
	b->right = e;
	c->left = f; c->right = g;
	e->right = h;

	return a;
}
//测试以上代码
void Test1() {
	Node *root = CreateTestTree();

	printf("结点个数: %d\n", NodeSize(root));
	printf("叶子结点个数: %d\n", LeafSize(root));
	printf("高度: %d\n", Height(root));
	KLevelSize(root, 3);
	/*
	for (int i = 1; i <= 5; i++) {
		printf("第 %d 层结点个数: %d\n", i, KLevelSize(root, i));
	}
	*/
	Find(root, 'F');
}




// A B D # # # # C E # # F
// 创建的树的根结点, 创建过程中用掉的个数
Node * CreateTree(char preorder[], int size, int *pUsed) {
	if (size == 0) {
		*pUsed = 0;
		return NULL;
	}

	if (preorder[0] == '#') {
		*pUsed = 1;
		return NULL;
	}

	// 递推
	// 根
	Node *root = (Node *)malloc(sizeof(Node));
	root->value = preorder[0];

	// 左子树
	int leftUsed;
	root->left = CreateTree(preorder + 1, size - 1, &leftUsed);
	// 右子树
	int rightUsed;
	root->right = CreateTree(preorder + 1 + leftUsed,
		size - 1 - leftUsed, &rightUsed);

	*pUsed = 1 + leftUsed + rightUsed;
	return root;
}


// size 不是前序序列刚好的长度
Node * CreateTree2(char preorder[], int size, int *pUsed) {
	if (size == 0) {
		*pUsed = 0;
		return NULL;
	}

	if (preorder[0] == '#') {
		*pUsed = 1;
		return NULL;
	}

	// 递推

	// 根
	Node *root = (Node *)malloc(sizeof(Node));
	root->value = preorder[0];

	// 左子树
	int leftUsed;
	root->left = CreateTree2(preorder + 1, size - 1, &leftUsed);
	// 右子树
	int rightUsed;
	root->right = CreateTree2(preorder + 1 + leftUsed,
		size - 1 - leftUsed, &rightUsed);

	// 处理返回
	*pUsed = 1 + leftUsed + rightUsed;
	return root;
}

int find(char array[], int size, char v) {
	for (int i = 0; i < size; i++) {
		if (array[i] == v) {
			return i;
		}
	}

	return -1;
}

// size 树的结点个数
Node * buildTree(char preorder[], char inorder[], int size) {
	if (size == 0) {
		return NULL;
	}

	char rootValue = preorder[0];
	int leftSize = find(inorder, size, rootValue);

	// 根
	Node *root = (Node *)malloc(sizeof(Node));
	root->value = rootValue;
	// 左子树
	root->left = buildTree(
		preorder + 1,// 左子树前序
		inorder,// 左子树中序
		leftSize// 左子树结点个数
		);
	// 右子树
	root->right = buildTree(
		preorder + 1 + leftSize,// 右子树前序
		inorder + leftSize + 1,// 右子树中序
		size - 1 - leftSize// 右子树结点个数
		);

	return root;
}


#include <queue>
//给定一个二叉树，返回其按层次遍历的节点值。
//（即逐层地，从左到右访问所有节点）。
void LevelOrder(Node *root) {
	if (root == NULL) {
		printf("\n");
	}
	std::queue<Node *>	q;
	// 启动
	q.push(root);

	while (!q.empty()) {
		Node *front = q.front();
		q.pop();

		printf("%c ", front->value);

		if (front->left != NULL) {
			q.push(front->left);
		}

		if (front->right != NULL) {
			q.push(front->right);
		}
	}
	printf("\n");
}
//判断二叉树是否是完全二叉树
bool IsComplete(Node *root) {
	if (root == NULL) {
		return true;
	}

	std::queue<Node *> q;
	q.push(root);

	while (true) {
		Node *front = q.front();
		q.pop();
		if (front == NULL) {
			break;
		}

		q.push(front->left);
		q.push(front->right);
	}

	// 判断队列剩余元素是否全是 NULL
	while (!q.empty()) {
		Node *front = q.front();
		q.pop();
		if (front != NULL) {
			return false;
		}
	}

	return true;
}



#include <stack>

void PreOrderNoR(Node *root) {
	std::stack<Node *> s;
	Node *cur = root;

	while (cur != NULL || !s.empty()) {
		while (cur != NULL) {
			printf("%c ", cur->value);
			s.push(cur);
			cur = cur->left;
		}

		Node *top = s.top();
		s.pop();

		cur = top->right;
	}
}


void InOrderNoR(Node *root) {
	std::stack<Node *> s;
	Node *cur = root;

	while (cur != NULL || !s.empty()) {
		while (cur != NULL) {
			s.push(cur);
			cur = cur->left;
		}

		Node *top = s.top();
		s.pop();
		printf("%c ", top->value);

		cur = top->right;
	}
}



void PostOrderNoR(Node *root) {
	std::stack<Node *> s;
	Node *cur = root;
	Node *last = NULL;		// 上一个被完整后序遍历过的树的根结点

	while (cur != NULL || !s.empty()) {
		while (cur != NULL) {
			s.push(cur);
			cur = cur->left;
		}

		Node *top = s.top();
		if (top->right == NULL) {
			printf("%c ", top->value);
			s.pop();
			last = top;
		}
		else if (top->right == last) {
			printf("%c ", top->value);
			s.pop();
			last = top;
		}
		else {
			cur = top->right;
		}
	}
}

void Test2() {
	char *preorder = "ABD###CE##F";
	int size = strlen(preorder);
	int used;

	Node *root = CreateTree(preorder, size, &used);
	LevelOrder(root);
	PreOrderNoR(root);
}

Node *prev = NULL;
void link(Node *node) {
	node->left = prev;
	if (prev != NULL) {
		prev->right = node;
	}

	prev = node;
}

void InOrder(Node *root) {
	if (root != NULL) {
		InOrder(root->left);
		link(root);
		InOrder(root->right);
	}
}