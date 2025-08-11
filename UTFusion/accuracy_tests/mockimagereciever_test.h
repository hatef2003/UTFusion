#ifndef MOCKIMAGERECIEVER_TEST_H
#define MOCKIMAGERECIEVER_TEST_H


#include <QObject>

class mockimagereciever_test : public QObject {
    Q_OBJECT
public:
    void run_all_mockimagereciever_tests();

private slots:

    bool testIgnoreIncompletePacket();
};
#endif 
