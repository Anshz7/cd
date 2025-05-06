#include <iostream>
#include <vector>
using namespace std;

struct Quad {
    string op, arg1, arg2, result;
};

vector<int> makelist(int i) {
    return vector<int>(1, i);
}

vector<int> merge(const vector<int>& l1, const vector<int>& l2) {
    vector<int> result = l1;
    result.insert(result.end(), l2.begin(), l2.end());
    return result;
}

void backpatch(vector<Quad>& quads, const vector<int>& list, int target) {
    for (int i : list)
        quads[i].result = to_string(target);
}

int main() {
    vector<Quad> quads;
    quads.push_back({"if_false", "a<b", "", ""}); // jump to be backpatched
    quads.push_back({"=", "1", "", "x"});
    quads.push_back({"goto", "", "", ""}); // jump to be backpatched
    quads.push_back({"=", "0", "", "x"});

    vector<int> falseList = makelist(0);
    vector<int> nextList = makelist(2);

    backpatch(quads, falseList, 3);
    backpatch(quads, nextList, 4);

    cout << "Quad Table after Backpatching:\n";
    cout << "No\tOp\tArg1\tArg2\tResult\n";
    for (int i = 0; i < quads.size(); ++i)
        cout << i << "\t" << quads[i].op << "\t" << quads[i].arg1 << "\t" << quads[i].arg2 << "\t" << quads[i].result << endl;
    return 0;
}