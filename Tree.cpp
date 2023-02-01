/** @file Tree.cpp */

#include "Tree.h" 
#include "Node.h" 
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;


//////////////////////////////////////////////////////////////
//      Constructor and Destructor Section
//////////////////////////////////////////////////////////////

Tree::Tree() : theWord(" "), rootPtr(nullptr)
{
} //end default constructor

Tree::Tree(const string& str)
{
   rootPtr = nullptr;
   theWord = str;
   convertStrToTree();
} //end constructor

Tree::~Tree()
{
   destroyTree(rootPtr);
   rootPtr = nullptr;
} //end destructor


//////////////////////////////////////////////////////////////
//      Protected Utility Methods Section
//////////////////////////////////////////////////////////////

/*
Recursively searches for target value in the tree by using 
a preorder traversal.
*/
bool Tree::containsHelper(Node* subTreePtr, const char& target) const
{
   if (subTreePtr == nullptr) // base case
      return false;
   
   if (subTreePtr->getItem() == target) // found it
   {
      return true;
   }
   else 
   {
      bool isFound = containsHelper(subTreePtr->getLeftChildPtr(), target);
      if (!isFound) // no need to search right subTree if already found
      {
         isFound = containsHelper(subTreePtr->getRightChildPtr(), target);
      }  // end if
      
      return isFound;
   }  // end if 
}  // end containsHelper

//inserts a new item into the binary search tree to which subTreePtr point
Node* Tree::addHelper(Node* subTreePtr, Node* newNodePtr)
{
   if (subTreePtr == nullptr)
      return newNodePtr;
   else if (subTreePtr->getItem() > newNodePtr->getItem())
   {
      //insert into the left subtree
      Node* tempPtr = addHelper(subTreePtr->getLeftChildPtr(), newNodePtr);
      subTreePtr->setLeftChildPtr(tempPtr);
   }
   else
   {
      //insert into the right subtree
      Node* tempPtr = addHelper(subTreePtr->getRightChildPtr(), newNodePtr);
      subTreePtr->setRightChildPtr(tempPtr);
   }

   return subTreePtr;
} //end addHelper

// swaps chars passed in by reference
void Tree::swapper (char &x, char &y)
{
   char temp;
   temp = x;
   x = y;
   y = temp;
} //end swapper

//sorts string using Bubble sort
void Tree::stringSort(string &str)
{
   bool swapped; //sets swapped true if any swap occurs
   
   do {
      swapped = false;
      for (int i=0; i < str.length() - 1; i++)
      {
         if (str[i] > str[i+1])
         {
            swapper(str[i], str[i+1]);
            swapped = true;
         }
      }
   } while (swapped);
} //end stringSort

int Tree::findMidpoint(int length)
{
   int mid;

   if (length % 2 == 0) //even
      mid = length/2;
   else //odd
      mid = 1 + (length-1)/2;

   return mid;
} //end findMidpoint

/*
add every char of the Secret Word to the tree in order to have a Balanced Binary Search Tree.
By sorting the string then adding its midpoint to the tree each time
*/
void Tree::convertStrToTree()
{
   int midpoint;
   char midCharacter;
   string str = theWord;

   if (str != " ") //valid word
   {
      stringSort(str); //sorts string

      while (str.length() != 0) //base case
      {
         midpoint = findMidpoint(str.length()); //midpoint of string
         midCharacter = str[midpoint-1]; //character at midpoint of string
         
         add(midCharacter);
         
         str.erase(midpoint-1, 1); //removes the char from the string
      }
   }
   else
      cout << "The Word wasn't successfully converted to a Tree. \n";
} //end convertStrToTree

void Tree::destroyTree(Node* subTreePtr)
{
   if (subTreePtr != nullptr)
   {
      destroyTree(subTreePtr->getLeftChildPtr());
      destroyTree(subTreePtr->getRightChildPtr());
      delete subTreePtr;
   }  // end if
}  // end destroyTree


//////////////////////////////////////////////////////////////
//      PUBLIC METHODS BEGIN HERE
//////////////////////////////////////////////////////////////

void Tree::add(const char& newData)
{
   Node* newNodePtr = new Node(newData);
   rootPtr = addHelper(rootPtr, newNodePtr);
} //end add

//use of containsHelper for a recursive search
bool Tree::contains(const char& anEntry) const
{
   return containsHelper(rootPtr, anEntry);
} //end contains

//makes a new tree with the word
void Tree::setWord(const string& str)
{
   destroyTree(rootPtr);
   rootPtr = nullptr;
   theWord = str;
   convertStrToTree();
} //end setWord

string Tree::getWord() const
{
   return theWord;
} //end getWord

//end Tree.cpp