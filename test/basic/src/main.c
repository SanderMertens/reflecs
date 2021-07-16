
/* A friendly warning from bake.test
 * ----------------------------------------------------------------------------
 * This file is generated. To add/remove testcases modify the 'project.json' of
 * the test project. ANY CHANGE TO THIS FILE IS LOST AFTER (RE)BUILDING!
 * ----------------------------------------------------------------------------
 */

#include <basic.h>

// Testsuite 'Basic'
void Basic_world(void);
void Basic_entities(void);
void Basic_filters(void);
void Basic_triggers(void);
void Basic_observers(void);
void Basic_queries(void);
void Basic_systems(void);

bake_test_case Basic_testcases[] = {
    {
        "world",
        Basic_world
    },
    {
        "entities",
        Basic_entities
    },
    {
        "filters",
        Basic_filters
    },
    {
        "triggers",
        Basic_triggers
    },
    {
        "observers",
        Basic_observers
    },
    {
        "queries",
        Basic_queries
    },
    {
        "systems",
        Basic_systems
    }
};

static bake_test_suite suites[] = {
    {
        "Basic",
        NULL,
        NULL,
        7,
        Basic_testcases
    }
};

int main(int argc, char *argv[]) {
    ut_init(argv[0]);
    return bake_test_run("basic", argc, argv, suites, 1);
}
