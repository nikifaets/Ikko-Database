
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Record/RecordInt/RecordInt.h"
#include "Record/RecordDouble/RecordDouble.h"

using namespace std;

int main(){

    
    RecordInt r_int;
    r_int.parse("123");

    RecordDouble r_double;
    r_double.parse("234.324");

    cout << r_int.get_value() << endl;
    cout << r_double.get_value() << endl;
}

