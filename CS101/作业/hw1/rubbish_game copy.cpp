#include <queue>
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    int n, m, command;
    int max = 0;
    queue<int> server;
    queue<int> types;
    int monsterCount[2 * 10 ^ 5] = {0};
    int maxCurCount = 0;
    cin >> n;
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> command;
        if (command == 1)
        {
            cin >> m;
            types.push(m);
            for (int j = 0; j < m; j++)
            {
                int val;
                cin >> val;
                server.push(val);
                monsterCount[val - 1]++;
                if (monsterCount[val - 1] == 0)

                    maxCurCount++;
            }
        }
        else if (command == 2)
        {
            int count = server.size();

            if (count >= max)
            {
                max = count;
            }
            cout << max << "\n";

            int times = types.front();
            types.pop();
            for (int i = 0; i < times; i++)
            {
                server.pop();
            }
        }
    }
}