#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<string>
#include<cmath>
#include "normalize_data.h"

using namespace std;

void load_data(string filename, vector< vector<double> >& data, vector< vector<double> >& X, vector<double>& y, bool normalize)
{
    ifstream infile(filename);
    string line;
    double input;
    int count = 0;
    
    while( getline(infile,line))
    {
        stringstream ss(line);
        vector<double> temp;

        while( ss >> input )
        {
            temp.push_back(input);
            if( ss.peek() == ',')
                ss.ignore();
        }
        data.push_back(temp);
        ss.str("");
    }

    vector<double> temp;
	vector<double> norm_temp;
	vector< vector<double> > norm_data;
    
	temp.assign(data[0].size(),0);
	norm_temp.assign(data[0].size()-1,0);
	norm_data.assign(data.size(),norm_temp);
    X.assign(data.size(),temp);
    y.assign(data.size(),0);
	for(int i = 0; i < data.size(); i++)
	{
		for(int j = 0; j < data[i].size()-1; j++)
			norm_data[i][j] = data[i][j];
	}

	if( normalize == true) normalize_data(norm_data);
    for( int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < data[i].size(); j++)
            if( j == 0) X[i][j] = 1;
            else X[i][j] = norm_data[i][j-1];
        y[i] = data[i][data[i].size()-1];
    }
}

