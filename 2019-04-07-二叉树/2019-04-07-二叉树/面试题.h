//������������������дһ�����������������Ƿ���ͬ��
bool isSame(struct TreeNode *p, struct TreeNode *q) {
	if (p == NULL && q == NULL) {
		return true;
	}

	if (p == NULL || q == NULL) {
		return false;
	}

	return p->val == q->val
		&& isSame(p->left, q->left)
		&& isSame(p->right, q->right);
}

bool Find(struct TreeNode *root, struct TreeNode *t) {
	if (root == NULL) {
		return false;
	}

	if (isSame(root, t) == true) {
		return true;
	}

	if (Find(root->left, t) == true) {
		return true;
	}

	return Find(root->right, t);
}
//���������ǿն����� s �� t��
//���� s ���Ƿ������ t ������ͬ�ṹ�ͽڵ�ֵ��������
//s ��һ���������� s ��һ���ڵ������ڵ���������
//s Ҳ���Կ����������һ��������
bool isSubtree(struct TreeNode* s, struct TreeNode* t) {
	return Find(s, t);
}