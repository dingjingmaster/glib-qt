TEMPLATE                = lib
TARGET                  = glib


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
    $$PWD/../                               \


DEFINES                 += \
    GLIB_COMPILATION


LIBS                    += \
#    -L../gthread                  \
#    -lgthread                               \


include($$PWD/glib.pri)
include($$PWD/libcharset/charset.pri)
include($$PWD/deprecated/deprecated.pri)
