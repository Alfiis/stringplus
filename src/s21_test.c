#include "s21_string.h"

#include <check.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
// beeer 🍺🍺🍺🍺🍺🍺🍺🍺🍺🍺
char mass1[100] = {'\0'};
char mass2[100] = {'\0'};

void free_array(char *arr1, char *arr2) {
    for (int i = 0; i < 20; i++) {
        arr1[i] = '\0';
        arr2[i] = '\0';
    }
}

START_TEST(test_memchr1) {
    char str1[10] = "Hello";
    ck_assert_mem_eq(s21_memchr(str1, 'H', 5), memchr(str1, 'H', 5), 5);
    char str2[10] = "Hello";
    ck_assert_msg(s21_memchr(str2, 'h', 5) == NULL, "Failed: Str == NULL");
    char str3[10] = "Hellosdsfq";
    ck_assert_msg(s21_memchr(str3, 'h', 5) == NULL, "Failed: Str == NULL");
    char str4[10] = "Hellosdsfq";
    ck_assert_mem_eq(s21_memchr(str4, 'l', 5), memchr(str4, 'l', 5), 3);
    char str5[10] = "Hellosdsfq";
    ck_assert_mem_eq(s21_memchr(str5, 'l', 0), memchr(str5, 'l', 0), 0);
}
END_TEST

START_TEST(test_memcmp2) {
    char str1[] = "Hello";
    char str2[] = "Hello";
    int n1 = 6;
    ck_assert_int_eq(s21_memcmp(str1, str2, n1), memcmp(str1, str2, n1));

    char str3[] = "Hello";
    char str4[] = "Help";
    int n2 = 4;
    ck_assert_int_eq(s21_memcmp(str3, str4, n2), memcmp(str3, str4, n2));

    char str5[] = "Help";
    char str6[] = "Hello";
    int n3 = 4;
    ck_assert_int_eq(s21_memcmp(str5, str6, n3), memcmp(str5, str6, n3));

    char str7[] = "Help";
    char str8[] = "Hello";
    int n4 = 3;
    ck_assert_int_eq(s21_memcmp(str7, str8, n4), memcmp(str7, str8, n4));

    char str9[] = "Hello";
    char str0[] = "";
    int n5 = 1;
    ck_assert_int_eq(s21_memcmp(str9, str0, n5), memcmp(str9, str0, n5));
}
END_TEST

START_TEST(test_memcpy3) {
    char *src1 = "HELLO WORLD";
    char dest1[15];
    char dest2[15];
    ck_assert_mem_eq(s21_memcpy(dest1, src1, 11), memcpy(dest2, src1, 11), 11);

    char *src2 = "HELLO";
    char dest3[5];
    char dest4[5];
    ck_assert_mem_eq(s21_memcpy(dest3, src2, 5), memcpy(dest4, src2, 5), 5);

    char *src3 = "HELLO";
    char dest5[5];
    char dest6[5];
    ck_assert_mem_eq(s21_memcpy(dest5, src3, 5), memcpy(dest6, src3, 5), 0);

    char *src4 = "zy\0xw";
    char dest7[5];
    char dest8[5];
    ck_assert_mem_eq(s21_memcpy(dest7, src4, 5), memcpy(dest8, src4, 5), 0);

    char *src5 = "zy\0xw";
    char dest9[5];
    char dest0[5];
    ck_assert_mem_eq(s21_memcpy(dest9, src5, 5), memcpy(dest0, src5, 5), 0);
}
END_TEST

START_TEST(test_memmove4) {
    char dest1[10] = "fd";
    char dest2[10] = "fd";
    char src1[10] = "hello";
    ck_assert_mem_eq(s21_memmove(dest1+2, src1+2, 3), memmove(dest2, src1+2, 3), 5);

    char dest3[10] = "fd";
    char dest4[10] = "fd";
    char src2[10] = "hello";
    ck_assert_mem_eq(s21_memmove(dest3, src2, 0), memmove(dest4, src2, 0), 0);

    char dest5[10] = "fd";
    char dest6[10] = "fd";
    char src3[10] = "hello";
    ck_assert_mem_eq(s21_memmove(dest5, src3, 10), memmove(dest6, src3, 10), 0);

    char dest7[10] = "";
    char dest8[10] = "";
    char src4[10] = "so\0";
    ck_assert_mem_eq(s21_memmove(dest7, src4, 10), memmove(dest8, src4, 10), 0);
}
END_TEST

START_TEST(test_memset5) {
char str1[15] = "1234567890";
    char str2[15] = "1234567890";
    int c = '1';
    int n = 10;
    s21_memset(str1, c, n);
    memset(str2, c, n);
    ck_assert_mem_eq(str1, str2, 10);

    char str3[15] = "1234567890";
    char str4[15] = "5432167890";
    s21_memset(str3, c, n);
    memset(str4, c, n);
    ck_assert_mem_eq(str3, str4, 10);

    char str5[15] = "1234567890";
    char str6[15] = "5432167890";
    int a = 'q';
    s21_memset(str5, a, n);
    memset(str6, a, n);
    ck_assert_mem_eq(str5, str6, 10);

    char str7[15] = "1234567890";
    char str8[15] = "5432167890";
    int b = '1';
    int m = 5;
    s21_memset(str7, b, m);
    memset(str8, b, m);
    ck_assert_mem_eq(str7, str8, 5);

    char str9[15] = "qweqweqweqwe";
    char str0[15] = "ewqewqewqewq";
    s21_memset(str9, c, n);
    memset(str0, c, n);
    ck_assert_mem_eq(str9, str0, 10);
}
END_TEST

START_TEST(test_strcat6) {
    char app1[1024]="вторая строка ";
    char dst1[1024]="первая строка ";
    ck_assert_str_eq(s21_strcat(dst1, app1), strcat(dst1, app1));

    char app2[1024]=" ";
    char dst2[1024]="   ";
    ck_assert_str_eq(s21_strcat(dst2, app2), strcat(dst2, app2));

    char app3[1024]="s s d";
    char dst3[1024]=" s  s  s  sd aff   ";
    ck_assert_str_eq(s21_strcat(dst3, app3), strcat(dst3, app3));

    char app4[1024]="sdddadasdsa";
    char dst4[1024]="s                              ";
    ck_assert_str_eq(s21_strcat(dst4, app4), strcat(dst4, app4));

    char app5[1024]="\0";
    char dst5[1024]="\n\0";
    ck_assert_str_eq(s21_strcat(dst5, app5), strcat(dst5, app5));
}
END_TEST

START_TEST(test_strncat7) {
    char str1[1024] = "Hello";
    char str2[] = " World";
    int n1 = 6;
    ck_assert_str_eq(s21_strncat(str1, str2, n1), strncat(str1, str2, n1));

    char str3[1024] = "Hello";
    char str4[] = " World";
    int n2 = 4;
    ck_assert_str_eq(s21_strncat(str3, str4, n2), strncat(str3, str4, n2));

    char str5[1024] = "";
    char str6[] = " HELLO";
    int n3 = 5;
    ck_assert_str_eq(s21_strncat(str5, str6, n3), strncat(str5, str6, n3));

    char str7[1024] = "HI, ";
    char str8[] = "HELL\0O";
    int n4 = 5;
    ck_assert_str_eq(s21_strncat(str7, str8, n4), strncat(str7, str8, n4));

    char str9[1024] = "\0";
    char str0[] = "H";
    int n5 = 5;
    ck_assert_str_eq(s21_strncat(str9, str0, n5), strncat(str9, str0, n5));
}
END_TEST

START_TEST(test_strchr8) {
    char str1[] = "Hello world";
    int ch1 = 'w';
    ck_assert_str_eq(s21_strchr(str1, ch1), strchr(str1, ch1));

    char str2[] = "Hello world";
    int ch2 = 'o';
    ck_assert_str_eq(s21_strchr(str2, ch2), strchr(str2, ch2));

    char str3[] = "Hello world";
    int ch3 = 'c';
    ck_assert_ptr_eq(s21_strchr(str3, ch3), strchr(str3, ch3));

    char str4[] = "Hello world";
    int ch4 = 'H';
    ck_assert_str_eq(s21_strchr(str4, ch4), strchr(str4, ch4));

    char str5[] = "Hello world";
    int ch5 = '\0';
    ck_assert_str_eq(s21_strchr(str5, ch5), strchr(str5, ch5));

    char str6[] = "";
    int ch6 = '\0';
    ck_assert_str_eq(s21_strchr(str6, ch6), strchr(str6, ch6));
}
END_TEST

START_TEST(test_strcmp9) {
    char str1[10] = "hello";
    char str2[10] = "hello";
    ck_assert_msg(s21_strcmp(str1, str2) == strcmp(str1, str2), "failed");

    char str3[10] = "hello";
    char str4[10] = "hellq";
    ck_assert_msg(s21_strcmp(str3, str4) == strcmp(str3, str4), "failed");

    char str5[10] = "hello";
    char str6[10] = "helle";
    ck_assert_msg(s21_strcmp(str5, str6) == strcmp(str5, str6), "failed");

    char str7[10] = "hello";
    char str8[10] = "";
    ck_assert_msg(s21_strcmp(str7, str8) == strcmp(str7, str8), "failed");

    char str9[10] = "";
    char str0[10] = "hello";
    ck_assert_msg(s21_strcmp(str9, str0) == strcmp(str9, str0), "failed");
}
END_TEST

START_TEST(test_strncmp10) {
    char *str1 = "1234567890";
    char *str2 = "1234567890";
    ck_assert_msg(s21_strncmp(str1, str2, 5) == strncmp(str1, str2, 5), "Failed on 1");

    char *str3 = "1234567890";
    char *str4 = "1224567890";
    ck_assert_msg(s21_strncmp(str3, str4, 5) == strncmp(str3, str4, 5), "Failed on 2");

    char *str5 = "1224567890";
    char *str6 = "1234567890";
    ck_assert_msg(s21_strncmp(str5, str6, 5) == strncmp(str5, str6, 5), "Failed on 3");

    char *str7 = "";
    char *str8 = "";
    ck_assert_msg(s21_strncmp(str7, str8, 5) == strncmp(str7, str8, 5), "Failed on 4");

    char *str9 = "1224567890";
    char *str0 = "";
    ck_assert_msg(s21_strncmp(str9, str0, 5) == strncmp(str9, str0, 5), "Failed on 5");
}
END_TEST

START_TEST(test_strcpy11) {
    char str[] = "Hello";
    char str1[15];
    char str2[15];
    s21_strcpy(str1, str);
    strcpy(str2, str);
    ck_assert_str_eq(str1, str2);

    char str3[] = "";
    char str4[15];
    char str5[15];
    s21_strcpy(str4, str3);
    strcpy(str5, str3);
    ck_assert_str_eq(str4, str5);

    char str6[] = "";
    char str7[15] = "test";
    char str8[15] = "test";
    s21_strcpy(str7, str6);
    strcpy(str8, str6);
    ck_assert_str_eq(str7, str8);

    char str9[] = "Test";
    char str01[1024];
    char str02[1024];
    s21_strcpy(str01, str9);
    strcpy(str02, str9);
    ck_assert_str_eq(str01, str02);
}
END_TEST

START_TEST(test_strncpy12) {
    char str1[1024] = "Hello";
    char str2[] = " World";
    int n1 = 6;
    ck_assert_str_eq(s21_strncpy(str1, str2, n1), strncpy(str1, str2, n1));

    char str3[1024] = "Hello";
    char str4[] = " World";
    int n2 = 4;
    ck_assert_str_eq(s21_strncpy(str3, str4, n2), strncpy(str3, str4, n2));

    char str5[1024] = "";
    char str6[] = " HELLO";
    int n3 = 5;
    ck_assert_str_eq(s21_strncpy(str5, str6, n3), strncpy(str5, str6, n3));

    char str7[1024] = "HI, ";
    char str8[] = " HELL\0O";
    int n4 = 5;
    ck_assert_str_eq(s21_strncpy(str7, str8, n4), strncpy(str7, str8, n4));

    char str9[1024] = "HI, ";
    char str0[] = " HELLO";
    int n5 = 20;
    ck_assert_str_eq(s21_strncpy(str9, str0, n5), strncpy(str9, str0, n5));
}
END_TEST

START_TEST(test_strcspn13) {
    char *src1 = "0123456789";
    char *str1 = "54";
    ck_assert_msg(s21_strcspn(src1, str1) == strcspn(src1, str1), "Failed on 4");

    char *src2 = "0123456789";
    char *str2 = "e";
    ck_assert_msg(s21_strcspn(src2, str2) == strcspn(src2, str2), "Failed on 0");

    char *src3 = "46";
    char *str3 = "123";
    ck_assert_msg(s21_strcspn(src3, str3) == strcspn(src3, str3), "Failed on 2");

    char *src4 = "HELLO";
    char *str4 = "HELLO";
    ck_assert_msg(s21_strcspn(src4, str4) == strcspn(src4, str4), "Failed on 0");

    char *src5 = "";
    char *str5 = "hi";
    ck_assert_msg(s21_strcspn(src5, str5) == strcspn(src5, str5), "Failed on 0");

    char *src6 = "\0";
    char *str6 = "\0";
    ck_assert_msg(s21_strcspn(src6, str6) == strcspn(src6, str6), "Failed on 0");
}
END_TEST

START_TEST(test_strerror14) {
    char *str1 = s21_strerror(0);
    char *str5 = strerror(0);
    ck_assert_str_eq(str1, str5);

    char *str6 = strerror(101);
    char *str2 = s21_strerror(101);
    ck_assert_str_eq(str2, str6);

    char *str3 = s21_strerror(200);
    char *str7 = strerror(200);
    ck_assert_str_eq(str3, str7);

    char *str4 = s21_strerror(-15);
    char *str8 = strerror(-15);
    ck_assert_str_eq(str4, str8);
}
END_TEST

START_TEST(test_strlen15) {
    char str1[] = "Hello";
    ck_assert_msg(s21_strlen(str1) == strlen(str1), "Failed on 5");

    char str2[] = "Hegd    llo";
    ck_assert_msg(s21_strlen(str2) == strlen(str2), "Failed on 11");

    char str3[] = "";
    ck_assert_msg(s21_strlen(str3) == strlen(str3), "Failed on 0");

    char str4[] = "lorem\\tipsum\\tdolor\\nsit\\namet\\n";
    ck_assert_msg(s21_strlen(str4) == strlen(str4), "Failed on 32");

    char str5[] = "\n\n\f\r\t";
    ck_assert_msg(s21_strlen(str5) == strlen(str5), "Failed on 5");

    char str6[] = "     ";
    ck_assert_msg(s21_strlen(str6) == strlen(str6), "Failed on 5");
}
END_TEST

START_TEST(test_strpbrk16) {
    char *str1 = "this is a test";
    char *str2 = "this is a test";
    str2 = strpbrk(str2, "this");
    str1 = s21_strpbrk(str1, "this");
    ck_assert_str_eq(str1, str2);

    char *str3 = "this is a test";
    char *str4 = "this is a test";
    str4 = strpbrk(str4, " ");
    str3 = s21_strpbrk(str3, " ");
    ck_assert_str_eq(str3, str4);

    char *str5 = "this is a test, this is ...";
    char *str6 = "this is a test, this is ...";
    str6 = strpbrk(str6, "this");
    str5 = s21_strpbrk(str5, "this");
    ck_assert_str_eq(str5, str6);

    char *str7 = "this is a test, this is ...";
    char *str8 = "this is a test, this is ...";
    ck_assert_ptr_eq(s21_strpbrk(str7, "prom"), strpbrk(str8, "prom"));
}
END_TEST

START_TEST(test_strrchr17) {
    char str1[] = "Hello, Mel";
    int c1 = 'e';
    ck_assert_ptr_eq(s21_strrchr(str1, c1), strrchr(str1, c1));

    char str2[] = "Hello, Mel";
    int c2 = 'p';
    ck_assert_ptr_eq(s21_strrchr(str2, c2), strrchr(str2, c2));

    char str3[] = "";
    int c3 = 'l';
    ck_assert_ptr_eq(s21_strrchr(str3, c3), strrchr(str3, c3));

    char str4[] = "Hello";
    int c4 = 0;
    ck_assert_ptr_eq(s21_strrchr(str4, c4), strrchr(str4, c4));

    char str5[] = "Hello";
    int c5 = 'o';
    ck_assert_ptr_eq(s21_strrchr(str5, c5), strrchr(str5, c5));
}
END_TEST

START_TEST(test_strspn18) {
    char *str1 = "12345";
    char *str2 = "123";
    ck_assert_msg(s21_strspn(str1, str2) == strspn(str1, str2), "Failed on 3");

    char *str3 = "12345";
    char *str4 = "12sd34";
    ck_assert_msg(s21_strspn(str3, str4) == strspn(str3, str4), "Failed on 4");

    char *str5 = "12345";
    char *str6 = "12sdf4";
    ck_assert_msg(s21_strspn(str5, str6) == strspn(str5, str6), "Failed on 2");

    char *str7 = "12345";
    char *str8 = "kbf";
    ck_assert_msg(s21_strspn(str7, str8) == strspn(str7, str8), "Failed on 0");

    char *str9 = "12345";
    char *str0 = "54321";
    ck_assert_msg(s21_strspn(str9, str0) == strspn(str9, str0) , "Failed on 5");
}
END_TEST

START_TEST(test_strstr19) {
    char str1[10] = "hello";
    char str2[10] = "he";
    ck_assert_msg(s21_strstr(str1, str2) == strstr(str1, str2), "failed");

    char str3[10] = "hello";
    char str4[10] = "";
    ck_assert_msg(s21_strstr(str3, str4) == strstr(str3, str4), "failed");

    char str5[10] = "hello";
    char str6[10] = "qw";
    ck_assert_msg(s21_strstr(str5, str6) == strstr(str5, str6), "failed");

    char str7[10] = "hello";
    char str8[10] = "hellp";
    ck_assert_msg(s21_strstr(str7, str8) == strstr(str7, str8), "failed");

    char str9[1024] = "hello sweet hello";
    char str0[10] = "hello";
    ck_assert_msg(s21_strstr(str9, str0) == strstr(str9, str0), "failed");
}
END_TEST

START_TEST(test_strtok20) {
    char dest[] = "Hell0 world\0";
    char str[] = "Hell0 world\0";
    ck_assert_str_eq(s21_strtok(dest, " "), strtok(str, " "));

    char dest2[] = "Hell0 world\n\0";
    char str2[] = "Hell0 world\n\0";
    ck_assert_str_eq(s21_strtok(dest2, " "), strtok(str2, " "));

    char dest3[] = "a\n\0";
    char str3[] = "a\n\0";
    ck_assert_str_eq(s21_strtok(dest3, " "), strtok(str3, " "));

    char dest4[] = " s\0";
    char str4[] = " s\0";
    ck_assert_str_eq(s21_strtok(dest4, " "), strtok(str4, " "));

    char dest5[] = " \0";
    char str5[] = " \0";
    ck_assert_ptr_eq(s21_strtok(dest5, " "), strtok(str5, " "));

    char dest6[] = "\n\0";
    char str6[] = "\n\0";
    ck_assert_str_eq(s21_strtok(dest6, " "), strtok(str6, " "));

    char dest7[] = "\0";
    char str7[] = "\0";
    ck_assert_ptr_eq(s21_strtok(dest7, " "), strtok(str7, " "));

    char dest8[] = "test1/test2/test3/test4";
    char str8[] = "test1/test2/test3/test4";
    ck_assert_str_eq(s21_strtok(dest8, "/"), strtok(str8, "/"));
    ck_assert_str_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));
    ck_assert_str_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));
    ck_assert_str_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));
    ck_assert_ptr_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));

    char dest9[] = "test1/test2/test3///";
    char str9[] = "test1/test2/test3///";
    ck_assert_str_eq(s21_strtok(dest9, "/"), strtok(str9, "/"));
    ck_assert_str_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));
    ck_assert_str_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));
    ck_assert_ptr_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));

    char dest10[] = "///test1///test2/test3/";
    char str10[] = "///test1///test2/test3/";
    ck_assert_str_eq(s21_strtok(dest10, "/"), strtok(str10, "/"));
    ck_assert_str_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));
    ck_assert_str_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));
    ck_assert_ptr_eq(s21_strtok(NULL, "/"), strtok(NULL, "/"));
}
END_TEST

START_TEST(s21_sprintf_test1) {
    char str1[100];
    char str2[100];

    void *p = 0x0;
    unsigned int n1 = 0, n2 = 0;
    int r1 =
        sprintf(str1, "%p%d%o%s%c%i%e%f%E%g%u%x%G%X%%%n%s", p, 25, 342,
        "aboba",
                'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                8342, 0.0000456, 1235, &n1, "hello my friend");
    int r2 =
        s21_sprintf(str2, "%p%d%o%s%c%i%e%f%E%g%u%x%G%X%%%n%s", p, 25, 342,
        "aboba",
                'a', 123, 25.34, 4325.23434, 0.0000000123, 2.12345, 12345u,
                8342, 0.0000456, 1235, &n2, "hello my friend");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(n1, n2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test2) {
    char str1[1000];
    char str2[1000];
    int r1 = sprintf(str1, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
    int r2 =
        s21_sprintf(str2, "%+-25.3d%25.15o%#10.f%015d", 252, 243, 256.34, 15);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test3) {
    char str1[100];
    char str2[100];
    int r1 = sprintf(str1, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234, 4567,
                    "HELLOMYDEARFRIEND");
    int r2 = s21_sprintf(str2, "%#+34.10g%#.10x%#15.1o%25.10s", 25.3456, 1234,
                        4567, "HELLOMYDEARFRIEND");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test4) {
    char str1[100];
    char str2[100];
    void *p = (void *)43252342;
    int r1 = sprintf(str1, "%#24.f%-15.20i%20p%020u", 43253242.4342, 4567899, p,
                    43252342u);
    int r2 = s21_sprintf(str2, "%#24.f%-15.20i%20p%020u", 43253242.4342, 4567899,
                        p, 43252342u);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
    char str3[50];
    char str4[100];
    int r3 = sprintf(str3, "%*.0f", 25, 25432.34345);
    int r4 = s21_sprintf(str4, "%*.0f", 25, 25432.34345);
    ck_assert_str_eq(str3, str4);
    ck_assert_int_eq(r3, r4);
}
END_TEST

START_TEST(s21_sprintf_test_d) {
    char str1[1000];
    char str2[1000];
    short h = 34;
    int r1 = sprintf(
        str1, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
        335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
    int r2 = s21_sprintf(
        str2, "%-25.10d%-30.2d%10.12d%11d%*d%*.*d%+-25.*d%+10.2ld%-11.*hd", 253,
        335, 1234, 34, 10, 25, 5, 15, 345, 5, 666, 456789l, 5, h);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_i) {
    char str1[1000];
    char str2[1000];
    short h = 34;
    long l = 2353423523424;
    int r1 = sprintf(str1, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                    34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
    int r2 =
        s21_sprintf(str2, "%+50.i%-10.20i%10.i%012i%*.*i%-10.*i%+10.1li%*.25hi",
                    34567, 225, 5230, 125, 10, 5, 456, 10, 377, l, 12, h);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_c) {
    char str1[1000];
    char str2[1000];
    wchar_t c1 = 'T', c2 = 'Z';
    int r1 = sprintf(str1, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a', 'e',
                    'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
    int r2 = s21_sprintf(str2, "%10c%-10c%25c%-30c%25c%*c%2c%*c%lc%-50lc", 'a',
                        'e', 'f', 'R', 'Q', 10, 'P', 'L', 20, 'x', c1, c2);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_e) {
    char str1[1000];
    char str2[1000];
    int r1 =
        sprintf(str1, "%+-20e%010.*e%-*.10e%#025.7e%*.*e%*.9e%#010.*e%25.16e",
                2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
                11111.22, 16, -3245.3425342, 10, -0.00123, 235423424.43252);
    int r2 = s21_sprintf(
        str2, "%+-20e%010.*e%-*.10e%#025.7e%*.*e%*.9e%#010.*e%25.16e",
        2543.43254, 10, 1012.34567, 15, -0.00123, 45678.342532, 10, 15,
        11111.22, 16, -3245.3425342, 10, -0.00123, 235423424.43252);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_E) {
    char str1[1000] = "";
    char str2[1000] = "";
    int r1 = sprintf(str1, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.10E",
                    3456.4325, 8, 23452.43242, 5, -0.05234, 25.432523432, 10,
                    2, 53242.4242, 10, 456789.43242, 25, 1111122222.34567899,
                    2345678.23453242);
    int r2 = s21_sprintf(
        str2, "%+-25.4E%25.*E%-*.10E%#02.E%*.*E%*.15E%*E%12.10E", 3456.4325, 8,
        23452.43242, 5, -0.05234, 25.432523432, 10, 2, 53242.4242, 10,
        456789.43242, 25, 1111122222.34567899, 2345678.23453242);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_f) {
    char str1[1000];
    char str2[1000];
    int r1 = sprintf(
        str1, "%+-10.3f%+10.2f%15.10f%+*.6f%*.10f%-10.*f%25.*f%25.f%#+10.f%*.*f",
        2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
        2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
        34567.43244);
    int r2 = s21_sprintf(
        str2, "%+-10.3f%+10.2f%15.10f%+*.6f%*.10f%-10.*f%25.*f%25.f%#+10.f%*.*f",
        2546.4324, 3452.4325, 5678.43256, 25, 456789.243242, 10, 3456789123.43245,
        2, 12345.6788, 1, 34.4325432, 4325678.43242, 34567.2345432, 10, 2,
        34567.43244);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_o) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 253;
    unsigned long l = 4325234324242l;
    int r1 = sprintf(str1, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                    12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
    int r2 =
        s21_sprintf(str2, "%-25.10o%-10o%#-30.2o%#*.10o%#*.*o%25.*o%#.10ho%*lo",
                    12345, 6532, 43522, 10, 64342, 15, 2, 343, 6, 678, h, 10, l);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_x) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 345;
    unsigned long l = 52342353242l;
    int r1 = sprintf(str1,
                    "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%20.*"
                    "x%#10.*x%*.5hx%10.25lx",
                    235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                    8, 23452, 10, 34254, 3, 33334, 10, h, l);
    int r2 = s21_sprintf(str2,
                        "%x%-25x%#10x%#-10x%#10.5x%-25.34x%#-10.2x%*.*x%#*.10x%"
                        "20.*x%#10.*x%*.5hx%10.25lx",
                        235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                        3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_X) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 234;
    unsigned long l = 4325243132l;
    int r1 = sprintf(str1,
                    "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%21.*X%"
                    "#12.*X%*.8hx%14.12lX",
                    235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15, 3452,
                    8, 23452, 10, 34254, 3, 33334, 10, h, l);
    int r2 = s21_sprintf(str2,
                        "%X%-10X%15X%#-15X%#20.3X%-30.12X%#-12.3X%*.*X%#*.15X%"
                        "21.*X%#12.*X%*.8hx%14.12lX",
                        235, 1234, 3456, 12345, 222234, 68432, 34567, 10, 15,
                        3452, 8, 23452, 10, 34254, 3, 33334, 10, h, l);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_u) {
    char str1[1000];
    char str2[1000];
    unsigned short h = 115;
    unsigned long l = 123325242342l;
    int r1 =
        sprintf(str1, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu",
                4321u, 34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u,
                20, 2432u, l, h);
    int r2 = s21_sprintf(
        str2, "%u%15u%-20u%010u%-15.10u%20.*u%*.*u%*.10u%-20.12lu%19hu", 4321u,
        34567u, 2342u, 12346u, 234542u, 10, 234523u, 10, 5, 2345u, 20, 2432u, l,
        h);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_s) {
    char str1[1000];
    char str2[1000];
    wchar_t s[10] = {'h', 'e', 'l', 'l', 'o'};
    int r1 = sprintf(str1, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                    "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                    "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
    int r2 =
        s21_sprintf(str2, "%s%23s%-15s%10.s%15.2s%16.*s%*.*s%*s%15ls%15.3ls",
                    "aboba", "helloworld", "ABOBA", "ABOBBAAA", "AAABOBA", 10,
                    "QWERTY", 15, 4, "AAAAABOOOOOBAAA", 10, "ABOBAAAAA", s, s);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_p) {
    char str1[1000];
    char str2[1000];
    void *p1 = (void *)0x123456789;
    void *p2 = (void *)4325234;
    void *p3 = (void *)0x123f324b;
    void *p4 = (void *)432520;
    int r1 = sprintf(str1, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4, p2,
                    10, p3, p1, 10, p4);
    int r2 = s21_sprintf(str2, "%p%20p%-15p%10p%-15p%*p%10p%*p", p1, p2, p3, p4,
                        p2, 10, p3, p1, 10, p4);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_percent) {
    char str1[1000];
    char str2[1000];
    int r1 = sprintf(str1, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    int r2 = s21_sprintf(str2, "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%");
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_g) {
    char str1[1000];
    char str2[1000];
    int r1 = sprintf(
        str1, "%g%23g%-10g%015g%#10.5g%0#15.10g%+10.6g%#*.g%-10.*g%+#25.8g",
        2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234,
        2345.4234, 5, 23456.4324, 9, 234567.43242, 0.0000034);
    int r2 = s21_sprintf(
        str2, "%g%23g%-10g%015g%#10.5g%0#15.10g%+10.6g%#*.g%-10.*g%+#25.8g",
        2345.4324, 23445.2342, 1234.234242, 3456.3424, 0.00001234, -324234.234,
        2345.4234, 5, 23456.4324, 9, 234567.43242, 0.0000034);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(s21_sprintf_test_G) {
    char str1[1000];
    char str2[1000];
    int r1 = sprintf(
        str1,
        "%G%25G%#-15G%017G%#05.2G%#010.16G%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
        43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5,
        111.432534243243242, 4324.43242, 25, -3213.43242, 16,
        -43.43242353242342, 111.24324242, 25, 5, 0.000000342);
    int r2 = s21_sprintf(
        str2,
        "%G%25G%#-15G%017G%#05.2G%#010.16G%+#8.6G%*.8G%#-10.*G%+#12.16G%*.*G",
        43242.43242, 123432.43242, 0000.1234, -34252.43242, 1234.5,
        111.432534243243242, 4324.43242, 25, -3213.43242, 16,
        -43.43242353242342, 111.24324242, 25, 5, 0.000000342);
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(to_upper) {
    char *mass1 = s21_to_upper("hello");
    char *mass2 = "HELLO";
    ck_assert_str_eq(mass1, mass2);
    free(mass1);

    char *mass3 = s21_to_upper("NOSOK");
    char *mass4 = "NOSOK";
    ck_assert_str_eq(mass3, mass4);
    free(mass3);

    char *mass5 = s21_to_upper("");
    char *mass6 = "";
    ck_assert_str_eq(mass5, mass6);
    free(mass5);

    char *mass7 = s21_to_upper("RasSoL");
    char *mass8 = "RASSOL";
    ck_assert_str_eq(mass7, mass8);
    free(mass7);

    char *mass9 = s21_to_upper("RasSoL12Upper");
    char *mass10 = "RASSOL12UPPER";
    ck_assert_str_eq(mass9, mass10);
    free(mass9);
}
END_TEST

START_TEST(to_lower) {
    char *mass1 = s21_to_lower("HELLO");
    char *mass2 = "hello";
    ck_assert_str_eq(mass1, mass2);
    free(mass1);

    char *mass3 = s21_to_lower("nosok");
    char *mass4 = "nosok";
    ck_assert_str_eq(mass3, mass4);
    free(mass3);

    char *mass5 = s21_to_lower("");
    char *mass6 = "";
    ck_assert_str_eq(mass5, mass6);
    free(mass5);

    char *mass7 = s21_to_lower("RasSoL");
    char *mass8 = "rassol";
    ck_assert_str_eq(mass7, mass8);
    free(mass7);

    char *mass9 = s21_to_lower("RasSoL12Upper");
    char *mass10 = "rassol12upper";
    ck_assert_str_eq(mass9, mass10);
    free(mass9);
}
END_TEST

START_TEST(insert) {
    char *mass1 = s21_insert("HELLO", "new", 2);
    char *mass2 = "HEnewLLO";
    ck_assert_str_eq(mass1, mass2);
    free(mass1);

    char *mass3 = s21_insert("nosok", "kot", 3);
    char *mass4 = "noskotok";
    ck_assert_str_eq(mass3, mass4);
    free(mass3);

    char *mass5 = s21_insert("", "new", 5);
    char *mass6 = NULL;
    fail_unless(mass5 == mass6);
    free(mass5);

    char *mass7 = s21_insert("1", "new", 1);
    char *mass8 = "1new";
    ck_assert_str_eq(mass7, mass8);
    free(mass7);

    char *mass9 = s21_insert("1", "new", 0);
    char *mass10 = "new1";
    ck_assert_str_eq(mass9, mass10);
    free(mass9);
}
END_TEST

START_TEST(trim) {
    char *mass1 = s21_trim("hello", "h");
    char *mass2 = "ello";
    ck_assert_str_eq(mass1, mass2);
    free(mass1);

    char *mass3 = s21_trim("nosok", "sok");
    char *mass4 = "n";
    ck_assert_str_eq(mass3, mass4);
    free(mass3);

    char *mass5 = s21_trim("", "123");
    char *mass6 = "";
    ck_assert_str_eq(mass5, mass6);
    free(mass5);

    char *mass7 = s21_trim("1", "new");
    char *mass8 = "1";
    ck_assert_str_eq(mass7, mass8);
    free(mass7);

    char *mass9 = s21_trim("1234", "14");
    char *mass10 = "23";
    ck_assert_str_eq(mass9, mass10);
    free(mass9);
}
END_TEST

START_TEST(s21_sscanf_test_d) {
    int a, a1;
    short b, b1;
    long c, c1, d, d1, e, e1;
    a = b = c = d = 1;
    a1 = b1 = c1 = d1 = 1;
    const char str[] = "-12345 -000456000 111 +0005 666 777";
    ck_assert_int_eq(sscanf(str, "%3d %hd %ld %*d %ld %2ld", &a, &b, &c, &d, &e),
                    s21_sscanf(str, "%3d %hd %ld %*d %ld %2ld", &a1, &b1, &c1, &d1,
                                &e1));
    ck_assert_int_eq(a, a1);
    ck_assert_int_eq(b, b1);
    ck_assert_int_eq(c, c1);
    ck_assert_int_eq(d, d1);
    ck_assert_int_eq(e, e1);
}
END_TEST

START_TEST(s21_sscanf_test_c_and_s) {
    char a[40] = {'\0'}, c[40] = {'\0'}, d[40] = {'\0'};
    wchar_t b[40] = {'\0'};
    char a2[40] = {'\0'}, c2[40] = {'\0'}, d2[40] = {'\0'};
    wchar_t b2[40] = {'\0'};
    const char str[] = "lol kek cheburek morzh pisos";
    ck_assert_int_eq(sscanf(str, "%s %ls %3c %*s %s", a, b, c, d),
                    s21_sscanf(str, "%s %ls %3c %*s %s", a2, b2, c2, d2));
    ck_assert_str_eq(a, a2);
    ck_assert_str_eq(c, c2);
    ck_assert_str_eq(d, d2);
}
END_TEST

START_TEST(s21_sscanf_test_x) {
    int a1, b1, c1, d1, a2, b2, c2, d2;
    a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = 1;
    const char str[] = "1778 012 0x1111 -10 pisos";
    int r1 = sscanf(str, "%x%x%x%x", &a1, &b1, &c1, &d1);
    int r2 = s21_sscanf(str, "%x%x%x%x", &a2, &b2, &c2, &d2);
    ck_assert_int_eq(r1, r2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(s21_sscanf_test_i) {
    int a1, b1, c1, d1, a2, b2, c2, d2;
    a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = 1;
    const char str[] = "1778 012 0x1Aa8 -10 pisos";
    int r1 = sscanf(str, "%i%i%i%i", &a1, &b1, &c1, &d1);
    int r2 = s21_sscanf(str, "%i%i%i%i", &a2, &b2, &c2, &d2);
    ck_assert_int_eq(r1, r2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(s21_sscanf_test_o) {
    int a1, b1, c1, d1, a2, b2, c2, d2;
    a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = 1;
    const char str[] = "1775 012 0 -10 pisos";
    int r1 = sscanf(str, "%o%o%o%o", &a1, &b1, &c1, &d1);
    int r2 = s21_sscanf(str, "%o%o%o%o", &a2, &b2, &c2, &d2);
    ck_assert_int_eq(r1, r2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(s21_sscanf_test_p) {
    int integer = 5;
    int *p1a = &integer;
    int *p2a;
    int *p3a;
    char temp[50] = {'\0'};
    sprintf(temp, "%p", p1a);
    sscanf(temp, "%p", &p2a);
    s21_sscanf(temp, "%p", &p3a);
    ck_assert_ptr_eq(p2a, p3a);
}
END_TEST

START_TEST(s21_sscanf_test_n_and_percent) {
    int a1, b1, c1, d1, a2, b2, c2, d2;
    a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = 1;
    const char str[] = "-12345%    -000456000    111    0005 pisos";
    int r1 = s21_sscanf(str, "%d%% %d %n %d", &a1, &b1, &c1, &d1);
    int r2 = sscanf(str, "%d%% %d %n %d", &a2, &b2, &c2, &d2);
    ck_assert_int_eq(r1, r2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(s21_sscanf_test_f_and_e) {
    float a1, b1, a2, b2;
    double c1, c2;
    long double d1, d2;
    a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = 1.1;
    const char str[] = "-12345.445 12.34e+07 -0.0 1234e-07 pisos";
    s21_sscanf(str, "%f%f%lf%Lf", &a1, &b1, &c1, &d1);
    sscanf(str, "%f%f%lf%Lf", &a2, &b2, &c2, &d2);
    ck_assert_float_eq(a1, a2);
    ck_assert_float_eq(b1, b2);
    ck_assert_float_eq(c1, c2);
    ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(s21_sscanf_test_u) {
    unsigned int a1, b1, a2, b2;
    unsigned short c1, c2;
    unsigned long d1, d2;
    a1 = a2 = b1 = b2 = c1 = c2 = d1 = d2 = 1;
    const char str[] = "0 0002 -1 -1234 666 pisos";
    int r1 = sscanf(str, "%*u%u%u%hu%lu", &a1, &b1, &c1, &d1);
    int r2 = s21_sscanf(str, "%*u%u%u%hu%lu", &a2, &b2, &c2, &d2);
    ck_assert_int_eq(r1, r2);
    ck_assert_int_eq(a1, a2);
    ck_assert_int_eq(b1, b2);
    ck_assert_int_eq(c1, c2);
    ck_assert_int_eq(d1, d2);
}
END_TEST

int main() {
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_memchr1);
    tcase_add_test(tc1_1, test_memcmp2);
    tcase_add_test(tc1_1, test_memcpy3);
    tcase_add_test(tc1_1, test_memmove4);
    tcase_add_test(tc1_1, test_memset5);
    tcase_add_test(tc1_1, test_strcat6);
    tcase_add_test(tc1_1, test_strncat7);
    tcase_add_test(tc1_1, test_strchr8);
    tcase_add_test(tc1_1, test_strcmp9);
    tcase_add_test(tc1_1, test_strncmp10);
    tcase_add_test(tc1_1, test_strcpy11);
    tcase_add_test(tc1_1, test_strncpy12);
    tcase_add_test(tc1_1, test_strcspn13);
    tcase_add_test(tc1_1, test_strerror14);
    tcase_add_test(tc1_1, test_strlen15);
    tcase_add_test(tc1_1, test_strpbrk16);
    tcase_add_test(tc1_1, test_strrchr17);
    tcase_add_test(tc1_1, test_strspn18);
    tcase_add_test(tc1_1, test_strstr19);
    tcase_add_test(tc1_1, test_strtok20);

    tcase_add_test(tc1_1, s21_sprintf_test1);
    tcase_add_test(tc1_1, s21_sprintf_test2);
    tcase_add_test(tc1_1, s21_sprintf_test3);
    tcase_add_test(tc1_1, s21_sprintf_test4);
    tcase_add_test(tc1_1, s21_sprintf_test_d);
    tcase_add_test(tc1_1, s21_sprintf_test_i);
    tcase_add_test(tc1_1, s21_sprintf_test_c);
    tcase_add_test(tc1_1, s21_sprintf_test_e);
    tcase_add_test(tc1_1, s21_sprintf_test_E);
    tcase_add_test(tc1_1, s21_sprintf_test_f);
    tcase_add_test(tc1_1, s21_sprintf_test_o);
    tcase_add_test(tc1_1, s21_sprintf_test_x);
    tcase_add_test(tc1_1, s21_sprintf_test_X);
    tcase_add_test(tc1_1, s21_sprintf_test_u);
    tcase_add_test(tc1_1, s21_sprintf_test_s);
    tcase_add_test(tc1_1, s21_sprintf_test_p);
    tcase_add_test(tc1_1, s21_sprintf_test_percent);
    tcase_add_test(tc1_1, s21_sprintf_test_g);
    tcase_add_test(tc1_1, s21_sprintf_test_G);

    tcase_add_test(tc1_1, to_upper);
    tcase_add_test(tc1_1, to_lower);
    tcase_add_test(tc1_1, insert);
    tcase_add_test(tc1_1, trim);

    tcase_add_test(tc1_1, s21_sscanf_test_d);
    tcase_add_test(tc1_1, s21_sscanf_test_c_and_s);
    tcase_add_test(tc1_1, s21_sscanf_test_x);
    tcase_add_test(tc1_1, s21_sscanf_test_i);
    tcase_add_test(tc1_1, s21_sscanf_test_o);
    tcase_add_test(tc1_1, s21_sscanf_test_p);
    tcase_add_test(tc1_1, s21_sscanf_test_n_and_percent);
    tcase_add_test(tc1_1, s21_sscanf_test_f_and_e);
    tcase_add_test(tc1_1, s21_sscanf_test_u);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
