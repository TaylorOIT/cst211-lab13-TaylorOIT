#ifndef BSNODE_H
#define BSNODE_H

template<typename T>
class BSTree;

template<typename T>
class BSNode
{
public:
	BSNode(T val); // default constructor
	BSNode(const BSNode<T>& copy); // copy constructor
	BSNode(BSNode<T>&& copy); // move constructor
	BSNode& operator =(const BSNode<T>& rhs); // copy assignment
	BSNode& operator =(BSNode<T>&& rhs); // move assignment
private:
	T data;
	BSNode* leftchild;
	BSNode* rightchild;
	friend class BSTree<T>;
};

template<typename T>
BSNode<T>::BSNode(T val) : data(val), leftchild(nullptr), rightchild(nullptr) {}

template<typename T>
inline BSNode<T>::BSNode(const BSNode<T>& copy)
{
	if (this != copy)
	{
		copy = *this;
	}
}

template<typename T>
inline BSNode<T>::BSNode(BSNode<T>&& copy)
{
	if (this != copy)
	{
		*this = std::move(copy);
	}
}

template<typename T>
inline BSNode<T>& BSNode<T>::operator=(const BSNode<T>& rhs)
{
	if (this != rhs)
	{
		rhs = *this;
	}
	return *this;
}

template<typename T>
inline BSNode<T>& BSNode<T>::operator=(BSNode<T>&& rhs)
{
	if (this != rhs)
	{
		*this = std::move(rhs);
	}
	return *this;
}



#endif

