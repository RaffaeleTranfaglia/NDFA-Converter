#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include "nd.h"
#include "d.h"

using namespace std;

int main (int argc, char** argv)
{
    if (argc > 1)
    {
        nonDeterministic N = {};

        // opens input file and make opening check
        ifstream fin(argv[1]);
        if (!fin)
        {
            cerr << "File opening failed" << endl;
            return 1;
        }

        // reads and stores the alphabet symbols
        char c;
        while(fin.peek() != '\n')
        {
            if (fin.peek() == ' ')
            {
                fin.ignore();
            }
            else
            {
                c = fin.get();
                N.symbols.push_back(c);
            }
        }
        fin.ignore();

        /*
            Associates another ifstream to the same input file in order to
            count the lines.
            This procedure is needed to get the number of states.
        */
        ifstream f(argv[1]);
        if (!f)
        {
            cerr << "File opening failed" << endl;
            return 1;
        }

        // computes the number of states
        size_t number_of_lines = 0;
        string str;
        while (getline(f, str))
            ++number_of_lines;
        N.states = (number_of_lines - 2) / N.symbols.size();

        f.close();

        // reads and stores final states
        fin >> noskipws;
        int n;
        while(fin.peek() != '\n')
        {
            if (fin.peek() == ' ')
            {
                fin.ignore();
            }
            else
            {
                fin >> n;
                N.f.insert(n);
            }
        }
        fin.ignore();

        // reads and stores N.delta table
        N.delta = new vector<int>*[N.states];
        for (int i = 0; i < N.states; i++)
        {
            N.delta[i] = new vector<int>[N.symbols.size()];
            for (int j = 0; j < N.symbols.size(); j++)
            {
                while(fin.peek() != '\n')
                {
                    if (fin.peek() == ' ')
                    {
                        fin.ignore();
                    }
                    else
                    {
                        fin >> n;
                        N.delta[i][j].push_back(n);
                    }
                }
                fin.ignore();
            }
        }

        fin.close();

        // SUBSET CONSTRUCTION
        Deterministic D = {};
        D.symbols = N.symbols;
        queue<set<int>> q;                      // states not yet examined

        // initialises D.delta and closure in order to begin by state 0
        D.delta.push_back(vector<int>(D.symbols.size()-1, -1));
        set<int> closure = {0};
        set<int> state;                         // analyzed deterministic state

        /*
            The first set examined is composed by just 0 (non-deterministic 
            first state). Accordingly, as the first thing it executes 
            epsilonClosure on the state in order to include any 
            epsilon-transition.
        */
        epsilonClosure(N.delta[0][0], N.delta, closure);
        D.states.push_back(closure);
        if (isfinal(closure, N.f))
        {
            D.f.insert(getDState(closure, D.states));
        }
        q.push(closure);
        closure.clear();
        /*
            Now q contains the deterministic state 0 and the algorithim may 
            start.
        */
        while (!q.empty())
        {
            state = q.front();
            for (int j = 1; j < D.symbols.size(); j++)
            {
                for (int i : state)
                {
                    for (int x : N.delta[i][j])
                    {
                        closure.insert(x);
                    }
                    epsilonClosure(N.delta[i][j], N.delta, closure);
                }
                
                /*
                    If the new set is not contained in deterministic states then 
                    it is inserted in D.states and eventually in the queue, in 
                    order to be examined in the future.
                */
                if (!closure.empty() && isnew(closure, D.states))
                {
                    D.states.push_back(closure);
                    /*
                        Initializes the vector elements with -1.
                        This value represents the absence of information.
                    */
                    D.delta.push_back(vector<int>(D.symbols.size()-1, -1));
                    D.delta[getDState(state, D.states)][j-1] = D.states.size()-1;
                    if (isfinal(closure, N.f))
                    {
                        D.f.insert(getDState(closure, D.states));
                    }
                    q.push(closure);
                }
                else
                {
                    D.delta[getDState(state, D.states)][j-1] = getDState(closure, D.states);
                }
                closure.clear();
            }
            q.pop();
        }

        printD(D);
        
        // deallocates dynamic vector N.delta
        for (int i = 0; i < N.states; i++)
        {
            delete[] N.delta[i];
        }
        delete[] N.delta;

        return 0;
    }
    else
    {
        cerr << "Missing argument" << endl;
        return 1;
    }
}