#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "task1.h"
#include "task2_3.h"
#include "task4.h"


#include "OrderBook.h"
#include "Wallet.h"
#include <map>
#include <string>

class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
    private: 
        void printMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        bool processUserOption(int userOption,WeatherDataProcessor &LOADER);
       


        std::string currentTime;

//        OrderBook orderBook{"20200317.csv"};
	OrderBook orderBook{"20200601.csv"};
        Wallet wallet;

};
