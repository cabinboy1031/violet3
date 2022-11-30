#include "unity.h"

void setUp(void){

}
void tearDown(void){

}

void test_UnityIsSetup(){
    TEST_ASSERT_EQUAL(10,10);
}

int main(){
UNITY_BEGIN();
    RUN_TEST(test_UnityIsSetup);
UNITY_END();
}
