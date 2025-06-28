#include <queue>
#include <iostream>
#include <vector>

using namespace std;
int main()
{
    int n, m, command;

    deque<pair<int, int>> playerMax;
    int head = 1;
    int tail = 0;
    queue<int> monsters;
    queue<int> playermonster;
    int monsterCount[400000] = {0};
    int maxCurCount = 0;
    cin >> n;
    for (int i = 0; i < 2 * n; i++)
    {
        cin >> command;
        if (command == 1)
        {
            tail++;
            cin >> m;
            playermonster.push(m);
            for (int j = 0; j < m; j++)
            {
                int val;
                cin >> val;
                monsters.push(val);

                if (monsterCount[val - 1] == 0)
                    maxCurCount++;
                monsterCount[val - 1]++;
            }
            while (!playerMax.empty() && playerMax.back().second < maxCurCount)
            {
                playerMax.pop_back();
            }

            playerMax.push_back(make_pair(tail, maxCurCount));
        }
        else if (command == 2)
        {
            head++;
            cout << playerMax.front().second << "\n";
            int count = playermonster.front();
            for (int j = 0; j < count; j++)
            {
                int monstertype = monsters.front();
                monsterCount[monstertype - 1]--;
                monsters.pop();
                if (monsterCount[monstertype - 1] == 0)
                {
                    maxCurCount--;
                }
            }
            playermonster.pop();
            if (playerMax.front().first < head)
            {
                playerMax.pop_front();
            }
        }
    }
}