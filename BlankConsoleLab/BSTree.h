#ifndef BSTREE_H
#define BSTREE_H

#include <iostream> 
#include "BSNode.h"
#include "Exception.h"
using std::cout;
using std::endl;

template<typename T>
class BSTree {
public:
	BSTree(); // default constructor
	~BSTree(); // destructor
	BSTree(const BSTree<T>& copy); // copy constructor
	BSTree(BSTree<T>&& copy); // move constructor
	BSTree& operator =(const BSTree<T>& rhs); // copy assignment
	BSTree& operator =(BSTree<T>&& rhs); // move assignment
	BSNode<T>* GetRoot(); // gets and returns the root node. Used in the Unit Tests.
	const int GetTreeSize(); // gets and returns the tree size
	const int GetArrIncr();
	void Insert(T value); // inserts a value into the tree
	const int Height(const BSNode<T>* root); // finds the height of the tree and returns a int value
	void Purge(const BSNode<T>* root); // deletes the entire tree
	void PreOrderTreeArray(T arr[]); // creates a PreOrder Tranversal Array. Used in Unit Tests
	T search(BSNode<T>* root, T item);

	void Delete(T value); // deletes a value that is inside the tree using the DeleteNode function

	void InOrder(void(*visit)(T)); // method used in main to call the InOrder Tree Tranversal with a function of your choosing
	void PreOrder(void(*visit)(T)); // method used in main to call the PreOrder Tree Tranversal with a function of your choosing
	void PostOrder(void(*visit)(T)); // method used in main to call the PostOrder Tree Tranversal with a function of your choosing
	void BreadthFirst(void(*visit)(T)); // method used in main to call the LevelOrder Tree Tranversal with a function of your choosing
private:
	BSNode<T>* root;
	int treesize;
	int arr_incr;

	BSNode<T>* DeleteNode(BSNode<T>* root, T value); // used by the delete function to delete the node requested
	BSNode<T>* MinValueNode(BSNode<T>* node); // finds the minimum value node in the left subtree. It is a helper function for DeleteNode
	void SetRootNullptr(); // helper function for purge so that the root gets set to nullptr after we delete all the nodes
	BSNode<T>* CloneTree(BSNode<T>* root); // helper function for copy ctor, move ctor, copy assignment, and move assignment
	void InOrder(BSNode<T>* root, void(*visit)(T)); // used by the InOrder function 
	void PreOrder(BSNode<T>* root, void(*visit)(T)); // used by the PreOrder function
	void PreOrder(BSNode<T>* root, T arr[]); // used by the PreOrderTreeArray function to create an arr based on the values of the tree
	void PostOrder(BSNode<T>* root, void(*visit)(T)); // used by the PostOrder function
	void BreadthFirst(BSNode<T>* root, int level, void(*visit)(T)); // used by the BreadthFirst function
};

template<typename T>
inline BSTree<T>::BSTree() : root(nullptr), treesize(1), arr_incr(0) {}

template<typename T>
inline BSTree<T>::~BSTree()
{
	if (root != nullptr) {
		Purge(root);
	}

	treesize = 0;
}

template<typename T>
inline BSNode<T>* BSTree<T>::CloneTree(BSNode<T>* root)
{
	if (root == nullptr)
		return nullptr;

	BSNode<T>* copy = new BSNode<T>(root->data);

	copy->leftchild = CloneTree(root->leftchild);
	copy->rightchild = CloneTree(root->rightchild);
	return copy;
}

template<typename T>
inline BSTree<T>::BSTree(const BSTree& copy)
{
	if (this != &copy) {
		root = CloneTree(copy.root);
		treesize = copy.treesize;
	}
}

template<typename T>
inline BSTree<T>::BSTree(BSTree&& copy)
{
	if (this != &copy) {
		root = CloneTree(copy.root);
		treesize = copy.treesize;
		copy.Purge(copy.root);
	}
}

template<typename T>
inline BSTree<T>& BSTree<T>::operator=(const BSTree<T>& rhs)
{
	if (this != &rhs) {
		root = CloneTree(rhs.root);
		treesize = rhs.treesize;
	}
	return *this;
}

template<typename T>
inline BSTree<T>& BSTree<T>::operator=(BSTree<T>&& rhs)
{
	if (this != &rhs) {
		root = CloneTree(rhs.root);
		treesize = rhs.treesize;
		rhs.Purge(rhs.root);
	}
	return *this;
}

template<typename T>
inline BSNode<T>* BSTree<T>::GetRoot()
{
	return root;
}

template<typename T>
inline const int BSTree<T>::GetTreeSize()
{
	return treesize;
}

template<typename T>
inline const int BSTree<T>::GetArrIncr()
{
	return arr_incr;
}

template<typename T>
inline void BSTree<T>::Insert(T value)
{
	if (root == nullptr) {
		root = new BSNode<T>(value);
		return;
	}
	// if we start at the root and it is assigned to nullptr

	BSNode<T>* curr = root;
	BSNode<T>* parent = nullptr;

	while (curr != nullptr) {
		parent = curr;
		// sets the parent of our child
		if (value < curr->data) {
			curr = curr->leftchild;
		}
		else
			curr = curr->rightchild;
	}
	// tranverse the tree until curr = nullptr and we found a open spot in the tree to place our data with a available parent

	if (value < parent->data) {
		parent->leftchild = new BSNode<T>(value);
	}
	else {
		parent->rightchild = new BSNode<T>(value);
	}
	// creates a new node depending if the value is less (left) or the value is greater (right) of the parent node

	++treesize;
}

template<typename T>
inline const int BSTree<T>::Height(const BSNode<T>* root)
{
	if (root == nullptr)
		return 0;
	else {
		int lheight = Height(root->leftchild);
		int rheight = Height(root->rightchild);

		if (lheight > rheight)
			return(lheight + 1);
		else
			return (rheight + 1);
	}
}

template<typename T>
inline void BSTree<T>::Purge(const BSNode<T>* root)
{
	if (root == nullptr)
		return;

	Purge(root->leftchild);
	Purge(root->rightchild);

	delete root;
	SetRootNullptr();
	--treesize;
}

template<typename T>
inline void BSTree<T>::PreOrderTreeArray(T arr[])
{
	PreOrder(root, arr);
}

template<typename T>
inline T BSTree<T>::search(BSNode<T>* root, T item)
{
	if (root == nullptr || root->data == item)
		return root->data;

	if (root->data < item)
		return search(root->rightchild, item);

	return search(root->leftchild, item);
}

template<typename T>
inline BSNode<T>* BSTree<T>::MinValueNode(BSNode<T>* node)
{
	if (root == nullptr)
		throw (Exception("The tree is empty! Please add elements to the tree before trying to find the minimum value."));

	BSNode<T>* curr = node;
	while (curr && curr->leftchild != nullptr)
		curr = curr->leftchild;
	return curr;
}

template<typename T>
inline void BSTree<T>::InOrder(void(*visit)(T))
{
	InOrder(root, visit);
}

template<typename T>
inline void BSTree<T>::PreOrder(void(*visit)(T))
{
	PreOrder(root, visit);
}

template<typename T>
inline void BSTree<T>::PostOrder(void(*visit)(T))
{
	PostOrder(root, visit);
}

template<typename T>
inline void BSTree<T>::BreadthFirst(BSNode<T>* root, int level, void(*visit)(T))
{
	if (root == nullptr)
		return;
	if (level == 1) {
		visit(root->data);
	}
	else if (level > 1) {
		BreadthFirst(root->leftchild, level - 1, visit);
		BreadthFirst(root->rightchild, level - 1, visit);
	}
}


template<typename T>
inline void BSTree<T>::BreadthFirst(void(*visit)(T))
{
	int height = Height(root);

	for (int i = 1; i <= height; i++)
		BreadthFirst(root, i, visit);
}

template<typename T>
inline BSNode<T>* BSTree<T>::DeleteNode(BSNode<T>* root, T value)
{
	if (root == nullptr)
		throw (Exception("The tree is empty! Please add elements to the tree before trying to delete an element."));
	// if the tree is empty, it will return the root node and not delete anything.

	if (value < root->data)
		root->leftchild = DeleteNode(root->leftchild, value);
	// if the value is less than the root, navigate to the left subtree
	else if (value > root->data)
		root->rightchild = DeleteNode(root->rightchild, value);
	// if the value is more than the root, navigate to the right subtree

	else {
		if (root->leftchild == nullptr && root->rightchild == nullptr)
			return nullptr;
		// statement to determine if the node has no leftchild or rightchild, and will return nullptr if it is true
		else if (root->leftchild == nullptr) {
			BSNode<T>* temp = root->rightchild;
			delete root;
			return temp;
		}
		// determines if the leftchild is empty and if it is, it will delete and root and make the rightchild the new root.

		else if (root->rightchild == nullptr) {
			BSNode<T>* temp = root->leftchild;
			delete root;
			return temp;
		}
		// determines if the rightchild is empty and if it is, it will delete and root and make the leftchild the new root.

		BSNode<T>* temp = MinValueNode(root->rightchild);
		root->data = temp->data;
		root->rightchild = DeleteNode(root->rightchild, temp->data);
	}
	return root;
}

template<typename T>
inline void BSTree<T>::Delete(T value)
{
	DeleteNode(root, value);
	--treesize;
}

template<typename T>
inline void BSTree<T>::SetRootNullptr()
{
	root = nullptr;
}

template<typename T>
inline void BSTree<T>::InOrder(BSNode<T>* root, void(*visit)(T))
{
	if (root != nullptr) {
		InOrder(root->leftchild, visit);
		visit(root->data);
		InOrder(root->rightchild, visit);
	}
}


template<typename T>
inline void BSTree<T>::PreOrder(BSNode<T>* root, void(*visit)(T))
{
	if (root != nullptr) {
		visit(root->data);
		PreOrder(root->leftchild, visit);
		PreOrder(root->rightchild, visit);
	}
}

template<typename T>
inline void BSTree<T>::PreOrder(BSNode<T>* root, T arr[])
{
	if (root != nullptr) {
		arr[arr_incr++] = root->data;
		PreOrder(root->leftchild, arr);
		PreOrder(root->rightchild, arr);
	}
}

template<typename T>
inline void BSTree<T>::PostOrder(BSNode<T>* root, void(*visit)(T))
{
	if (root != nullptr) {
		PostOrder(root->leftchild, visit);
		PostOrder(root->rightchild, visit);
		visit(root->data);
	}
}

#endif

