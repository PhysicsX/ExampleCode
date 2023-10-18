#include "Data.h"

class Example {
    Data data;

public:
    int foo() {
        return data.call();
    }
};
