#include<iostream>
#include<vector>
#include<sstream>
#include<fstream>
#include<cmath>
#include "load_data.h"

using namespace std;

class LinearRegression
{
	private:
		double alpha = 0.01;
		int iterations = 1000;
		
	public:
		vector<double> theta;
		vector<double> cost;
		vector<double> predicted_y;

		LinearRegression(double learning_rate,int iterations)
		{
			this->alpha = learning_rate;
			this->iterations = iterations;
		}
		LinearRegression(){};
		double compute_cost(vector< vector<double> > X, vector<double> y, vector<double> theta);
		void fit(vector< vector<double> > X, vector<double> y);
		vector<double> predict(vector< vector<double> > X);
};

double LinearRegression::compute_cost(vector< vector<double> > X, vector<double> y, vector<double> theta)
{
	double cost = 0.0;
	int m = X.size();
	int n = X[0].size();

	for(int i = 0; i < m; i++)
	{
		double h = 0.0;
		for(int j = 0; j < n; j++)
		{
			h += X[i][j] * theta[j];
		}
		double error = h - y[i];
		cost += error * error;
	}
	cost = cost / (2*m);
	return cost;
}

void LinearRegression::fit(vector< vector<double> > X, vector<double> y)
{
	int m = X.size();
	int n = X[0].size();

	vector<double> costs;
	costs.assign(this->iterations,0);

	vector<double> theta;
	theta.assign(n,0);

	cout << "Initial cost: " << compute_cost(X,y,theta) << endl;
	for(int it = 0; it < this->iterations; it++)
	{
		vector<double> temp = theta;
		vector<double> gradient;	
		gradient.assign(n,0);

		for(int i = 0; i < m; i++)
		{
			int h = 0.0;
			for(int j = 0; j < n; j++)
				h += X[i][j] * theta[j];
			double error = h - y[i];
			for(int j = 0; j < n; j++)
				gradient[j] += error * X[i][j];
		}

		for(int j = 0; j < n; j++)
			temp[j] = theta[j] - this->alpha * (1.0/m) * gradient[j];
		theta = temp;
		costs[it] = LinearRegression::compute_cost(X,y,theta);
	}
	this->theta = theta;
	this->cost = costs;
}
	
vector<double> LinearRegression::predict( vector< vector<double> > X)
{
	int m = X.size();
	int n = X[0].size();
	vector<double> theta = this->theta;

	vector<double> y;
	y.assign(m,0);

	for(int i = 0; i < m; i++)
	{
		double h = 0.0;
		for(int j = 0; j < n; j++)
			h += X[i][j] * theta[j];
		y[i] = h;
	}
	this->predicted_y = y;
	return y;
}

int main()
{
	string filename = "./data/ex1data1.txt";
	vector< vector<double> > data;
	vector< vector<double> > X;
	vector<double> y;
	load_data(filename,data,X,y,false);
	LinearRegression lr;
	lr.fit(X,y);
	vector<double> theta = lr.theta;
	for(int i = 0; i < theta.size(); i++)
		cout << theta[i] << " ";
	cout << endl;
	cout << lr.cost[lr.cost.size()-1] << endl;		
	
	return 0;
}
