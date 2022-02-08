/**
 * Before: Oh hey learning how to do unit tests sounds fun
 * After: I REGRET EVERYTHING
 *
 * Author: mysticalCabinboy
 **/

#include "unity.h"
#include "Violet/Rendering.h"

void setUp(void){
}
void tearDown(void){

}

void test_UnityIsSetup(void){
    TEST_ASSERT_EQUAL(10,10);
}

void test_RendererRegistersAModel(void){
    VGRSetupRenderer(0,0,"");
    struct Model testModel;

    TEST_ASSERT_NOT_EQUAL(0, VGRRegisterModel("test", &testModel));
    TEST_ASSERT_EQUAL(1, VGRGetModelID("test"));

    VGRUnloadModel("test");
    TEST_ASSERT_EQUAL(0, VGRGetModelID("test"));
}

void test_RendererRegistersAModelToASpecificID(void){
    VGRSetupRenderer(0,0,"");
    struct Model testModel;

    TEST_ASSERT_NOT_EQUAL(0, VGRRegisterModelWithID("test",10, &testModel));
    TEST_ASSERT_EQUAL(10, VGRGetModelID("test"));

    VGRUnloadModel("test");
}

void test_RendererCreatesANewDrawable(){
    VGRSetupRenderer(0,0,"");
    struct Model testModel;
    Transform originPoint;

    VGRRegisterModel("test", &testModel);
    Drawable testDrawable = VGRCreateDrawableByName("test", originPoint);
    Drawable testDrawableByID = VGRCreateDrawable(VGRGetModelID("test"), originPoint);
    Drawable testDrawableByCopy = VGRCreateDrawableByCopy(testDrawable, originPoint);

    TEST_ASSERT_EQUAL(0,testDrawable.rendererID);
    TEST_ASSERT_EQUAL(VGRGetModelID("test"), VGRGetDrawableModelID(testDrawable));

    TEST_ASSERT_EQUAL(1,testDrawableByID.rendererID);
    TEST_ASSERT_EQUAL(VGRGetModelID("test"), VGRGetDrawableModelID(testDrawableByID));
    TEST_ASSERT_NOT_EQUAL(testDrawable.transform,testDrawableByID.transform);

    TEST_ASSERT_EQUAL(2,testDrawableByCopy.rendererID);
    TEST_ASSERT_EQUAL(VGRGetModelID("test"), VGRGetDrawableModelID(testDrawableByCopy));
    TEST_ASSERT_NOT_EQUAL(testDrawable.transform,testDrawableByCopy.transform);

    VGRCleanupRenderer();
}

void main(){
    UNITY_BEGIN();
    RUN_TEST(test_UnityIsSetup);
    RUN_TEST(test_RendererRegistersAModel);
    RUN_TEST(test_RendererRegistersAModelToASpecificID);
    RUN_TEST(test_RendererCreatesANewDrawable);
    UNITY_END();
}
