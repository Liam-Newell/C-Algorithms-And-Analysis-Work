#include "arrayqueue.h"
#include <iostream>
using namespace std;
template <typename T>
class BST {
	struct Node {
		T data_;
		Node* left_;
		Node* right_;
		Node(const T& data, Node* left = nullptr, Node* right = nullptr) {
			data_ = data;
			left_ = left;
			right_ = right;
		}
	};
	Node* root_;
	//this function inserts data into the tree with root
	//subRoot
	void insert(const T& data, Node*& subRoot) {
		if (subRoot == nullptr) {
			subRoot = new Node(data);
		}
		else {
			if (data < subRoot->data_) {
				insert(data, subRoot->left_);
			}
			else {
				insert(data, subRoot->right_);
			}
		}
	}

	Node* detachInorderSuccessor(Node*& subRoot) {
		Node* curr = subRoot;
		while (curr->left_->left_) {
			curr = curr->left_;
		}
		Node* detach = curr->left_;
		curr->left_ = curr->left_->right_;
		return detach;

	}
	void remove(const T& data, Node*& subRoot) {
		if (subRoot != nullptr) {
			if (data == subRoot->data_) {
				Node* rm = subRoot;
				if (!subRoot->left_ && !subRoot->right_) {
					subRoot = nullptr;
				}
				else if (subRoot->left_ && !subRoot->right_) {
					subRoot = subRoot->left_;
				}
				else if (subRoot->right_ && !subRoot->left_) {
					subRoot = subRoot->right_;
				}
				else {
					Node* inorderSuccesor = detachInorderSuccessor(subRoot->right_);
					inorderSuccesor->left_ = subRoot->left_;
					inorderSuccesor->right_ = subRoot->right_;
					subRoot = inorderSuccesor;
				}
				delete rm;
			}
			else if (data < subRoot->data_) {
				remove(data, subRoot->left_);
			}
			else {
				remove(data, subRoot->right_);
			}
		}
	}
	void printPreOrder(const Node* subRoot) const {
		if (subRoot != nullptr) {
			std::cout << subRoot->data_ << " ";
			printPreOrder(subRoot->left_);
			printPreOrder(subRoot->right_);
		}
	}
	void printInOrder(const Node* subRoot) const {
		if (subRoot != nullptr) {
			printInOrder(subRoot->left_);
			std::cout << subRoot->data_ << " ";
			printInOrder(subRoot->right_);
		}
	}
	void destroy(Node* subRoot) {
		if (subRoot != nullptr)
		{
			destroy(subRoot->left_);
			destroy(subRoot->right_);
			delete subRoot;
		}
	}
	void copy(Node*& subRoot,const Node* rhsSub) {
		if (subRoot != nullptr) {
			if (rhsSub->left_ != nullptr) {
				subRoot->left_ = new Node(rhsSub->left_->data_);
				copy(subRoot->left_, rhsSub->left_);
			}
			if (rhsSub->right_ != nullptr) {
				subRoot->right_ = new Node(rhsSub->right_->data_);
				copy(subRoot->right_, rhsSub->right_);
			}
			
			
		}

	}
public:
	BST() {
		root_ = nullptr;
	}
	BST(const BST& rhs)
	{
		root_ = new Node(rhs.root_->data_);
		copy(root_, rhs.root_);
	}
	int depth(const T& data) {
		Node* curr = root_;
		int depth = 0;
		while (curr) {
			if (curr->data_ != data) {
				depth++;
				if (data < curr->data_)
					curr = curr->left_;
				else
					curr = curr->right_;
			}
			else
				break;
		}
		if (!curr)
			return -1;
		else
			return depth;
	}
	void insert(const T& data) {
		insert(data, root_);
	}
	void iterativeInsert(const T& data) {
		if (root_ == nullptr) {
			root_ = new Node(data);
		}
		else {
			Node* curr = root_;
			bool inserted = false;
			while (!inserted) {
				if (data < curr->data_) {
					if (curr->left_ == nullptr) {
						curr->left_ = new Node(data);
						inserted = true;
					}
					else {
						curr = curr->left_;
					}
				}
				else {
					if (curr->right_ == nullptr) {
						curr->right_ = new Node(data);
						inserted = true;
					}
					else {
						curr = curr->right_;
					}
				}
			}
		}
	}
	void remove(const T& data) {
		remove(data, root_);
	}
	//preOrder is depth first
	void printPreOrder() const {
		printPreOrder(root_);
	}
	//inOrder is depth first
	void printInOrder() const {
		printInOrder(root_);
	}
	//postOrder is depth first
	void printPostOrder() const {

	}


	//breadthFirst
	void printBreadthFirst() const {
		Queue<Node*> q;
		q.enqueue(root_);
		while (!q.empty()) {
			Node* curr = q.front();
			q.dequeue();
			if (curr != nullptr) {
				std::cout << curr->data << " " << std::endl;
				q.enqueue(curr->left_);
				q.enqueue(curr->right);
			}
		}
		if (root_) {
			q.enqueue(root_);
		}
		while (!q.empty()) {
			Node* curr = q.front();
			q.dequeue();
			cout << curr->data_ << " ";
			if (curr->left_) {
				q.enqueue(curr->left_);
			}
			if (curr->right_) {
				q.enqueue(curr->right_);
			}
		}
	}

	~BST() {
		destroy(root_);
	}
};