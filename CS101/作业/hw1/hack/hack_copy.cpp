#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

const int N = 100000; // 数组长度 n = 10^5
std::mt19937 engine;

void switchRandom2(int first, int last, std::vector<int> &arr, std::mt19937 &engine, int &num)
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
    int random = first + pos;
    arr[random] = num++;
    std::swap(arr[first], arr[random]);

    switchRandom2(first + 1, last, arr, engine, num);
    std::swap(arr[first], arr[random]);
};
void switchRandom3(int first, int last, std::vector<int> &arr, std::mt19937 &engine, int &num)
{
    int n = last - first;
    if (n < 4) // 对小数组直接填充
    {
        for (int i = 0; i < 2; i++)
        {
            arr[first + i] = num++;
        }
        return;
    }
    /*if (n <= 1)
    {
        return; // 当只剩下一个元素时直接返回
    }*/

    int pos1 = std::uniform_int_distribution<>(0, n - 1)(engine);
    int pos2 = std::uniform_int_distribution<>(0, n - 2)(engine);
    int pos3 = std::uniform_int_distribution<>(0, n - 3)(engine);
    pos3 += pos3 >= pos2;
    pos3 += pos3 >= pos1;
    pos2 += pos2 >= pos1;
    int random1 = first + pos1;
    int random2 = first + pos2;

    arr[random1] = num++;
    arr[random2] = num++;

    std::swap(arr[first], arr[random2]);

    std::swap(arr[first + 1], arr[random1]);
    std::swap(arr[first + 1], arr[first]);
    // switchRandom3(first, first + 1, arr, engine, num);
    switchRandom3(first + 2, last, arr, engine, num); // 递归处理剩余部分
    std::swap(arr[first + 1], arr[first]);

    std::swap(arr[first + 1], arr[random1]);
    std::swap(arr[first], arr[random2]);
}

void generate_worst_case_array(std::vector<int> &arr, int pivotStrategy)
{

    if (pivotStrategy == 1)
    {
        for (int i = 0; i < N; ++i)
            arr[i] = i + 1;
    }
    else if (pivotStrategy == 2)
    {
        int num = 0;
        switchRandom2(0, N, arr, engine, num);
    }
    else if (pivotStrategy == 3)
    {
        int num = 0;
        switchRandom3(0, N, arr, engine, num);
    }
}

int main()
{
    int pivotStrategy, seed;
    std::cin >> pivotStrategy >> seed;
    engine.seed(seed);
    std::vector<int> arr(N);
    generate_worst_case_array(arr, pivotStrategy);

    for (const int &num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}