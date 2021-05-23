#pragma once
// Binary Search Tree ADT
// Created by Ashley Irawan

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include "BSTData.h"
#include "BinaryNode.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
public:
    // insert a node at the correct location
    bool insert(const ItemType& item);
    // remove a node if found
    //bool remove(const ItemType &item);
    // find a target node
    bool removeNode(BinarySearchTree<ItemType>& tree, ItemType key);
    bool search(const ItemType &target, ItemType &returnedItem) const;
    bool insertCRNList(const ItemType& crn) const;

private:
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode)
    {
        BinaryNode<ItemType>* pWalk = nodePtr;

        if (nodePtr == nullptr) // == NULL
        {
            nodePtr = newNode;
            return nodePtr;
        }
        else
        {

            //parent = pWalk;
            if (nodePtr->getItem() > newNode->getItem())
            {
                pWalk = _insert(nodePtr->getLeftPtr(), newNode);
                nodePtr->setLeftPtr(pWalk);
            }
            else
            {
                pWalk = _insert(nodePtr->getRightPtr(), newNode);
                nodePtr->setRightPtr(pWalk);
            }
        }


        return nodePtr;
    }

    // search for target node
    BinaryNode<ItemType>* _search(BinaryNode<ItemType>* treePtr, const ItemType& target) const
    {
        BinaryNode<ItemType>* found = nullptr;
        BinaryNode<ItemType>* pWalk = treePtr;
        ItemType temptarget = target;
        if (pWalk == nullptr)
        {
            return found;
        }
        else if (pWalk && temptarget == pWalk->getItem())
        {
            found = pWalk;
            return found;
        }
        else if (pWalk->getItem() > temptarget)
        {
            pWalk = _search(pWalk->getLeftPtr(), target);
            return pWalk;
        }
        else if (pWalk->getItem() < temptarget)
        {
            pWalk = _search(pWalk->getRightPtr(), target);
            return pWalk;
        }
        return found;
    }

    // find the smallest node
   // BinaryNode<ItemType>* _findSmallest(BinaryNode<ItemType>* nodePtr, ItemType& smallest) const;

    // find the largest node
    //BinaryNode<ItemType>* _findLargest(BinaryNode<ItemType>* nodePtr, ItemType& smallest) const;

    // internal remove node: locate and delete target node under nodePtr subtree
    // BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool &success);

     // delete target node from tree, called by internal remove node
     //BinaryNode<ItemType>* _removeNode(BinaryNode<ItemType>* targetNodePtr);

     // remove the leftmost node in the left subtree of nodePtr
     //BinaryNode<ItemType>* _removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType &successor);

};


///////////////////////// public function definitions ///////////////////////////
//Inserting items within a tree
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType& newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    return true;
}

//Wrapper for _search
// - it calls the private _search function that returns a Node pointer or NULL
// - if found, it copies data from that node and sends it back to the caller
//   via the output parameter, and returns true, otherwise it returns false.
template<class ItemType>
bool BinarySearchTree<ItemType>::search(const ItemType& anEntry, ItemType& returnedItem) const
{
    BinaryNode<ItemType>* temp = nullptr;
    temp = _search(this->rootPtr, anEntry);
    if (temp)
    {
        returnedItem = temp->getItem();
        return true;
    }
    else
        return false;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::insertCRNList(const ItemType &target) const
{
    BinaryNode<ItemType>* temp = nullptr;
    //BinaryNode<ItemType>* course = nullptr;

    temp = _search(this->rootPtr, target);
    //std::cout << temp->getItem().getCRN(0) << " " << temp -> getItem().getCRN(1) << std::endl;
    //course = temp;
    if (temp){
        temp->getItem().insertCRN(temp->getItem().getCRNlist(), target.getCRN(0));
    }
    return true;

}

template<class ItemType>
bool BinarySearchTree<ItemType>::removeNode(BinarySearchTree<ItemType>& tree, ItemType key) {
   BinaryNode<ItemType>* par = nullptr;
   BinaryNode<ItemType>* cur = tree.rootPtr;
   while (cur)
    { // Search for node
      if (cur->getItem() == key)
      { // Node found
         if (cur->isLeaf()) // Remove leaf
            {   if(par->getLeftPtr()->getItem() == key)
                    par->setLeftPtr(nullptr);
                else
                    par->setRightPtr(nullptr);
            }
         else if (!par) // Node is root
         {
             tree.rootPtr = nullptr;
             if (par->getLeftPtr() == cur)
               par->setLeftPtr(nullptr);
             else
               par->setRightPtr(nullptr);
         }
         else if (cur->getLeftPtr() && !cur->getRightPtr())
            {    // Remove node with only left child
            if (!par) // Node is root
               tree.rootPtr = cur->getLeftPtr();
            else if (par->getLeftPtr() == cur)
               par->setLeftPtr(cur->getLeftPtr());
            else
               par->setRightPtr(cur->getLeftPtr());
            }
         else if (!cur->getLeftPtr() && cur->getRightPtr())
            {    // Remove node with only right child
            if (!par) // Node is root
               tree.rootPtr = cur->getRightPtr();
            else if (par->getLeftPtr() == cur)
               par->setLeftPtr(cur->getRightPtr());
            else
               par->setRightPtr(cur->getRightPtr());
            }
         else
            {                                  // Remove node with two children
            // Find successor (leftmost child of right subtree)
            BinaryNode<ItemType>* suc = cur->getRightPtr();
            while (suc->getLeftPtr())
               suc = suc->getLeftPtr();
            ItemType successorData = suc->getItem(); //Create copy of suc's data
            removeNode(tree, suc->getItem());    // Remove successor
            cur->setItem(successorData);    //Assign cur's data with successorData
            }
         return true;// Node found and removed
      }
      else if (cur->getItem() < key) { // Search right
         par = cur;
         cur = cur->getRightPtr();
      }
      else {                     // Search left
         par = cur;
         cur = cur->getLeftPtr();
      }
   }
   return false;// Node not found
}


//////////////////////////// private functions ////////////////////////////////////////////

#endif


