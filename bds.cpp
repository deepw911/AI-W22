#include <bits/stdc++.h>
using namespace std;

class _8tileproblem
{

    vector<vector<vector<int>>> path;

public:
    void BidirectionalBFS(vector<vector<int>> current, vector<vector<int>> goal)
    {
        queue<vector<vector<int>>> q_start, q_goal;
        q_start.push(current);
        q_goal.push(goal);

        set<vector<vector<int>>> fringe;
        // fringe.insert(current);
        // fringe.insert(goal);

        bool flag=0;
        while (!q_start.empty() && !q_goal.empty())
        {
            int n = q_start.size();
            int m = q_goal.size();
            while (n-- && flag==0)
            {
                vector<vector<int>> state = q_start.front();
                q_start.pop();
                if (fringe.find(state) != fringe.end())
                {
                    // we met
                }
                fringe.insert(state);
                // insert child of state
                int blank_i, blank_j;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (state[i][j] == 0)
                        {
                            blank_i = i;
                            blank_j = j;
                        }
                    }
                }
                if (blank_i - 1 >= 0)
                {
                    int temp = state[blank_i - 1][blank_j];
                    state[blank_i - 1][blank_j] = 0;
                    state[blank_i][blank_j] = temp;
                    q_start.push(state);
                    state[blank_i - 1][blank_j] = temp;
                    state[blank_i][blank_j] = 0;
                }

                if (blank_j - 1 >= 0)
                {
                    int temp = state[blank_i][blank_j - 1];
                    state[blank_i][blank_j - 1] = 0;
                    state[blank_i][blank_j] = temp;
                    q_start.push(state);
                    state[blank_i][blank_j - 1] = temp;
                    state[blank_i][blank_j] = 0;
                }

                if (blank_i + 1 < 3)
                {
                    int temp = state[blank_i + 1][blank_j];
                    state[blank_i + 1][blank_j] = 0;
                    state[blank_i][blank_j] = temp;
                    q_start.push(state);
                    state[blank_i + 1][blank_j] = temp;
                    state[blank_i][blank_j] = 0;
                }

                if (blank_j + 1 < 3)
                {
                    int temp = state[blank_i][blank_j + 1];
                    state[blank_i][blank_j + 1] = 0;
                    state[blank_i][blank_j] = temp;
                    q_start.push(state);
                    state[blank_i][blank_j + 1] = temp;
                    state[blank_i][blank_j] = 0;
                }
            }

            while (m-- && flag)
            {
                vector<vector<int>> state = q_goal.front();
                q_goal.pop();
                if (fringe.find(state) != fringe.end())
                {
                    // we met
                }
                fringe.insert(state);
                // insert child of state
                int blank_i, blank_j;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (state[i][j] == 0)
                        {
                            blank_i = i;
                            blank_j = j;
                        }
                    }
                }
                if (blank_i - 1 >= 0)
                {
                    int temp = state[blank_i - 1][blank_j];
                    state[blank_i - 1][blank_j] = 0;
                    state[blank_i][blank_j] = temp;
                    q_goal.push(state);
                    state[blank_i - 1][blank_j] = temp;
                    state[blank_i][blank_j] = 0;
                }

                if (blank_j - 1 >= 0)
                {
                    int temp = state[blank_i][blank_j - 1];
                    state[blank_i][blank_j - 1] = 0;
                    state[blank_i][blank_j] = temp;
                    q_goal.push(state);
                    state[blank_i][blank_j - 1] = temp;
                    state[blank_i][blank_j] = 0;
                }

                if (blank_i + 1 < 3)
                {
                    int temp = state[blank_i + 1][blank_j];
                    state[blank_i + 1][blank_j] = 0;
                    state[blank_i][blank_j] = temp;
                    q_goal.push(state);
                    state[blank_i + 1][blank_j] = temp;
                    state[blank_i][blank_j] = 0;
                }

                if (blank_j + 1 < 3)
                {
                    int temp = state[blank_i][blank_j + 1];
                    state[blank_i][blank_j + 1] = 0;
                    state[blank_i][blank_j] = temp;
                    q_goal.push(state);
                    state[blank_i][blank_j + 1] = temp;
                    state[blank_i][blank_j] = 0;
                }
            }
        
            flag^=1;
        }
    }
};

int main()
{
    vector<vector<int>> goal = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}};
    vector<vector<int>> startState = {
        {7, 4, 0},
        {2, 6, 3},
        {1, 5, 8}};
    _8tileproblem p1;

    p1.BidirectionalBFS(startState, goal);
    return 0;
}