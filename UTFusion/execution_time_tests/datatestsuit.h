#ifndef DATATESTSUIT_H
#define DATATESTSUIT_H
#include "testsuit.h"
#include "buffer.h"
#include "datacontainer.h"

class DataTestsuit : TestSuit
{
    Buffer buf;
    DataContainer container;
public:
    DataTestsuit();
    void setup();
    void setup_container();
    void setup_buf();

    void test_buffer_isValid();
    void test_container_getData();
    QStringList run_suit();
};

#endif // DATATESTSUIT_H
