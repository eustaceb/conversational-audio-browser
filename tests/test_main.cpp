#include <QtTest>
#include "teststatistics.h"
#include "testdatamodels.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    TestStatistics testStats;
    TestDataModels testDM;
    return QTest::qExec(&testStats, argc, argv)
         | QTest::qExec(&testDM, argc, argv);
}
