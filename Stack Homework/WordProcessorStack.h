#ifndef WORDPROCESSORSTACK_H
#define WORDPROCESSORSTACK_H
#include <iostream>
#include <exception>
//MY EXCEPTION CLAS :)
class Underflow : public std::exception{
public:
	const char * what(){return "You can not move cursor or delete element since you are at the begining/end!";}
};

template <class Object>
struct ListNode{
	Object element; //DATA TO BE STORED
	ListNode* next; //A POINTER TO THE NEXT ELEMENT OF STACK

	ListNode(const Object & givenElement, ListNode* givenNext = nullptr): //CONSTRUCTOR
		element(givenElement),next(givenNext){}
};

template <class Object>
class WordProcessorStack{
public:

	WordProcessorStack(); //DEFAULT CONSTRUCTOR
	WordProcessorStack(const WordProcessorStack & rhs); //COPY CONSTRUCTOR
	~WordProcessorStack(); //DESTRUCTOR

	bool isEmpty() const; //CHECKS IF THE STACK IS EMPTY, A HELPER FUNCTION
	void makeEmpty();     //MAKES THE STACK EMPTY, A HELPER FUNCTION

	Object pop(); //POPS THE ELEMENT ON TOP OF STACK, AND REMOVES THAT ELEMENT FROM THE STACK
	void push(const Object & newItem); //PUSHES THE GIVEN ELEMENT TO CURRENT POSITION OF THE CURSOR
	const Object & topElement() const; // GETS THE TOP ELEMENT WITHOUT REMOVING
	void printStack() const; // PRINTS THE CONTENTS OF THE STACK
	void reverseStack(); // REVERSES THE STACK
	void deleteFromStack(const Object & elementToBeDeleted); //DELETES FROM STACK, WILL NOT BE USED

	const WordProcessorStack & operator=(const WordProcessorStack & rhs); //ASSIGNMENT OPERATOR OVERLOAD


private:

	ListNode<Object>* top; //TOP OF STACK
};


#include "WordProcessorStack.cpp"
#endif