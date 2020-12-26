#include <QtTest>

#include "glib/glib.h"
#include "glib/gstring.h"

class GLibCompetion : public QObject
{
    Q_OBJECT

public:
    GLibCompetion();
    ~GLibCompetion();

private slots:
    void test_case1();

};

GLibCompetion::GLibCompetion()
{

}

GLibCompetion::~GLibCompetion()
{

}

void GLibCompetion::test_case1()
{
    GCompletion *cmp;
    GList *items;
    gchar *prefix;

    cmp = g_completion_new (NULL);
    g_completion_set_compare (cmp, strncmp);

    items = NULL;
    items = g_list_append ((GList*)items, (void*)"a\302\243");
    items = g_list_append ((GList*)items, (void*)"a\302\244");
    items = g_list_append ((GList*)items, (void*)"bb");
    items = g_list_append ((GList*)items, (void*)"bc");
    g_completion_add_items (cmp, items);
    g_list_free (items);

    items = g_completion_complete (cmp, "a", &prefix);
    g_assert (!strcmp ("a\302", prefix));
    g_assert (g_list_length (items) == 2);
    g_free (prefix);

    items = g_completion_complete_utf8 (cmp, "a", &prefix);
    g_assert (!strcmp ("a", prefix));
    g_assert (g_list_length (items) == 2);
    g_free (prefix);

    items = g_completion_complete (cmp, "b", &prefix);
    g_assert (!strcmp ("b", prefix));
    g_assert (g_list_length (items) == 2);
    g_free (prefix);

    items = g_completion_complete_utf8 (cmp, "b", &prefix);
    g_assert (!strcmp ("b", prefix));
    g_assert (g_list_length (items) == 2);
    g_free (prefix);

    items = g_completion_complete (cmp, "a", NULL);
    g_assert (g_list_length (items) == 2);

    items = g_completion_complete_utf8 (cmp, "a", NULL);
    g_assert (g_list_length (items) == 2);

    items = g_list_append ((GList*)NULL, (void*)"bb");
    g_completion_remove_items (cmp, items);
    g_list_free (items);

    items = g_completion_complete_utf8 (cmp, "b", &prefix);
    g_assert (g_list_length (items) == 1);
    g_free (prefix);

    g_completion_free (cmp);
}

QTEST_APPLESS_MAIN(GLibCompetion)

#include "tst_glibcompetion.moc"
