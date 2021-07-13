#include "json.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format) \
    do {\
        test_count++;\
        if (equality)\
            test_pass++;\
        else {\
            fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", __FILE__, __LINE__, expect, actual);\
            main_ret = 1;\
        }\
    } while(0)

#define EXPECT_EQ_INT(expect, actual) EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

static void test_parse_null() {
	lept_value v;
	v.type = LEPT_TRUE;
	EXPECT_EQ_INT(LEPT_PARSE_OK, lept_parse(&v, "null"));
	EXPECT_EQ_INT(LEPT_NULL, lept_get_type(&v));
}

int main() 
{
	lept_context a;
	lept_value ret;
	a.json = "false";
	lept_parse_false(&a, &ret);
	printf("%d\n", ret.type);
	a.json = "true";
	lept_parse_true(&a, &ret);
	printf("%d\n", ret.type);
	a.json = "null";
	lept_parse_null(&a, &ret);
	printf("%d\n", ret.type);

	lept_parse(&ret, "false");
	printf("%d\n", ret.type);
	return 0;
}