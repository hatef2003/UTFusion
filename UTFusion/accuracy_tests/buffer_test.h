#ifndef BUFFER_TEST_H
#define BUFFER_TEST_H

class buffer_test
{
public:
    // Runs all tests and prints a summary
    void run_all_buffer_tests();

private:
     bool testEmptyReadThrows();
    bool testAddAndReadSync();
    bool testNotSyncBeyondDrift();

};




#endif // BUFFER_TEST_H
