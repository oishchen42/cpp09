#pragma once
#include "include.h"

class BitExchange
{
public:
    BitExchange();
    BitExchange(const BitExchange &other) = delete;
    BitExchange& operator=(const BitExchange &other) = delete;
    ~BitExchange() = default;

    void inputFile(const std::string &file);

    private:
    std::map<std::string, float> _database;

    void getDB(const std::string& dbFile);
    float getPrice(const std::string &date);

    void calculateAndPrint(const std::string& line);

    // data.csv checkers
    bool validateLine(const std::string& line) const;
    bool isDateValid(const std::string& date) const;
    bool isValidMonthDay(long year_l, long month_l, long day_l) const;
    bool isDouble(const std::string &value) const;
};