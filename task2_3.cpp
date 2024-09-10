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
using namespace std;






//constructor

CandlestickPlotter::CandlestickPlotter(const vector<Candlestick>& candles) : candlesticks(candles) {}

//getter
vector<Candlestick> CandlestickPlotter::get_candlesticks(){

return candlesticks;


}

    void CandlestickPlotter::setColor(const string& color) {
        cout << color;
    }


      // task 3
// filetrs 
// Filter by date 
vector<Candlestick> CandlestickPlotter::filterByDateRange(const vector<Candlestick>& candlesticks, int startYear, int endYear) {
    vector<Candlestick> filtered;
    cout<<" Filter by date \n";

    for (const auto& candle : candlesticks) {
        if (candle.year >= startYear && candle.year <= endYear) {
            filtered.push_back(candle);
             candle.print();
        }
    }
    return filtered;
}
// filter by Country 
vector<Candlestick> CandlestickPlotter::filterByCountry(const vector<Candlestick>& candlesticks, const string& country) {
    vector<Candlestick> filtered;
        cout<<" Filter by region \n";

    for (const auto& candle : candlesticks) {
        if (candle.region == country) {
            filtered.push_back(candle);
                         candle.print();

        }
    }
    return filtered;
}
// filter by temperature

vector<Candlestick> CandlestickPlotter::filterByTemperatureRange(const vector<Candlestick>& candlesticks, double minTemp, double maxTemp) {
    vector<Candlestick> filtered;
        cout<<" Filter by temperature \n";

    for (const auto& candle : candlesticks) {
        if ((candle.getHigh() >= minTemp && candle.getHigh() <= maxTemp) ||
            (candle.getLow() >= minTemp && candle.getLow() <= maxTemp)) {
            filtered.push_back(candle);
            candle.print();

        }
    }
    return filtered;
}



     // task 2
    // using default parameters or passing parameters 
    void CandlestickPlotter::plotCandlesticks(const vector<Candlestick>& candlesticks ) {
         cout << "Creating Text-Based Candlestick Plot:\n\n";
    int year;
    string region;

    cout << "Enter year (0 for all): ";
    cin >> year;
    if (year != 0) {
        cout << "Enter region (empty for all): ";
        cin.ignore();
        getline(cin, region);
    }

    for (const auto& candle : candlesticks) {
        if ((year == 0 || candle.year == year) && (region.empty() || candle.region == region)) {
            //candle.print();
            // speifing regions and years for clearification
            cout<<"CandleStick For Year: "<<candle.year<<endl;
            cout<<"CandleStick For Region: "<<candle.region<<endl;


            if(candle.open>candle.close){
               double var= candle.close-candle.open;
               setColor("\033[1;31m"); // Set text color to red
               cout<<"Highest-->"<<"          ____|____       "<<candle.getHigh()<<endl;
               cout<<"Open-->   ";
               cout<<"         |         |      "<<candle.getOpen()<<endl;

               int var1=var;


               // using abs to ignore -sign in computation
               for(int i=0;i<abs(var1);i+=2){
               cout<<"          "<<"         |         |      ";// flexible body for large range candlesticks 

               if(i<=abs(var1)){
               cout<<"\n";

               }
               }
               //cout<<"\n";

               //cout<<candle.getOpen()<<endl;




            cout<<"Close-->  "<<"         |         |      "<<candle.getClose()<<endl;
            cout<<"Lowest--> "<<"          ----|----       "<<candle.getLow()<<endl<<endl<<endl<<endl;
             //reset color to default
             setColor("\033[0m"); // Reset to default color
    
}
            else if(candle.getOpen()<candle.getClose()){


               double var= candle.open-candle.close;
               setColor("\033[1;32m"); // Set text color to green
               cout<<"Highest-->"<<"          ____|____       "<<candle.getHigh()<<endl;
               cout<<"Close-->  ";
               cout<<"         |         |      "<<candle.getClose()<<endl;
                             
                // using abs to ignore -sign in computation
                int var1=var;

               for(int i=0;i<abs(var1);i+=2){
               cout<<"          "<<"         |         |      ";// flexible body for large range candlesticks 
               if(i<=abs(var1)){
               cout<<"\n";

               }
               }
               //cout<<"\n";

               //cout<<candle.getClose()<<endl;
               cout<<"Open-->   "<<"         |         |      "<<candle.getOpen()<<endl;
               cout<<"Lowest--> "<<"          ----|----       "<<candle.getLow()<<endl<<endl<<endl<<endl;
               //reset color to default
               setColor("\033[0m"); // Reset to default color
    
    }
}
    }
    
    }
    
    
  

//filter by menu 
// this function can apply filters over filters 
// all the three filters are always availble for data 
void CandlestickPlotter::Filters_menu() {
    // Start with all candlesticks then store filtered candlesticks then if another filter is applied then store nested filterted candlesticks 
    // in filteredcandles vector 
    vector<Candlestick> filteredCandles = candlesticks; 
bool leave=false;
    while (!leave) {
        // menu driven filters 
        cout << "Select Your Filter:\n";
        cout << "1 - Filter by Year\n";
        cout << "2 - Filter by Region\n";
        cout << "3 - Filter by Temperature\n";
        cout << "4 - Exit Filtering\n";
        int option;
        cin >> option;

        if (option == 1) {// filter by year
            int startYear, endYear;
            cout << "Enter Start Year: ";
            cin >> startYear;
            cout << "Enter End Year: ";
            cin >> endYear;
            filteredCandles = filterByDateRange(filteredCandles, startYear, endYear);
            plotCandlesticks(filteredCandles);
        } else if (option == 2) {// filter by region
            string region;
            cout << "Enter Region: ";
            cin >> region;
            filteredCandles = filterByCountry(filteredCandles, region);
            plotCandlesticks(filteredCandles);
        } else if (option == 3) {// filter by temperature 
            double minTemp, maxTemp;
            cout << "Enter Minimum Temperature: ";
            cin >> minTemp;
            cout << "Enter Maximum Temperature: ";
            cin >> maxTemp;
            filteredCandles = filterByTemperatureRange(filteredCandles, minTemp, maxTemp);
            plotCandlesticks(filteredCandles);
        } else if (option == 4) {
            cout << "Exiting filter menu.\n";
            break; // Exit the loop and function
        } else {
            cout << "Invalid option. Please select a valid option.\n";
            continue; // Prompt again for valid input
        }

        char continueChoice;
        // for filter over filters 
        cout << "Do you want to continue filtering (y/n)? ";
        cin >> continueChoice;
        if (tolower(continueChoice) != 'y') {
            cout << "Exiting filter menu.\n";
            break; 
        }
        else 
        {leave=false;
        }
    }
}
     
    