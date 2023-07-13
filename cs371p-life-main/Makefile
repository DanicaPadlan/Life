.DEFAULT_GOAL := all

ASTYLE        := astyle
CHECKTESTDATA := checktestdata
CPPCHECK      := cppcheck
DOXYGEN       := doxygen
SHELL         := bash

ifeq ($(shell uname -s), Life)
    BOOST    := /usr/local/include/boost
    CXX      := clang++
    CXXFLAGS := --coverage -g -std=c++20 -I/usr/local/include/ -Wall -Wextra -Wpedantic
    GCOV     := llvm-cov gcov
    GTEST    := /usr/local/include/gtest
    LDFLAGS  := -lgtest -lgtest_main
    LIB      := /usr/local/lib
    VALGRIND := valgrind
else ifeq ($(shell uname -p), unknown)
    BOOST    := /usr/include/boost
    CXX      := g++
    CXXFLAGS := --coverage -g -std=c++20 -Wall -Wextra -Wpedantic
    GCOV     := gcov
    GTEST    := /usr/include/gtest
    LDFLAGS  := -lgtest -lgtest_main -pthread
    LIB      := /usr/lib
    VALGRIND := valgrind
else
    BOOST    := /usr/local/opt/boost-1.67/include/boost
    CXX      := g++-11
    CXXFLAGS := --coverage -g -std=c++20 -Wall -Wextra -Wpedantic
    GCOV     := gcov-11
    GTEST    := /usr/local/include/gtest
    LDFLAGS  := -L/usr/local/opt/boost-1.77/lib/ -lgtest -lgtest_main -pthread
    LIB      := /usr/local/lib
    VALGRIND := valgrind-3.17
endif

# run docker
docker:
	docker run --rm -it -v $(PWD):/usr/gcc -w /usr/gcc gpdowning/gcc

# get git config
config:
	git config -l

# get git log
Life.log.txt:
	git log > Life.log.txt

# get git status
status:
	make clean
	@echo
	git branch
	git remote -v
	git status

# download files from the Life code repo
pull:
	make clean
	@echo
	git pull
	git status

# upload files to the Life code repo
push:
	make clean
	@echo
	git add .gitignore
	git add .gitlab-ci.yml
	git add Life.hpp
	-git add Life.log.txt
	-git add html
	git add Makefile
	git add Makefile.mk
	git add README.md
	git add RunLifeCell.cpp
	-git add RunLife.ctd.txt
	git add TestLife.cpp
	git commit -m "another commit"
	git push
	git status

#NOTE: changed order of compilation of parent/child order
# compile run harness
RunLifeCell: AbstractCell.cpp AbstractCell.hpp ConwayCell.cpp ConwayCell.hpp FredkinCell.cpp FredkinCell.hpp Cell.cpp Cell.hpp Life.hpp RunLifeCell.cpp 
	-$(CPPCHECK) AbstractCell.cpp
	-$(CPPCHECK) FredkinCell.cpp
	-$(CPPCHECK) Cell.cpp
	-$(CPPCHECK) RunLifeCell.cpp
	$(CXX) $(CXXFLAGS) FredkinCell.cpp ConwayCell.cpp AbstractCell.cpp Cell.cpp Life.hpp RunLifeCell.cpp -o RunLifeCell

RunLifeConway: AbstractCell.cpp AbstractCell.hpp ConwayCell.cpp ConwayCell.hpp FredkinCell.cpp FredkinCell.hpp Cell.cpp Cell.hpp Life.hpp RunLifeConway.cpp
	-$(CPPCHECK) AbstractCell.cpp
	-$(CPPCHECK) ConwayCell.cpp
	-$(CPPCHECK) Cell.cpp
	-$(CPPCHECK) RunLifeConway.cpp
	$(CXX) $(CXXFLAGS) FredkinCell.cpp ConwayCell.cpp AbstractCell.cpp Cell.cpp Life.hpp RunLifeConway.cpp -o RunLifeConway

RunLifeFredkin: AbstractCell.cpp AbstractCell.hpp ConwayCell.cpp ConwayCell.hpp FredkinCell.cpp FredkinCell.hpp Cell.cpp Cell.hpp Life.hpp RunLifeFredkin.cpp 
	-$(CPPCHECK) AbstractCell.cpp
	-$(CPPCHECK) FredkinCell.cpp
	-$(CPPCHECK) Cell.cpp
	-$(CPPCHECK) RunLifeFredkin.cpp
	$(CXX) $(CXXFLAGS) FredkinCell.cpp ConwayCell.cpp AbstractCell.cpp Cell.cpp Life.hpp RunLifeFredkin.cpp -o RunLifeFredkin

# compile test harness
TestLife: AbstractCell.cpp Cell.cpp ConwayCell.cpp FredkinCell.cpp TestLife.cpp
	-$(CPPCHECK) AbstractCell.cpp
	-$(CPPCHECK) FredkinCell.cpp
	-$(CPPCHECK) Cell.cpp
	-$(CPPCHECK) TestLife.cpp
	$(CXX) $(CXXFLAGS) FredkinCell.cpp ConwayCell.cpp AbstractCell.cpp Cell.cpp Life.hpp TestLife.cpp -o TestLife $(LDFLAGS)

# run/test files, compile with make all
FILES :=          \
    RunLifeCell  \
	RunLifeConway \
	RunLifeFredkin \
	TestLife

# compile all
all: $(FILES)

# execute test harness with coverage
test: TestLife
	$(VALGRIND) ./TestLife
ifeq ($(shell uname -s), Life)
	$(GCOV) TestLife.cpp | grep -B 2 "cpp.gcov"
else
	$(GCOV) TestLife-TestLife.cpp | grep -B 2 "cpp.gcov"

endif

# clone the Life test repo
../cs371p-life-tests:
	git clone https://gitlab.com/gpdowning/cs371p-life-tests.git ../cs371p-life-tests

#add more files
# test files in the Life test repo
#T_FILES := `ls ../cs371p-life-tests/*.in.txt`

CONWAY_FILES := `ls ../cs371p-life-tests/*Conway.in.txt`

# generate a random input file
ctd-generate:
	for v in {1}; do $(CHECKTESTDATA) -g RunLife.ctd.txt >> RunLife.gen.txt; done

# execute the run harness against a test file in the Life test repo and diff with the expected output
#tests not running in order, how to specify which sim to run
../cs371p-life-tests/%: RunLifeConway RunLifeFredkin RunLifeCell
	$(CHECKTESTDATA) RunLife.ctd.txt $@Conway.in.txt
	./RunLifeConway < $@Conway.in.txt > RunLifeConway.tmp.txt
	diff RunLifeConway.tmp.txt $@Conway.out.txt

	$(CHECKTESTDATA) RunLife.ctd.txt $@Fredkin.in.txt
	./RunLifeFredkin < $@Fredkin.in.txt > RunLifeFredkin.tmp.txt
	diff RunLifeFredkin.tmp.txt $@Fredkin.out.txt

	$(CHECKTESTDATA) RunLife.ctd.txt $@Cell.in.txt
	./RunLifeCell < $@Cell.in.txt > RunLifeCell.tmp.txt
	diff RunLifeCell.tmp.txt $@Cell.out.txt

# execute the run harness against your test files in the Life test repo and diff with the expected output
run: ../cs371p-life-tests
	-make ../cs371p-life-tests/DanicaPadlan-RunLifeCell # change gpdowning to your GitLab-ID

# execute the run harness against all of the test files in the Life test repo and diff with the expected output
run-all: ../cs371p-life-tests
	-for v in $(CONWAY_FILES); do make $${v/Conway.in.txt/}; done

# auto format the code
format:

	$(ASTYLE) TestLife.cpp
	$(ASTYLE) ConwayCell.cpp
	$(ASTYLE) FredkinCell.cpp
	$(ASTYLE) Cell.cpp
	$(ASTYLE) AbstractCell.cpp
	$(ASTYLE) RunLifeCell.cpp
	$(ASTYLE) RunLifeConway.cpp
	$(ASTYLE) RunLifeFredkin.cpp
	$(ASTYLE) ConwayCell.hpp
	$(ASTYLE) FredkinCell.hpp
	$(ASTYLE) Cell.hpp
	$(ASTYLE) AbstractCell.hpp

# you must edit Doxyfile and
# set EXTRACT_ALL     to YES
# set EXTRACT_PRIVATE to YES
# set EXTRACT_STATIC  to YES
# create Doxfile
Doxyfile:
	$(DOXYGEN) -g

# create html directory
html: Doxyfile
	$(DOXYGEN) Doxyfile

# check files, check their existence with make check
C_FILES :=            \
    .gitignore        \
    .gitlab-ci.yml    \
    Life.log.txt \
    html

# check the existence of check files
check: $(C_FILES)

# remove executables and temporary files
clean:
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  *.gen.txt
	rm -f  *.tmp.txt
	rm -f  RunLife
	rm -f  TestLife
	rm -rf *.dSYM

# remove executables, temporary files, and generated files
scrub:
	make clean
	rm -f  Life.log.txt
	rm -f  Doxyfile
	rm -rf html
	rm -rf latex

# output versions of all tools
versions:
	uname -p

	@echo
	uname -s

	@echo
	which $(ASTYLE)
	@echo
	$(ASTYLE) --version

	@echo
	which $(CHECKTESTDATA)
	@echo
	$(CHECKTESTDATA) --version | head -n 1

	@echo
	which $(CPPCHECK)
	@echo
	$(CPPCHECK) --version

	@echo
	which $(DOXYGEN)
	@echo
	$(DOXYGEN) --version

	@echo
	which $(CXX)
	@echo
	$(CXX) --version | head -n 1

	@echo
	which $(GCOV)
	@echo
	$(GCOV) --version | head -n 1

	@echo
	which git
	@echo
	git --version

	@echo
	which make
	@echo
	make --version | head -n 1

ifneq ($(VALGRIND),)
	@echo
	which $(VALGRIND)
	@echo
	$(VALGRIND) --version
endif

	@echo
	which vim
	@echo
	vim --version | head -n 1

	@echo
	grep "#define BOOST_LIB_VERSION " $(BOOST)/version.hpp

	@echo
	ls -al $(GTEST)/gtest.h
	@echo
	pkg-config --modversion gtest
	@echo
	ls -al $(LIB)/libgtest*.a
