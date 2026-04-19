#pragma once
#include "include.h"

class BitExchange
{
public:
    BitExchange();
    BitExchange(const BitExchange &other);
    BitExchange& operator=(const BitExchange &other);
    ~BitExchange();

    void beInput(const std::string& file) const;
    
    private:
    std::map<std::string, float> _database;

    float getPrice(const std::string& date) const;
    void getDB(const std::string& dbFile);
    bool purifyInput(const std::string& line, std::string& date, float& value) const;

    // data.csv checkers
    bool isValidDataLine(const std::string& line) const;
    bool checkDate(const std::string& date) const;
    bool checkValue(const std::string& value) const;
    bool checkMonthDay(long year_l, long month_l, long day_l) const;
    bool isLeap(long year_l) const;
};