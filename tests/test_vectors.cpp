#include <tlshc/tlsh.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include <gtest/gtest.h>

class TlshTest : public testing::Test
{
  protected:
    Tlsh* tlsh;

    void SetUp() override { tlsh = tlsh_new(); }

    void TearDown() override { tlsh_free(tlsh); }
};

TEST_F(TlshTest, TestVector1)
{
    const char* str1 = "The quick brown fox jumps over the lazy dog.The quick brown fox jumps over "
                       "the lazy dog.The quick brown fox jumps over the lazy dog.The quick brown "
                       "fox jumps over the lazy dog.The quick brown fox jumps over the lazy "
                       "dog.The quick brown fox jumps over the lazy dog";

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), 0);
    ASSERT_STREQ(
        "T1F7D0024A251C5294648A1888438D98B292C8C51161211421643460022908221DCD8551",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_CONSERVATIVE);
    ASSERT_STREQ(
        "T1F7D0024A251C5294648A1888438D98B292C8C51161211421643460022908221DCD8551",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_PRIVATE);
    ASSERT_STREQ(
        "T100D0024A251C5294648A1888438D98B292C8C51161211421643460022908221DCD8551",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_THREADED);
    ASSERT_STREQ(
        "T100D0024A251C5294648A1888438D98B292C8C51161211421643460022908221DCD8551",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);
}

TEST_F(TlshTest, TestVector2)
{
    const char* str1 =
        "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Vivamus ac leo pretium "
        "faucibus. Nullam sapien sem, ornare ac, nonummy non, lobortis a enim. Ut tempus purus at "
        "lorem. Nulla accumsan, elit sit amet varius semper, nulla mauris mollis quam, tempor "
        "suscipit diam nulla vel leo. Curabitur sagittis hendrerit ante. Donec ipsum massa, "
        "ullamcorper in, auctor et, scelerisque sed, est. Duis viverra diam non justo. Sed elit "
        "dui, pellentesque a, faucibus vel, interdum nec, diam. Class aptent taciti sociosqu ad "
        "litora torquent per conubia nostra, per inceptos hymenaeos. Cum sociis natoque penatibus "
        "et magnis dis parturient montes, nascetur ridiculus mus. Integer rutrum, orci vestibulum "
        "ullamcorper ultricies, lacus quam ultricies odio, vitae placerat pede sem sit amet enim. "
        "Duis sapien nunc, commodo et, interdum suscipit, sollicitudin et, dolor. Praesent in "
        "mauris eu tortor porttitor accumsan. In convallis. Fusce tellus odio, dapibus id "
        "fermentum quis, suscipit id erat. Aliquam erat volutpat. Ut tempus purus at lorem. Nulla "
        "non arcu lacinia neque faucibus fringilla. Aliquam id dolor.";

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), 0);
    ASSERT_STREQ(
        "T1BA11B9370D7A075140411376AB64CFAFF71860042A52BFA94CF0FB1FB197E648362268",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_CONSERVATIVE);
    ASSERT_STREQ(
        "T1BA11B9370D7A075140411376AB64CFAFF71860042A52BFA94CF0FB1FB197E648362268",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_PRIVATE);
    ASSERT_STREQ(
        "T10011B9370D7A075140411376AB64CFAFF71860042A52BFA94CF0FB1FB197E648362268",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_THREADED);
    ASSERT_STREQ(
        "T10011B9370D7A075140411376AB64CFAFF71860042A52BFA94CF0FB1FB197E648362268",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);
}

TEST_F(TlshTest, TestVector3)
{
    const char* str1 = "This text is too short for tlsh by exactly 1 byte";

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), 0);
    ASSERT_STREQ("", tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_CONSERVATIVE);
    ASSERT_STREQ("", tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_PRIVATE);
    ASSERT_STREQ("", tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_THREADED);
    ASSERT_STREQ("", tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);
}

TEST_F(TlshTest, TestVector4)
{
    const char* str1 = "This text is too short for conservative tlsh, but enough for the others";

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), 0);
    ASSERT_STREQ(
        "T1CDA00241BFCB83B3E0D60948133F2495D35CD5E545A3E224AE81555945131B6467E3D6",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_CONSERVATIVE);
    ASSERT_STREQ("", tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_PRIVATE);
    ASSERT_STREQ(
        "T100A00241BFCB83B3E0D60948133F2495D35CD5E545A3E224AE81555945131B6467E3D6",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_THREADED);
    ASSERT_STREQ(
        "T100A00241BFCB83B3E0D60948133F2495D35CD5E545A3E224AE81555945131B6467E3D6",
        tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);
}
