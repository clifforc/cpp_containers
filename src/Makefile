DATE = $(shell date -R)
CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17 -pedantic -g

DB = -g -O0
OBJ = obj
SRC_DIR = src
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, $(OBJ)/%.o, $(SOURCES))
TEST = s21_test
TEST_DIR = ./tests/
RM_EXTS := o a out gcno gcda gcov info html css

OS := $(shell uname)
UBUNTU := $(shell hostnamectl | grep -o 'Ubuntu')
MAC_X86 := $(shell uname -a | grep -o _X86_64)
MAC_M1 := $(shell uname -a | grep -o _ARM64)

GTEST_INCLUDE = $(shell brew --prefix googletest)/include
GTEST_LIB = $(shell brew --prefix googletest)/lib
GTEST_FLAGS = -DGTEST_HAS_PTHREAD=1 -I$(GTEST_INCLUDE) -L$(GTEST_LIB) -lgtest

ifeq ($(OS), Linux)
    TEST_LIBS = $(GTEST_FLAGS) -lpthread
    MATH = -lm
    OPEN = xdg-open
else ifeq ($(UBUNTU), Ubuntu)
    TEST_LIBS = $(GTEST_FLAGS) -lpthread
    OPEN = open
endif

ifeq ($(MAC_M1), _ARM64)
    TEST_LIBS := $(GTEST_FLAGS)
    OPEN = open
endif
ifeq ($(MAC_X86), _X86_64)
    TEST_LIBS = $(GTEST_FLAGS) -lpthread
    OPEN = open
endif

all: test

build: all

repo:
	mkdir -p $(OBJ)

$(OBJ)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


test:
	$(CXX) $(CXXFLAGS)  containers/tests/*.cpp $(TEST_LIBS) -o $(TEST)
	./$(TEST)

ifeq ($(OS),Linux)
	valgrind -s --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(TEST)
else
	leaks --atExit -- ./$(TEST)
endif


gcov_flag:
	$(eval CXXFLAGS += --coverage)

gcov_report: clean test
	$(CXX) $(CXXFLAGS) $(GTEST_FLAGS) --coverage containers/tests/*.cpp $(TEST_LIBS) -o report.out
	./report.out
	mkdir -p report
	lcov --ignore-errors deprecated --ignore-errors inconsistent --no-external --capture --directory . --output-file coverage.info --rc lcov_branch_coverage=1
	genhtml --ignore-errors inconsistent,corrupt coverage.info -o report
	rm -rf *.gcno *.gcda *.gcov *.info
	$(OPEN) report/index.html
	#gcovr --html-details -o report.html
	#$(OPEN) report.html

format-check:
	@cp ../materials/linters/.clang-format ./
	@find ./ -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -n {} \;
	@rm ./.clang-format
.PHONY: format-check

format:
	@cp ../materials/linters/.clang-format ./
	@find ./ -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i {} \;
	@rm ./.clang-format
.PHONY: format
cppcheck :
	@find ./ -type f -name "*.h" -exec cppcheck --enable=all --suppress=missingIncludeSystem --std=c++17 \
    --language=c++ --suppress=operatorEqVarError --suppress=unusedFunction --suppress=noExplicitConstructor {} \
    --suppress=shadowFunction \;
.PHONY: cppcheck

rebuild: clean build

clean:
	rm -rf $(TEST) *.o *.a *.gcno *.gcda *.gcov *.info report a.out *.dSYM $(OBJ)
	@for ext in $(RM_EXTS); do \
	find ./ -type f -name "*.$$ext" -exec rm {} \;; \
	done
	@rm -rf ./report
	@rm -rf ./$(OBJ)

.PHONY: clean
reset:
	reset | bash