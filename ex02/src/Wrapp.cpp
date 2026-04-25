#include "Wrapp.hpp"

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
static void pairsSortByFirstElement(T& pairs)
{
    if (pairs.size() <= 1)
        return ;
    size_t left = pairs.size() / 2;
    T left_arr(pairs.begin(), pairs.begin() + left);
    T right_arr(pairs.begin() + left, pairs.end());
    pairsSortByFirstElement(left_arr);
    pairsSortByFirstElement(right_arr);
    size_t l = 0;
    size_t r = 0;
    size_t a = 0;
    while (l < left_arr.size() && r < right_arr.size())
    {
        if (left_arr[l].first <= right_arr[r].first)
            pairs[a++] = left_arr[l++];
        else
            pairs[a++] = right_arr[r++];
    }
    while (l < left_arr.size())
        pairs[a++] = left_arr[l++];
    while (r < right_arr.size())
        pairs[a++] = right_arr[r++];
}

template <typename T>
static void getSequence(size_t size, T& box)
{
    if (size == 0)
        return ;
    T jb_que;
    jb_que.push_back(1);
    jb_que.push_back(3);
    while ((size_t)jb_que.back() < size)
    {
        size_t next = jb_que.back() + 2 * jb_que.at(jb_que.size() - 2);
        jb_que.push_back(next);
    }
    size_t last = jb_que.at(0);
    for (size_t i = 1; i < jb_que.size(); i++)
    {
        size_t current = jb_que.at(i);
        size_t last_idx = current - 1;
        if (last_idx >= size)
            last_idx = size - 1;
        for (; last_idx >= last; last_idx--)
        {
            box.push_back(last_idx);
            if (last_idx == 0)
                break ;
        }
        last = current;
    }
}

template <typename T>
static void insertJcb(T& sque, T& ft_pend, T& ft_main, int tail)
{
    for (size_t i = 0; i < sque.size(); i++)
    {
        size_t idx = sque.at(i);
        int value = ft_pend.at(idx);
        typename T::iterator insert_point = std::lower_bound(ft_main.begin(), ft_main.end(), value);
        ft_main.insert(insert_point, value);
    }
    if (tail != -1)
    {
        typename T::iterator insert_point = std::lower_bound(ft_main.begin(), ft_main.end(), tail);
        ft_main.insert(insert_point, tail);
    }
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
    pairsSortByFirstElement(pairs);
    std::vector<int> ft_main;
    std::vector<int> ft_pend;
    ft_main.reserve(pairs.size());
    ft_pend.reserve(pairs.size());
    for (size_t i = 0; i < pairs.size(); i++)
    {
        ft_main.push_back(pairs[i].first);
        ft_pend.push_back(pairs[i].second);
    }
    ft_main.insert(ft_main.begin(), ft_pend.at(0));
    std::vector<int> jcb_sque;
    getSequence(ft_pend.size(), jcb_sque);
    insertJcb(jcb_sque, ft_pend, ft_main, tail);
    vec = ft_main;
}

static void sortDqPairs(std::deque<int>& dq)
{
    if (dq.size() <= 1)
        return ;
    int tail = -1;
    std::vector<std::pair<int, int>> pairs;
    if (dq.size() % 2 != 0)
    {
        tail = dq.at(dq.size() - 1);
        dq.pop_back();
    }
    pairs.reserve(dq.size() / 2);
    for (size_t i = 1; i < dq.size(); i+=2)
    {
        if (dq.at(i) > dq.at(i - 1))
            pairs.push_back(std::make_pair(dq.at(i), dq.at(i - 1)));
        else
            pairs.push_back(std::make_pair(dq.at(i - 1), dq.at(i)));
    }
    pairsSortByFirstElement(pairs);
    std::deque<int> ft_main;
    std::deque<int> ft_pend;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        ft_main.push_back(pairs[i].first);
        ft_pend.push_back(pairs[i].second);
    }
    ft_main.insert(ft_main.begin(), ft_pend.at(0));
    std::deque<int> jcb_sque;
    getSequence(ft_pend.size(), jcb_sque);
    insertJcb(jcb_sque, ft_pend, ft_main, tail);
    dq = ft_main;
}

void Wrapp::sortVec(const std::string& input)
{
    struct timeval start;
    struct timeval end;
    double sec;
    double msec;
    checkInput(input);
    std::vector<int> vec;
    recordInput(input, vec);
    std::cout << "\n=========Before sort Vec=================\n";
    std::cout << "Is vector sorted: " << isSorted(vec.begin(), vec.end()) << std::endl;
    std::cout << "Our vector: ";
    printVec(vec);
    std::cout << "===========================\n";
    gettimeofday(&start, NULL);
    sortVecPairs(vec);
    gettimeofday(&end, NULL);
    sec = end.tv_sec - start.tv_sec;
    msec = end.tv_usec - start.tv_usec;
    std::cout << "\n=========After sort Vec=================\n";
    std::cout << "Is vector sorted: " << isSorted(vec.begin(), vec.end()) << std::endl;
    std::cout << "Our vector: ";
    printVec(vec);
    std::cout << "Time to process a range of " << vec.size() << " elements with std::vec is: " << ((sec * 1000000) + msec) / 1000000 << " us" << std::endl;
    std::cout << "===========================\n";
}

void Wrapp::sortDque(const std::string& input)
{
    struct timeval start;
    struct timeval end;
    double sec;
    double msec;
    checkInput(input);
    std::deque<int> dq;
    recordInput(input, dq);
    std::cout << "\n=========Before sort Dque=================\n";
    std::cout << "Is vector sorted: " << isSorted(dq.begin(), dq.end()) << std::endl;
    std::cout << "Our dq: ";
    dqPrint(dq);
    std::cout << "===========================\n";
    gettimeofday(&start, NULL);
    sortDqPairs(dq);
    gettimeofday(&end, NULL);
    sec = end.tv_sec - start.tv_sec;
    msec = end.tv_usec - start.tv_usec;
    std::cout << "\n=========After sort Dque=================\n";
    std::cout << "Is vector sorted: " << isSorted(dq.begin(), dq.end()) << std::endl;
    std::cout << "Our vector: ";
    dqPrint(dq);
    std::cout << "Time to process a range of " << dq.size() << " elements with std::deque is: " << ((sec * 1000000) + msec) / 1000000 << " us" << std::endl;
    std::cout << "===========================\n";
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