/* Test case for FontFace */

#ifndef _FONTTYPE_TEST_H
#define _FONTTYPE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <string>

#define WIDTH 640
#define HEIGHT 480

using namespace std;

class FontTypeTest: public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(FontTypeTest);

    CPPUNIT_TEST(create1);
    CPPUNIT_TEST(create2);

    CPPUNIT_TEST_SUITE_END();

 public:

    FontTypeTest();

    virtual ~FontTypeTest();

    void setUp();

    void tearDown();

    void runTest ();

 private:

    /* Test case */
    void create1 ();
    void create2 ();

    /* draw bitmap */
    void draw_bitmap (FT_Bitmap* bitmap, FT_Int x, FT_Int y);

    void show_image(void);

    unsigned char image[HEIGHT][WIDTH];
};

#endif  /* _FONTTYPE_TEST_H */