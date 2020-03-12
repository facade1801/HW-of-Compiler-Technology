#include "error.h"
#include "stdlib.h"
void error(int errcode) {
	switch (errcode) {
		case 0:
			cout << "normal terminate code 0" << endl;
			exit(0);
		case 1:
			cout << "Unknown type error 1" << endl;
			terminate();
//			exit(1);
		case 3:
			cout << "wrong type of sentence" << endl;
			terminate();
//			exit(3);

		default:
			cout << "Unknown default type error" << endl;
//			exit(2);
	}
}

//exit(0);//normal
//exit(1);//abnormal
