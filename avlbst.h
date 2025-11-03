#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
		// void debugTime()
		// {
		// 	debug = !debug;
		// };
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		AVLNode<Key, Value>* AVLroot_ = NULL;
    void rotateLeft(AVLNode<Key, Value>* n);
    void rotateRight(AVLNode<Key, Value>* n);
    void setTreeBalance(AVLNode<Key, Value>* n);
    void checkBalance(AVLNode<Key, Value>* n);
    void fixBalance(AVLNode<Key, Value>* n);
		AVLNode<Key,Value>* internalFind(const Key& key) const;
		// bool debug = false;
};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    // no tree at all
		// if(debug)
		// std::cout << "Trying to insert " << new_item.first << std::endl;

		// if(debug)
		// 	BinarySearchTree<Key, Value>::print();
		
			
		if(BinarySearchTree<Key,Value>::root_ == NULL)
		{
			AVLroot_ = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
			BinarySearchTree<Key,Value>::root_ = AVLroot_;
			AVLroot_->setBalance(0);
			return;
		}

		// not a new key, update value
		AVLNode<Key, Value> * temp = AVLTree<Key, Value>::internalFind(new_item.first);
		if(temp!=NULL)
		{
			temp->setValue(new_item.second);
			// if(debug)
			// std::cout << "Updated value" << std::endl;
			return;
		}

		temp = AVLroot_;
		while(temp->getLeft()!=NULL || temp->getRight()!=NULL)
		{
			// need to enter left subtree

			if(temp->getKey()>new_item.first)
			{
				if(temp->getLeft() == NULL) break;
				temp = temp->getLeft();
				// if(debug)
				// std::cout << "left ";
			}
			// need to enter right subtree
			else
			{
				
				// std::cout << "enter here?" << std::endl;
				if(temp->getRight() == NULL) break;
				temp = temp->getRight();
				// if(debug)
				// std::cout << "right ";
			}
		}

		// if we made it out we are at a leaf
		AVLNode<Key, Value>* n = new AVLNode<Key, Value>(new_item.first, new_item.second, temp);
		if(temp->getKey()>new_item.first)
			temp->setLeft(n);
		else 
			temp->setRight(n);

		// std::cout << "New insert :D" << std::endl;
		// if(debug)
		// std::cout << std::endl << "End of insert, now calling setTreeBalance" << std::endl;
		// if(debug) BinarySearchTree<Key,Value>::print();
		
		setTreeBalance(n);
		

}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
		AVLNode<Key, Value> * to_remove = internalFind(key);
		
			// std::cout << "remove time " << key << std::endl;
			
			
		if(to_remove==NULL) return;

		if((to_remove==BinarySearchTree<Key,Value>::root_) && ( BinarySearchTree<Key, Value>::height(BinarySearchTree<Key,Value>::root_) == 1))
		{
			// std::cout << "\tidentified root" << std::endl;
			BinarySearchTree<Key,Value>::root_ = NULL;
			AVLroot_ = NULL;
			delete to_remove;
			return;
		}

		AVLNode<Key, Value>* ogP = to_remove->getParent(); 

		if(to_remove->getLeft()==NULL && to_remove->getRight()==NULL)
		{
			if(ogP->getRight() == to_remove)
				ogP->setRight(NULL);
			else
				ogP->setLeft(NULL);
		}
		else if(to_remove->getLeft()==NULL)
		{
			Node<Key,Value>* removeNode = to_remove;
			AVLNode<Key, Value>* swap = 
				internalFind(BinarySearchTree<Key, Value>::successor(removeNode)->getKey());
			nodeSwap(to_remove, swap);
			ogP = to_remove->getParent(); 

			if(ogP==swap)
			{
				if(to_remove->getRight()!= NULL)
				{
					ogP->setRight(to_remove->getRight());
					to_remove->getRight()->setParent(ogP);
				}
				else
				{
					ogP->setRight(NULL);
					if(to_remove->getLeft()!=NULL)
					{	
						ogP->setRight(to_remove->getLeft());
						to_remove->getLeft()->setParent(ogP);
					}
				}
			}
			else
			{
				if(to_remove->getLeft()!= NULL)
				{
				  ogP->setLeft(to_remove->getLeft());
					to_remove->getLeft()->setParent(ogP);
				}
				else
				{
					ogP->setLeft(NULL);
					if(to_remove->getRight()!=NULL)
					{	
						ogP->setLeft(to_remove->getRight());
						to_remove->getRight()->setParent(ogP);
					}
				}
			}
		}
		else
		{
			
			Node<Key,Value>* removeNode = to_remove;
			AVLNode<Key, Value>* swap = 
				internalFind(BinarySearchTree<Key, Value>::predecessor(removeNode)->getKey());
			nodeSwap(to_remove, swap);
			ogP = to_remove->getParent(); 

			if(ogP!=swap)
			{
				if(to_remove->getRight()!= NULL)
				{	
					ogP->setRight(to_remove->getRight());
					to_remove->getRight()->setParent(ogP);
				}
				else
				{
					ogP->setRight(NULL);
					if(to_remove->getLeft()!=NULL)
					{	
						ogP->setRight(to_remove->getLeft());
						to_remove->getLeft()->setParent(ogP);
					}
				}
			}
			else
			{
				if(to_remove->getLeft()!= NULL)
				{
					ogP->setLeft(to_remove->getLeft());
					to_remove->getLeft()->setParent(ogP);
				}
				else
				{
					ogP->setLeft(NULL);
					if(to_remove->getRight()!=NULL)
					{	
						ogP->setLeft(to_remove->getRight());
						to_remove->getRight()->setParent(ogP);
					}
				}
			}
		}
		
		delete to_remove;
		setTreeBalance(ogP);
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);

		if(this->AVLroot_ == n1) {
        this->AVLroot_ = n2;
    }
    else if(this->AVLroot_ == n2) {
        this->AVLroot_ = n1;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: setTreeBalance(AVLNode<Key, Value>* n)
{
	AVLNode<Key, Value>* temp = n;
	while(temp!=NULL)
	{
		
		int b = BinarySearchTree<Key, Value>::height(temp->getRight())-BinarySearchTree<Key, Value>::height(temp->getLeft());
		// std::cout << "we at node " << temp->getKey() << " setting balance of " << b << std::endl;
		temp->setBalance(b);
		temp = temp->getParent();
	}

	checkBalance(n);
}

template<class Key, class Value>
void AVLTree<Key, Value>:: checkBalance(AVLNode<Key, Value>* n)
{
	// std::cout << "we at leaf " << n->getKey() << std::endl;
	AVLNode<Key, Value>* temp = n;
	while(temp!=NULL)
	{
		if(abs(temp->getBalance())>1){
						// std::cout << "I guess we fix on " << temp->getKey() << std::endl;
						fixBalance(temp);
						break;}
		temp = temp->getParent();
	}
}

template<class Key, class Value>
void AVLTree<Key, Value>::fixBalance(AVLNode<Key, Value>* n)
{
	// std::cout << "start of fixBalance" << std::endl;
		// BinarySearchTree<Key,Value>::print();
		if(n->getBalance()>1)
		{
			// std::cout << "decided on right zig ";
			if(n->getRight()->getBalance()<0)
			{
				// std:: cout << "zag";
				// Node* ogR = n->getRight();
				rotateRight(n->getRight());
				rotateLeft(n);
			}
			else
				rotateLeft(n);
		}
		if(n->getBalance()<-1)
		{
			// std::cout << "decided on left zig ";
			if(n->getLeft()->getBalance()>0)
			{		
				// std:: cout << "zag";		
				rotateLeft(n->getLeft());
				rotateRight(n);
			}
			else
				rotateRight(n);
		}
	// std::cout << std::endl;
	setTreeBalance(n);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* n)
{
	AVLNode<Key, Value>* ogP = n->getParent();
	AVLNode<Key, Value>* ogL = n->getLeft();
	
	if(ogL->getRight()!=NULL)
	{	
		n->setLeft(ogL->getRight());
		ogL->getRight()->setParent(n);
	}
	else
		n->setLeft(NULL);
	
	n->setParent(ogL);
	
	if(ogP!=NULL)
	{
		ogL->setParent(ogP);
		if(ogP->getRight()==n){
			ogP->setRight(ogL);
			ogP->setBalance(ogL->getBalance());
		}
		else
			ogP->setLeft(ogL);
	}
	else
	{
		ogL->setParent(NULL);
		AVLroot_ = ogL;
		BinarySearchTree<Key,Value>::root_ = AVLroot_;
	}
	
	ogL->setRight(n);
	
	if(n!=NULL)
		n->setBalance(BinarySearchTree<Key, Value>::height(n->getRight())-BinarySearchTree<Key, Value>::height(n->getLeft()));
	if(ogL!=NULL)
		ogL->setBalance(BinarySearchTree<Key, Value>::height(ogL->getRight())-BinarySearchTree<Key, Value>::height(ogL->getLeft()));
	if(ogP!=NULL)
		ogP->setBalance(BinarySearchTree<Key, Value>::height(ogP->getRight())-BinarySearchTree<Key, Value>::height(ogP->getLeft()));
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* n)
{
	AVLNode<Key, Value>* ogP = n->getParent();
	AVLNode<Key, Value>* ogR = n->getRight();

	if(ogR->getLeft()!=NULL)
	{	
		n->setRight(ogR->getLeft());
		ogR->getLeft()->setParent(n);
	}
	else
		n->setRight(NULL);
	
	n->setParent(ogR);
	
	if(ogP!=NULL)
	{
		ogR->setParent(ogP);
		if(ogP->getLeft()==n)
			ogP->setLeft(ogR);
		else
			ogP->setRight(ogR);
	}
	else
	{
		ogR->setParent(NULL);
		AVLroot_ = ogR;
		BinarySearchTree<Key,Value>::root_ = AVLroot_;
	}

	ogR->setLeft(n);
	
	if(n!=NULL)
		n->setBalance(BinarySearchTree<Key, Value>::height(n->getRight())-BinarySearchTree<Key, Value>::height(n->getLeft()));
	if(ogR!=NULL)
		ogR->setBalance(BinarySearchTree<Key, Value>::height(ogR->getRight())-BinarySearchTree<Key, Value>::height(ogR->getLeft()));
	if(ogP!=NULL)
		ogP->setBalance(BinarySearchTree<Key, Value>::height(ogP->getRight())-BinarySearchTree<Key, Value>::height(ogP->getLeft()));
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
		if(BinarySearchTree<Key,Value>::root_==NULL) return NULL;
		AVLNode<Key, Value>* temp = AVLroot_;
		
		while(temp->getLeft()!=NULL || temp->getRight()!=NULL)
		{
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

#endif
