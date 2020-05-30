//CANBERK KELES
//25393

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "BinarySearchTree.h"
/*
PRE: TAKES STRING A WORD AS A PARAMETER
POST: WORD BECOMES ALL LOWERCASE SINCE PROGRAM IS NOT CASE SENSITIVE
*/
void toLower(std::string & word){
	for(int i = 0 ; i < word.size() ; i++){
		char curr = word[i];
		if(curr >= 'A' && curr <= 'Z'){
			curr += 32;
		}
	}
}

int main(){
	std::string notFound = "Cengiz"; //NOT FOUND ITEM ^^
	BinaryWordTree<std::string> dictionary(notFound);
	std::ifstream dictFile("dictUpdatedEN.txt");

	if(!dictFile.is_open()){
		std::cout << "Invalid file, please open dictUpdatedEN.txt";
		return 0;
	}

	std::string dictLines;
	//FILLING UP THE DICTIONARY
	while(std::getline(dictFile,dictLines)){

		bool hasMeaning = false;
		std::istringstream parsingObject(dictLines);
		std::string word;
		parsingObject >> word;

		std::string meaning,helper = "";

		while(parsingObject >> meaning){
			helper = helper + meaning + " ";
			hasMeaning = true;
		}
		if(hasMeaning)
			toLower(word);
		dictionary.insert(word,helper.substr(0,helper.size() - 1)); //TO REMOVE THE LAST SPACE FROM STRING

	}

	std::string message = "***Help***\nQuery: 1\nAdd new translation: 2\nAdd new word: 3\nExit: 0\n";
	std::cout << message;
	std::string command;
	do{
		std::cout <<"Enter command: ";
		std::cin >> command;

		if(command == "0"){
			std::cout << "Bye..." << std::endl;
		}

		else if(command == "1"){ //QUERY COMMAND
			std::string qWord;
			std::cout << "Enter queried word: ";
			std::cin >> qWord;
			toLower(qWord); 
			std::string translation = dictionary.translate(qWord); //SEARCH IN DICTIONARY
			if(translation != "Cengiz") //IF FOUND
				std::cout << qWord << " ---> " << translation << std::endl;
			else
				std::cout << "No such word!" << std::endl;

		}

		else if(command == "2"){
			std::string editWord,newTranslation;

			std::cout << "Which word do you want to edit: ";
			std::cin >> editWord;
			toLower(editWord);
			std::string translation = dictionary.translate(editWord);
			if(translation != "Cengiz"){
				std::cout << "Enter new translation: ";
				std::cin >> newTranslation;

				if(dictionary.addTranslation(editWord,newTranslation,dictionary.getRoot()))
					std::cout << "***UPDATED***" << std::endl;
			}
			else
				std::cout << "No such word!" << std::endl;
		}

		else if(command == "3"){

			std::string newWord;
			std::cout << "Enter new word: ";
			std::cin >> newWord;
			toLower(newWord);
			std::string translation = dictionary.translate(newWord);

			if(translation != "Cengiz"){ //IF THERE IS SUCH WORD
				std::cout << "Word already exists, if you want to add new translation please use command 2."<<std::endl;
			}
			else{
				std::string newTrans;
				std::cout << "Enter translations: ";
				std::cin >> newTrans;

				dictionary.insert(newWord,newTrans); //IF THERE IS NOT SUCH WORD
			}
		}

	}while(command != "0");




	return 0;
}