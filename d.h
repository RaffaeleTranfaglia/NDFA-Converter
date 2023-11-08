#include <vector>
#include <set>
#include <unordered_set>

/*
    Attributes of the deterministic automaton, 
    the alphabet is the same of the non-deterministic one
*/
struct Deterministic
{
    std::vector<char> symbols;                     // alphabet
    std::vector<std::set<int>> states;              // states
    std::set<int> f;                                // final states
    std::vector<std::vector<int>> delta;            // transition table
};

void printD(const Deterministic D);
void epsilonClosure (const std::vector<int> v, std::vector<int>** delta, std::set<int>& result);
bool isnew (const std::set<int> closure, const std::vector<std::set<int>> D);
int getDState (const std::set<int> NDstate, const std::vector<std::set<int>> D);
bool isfinal (const std::set<int> closure, const std::unordered_set<int> Nf);