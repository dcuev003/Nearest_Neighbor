#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include "instance.cpp"
#include <algorithm>
#include <float.h>
using namespace std;

vector<Instance> normalize(vector<Instance> temp){
	double mean = 0.0;
	double sum = 0.0;
	double stdDev = 0.0;
	double var = 0.0;
	double sz = static_cast<double>(temp.size());
	
	vector<Instance> ret = temp;
	for(int i = 0; i < temp.at(0).features.size(); i++){
		for(int j = 0; j < temp.size(); j++){
			sum += temp.at(j).features.at(i); 	
		}
		//cout << endl << "sum: " << sum << endl;
		mean = sum/sz;
		//cout << "mean: " << mean << endl;
		for(int k = 0; k < temp.size(); k++){
			var += pow(temp.at(k).features.at(i) - mean, 2);
		}
		var = var/sz;
		stdDev = sqrt(var);
		//cout <<  "stdDev: " << stdDev << endl;
		for(int f = 0; f < temp.size(); f++){
			ret.at(f).features.at(i) = ((ret.at(f).features.at(i) - mean)/stdDev);
		}
		mean = 0.0;
		sum = 0.0;
		stdDev = 0.0;
		var = 0.0;
	}

	return ret;   
	
}

int nearestNeighbor(vector<Instance> t, vector<double> featureSet, vector<int> fnumber){
		
	double min = DBL_MAX;
	double dist = 0;
	
	for(int i = 0; i < featureSet.size(); i++){
		
	
	}

	return 0;
}

int main(){
	
	cout << "Welcome to Daniel Cueva's Feature Selection Algorithm." << endl;
	cout << "Type in the name of the file to test: ";

	double val;
	vector <double> data;
	vector <Instance> train;

	string fname; //variable for file name
	int choice;
	cin >> fname;

	cout << fname << endl << endl;

	ifstream dat;

	dat.open(fname.c_str());
	
	string line;
	Instance *temp;
	
	while(getline(dat, line)){
		stringstream ss(line);
		
		while(ss >> val){
			data.push_back(val);
		}
		temp = new Instance(data);
		ss.clear();
		data.clear();
		train.push_back(*temp);
		delete temp;
	}
			
	dat.close();
	
	cout << "This dataset has " << train.at(0).features.size() << " features, with " << train.size() << " instances." << endl;
	cout << endl;

	cout << "Please wait while I normalize the data.. ";

	train = normalize(train);

	cout << "Done!" << endl << endl;

	for(int i = 0; i < train.size(); i++){
		train.at(i).print();
	}

	cout << endl;
	cout << "Type the number of the algorithm you want to run." << endl;
	cout << "1) Forward selection" << endl << "2) Backward Elimination" << endl << endl;


	cin >> choice;
	cout << "Running nearest neighbor with x features, using leaving-one-out evaluation";
	cout << endl;
	
	


	return 1;
}
