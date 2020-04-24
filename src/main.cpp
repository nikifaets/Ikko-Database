
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

    RecordDouble rint("234.52");
    RecordInt();
    Record* rec;
    rec = &rint;
    cout << rint.get_type() << endl;
    cout << rec->get_type() << endl;

    Table table;
    table.read_table("../test_o");
    if(!table.get_rows().size()) return 0;
    vector<Row> rows = table.get_rows();
    cout << rows.size() << endl;
    cout << rows[0].get_records().size() << endl;

    table.save_table("../test_o1");
}

