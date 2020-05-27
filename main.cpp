#include <iostream> 
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(){
	
	cout << "Welcome to Daniel Cueva's Feature Selection Algorithm." << endl;
	cout << "Type in the name of the file to test: ";

	double val;
	vector <double> data;

	string fname; //variable for file name
	int choice;
	cin >> fname;

	cout << fname << endl << endl;

	ifstream dat;

	dat.open(fname.c_str());
	
	string line;

		getline(dat, line);
		stringstream ss(line);

		while(ss >> val){
			data.push_back(val);
		}
		
	dat.close();
	
	cout << endl;
	for(int i = 0; i < data.size(); i++){
		cout << data.at(i) << " ";
	}
	
	cout << endl;

	cout << "Please wait while I normalize the data.. ";

	//normalize data here
	cout << "Done!" << endl << endl;

	cout << "Type the number of the algorithm you want to run." << endl;
	cout << "1) Forward selection" << endl << "2) Backward Elimination" << endl << endl;


	cin >> choice;
	cout << "Running nearest neighbor with x features, using leaving-one-out evaluation";
	cout << endl;
	
	


	return -1;
}
