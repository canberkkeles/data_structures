#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <vector>
#include <string>
#include <iostream>

template<class Object>
struct HashNode{
	Object key;
	Object translation;
	HashNode * next;

	HashNode(const Object & theKey = Object (), const Object & theTrans = Object (), HashNode* n = nullptr) : key(theKey), 
		translation(theTrans),next(n){ }
};

template<class Object>
class WordTable{
public:
	WordTable(const Object & nFound,int size = 52);
	~WordTable();

	int getWordCount(){return wordCount;}
	double getLoadFactor(){return (double)wordCount / (double)table.size();}

	void insert(const Object & key,const Object & translation);
	const Object  translate(const Object & key,int idx) const;
	unsigned int hash(const std::string & key) const;

private:

	unsigned int wordCount;
	std::vector<HashNode<Object>> table;
	const Object & ITEM_NOT_FOUND;


	void addToEntry(HashNode<Object> * head,const Object & key, const Object & translation);

	void rehash();
	//const Object  find(HashNode<Object> * head, const Object & key) const;

};








#include "HashTable.cpp"
#endif