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
		vector<double> features;
		int id;


		Instance(){
			id = 0;
		}

		Instance(vector<double> v ){
			inst = v;
			id = inst.at(0);
			for(int i = 1; i < inst.size(); i++){
				features.push_back(inst.at(i));
			}
		}

		void print(){
			cout << id << " ";
			for(int i = 0; i < features.size(); i++){
				cout << features.at(i) << " ";
			}
			cout << endl;
		}

};

#endif
			


