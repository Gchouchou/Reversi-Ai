#include "interface.h"

#include <iostream>

using namespace reversi;
using namespace std;

int main(int argc, char const *argv[])
{
    gui *a = new gui();
    while(a->input())
    ;
    delete(a);
    
}
