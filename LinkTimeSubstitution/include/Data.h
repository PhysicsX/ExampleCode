#pragma once

class Data {
public:
    virtual int call();
    virtual ~Data() = default; // Add a virtual destructor for good measure

};
