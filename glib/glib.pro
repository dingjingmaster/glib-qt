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


HEADERS                 += \
    gmem.h                                  \
    glib.h                                  \
    gdir.h                                  \
    guri.h                                  \
    gpoll.h                                 \
    gnode.h                                 \
    gdate.h                                 \
    grand.h                                 \
    ghook.h                                 \
    ghash.h                                 \
    ghmac.h                                 \
    glist.h                                 \
    gmain.h                                 \
    gi18n.h                                 \
    gtree.h                                 \
    guuid.h                                 \
    gslist.h                                \
    grcbox.h                                \
    garray.h                                \
    gtypes.h                                \
    gquark.h                                \
    gqueue.h                                \
    gstdio.h                                \
    gregex.h                                \
    gerror.h                                \
    gwin32.h                                \
    gshell.h                                \
    gtimer.h                                \
    gqsort.h                                \
    gspawn.h                                \
    gutils.h                                \
    gbytes.h                                \
    gslice.h                                \
    gbase64.h                               \
    gthread.h                               \
    gmacros.h                               \
    gwakeup.h                               \
    goption.h                               \
    gmarkup.h                               \
    galloca.h                               \
    gstring.h                               \
    gatomic.h                               \
    gprimes.h                               \
    gprintf.h                               \
    gunicode.h                              \
    gconvert.h                              \
    gdataset.h                              \
    gkeyfile.h                              \
    genviron.h                              \
    gvariant.h                              \
    gversion.h                              \
    glibintl.h                              \
    gscanner.h                              \
    gbitlock.h                              \
    gpattern.h                              \
    gunicomp.h                              \
    ggettext.h                              \
    valgrind.h                              \
    gcharset.h                              \
    glib-unix.h                             \
    gtimezone.h                             \
    gdatetime.h                             \
    gsequence.h                             \
    gvalgrind.h                             \
    gchecksum.h                             \
    gi18n-lib.h                             \
    gstrfuncs.h                             \
    gunibreak.h                             \
    glib-init.h                             \
    gprintfint.h                            \
    glib_trace.h                            \
    gfileutils.h                            \
    giochannel.h                            \
    grefstring.h                            \
    ghostutils.h                            \
    gbacktrace.h                            \
    gunidecomp.h                            \
    gtestutils.h                            \
    glib-object.h                           \
    guriprivate.h                           \
    gtrashstack.h                           \
    gthreadpool.h                           \
    gasyncqueue.h                           \
    gmappedfile.h                           \
    gscripttable.h                          \
    glib-private.h                          \
    gstrvbuilder.h                          \
    gstringchunk.h                          \
    gconstructor.h                          \
    gvarianttype.h                          \
    gutilsprivate.h                         \
    gbsearcharray.h                         \
    gstdioprivate.h                         \
    gvariant-core.h                         \
    grcboxprivate.h                         \
    gbookmarkfile.h                         \
    gthreadprivate.h                        \
    gunichartables.h                        \
    gversionmacros.h                        \
    gtranslit-data.h                        \
    gspawn-private.h                        \
    gmain-internal.h                        \
    gtrace-private.h                        \
    gdatasetprivate.h                       \
    gmirroringtable.h                       \
    gunicodeprivate.h                       \
    gcharsetprivate.h                       \
    gvarianttypeinfo.h                      \
    gvariant-internal.h                     \
    glib-autocleanups.h                     \
    gasyncqueueprivate.h                    \
    gvariant-serialiser.h                   \


SOURCES                     += \
    gmem.c                                  \
    gdir.c                                  \
    guri.c                                  \
    gpoll.c                                 \
    gnode.c                                 \
    gdate.c                                 \
    grand.c                                 \
    ghook.c                                 \
    ghash.c                                 \
    ghmac.c                                 \
    glist.c                                 \
    gmain.c                                 \
    gtree.c                                 \
    guuid.c                                 \
    gslist.c                                \
    grcbox.c                                \
    garray.c                                \
    gquark.c                                \
    gqueue.c                                \
    gstdio.c                                \
    gregex.c                                \
    gerror.c                                \
    gshell.c                                \
    gtimer.c                                \
    gqsort.c                                \
    gspawn.c                                \
    gutils.c                                \
    gbytes.c                                \
    gslice.c                                \
    gbase64.c                               \
    gthread.c                               \
    gwakeup.c                               \
    goption.c                               \
    gmarkup.c                               \
    gstring.c                               \
    gatomic.c                               \
    gprimes.c                               \
    gprintf.c                               \
    gconvert.c                              \
    gdataset.c                              \
    gkeyfile.c                              \
    genviron.c                              \
    gvariant.c                              \
    gversion.c                              \
    gscanner.c                              \
    gbitlock.c                              \
    gpattern.c                              \
    ggettext.c                              \
    gcharset.c                              \
    glib-unix.c                             \
    gtimezone.c                             \
    gdatetime.c                             \
    gsequence.c                             \
    gchecksum.c                             \
    gstrfuncs.c                             \
    gunibreak.c                             \
    glib-init.c                             \
    gfileutils.c                            \
    giochannel.c                            \
    grefstring.c                            \
    ghostutils.c                            \
    gbacktrace.c                            \
    gunidecomp.c                            \
    gtestutils.c                            \
    gtrashstack.c                           \
    gthreadpool.c                           \
    gasyncqueue.c                           \
    gmappedfile.c                           \
    gstrvbuilder.c                          \
    gstringchunk.c                          \
    gvarianttype.c                          \
    gvariant-core.c                         \
    gbookmarkfile.c                         \
    gvarianttypeinfo.c                      \
    gvariant-serialiser.c                   \
