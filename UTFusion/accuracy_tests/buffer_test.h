#ifndef BUFFER_TEST_H
#define BUFFER_TEST_H

class buffer_test
{
public:
    
    void run_all_buffer_tests();

private:
     bool testEmptyReadThrows();
    bool testAddAndReadSync();
    bool testNotSyncBeyondDrift();

};




#endif 
