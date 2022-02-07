#include <iostream>
#include <fstream>
using namespace std;

int main(){
ofstream myfile;
myfile.open("home1.txt");
myfile<<"HelloWorld!\n" << endl;
myfile.close();
return 0;
}

