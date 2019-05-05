#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//�������ĳ�ʼ��
typedef struct Node {
	struct Node *left;
	struct Node *right;
	char value;
}	Node;


// ������˼·
//ǰ�����
int count = 0;
void PreorderCount(Node *root) {
	if (root != NULL) {
		// ��
		count++;
		PreorderCount(root->left);
		PreorderCount(root->right);
	}
}

// �������˼·
//�������
int NodeSize(Node *root) {
	if (root == NULL) {
		return 0;
	}
	else if (root->left == NULL && root->right == NULL) {
		// ��ѡ��֧
		return 1;
	}
	else {
		// �����Ǻ�����������Ҹ�
		int left = NodeSize(root->left);
		int right = NodeSize(root->right);
		return left + right + 1;
	}
}
//Ҷ�ӽ��������������
int LeafSize(Node *root) {
	if (root == NULL) {
		return 0;
	}
	else if (root->left == NULL && root->right == NULL) {
		// �������
		return 1;
	}
	else {
		// �����Ǻ������
		int left = LeafSize(root->left);
		int right = LeafSize(root->right);
		return left + right;
	}
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
//��������߶�
int Height(Node *root) {
	if (root == NULL) {
		return 0;
	}

	int left = Height(root->left);
	int right = Height(root->right);

	return MAX(left, right) + 1;
}
//��k��������
int KLevelSize(Node *root, int k) {
	if (root == NULL) {
		return 0;
	}

	if (k == 1) {
		// ������ root ���ǿ���
		return 1;
	}

	int left = KLevelSize(root->left, k - 1);
	int right = KLevelSize(root->right, k - 1);

	return left + right;
}
//����������
Node * CreateNode(char value) {
	Node * node = (Node *)malloc(sizeof(Node));
	node->value = value;
	node->left = node->right = NULL;
	return node;
}
//�������в���v�Ƿ���ڣ����ض�Ӧ���
Node * Find(Node *root, char v) {
	if (root == NULL) {
		return NULL;	// һ
	}

	if (root->value == v) {
		return root;	// ��
	}

	Node *result = Find(root->left, v);
	if (result != NULL) {
		return result;	// ��
	}
	
	result = Find(root->right, v);
	if (result != NULL) {
		return result;	// ��
	}

	return NULL;		// ��
}
//����������
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
//�������ϴ���
void Test1() {
	Node *root = CreateTestTree();

	printf("������: %d\n", NodeSize(root));
	printf("Ҷ�ӽ�����: %d\n", LeafSize(root));
	printf("�߶�: %d\n", Height(root));
	KLevelSize(root, 3);
	/*
	for (int i = 1; i <= 5; i++) {
		printf("�� %d �������: %d\n", i, KLevelSize(root, i));
	}
	*/
	Find(root, 'F');
}




// A B D # # # # C E # # F
// ���������ĸ����, �����������õ��ĸ���
Node * CreateTree(char preorder[], int size, int *pUsed) {
	if (size == 0) {
		*pUsed = 0;
		return NULL;
	}

	if (preorder[0] == '#') {
		*pUsed = 1;
		return NULL;
	}

	// ����
	// ��
	Node *root = (Node *)malloc(sizeof(Node));
	root->value = preorder[0];

	// ������
	int leftUsed;
	root->left = CreateTree(preorder + 1, size - 1, &leftUsed);
	// ������
	int rightUsed;
	root->right = CreateTree(preorder + 1 + leftUsed,
		size - 1 - leftUsed, &rightUsed);

	*pUsed = 1 + leftUsed + rightUsed;
	return root;
}


// size ����ǰ�����иպõĳ���
Node * CreateTree2(char preorder[], int size, int *pUsed) {
	if (size == 0) {
		*pUsed = 0;
		return NULL;
	}

	if (preorder[0] == '#') {
		*pUsed = 1;
		return NULL;
	}

	// ����

	// ��
	Node *root = (Node *)malloc(sizeof(Node));
	root->value = preorder[0];

	// ������
	int leftUsed;
	root->left = CreateTree2(preorder + 1, size - 1, &leftUsed);
	// ������
	int rightUsed;
	root->right = CreateTree2(preorder + 1 + leftUsed,
		size - 1 - leftUsed, &rightUsed);

	// ������
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

// size ���Ľ�����
Node * buildTree(char preorder[], char inorder[], int size) {
	if (size == 0) {
		return NULL;
	}

	char rootValue = preorder[0];
	int leftSize = find(inorder, size, rootValue);

	// ��
	Node *root = (Node *)malloc(sizeof(Node));
	root->value = rootValue;
	// ������
	root->left = buildTree(
		preorder + 1,// ������ǰ��
		inorder,// ����������
		leftSize// ������������
		);
	// ������
	root->right = buildTree(
		preorder + 1 + leftSize,// ������ǰ��
		inorder + leftSize + 1,// ����������
		size - 1 - leftSize// ������������
		);

	return root;
}


#include <queue>
//����һ���������������䰴��α����Ľڵ�ֵ��
//�������أ������ҷ������нڵ㣩��
void LevelOrder(Node *root) {
	if (root == NULL) {
		printf("\n");
	}
	std::queue<Node *>	q;
	// ����
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
//�ж϶������Ƿ�����ȫ������
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

	// �ж϶���ʣ��Ԫ���Ƿ�ȫ�� NULL
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
	Node *last = NULL;		// ��һ����������������������ĸ����

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