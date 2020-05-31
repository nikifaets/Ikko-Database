
#include <iostream>
#include <string>
#include "Table/Row/Row.h"
#include "Table/Table.h"

using namespace std;

void test(string read_filename, string write_filename){

    Table table;
    table.read_table(read_filename);
    if(!table.get_rows().size()) return;

    vector<Row> rows = table.get_rows();

    cout << "Rows in Table: " << rows.size() << endl;

    for(int i=0; i<rows.size(); i++){

        string row_string = rows[i].to_string();

        cout << "Row number " << i << endl;
        cout << row_string << endl;
    }
    
    table.save_table(write_filename);

}
int main(){

    
    //Може да създадете собствени таблици и да ги тествате за четене и писане. В главната директория има предварително подготвени файлове "test", "test1", "test2"
   //Засега поддържаните типове са само Int и Double!
   test("../test1", "../test1_o");
   return 0;
}

