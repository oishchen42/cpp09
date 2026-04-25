#include "Wrapp.hpp"

// static void printVec(const std::vector<int>& vec)
// {
//     for(const auto& v : vec)
//     {
//         std::cout << v << " ";
//     }
//     std::cout << std::endl;
// }

// static void dqPrint(const std::deque<int>& dqs)
// {
//     for(const auto& dq : dqs)
//     {
//         std::cout << dq << " ";
//     }
//     std::cout << std::endl;
// }

template <typename T>
static void pairsPrint(const T& box)
{
    for (const auto& item : box)
    {
        std::cout << "[" << item.first << "; " << item.second << "] ";
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

template <typename T>
static void pairsSortByFirstElement(T& pairs)
{
    if (pairs.size() <= 1)
        return ;
    size_t left = pairs.size() / 2;
    T left_arr(pairs.begin(), pairs.begin() + left);
    T right_arr(pairs.begin() + left, pairs.end());
    // std::cout << "Left array: ";
    // pairsPrint(left_arr);
    // std::cout << "Right array: ";
    // pairsPrint(right_arr);
    pairsSortByFirstElement(left_arr);
    pairsSortByFirstElement(right_arr);
    size_t l = 0;
    size_t r = 0;
    size_t a = 0;
    while (l < left_arr.size() && r < right_arr.size())
    {
        if (left_arr[l].first <= right_arr[r].first)
            pairs[v++] = left_arr[l++];
        else
            pairs[v++] = right_arr[r++];
    }
    while (l < left_arr.size())
        pairs[v++] = left_arr[l++];
    while (r < right_arr.size())
        pairs[v++] = right_arr[r++];
}

static void sortVecPairs(std::vector<int>& vec)
{
    if (vec.size() <= 1)
        return ;
    int tail = -1;
    std::vector<std::pair<int, int>> pairs;
    if (vec.size() % 2 != 0)
    {
        tail = vec.at(vec.size() - 1);
        vec.pop_back();
    }
    pairs.reserve(vec.size() / 2);
    for (size_t i = 1; i < vec.size(); i+=2)
    {
        if (vec.at(i) > vec.at(i - 1))
            pairs.push_back(std::make_pair(vec.at(i), vec.at(i - 1)));
        else
            pairs.push_back(std::make_pair(vec.at(i - 1), vec.at(i)));
    }
    // std::cout << "Our pairs: ";

    // pairsPrint(pairs);
    // std::cout << "===================================\n";
    pairsSortByFirstElement(pairs);
    std::vector<int> ft_main;
    std::vector<int> ft_pend;
    ft_main.reserve(pairs.size());
    ft_pend.reserve(pairs.size());
    dividePairs(pairs, ft_pend, ft_main);
    ft_main.insert(ft_main.begin(), ft_pend.at(0));
    std::vector<int> jcb_sque = getSequence(ft_pend.size());
    insertJcb(jcb_sque, ft_pend, ft_main);
}

void Wrapp::sortVec(const std::string& input)
{
    checkInput(input);
    std::vector<int> vec;
    recordInput(input, vec);
    sortVecPairs(vec);
}

// void Wrapp::sortVec(const std::string& input)
// {
//     struct timeval start;
//     struct timeval end;
//     checkInput(input);
//     std::vector<int> vec;
//     recordInput(input, vec);
//     std::cout << "==========Vec before: ============================\n";
//     printVec(vec);
//     std::cout << "IS Container sorted: " << isSorted(vec.begin(), vec.end()) << std::endl;
//     std::cout <<"====================================================\n";

//     gettimeofday(&start, NULL);
//     mergeSort(vec);
//     gettimeofday(&end, NULL);
//     double sec = end.tv_sec - start.tv_sec;
//     double msec = end.tv_usec - start.tv_usec;

//     std::cout << "==========Vec after: ============================\n";
//     printVec(vec);
//     std::cout << "IS Container sorted: " << isSorted(vec.begin(), vec.end()) << std::endl;
//     std::cout << "Time to process a range of " << vec.size() << " elements with std::vec is: " << ((sec * 1000000) + msec) / 1000000 << " us" << std::endl;
//     std::cout <<"====================================================\n";

//     std::deque<int> dq;
//     recordInput(input, dq);
//     std::cout << "==========DQ before: ============================\n";
//     dqPrint(dq);
//     std::cout << "IS Container sorted: " << isSorted(dq.begin(), dq.end()) << std::endl;
//     std::cout <<"====================================================\n";
//     gettimeofday(&start, NULL);
//     mergeSort(dq);
//     gettimeofday(&end, NULL);
//     sec = end.tv_sec - start.tv_sec;
//     msec = end.tv_usec - start.tv_usec;
//     std::cout << "==========DQ after: ============================\n";
//     dqPrint(dq);
//     std::cout << "IS Container sorted: " << isSorted(dq.begin(), dq.end()) << std::endl;
//     std::cout << "Time to process a range of " << dq.size() << " elements with std::deque is: " << ((sec * 1000000) + msec) / 1000000 << " us" << std::endl;
//     std::cout <<"====================================================\n";
// }