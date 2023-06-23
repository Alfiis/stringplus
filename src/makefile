CC = gcc -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
TEST_FLAGS=-I -L -lcheck `pkg-config --cflags --libs check`
SRCS = 	s21_strlen.c \
		s21_strcpy.c \
		s21_strncpy.c \
		s21_strcmp.c \
		s21_strncmp.c \
		s21_memset.c \
		s21_itoa.c \
		s21_memcpy.c \
		s21_memmove.c \
		s21_memchr.c \
		s21_memcmp.c \
		s21_strcat.c \
		s21_strncat.c \
		s21_strchr.c \
		s21_strrchr.c \
		s21_strstr.c \
		s21_strpbrk.c \
		s21_strspn.c \
		s21_strtok.c \
        s21_strcspn.c \
        s21_strerror.c \
		s21_trim.c \
        s21_to_lower.c \
		s21_to_upper.c \
		s21_insert.c \
		s21_sprintf.c \
		s21_sscanf.c
OBJ = *.o
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC += -D OS_MAC
	TEST_FLAGS =-lcheck
endif
ifeq ($(OS), linux)
	CC += -D OS_LINUX
	TEST_FLAGS =-lpthread -lcheck -pthread -lrt -lm -lsubunit
endif

all: clean s21_string.a test gcov_report
s21_string.a: 
	$(CC) -c $(SRCS)
	@ar rcs s21_string.a $(OBJ)
test: s21_test.c s21_string.a
	$(CC) $< s21_string.a -lcheck -o s21_test
gcov_report: s21_string.a
	@gcc $(GCOVFLAGS) s21_test.c -lcheck $(SRCS) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./GcovReport.* 
check: s21_string.a
	@cppcheck *.h *.c
	@cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	@python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	@$(CC) s21_test.c s21_string.a -lcheck
	@CK_FORK=no leaks --atExit -- ./a.out
	@rm CPPLINT.cfg
clean:
	@rm -rf ./*.o ./*.a ./a.out ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./sprintf_o ./sscanf_o ./string_o ./*.dSYM ./s21_test ./CPPLINT*
rebuild:
	$(MAKE) clean
	$(MAKE) all
    
#drink some beer 🍺🍺🍺🍺🍺