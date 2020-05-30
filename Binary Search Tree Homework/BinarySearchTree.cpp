#include "BinarySearchTree.h"
#include <iostream>
/*
CONSTRUCT THE TREE
*/
template<class Object>
BinaryWordTree<Object>::BinaryWordTree(const Object & notFound):ITEM_NOT_FOUND(notFound),root(nullptr){}

/*
INTERNAL METHOD
RETURN TRANSLATION IF FOUND,
ELSE RETURN NOT_FOUND ITEM
*/
template<class Object>
const Object & BinaryWordTree<Object>::elementAt(treeNode<Object> * t) const{
	return t == nullptr ? ITEM_NOT_FOUND : t->translation;
}

/*
RETURN THE TRANSLATION OF GIVEN WORD
*/
template<class Object>
const Object & BinaryWordTree<Object>::translate(const Object & word) const{
	return elementAt(find(word,root));
}

/*
INTERNAL METHOD
FIND THE WORD
*/
template<class Object>
treeNode<Object> * BinaryWordTree<Object>::find(const Object & word,treeNode<Object> * t) const{
	if(t == nullptr)return nullptr;
	else if(word < t->word) return find(word,t->leftChild);
	else if(word > t->word) return find(word,t->rightChild);
	else return t;
}

/*
INSERT THE WORD AND ITS TRANSLATION INTO THE TREE
*/
template<class Object>
void BinaryWordTree<Object>::insert(const Object & word, const Object & translation){
	insert(word,translation,root);
}
/*
INSERTS THE WORD AND TRANSLATION, HELPER METHOD
*/
template <class Object>
void BinaryWordTree<Object>::insert(const Object & word, const Object & translation, treeNode<Object> * & t){
	if(t == nullptr) t = new treeNode<Object>(nullptr,nullptr,word,translation);
	else if(word < t->word) insert(word,translation,t->leftChild);
	else if(word > t->word) insert(word,translation,t->rightChild);
	else addTranslation(word,translation,t);
}

/*
ADDS TRANSLATION
*/
template <class Object>
bool BinaryWordTree<Object>::addTranslation(const Object & word,const Object & translation,treeNode<Object> * t){ 
	treeNode<Object> * wordNode = find(word,root);
	if(wordNode != nullptr){
		wordNode->translation = wordNode -> translation + ", " + translation;
		return true;
	}
	return false;
}
/*
HELPER FOR DESTRUCTOR
*/
template <class Object>
void BinaryWordTree<Object>::makeEmpty(){
	makeEmpty(root);
}

/*
HELPER FOR DESTRUCTOR
*/
template<class Object>
void BinaryWordTree<Object>::makeEmpty(treeNode<Object>* & t) const{
	if(t != nullptr){
		makeEmpty(t->leftChild);
		makeEmpty(t->rightChild);
		delete t;
	}
	t = nullptr;
}

/*
JUST FOR MY DEBUG PURPOSES
*/
template<class Object>
void BinaryWordTree<Object>::printTree() const{
	if(root != nullptr){
		printTree(root);
	}
}
/*
DESTRUCTOR
*/
template<class Object>
BinaryWordTree<Object>::~BinaryWordTree(){
	makeEmpty();
}

/*
JUST FOR MY DEBUG PURPOSES
*/
template <class Object>
void BinaryWordTree<Object>::printTree(treeNode<Object> * t) const{
	if(t != nullptr){
		printTree(t->leftChild);
		std::cout << t -> word << std::endl;
		printTree(t->rightChild);
	}
}
