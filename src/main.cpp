
#include <iostream>
#include <string>
#include "Table/Row/Row.h"
#include "Table/Table.h"
#include "Database/Database.h"
#include "Record/RecordInt/RecordInt.h"
#include "Record/RecordDouble/RecordDouble.h"
#include "Tester/Tester.h"

using namespace std;

int main(){

    Tester tester;
    tester.test_load_database();
    tester.test_load_table("test_table1");
    tester.test_import_table("test_table1");
    tester.test_load_table("test_table1");
}

