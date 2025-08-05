#ifndef DATATESTSUIT_H
#define DATATESTSUIT_H
#include "testsuit.h"
#include "buffer.h"
#include "datacontainer.h"

class DataTestsuit : TestSuit
{
    Buffer buf;
public:
    DataTestsuit();
    void setup();
    void test_buffer_isValid();
    QStringList run_suit();
};

#endif // DATATESTSUIT_H
