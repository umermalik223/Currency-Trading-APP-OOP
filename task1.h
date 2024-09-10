#pragma once
#include<vector>
#include<map>
#include<string>
using namespace std;




// candlesticks basics class 
class Candlestick{
 public:
double open;
double close;
double High;
double Low;
int year;           
string region; 


// constructor
// passing year , region to get candlesticks of specific region in specific year
Candlestick(int yr, std::string reg) ;



//setters
    void setOpen(double o) ;

    void setClose(double c);

    void setHigh(double h) ;

    void setLow(double l) ;




// Getters 
    double getOpen() const ;

    double getClose() const ;
    
    double getHigh() const ;

    double getLow() const ;




// basic Print Function

    void print() const ;




};


// class for parsing and  storing data then compute candlesticks 
// class # 2

class WeatherDataProcessor {
private:
// basic nested map to store the whole infotmation of weather from csv file 
    map<int, map<string, map<int, pair<vector<int>, double> > > > weatherData;
   //vector<Candlestick> Candlestick;


public:

// getter 
map<int, map<string, map<int, pair<vector<int>, double> > > > get_Data();

 vector <Candlestick> get_candlesticks();
 

    WeatherDataProcessor(const string& filepath) ;
    
    void parseCSV(const string& filepath);

void print_loadedData(std::map<int, std::map<std::string, std::map<int, std::pair<std::vector<int>, double> > > > weatherData);
vector<Candlestick> computeCandlesticks(const map<int, map<string, map<int, pair<vector<int>, double> > > >& data = map<int, map<string, map<int, pair<vector<int>, double> > > >()) ;
    void task1Menu() ;


};