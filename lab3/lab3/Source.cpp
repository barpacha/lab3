
template <typename T, typename key = int> class BST
{
	struct node
	{
		T data;
		key key;
		node *left;
		node *right;
	};
	
public:
	BST();
	~BST();
};

template<typename T, typename key>
BST<T, key>::BST()
{
}

template<typename T, typename key>
BST<T, key>::~BST()
{
}

void main()
{
	int g = 0;
}