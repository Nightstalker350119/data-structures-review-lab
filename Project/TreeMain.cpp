// TreeMain.cpp - the entry point of the tree application
// Code by Cromwell D. Enage, December 2008
// Updated by Jeremiah Blanchard, January 2009
// Updated by Cromwell D. Enage, April 2009
#include <limits>
#include <string>
#include <cassert>
#include <iostream>
#include "Structures/Tree.h"

using namespace std;

// Wrappers.
class SizeHolder { SizeHolder(); friend SizeHolder create(size_t element); public: size_t held; };
struct StringHolder { string beans; };

// Prototypes (so that implementations may go after main)
bool isNotLeafSize(SizeHolder const& element);
void createSizeNodes(TreeNode<SizeHolder>* node);
void printSize(SizeHolder const& element);

bool isNotLeafString(char* const& data);
void createStringNodes(TreeNode<char*>* node);
void printString(char* const& data);
void pruneString(char* const& data);
void deleteString(char* const& data);

template <typename T, typename Predicate, typename Function>
void buildTree(TreeNode<T>* node, Predicate& canHaveChildElements, Function& createChildren);

int main()
{
	// Everything must compile.
	TreeNode<StringHolder> dummy;

	// Run the tests.
	TreeNode<SizeHolder>* size_root = new TreeNode<SizeHolder>(create(5));
	TreeNode<char*>* string_root = new TreeNode<char*>();

	assert(!size_root->getParent() && "You did not initialize your parent member.");
	assert(!string_root->getData() && "You did not default-construct your data member.");

	Tree<SizeHolder> size_tree(size_root);

	buildTree(size_root, isNotLeafSize, createSizeNodes);
	cout << "After construction," << endl << "    Breadth-first traversal:";
	size_tree.breadthFirstTraverse(printSize);
	cout << endl << "    Pre-order traversal:";
	size_tree.preOrderTraverse(printSize);
	cout << endl << "    Post-order traversal:";
	size_tree.postOrderTraverse(printSize);
	cout << endl << endl;

	size_root->getChild(4)->deleteChildren();
	cout << "After deleteChildren call," << endl << "    Breadth-first traversal:";
	size_tree.breadthFirstTraverse(printSize);
	cout << endl << "    Pre-order traversal:";
	size_tree.preOrderTraverse(printSize);
	cout << endl << "    Post-order traversal:";
	size_tree.postOrderTraverse(printSize);
	cout << endl << endl;

	Tree<char*> string_tree(string_root);
	char* root_data = new char[2];

	root_data[0] = '5';
	root_data[1] = '\0';
	string_root->getData() = root_data;
	buildTree(string_root, isNotLeafString, createStringNodes);
	cout << "After construction," << endl << "    Breadth-first traversal:";
	string_tree.breadthFirstTraverse(printString);
	cout << endl << "    Pre-order traversal:";
	string_tree.preOrderTraverse(printString);
	cout << endl << "    Post-order traversal:";
	string_tree.postOrderTraverse(printString);
	cout << endl << endl;

	TreeNode<char*>* prune_string = string_root->getChild(4);
	Tree<char*> prune_string_tree(prune_string);

	prune_string_tree.postOrderTraverse(pruneString);
	prune_string->deleteChildren();
	cout << "After deleteChildren call," << endl << "    Breadth-first traversal:";
	string_tree.breadthFirstTraverse(printString);
	cout << endl << "    Pre-order traversal:";
	string_tree.preOrderTraverse(printString);
	cout << endl << "    Post-order traversal:";
	string_tree.postOrderTraverse(printString);
	cout << endl << endl;

	string_tree.postOrderTraverse(deleteString);
	delete string_root;
	delete size_root;

	cout << "Press ENTER to continue..." << endl;
	cin.ignore((numeric_limits<streamsize>::max)(), '\n');
	return 0;
}

SizeHolder::SizeHolder()
{
}

SizeHolder create(size_t element)
{
	SizeHolder holder;
	holder.held = element;
	return holder;
}

void printSize(SizeHolder const& element)
{
	cout << ' ' << element.held;
}

bool isNotLeafSize(SizeHolder const& element)
{
	return 1 < element.held;
}

void createSizeNodes(TreeNode<SizeHolder>* node)
{
	TreeNode<SizeHolder>* child;

	for (size_t i = 0; i < node->getData().held; ++i)
	{
		child = new TreeNode<SizeHolder>(create(i), node);
		assert((child->getParent() == node) && "You\'re not linking the child to its parent.");
		assert((child == node->getChild(i)) && "You\'re not linking the parent to its child.");
	}
}

bool isNotLeafString(char* const& data)
{
	return '1' < data[0];
}

void createStringNodes(TreeNode<char*>* node)
{
	TreeNode<char*>* child = 0;
	char* data = 0;

	// I'd use Ewok names instead if I actually remembered any of them...
	for (char charbinx = '0'; charbinx < node->getData()[0]; ++charbinx)
	{
		child = new TreeNode<char*>(node);

		char*& data = child->getData();

		assert(!data && "You did not default-construct your data member.");
		data = new char[2];
		data[0] = charbinx;
		data[1] = '\0';
		assert(
		    (child->getParent() == node)
		 && "You\'re not linking the child to its parent."
		);
		assert(
		    (child == node->getChild(charbinx - '0'))
		 && "You\'re not linking the parent to its child."
		);
	}
}

void printString(char* const& data)
{
	cout << ' ' << data;
}

void pruneString(char* const& data)
{
	if (data[0] < '4')
	{
		delete[] data;
	}
}

void deleteString(char* const& data)
{
	delete[] data;
}

template <typename T, typename Predicate, typename Function>
void buildTree(TreeNode<T>* node, Predicate& canHaveChildElements, Function& createChildren)
{
	QueueList<TreeNode<T>*> nodeQueue;
	nodeQueue.enqueue(node);

	while (!nodeQueue.isEmpty())
	{
		node = nodeQueue.getFront();
		nodeQueue.dequeue();

		if (canHaveChildElements(node->getData()))
		{
			createChildren(node);
		}

		for (std::size_t i = 0; i < node->getChildCount(); ++i)
		{
			nodeQueue.enqueue(node->getChild(i));
		}
	}
}

