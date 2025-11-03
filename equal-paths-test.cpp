#include <iostream>
#include <cstdlib>
#include "equal-paths.h"
using namespace std;


Node* a;
Node* b;
Node* c;
Node* d;
Node* e;
Node* f;

void setNode(Node* n, int key, Node* left=NULL, Node* right=NULL)
{
  n->key = key;
  n->left = left;
  n->right = right;
}

void test1(const char* msg)
{
	// one node, this is balanced
  setNode(a,1,NULL, NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test2(const char* msg)
{
	// a -> b, only one leaf
  setNode(a,1,b,NULL);
  setNode(b,2,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test3(const char* msg)
{
	// a -> b 
	// a ->c
	// both leaves on same level
  setNode(a,1,b,c);
  setNode(b,2,NULL,NULL);
  setNode(c,3,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test4(const char* msg)
{
	// a->c, only one leaf
  setNode(a,1,NULL,c);
  setNode(c,3,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test5(const char* msg)
{
	// a -> b -> d 
	// a -> c 
  setNode(a,1,b,c);
  setNode(b,2,NULL,d);
  setNode(c,3,NULL,NULL);
  setNode(d,4,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test6(const char* msg)
{
	// a -> b -> d 
	// a -> b -> d -> f
	// a -> c -> e
  setNode(a,1,b,c);
  setNode(b,2,NULL,d);
  setNode(c,3,NULL,e);
  setNode(d,4,NULL,NULL);
	setNode(e,5,NULL,NULL);
	setNode(f,6,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

void test7(const char* msg)
{
	// a -> b -> c
  setNode(a,1,b,NULL);
  setNode(b,2,NULL,c);
  setNode(c,3,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}
void test8(const char* msg)
{
	// a -> b -> c
	// a -> d -> e
  setNode(a,1,b,d);
  setNode(b,2,NULL,c);
  setNode(c,3,NULL,NULL);
  setNode(d,4,e,NULL);
	setNode(e,5,NULL,NULL);
  cout << msg << ": " <<   equalPaths(a) << endl;
}

int main()
{
  a = new Node(1);
  b = new Node(2);
  c = new Node(3);
  d = new Node(4);
  e = new Node(5);
  f = new Node(6);

  test1("Test1");
  test2("Test2");
  test3("Test3");
  test4("Test4");
  test5("Test5");
  test6("Test6");
  test7("Test7");
  test8("Test8");
 
  delete a;
  delete b;
  delete c;
  delete d;
	delete e;
	delete f;
}

