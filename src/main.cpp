
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Record/Record.h"
#include "Record/RecordInt/RecordInt.h"
#include "Record/RecordDouble/RecordDouble.h"
#include "Table/Row/Row.h"
#include "Table/Table.h"

using namespace std;

int main(){

    


    Table table;
    table.read_table("../test");
    vector<Row> rows = table.get_rows();
    cout << rows.size() << endl;
    cout << rows[0].get_records().size() << endl;

    table.save_table("../test_o");
}

