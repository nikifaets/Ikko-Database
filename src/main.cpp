
#include <iostream>
#include <fstream>
#include <string>
#include "Record/Record.h"
#include "Record/RecordInt/RecordInt.h"
#include "Record/RecordDouble/RecordDouble.h"
#include "Table/Row/Row.h"
#include "Table/Table.h"

using namespace std;

int main(){

    Table table;
    table.read_table("../test_o");
    if(!table.get_rows().size()) return 0;
    vector<Row> rows = table.get_rows();
    cout << rows.size() << endl;
    cout << rows[0].get_records().size() << endl;

    table.save_table("../test_o1");

    /*RecordInt rint("123");
    Record* rec;
    rec = &rint;
    rec->set_empty(true);
    cout << rec->is_empty();*/
}

