
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "Record/Record.h"
#include "Record/RecordInt/RecordInt.h"
#include "Record/RecordDouble/RecordDouble.h"
#include "Table/Row/Row.h"

using namespace std;

int main(){

    Row row;
    row.add_record("123");
    row.add_record("123");

    vector <Record*> recs = row.get_records();

    for(int i=0; i<recs.size(); i++){

        Record* rec = recs[i];
        cout << dynamic_cast<RecordInt*>(rec)->get_value() << endl;
    }

    
}

