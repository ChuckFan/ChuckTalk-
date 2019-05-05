//给定两个二叉树，编写一个函数来检验它们是否相同。
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
//给定两个非空二叉树 s 和 t，
//检验 s 中是否包含和 t 具有相同结构和节点值的子树。
//s 的一个子树包括 s 的一个节点和这个节点的所有子孙。
//s 也可以看做它自身的一棵子树。
bool isSubtree(struct TreeNode* s, struct TreeNode* t) {
	return Find(s, t);
}