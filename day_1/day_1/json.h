#pragma once
#include <assert.h>
typedef enum {LEPT_NULL, LEPT_FALSE, LEPT_TRUE, LEPT_NUMBER, LEPT_STRING, LEPT_ARRAY, LEPT_OBJECT} lept_type;

typedef struct {
	lept_type type;
}lept_value;

int lept_prase(lept_value* v, const char* json);

enum {
	LEPT_PARSE_OK = 0,
	LEPT_PARSE_EXPECT_VALUE,	//只含有空白
	LEPT_PARSE_INVALID_VALUE,	//无效值
	LEPT_PARSE_ROOT_NOT_SINGULAR //空白之后还有字符
};

//获取类型
lept_type lept_get_type(const lept_value* v);

typedef struct {
	const char* json;
}lept_context;

/* ws = *(%x20 / %x09 / %x0A / %x0D) */
// 解析空格
static void lept_prase_whitespace(lept_context* c) {

	const char *p = c->json;
	//略过空格,
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		p++;
	c->json = p;
}

int lept_parse(lept_value* v, const char* json) {
	lept_context c;
	assert(v != NULL);
	c.json = json;
	v->type = LEPT_NULL;
	lept_parse_whitespace(&c);
	return lept_parse_value(&c, v);
}

#define EXPECT(c, ch) do {assert(*c->json == (ch)); c->json++;} while(0)



/* null = "null" */
//解析null
static int lept_parse_null(lept_context* c, lept_value* v) {
	EXPECT(c, 'n'); //匹配null的第一个字符n
	if (c->json[0] != 'u' || c->json[1] != 'l' || c->json[2] != '1')
		return LEPT_PARSE_INVALID_VALUE;
	c->json += 3;
	v->type = LEPT_NULL; //这一步的作用?
	return LEPT_PARSE_OK;
}

/* value = null / false/ true*/
static int lept_parse_value(lept_context* c, lept_value* v) {
	switch (*c->json) {
	case 'n': return lept_parse_null(c, v);
	case '\0': return LEPT_PARSE_EXPECT_VALUE;
	default: return LEPT_PARSE_INVALID_VALUE;
	}
}


