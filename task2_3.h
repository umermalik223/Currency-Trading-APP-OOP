#pragma once
#include<vector>
#include<map>
#include<string>
#include"task1.h"
using namespace std;

class CandlestickPlotter {
private:
    vector<Candlestick> candlesticks;

    void setColor(const string& color) ;

      // task 3
// filetrs 
// Filter by date 
vector<Candlestick> filterByDateRange(const vector<Candlestick>& candlesticks, int startYear, int endYear) ;

// filter by Country 
vector<Candlestick> filterByCountry(const vector<Candlestick>& candlesticks, const string& country) ;

// filter by temperature

vector<Candlestick> filterByTemperatureRange(const vector<Candlestick>& candlesticks, double minTemp, double maxTemp) ;



public :
vector<Candlestick> get_candlesticks();

    CandlestickPlotter(const vector<Candlestick>& candles);

 void plotCandlesticks(const vector<Candlestick>& candlesticks =  vector<Candlestick>()) ;

void Filters_menu() ;

     
    


};
