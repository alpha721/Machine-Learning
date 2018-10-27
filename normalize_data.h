#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

void normalize_data(vector< vector<double> >& dataset)
{
    int m = dataset.size();
    int n = dataset[0].size();

    vector<double> mean;
    mean.assign(n,0);
    vector<double> std;
    std.assign(n,0); 
    for(int j = 0; j < n; j++)
    {
        double total = 0.0;
        for(int i = 0; i < m; i++)
        {
            total += dataset[i][j];
        }
        mean[j] = total/m;
    }

    for(int j = 0; j < n; j++)
    {
        double dev = 0.0;
        for(int i = 0; i < m; i++)
        {
            dev += pow(( dataset[i][j] - mean[j]),2);
        }
        dev = dev / (m-1);
        dev = sqrt(dev);
        std[j] = dev;
    }

    for(int j = 0; j < n; j++)
    {
        for(int i = 0; i < m; i++)
            dataset[i][j] = (dataset[i][j] - mean[j])/ ( std[j]);
    }
}

