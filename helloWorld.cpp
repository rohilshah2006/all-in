#include <iostream>
using namespace std;

int testMethod() {
    int i = 3;
    int j = 3;
    if (i == j)
        return i;
    else
        return 0;
}

int main () {
    cout << "hello world" << endl;
    cout << "!" << endl;
    cout << "hi " <<endl;
    cout << "is it working" << endl;
    cout << testMethod() << endl;
}

