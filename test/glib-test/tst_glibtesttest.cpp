#include <QtTest>

#include "glib/glib.h"

class GLibTestTest : public QObject
{
    Q_OBJECT

public:
    GLibTestTest();
    ~GLibTestTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case_assert();

};

GLibTestTest::GLibTestTest()
{

}

GLibTestTest::~GLibTestTest()
{

}

void GLibTestTest::initTestCase()
{

}

void GLibTestTest::cleanupTestCase()
{

}

void GLibTestTest::test_case_assert ()
{
    g_assert(42 > 0);
}

QTEST_APPLESS_MAIN(GLibTestTest)

#include "tst_glibtesttest.moc"
