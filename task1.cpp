#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iomanip> 
#include <numeric>  // For std::inner_product
#include"task1.h"

using namespace std;

Candlestick::Candlestick(int yr, string reg) : year(yr), region(reg), open(0), close(0),
        High(numeric_limits<double>::lowest()), Low(numeric_limits<double>::max()) {}
//setters
    void Candlestick::setOpen(double o) { open = o; }
    void Candlestick::setClose(double c) { close = c; }
    void Candlestick::setHigh(double h) { if (h > High) High = h; }
    void Candlestick::setLow(double l) { if (l < Low) Low = l; }

    double Candlestick::getOpen() const { return open; }
    double Candlestick::getClose() const { return close; }
    double Candlestick::getHigh() const { return High; }
    double Candlestick::getLow() const { return Low; }
//getters
    void Candlestick::print() const {
        cout << "Year: " << year << ", Region: " << region
             << ", Open: " << open << ", High: " << High
             << ", Low: " << Low << ", Close: " << close << endl;
    }



//Weather data processer class 
//print loading statements and calling parse function 
//constructor

    WeatherDataProcessor::WeatherDataProcessor(const string& filepath) {
        cout << "Loading Weather data ..........\n";

        parseCSV(filepath);
        cout << "Weather data loaded successfully.\n";

        cout<<"Do You want to Check Loaded Data(y/n) ?\n";
     char ans;
     cin>>ans;
     if(ans=='y'||ans=='Y'){
        print_loadedData(weatherData);

     }
    }


// getter 
map<int, map<string, map<int, pair<vector<int>, double> > > > WeatherDataProcessor::get_Data(){


    return weatherData;
}

 vector <Candlestick> WeatherDataProcessor::get_candlesticks(){
    vector <Candlestick> candlesticks =computeCandlesticks(get_Data());
    

     return candlesticks;


}


 // parsing csv file as per requirement .... using data structure of nested map to store the data 
// parsing CSV file and storing it in nested map 
// first key=>yera
// second key =>year
// third key=>month
// pair.first vector=> daily temperatures over a month temperatures
// pair.second average of monthly temperture
    void WeatherDataProcessor::parseCSV(const string& filepath) {
        std::ifstream file(filepath);
    std::string line;
    getline(file, line); // Read header of file
    std::string region;
    std::vector<std::string> regions;

    // Read the header to get region names
    std::stringstream headerStream(line);
    // skip date column
    //reading but not storing 
    getline(headerStream, region, ','); 

    //storing the names of regions 
    while (getline(headerStream, region, ',')) {
        regions.push_back(region);
    }
    
    // moving to data rows 
    while (getline(file, line)) {
        // stored stream in line already
        std::stringstream ss(line);
        std::string date, temp;
        //parsing stream in date and temperature

        getline(ss, date, ','); // Extract date
            // parsing date in year and month
        int year = std::stoi(date.substr(0, 4));
        int month = std::stoi(date.substr(5, 2));
    //std::cout << "Year parsed: " << year << ", Month parsed: " << month << std::endl; // Debugging line
       


       // storing data according to regions 
       //monthly temperature data of every region 

        int regionIndex = 0;
        while (getline(ss, temp, ',') && regionIndex < regions.size()) {
            int temperature = std::stoi(temp);
            auto& entry = weatherData[year][regions[regionIndex]][month];
            entry.first.push_back(temperature);
            entry.second += temperature;
            ++regionIndex;
        }
        

        
    }
    file.close();


// calculating sum of temperatures for every month from stored information 
    for (auto& yearMap : weatherData) {
        for (auto& regionMap : yearMap.second) {
            for (auto& monthMap : regionMap.second) {
                auto& temperatures = monthMap.second.first;
                double sum = 0;
                for (int temp : temperatures) {
                    sum += temp;
               
   }
            // Storing the average  temperature of each month 
            monthMap.second.second = temperatures.size() > 0 ? sum / temperatures.size() : 0;
        }
    }
}



    }
//Once the Data is being loaded from CSV file to the nested map data structure of code we can print it on terminal also 
void WeatherDataProcessor::print_loadedData(std::map<int, std::map<std::string, std::map<int, std::pair<std::vector<int>, double> > > > weatherData){
//iterating over every year of weather data set   
for (const auto& yearPair : weatherData)  
    {
        int year = yearPair.first;
        const auto& regions = yearPair.second;
        //iterating over every region of weather data set
        for (const auto& regionPair : regions) 
    {
        {
            string region = regionPair.first;
            const auto& months = regionPair.second;
            for (const auto& monthPair : months) {
                int month = monthPair.first;
                const auto& temps = monthPair.second.first;
                double avrtemp = monthPair.second.second;
                // Printing Monthly Info for Every year 
                cout << "Year: " << year <<"\t\t"<< " Region: " << region <<endl<< " Month: " << month << ", Average Temperature of the Month: " << avrtemp << std::endl;
              
        //return 1;
    }

    
        }
        }
    }

}
vector<Candlestick> WeatherDataProcessor::computeCandlesticks(const map<int, map<string, map<int, pair<vector<int>, double> > > >& data ) {
        std::vector<Candlestick> candlesticks;
    for (const auto& yearEntry : data) {
        int year = yearEntry.first;
        for (const auto& regionEntry : yearEntry.second) {
            string region = regionEntry.first;
            //cout << "Creating Candlestick for year: " << year << ", region: " << region << endl;


            // calling constructor of candlestick calss to initialize year and region
            Candlestick cs(year, region);
             //setting values of fields of candlestick 
            for (const auto& monthEntry : regionEntry.second) {
                const auto& temperatures = monthEntry.second.first;
                double monthlyAvg = monthEntry.second.second;
                
                //providing candlesticks by date(yearly)
                // January is considered the opening month
                if (monthEntry.first == 1) {
                    cs.setOpen(monthlyAvg);
                }
                // December is considered the closing month
                if (monthEntry.first == 12) {
                    cs.setClose(monthlyAvg);
                }
                // Calculate high and low across all months
                for (int temp : temperatures) {
                    // higher and lower comparison will be in setters 
                    cs.setHigh(temp);
                    cs.setLow(temp);
                }
            }
            candlesticks.push_back(cs);
        }
    }
    return candlesticks;
}

    void WeatherDataProcessor::task1Menu() {
       char choice='n';
      // Getting vector<Candlestick>  for every year
        int option;
        
        
        do 
         {

        // menu 
        cout<<"What do you want to check ? \nPlease Select an Option :\n1-CandleStick Data From 1980-2019\n2-CandleStick Data for Year and Region of Your Choice ?\n3-Exist\n";
        cin>>option;
        // input check
        while (option<0 || option>3){

       cout<<"Error! Please Select the right Option.\n";
       cin>>option;
        }
        cout<<"computing candlesticks...\n";
                   // basic for task 1 
                vector <Candlestick>  candlesticks = computeCandlesticks(weatherData);
                 //cout<<"size:"<<candlesticks.size()<<endl;

         
         if(option==1){

          //candlesticks = computeCandlesticks(weatherData);
          // printing  candle sticks for all the parsed data present in map<>
         for (const auto& cs : candlesticks) {
          cs.print();
        }


         }
         else if (option == 2) {

            int selectedYear;
            string selectedRegion;
            cout << "Enter year: ";
            cin >> selectedYear;
            // verfication of year 
            if (weatherData.find(selectedYear) == weatherData.end()) {
                cout << "No data available for year " << selectedYear << ".\n";
                continue;
            }
            // printing all the available region under a specific year , from map<>
            cout << "Available regions for " << selectedYear << ":\n";
            for (const auto& region : weatherData.at(selectedYear)) {
                cout << region.first << "\n";
            }

            cout << "Select region: ";
            cin >> selectedRegion;
                 // verfication of region

            if (weatherData.at(selectedYear).find(selectedRegion) == weatherData.at(selectedYear).end()) {
                cout << "No data available for region " << selectedRegion << ".\n";
                continue;
            }
            //filtering weather information for selected year and region and storing it in new map
            map<int, map<string, map<int, pair<vector<int>, double> > > > filteredData;
            filteredData[selectedYear][selectedRegion] = weatherData.at(selectedYear).at(selectedRegion);
            vector<Candlestick>candle;
            // Computing candlesticks for filtered data  

            candle= computeCandlesticks(filteredData);

            for (const auto& candles : candle) {
                // printing of filetered candlesticks only
                candles.print();
            }
        }

   //cout<<"\n\nsize:"<<candlesticks.size();

   cout<<"Do you want to Continue Checking CandleStick Data (y/n)?\n";
    cin>> choice;

    } while (choice =='y'|| choice=='Y');


    }




