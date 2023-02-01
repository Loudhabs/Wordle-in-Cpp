#ifndef TREE_H
#define TREE_H

#include "Node.h"
#include <string>
using namespace std;


//Class that transforms a string to a Balanced Binary Search Tree
class Tree
{
private:
   string theWord;
   Node* rootPtr;
   
protected:
   //------------------------------------------------------------
   // Protected Utility Methods Section:
   // Recursive helper methods for the public methods.
   //------------------------------------------------------------
   
   // Recursively deletes all nodes from the tree.
   void destroyTree(Node* subTreePtr);
   
   // Recursively searches for target value in the tree by using a
   // preorder traversal.
   bool containsHelper(Node* subTreePtr, const char& target) const;

   void convertStrToTree();

   // Recursively adds a new node to the tree in a way to
   // keep the tree sorted.
   Node* addHelper(Node* subTreePtr, Node* newNodePtr);

   void swapper (char &x, char &y); //used in stringSort()
   void stringSort(string &str); //used in convertStrToTree()
   int findMidpoint(int length); //used in convertStrToTree()

public:
   //------------------------------------------------------------
   // Constructor and Destructor Section.
   //------------------------------------------------------------
   Tree();
   Tree(const string& str);
   virtual ~Tree();
   
   //------------------------------------------------------------
   // Public BinaryTreeInterface Methods Section.
   //------------------------------------------------------------

   void add(const char& newData); // Adds a node

   bool contains(const char& anEntry) const;

   void setWord(const string& str);

   string getWord() const;

}; // end Tree

#endif

//end Tree.h