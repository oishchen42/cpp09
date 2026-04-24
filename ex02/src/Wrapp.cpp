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

template <typename T>
static void recordInput(const std::string& input, T& vec)
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
        if (value.ec == std::errc())
        {
            vec.push_back(parsed_value);
            cur_step = value.ptr;
        }
        else
            throw std::logic_error("Error: smth went wrong in recordInputVec");
    }
}

template <typename T>
static void mergeBoth(T& larry, T& rarry, T& vec)
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

template <typename T>
static void mergeSort(T& vec)
{
    if (vec.size() <= 1)
        return ;
    size_t left_array = vec.size() / 2;
    T larry(vec.begin(), vec.begin() + left_array);
    T rarry(vec.begin() + left_array, vec.end());
    mergeSort(larry);
    mergeSort(rarry);
    mergeBoth(larry, rarry, vec);
}

template <typename I>
bool isSorted(I first, I last)
{
    if (first == last)
        return true;
    I next = first;
    next++;
    while (next != last)
    {
        if (*first > *next)
            return false;
        first++;
        next++;
    }
    return true;
}

void Wrapp::sortVec(const std::string& input)
{
    struct timeval start;
    struct timeval end;
    checkInput(input);
    std::vector<int> vec;
    recordInput(input, vec);
    std::cout << "==========Vec before: ============================\n";
    printVec(vec);
    std::cout << "IS Container sorted: " << isSorted(vec.begin(), vec.end()) << std::endl;
    std::cout <<"====================================================\n";

    gettimeofday(&start, NULL);
    mergeSort(vec);
    gettimeofday(&end, NULL);
    double sec = end.tv_sec - start.tv_sec;
    double msec = end.tv_usec - start.tv_usec;

    std::cout << "==========Vec after: ============================\n";
    printVec(vec);
    std::cout << "IS Container sorted: " << isSorted(vec.begin(), vec.end()) << std::endl;
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vec is: " << ((sec * 1000000) + msec) / 1000000 << " us" << std::endl;
    std::cout <<"====================================================\n";

    std::deque<int> dq;
    recordInput(input, dq);
    std::cout << "==========DQ before: ============================\n";
    dqPrint(dq);
    std::cout << "IS Container sorted: " << isSorted(dq.begin(), dq.end()) << std::endl;
    std::cout <<"====================================================\n";
    gettimeofday(&start, NULL);
    mergeSort(dq);
    gettimeofday(&end, NULL);
    sec = end.tv_sec - start.tv_sec;
    msec = end.tv_usec - start.tv_usec;
    std::cout << "==========DQ after: ============================\n";
    dqPrint(dq);
    std::cout << "IS Container sorted: " << isSorted(dq.begin(), dq.end()) << std::endl;
    std::cout << "Time to process a range of " << dq.size() << " elements with std::deque is: " << ((sec * 1000000) + msec) / 1000000 << " us" << std::endl;
    std::cout <<"====================================================\n";
}