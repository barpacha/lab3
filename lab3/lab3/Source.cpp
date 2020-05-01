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
	node* first_node;

	node* bin_insearch_get(node* sourse, key _key)
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

	node* bin_insearch_add(node* sourse, key _key)
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
	
public:
	BST();
	~BST();
	void add(T data, key _key);
	T get(key _key);
};


template<typename T, typename key>
BST<T, key>::BST()
{
	first_node = nullptr;
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
		if (prev_node->key > _key)
		{
			node* new_node = new node;
			prev_node->right = new_node;
			new_node->data = data;
			new_node->key = _key;
		}
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


void main()
{
	BST<int> tree;
	tree.add(245, 9000);
	tree.add(247, 10000);
	tree.add(249, 8000);
	tree.add(251, 10);

	printf("%d\n",tree.get(10));
	printf("%d\n", tree.get(10000));
	int g = 0;
	system("pause");
}