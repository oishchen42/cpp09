#include "BitExchange.hpp"

BitExchange::BitExchange()
{
    this->getDB("data.csv");
}

bool BitExchange::isValidMonthDay(long year_l, long month_l, long day_l) const
{
    const std::array<int, 12> days = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (!(month_l > 0 && month_l < 13))
        return false;
    int max_day = days[month_l - 1];
    if (month_l == 2 && ((year_l % 4 == 0 && year_l % 100 != 0) || year_l % 400 == 0))
        max_day = 29;
    return (day_l <= max_day);
}

bool BitExchange::isDateValid(const std::string& date) const
{
    uint64_t year = std::stol(date.substr(0, FIRST_DASH_IDX));
    uint64_t month = std::stol(date.substr(FIRST_DASH_IDX + 1, 2));
    uint64_t day = std::stol(date.substr(SECOND_DASH_IDX + 1, 2));
    if (!isValidMonthDay(year, month, day))
        return false;
    return true;
}

bool BitExchange::validateLine(const std::string& line) const
{
    std::regex pattern("^[0-9]{4}-[0-9]{2}-[0-9]{2},[0-9]{1,5}+(\\.{0,1}[0-9]{1,4}){0,1}$");
    if (!std::regex_match(line, pattern))
        throw std::logic_error("Error: line's format does not match (allowed type: 0000-00-00,00.00).");
    if (!isDateValid(line.substr(0, DATE_LENGTH)))
        throw std::logic_error("Error: the date is not valid.");
    return true;
}

void BitExchange::getDB(const std::string &dbFile)
{
    std::ifstream file(dbFile.c_str());

    if (!file.is_open())
    {
        throw std::runtime_error("Error: the file \"data.csv\" does not exist or is named not correctly.");
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
        if (!validateLine(line))
        {
            file.close();
            throw std::logic_error("Error: the date should be of a format yyyy-mm-dd (2009-01-02; 2022-03-29) and the value could not be more then 99999).");
        }
        #if DEBUG
            std::cout << "============getDB=============\n";
            std::cout << line << " - IS CLEAN\n";
            std::cout << "=============================\n";
        #endif
        this->_database[line.substr(0,DATE_LENGTH)] = stod(line.substr(VALUE_IDX));
    }
    file.close();
}

void BitExchange::inputFile(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Error: the file could not be opened or does not exist.");
    }
    std::string line;
    std::getline(file, line);
    if (line != FIRST_LINE)
    {
        file.close();
        throw std::logic_error("Error: the first line of input file should be (\"date | value\").");
    }
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        calculateAndPrint(line);
    }
    file.close();
}

void BitExchange::calculateAndPrint(const std::string& line)
{
    std::regex pattern("^[0-9]{4}-[0-9]{2}-[0-9]{2} \\| [0-9]+(\\.[0-9]+)?$");
    if (!std::regex_match(line, pattern))
    {
        std::cerr << "Error: the format of the value is wrong. Try again following the example from the subject.\n";
        return ;
    }
    if (line.size() > MAX_SIZE)
    {
        std::cerr << "Error: the value is too big.";
        return ;
    }
    std::string value = line.substr(PIPE_IDX);
    float value_f = std::stod(value);
    if (value_f < 0 || value_f > 1000.0)
        std::cerr << ("Error: the value should be in the range [0, 1000].");
    float modifer = getPrice(line.substr(0, DATE_LENGTH));
    if (modifer != -1.0)
        std::cout << line.substr(0, DATE_LENGTH) << " => " << value_f << " = " << modifer * value_f << "\n";
}

float BitExchange::getPrice(const std::string &date)
{
    std::map<std::string, float>::iterator it = _database.lower_bound(date);
    if (it != _database.end() && it->first == date)
        return it->second;
    if (it == _database.begin())
    {
        std::cerr << "Error: the given date should not be earlier the first date in data.csv.";
        return -1.0;
    }
    --it;
    return it->second;
}