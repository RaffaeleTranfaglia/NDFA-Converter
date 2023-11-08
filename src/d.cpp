#include <iostream>
#include "d.h"

using namespace std;

// print deterministic automaton
void printD (const Deterministic D)
{
    for (int i = 0; i < D.states.size(); i++)
    {
        for (int v : D.states[i])
        {
            cout << v << ' ';
        }
        cout << endl;
    }

    for (int v : D.f)
    {
        cout << v << ' ';
    }
    cout << endl;

    for (int i = 0; i < D.delta.size(); i++)
    {
        for (int j = 0; j < D.symbols.size()-1; j++)
        {
            if (D.delta[i][j] != -1)
                cout << D.delta[i][j];
            cout << endl;
        }
    }
}

/*
    Develops the epsilon closure starting from v.
    The result of the operation is stored in result.
    Base case: every element of v has not connections labelled as epsilon
    Recursive case: if an element of v has at least one connection labelled as 
                    epsilon, then epsilonClosure is called on that state
*/
void epsilonClosure (const vector<int> v, vector<int>** delta, set<int>& result)
{
    for (int i : v)
    {
        result.insert(i);
        if (!delta[i][0].empty())
        {
            epsilonClosure(delta[i][0], delta, result);
        }
    }
    return;
}

/*
    Checks whether closure is already contained in D.
    If D doesn't contain closure returns true, otherwise false.
*/
bool isnew (const set<int> closure, const vector<set<int>> D)
{
    for (int z = 0; z < D.size(); z++)
    {
        if (D[z] == closure)
        {
            return false;
        }
    }
    return true;
}

/*
    Returns the deterministic state corresponding to a set of 
    non-deterministic states.
*/
int getDState (const set<int> NDstate, const vector<set<int>> D)
{
    for (int z = 0; z < D.size(); z++)
    {
        if (D[z] == NDstate)
        {
            return z;
        }
    }
    return -1;
}

/*
    Checks whether clousre is a final state in the non-deterministic automaton.
    If it is a final state returns true, otherwise false.
*/
bool isfinal (const set<int> closure, const unordered_set<int> Nf)
{
    for (int i : closure)
    {
        if (Nf.count(i) == 1)
        {
            return true;
        }
    }
    return false;
}