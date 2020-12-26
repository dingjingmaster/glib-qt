TEMPLATE        = app
TARGET          = test-completion.run
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
    tst_glibcompetion.cpp

