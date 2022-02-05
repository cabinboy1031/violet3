#include "unity.h"

void setUp(void){

}
void tearDown(void){

}

void test_UnityIsSetup(void){
    TEST_ASSERT_EQUAL(10,10);
}

UNITY_BEGIN()
void main(){
    RUN_TEST(tes)
}
UNITY_END()
