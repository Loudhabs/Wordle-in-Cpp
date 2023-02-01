#ifndef NODE_H
#define NODE_H

class Node
{   
private:
   char item;           // Data portion
   Node* leftChildPtr;   // Pointer to left child
   Node* rightChildPtr;  // Pointer to right child

public:
   Node();
   Node(const char& anItem);
   Node(const char& anItem,
              Node* leftPtr,
              Node* rightPtr);

   void setItem(const char& anItem);
   char getItem() const;
   
   bool isLeaf() const;

   Node* getLeftChildPtr() const;
   Node* getRightChildPtr() const;
   
   void setLeftChildPtr(Node* leftPtr);
   void setRightChildPtr(Node* rightPtr);            
}; // end Node

#endif 

//end Node.h