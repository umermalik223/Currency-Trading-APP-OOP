#include "MerkelMain.h"
#include "task1.h"
#include "task2_3.h"
#include "task4.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "csvreader.h"
#include "OrderBook.h"
#include <map>
#include <vector>
#include <string>
//#include "AssignmentTasks.cpp"
//vector<Candlestick>candleSticks;



MerkelMain::MerkelMain()
{

}

void MerkelMain::init()
{    string filePath = "weather_data_EU_1980-2019_temp_only.csv";
    WeatherDataProcessor LOADER(filePath);

    int input;
    currentTime = orderBook.getEarliestTime();

    wallet.insertCurrency("BTC", 10);
    bool loopcheck=false;
    while(!loopcheck)
    {   
        printMenu();
        input = getUserOption();
        loopcheck=processUserOption(input,LOADER);
    }
}


void MerkelMain::printMenu()
{    //exist 
    std::cout << "0: Exit Menu" << std::endl;

    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid 
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 continue   
    std::cout << "6: Continue " << std::endl;
    // task 1
    std::cout << "7: Compute CandleSticks Data" << std::endl;
    //taskk 2
    std::cout << "8: Text Based CandleStick Representation " << std::endl;
    //task 3
    std::cout << "9: Apply filters on data and get candlesticks against them" << std::endl;
    //task 4
    std::cout << "10:Prediction of Weather " << std::endl;


    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, 
                                                                p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;



    }
    // std::cout << "OrderBook contains :  " << orders.size() << " entries" << std::endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.orderType == OrderBookType::ask)
    //     {
    //         asks ++;
    //     }
    //     if (e.orderType == OrderBookType::bid)
    //     {
    //         bids ++;
    //     }  
    // }    
    // std::cout << "OrderBook asks:  " << asks << " bids:" << bids << std::endl;

}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::ask 
            );
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }   
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else {
        try {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2], 
                currentTime, 
                tokens[0], 
                OrderBookType::bid 
            );
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }catch (const std::exception& e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }   
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}
        
void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl; 
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
        
    }

    currentTime = orderBook.getNextTime(currentTime);
}
 
int MerkelMain::getUserOption()
{
    int userOption ;
    std::string line;
    std::cout << "Type in 0-10" << std::endl;
    cin>>userOption;
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

bool MerkelMain::processUserOption(int userOption,WeatherDataProcessor &LOADER)
     {
        static bool check_parsing=false;

        // onject outside the  condition so that i can access it through out the code 
          CandlestickPlotter  plotter (LOADER.get_candlesticks());

    
    if (userOption <0&&userOption>10) // bad input
    {
        std::cout << "Invalid choice. Choose 1-10" << std::endl;
        return 0;
    }
    if (userOption == 1) 
    {
        printHelp();
                return 0;

    }
    if (userOption == 2) 
    {
        printMarketStats();
                return 0;

    }
    if (userOption == 3) 
    {
        enterAsk();
                return 0;

    }
    if (userOption == 4) 
    {
        enterBid();
                return 0;

    }
    if (userOption == 5) 
    {
        printWallet();
                return 0;

    }
    if (userOption == 6) 
    {
        gotoNextTimeframe();
                return 0;

    }       
    if (userOption == 7) 
    {

    //task 1
         LOADER.task1Menu();
         check_parsing=true;
              return 0;


    }
    if (userOption == 8) 
    {//task2 


        if(!check_parsing){
          string filePath = "weather_data_EU_1980-2019_temp_only.csv";
          WeatherDataProcessor LOADER(filePath); 
          plotter.plotCandlesticks(plotter.get_candlesticks());


        }
         else  plotter.plotCandlesticks(plotter.get_candlesticks());
        
        
                 return 0;

     }     
    if (userOption == 9) 
    {

// task 3 
if(!check_parsing){
          string filePath = "weather_data_EU_1980-2019_temp_only.csv";
          WeatherDataProcessor LOADER(filePath); 
              plotter.Filters_menu();


        }
     
    else plotter.Filters_menu();
             return 0;

     }
    if (userOption == 10) 
    {
        if(!check_parsing){
          string filePath = "weather_data_EU_1980-2019_temp_only.csv";
          WeatherDataProcessor LOADER(filePath); 
              TemperaturePredictor prediction(LOADER.get_Data());
                  prediction.Prediction(LOADER.get_Data());



        }
    else {TemperaturePredictor prediction(LOADER.get_Data());
    prediction.Prediction(LOADER.get_Data());
    
    }
             return 0;

    }       
    if (userOption==0){
        return 1;
    }
    return 0;
}
