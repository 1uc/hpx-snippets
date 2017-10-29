HPX_DIR := $(HOME)/third_party/hpx

INCLUDE := -I $(HPX_DIR)/include
LIBS := -L $(HPX_DIR)/lib -lhpx -lhpx_iostreams -lboost_program_options -lboost_system

simple_direct_action: %: %.cpp
	$(CXX) $(INCLUDE) $< $(LIBS) -o $@
