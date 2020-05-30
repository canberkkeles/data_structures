#include "BinarySearchTree.h"
#include "HashTable.h"
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>

void toLower(std::string & word){
	for(unsigned int i = 0 ; i < word.size() ; i++){
		char curr = word[i];
		if(curr >= 'A' && curr <= 'Z'){
			curr += 32;
		}
	}
}

int main(){

	std::fstream inFile("dict.txt");
	if(!inFile.is_open()){
		std::cout << "ERROR OPENING THE FILE!\n";
		return 0;
	}

	std::string notFound = "Cengiz";

	BinaryWordTree<std::string> tree(notFound);
	WordTable<std::string> ht(notFound);


	std::cout << "Building a binary tree for dict.txt...\n";
	std::string dictLines;
	while(std::getline(inFile,dictLines)){
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
		tree.insert(word,helper.substr(0,helper.size() - 1)); //TO REMOVE THE LAST SPACE FROM STRING

	}
	inFile.close();

	std::fstream inFileHT("dict.txt");
	if(!inFileHT.is_open()){
		std::cout << "ERROR OPENING THE FILE!\n";
		return 0;
	}

	std::cout << "Building a hash table for dict.txt...\n";
	std::string htDictLines;
	while(std::getline(inFileHT,htDictLines)){
		bool hasMeaning = false;
		std::istringstream parsingObject(htDictLines);
		std::string word;
		parsingObject >> word;

		std::string meaning,helper = "";

		while(parsingObject >> meaning){
			helper = helper + meaning + " ";
			hasMeaning = true;
		}
		if(hasMeaning)
			toLower(word);
		ht.insert(word,helper.substr(0,helper.size() - 1)); //TO REMOVE THE LAST SPACE FROM STRING

	}
	inFileHT.close();
	//INFO MESSAGE
	std::cout << "After preprocessing, the unique word count is " << ht.getWordCount() << ". Current load ratio is "
		<< ht.getLoadFactor() << std::endl;
	std::cout << "Running queries in query1.txt\n\n";
	std::ifstream q("query1.txt");

	if(!q.is_open()){
		std::cout << "ERROR OPENING THE FILE!\n";
		return 0;
	}

	std::string query;
	std::vector<std::string> words;
	std::vector<int> hashValues; //TO HOLD THE HASH INDEXES FOR THE WORDS, TO SAVE SOME TIME

	while(std::getline(q,query)){ // FILLING THE WORDS ARRAY AND HASH VECTOR
		std::istringstream pars(query);
		std::string word;
		pars >> word;
		toLower(word);
		words.push_back(word);
		hashValues.push_back(ht.hash(word));
	}
	q.close();

	std::string translation;
	std::ofstream outHT("ht_result.txt");
	std::ofstream outBST("bst_result.txt");


	//Sleep(200); // PLEASE DONT SEE THIS
	//BST PART
	long long totalTimeBST = 0;
	for(unsigned int i = 0 ; i < words.size() ; i++){
		auto startbst = std::chrono::high_resolution_clock::now();
		translation = tree.translate(words[i]);
		auto timebst = (std::chrono::high_resolution_clock::now() - startbst).count();
		totalTimeBST += timebst;
		outBST << words[i] << "\t" << translation << "\n";
	}



	//HT PART
	long long totalTimeHT = 0;
	for(unsigned int i = 0; i < words.size(); i++){
		auto startht = std::chrono::high_resolution_clock::now();
		translation = ht.translate(words[i],hashValues[i]);
		auto timeht = (std::chrono::high_resolution_clock::now() - startht).count();
		totalTimeHT += timeht;
		outHT << words[i] << "\t" << translation << "\n";
	}


	std::cout << "***********************************************\n";
	std::cout << "Benchmark results for Binary Search Tree (BST):\n";
	std::cout << "***********************************************\n";
	std::cout << "+ Elapsed time: " << totalTimeBST << " ns\n";
	std::cout << "+ Average query time: " << totalTimeBST / words.size() << " ns\n\n";

	std::cout << "***********************************************\n";
	std::cout << "Benchmark results for Hash Table:\n";
	std::cout << "***********************************************\n";
	std::cout << "+ Elapsed time: " << totalTimeHT << " ns\n";
	std::cout << "+ Average query time: " << totalTimeHT / words.size() << " ns\n";
	if(totalTimeHT != 0)
		std::cout << "+ Speed up: " << (totalTimeBST) / (totalTimeHT) << "x\n\n";
	else
		std::cout << "+ Speed up: " << (totalTimeBST) / (totalTimeHT+1) << "x\n\n";

	std::cout << "Time measurements in ns(N,4096N):\n";
	std::cout << "*****************************\n";
	std::cout << "bst\n";
	std::cout << "N\ttime\n";

	// RUNNING THE SAME QUERY 1,2,... TIMES RIGHT?
	// BST PART

	unsigned int i = 1;
	while(i <= 4096){
		long long totalQueryBST = 0;

		//Sleep(200); // PLEASE DONT SEE THIS!!
		for(unsigned int j = 0 ; j < i ; j++){
			for(unsigned int idx = 0 ; idx < words.size() ; idx++){
				auto start = std::chrono::high_resolution_clock::now();
				tree.translate(words[idx]);
				auto time = (std::chrono::high_resolution_clock::now() - start).count();
				totalQueryBST += time;
			}
		}

		std::cout << i << "\t" << totalQueryBST << std::endl;
		i*=2;
	}


	std::cout << std::endl;
	std::cout << "ht" << std::endl;
	std::cout << "N\ttime" << std::endl;
	// HT PART
	unsigned int ji = 1;
	while(ji <= 4096){

		long long queryHT = 0;
		for(unsigned int j = 0 ; j < ji ; j++){
			for(unsigned int idx = 0 ; idx < words.size() ; idx++){

				std:: string word = words[idx];
				int hash = hashValues[idx];

				auto start = std::chrono::high_resolution_clock::now();
				ht.translate(word,hash);
				auto time = (std::chrono::high_resolution_clock::now() - start).count();

				queryHT += time;
			}
		}

		std::cout << ji << "\t" << queryHT << std::endl;
		ji*=2;
	}


	return 0;
}