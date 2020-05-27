#ifndef __INSTANCE_CPP
#define __INSTANCE_CPP

#include <iostream> 
#include <vector>
#include <cstdlib>
#include <string>

using namespace std;

class Instance{

	public:
		vector<double> inst;
		int id;


		Instance(){
			id = 0;
		}

		Instance(vector<double> v ){
			inst = v;
			id = inst.at(0);
		}

		void print(){
			for(int i = 0; i < inst.size(); i++){
				cout << inst.at(i) << " ";
			}
			cout << endl;
		}

};

#endif
			

