#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip> 
#include <numeric>  // For std::inner_product
#include"task1.h"
#include"task2_3.h"
#include"task4.h"


using namespace std;


 TemperaturePredictor::TemperaturePredictor(const map<int, map<string, map<int, pair<vector<int>, double> > > >& data) {
        
        cout<<"in prediction constructor\n";
        prediction_params(data);
    }

 map<string,pair<double,double> > TemperaturePredictor::prediction_params(const map<int, map<string, map<int, pair<vector<int>, double> > > >& data) {
    cout<<"in prediction params\n";
// Map to store the slope and intercept for each region
    map<string, pair<double, double> > regressionParams;

    // Iterate over each region to calculate slope and intercept
    for (const auto& yearEntry : data.begin()->second) {
        string region = yearEntry.first;
        vector<int> years;
        vector<double> yearlyAverages;

        // Gather data for this region across all years
        for (const auto& yearMap : data) {
            int year = yearMap.first;
            double totalAverage = 0;
            int count = 0;

            auto regionIt = yearMap.second.find(region);
            if (regionIt != yearMap.second.end()) {
                for (const auto& monthMap : regionIt->second) {
                    totalAverage += monthMap.second.second;
                    count++;
                }
            }
             // yearly temperature averages -> Y
             // years ->Y 
            if (count > 0) {
                double yearlyAverage = totalAverage / count;
                years.push_back(year);
                yearlyAverages.push_back(yearlyAverage);
            }
        }

        if (years.size() < 2) continue; // Skip regions with insufficient data



         int n=years.size();   // number of total enteries 
         // Step 1 


        //Calculate sum of X and Calculate mean of Y 

        double sum_X = accumulate(years.begin(), years.end(), 0.0);
        double sum_Y = accumulate(yearlyAverages.begin(), yearlyAverages.end(), 0.0);
        //step 2
         //Calculate sum of X and Calculate mean of Y 
        double mean_X = sum_X / n;
        double mean_Y = sum_Y / n;

        // Step 3
        // calculation of dev_x and dev_y 
        double numerator = 0.0; // step 4  Product of Dev_X and DEV_y 
        double denominator = 0.0;// step 5  square of Dev_X  
        for (int i = 0; i < n; ++i) {
            double x_dev = years[i] - mean_X;
            double y_dev = yearlyAverages[i] - mean_Y;
            numerator += x_dev * y_dev;
            denominator += x_dev * x_dev;
        }
        // step 6 
        // slop => m 
        double slope = numerator / denominator;
        // step 7
        // calculation of b
        double intercept = mean_Y - (slope * mean_X);

        regressionParams[region] = make_pair(slope, intercept);
    }

    // Output the results
    for (const auto& reg : regressionParams) {
        cout << "Region: " << reg.first
             << "\nSlope: " << reg.second.first
             << "\nIntercept: " << reg.second.second << "\n\n";
    }

return regressionParams;
   

}


// task 4 
void  TemperaturePredictor::Prediction(const map<int, map<string, map<int, pair<vector<int>, double> > > >& data){
cout<<"in prediction function\n";

map<string, pair<double, double> > regressionParams;

regressionParams=prediction_params(data);

 string region;
 int yr;// x
 cout<<"Enter Year for which you want Temperature Prediction:\n";
 cin>>yr;
 cout<<"Enter region for which you want Temperature Prediction:\n";
 cin>>region;

// calculation
bool found=false;
for(const auto & iter:regressionParams){

if(region==iter.first)
{
 // y      =   m (slope)          *   x   +  b(intercept)
   double y = ((iter.second.first)*yr )+(iter.second.second);
cout<<"Predicted Average Temperature of "<<region<<"in "<<yr<<"is "<<y<<endl;
found=true;

}




}

if(!found)
 {cout<<"NO such Region available \n";
 }

}

