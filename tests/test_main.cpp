#include <QtTest>
#include "testdatamodels.h"
#include "teststatistics.h"
#include "testhelpers.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);

    TestDataModels testDM;
    TestHelpers testHelpers;
    TestStatistics testStats;

    return QTest::qExec(&testDM, argc, argv)
         | QTest::qExec(&testHelpers, argc, argv)
         | QTest::qExec(&testStats, argc, argv);
}
