#include "unity.h"
#include "hasfile.h"

void setUp(void) {}
void setDowm(void) {}


void test_NomeDaFuncao(void){
  TEST_ASSERT_RESTO();
}

int main (void){
UNITY_BEGIN();

RUN_TEST(test_NomeDaFuncao);

return UNITY_END();
}
