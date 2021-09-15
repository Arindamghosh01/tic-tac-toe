# +--------------------+
# |                    |
# |   GENERAL CONFIG   |
# |                    |
# +--------------------+

PROBLEM_NAME := main
DEBUG := true
LANG := cpp

ifeq ($(LANG),cpp)
TARGET := $(PROBLEM_NAME)
EXECUTE := $(TARGET).exe
CLEAN_TARGETS := $(TARGET).exe
else ifeq ($(LANG),python)
TARGET := $(PROBLEM_NAME).py
EXECUTE := python $(TARGET)
CLEAN_TARGETS :=
else
$(error "Unknown language; please set TARGET, EXECUTE, and CLEAN_TARGETS manually")
endif

CXX := g++
CXXFLAGS := -DLOCAL_DEFINE -std=c++17 -O2 -Wall -Wextra -pedantic -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -Wno-unused-result -Wno-sign-conversion
DEBUG_CXXFLAGS := -D_FORTIFY_SOURCE=2
DEBUG_CXXFLAGS += -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC


# +-------------------+
# |                   |
# |   GENERAL RULES   |
# |                   |
# +-------------------+

all: $(TARGET)
.PHONY: all

clean:
	-rm -rf $(CLEAN_TARGETS) *.o
.PHONY: clean

rebuild: clean all
.PHONY: rebuild

# +---------------------+
# |                     |
# |   C++ COMPILATION   |
# |                     |
# +---------------------+

ifeq ($(DEBUG),true)
CXXFLAGS += $(DEBUG_CXXFLAGS)
endif

%: %.cpp %.exe # Cancel the builtin rule

