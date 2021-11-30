#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tlshc/tlsh.h>

int main()
{
    Tlsh* tlsh = tlsh_new();

    const char* str1 = "The quick brown fox jumps over the lazy dog.The quick brown fox jumps over "
                       "the lazy dog.The quick brown fox jumps over the lazy dog.The quick brown "
                       "fox jumps over the lazy dog.The quick brown fox jumps over the lazy "
                       "dog.The quick brown fox jumps over the lazy dog";

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), 0);
    printf("%s\n", tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_CONSERVATIVE);
    printf("%s\n", tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_PRIVATE);
    printf("%s\n", tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_final(tlsh, (const unsigned char*)str1, strlen(str1), TLSH_OPTION_THREADED);
    printf("%s\n", tlsh_get_hash(tlsh, true));
    tlsh_reset(tlsh);

    tlsh_free(tlsh);
}