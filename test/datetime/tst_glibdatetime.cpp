#include <QtTest>

#include <locale.h>
#include "glib/glib.h"

class GLibDatetime : public QObject
{
    Q_OBJECT

public:
    GLibDatetime();
    ~GLibDatetime();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

GLibDatetime::GLibDatetime()
{

}

GLibDatetime::~GLibDatetime()
{

}

void GLibDatetime::initTestCase()
{

}

void GLibDatetime::cleanupTestCase()
{

}

void GLibDatetime::test_case1()
{
    gchar *fmt = "%x %X";
    GDateTime *dt;
    gchar *str;

    setlocale (LC_ALL, "");

    dt = g_date_time_new_now_local ();
    str = g_date_time_format (dt, fmt);
    QWARN (str);
    g_free (str);
    g_date_time_unref (dt);

}

QTEST_APPLESS_MAIN(GLibDatetime)

#include "tst_glibdatetime.moc"
