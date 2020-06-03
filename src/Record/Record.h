#pragma once
#include <string>

enum Type{Int, Double, String, Null, Invalid};

const std::string NULL_REC = "Null";

class Record{


    protected:

    Type type = Invalid;
    bool empty = false;

    public:

    virtual void parse(std::string value) = 0;
    virtual bool is_empty();
    virtual void set_empty(bool empty);
    virtual std::string to_string() = 0;

    //template<typename T>
    //virtual T get_value() = 0;
    virtual Type get_type() const;

    
    //virtual bool operator==(const Record& other) const = 0;

};