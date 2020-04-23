#include "../Record.h"

class RecordDouble : private Record{

    const std::string name = "Double";
    double value;

    public:

    void parse(std::string value);
    double get_value();
};