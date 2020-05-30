#include <iostream>
#include "Heap.h"
#include <fstream>
#include <string>
#include <sstream>
#include <queue>


int main(){

	std::string fileName;
	std::cout << "Please enter a filename: ";
	std::cin >> fileName;

	std::ifstream inFile(fileName);
	if(!inFile.is_open()){
		std::cout << "ERROR OPENING THE FILE!\n";
		return 0;
	}

	int painterCount;
	inFile >> painterCount;

	int jobCount;
	inFile >> jobCount;

	std::queue<Job> jobs;
	std::string line;

	while(std::getline(inFile,line)){

		if(line != ""){
			std::istringstream data(line);
			int jobid, deadline;

			data >> jobid >> deadline;

			Job j(jobid,deadline);
			jobs.push(j);
		}

	}

	WorkerHeap<Worker> workers;
	int day = 0;
	int jobsAssigned = 0;

	std::ofstream outFile(fileName + ".out");

	for(int wid = 1 ; !jobs.empty() && wid <= painterCount ; wid++){

		Job currJob = jobs.front();
		Worker w(wid,currJob);

		outFile << "Job-" << currJob.id << "->Worker-" << wid << " (Day: " << day << ")\n" ;

		workers.insert(w);
		jobs.pop();
		jobsAssigned++;

	}


	Worker w;
	while(jobsAssigned < jobCount){

		workers.deleteMin(w); //GET THE MINIMUM DEADLINE WORKER
		Job newJob = jobs.front();
		jobs.pop();

		int daysPassed = w.assigned->deadline;
		day += daysPassed;
		workers.decreaseElements(daysPassed);

		Worker x(w.id,newJob); //ASSIGN A NEW JOB TO THAT WORKER
		workers.insert(x);
		outFile << "Job-" << newJob.id << "->Worker-" << w.id << " (Day: " << day << ")\n" ;
		jobsAssigned++;


	}

	while(!workers.isEmpty()){ // ONLY CURRENT JOBS ARE LEFT

		workers.deleteMin(w); //GET THE MINIMUM DEADLINE WORKER


		int daysPassed = w.assigned->deadline;
		day += daysPassed;
		workers.decreaseElements(daysPassed);

	}

	outFile << "All jobs are completed in " << day <<" days.";



	return 0;
}