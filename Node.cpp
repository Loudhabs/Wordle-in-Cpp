#include "Node.h"
#include <cstddef>
#include <string>

Node::Node() : leftChildPtr(nullptr), rightChildPtr(nullptr)
{
}  // end default constructor

Node::Node(const char& anItem) : item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr)
{
}  // end constructor

Node::Node(const char& anItem, Node* leftPtr,
                             Node* rightPtr) : item(anItem), leftChildPtr(leftPtr), rightChildPtr(rightPtr)
{
}  // end constructor

void Node::setItem(const char& anItem)
{
   item = anItem;
}  // end setItem

char Node::getItem() const 
{
   return item;
}  // end getItem

bool Node::isLeaf() const
{
   return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
}

void Node::setLeftChildPtr(Node* leftPtr) 
{
   leftChildPtr = leftPtr;
}  // end setLeftChildPtr

void Node::setRightChildPtr(Node* rightPtr) 
{
   rightChildPtr = rightPtr;
}  // end setRightChildPtr

Node* Node::getLeftChildPtr() const
{
   return leftChildPtr;
}  // end getLeftChildPtr		

Node* Node::getRightChildPtr() const
{
   return rightChildPtr;
}  // end getRightChildPtr

//end Node.cpp
