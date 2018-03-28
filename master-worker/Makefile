HPX_DIR := $(HOME)/third_party/hpx

INCLUDE := -I $(HPX_DIR)/include
LIBS := -L $(HPX_DIR)/lib -lhpx -lhpx_iostreams -lboost_program_options -lboost_system

.PHONY: all

all: for_each
# all: for_each remote_action

remote_action: %: %.cpp
	$(CXX) $(INCLUDE) $< $(LIBS) -o $@

for_each: %: %.cpp
	$(CXX) $(INCLUDE) $< $(LIBS) -o $@
