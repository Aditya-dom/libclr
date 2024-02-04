#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

static tests test1;

int main() {
  test1.total = 6;
  test1.success = 0;
  test1.failure = 0;

  int a = system("cd ./test 2>/dev/null");
  if (a) {
    basic_display("Error:", BLACK * 16 + RED, FULL);
    printf(" Only run tests from root folder of project\n");
    exit(1);
  }

  getbg_test();
  getfg_test();
  getbasic_colour_test();

  return test1.total != test1.success;
}

// TEST FUNCTIONS

void test_log(const char *testname, int status) {
  switch (status) {
  case 0:
    test1.success++;
    printf("\033[32m");
    printf("SUCCESS [%d/%d]:\t%s", test1.success, test1.total, testname);
    break;
  case 1:
    test1.failure++;
    printf("\033[31m");
    printf("FAILURE [%d/%d]:\t%s", test1.failure, test1.total, testname);
    break;
  case 3:
    break;
  default:
    break;
  }
  printf("\033[0m\n");
}

/*
  ALL TESTS HERE
*/

void getbg_test() {
  /*
    test for 0x71
              should return 47
    test for 0xFF
              should return 107
  */

  basic_colour testbg1 = getbg(0x7F);
  test_log("getbg", testbg1 - 47);

  basic_colour testbg2 = getbg(0xFF);
  test_log("getbg", testbg2 - 107);
}

void getfg_test() {
  /*
    test for 0x07
              expect 37
    test for 0xFF
              expect 97
  */

  basic_colour testfg1 = getfg(0x07);
  test_log("getfg", testfg1 - 37);

  basic_colour testfg2 = getfg(0xFF);
  test_log("getfg", testfg2 - 97);
}

void getbasic_colour_test() {
  /*
    test for BRIGHT_BLACK, RED
            expect 0x81
    test for BRIGHT_MAGENTA, BRIGHT_CYAN
            expect 0xDE
  */

  basic_colour testgc1 = getbasic_colour(BRIGHT_BLACK, RED);
  test_log("getbasic_colour", testgc1 - 0x81);

  basic_colour testgc2 = getbasic_colour(BRIGHT_MAGENTA, BRIGHT_CYAN);
  test_log("getbasic_colour", testgc2 - 0xDE);
}
