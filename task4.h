#pragma once
#include<vector>
#include<map>
#include<string>
#include"task1.h"
#include"task2_3.h"

using namespace std;


// for task 4 
    class TemperaturePredictor {
private:
    map<string, pair<double, double> > regressionParams;

public:
    TemperaturePredictor(const map<int, map<string, map<int, pair<vector<int>, double> > > >& data) ;
    

 map<string,pair<double,double> > prediction_params(const map<int, map<string, map<int, pair<vector<int>, double> > > >& data);
 void  Prediction(const map<int, map<string, map<int, pair<vector<int>, double> > > >& data);
    };
