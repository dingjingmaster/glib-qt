TEMPLATE            = subdirs


SUBDIRS             += \
    test                                    \
    glib                                    \
    gobject                                 \
    gmodule                                 \


#glib.depends        = \
#    gthread                                 \


test.depends        = \
    glib                                    \

OTHER_FILES         += \
    $$PWD/run-test.sh
