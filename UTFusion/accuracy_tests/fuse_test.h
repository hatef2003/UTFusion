#ifndef FUSE_TEST_H
#define FUSE_TEST_H


class fuse_test {
public:
    void run_all_fuse_tests();

private:

    bool testOperationDoneOnce(); 
    bool testOperationDoneTwice();
};

#endif 
