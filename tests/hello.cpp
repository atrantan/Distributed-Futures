
#include "futures.hpp"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#define MASTER 0

using namespace std;
using namespace futures;

class helloWorld {
public:
	helloWorld() {};
	~helloWorld() {};
	int operator()() { 
		int id = Futures_Id();
		cout << "- Worker" << id << ":Hello Master" << endl;
		return id;
	};
};

int helloWorld_func() { 
	int id = Futures_Id();
	cout << "- Worker" << id << ":Hello Master" << endl;
	return id;
};

FUTURES_EXPORT_FUNCTOR((async_function<helloWorld>));

int main(int argc, char* argv[]) {
	Futures_Initialize(argc, argv);
	helloWorld f;
	boost::function<void()> foo;
	foo = boost::bind(helloWorld_func);
	foo();
	future<int> message = async(f);

	cout << "- Master :Hello " << message.get() << endl;

	Futures_Finalize();
	cout << "done!!";
};

