//CANBERK KELES
//25393
#include <iostream>
#include "WordProcessorStack.h"
#include <string>

int main(){


	std::string input;
	std::cin >> input;
	WordProcessorStack<char> inputStack,cursorStack; // CURSOR STACK WILL BE USED FOR CURSOR OPERATIONS.
	bool isValid = false;
	int sizeOfInput = input.size();

	for(int index = 0; index < sizeOfInput ; index++){

		char curr = input[index];

		if(curr == '1'){ // END OF INPUT COMMAND
			isValid = true; // MAKES THE INPUT VALID
			while(!cursorStack.isEmpty()){ // PUSH ALL REMAINING ELEMENTS AT THE RIGHT SIDE OF THE CURSOR
				inputStack.push(cursorStack.pop());
			}

			inputStack.reverseStack(); // REVERSE THE STACK TO PRING OUTPUT STRING

			inputStack.printStack();
			return 0;

		}
		else if(curr == '2'){ // DELETE COMMAND
			try{
				inputStack.pop();
			}
			catch(Underflow & u){
				continue;
				/*std::cout << u.what() << std::endl;
				std::cout << "Invalid input, program will terminate" << std::endl;;
				return 0;*/
			}

		}
		else if(curr == '3'){ // MOVE CURSOR TO THE LEFT
			try{
				cursorStack.push(inputStack.pop()); // POP THE LAST ELEMENT AND STORE IT INSIDE THE CURSOR STACK
			}
			catch(Underflow & u){
				continue;
				//std::cout << u.what() << std::endl;
				//std::cout << "Invalid input, program will terminate" << std::endl;;
				//return 0;
			}

		}
		else if(curr == '4'){ // MOVE CURSOR RIGHT
			try{
				inputStack.push(cursorStack.pop()); // PUSH THE ELEMENT FROM CURSOR STACK TO INPUT STACK
			}
			catch(Underflow & u){
				continue;
				//std::cout << u.what() << std::endl;
				//std::cout << "Invalid input, program will terminate" << std::endl;;
				//return 0;
			}

		}

		else if(curr == '5'){ // REVERSE COMMAND
			if(!inputStack.isEmpty())
				inputStack.reverseStack();

		}

		else if(curr == '6'){ // DELETE COMMAND
			WordProcessorStack<char> helper;
			try{
				char toBeDeleted = input[index+1]; // CHAR AFTER 6 IS TO BE DELETED 
				if(toBeDeleted != '1' && toBeDeleted != '2' && toBeDeleted != '3' && toBeDeleted != '4' && toBeDeleted != '5' && toBeDeleted != '6'){
					while(!inputStack.isEmpty()){ // POP OUT EVERY ELEMENT IN INPUT STACK
						char element = inputStack.pop();
						if(element != toBeDeleted){ // CHECK IF ELEMENT IS TO BE DELETED
							helper.push(element);
						}
					}
					//inputStack.deleteFromStack(toBeDeleted);
					helper.reverseStack(); // REVERSING THE STACK BECAUSE OF THE WAY THE STACKS WORK
					inputStack = helper; // ASSIGNMENT OPERATOR OVERLOAD
					index++; // SINCE WE DO NOT NEED THE CHAR AFTER NUMBR 6, INCREMENT THE INDEX
				}
				else if(toBeDeleted = '1'){ 
					isValid = true; // MAKES THE INPUT VALID
					while(!cursorStack.isEmpty()){ // PUSH ALL REMAINING ELEMENTS AT THE RIGHT SIDE OF THE CURSOR
						inputStack.push(cursorStack.pop());
					}

					inputStack.reverseStack(); // REVERSE THE STACK TO PRING OUTPUT STRING

					inputStack.printStack();
					return 0;
				}
				// IF A NUMBER ENTERED AFTER CHARACTER 6, THAT CHARACTER IS IGNORED AND LOOP CONTINUES
			}
			catch(...){
				continue;
			}



		}
		else{ //IF CURRENT CHAR IS NOT A WORD PROCESSING COMMAND, ADD IT TO INPUT STACK

			inputStack.push(curr);

		}

	}
	if(!isValid){
		//IT IS GOOD TO BE CAUTIOUS I GUESS :) CHECKS FOR VALIDITY OF THE INPUT
		std::cout << "Your input should end with character 1, Invalid input!" << std::endl;
	}
	return 0;
}