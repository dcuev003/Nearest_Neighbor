#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <iomanip>
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

int nearestNeighbor(int out, vector<double> featureSet, vector<Instance> train, vector<int> fnum){
		
	double min = DBL_MAX;
	double dist = 0.0;
	int id;
	
	for(int i = 0; i < train.size(); i++){
		if(i != out){
			for(int j = 0; j < featureSet.size(); j++){
				dist += pow((train.at(i).features.at(fnum.at(j)) - featureSet.at(j)),2); 
			}
			if(dist < min){
				min = dist;
				id = train.at(i).id;
			}
		}
		dist = 0.0;
			
	}
	return id;
}

double leaveOneOut(vector<Instance> train, vector<int> fnumber){
	vector<double> temp; //variable to hold current features
	double correct = 0.0;
	double sz = static_cast<double>(train.size());
	double accuracy;
	
	for(int i = 0; i < train.size(); i++){
		for(int j = 0; j < fnumber.size(); j++){
			temp.push_back(train.at(i).features.at(fnumber.at(j)));
		}
		if(nearestNeighbor(i, temp, train, fnumber) == train.at(i).id){
			correct = correct + 1.000;
		}
		temp.clear();
	}
	accuracy = (correct/sz)*100.000;

	cout << "Using feature(s) {"; 
	for(int i = 0; i < fnumber.size(); i++){
		cout << fnumber.at(i)+1;
		if(i != fnumber.size()-1){
			cout << ",";
		}
	}
	cout << "} accuracy is " << setprecision(4) << accuracy << "%" << endl;

	return accuracy;
		
}

void forwardSelection(vector<Instance> instances){
	vector<int> feat;
	int siz = instances.at(0).features.size();
	double max = 0;
	double tmax;
	double temp;
	int best;

	cout << "Running nearest neighbor with all features and leave-one-out evaluation.";
	for(int i = 0; i < siz; i++){
		feat.push_back(i);
	}
	tmax = leaveOneOut(instances, feat);
	feat.clear();
	cout << endl << "Beginning search." << endl << endl;
	for(int i = 0; i < siz; i++){
		feat.push_back(i);
		temp = leaveOneOut(instances,feat);
		if(temp > max){
			max = temp;
			best = i;
		}
		feat.pop_back();
	}
	cout << endl << "Feature set {" << best+1 << "} was best, accuracy is " << max << "%" << endl;
	
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

	/*cout << "testing nearest neighbor" << endl;
	vector<double> f;
	f.push_back(3.64);
	f.push_back(3.51);
	f.push_back(3.55);
	f.push_back(3.13);

	cout << "the nearest neighbor is: " << nearestNeighbor(f, train) << endl;*/

	cout << "Please wait while I normalize the data.. ";

	train = normalize(train);

	cout << "Done!" << endl << endl;
	cout << endl;
	cout << "Type the number of the algorithm you want to run." << endl;
	cout << "1) Forward selection" << endl << "2) Backward Elimination" << endl << endl;


	cin >> choice;
	cout << endl;

	forwardSelection(train);
	
	return 1;
}
