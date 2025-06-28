#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

const int N = 100000; // 数组长度 n = 10^5
std::mt19937 engine;

void switchRandom2(int first, int last, std::vector<int> &arr, int &num)
{
    if (first == last)
    {
        return;
    }

    int n = last - first;
    std::uniform_int_distribution<> dist(0, n - 1);
    int pos = dist(engine);
    int random = first + pos;
    arr[random] = num++;
    std::swap(arr[first], arr[random]);
    switchRandom2(first + 1, last, arr, num);
    std::swap(arr[first], arr[random]);
};
void switchRandom3(int first, int last, std::vector<int> arr, int num)
{
    int n = last - first;
    if (last < first)
    {
        return;
    }
    if (n < 4) // 对小数组直接填充
    {
        for (int i = 0; i < 2; i++)
        {
            arr[first + i] = num++;
        }
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
    std::uniform_int_distribution<> dist1(0, n - 1);
    int pos1 = dist1(engine);
    std::uniform_int_distribution<> dist2(0, n - 2);
    int pos2 = dist2(engine);
    std::uniform_int_distribution<> dist3(0, n - 3);
    int pos3 = dist3(engine);
    pos3 += pos3 >= pos2;
    pos3 += pos3 >= pos1;
    pos2 += pos2 >= pos1;

    // the median first+pos2 is the pivot
    int random3 = first + pos3;
    int random1 = first + pos1;
    int random2 = first + pos2;
    if (arr[random2] < arr[random1])
        std::swap(random2, random1);
    if (arr[random3] < arr[random2])
        std::swap(pos3, pos2);
    if (arr[random2] < arr[random1])
        std::swap(pos2, pos1);
    arr[random1] = num++;
    arr[random2] = num++;
    std::swap(arr[first], arr[random2]);
    std::swap(arr[first + 1], arr[random1]);
    std::swap(arr[first], arr[first + 1]);
    switchRandom3(first + 2, last, arr, num);
    std::swap(arr[first], arr[first + 1]);
    std::swap(arr[first], arr[random2]);
    std::swap(arr[first + 1], arr[random1]);
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
        switchRandom2(0, N, arr, num);
    }
    else if (pivotStrategy == 3)
    {
        int num = 0;
        switchRandom3(0, N, arr, num);
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