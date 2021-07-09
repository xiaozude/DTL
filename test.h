#ifndef _DTL_TEST_H_
#define _DTL_TEST_H_

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define COLOR(msg, code) "\033[0;" #code "m" msg "\033[0m"
#define RED(msg) COLOR(msg, 31)
#define GREEN(msg) COLOR(msg, 32)
#define YELLOW(msg) COLOR(msg, 33)
#define BLUE(msg) COLOR(msg, 34)

#define EXPECT(a, comp, b) { \
	typeof(a) _a = (a), _b = (b); \
	if (!((_a) comp (_b))) { \
		func_flag = false; \
		printf(YELLOW("%s:%d: Failure\n"), __FILE__, __LINE__); \
		printf(YELLOW("Excepted: (%s) %s (%s), actual: %d vs %d\n"), \
			#a, #comp, #b, _a, _b); \
	} \
}
#define EXPECT_EQ(a, b) EXPECT(a, ==, b)
#define EXPECT_NE(a, b) EXPECT(a, !=, b)
#define EXPECT_LT(a, b) EXPECT(a, <, b)
#define EXPECT_LE(a, b) EXPECT(a, <=, b)
#define EXPECT_GT(a, b) EXPECT(a, >, b)
#define EXPECT_GE(a, b) EXPECT(a, >=, b)

#define FUNC_NAME(a, b) test_##a##_##b
#define TEST(a, b) \
void FUNC_NAME(a, b)(); \
__attribute__((constructor)) \
void reg_test_##a##_##b() { \
	add_test_function(FUNC_NAME(a, b), #a "." #b); \
} \
void FUNC_NAME(a, b)()

struct FuncData {
	void (*func)();
	const char *name;
} func_arr[100];

int func_arr_cnt = 0;

void add_test_function(void (*func)(), const char *name)
{
	func_arr[func_arr_cnt].func = func;
	func_arr[func_arr_cnt].name = name;
	func_arr_cnt++;
}

int func_flag = false;

const char *RUN	 = GREEN("[ RUN      ]");
const char *OK   = GREEN("[       OK ]");
const char *FAILED = RED("[  FAILED  ]");

int RUN_ALL_TESTS()
{
	for (int i = 0; i < func_arr_cnt; i++) {
		printf("%s %s\n", RUN, func_arr[i].name);
		func_flag = true;
		clock_t a = clock();
		func_arr[i].func();
		clock_t b = clock();
		if (func_flag) {
			printf("%s ", OK);
		} else {
			printf("%s ", FAILED);
		}
		printf("%s " YELLOW("(%ld ms)") "\n\n", func_arr[i].name, (b - a) * 1000 / CLOCKS_PER_SEC);
	}
	return 0;
}

#endif /* _DTL_TEST_H_ */

