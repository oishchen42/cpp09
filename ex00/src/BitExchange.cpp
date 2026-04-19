#include "BitExchange.hpp"

BitExchange::BitExchange()
{
    this->getDB("data.csv");
}

BitExchange::~BitExchange() {};

bool BitExchange::isLeap(long year_l) const
{
    return (year_l % 4 == 0);
}

bool BitExchange::checkMonthDay(long year_l, long month_l, long day_l) const
{
    #if DEBUG
        std::cout << "\n=========checkDate===============\n";
        std::cout << "That is our year_l-month_l-day_l: " << year_l << "-" << month_l << "-" << day_l << std::endl;
        std::cout << "=================================\n";
    #endif
    if (isLeap(year_l) && month_l == 2)
        return (day_l > 0 && day_l < 31);
    if (month_l == 1)
        return (day_l > 0 && day_l < 32);
    if (month_l == 2)
        return (day_l > 0 && day_l < 29);
    if (month_l == 3)
        return (day_l > 0 && day_l < 32);
    if (month_l == 4)
        return (day_l > 0 && day_l < 31);
    if (month_l == 5)
        return (day_l > 0 && day_l < 32);
    if (month_l == 6)
        return (day_l > 0 && day_l < 31);
    if (month_l == 7)
        return (day_l > 0 && day_l < 32);
    if (month_l == 8)
        return (day_l > 0 && day_l < 32);
    if (month_l == 9)
        return (day_l > 0 && day_l < 31);
    if (month_l == 10)
        return (day_l > 0 && day_l < 32);
    if (month_l == 11)
        return (day_l > 0 && day_l < 31);
    if (month_l == 12)
        return (day_l > 0 && day_l < 32);
    return false;
}

bool BitExchange::checkDate(const std::string& date) const
{
    //general date_size check: should be 10 yyyy-mm-dd
    if (date.size() != DATE_LENGTH)
        throw std::logic_error("Error: the date format of one or more of the lines in data.csv is wrong (DATE_LENGTH is too short/long)");

    // dashes extracting first dash should be at 4th idx, second at 7th
    uint64_t first_dash = date.find("-");
    if (first_dash != FIRST_DASH_IDX || first_dash == date.size())
        throw std::logic_error("Error: the date format of one or more of the lines in data.csv is wrong (FIRST_DASH_IDX is wrong)");

    uint64_t second_dash = date.find("-", first_dash + 1);
    if (second_dash != SECOND_DASH_IDX || second_dash == date.size())
        throw std::logic_error("Error: the date format of one or more of the lines in data.csv is wrong (SECOND_DASH_IDX is wrong)");

    // strings extraction YYYY | MM | DD
    std::string year = date.substr(0, first_dash);
    std::string month = date.substr(first_dash + 1, MONTH_SIZE);
    std::string day = date.substr(second_dash + 1, DAY_SIZE);
    #if DEBUG
        std::cout << "\n=========checkDate===============\n";
        std::cout << "That is our year.size() month.size() day.size(): " << year.size() << "-" << month.size() << "-" << day.size() << std::endl;
        std::cout << "YEAR: |" << year << "| MONTH: |" << month << "| DAY: |" << day << "|\n";
        std::cout << "=================================\n";
    #endif
    if (year.size() != YEAR_SIZE || month.size() != MONTH_SIZE || day.size() != DAY_SIZE)
        throw std::logic_error("Error: the size or year|month|day is incorrect");

    // value checks for year_l month_l && day_l
    long year_l = std::atol(year.c_str());
    if (year_l > 2022 || year_l < 2009)
        throw std::logic_error("Error: the year cannot be more than 2022 or less than 2009");
    long month_l = std::atol(month.c_str());
    long day_l = std::atol(day.c_str());
    if (!checkMonthDay(year_l, month_l, day_l))
        throw std::logic_error("Error: month should be more than 01 and less than 12, day should be more than 01 and shouldn't be more than max days in a specific month");
    #if DEBUG
        std::cout << "\n=========checkDate===============\n";
        std::cout << "That is our year_l-month_l-day_l: " << year_l << "-" << month_l << "-" << day_l << std::endl;
        std::cout << "=================================\n";
    #endif
    return true;
}

bool BitExchange::isValidDataLine(const std::string& line) const
{
    uint64_t comma = line.find(",");
    if (comma == std::string::npos)
        throw std::logic_error("Error: some date in data.csv is missing a comma");
    std::string date = line.substr(0, comma);
    if (comma == line.size())
        throw std::out_of_range("Error: the value part is missing in one of the lines in data.csv");

    std::string value = line.substr(comma, line.size() - 1);
    if (!checkDate(date)) // TODO :: Values
        return false;
    #if DEBUG
        std::cout << "\n====isValidDataLine==============\n";
        std::cout << "That is our date: " << date << "\n";
        std::cout << "That is our value: " << value << "\n";
        std::cout << "==================================\n";
    #endif
    return true;
}

void BitExchange::getDB(const std::string &dbFile)
{
    std::ifstream file(dbFile.c_str());

    if (!file.is_open())
    {
        throw std::runtime_error("Error: the file \"data.csv\" does not exist or is named not correctly");
    }
    std::string line;
    std::getline(file, line);
    while (getline(file, line))
    {
        if (line.empty())
            continue;
        #if DEBUG
            std::cout << "============getDB=============\n";
            std::cout << "current line: |" << line << "|\n";
            std::cout << "=============================\n";
        #endif
        if (!isValidDataLine(line))
            throw std::logic_error("Error: the date should be of a format yyyy-mm-dd (2009-01-02; 2022-03-29) and the value could not be more then 99999)");
        #if DEBUG
            std::cout << "============getDB=============\n";
            std::cout << line << " - IS CLEAN\n";
            std::cout << "=============================\n";
        #endif
    }
    file.close();
}