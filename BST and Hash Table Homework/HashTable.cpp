#include "HashTable.h"
/*
A FUNCTION TO CHECK IF GIVEN PARAMETER IS PRIME NUMBER OR NOT
*/
bool isPrime(int n){
	if(n == 2 ||n == 3) return true;
	if(n == 1 ||n % 2 == 0) return false;

	for(int i = 3; i * i <= n; i+=2){
		if(n % i == 0) return false;
	}

	return true;
}
/*
RETURNS THE NEXT PRIME BIGGER THAN PARAMETER N
*/
int nextPrime(int n){
	if(n % 2 == 0) n++;
	for(; !isPrime(n); n+=2)
		;
	return n;
}

/*
CONSTRUCTOR
*/
template<class Object>
WordTable<Object>::WordTable(const Object & nFound,int size = 52):ITEM_NOT_FOUND(nFound),table(nextPrime(size)){
	wordCount = 0;
}

/*
DESTRUCTOR
*/
template<class Object>
WordTable<Object>::~WordTable(){
	table.clear();
	wordCount = 0;
}

/*
HASH FUNCTION
*/
template <class Object>
unsigned int WordTable<Object>::hash(const std::string & key) const {
	unsigned int hashVal = 0;
	for (unsigned int x = 0; x < key.length(); ++x)
	{
		hashVal ^= (hashVal << 5) +
			(hashVal >> 2) +
			key[x];
	}
	return hashVal % table.size();
}

/*
INSERTS THE GIVEN KEY AND TRANSLATION COMBINATION INTO HASHTABLE
*/
template <class Object>
void WordTable<Object>::insert(const Object & key, const Object & translation){
	addToEntry(&table[hash(key)],key,translation);
	if(wordCount > table.size() / 5) rehash();
}

/*
INNER FUNCTION TO ADD A NEW ELEMENT OR UPDATE EXISTING TRANSLATION INTO GIVEN ENTRY
*/
template <class Object>
void WordTable<Object>::addToEntry(HashNode<Object> * head,const Object & key, const Object & translation){
	if(head -> key == ""){
		head -> key = key;
		head -> translation = translation;
		head -> next = nullptr;
		wordCount++;
		return;
	}
	HashNode<Object> * iter = head;
	while(iter -> next){
		if(iter -> key == key){ //IF THE WORD ALREADY EXISTS
			iter -> translation = iter -> translation + ", " + translation;
			return;
		}
		iter = iter -> next;
	}
	wordCount++;
	iter -> next = new HashNode<Object>(key,translation,nullptr);
}

/*
REHASH FUNCTION
*/
template<class Object>
void WordTable<Object>::rehash(){

	int newSize = nextPrime(2 * table.size());
	int oldSize = table.size();
	int oldWord = wordCount;

	std::vector<HashNode<Object>> oldTable = table;
	table.clear();
	table.resize(newSize);


	wordCount = 0;
	for(int i = 0 ; i < oldSize ; i++){
		if(oldTable[i].key != ""){
			HashNode<Object> * iter = &oldTable[i];
			while(iter){
				insert(iter->key,iter->translation);
				iter = iter -> next;
			}
		}
	}


	std::cout << "rehashed...\n";
	std::cout << "previous table size: " << oldSize << ", new table size: " << newSize << ", current unique word count: " 
		<< wordCount << ", current load factor: " << (double)wordCount / (double)newSize   << std::endl;
}

//template<class Object>
//const Object WordTable<Object>::find(HashNode<Object> * head, const Object & key) const{
//	if(head ->key == key) 
//		return head -> translation;
//	HashNode<Object> * itr = head;
//	while(itr -> key != key){
//		itr = itr -> next;
//	}
//	return itr -> translation;
//}
template<class Object>
const Object WordTable<Object>::translate(const Object & key,int idx) const{

	if(table[idx].key == key) return table[idx].translation;
	HashNode<Object> theList = table[idx];


	HashNode<Object> * iter = &theList;
	while(iter -> key != key) iter = iter -> next;
	return iter -> translation;

}