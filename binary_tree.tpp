#include "binary_tree.hpp"

#include <stdexcept>
#include <iostream>

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::BinaryTree(
    const TreeItemType &rootItem) {
  root = new NodeType(rootItem);
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::BinaryTree(const TreeItemType &rootItem,
                                                   BinaryTree &leftTree,
                                                   BinaryTree &rightTree) {
  root = new NodeType(rootItem);

  attachLeftSubtree(leftTree);
  attachRightSubtree(rightTree);
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::BinaryTree(NodeType *nodePtr) {
  root = nodePtr;
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::BinaryTree(const BinaryTree &tree) {
  copyTree(tree.root, root);
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType> &
BinaryTree<TreeItemType, FunctionType>::operator=(const BinaryTree &rhs) {
  if (this != &rhs) {
    destroyTree(root);        // deallocate left-hand side
    copyTree(rhs.root, root); // copy right-hand side
  }
  return *this;
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>::~BinaryTree() {
  destroyTree(root);
}

template <typename TreeItemType, typename FunctionType>
bool BinaryTree<TreeItemType, FunctionType>::isEmpty() const noexcept {
  return (root == nullptr);
}

template <typename TreeItemType, typename FunctionType>
TreeItemType BinaryTree<TreeItemType, FunctionType>::rootData() const

{
  if (root == nullptr) {
    throw std::logic_error("Empty tree in BinaryTree:rootData");
  }
  return root->item;
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::setRootData(
    const TreeItemType &newItem) {
  if (root != nullptr) {
    root->item = newItem;
  } else {
    root = new NodeType(newItem);
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::attachLeft(
    const TreeItemType &newItem) {
  if (root == nullptr) {
    throw std::logic_error("Empty tree in BinaryTree::attachLeft");
  } else if (root->leftChildPtr != nullptr) {
    throw std::logic_error("Cannot overwrite left subtree");
  } else {
    root->leftChildPtr = new NodeType(newItem);
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::attachRight(
    const TreeItemType &newItem) {

    //Check if the root node exists
    if (root == nullptr)
    {
        throw std::logic_error("Empty tree in BinaryTree::attachRight");
    }

    //Check if the right node already exists
    else if (root->rightChildPtr != nullptr)
    {
        throw std::logic_error("Cannot overwrite right subtree");
    }

    //Root node exists and right node does not already exist
    else
    {
        root->rightChildPtr = new NodeType(newItem);
    }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::attachLeftSubtree(
    BinaryTree &leftTree) {
  if (root == nullptr) {
    throw std::logic_error("Empty tree in BinaryTree::attachLeftSubtree");
  } else if (root->leftChildPtr != nullptr) {
    throw std::logic_error("Cannot overwrite left subtree");
  } else {
    root->leftChildPtr = leftTree.root;
    leftTree.root = nullptr;
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::attachRightSubtree(
    BinaryTree &rightTree) {

    //Check if the root node exists
    if (root == nullptr)
    {
        throw std::logic_error("Empty tree in BinaryTree::attachRightSubtree");
    }

    //Check if the right node already exists
    else if(root->rightChildPtr != nullptr)
    {
        throw std::logic_error("Cannot overwrite right subtree");
    }

    //Root node exists and right node does not already exist
    else
    {
        root->rightChildPtr = rightTree.root;
        rightTree.root = nullptr;
    }

}
    

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::detachLeftSubtree(
    BinaryTree &leftTree) {
  if (root == nullptr) {
    throw std::logic_error("Empty tree in BinaryTree::detachLeftSubtree");
  } else {
    leftTree = BinaryTree(root->leftChildPtr);
    root->leftChildPtr = nullptr;
  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::detachRightSubtree(
    BinaryTree &rightTree) {

    //Check if the root node exists
    if (root == nullptr)
    {
        throw std::logic_error("Empty tree in BinaryTree::detachRightSubtree");
    }

    //Store the right subtree/node in the given reference
    else
    {
        rightTree = BinaryTree(root->rightChildPtr);
        root->rightChildPtr = nullptr;
    }

}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>
BinaryTree<TreeItemType, FunctionType>::leftSubtree() const {
  NodeType *subTreePtr = nullptr;
  copyTree(root->leftChildPtr, subTreePtr);
  return BinaryTree(subTreePtr);
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType>
BinaryTree<TreeItemType, FunctionType>::rightSubtree() const {

    //Create a new pointer
    NodeType* subTreePtr = nullptr;

    //Make a copy of the right subtree and make the new pointer point to the copy
    copyTree(root->rightChildPtr, subTreePtr);

    //Return a new tree with the copy as root
    return BinaryTree(subTreePtr);
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::preorderTraverse(
    FunctionType visit) {
  preorder(root, visit);
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::inorderTraverse(
    FunctionType visit) {
  inorder(root, visit);
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::postorderTraverse(
    FunctionType visit) {
  postorder(root, visit);
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::copyTree(
    NodeType *treePtr, NodeType *&newTreePtr) const {

    // preorder traversal
  if (treePtr != nullptr) 
  { 
    // copy root node

      //Copy item into root node
      newTreePtr = new NodeType(treePtr->item);
      
    // copy left subtree

      NodeType* originalLeftSubtree = treePtr->leftChildPtr;
      NodeType* newLeftSubtree;
    
      //Recurse through left subtree
      copyTree(originalLeftSubtree, newLeftSubtree);

    // copy right subtree
      NodeType* originalRightSubtree = treePtr->rightChildPtr;
      NodeType* newRightSubtree;
   
      //Recurse through right subtree
      copyTree(originalRightSubtree, newRightSubtree);


      //Assign left and right children to parent
      newTreePtr->leftChildPtr = newLeftSubtree;
      newTreePtr->rightChildPtr = newRightSubtree;


  } else {
    //Base Case, a leaf is reached / exceeded
    newTreePtr = nullptr; // copy empty tree

  }
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::destroyTree(NodeType *&treePtr) {
  // postorder traversal
  if (treePtr != nullptr) {
    
    //destroy left subtree
      //Recurse through left subtree
    NodeType* leftSubtree = treePtr->leftChildPtr;
    destroyTree(leftSubtree);

    //destroy right subtree
      //Recurse through right subtree
    NodeType* rightSubtree = treePtr->rightChildPtr;
    destroyTree(rightSubtree);

    // delete root
    delete treePtr;
    treePtr = nullptr;
  }

  //Base case, when treePtr == nullptr - do nothing
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::preorder(NodeType *treePtr,
                                                      FunctionType visit) {
  if (treePtr != nullptr) {
   
    
      visit(treePtr->item); //Act on root first, before traversing subtrees

      //Recurse through left subtree
      NodeType* leftSubtree = treePtr->leftChildPtr;
      preorder(leftSubtree, visit);

      //Recurse through right subtree
      NodeType* rightSubtree = treePtr->rightChildPtr;
      preorder(rightSubtree, visit);
  }

  //Base case, when treePtr == nullptr - do nothing
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::inorder(NodeType *treePtr,
                                                     FunctionType visit) {
  if (treePtr != nullptr) {
   

      //Recurse through left subtree
      NodeType* leftSubtree = treePtr->leftChildPtr;
      preorder(leftSubtree, visit);

      visit(treePtr->item); //Act on root before moving on to right subtree

      //Recurse through right subtree
      NodeType* rightSubtree = treePtr->rightChildPtr;
      preorder(rightSubtree, visit);
  }

  //Base case, when treePtr == nullptr - do nothing
}

template <typename TreeItemType, typename FunctionType>
void BinaryTree<TreeItemType, FunctionType>::postorder(NodeType *treePtr,
                                                       FunctionType visit) {
  if (treePtr != nullptr) {
   

      //Recurse through left subtree
      NodeType* leftSubtree = treePtr->leftChildPtr;
      preorder(leftSubtree, visit);

      //Recurse through right subtree
      NodeType* rightSubtree = treePtr->rightChildPtr;
      preorder(rightSubtree, visit);

      visit(treePtr->item); //Act on root after traversing both subtrees
  }

  //Base case, when treePtr == nullptr - do nothing
}

template <typename TreeItemType, typename FunctionType>
BinaryTree<TreeItemType, FunctionType> BinaryTree<TreeItemType, FunctionType>::makeBinaryTree(const TreeItemType *array, int low, int high) {
    std::cout << "low, high = " << low << " " << high << std::endl;
    
    //Base case 1: low == high, only one item left
    if (low == high)
    {
        //Create a new BinaryTree
        //Assign item as root
        BinaryTree newTree = BinaryTree(array[low]);

        return newTree;
    }
    //Base case 2: high - low == 1, only two items left
    else if (high - low == 1)
    {
        BinaryTree newTree = BinaryTree(array[low]);

        BinaryTree rightSubtree = BinaryTree(array[high]);

        newTree.attachRightSubtree(rightSubtree);

        return newTree;
    }
    //Otherwise...

    //Find the midpoint
    int midIndex = (high + low) / 2;

    //Find the low and high for each subtree
    int leftLowIndex = low;
    int leftHighIndex = midIndex - 1;

    int rightLowIndex = midIndex + 1;
    int rightHighIndex = high;

    //Create a new BinaryTree
    //Assign middle item as root
    BinaryTree newTree = BinaryTree(array[midIndex]);

    //Create left subtree
    BinaryTree leftSubtree = makeBinaryTree(array, leftLowIndex, leftHighIndex);

    //Attach left subtree
    newTree.attachLeftSubtree(leftSubtree);

    //Create right subtree
    BinaryTree rightSubtree = makeBinaryTree(array, rightLowIndex, rightHighIndex);;

    //Attach right subtree
    newTree.attachRightSubtree(rightSubtree);

    return newTree;
    
}
