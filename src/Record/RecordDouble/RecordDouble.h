#include "../Record.h"

class RecordDouble : public Record{

    Type type = Double;
    double value = 0;

    public:

    RecordDouble(std::string val);
    RecordDouble();
    void parse(std::string value);
    double get_value();
    std::string to_string();
    Type get_type();
};