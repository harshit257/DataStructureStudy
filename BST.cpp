#include <iostream>
using namespace std;

class Node {
public:
	Node* parent;
	Node* left;
	Node* right;
	int data;
	Node(int n) {
		parent = NULL;
		left = NULL;
		right = NULL;
		data = n;
	}
};

class Tree {
private:
	Node* root;
public:
	Tree() {
		root = NULL;
	}

	Node* search(Node* node, int num) {
		// ����Լ��� Ư���� ������ ��带 Ʈ������ ã��
		if (node == NULL || node->data == num)
			return node;
		if (node->data > num)
			return search(node->left, num);
		else
			return search(node->right, num);
	}

	void treeInsert(int num) {
		Node* newNode = new Node(num); // ���Ե� ��� ����
		Node* current = root; // root�������� ���� ���Ͽ� �� ��ġ ã��
		Node* parent = NULL;

		while (current != NULL) {
			parent = current;
			if (current->data > num)
				current = current->left;
			else
				current = current->right;
		}
		newNode->parent = parent; // ���ԵǴ� ����� �θ��带 ����

		if (parent == NULL)
			root = newNode;
		else if (parent->data > newNode->data)
			parent->left = newNode;
		else
			parent->right = newNode;
	}

	void transPlant(Node* parent, Node* child) { // ��� �翬���ϴ� ����
		if (parent->parent == NULL)
			root = child;
		else if (parent == parent->parent->left)
			parent->parent->left = child;
		else
			parent->parent->right = child;

		if (child != NULL)
			child->parent = parent->parent;
	}

	void treeDelete(int num) {
		Node* n = search(root, num); // ������ ��带 Ž��

		if (n->left == NULL && n->right == NULL) { 
			// �ڽ� �Ѵ� ������
			if (n->parent == NULL) { // �θ� �ΰ�(�����ҳ�� ��Ʈ)�̸� ��Ʈ ����
				this->root = NULL;
			}
			else { 
				// �θ� �ξƴϸ�(�����ҳ�尡 ��Ʈ�ƴ�) ���ʿ����� �������
				if (n == n->parent->right) // ������尡 �θ��� �������̸� �����ʻ���
					n->parent->right = NULL;
				else // ������尡 �θ��� �����̸� ���ʻ���
					n->parent->left = NULL;
			}
		}
		else if (n->left == NULL && n->right != NULL) {
			// �����ʳ�常 �ִٸ�
			transPlant(n, n->right);
		}
		else if (n->left != NULL && n->right == NULL) {
			// ���ʳ�常 �ִٸ�
			transPlant(n, n->left);
		}
		else {
			// �� �ڽ� ��� �ִٸ�
			Node* minNode = n->right;
			while (minNode->left != NULL)
				minNode = minNode->left;

			if (minNode->parent != n) {
				// ���� ���� ���� ������ ��尡 ������ ����� �ڽ��� �ƴ϶��
				transPlant(minNode, minNode->right);
				minNode->right = n->right;
				minNode->right->parent = minNode;
			}
			transPlant(n, minNode);
			minNode->left = n->left;
			minNode->left->parent = minNode;
		}
		delete n;
	}
};