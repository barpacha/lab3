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
	
public:
	BST();
	~BST();
	void add(T data, key _key);
	T get(key _key);
	void remove(key _key);
};


template<typename T, typename key>
BST<T, key>::BST()
{
}

template<typename T, typename key>
BST<T, key>::~BST()
{
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
<<<<<<< HEAD
		if (prev_node->key < _key)  
			prev_node->right = new_node; 
		else 
			prev_node->left = new_node;
=======
		if (prev_node->key < _key) prev_node->right = new_node;
		else prev_node->left = new_node;
>>>>>>> bd663e8904d8121695e4f10faa446f046c40a1f5
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

	}
}


void main()
{
	BST<int> tree;
	tree.add(245, 9000);
	tree.add(247, 10000);
	tree.add(249, 8000);
	tree.add(251, 10);
	tree.remove(9000);
	system("pause");
}