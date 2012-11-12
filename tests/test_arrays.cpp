
#include <mpi.h>

#include "futures_enviroment.hpp"
#include "future.hpp"
#include "promise.hpp"

#include <iostream>
#include <vector>

#define MASTER 0
#define MAX_FUTURES 1 //works for more
#define NUMBER_OF_FUTURES 100
#define SIZE_X 1000
#define SIZE_Y 100

using namespace std;
using namespace futures;

int main(int argc, char* argv[]) {
	Futures_Enviroment* env = Futures_Enviroment::Initialize(argc, argv, "MPI");
	int id = env->get_procId();
	
	double A[SIZE_X];

	for(int i=0; i < SIZE_X; i++) {
		A[i] = i;
	}	

	vector<Promise<double*>* > promises(NUMBER_OF_FUTURES);
	vector<Future<double*>* > answers(NUMBER_OF_FUTURES);

	for(int i=0; i < NUMBER_OF_FUTURES; i++) {
		promises[i] = new Promise<double*>(1, 0, SIZE_X, sizeof(double));
		answers[i] = promises[i]->get_future();
	}	

	if(id == MASTER) {
		cout << "Master waits for answer" << endl;
		for(int i=0; i < NUMBER_OF_FUTURES; i++) {
			double *B = answers[i]->get(MPI_DOUBLE);
			/*
			for(int j = 0; j < SIZE_X; j++) {
				cout << "B[" << j << "]=" << B[j] << endl;
			}
			*/
			for(int i=0; i < SIZE_X; i++) {
				if(A[i] != B[i]) cout << "Test Failed" << endl;
				else if(i == SIZE_X-1) cout << "Test Passed" << endl;
			}
		}
	}
	else {
		cout << "Worker computes answer" << endl;

		for(int i=0; i < NUMBER_OF_FUTURES; i++) {
    	promises[i]->set_value(&(A[0]), MPI_DOUBLE);
		}
	}

	for(int i=0; i < NUMBER_OF_FUTURES; i++) {
		delete promises[i];
		delete answers[i];
	}
	delete env;
}
