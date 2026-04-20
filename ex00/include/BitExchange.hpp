#pragma once
#include "include.h"

class BitExchange
{
public:
    BitExchange();
    BitExchange(const BitExchange &other);
    BitExchange& operator=(const BitExchange &other);
    ~BitExchange();

    void inputFile(const std::string &file) const;

    void findDate(const std::string &date) const;

    private:
    std::map<std::string, float> _database;

    float getPrice(const std::string& date) const;
    void getDB(const std::string& dbFile);
    bool purifyInput(const std::string& line, std::string& date, float& value) const;

    // data.csv checkers
    bool validateLine(const std::string& line) const;
    bool isDateValid(const std::string& date) const;
    float purifyValue(const std::string& value) const;
    bool isValidMonthDay(long year_l, long month_l, long day_l) const;
    bool isDouble(const std::string &value) const;
};