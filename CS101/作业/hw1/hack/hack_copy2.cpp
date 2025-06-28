#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

const int N = 100000; // 数组长度 n = 10^5
std::mt19937 engine;

void switchRandom2(int *first, int *last, std::mt19937 &engine, int &num)
{
    int n = last - first;
    if (first == last)
    {
        return;
    }
    /*if (last - first <= 5)
    {
        for (int i = 0; i < n; i++)
        {
            arr[i + first] = num++;
            return;
        }
    }*/
    std::uniform_int_distribution<> dist(0, n - 1);
    int pos = dist(engine);
    int *random = first + pos;
    *random = num++;
    std::swap(*first, *random);

    switchRandom2(first + 1, last, engine, num);
    std::swap(*first, *random);
};
void switchRandom3(int *first, int *last, std::mt19937 &engine, int &num)
{
    int n = last - first;

    if (n <= 5) // 对小数组直接填充
    {
        for (auto it = first; it < last; it++)
        {
            *it = num++;
        }
        return;
    }

    int pos1 = std::uniform_int_distribution<>(0, n - 1)(engine);
    int pos2 = std::uniform_int_distribution<>(0, n - 2)(engine);
    int pos3 = std::uniform_int_distribution<>(0, n - 3)(engine);
    pos3 += pos3 >= pos2;
    pos3 += pos3 >= pos1;
    pos2 += pos2 >= pos1;
    int *random1 = first + pos1;
    int *random2 = first + pos2;

    std::swap(*first, *random2);
    std::swap(*(first + 1), *random1);
    // std::swap(*(first + 1), *first);
    switchRandom3(first, first + 1, engine, num);
    switchRandom3(first + 2, last, engine, num); // 递归处理剩余部分
    // std::swap(*(first + 1), *first);
    std::swap(*(first + 1), *random1);
    std::swap(*first, *random2);
}

void generate_worst_case_array(int *arr, int pivotStrategy)
{

    if (pivotStrategy == 1)
    {
        for (int i = 0; i < N; ++i)
            arr[i] = i + 1;
    }
    else if (pivotStrategy == 2)
    {
        int num = 0;
        switchRandom2(arr, arr + N, engine, num);
    }
    else if (pivotStrategy == 3)

    {
        int num = 0;
        switchRandom3(arr, arr + N, engine, num);
    }
}

int main()
{
    int pivotStrategy, seed;
    std::cin >> pivotStrategy >> seed;
    engine.seed(seed);
    int arr[N];
    for (int i = 0; i < N; ++i)
    {
        arr[i] = -1;
    }
    generate_worst_case_array(arr, pivotStrategy);

    for (const int &num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}