
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
    //tester.test_import_table("../src/Database/Tables/test_import");
    //tester.test_export_table("Dogs", "../baddogs");
    //tester.test_select_rows("Dogs", 1, new RecordDouble(12.23));
    //tester.test_add_empty_col("Dogs", "NewCol", Type::Int);
    //tester.test_rec_comparison();
    //tester.test_update_rec();
    tester.test_delete_rows();
}

