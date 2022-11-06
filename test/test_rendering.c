/**
 * Before: Oh hey learning how to do unit tests sounds fun
 * After: I REGRET EVERYTHING
 *
 * Author: mysticalCabinboy
 **/

#include "unity.h"
#include "Violet/Rendering.h"
#include <raylib.h>

void setUp(void){
}
void tearDown(void){

}

void test_UnityIsSetup(void){
    TEST_ASSERT_EQUAL(10,10);
}

void test_RendererRegistersAModel(void){
    VGRSetup(0,0,"");
    struct Model testModel;

    u32 modelID = VGRRegisterModel("test", &testModel);

    TEST_ASSERT_NOT_EQUAL_MESSAGE(0, modelID, "Model does not have an ID.");
    TEST_ASSERT_EQUAL_MESSAGE(1, VGRGetModelID("test"), "Model might not be registered.");

    VGRUnloadModel("test");
    TEST_ASSERT_EQUAL(0, VGRGetModelID("test"));
}

void test_RendererRegistersAModelToASpecificID(void){
    VGRSetup(0,0,"");
    struct Model testModel;
    u32 modelID = VGRRegisterModelWithID("test", 10, &testModel);

    TEST_ASSERT_EQUAL(10, VGRGetModelID("test"));

    VGRUnloadModel("test");
}

void test_RendererCreatesANewDrawable(){
    VGRSetup(0,0,"");
    struct Model testModel;
    Transform originPoint;

    VGRRegisterModel("test", &testModel);
    VGRRegisterModel("test2", &testModel);

    Drawable testDrawable = VGRCreateDrawableByName("test");
    Drawable testDrawableByID = VGRCreateDrawable(VGRGetModelID("test"));
    Drawable testDrawableByCopy = VGRCreateDrawableByCopy(testDrawable);
    
    
    Drawable testUniqueDrawableByID = VGRCreateDrawable(VGRGetModelID("test2"));

    TEST_ASSERT_EQUAL(1,testDrawable.modelID);
    TEST_ASSERT_EQUAL(VGRGetModelID("test"), VGRGetDrawableModelID(testDrawable));
    TEST_ASSERT_EQUAL(VGRGetModelID("test"), VGRGetDrawableModelID(testDrawableByID));
    TEST_ASSERT_EQUAL(VGRGetModelID("test"), VGRGetDrawableModelID(testDrawableByCopy));
    
    TEST_ASSERT_NOT_EQUAL(VGRGetModelID("test2"), VGRGetModelID("test"));

    VGRCleanup();
}

void main(){
    UNITY_BEGIN();
    RUN_TEST(test_UnityIsSetup);
    RUN_TEST(test_RendererRegistersAModel);
    RUN_TEST(test_RendererRegistersAModelToASpecificID);
    RUN_TEST(test_RendererCreatesANewDrawable);
    UNITY_END();
}
