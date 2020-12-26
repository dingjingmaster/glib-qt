TEMPLATE        = app
TARGET          = test-test.run
QT              += testlib
QT              -= gui

CONFIG          += \
    qt                              \
    console                         \
    warn_on                         \
    testcase                        \
    depend_includepath              \


CONFIG          -= \
    app_bundle


INCLUDEPATH     += \
    $$PWD/../..                     \


LIBS            += \
    -L$$OUT_PWD/../../glib          \
    -lglib                          \


SOURCES         += \
    tst_glibtesttest.cpp
