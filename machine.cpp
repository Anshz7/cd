#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Symbol {
string name;
int address;
int value;
};

class MachineCodeGenerator {
private:
map<string, Symbol> symbolTable; // Stores variables and their metadata
int nextAddress = 100; // Tracks the next available memory address
vector<string> instructions; // Stores the generated machine code instructions

// Returns the next available memory address and increments the counter
int getNextAddress() { return nextAddress++; }

// Retrieves a symbol from the symbol table. Throws an error if the symbol
// is not found.
Symbol &getSymbol(const string &name) {
auto it = symbolTable.find(name);
if (it == symbolTable.end())
throw runtime_error("Undefined variable: " + name);
return it->second;
}

// Generates machine code instructions for a basic arithmetic operation
void generateOperation(const string &result, const string &op1,
const string &op2, const string &opCode) {
addVariable(result); // Ensure the result variable exists
int resultAddr = getSymbol(result).address;
int addr1 = getSymbol(op1).address;
int addr2 = getSymbol(op2).address;

instructions.push_back("LOAD " + to_string(addr1));
instructions.push_back(opCode + " " + to_string(addr2));
instructions.push_back("STORE " + to_string(resultAddr));

// Update the symbol table with the result of the operation
if (opCode == "ADD")
symbolTable[result].value =
symbolTable[op1].value + symbolTable[op2].value;
else if (opCode == "SUB")
symbolTable[result].value =
symbolTable[op1].value - symbolTable[op2].value;
}

public:
// Adds a new variable to the symbol table
void addVariable(const string &name) {
if (symbolTable.find(name) == symbolTable.end())
symbolTable[name] = {name, getNextAddress(), 0};
}

// Generates machine code for assigning a constant value to a variable
void generateAssignment(const string &var, int value) {
addVariable(var); // Ensure the variable exists
int address = getSymbol(var).address;
instructions.push_back("LOAD #" + to_string(value));
instructions.push_back("STORE " + to_string(address));
symbolTable[var].value = value; // Update symbol table with assigned value
}

// Generates machine code for adding two variables
void generateAddition(const string &result, const string &op1,
const string &op2) {
generateOperation(result, op1, op2, "ADD");
}

// Generates machine code for subtracting two variables
void generateSubtraction(const string &result, const string &op1,
const string &op2) {
generateOperation(result, op1, op2, "SUB");
}

// Prints the generated machine code instructions
void printGeneratedCode() {
cout << "\nGenerated Machine Code:\n----------------------" << endl;
for (size_t i = 0; i < instructions.size(); i++)
cout << i << ": " << instructions[i] << endl;
}

// Prints the contents of the symbol table
void printSymbolTable() {
cout << "\nSymbol Table:\n-------------" << endl;
cout << "Name\t| Address\t| Value\n---------------------------------"
<< endl;
for (const auto &entry : symbolTable) {
const Symbol &sym = entry.second;
cout << sym.name << "\t| " << sym.address << "\t\t| " << sym.value
<< endl;
}
}
};

int main() {
MachineCodeGenerator generator;
generator.generateAssignment("x", 5); // int x = 5;
generator.generateAssignment("y", 10); // int y = 10;
generator.generateAddition("z", "x", "y"); // int z = x + y;
generator.generateSubtraction("result", "z", "x"); // int result = z - x;
generator.printGeneratedCode();
generator.printSymbolTable();
return 0;
}