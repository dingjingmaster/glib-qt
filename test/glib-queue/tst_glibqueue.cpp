#include <QtTest>
#include <time.h>
#include <stdlib.h>

#include "glib/glib.h"

#define DEBUG_MSG(args)
/* #define DEBUG_MSG(args) g_printerr args ; g_printerr ("\n");  */
#define PRINT_MSG(args)
/* #define PRINT_MSG(args) g_printerr args ; g_printerr ("\n"); */

#define MAX_THREADS            50
#define MAX_SORTS              5    /* only applies if
                       ASYC_QUEUE_DO_SORT is set to 1 */
#define MAX_TIME               20   /* seconds */
#define MIN_TIME               5    /* seconds */

#define SORT_QUEUE_AFTER       1
#define SORT_QUEUE_ON_PUSH     1    /* if this is done, the
                       SORT_QUEUE_AFTER is ignored */
#define QUIT_WHEN_DONE         1


#if SORT_QUEUE_ON_PUSH == 1
#  undef SORT_QUEUE_AFTER
#  define SORT_QUEUE_AFTER     0
#endif


static GMainLoop*           main_loop       = NULL;
static GThreadPool*         thread_pool     = NULL;
static GAsyncQueue*         async_queue     = NULL;
static gint                 destroy_count   = 0;


static void counting_destroy (gpointer item);
static gboolean sort_queue (gpointer udata);
static void enter_thread (gpointer data, gpointer udata);
static gint sort_compare (gconstpointer p1, gconstpointer p2, gpointer udata);


class GLIbQueue : public QObject
{
    Q_OBJECT

public:
    GLIbQueue();
    ~GLIbQueue();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_asyncqueue_default();

private:
    int test_asyncqueue();
    void test_asyncqueue_basetest ();

};

GLIbQueue::GLIbQueue()
{

}

GLIbQueue::~GLIbQueue()
{

}

void GLIbQueue::initTestCase()
{

}

void GLIbQueue::cleanupTestCase()
{

}

void GLIbQueue::test_asyncqueue_default()
{
    test_asyncqueue();
}

int GLIbQueue::test_asyncqueue ()
{
    gint   i;
    gint   max_threads = MAX_THREADS;
    gint   max_unused_threads = MAX_THREADS;
    gint   sort_multiplier = MAX_SORTS;
    gint   sort_interval;
    gchar *msg G_GNUC_UNUSED;

    test_asyncqueue_basetest ();

    PRINT_MSG (("creating async queue..."));
    async_queue = g_async_queue_new ();

    g_return_val_if_fail (async_queue != NULL, EXIT_FAILURE);

    thread_pool = g_thread_pool_new (enter_thread, async_queue, max_threads, FALSE, NULL);

    g_return_val_if_fail (thread_pool != NULL, EXIT_FAILURE);

    g_thread_pool_set_max_unused_threads (max_unused_threads);

    PRINT_MSG (("creating threads..."));
    for (i = 1; i <= max_threads; i++) {
        GError *error = NULL;

        g_thread_pool_push (thread_pool, GINT_TO_POINTER (i), &error);

        g_assert_no_error (error);
    }

    if (!SORT_QUEUE_AFTER) {
        sort_multiplier = 1;
    }

    sort_interval = ((MAX_TIME / sort_multiplier) + 2)  * 1000;
    g_timeout_add (sort_interval, sort_queue, GINT_TO_POINTER (sort_multiplier));

    if (SORT_QUEUE_ON_PUSH) {
        msg = "sorting when pushing into the queue, checking queue is sorted";
    } else {
        msg = "sorting";
    }

    PRINT_MSG (("%s %d %s %d ms",
          msg,
          sort_multiplier,
          sort_multiplier == 1 ? "time in" : "times, once every",
          sort_interval));

    DEBUG_MSG (("entering main event loop"));

    main_loop = g_main_loop_new (NULL, FALSE);
    g_main_loop_run (main_loop);

    g_main_loop_unref (main_loop);
    g_thread_pool_free (thread_pool, TRUE, TRUE);
    g_async_queue_unref (async_queue);

    return 0;
}

void GLIbQueue::test_asyncqueue_basetest()
{
    GAsyncQueue *q;
    gpointer item;

    destroy_count = 0;

    q = g_async_queue_new_full (counting_destroy);
    g_async_queue_lock (q);
    g_async_queue_ref (q);
    g_async_queue_unlock (q);
    g_async_queue_lock (q);
    g_async_queue_ref_unlocked (q);
    g_async_queue_unref_and_unlock (q);

    item = g_async_queue_try_pop (q);
    QTRY_VERIFY (item == NULL);

    g_async_queue_lock (q);
    item = g_async_queue_try_pop_unlocked (q);
    g_async_queue_unlock (q);
    QTRY_VERIFY (item == NULL);

    g_async_queue_push (q, GINT_TO_POINTER (1));
    g_async_queue_push (q, GINT_TO_POINTER (2));
    g_async_queue_push (q, GINT_TO_POINTER (3));
    QCOMPARE (destroy_count, 0);

    g_async_queue_unref (q);
    QCOMPARE (destroy_count, 0);

    item = g_async_queue_pop (q);
    QCOMPARE (GPOINTER_TO_INT (item), 1);
    QCOMPARE (destroy_count, 0);

    g_async_queue_unref (q);
    QCOMPARE (destroy_count, 2);
}


static gint sort_compare (gconstpointer p1, gconstpointer p2, gpointer udata)
{
    gint32 id1;
    gint32 id2;

    id1 = GPOINTER_TO_INT (p1);
    id2 = GPOINTER_TO_INT (p2);

    return (id1 > id2 ? +1 : id1 == id2 ? 0 : -1);
}

static gboolean sort_queue (gpointer user_data)
{
    static gint     sorts = 0;
    static gpointer last_p = NULL;
    gpointer        p;
    gboolean        can_quit = FALSE;
    gint            sort_multiplier;
    gint            len;
    gint            i;

    sort_multiplier = GPOINTER_TO_INT (user_data);

    if (SORT_QUEUE_AFTER) {
        g_async_queue_sort (async_queue, sort_compare, NULL);

        sorts++;

        if (sorts >= sort_multiplier) {
            can_quit = TRUE;
        }

        g_async_queue_sort (async_queue, sort_compare, NULL);
        len = g_async_queue_length (async_queue);

    } else {
        can_quit = TRUE;
        len = g_async_queue_length (async_queue);
    }

    for (i = 0, last_p = NULL; i < len; i++) {
        p = g_async_queue_pop (async_queue);

        if (last_p) {
            QTest::qCompare(GPOINTER_TO_INT (last_p) <= GPOINTER_TO_INT (p), true, "GPOINTER_TO_INT (last_p) <= GPOINTER_TO_INT (p)", "true", __FILE__, __LINE__);
        }

        last_p = p;
    }

    if (can_quit && QUIT_WHEN_DONE) {
        g_main_loop_quit (main_loop);
    }

    return !can_quit;
}

static void enter_thread (gpointer data, gpointer user_data)
{
    gint   len G_GNUC_UNUSED;
    gint   id;
    gulong ms;

    id = GPOINTER_TO_INT (data);

    ms = g_random_int_range (MIN_TIME * 1000, MAX_TIME * 1000);

    g_usleep (ms * 1000);

    if (SORT_QUEUE_ON_PUSH) {
        g_async_queue_push_sorted (async_queue, GINT_TO_POINTER (id), sort_compare, NULL);
    } else {
        g_async_queue_push (async_queue, GINT_TO_POINTER (id));
    }

    len = g_async_queue_length (async_queue);

    DEBUG_MSG (("thread id:%d added to async queue (size:%d)",
         id, len));
}


static void counting_destroy (gpointer item)
{
    destroy_count++;
}

static void basic_tests (void)
{
    GAsyncQueue *q;
    gpointer item;

    destroy_count = 0;

    q = g_async_queue_new_full (counting_destroy);
    g_async_queue_lock (q);
    g_async_queue_ref (q);
    g_async_queue_unlock (q);
    g_async_queue_lock (q);
    g_async_queue_ref_unlocked (q);
    g_async_queue_unref_and_unlock (q);

    item = g_async_queue_try_pop (q);
    QTRY_VERIFY (item == NULL);

    g_async_queue_lock (q);
    item = g_async_queue_try_pop_unlocked (q);
    g_async_queue_unlock (q);
    QTRY_VERIFY (item == NULL);

    g_async_queue_push (q, GINT_TO_POINTER (1));
    g_async_queue_push (q, GINT_TO_POINTER (2));
    g_async_queue_push (q, GINT_TO_POINTER (3));
    QCOMPARE (destroy_count, 0);

    g_async_queue_unref (q);
    QCOMPARE (destroy_count, 0);

    item = g_async_queue_pop (q);
    QCOMPARE (GPOINTER_TO_INT (item), 1);
    QCOMPARE (destroy_count, 0);

    g_async_queue_unref (q);
    QCOMPARE (destroy_count, 2);
}

QTEST_APPLESS_MAIN(GLIbQueue)

#include "tst_glibqueue.moc"
