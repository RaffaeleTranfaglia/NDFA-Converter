# NDFA-Converter
Tool for converting a non deterministic finite automaton to a deterministic one.

## Installation
Download the source code:  
```
  git clone https://github.com/RaffaeleTranfaglia/NDFA-Converter.git
```
Compile the source code:  
```
  cd src
  make
```

## Usage
To convert a non deterministic automaton to a deterministic one:
```
  ./part1 <input_file>
```
To redirect the output in a text file:  
```
  ./part1 <input_file> > <file_name>
```
Below are showed the format of the input file and the output (displayed in standard output).  

### Input
The non deterministic automaton (**N**) has to be stored in a file using the following representation:
1. **s** is the number of symbols and **k** is the number of states
2. States' names go from **0** to **k-1**.
3. The file must contains **(s+1)\*k+2** lines.
4. The first line contains the **s** symbols of the alphabet, separated by spaces.
5. The second line contains the final states separated by space.
6. The remaining **(s+1)\*k lines** are intended to be seen as **k** groups of **s+1** rows each. The generic, **i**-th, group (**i** = 0, ..., **k**-1) is connected to state **i**. The **j**-th row of each group (**j** = 1, ..., **s**+1 since there is the epsilon-transition) is related to the **j**-th input character (the order of input charactes is the same order in which they appear in the first line). Accordingly, every line contains the list of states reached with the **j**-th input symbol starting from the state **i**. For example, if in state **i**, with the **j**-th symbol as input, the automaton can transit in states **p**, **q** and **r**; the line at index **2+(s+1)\*i+j** will contain **p**, **q** and **r** separated by spaces.

Example of a non deterministic finite automaton (with its representation in `examples/NDFA-2.txt`):
![ndfa.png](/footage/ndfa.png)

### Output
The representation of the deterministic automaton **D** resulting from Subset construction is represented as follows:
1. If **D** has **h** states, the first **h** rows contain its definitions (in term of states of **N**): the first row for state 0 (initial state), the second for state 1 and so on.
2. The row at index **h+1** contains the list of final states of **D**.
3. The subsequent **h*s** rows contain the definition of the transition function as for the input (obviously, since D is deterministic, the non empty rows contain only one state).

Deterministic finite automaton obtained from the previous example (with its representation in `examples/`):


## Credits
_Languages and Compilers_ lectures at UniMoRe.
