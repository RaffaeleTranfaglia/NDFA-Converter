#include <vector>
#include <unordered_set>

// Attributes of the non-deterministic automaton
struct nonDeterministic
{
    std::vector<char> symbols = {' '};          // alphabet
    size_t states;                              // number of states
    std::unordered_set<int> f;                  // final states
    std::vector<int>** delta = NULL;            // transition table
};