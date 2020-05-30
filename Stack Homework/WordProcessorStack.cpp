#include "WordProcessorStack.h"
#include <iostream>

/*
DEFAULT CONSTRUCTOR, CONSTRUCTS AN EMPTY STACK OBJECT
****************GIVEN NO PARAMETERS.****************
*/
template <class Object>
WordProcessorStack<Object>::WordProcessorStack(){
	top = nullptr; // INITIALY, THE STACK IS EMPTY AND TOP POINTER IS NULL
}
/*
COPY CONSTRUCTOR, CONSTRUCTS A STACK WITH GIVEN STACK PARAMETER
*/
template<class Object>
WordProcessorStack<Object>::WordProcessorStack(const WordProcessorStack & rhs){
	top = nullptr;
	*this = rhs;
}
/*
DESTRUCTOR
*/
template<class Object>
WordProcessorStack<Object>::~WordProcessorStack(){
	makeEmpty();
}
/*
CHECK IF THE STACK IS EMPTY OR NOT BY LOOKING AT THE TOP POINTER
*/
template<class Object>
bool WordProcessorStack<Object>::isEmpty() const{
	return top == nullptr;
}
/*
MAKE THE STACK EMPTY
*/
template<class Object>
void WordProcessorStack<Object>::makeEmpty(){
	while (!isEmpty())
	{
		pop(); // POP UNTILL THE STACK IS EMPTY
	}
}
/*
POP THE ELEMENT ON TOP OF THE STACK
*/
template<class Object>
Object WordProcessorStack<Object>::pop(){
	if(isEmpty()) throw Underflow(); // THROWS AN EXCEPTION IF STACK IS EMPTY IE THERE IS NOTHING TO POP

	ListNode<Object>* oldTop = top; // TO DELETE THE NODE AFTER POPPING THE ELEMENT
	Object topItem = oldTop->element; // GETTING THE ELEMENT AT THE TOP
	top = top -> next; // MOVING THE TOP
	delete oldTop; // DELETING THE POPPED ELEMENT FROM THE STACK
	return topItem;
}
/*
PUSH THE ELEMENT TO TOP OF THE STACK
*/
template <class Object>
void WordProcessorStack<Object>::push(const Object & newItem){
	top = new ListNode<Object>(newItem,top); // MAKE A NEW NODE WHOSE NEXT POINTS TO THE TOP, AND MAKE THAT NODE TOP
}
/*
GET THE TOP ELEMENT WITHOUT DELETING THE ELEMENT
*/
template<class Object>
const Object & WordProcessorStack<Object>::topElement() const{
	return top -> element;
}
/*
PRINT THE STACK
*/
template<class Object>
void WordProcessorStack<Object>::printStack() const{
	ListNode<Object>* iterator = top;
	while(iterator){
		const Object curr = iterator -> element;
		std::cout << curr; // PRINT UNTILL THE STACK IS EMPTY
		iterator = iterator -> next;
	}
	std::cout << std::endl;
}
/*
REVERSE THE STACK
*/
template<class Object>
void WordProcessorStack<Object>::reverseStack(){
	WordProcessorStack helper; // CREATING A HELPER STACK

	while(!isEmpty()){ // WHILE THIS STACK IS NOT EMPTY,
		helper.push(pop()); // POP FROM THIS STACK AND PUSH TO HELPER, HELPER IS NOW REVERSED VERSION OF THIS STACK
	}

	*this = helper; // ASSIGN HELPER TO THIS, OPERATOR ALREADY OVERLOADED.
}
/*
DELETE ALL THE ELEMENTS FROM STACK 
WHICH HAS THE SAME DATA WITH GIVEN PARAMETER
**************THIS FUNCTION WONT BE USED ********************
*/
template<class Object>
void WordProcessorStack<Object>::deleteFromStack(const Object & elementToBeDeleted){
	ListNode<Object> * curr = top; // POINTER TO CURRENT ELEMENT, FIRST ASSIGNED TO TOP
	ListNode<Object> * prev = nullptr; // POINTER TO PREVIOUS ELEMENT, FIRST ASSIGNED TO NULL
	while(curr){ // WHILE THERE IS AN ELEMENT TO POINT

		Object currentElement = curr -> element; // CURRENT ELEMENT
		if(currentElement == elementToBeDeleted){ // IF FOUND ELEMENT TO BE DELETED
			if(!prev){ // IF THERE IS NO PREVIOUS, IT MEANS WE ARE DELETING FROM THE TOP
				top = curr -> next;
				delete curr;
				curr = top;
			}
			else{ // IF THERE IS PREVIOUS, WE ARE NOT DELETING FROM THE TOP
				prev -> next = curr -> next;
				delete curr;
				curr = prev -> next;
			}

		}
		else{ // IF NOTHING IS DELETED, ADVANCE THE POINTERS NORMALLY

			prev = curr;
			curr = curr -> next;

		}

	}
}
/*
ASSIGNMENT OPERATOR OVERLOADING
*/
template <class Object>
const WordProcessorStack<Object> & WordProcessorStack<Object>::operator=(const WordProcessorStack & rhs){
	if(this != &rhs){ // CHECK FOR SELF ASSIGNMENT
		makeEmpty(); // CLEAR THE STACK
		if(rhs.isEmpty()){ // IF THE STACK TO BE COPIED IS EMPTY, THEN RETURN *THIS WHICH IS EMPTY STACK
			return *this;
		}
		ListNode<Object>* iteratorForRhs = rhs.top;
		ListNode<Object>* iteratorForThis = new ListNode<Object>(iteratorForRhs->element);
		top = iteratorForThis;
		for(iteratorForRhs = iteratorForRhs -> next ; iteratorForRhs != nullptr ; iteratorForRhs = iteratorForRhs->next){
			iteratorForThis = iteratorForThis -> next = new ListNode<Object>(iteratorForRhs->element);
			//MAKE ITERATOR'S NEXT THE SAME WITH RHS'S ELEMENT AND MAKE ITERATOR POINT TO ITERATOR'S NEXT
		}
	}
	return *this;
}