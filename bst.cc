#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
//
// Node is already allocated and deleted in main()
Node::Node()
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}
// Constructor
//
// Node is already allocated and deleted in main()
Node::Node(int in) 
{
	key = in;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}
// Destructor
//
// Node is already allocated and deleted in main()
Node::~Node()
{
}

// Add parent 
void Node::add_parent(Node* in) 
{
	parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) 
{
	left = in;
}
// Add to right of current node
void Node::add_right(Node* in) 
{
	right = in;
}

// Get key
int Node::get_key()
{
	return key;
}
// Get parent node
Node* Node::get_parent()
{
	return parent;
}
// Get left node
Node* Node::get_left()
{
	return left;
}
// Get right node
Node* Node::get_right()
{
	return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
	if(in != nullptr) 
	{
		inorder_walk(in->get_left(), to);
		in->print_info(to);
		inorder_walk(in->get_right(), to);
	}
}
// Constructor
BST::BST()
{
	root = nullptr;
}
// Destructor
BST::~BST()
{
	// recursively delete dynamically allocated nodes
	rec_destruct(root);

}

// recursive destructor, deletes dynamically allocated node of BST
void BST::rec_destruct(Node* in)
{
	// at leaf, nothing to do
	if(in) 
	{
		
		// delete children
		rec_destruct(in->get_left());
		rec_destruct(in->get_right());

		// delete self
		delete in;
	}

	return;
}
// Insert a node to the subtree
//
// Source: CLSR (Introduction to Algorithms, 3rd ed.)
void BST::insert_node(Node* in)
{
	Node* node_y = nullptr;
	Node* node_x = root;

	// inserting node as leaf, doing comparisons along the way to keep BST property
	while(node_x != nullptr)
	{
		node_y = node_x;

		// comparing value to either go left or right
		if(in->get_key() < node_x->get_key()) 
		{
			node_x = node_x->get_left();
		}
		else
		{
			node_x = node_x->get_right();
		}
	}

	in->add_parent(node_y);

	// tree was empty
	if(node_y == nullptr) 
	{
		root = in;
	}
	else if(in->get_key() < node_y->get_key()) 
	{
		node_y->add_left(in);
	}
	else
	{
		node_y->add_right(in);
	}

}
// Delete a node to the subtree
//
//  4 cases when deleting:
//
//
//  1. Node has no left child:
//  Replace Node by it's right child.
//  When right child is None, this deals with case where Node has no children.
//
//  2. Node has no only one child (left child):
//  replace Node by it's left child.
//
//  3. Node has both left and right child:
//  find Node's successor, splice it out and replace Node
//  if successor is Node's right child, replace Node with successor,
//  leave successor's right child alone
//
//  successor is in Node's right subtree but isn't Node's right child.
//  Replace successor by it's own right child, THEN replace Node by successor

void BST::delete_node(Node* out)
{
	if(out->get_left() == nullptr)
	{
		transplant(out, out->get_right());
	}
	else if(out->get_right() == nullptr)
	{
		transplant(out, out->get_left());
	}
	else
	{
		Node* v = get_min(out->get_right());
		
		if(v->get_parent() != out)
		{
			transplant(v, v->get_right());
			v->add_right(out->get_right());
			v->get_right()->add_parent(v);
		}

		transplant(out, v);

		v->add_left(out->get_left());

		v->get_left()->add_parent(v);

	}

	delete out;

}

//  Method to help with delete.
//  replaces one subtree (rooted at u) with another (rooted at v).
//  when u replaces v, u's parent becomes v's parent and u's parent has
//  v as appropriate child
void BST::transplant(Node* u, Node* v)
{
	if(u->get_parent() == nullptr)
	{
		root = v;
	}
	else if(u == u->get_parent()->get_left())
	{
		u->get_parent()->add_left(v);
	}
	else
	{
		u->get_parent()->add_right(v);
	}

	if(v != nullptr) 
	{
		v->add_parent(u->get_parent());
	}
}

// minimum key in the BST
//
// minimum key is the left-most node in the BST
Node* BST::tree_min()
{
	return get_min(root);
}

// maximum key in the BST
//
// Maximum key is the right-most node in the BST
Node* BST::tree_max()
{
	return get_max(root);

}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
	Node* node_x = in;

	while(node_x->get_left() != nullptr) 
	{
		node_x = node_x->get_left();
	}

	return node_x;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
	Node* node_x = in;

	while(node_x->get_right() != nullptr) 
	{
		node_x = node_x->get_right();
	}

	return node_x;
}
// Get successor of the given node
//
// Successor is minimum of right subtree.
//
// If right subtree is empty and a successor does exist,
// then successor is lowest ancestor of the given node whose left child
// is also a an ancestor of given node.
Node* BST::get_succ(Node* in)
{
	if(in->get_right() != nullptr) 
	{
		return get_min(in->get_right());
	}

	Node* node_y = in->get_parent();

	while(node_y != nullptr and in == node_y->get_right())
	{
		in = node_y;
		node_y = node_y->get_parent();
	}

	return node_y;
}

// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
	if(in->get_left() != nullptr) 
	{
		return get_max(in->get_left());
	}

	Node* node_y = in->get_parent();

	while(node_y != nullptr and in == node_y->get_left())
	{
		in = node_y;
		node_y = node_y->get_parent();
	}

	return node_y;
}

// Walk the BST from min to max
void BST::walk(ostream& to)
{
	// minimum is the first element
	Node* node_x = tree_min();

	node_x->print_info(to);

	// once we have max, we're done
	while(node_x != get_max(root))
	{
		node_x = get_succ(node_x);
		node_x->print_info(to);
	}
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
	Node* node_x = root;

	while(node_x != nullptr and node_x->get_key() != search_key)
	{
		if(search_key < node_x->get_key())
		{
			node_x = node_x->get_left();
		}
		else
		{
			node_x = node_x->get_right();
		}
	}

	return node_x;
}
// ---------------------------------------
