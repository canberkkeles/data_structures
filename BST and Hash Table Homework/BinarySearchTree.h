#ifndef BINARYWORDTREE_H
#define BINARYWORDTREE_H

template <class Object>
struct treeNode{
	treeNode* leftChild;
	treeNode* rightChild;
	Object word;
	Object translation;

	treeNode(treeNode* left, treeNode* right,Object w, Object t):leftChild(left),rightChild(right),word(w),translation(t){}
};

template <class Object>
class BinaryWordTree{
public:
	BinaryWordTree(const Object & notFound); //CONSTRUCTOR
	~BinaryWordTree(); //DESTRUCTOR

	const Object & translate(const Object & word) const; //FIND
	bool addTranslation(const Object & word,const Object & translation,treeNode<Object> * t); //
	void printTree() const;

	void makeEmpty(); //HELPER FOR DESTRUCTOR
	void insert(const Object & word,const Object & translation); //INSERT AN ELEMENT
	treeNode<Object> * getRoot(){return root;} //INORDER TO USE ROOT OUTSIDE AND CALL ADD TRANSLATION FUNCTION


private:
	treeNode<Object>* root;
	const Object ITEM_NOT_FOUND;
	
	const Object & elementAt(treeNode<Object> * t)const; //PRIVATE HELPER
	treeNode<Object> * find(const Object & word, treeNode<Object> * t) const; //PRIVATE HELPER
	void insert(const Object & word, const Object & translation, treeNode<Object> * & t); //PRIVATE HELPER
	void makeEmpty(treeNode<Object> * & t) const; //PRIVATE HELPER
	void printTree(treeNode<Object> * t) const; //PRIVATE HELPER
};


#include "BinarySearchTree.cpp"
#endif