TEMPLATE                = lib
TARGET                  = gobject


QT                      += \
    core                                    \


QMAKE_CXXFLAGS          += \
    -Werror=return-type                     \
    -Werror=unused-label                    \
    -Werror=uninitialized                   \
    -Werror=return-local-addr               \


CONFIG                  += \
    c++11                                   \
    no_keywords                             \
    hide_symbols                            \
    link_pkgconfig                          \


INCLUDEPATH             += \
    $$PWD/../glib                           \
    $$PWD/../                               \


DEFINES                 += \
    GOBJECT_COMPILATION                     \


include($$PWD/gobject.pri)
