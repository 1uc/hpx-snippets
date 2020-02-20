HPX_DIR := $(HOME)/third_party/hpx-clang

LDFLAGS := -L $(HPX_DIR)/lib -lhpx -lhpx_iostreams -lboost_program_options -lboost_system

CC := clang
CXX := clang++
CXXFLAGS := $(CXXFLAGS) -g -std=c++17 -I $(HPX_DIR)/include

TARGETS := channel

.PHONY: all clean

all: $(TARGETS)

$(TARGETS): %: %.cpp

clean:
	@rm -f $(TARGETS)
