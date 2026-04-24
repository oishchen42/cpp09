#include "Wrapp.hpp"

static void printVec(const std::vector<int>& vec)
{
    for(const auto& v : vec)
    {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

static void dqPrint(const std::deque<int>& dqs)
{
    for(const auto& dq : dqs)
    {
        std::cout << dq << " ";
    }
    std::cout << std::endl;
}

static void checkInput(const std::string& input)
{
    std::regex pattern("^[0-9 ]*$");
    if (!std::regex_match(input, pattern))
        throw std::logic_error("Error: the input contains unallowed values");
}

static void recordInputVec(const std::string& input, std::vector<int>& vec)
{
    const char* cur_step = input.data();
    const char* end = input.data();
    end += input.size();
    int parsed_value;
    while (cur_step < end)
    {
        while (cur_step < end && *cur_step == ' ')
            cur_step ++;
        if (cur_step == end)
            break;
        auto value = std::from_chars(cur_step, end, parsed_value);
        // std::cout << "parsed value: " << parsed_value << std::endl;
        if (value.ec == std::errc())
        {
            vec.push_back(parsed_value);
            cur_step = value.ptr;
        }
        else
            throw std::logic_error("Error: smth went wrong in recordInputVec");
    }
    // std::cout << "Our vector: \n";
    // printVec(vec);
}

static void recordInputDq(const std::string& input, std::deque<int>& dq)
{
    const char* cur_step = input.data();
    const char* end = input.data();
    end += input.size();
    int parsed_value;
    while (cur_step < end)
    {
        while (cur_step < end && *cur_step == ' ')
            cur_step ++;
        if (cur_step == end)
            break;
        auto value = std::from_chars(cur_step, end, parsed_value);
        // std::cout << "parsed value: " << parsed_value << std::endl;
        if (value.ec == std::errc())
        {
            dq.push_back(parsed_value);
            cur_step = value.ptr;
        }
        else
            throw std::logic_error("Error: smth went wrong in recordInputVec");
    }
    // std::cout << "Our vector: \n";
    // printVec(vec);
}

static void mergeBoth(std::vector<int>& larry, std::vector<int>& rarry, std::vector<int>& vec)
{
    size_t l = 0;
    size_t r = 0;
    size_t v = 0;
    while (l < larry.size() && r < rarry.size())
    {
        if (larry.at(l) <= rarry.at(r)) 
        {
            vec.at(v) = larry.at(l);
            l++;
        }
        else 
        {
            vec.at(v) = rarry.at(r);
            r++;
        }
        v++;
    }
    while (l < larry.size())
    {
        vec.at(v) = larry.at(l);
        v++;
        l++;
    }
    while (r < rarry.size())
    {
        vec.at(v) = rarry.at(r);
        v++;
        r++;
    }
}

static void mergeBothDq(std::deque<int>& lque, std::deque<int>& rque, std::deque<int>& dq)
{
    size_t l = 0;
    size_t r = 0;
    size_t v = 0;
    while (l < lque.size() && r < rque.size())
    {
        if (lque.at(l) <= rque.at(r)) 
        {
            dq.at(v) = lque.at(l);
            l++;
        }
        else 
        {
            dq.at(v) = rque.at(r);
            r++;
        }
        v++;
    }
    while (l < lque.size())
    {
        dq.at(v) = lque.at(l);
        v++;
        l++;
    }
    while (r < rque.size())
    {
        dq.at(v) = rque.at(r);
        v++;
        r++;
    }
}

static void mergeSort(std::vector<int>& vec)
{
    if (vec.size() <= 1)
        return ;
    // std::cout << "Our array's size: " << vec.size() << "\n";
    // printVec(vec);
    // std::cout << "==================\n";
    size_t left_array = vec.size() / 2;
    std::vector<int> larry(vec.begin(), vec.begin() + left_array);
    std::vector<int> rarry(vec.begin() + left_array, vec.end());
    mergeSort(larry);
    mergeSort(rarry);
    mergeBoth(larry, rarry, vec);
}

static void mergeSortDq(std::deque<int>& dq)
{
    if (dq.size() <= 1)
        return ;
    // std::cout << "Our array's size: " << vec.size() << "\n";
    // printVec(vec);
    // std::cout << "==================\n";
    size_t left_que = dq.size() / 2;
    std::deque<int> lque(dq.begin(), dq.begin() + left_que);
    std::deque<int> rque(dq.begin() + left_que, dq.end());
    mergeSortDq(lque);
    mergeSortDq(rque);
    mergeBothDq(lque, rque, dq);
}

void Wrapp::sortVec(const std::string& input)
{
    struct timeval start;
    struct timeval end;
    checkInput(input);
    std::vector<int> vec;
    recordInputVec(input, vec);
    std::cout << "==========Vec before: ============================\n";
    printVec(vec);
    std::cout <<"====================================================\n";

    gettimeofday(&start, NULL);
    mergeSort(vec);
    gettimeofday(&end, NULL);
    double sec = end.tv_sec - start.tv_sec;
    double msec = end.tv_usec - start.tv_usec;

    std::cout << "Time to process a range of " << vec.size() << " elements with std::vec is: " << ((sec * 1000000) + msec) / 1000000 << " us" << std::endl;
    // std::cout << "The total time spend is: " << msec << std::endl;
    std::cout << "==========Vec after: ============================\n";
    printVec(vec);
    std::cout <<"====================================================\n";

    std::deque<int> dq;
    recordInputDq(input, dq);
    std::cout << "==========DQ before: ============================\n";
    dqPrint(dq);
    std::cout <<"====================================================\n";
    gettimeofday(&start, NULL);
    mergeSortDq(dq);
    gettimeofday(&end, NULL);
    sec = end.tv_sec - start.tv_sec;
    msec = end.tv_usec - start.tv_usec;
    std::cout << "Time to process a range of " << dq.size() << " elements with std::deque is: " << ((sec * 1000000) + msec) / 1000000 << " us" << std::endl;
    std::cout << "==========DQ after: ============================\n";
    dqPrint(dq);
    std::cout <<"====================================================\n";
}