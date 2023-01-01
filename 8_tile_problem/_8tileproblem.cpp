#include <iostream>
#include <stdio.h>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class _8tileproblemBDS
{
    vector<vector<vector<int>>> path;

public:
    void printState(vector<vector<int>> state)
    {
        for (auto s : state)
        {
            for (auto x : s)
            {
                cout << x << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";
    }

    void printPath()
    {
        for (auto state : path)
        {
            printState(state);
        }
    }

    void getPathfromStart(map<vector<vector<int>>, vector<vector<int>>> parent, vector<vector<int>> currentState, vector<vector<int>> startState)
    {
        if (parent[currentState] == startState)
        {
            path.push_back(parent[currentState]);
            return;
        }
        getPathfromStart(parent, parent[currentState], startState);
        path.push_back(parent[currentState]);
        return;
    }

    void getPathfromGoal(map<vector<vector<int>>, vector<vector<int>>> parent, vector<vector<int>> currentState, vector<vector<int>> goalState)
    {
        if (parent[currentState] == goalState)
        {
            path.push_back(parent[currentState]);
            return;
        }
        path.push_back(parent[currentState]);
        getPathfromGoal(parent, parent[currentState], goalState);
        return;
    }

    // generating next states from the currentState
    vector<vector<vector<int>>> getNextStates(vector<vector<int>> state, int blank_i, int blank_j)
    {
        vector<vector<vector<int>>> nextStates;
        if (blank_i - 1 >= 0)
        {
            int temp = state[blank_i - 1][blank_j];
            state[blank_i - 1][blank_j] = 0;
            state[blank_i][blank_j] = temp;
            nextStates.push_back(state);
            state[blank_i - 1][blank_j] = temp;
            state[blank_i][blank_j] = 0;
        }

        if (blank_j - 1 >= 0)
        {
            int temp = state[blank_i][blank_j - 1];
            state[blank_i][blank_j - 1] = 0;
            state[blank_i][blank_j] = temp;
            nextStates.push_back(state);
            state[blank_i][blank_j - 1] = temp;
            state[blank_i][blank_j] = 0;
        }

        if (blank_i + 1 < 3)
        {
            int temp = state[blank_i + 1][blank_j];
            state[blank_i + 1][blank_j] = 0;
            state[blank_i][blank_j] = temp;
            nextStates.push_back(state);
            state[blank_i + 1][blank_j] = temp;
            state[blank_i][blank_j] = 0;
        }

        if (blank_j + 1 < 3)
        {
            int temp = state[blank_i][blank_j + 1];
            state[blank_i][blank_j + 1] = 0;
            state[blank_i][blank_j] = temp;
            nextStates.push_back(state);
            state[blank_i][blank_j + 1] = temp;
            state[blank_i][blank_j] = 0;
        }
        return nextStates;
    }

    void BidirectionalBFS(vector<vector<int>> startState, vector<vector<int>> goalState)
    {
        //map to store parent information of every state
        // so we can backtrack from intersectionState to start or goal state
        map<vector<vector<int>>, vector<vector<int>>> parent_start, parent_goal;
        queue<vector<vector<int>>> q_start, q_goal;
        //maintaining fringe list for bfs from start node and bfs from end node
        set<vector<vector<int>>> fringe_start, fringe_goal;

        q_start.push(startState);
        q_goal.push(goalState);

        bool flag = 1;
        int depth = 0;
        vector<vector<int>> intersectionState;
        while (!q_start.empty() && !q_goal.empty() && flag)
        {
            int n = q_start.size();
            int m = q_goal.size();

            while (n-- && flag)
            {
                vector<vector<int>> currentState = q_start.front();
                q_start.pop();
                if (fringe_goal.find(currentState) != fringe_goal.end())
                {
                    // intersection of the bfs
                    intersectionState = currentState;
                    cout << "\nGoal state found at depth: " << depth << " using BDS algortihm\n\n";
                    flag = 0;
                    break;
                }
                fringe_start.insert(currentState);

                // getting coordinates for blank
                int blank_i, blank_j;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (currentState[i][j] == 0)
                        {
                            blank_i = i;
                            blank_j = j;
                        }
                    }
                }

                // generating the next states for the current state as parent
                auto nextStates = getNextStates(currentState, blank_i, blank_j);
                for (auto nextState : nextStates)
                {
                    if (fringe_start.find(nextState) == fringe_start.end())
                    {
                        q_start.push(nextState);
                        parent_start[nextState] = currentState;
                    }
                }
            }

            while (m-- && flag)
            {
                vector<vector<int>> currentState = q_goal.front();
                q_goal.pop();
                if (fringe_start.find(currentState) != fringe_start.end())
                {
                    // intersection of th bfs
                    intersectionState = currentState;
                    cout << "\nGoal state found at depth: " << depth << " using BDS algortihm\n\n";
                    flag = 0;
                    break;
                }

                fringe_goal.insert(currentState);

                // getting coordinates for blank
                int blank_i, blank_j;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        if (currentState[i][j] == 0)
                        {
                            blank_i = i;
                            blank_j = j;
                        }
                    }
                }

                // generating the next states for the current state as parent
                auto nextStates = getNextStates(currentState, blank_i, blank_j);
                for (auto nextState : nextStates)
                {
                    if (fringe_goal.find(nextState) == fringe_goal.end())
                    {
                        q_goal.push(nextState);
                        parent_goal[nextState] = currentState;
                    }
                }
            }
            depth++;
        }

        // generating the path from intersection state to start state
        getPathfromStart(parent_start, intersectionState, startState);
        // pushing the intersection state to the path array
        path.push_back(intersectionState);

        // generating path from the intersection to goal state
        getPathfromGoal(parent_goal, intersectionState, goalState);

        // printing the generated path.
        //  printPath();
    }

};

class _8tileproblemIDS
{
    set<vector<vector<int>>> expandedList;
    int depth_limit;

public:
    //printing states
    void printState(vector<vector<int>> state)
    {
        for (auto x : state)
        {
            for (auto y : x)
            {
                cout << y << " ";
            }
            cout << "\n";
        }
        cout << "\n\n\n";
    }

    // depth first search based on depth limit
    bool dfs(vector<vector<int>> current, vector<vector<int>> goal, int depth, vector<vector<vector<int>>> path)
    {
        path.push_back(current);
        //checking if we reached goal state
        if (current == goal)
        {
            cout << "\nGoal state found at depth: " << depth_limit << " using IDS algortihm\n";
            cout << "\n------IDS Steps-------\n";
            printPath(path);
            return true;
        }
        else if (depth == depth_limit) //checking if depth limit is reached
        {
            return false;
        }
        depth++;

        // dfs for depth d
        //getting coordinates for blank tile
        int blank_i, blank_j;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (current[i][j] == 0)
                {
                    blank_i = i;
                    blank_j = j;
                }
            }
        }
        //inserting currentState in expandedList which is basically storing the visited states
        expandedList.insert(current);
        int temp;
        bool ans = false;
        if (blank_i - 1 >= 0)
        {
            temp = current[blank_i - 1][blank_j];
            current[blank_i - 1][blank_j] = 0;
            current[blank_i][blank_j] = temp;
            
            // if new state is not visited then call dfs on that state
            if (expandedList.find(current) == expandedList.end())
            {
                ans = dfs(current, goal, depth, path);
                if (ans)
                {
                    return true;
                }
            }
            // getting the currentState back from the child state
            current[blank_i - 1][blank_j] = temp;
            current[blank_i][blank_j] = 0;
        }

        if (blank_j - 1 >= 0)
        {
            temp = current[blank_i][blank_j - 1];
            current[blank_i][blank_j - 1] = 0;
            current[blank_i][blank_j] = temp;
            if (expandedList.find(current) == expandedList.end())
            {
                ans = dfs(current, goal, depth, path);
                if (ans)
                {
                    return true;
                }
            }
            current[blank_i][blank_j - 1] = temp;
            current[blank_i][blank_j] = 0;
        }

        if (blank_i + 1 < 3)
        {
            temp = current[blank_i + 1][blank_j];
            current[blank_i + 1][blank_j] = 0;
            current[blank_i][blank_j] = temp;
            if (expandedList.find(current) == expandedList.end())
            {
                ans = dfs(current, goal, depth, path);
                if (ans)
                {
                    return true;
                }
            }
            current[blank_i + 1][blank_j] = temp;
            current[blank_i][blank_j] = 0;
        }

        if (blank_j + 1 < 3)
        {
            temp = current[blank_i][blank_j + 1];
            current[blank_i][blank_j + 1] = 0;
            current[blank_i][blank_j] = temp;
            if (expandedList.find(current) == expandedList.end())
            {
                ans = dfs(current, goal, depth, path);
                if (ans)
                {
                    return true;
                }
            }
            current[blank_i][blank_j + 1] = temp;
            current[blank_i][blank_j] = 0;
        }

        return ans;
    }

//IDS function
    void IDS(vector<vector<int>> current, vector<vector<int>> goal)
    {
        //initalizing depth_limit by 0
        depth_limit = 0;
        // runnning an infinite loop to go from depth 0 to infinite till we get the answer
        while (true)
        {
            vector<vector<vector<int>>> path; //to store the path 
            expandedList.clear();// cleared the visited list before starting a new df
            bool ans = dfs(current, goal, 0, path);
            if (ans)
            {
                return;
            }
            depth_limit++;
        }
    }

    // function to print path
    void printPath(vector<vector<vector<int>>> path)
    {
        for (auto state : path)
        {
            printState(state);
        }
    }
};

//to check if the give start state is a solvable 8 tile problem 
bool isSolvable(vector<vector<int>> startState){
    
    vector<int> grid_flatten;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            grid_flatten.push_back(startState[i][j]);
    
    // 2 tiles form an inversion 
    // if the values are in reverse order of that in the goal state
    int inverse_count = 0, i, j;
    for (i=0; i<8; i++)
        for (j=i+1; j<9; j++)
             if (grid_flatten[j] && grid_flatten[i] &&  grid_flatten[i] > grid_flatten[j])
                  inverse_count++;
    if(inverse_count % 2 == 0)
        return true;
    else 
        return false;
}

int main()
{
    vector<vector<int>> goalState;
    vector<vector<int>> startState;
    goalState = {{1, 2, 3},{4, 5, 6},{7, 8, 0}};
    
    // startState= {{1, 2, 3},{4, 5, 6},{0, 7, 8}}; // depth=2
    // startState = {{1, 0, 2}, {4, 6, 3}, {7, 5, 8}}; // depth= 5
    startState = {{4, 1, 2}, {7, 0, 3}, {8, 5, 6}}; // depth=8
    
    // startState = {{7, 4, 0},{2, 6, 3},{1, 5, 8}}; // depth=18

    // startState = {{8,1,2},{0,4,3},{7,6,5}}; // unsolvable
    
    //checking if given grid is solvable 8tile
    if(!isSolvable(startState)){
        cout<<"Given grid is not a solvable 8 tile problem\n";
        return 0;
    }

    // IDS
    // _8tileproblemIDS p1;
    
    // p1.IDS(startState, goalState);

    // BDS 
    _8tileproblemBDS p2;

    p2.BidirectionalBFS(startState, goalState);
    cout << "\n\n------Bidirectional BFS Steps-------\n";
    p2.printPath();

    
    cout << "-------EXPECTED GOAL STATE-------\n";
    for (auto s : goalState)
        {
            for (auto x : s)
            {
                cout << x << " ";
            }
            cout << "\n";
        }
        cout << "\n\n";

    return 0;
}

