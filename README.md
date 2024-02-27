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

To convert a non deterministic to a deterministic one:
```
  ./part1 <input_file>
```
Below are showed the format of input and outpu files.

### Input
The non deterministic automaton (**N**) has to be stored in a file using the following representation:
1. **s** is the number of symbols and **k** is the number of states
2. States' names go from **0** to **k-1**.
3. The file must contains **(s+1)\*k+2** lines.
4. The first line contains the **s** symbols of the alphabet, separated by spaces.
5. The second line contains the final states separated by space.
6. The remaining **(s+1)\*k lines** are intended to be seen as **k** groups of **s+1** rows each. The generic, **i**-th, group (**i** = 0, ..., **k**-1) is connected to state **i**. The **j**-th row of each group (**j** = 1, ..., **s**+1 since there is the epsilon-transition) is related to the **j**-th input character (the order of input charactes is the same order in which they appear in the first line). Accordingly, every line contains the list of states reached with the **j**-th input symbol starting from the state **i**. For example, if in state **i**, with the **j**-th symbol as input, the automaton can transit in states **p**, **q** and **r**; the line at index **2+(s+1)\*i+j** will contain **p**, **q** and **r** separated by spaces.

### Output
The representation of the deterministic automaton D (stored in NDFA) resulting from Subset construction must be represented as follows:

## Credits
_Languages and Compilers_ lectures at UniMoRe.
