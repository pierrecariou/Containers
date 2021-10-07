#ifndef NODE_HPP
# define NODE_HPP

namespace ft {
	template <class T, class Alloc, class Key, class Value, class Compare>
		struct node
		{	
			// Member types
			typedef T																		value_type;
			typedef Compare																	key_compare;
			typedef Alloc																	allocator_type;
			typedef Key																		key_type;
			typedef Value																	mapped_type;
			typedef node<value_type, allocator_type, key_type, mapped_type, key_compare>	self;
			typedef std::size_t																size_type;

			// Member variables
			value_type*		data;
			self*			root;
			self*			left;
			self*			right;
			allocator_type	alloc;
			key_compare		comp;
			size_type		n;
			self*			first;
			self*			last;

			// CONSTRUCTORS //
			node(const value_type& data) : data(data), root(NULL), left(NULL), right(NULL), alloc(alloc) {}

			node(const value_type& data, self* root) : data(data), root(root), left(NULL), right(NULL), alloc(alloc) {}

			//last constructor
			node(self* root) : root(root), left(NULL), right(NULL) {
				data = NULL;
			}
			
			//root constructor
			node(allocator_type alloc, key_compare comp, size_type n, const key_type& k) :
				root(NULL), left(NULL), right(new self(this)), alloc(alloc), comp(comp), n(n + 1), first(this), last(right) {
				data = alloc.allocate(1);
				alloc.construct(data, value_type(k, mapped_type()));
			}
			
			//leaf construcor
			node(allocator_type alloc, key_compare comp, const key_type& k, self* root) : root(root), left(NULL), right(NULL), alloc(alloc), comp(comp) {
				data = alloc.allocate(1);
				alloc.construct(data, value_type(k, mapped_type()));
			}

			// assign
			self& operator= (const self& x) {
				data = x.data;
				root = x.root;
				left = x.left;
				right = x.right;
				return *this;
			}

			// Member functions
			void	nodeRight(const value_type& data) {
				right = self(data, this);
			}

			void	nodeLeft(const value_type& data) {
				left = self(data, this);
			}

			self*	findNext(self* node, self* nodeprev) {
				if (node->right != NULL && node->right != nodeprev)
					return node->right;
				if (node->root->left == node)
					return node->root;
				return findNext(node->root, node);
			}

			self*	operator++() {
				return findNext(this, NULL);
			}

			self*	newNode(const key_type& k, self* node, size_type& n, self*& first, self*& last) {
				n+=1;
				if (comp(node->data->first, k)) {
					node->right = new self(alloc, comp, k, node);
					if (comp(last->root->data->first, k)) {
						self* cp = last;
						node->right->right = (last = new self(node->right));
						delete cp;
					}
					return node->right;
				}
				node->left = new self(alloc, comp, k, node);
				first = (comp(first->data->first, k)) ? first : node->left;
				return node->left;
			}

			self*	searchNode(const key_type& k, self* node, size_type& n, self*& first, self*& last) {
				if (node->data->first == k)
					return node;
				if (node->right != NULL && node->right->data != NULL && comp(node->data->first, k))
					node = node->right;
				else if (node->left != NULL && !comp(node->data->first, k))
					node = node->left;
				else
					return node->newNode(k, node, n, first, last);
				return searchNode(k, node, n, first, last);
			}

			self*	find(const key_type& k) {
				return searchNode(k, this, this->n, this->first, this->last);
			}
		};
}

#endif
