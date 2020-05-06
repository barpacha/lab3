#include <stdio.h>
#include <iostream>

template <typename T, typename key = int> class BST
{
	struct node
	{
		T data;
		key key;
		node *left = nullptr;
		node *right = nullptr;
	};
	node* first_node = nullptr;

	node* bin_insearch_get(node* sourse, key _key) // null - not found, sourse - correct node
	{
		if (_key == sourse->key) return sourse;
		if (_key > sourse->key)
		{
			if (sourse->right == nullptr) return nullptr;
			else return bin_insearch_get(sourse->right, _key);
		}
		else
		{
			if (sourse->left == nullptr) return nullptr;
			else return bin_insearch_get(sourse->left, _key);
		}
	}

	node* bin_insearch_add(node* sourse, key _key)//null - occupied, sourse - node with correct cell
	{
		if (_key == sourse->key) return nullptr;
		if (_key > sourse->key)
		{
			if (sourse->right == nullptr) return sourse;
			else return bin_insearch_add(sourse->right, _key);
		}
		else
		{
			if (sourse->left == nullptr) return sourse;
			else return bin_insearch_add(sourse->left, _key);
		}
	}

	node *bin_insearch_remove(node** prev_sourse, node* sourse, key _key) // null - not found, sourse - correct node, prev_sourse - cell with pointer on previous node
	{
		if (_key == sourse->key)return sourse;
		*prev_sourse = sourse;
		if (_key > sourse->key)
		{
			if (sourse->right == nullptr) return nullptr;
			else
				return bin_insearch_remove(prev_sourse, sourse->right, _key);
		}
		else
		{
			if (sourse->left == nullptr) return nullptr;
			else 
				return bin_insearch_remove(prev_sourse, sourse->left, _key);
		}
	}
	
	void bin_insearch_destructor(node* sourse)
	{
		if (sourse->left != nullptr) bin_insearch_destructor(sourse->left);
		if (sourse->right != nullptr) bin_insearch_destructor(sourse->right);
		delete sourse;
	}

	void bin_insearch_copy(node* sourse)
	{
		this->add(sourse->data, sourse->key);
		if (sourse->left != nullptr) bin_insearch_copy(sourse->left);
		if (sourse->right != nullptr) bin_insearch_copy(sourse->right);
	}

	

public:
	BST();
	BST(BST& obj);
	~BST();
	void add(T data, key _key);
	T get(key _key);
	void remove(key _key);
	void add_root(T data, key _key);
	BST& operator=(BST obj);
};


template<typename T, typename key>
BST<T, key>::BST()
{
}

template<typename T, typename key>
BST<T, key>::BST(BST & obj)
{
	if (obj.first_node == nullptr) return;
	bin_insearch_copy(obj.first_node);
}



template<typename T, typename key>
BST<T, key>::~BST()
{
	if (!first_node) return;
	bin_insearch_destructor(first_node);
}



template<typename T, typename key>
void BST<T, key>::add(T data, key _key)
{
	if (first_node != nullptr)
	{
		node* prev_node = bin_insearch_add(first_node, _key);
		if (prev_node == nullptr) return;
		node* new_node = new node;
		new_node->data = data;
		new_node->key = _key;
		if (prev_node->key < _key)  
			prev_node->right = new_node; 
		else 
			prev_node->left = new_node;
		if (prev_node->key < _key) prev_node->right = new_node;
		else prev_node->left = new_node;
	}
	else
	{
		node* new_node = new node;
		first_node = new_node;
		new_node->data = data;
		new_node->key = _key;
	}

}

template<typename T, typename key>
T BST<T, key>::get(key _key)
{
	if (first_node == nullptr) throw;
	return bin_insearch_get(first_node, _key)->data;
}

template<typename T, typename key>
void BST<T, key>::remove(key _key)
{
	if (_key == first_node->key)//remove root
	{
		if (first_node->left != nullptr)
		{
			if (first_node->right != nullptr)
			{
				node* new_right_node = bin_insearch_add(first_node->left, _key);
				new_right_node->right = first_node->right;
			}
			first_node = first_node->left;
		}
		else
			first_node = first_node->right;
		delete first_node;
		if (first_node->right == nullptr&&first_node->left == nullptr) first_node = nullptr;
	}
	else//remove node
	{
		node** prev_rem_node = new node*;
		node* rem_node = bin_insearch_remove(prev_rem_node, first_node, _key);
		if ((*prev_rem_node)->key > _key)//left
			if (rem_node->left != nullptr)
			{
				if (rem_node->right != nullptr)
				{
					node* new_right_node = bin_insearch_add(rem_node->left, _key);
					new_right_node->right = rem_node->right;
				}
				(*prev_rem_node)->left = rem_node->left;
			}
			else
				(*prev_rem_node)->left = rem_node->right;
		else//right
			if (rem_node->left != nullptr)
			{
				if (rem_node->right != nullptr)
				{
					node* new_right_node = bin_insearch_add(rem_node->left, _key);
					new_right_node->right = rem_node->right;
				}
				(*prev_rem_node)->right = rem_node->left;
			}
			else
				(*prev_rem_node)->right = rem_node->right;
		delete rem_node;
		delete prev_rem_node;
	}
}

template<typename T, typename key>
void BST<T, key>::add_root(T data, key _key)
{
	if (bin_insearch_add(first_node, _key) == nullptr) return;
	node* new_node = new node;
	new_node->data = data;
	new_node->key = _key;
	node* second_node = first_node;
	first_node = new_node;
	if (second_node->key > _key)
		first_node->right = second_node;
	else
		first_node->left = second_node;
}

template<typename T, typename key>
BST<T, key> &BST<T, key>::operator=(BST<T, key> obj)
{
	if (first_node)
	{
		bin_insearch_destructor(first_node);
		first_node = nullptr;
	}
	if (obj.first_node)
		bin_insearch_copy(obj.first_node);
	return *this;
}


void main()
{
	BST<int> tree;
	tree.add(245, 9000);
	tree.add(247, 10000);
	tree.add(249, 8000);
	tree.add(251, 10);
	BST<int> a(tree);
	tree.add_root(1, 1);
	tree.remove(9000);
	a = tree;
	printf("%d",a.get(9000));
	system("pause");
}
