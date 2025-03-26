#include <iostream>
#include <cstring>
#include <string>
using namespace std;

int main() {
    char aString[10] = "Hello";
    char anotherString[10] = "Goodbye";

    strcat_s(aString, anotherString);
    int i = 0;
    for (i;i < 10;i++)
        cout << aString[i];
    cout << endl;
    
    for (i=0;i < 10;i++)
        cout << anotherString[i];
    
    return 0;
}
