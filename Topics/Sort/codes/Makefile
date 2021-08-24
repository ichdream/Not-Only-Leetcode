
# set compiler defaults for OSX versus *nix
# left people override either
OS := $(shell uname)
ifeq ($(OS), Darwin)
ifndef CC
export CC = $(if $(shell which clang), clang, gcc )
endif
ifndef CXX
export CXX = $(if $(shell which cl;ang++), clang++, g++)
endif
else
# linux defaults
ifndef CC
export CC = gcc
endif
ifndef CXX
export CXX = g++
endif
endif


export CFLAGS = -std=c++11 -Wall -Wno-unknown-pragmas

ifeq ($(TEST_COVER), 1)
	CFLAGS += -g -O0 -fprofile-arcs -ftest-coverage
else
	CFLAGS += -O3 -funroll-loops
endif

ifndef LINT_LANG
	LINT_LANG = "all"
endif

.PHONY: clean all

sortMain: sortMain.cpp
	@mkdir -p $(@D)
	$(CXX) $(CFLAGS) $< -o $@


all: clean 


clean:
	$(RM) -rf sortMain

	