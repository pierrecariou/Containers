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
				root(NULL), left(new self(this)), right(new self(this)), alloc(alloc), comp(comp), n(n + 1), first(this), last(right) {
					data = alloc.allocate(1);
					alloc.construct(data, value_type(k, mapped_type()));
				}

			//child constructor
			node(allocator_type alloc, key_compare comp, const key_type& k, self* root) : root(root), left(NULL), right(NULL), alloc(alloc), comp(comp) {
				data = alloc.allocate(1);
				alloc.construct(data, value_type(k, mapped_type()));
			}

			// operator overloads
			self& operator= (const self& x) {
				data = x.data;
				root = x.root;
				left = x.left;
				right = x.right;
				return *this;
			}

			self*	deepLeft(self* node) {
				if (node->left == NULL)
					return node;
				if (node->left->data == NULL)
					return node;
				return deepLeft(node->left);
			}

			self*	findNext(self* node, self* nodeprev) {
				if (node->right != NULL && node->right != nodeprev)
					return deepLeft(node->right);
				if (node->root->left == node)
					return node->root;
				return findNext(node->root, node);
			}

			self*	operator++() {
				return findNext(this, NULL);
			}

			self*	deepRight(self* node) {
				if (node->right == NULL)
					return node;
				if (node->right->data == NULL)
					return node;
				return deepRight(node->right);
			}

			self*	findPrev(self* node, self* nodeprev) {
				if (node->left != NULL && node->left != nodeprev)
					return deepRight(node->left);
				if (node->root->right == node)
					return node->root;
				return findPrev(node->root, node);
			}

			self*	operator--() {
				return findPrev(this, NULL);
			}

			// Member functions
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
				self* cp = first->left;
				node->left = new self(alloc, comp, k, node);
				if (!comp(first->data->first, k)) {
					delete cp;
					first = node->left;
					node->left->left = new self(node->left);
				}
				return node->left;
			}

			self*	searchNode(const key_type& k, self* node, size_type& n, self*& first, self*& last) {
				if (node->data->first == k)
					return node;
				if (node->right != NULL && node->right->data != NULL && comp(node->data->first, k))
					node = node->right;
				else if (node->left != NULL && node->left->data != NULL && !comp(node->data->first, k))
					node = node->left;
				else
					return node->newNode(k, node, n, first, last);
				return searchNode(k, node, n, first, last);
			}

			self*	find(const key_type& k) {
				return searchNode(k, this, this->n, this->first, this->last);
			}

			void	becomeRoot(self* old_root) {
				root = NULL;
				first = (old_root == old_root->first) ? this : old_root->first;
				last = old_root->last;
				n = old_root->n;
			}

			void	deleteLeaf() {
				if (root->left == this)
					root->left = NULL;
				else
					root->right = NULL;
			}

			void	deleteOneChild() {
				if (root->left == this) {
					if (right != NULL) {
						root->left = right;
						right->root = root;
					} else {
						root->left = left;
						left->root = root;
					}
				} else {
					if (right != NULL) {
						root->right = right;
						right->root = root;
					} else {
						root->right = left;
						left->root = root;
					}
				}				
			}

			self*	searchMaxLeft(self* node, self* p) {
				if (node->right == NULL) {
					if (node->left != NULL) {
						node->left->root = node->root;
						node->root->right = node->left;
					}
					else
						node->root->right = NULL;
					p->left->root = node;
					p->right->root = node;
					node->root = p->root;
					node->left = p->left;
					node->right = p->right;
					if (node->root != NULL) {
						if (p->root->left == p)
							p->root->left = node;
						else
							p->root->right = node;
					}
					return node;
				}
				return searchMaxLeft(node->right, p);
			}

			self*	findFirst(self *node) {
				if (node->left == NULL)
					return node;
				if (node->left->data == NULL) {
					return node;
				}
				return findFirst(node->left);
			}

			self*	findLast(self *node) {
				if (node->right == NULL)
					return node;
				return findLast(node->right);
			}

			self* leftIsFirst(self* rroot) {
				if (left->data == NULL && this == rroot) { // left == first - 1 && this == root
					right->root = NULL;
					rroot->first = findFirst(right);
					rroot->first->left = left;
					rroot->first->left->root = rroot->first;
					return right;
				}
				else if (left->data == NULL) { // left == first - 1
					self* before_first = left;
					left = NULL;
					deleteOneChild();
					rroot->first = findFirst(rroot);
					rroot->first->left = before_first;
					rroot->first->left->root = rroot->first;
					return right;
				}
				return NULL;
			}

			self* rightIsLast(self* rroot) {
				if (right->data == NULL && this == rroot) { // right == last && this == root
					left->root = NULL;
					rroot->last = findLast(left);
					rroot->last->right = right;
					rroot->last->right->root = rroot->last;
					rroot->last = right;
					return left;
				}
				else if (right->data == NULL) { // right === last
					self* last = right;
					right = NULL;
					deleteOneChild();
					rroot->last = findLast(rroot);
					rroot->last->right = last;
					rroot->last->right->root = rroot->last;
					rroot->last = last;
					return left;
				}
				return NULL;
			}

			self*	deleteTwoChild(self* rroot) {	
				self* ret;

				if ((ret = leftIsFirst(rroot)) != NULL)
					return ret;
				else if ((ret = rightIsLast(rroot)) != NULL)
					return ret;	
				else if (left->right == NULL && left->data != NULL) { // special case
					left->right = right;
					left->right->root = left;
					left->root = root;
					if (root->left == this)
						root->left = left;
					else
						root->right = left;
					return left;
				}
				return searchMaxLeft(left->right, this); // normal case
			}
		};
}

#endif
