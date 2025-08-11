#ifndef DATACONTAINER_TESTS_H
#define DATACONTAINER_TESTS_H

class datacontainer_tests
{
public:
    
    void run_all_datacontainer_tests();

private:
    bool testGetDataBeforeAny();
    bool testSyncAfterRadarThenCam();
    bool testSyncAfterCamThenRadar();
};

#endif 
