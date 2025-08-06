#ifndef DATACONTAINER_TESTS_H
#define DATACONTAINER_TESTS_H

class datacontainer_tests
{
public:
    // Run all DataContainer tests and print a summary
    void run_all_datacontainer_tests();

private:
    bool testGetDataBeforeAny();
    bool testSyncAfterRadarThenCam();
    bool testSyncAfterCamThenRadar();
};

#endif // DATACONTAINER_TESTS_H
