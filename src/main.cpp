
#include <iostream>
#include <string>
#include "Table/Row/Row.h"
#include "Table/Table.h"
#include "Database/Database.h"
#include "Record/RecordInt/RecordInt.h"

using namespace std;

void test(string read_filename, string write_filename){


    Table table("gege1");
    table.read_table("../test1_o");

    RecordInt rec("15");

    table.find_rows_by_value(0, &rec);
    


}
int main(){

    test("hui", "hui");
}

