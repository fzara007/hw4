#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.
		static Node<Key, Value>* successor(Node<Key, Value>* current);

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		static int height(const Node<Key, Value>* n);
		static bool balanced(const Node<Key, Value>* n);
    Node<Key, Value> *getBiggestNode() const; 

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
		current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
		current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		return current_ == rhs.current_;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
		return current_ != rhs.current_;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
	// std::cout<<std::endl << "****" << std::endl << "ITERATOR" <<std::endl<< "Key " << current_->getKey() << std::endl;
	// TODO
	// We don't need to go up the tree, just return successor
	if(current_->getRight()!=NULL)
		current_ = successor(current_);
	// root with no right subtree
	else if(current_->getParent()==NULL && current_->getRight()==NULL)
		current_ = NULL;
	// right subtree, need to go up until a new right subtree is found
	else if(current_->getParent()->getRight() == current_)
	{
		Node<Key, Value>* temp = current_->getParent();
		// going back up until we reach the root
		// while(temp->getParent()!=NULL)
		// {
		// 	// found a different right subtree
		// 	if(temp->getRight()!=NULL && temp->getRight()!=current_)
		// 	{
		// 		current_ = successor(current_);
		// 		break;
		// 	}
		// 	temp = temp->getParent();
		// }
		// if(temp->getParent()==NULL && temp->getRight()==NULL)
		// 	current_ = temp;
		// else
		// 	current_ = NULL;

		// if(temp->getParent()!= NULL && temp->getRight()!=temp)
		// 	current_ = temp;

		// keep going up if temp is in right subtree
		
		
		// while(temp->getParent()!= NULL && temp->getParent()->getRight()!=temp)
		// {
		// 	if(temp->getParent()->getLeft() == temp){
		// 		temp = temp->getParent();
		// 		break;
		// 	} 
		// 	temp = temp->getParent();
		// }

		while(temp->getParent()!=NULL)
		{
			if(temp->getParent()->getLeft()==temp) break;
			if(temp->getParent()->getRight()!=NULL && temp->getParent()->getRight()!=temp) break;
			temp = temp->getParent();
		}


		if(temp->getParent()==NULL && temp ->getRight()==NULL) current_ = NULL;
		else current_ = temp->getParent();


		// std::cout << "\tTemp " << temp->getKey() << std::endl;
		// // we reached root, there is no other right subtrees to go down
		// // std::cout << "broke here" << std::endl;
		// if(temp->getParent()==NULL) current_ = NULL;
		// // found a new right subtree, need to return root of that subtree
		// else current_ = temp;

		// if(temp->getRight()!=NULL && temp->getRight()!=current_) current_  = temp;
		// else current_ = NULL;
		
		// if(temp->getParent()!=NULL && temp->getParent()->getRight()==temp)
		// 	{
		// 		// std::cout << "1" << std::endl;
		// 		if(temp->getParent()->getParent()!=NULL) 
		// 		{
		// 			// std::cout << "2" << std::endl;
		// 			if(temp->getParent()->getParent()->getLeft()==temp->getParent()) 
		// 			{
		// 				// std::cout << "3" << std::endl;
		// 				current_ = temp->getParent()->getParent();
		// 				// std::cout << "4" << std::endl;
		// }}}
		
		// std::cout << "or did we break here" << std::endl;
	}
	// otherwise we are in the left subtree and now need to return parent 
	else
		current_ = current_->getParent();
	
	// if(current_!=NULL)
	// std::cout << "current is " << current_->getKey() <<std::endl << "****"<< std::endl;
	// else
	// std::cout << "current is NULL" <<std::endl << "****"<< std::endl;

	return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
		//  std::cout << "In constructor" << std::endl;
		root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
		//  std::cout << "In deconstructor" << std::endl;
		
		// print();

		clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
		// TODO
		//  std::cout << "In insert func" << std::endl;
		// no tree at all
		if(root_ == NULL)
		{
			// std::cout << "\tinsert root" << std::endl;
			root_ = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
			// print();
			return;
		}

		// not a new key, update value
		Node<Key, Value> * temp = internalFind(keyValuePair.first);
		if(temp!=NULL)
		{
			// std::cout << "\tupdate val" << std::endl;
			temp->setValue(keyValuePair.second);
			return;
		}

		temp = root_;
		while(temp->getLeft()!=NULL || temp->getRight()!=NULL)
		{
			// need to enter left subtree
			if(temp->getKey()>keyValuePair.first)
			{
				if(temp->getLeft() == NULL) break;
				temp = temp->getLeft();
			}
			// need to enter right subtree
			else
			{
				if(temp->getRight() == NULL) break;
				temp = temp->getRight();
			}
		}

		// if we made it out we are at a leaf
		Node<Key, Value>* n = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, temp);
		if(temp->getKey()>keyValuePair.first)
			temp->setLeft(n);
		else 
			temp->setRight(n);
		
		// if(root_!=NULL){
		// 	std::cout << "Root: " << root_->getKey() << std::endl;
		// 	if(root_->getLeft()!=NULL){
		// 		std::cout << "LC: " << root_->getLeft()->getKey() << std::endl;
		// 	if(root_->getLeft()->getLeft()!=NULL){
		// 		std::cout << "LCLC: " << root_->getLeft()->getLeft()->getKey() << std::endl;
		// 	}}
		// 	if(root_->getRight()!=NULL){
		// 		std::cout << "RC: " << root_->getRight()->getKey() << std::endl;
		// 	if(root_->getRight()->getRight()!=NULL){
		// 		std::cout << "RCRC: " << root_->getRight()->getRight()->getKey() << std::endl;
		// 	}}
		// }
		// print();
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
		//  std::cout << "In remove func to remove " << key << std::endl;
		// print();
		Node<Key, Value> * to_remove = internalFind(key);

		if(to_remove==NULL) return;

		if((to_remove==root_) && (height(root_) == 1))
		{
			// std::cout << "\tidentified root" << std::endl;
			root_ = NULL;
			delete to_remove;
			return;
		}

		if(to_remove->getLeft()==NULL && to_remove->getRight()==NULL)
		{
			if(to_remove->getParent()->getRight() == to_remove)
				to_remove->getParent()->setRight(NULL);
			else
				to_remove->getParent()->setLeft(NULL);
		}
		else if(to_remove->getLeft()==NULL)
		{
			// std::cout << "\tI should be here" << std::endl;
			Node<Key, Value>* swap = successor(to_remove);
			nodeSwap(to_remove, swap);
			// if(to_remove==root_) root_ = swap;
			if(to_remove->getParent()==swap)
			{
				// std::cout << "\talso should be here" << std::endl;
				if(to_remove->getRight()!= NULL)
				{
					to_remove->getParent()->setRight(to_remove->getRight());
					to_remove->getRight()->setParent(to_remove->getParent());
					// std::cout << "\tdid i get here...?" << std::endl;
				}
				else
				{
					to_remove->getParent()->setRight(NULL);
					if(to_remove->getLeft()!=NULL)
					{	
						to_remove->getParent()->setRight(to_remove->getLeft());
						to_remove->getLeft()->setParent(to_remove->getParent());
					}
				}
			}
			else
			{
				if(to_remove->getLeft()!= NULL)
				{

					// std::cout << "\tdid i get here...?" << std::endl;
				  to_remove->getParent()->setLeft(to_remove->getLeft());
					to_remove->getLeft()->setParent(to_remove->getParent());
				}
				else
				{
					to_remove->getParent()->setLeft(NULL);
					if(to_remove->getRight()!=NULL)
					{	
						to_remove->getParent()->setLeft(to_remove->getRight());
						to_remove->getRight()->setParent(to_remove->getParent());
					}
				}
			}
		}
		else
		{
			Node<Key, Value>* swap = predecessor(to_remove);
			// if(to_remove==root_) root_ = swap;
			nodeSwap(to_remove, swap);
			if(to_remove->getParent()!=swap)
			{
				if(to_remove->getRight()!= NULL)
				{	
					to_remove->getParent()->setRight(to_remove->getRight());
					to_remove->getRight()->setParent(to_remove->getParent());
				}
				else
				{
					to_remove->getParent()->setRight(NULL);
					if(to_remove->getLeft()!=NULL)
					{	
						to_remove->getParent()->setRight(to_remove->getLeft());
						to_remove->getLeft()->setParent(to_remove->getParent());
					}
				}
			}
			else
			{
				if(to_remove->getLeft()!= NULL)
				{
					to_remove->getParent()->setLeft(to_remove->getLeft());
					to_remove->getLeft()->setParent(to_remove->getParent());
				}
				else
				{
					to_remove->getParent()->setLeft(NULL);
					if(to_remove->getRight()!=NULL)
					{	
						to_remove->getParent()->setLeft(to_remove->getRight());
						to_remove->getRight()->setParent(to_remove->getParent());
					}
				}
			}
		}

		// if(to_remove->getParent()->getLeft() == to_remove) to_remove->getParent()->setLeft(NULL);
		// else  to_remove->getParent()->setRight(NULL);
		delete to_remove;
		// std::cout << "is print failing?" << std::endl;
		// if(root_!=NULL){
		// 	std::cout << "Root: " << root_->getKey() << std::endl;
		// 	if(root_->getLeft()!=NULL){
		// 		std::cout << "LC: " << root_->getLeft()->getKey() << std::endl;
		// 	if(root_->getLeft()->getLeft()!=NULL){
		// 		std::cout << "LCLC: " << root_->getLeft()->getLeft()->getKey() << std::endl;
		// 	}}
		// 	if(root_->getRight()!=NULL){
		// 		std::cout << "RC: " << root_->getRight()->getKey() << std::endl;
		// 	if(root_->getRight()->getRight()!=NULL){
		// 		std::cout << "RCRC: " << root_->getRight()->getRight()->getKey() << std::endl;
		// 	}}
		// }
		// print();
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
		//  std::cout << "In predecessor func" << std::endl;
		if(current->getLeft()==NULL) return NULL;
		Node<Key, Value>* min = current->getLeft();
		while(min->getRight()!=NULL) min = min->getRight();
		return min;
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
		if(current->getRight()==NULL) return NULL;
		Node<Key, Value>* min = current->getRight();
		while(min->getLeft()!=NULL) min = min->getLeft();
		return min;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
		//  std::cout << "In clear func" << std::endl;
		Node<Key, Value>* temp = getSmallestNode();
		// if(temp!=NULL && temp==root_) temp = getBiggestNode();
		while(temp!=NULL)
		{
			// delete temp;
			remove(temp->getKey());
			temp = getSmallestNode();
			// std::cout << "what the hell is happening????????" << std::endl;
			if(temp == NULL) return;
			// if(temp!=NULL && temp==root_) temp = getBiggestNode();
		}
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
		//  std::cout << "In smallest node func";
		Node<Key, Value>* temp = root_;
		//  std::cout << ".";
		if(temp==NULL) return NULL;
		//  std::cout << ".";
		while(temp->getLeft() != NULL) temp = temp ->getLeft();
		//  std::cout << "." << std::endl;
		return temp;
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getBiggestNode() const
{
    // TODO
		//  std::cout << "In biggest node func" << std::endl;
		Node<Key, Value>* temp = root_;
		if(temp==NULL) return NULL;
		while(temp->getRight() != NULL) temp = temp ->getRight();
		return temp;
}


/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
		//  std::cout << "In internal find func" << std::endl;
		
		if(root_==NULL) return NULL;
		Node<Key, Value>* temp = root_;
		while(temp->getLeft()!=NULL || temp->getRight()!=NULL)
		{
			// std::cout << "around and around we go :D" << std::endl;
			if(temp->getKey() == key) return temp;
			if(temp->getKey() > key)
			{
				if(temp->getLeft()==NULL) return NULL;
				temp = temp->getLeft();
			}
			else
			{
				if(temp->getRight()==NULL) return NULL;
				temp = temp->getRight();
			}
		}

		if(temp->getKey() == key) return temp;
		return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
		//  std::cout << "In is balanced func" << std::endl;
		// print();
		return balanced(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::balanced(const Node<Key, Value>* n)
{
	if(height(n)==0 || height(n)==1) return true;
	if(height(n->getLeft())==0) return (height(n->getRight())<=1);
	if(height(n->getRight())==0) return (height(n->getLeft())<=1);
	// std::cout << "Node\t" << n->getKey() << std::endl;
	// std::cout << "(LC, height)\t" << n->getLeft()->getKey() << " " << height(n->getLeft()) << std::endl;
	// std::cout << "(RC, height)\t" << n->getRight()->getKey() << " " << height(n->getRight()) << std::endl;
	if(abs(height(n->getLeft())-height(n->getRight()))>1) return false;
	return balanced(n->getLeft()) && balanced(n->getRight());
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height(const Node<Key, Value>* n) 
{
	if(n==NULL) return 0;

	int l = height(n->getLeft())+1;
	int r = height(n ->getRight())+1;
	if(l>r) return l;
	return r;
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
