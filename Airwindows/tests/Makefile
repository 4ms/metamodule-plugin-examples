TEST_DIR ?= ./
BUILDDIR = $(TEST_DIR)/build
RYMLDIR = ../shared/patch_convert/ryml/rapidyaml

TEST_SOURCES = $(TEST_DIR)/doctest.cc
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_test.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/*_tests.cpp)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cc)
TEST_SOURCES += $(wildcard $(TEST_DIR)/test_*.cpp)
TEST_SOURCES += ../airwin2rack/src/airwin_consolidated_base.cpp

CXXFLAGS = 	-Wall \
		 	-std=c++23 \
			-I$(DOCTEST_DIR) \
			-I$(TEST_DIR) \
			-I$(TEST_DIR)/stubs \
			-I../$(TEST_DIR)/stubs \
			-isystem $(TEST_DIR) \
			-DTESTPROJECT \

### Boilerplate below here:

OBJECTS   = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(TEST_SOURCES))))
DEPDIR := $(BUILDDIR)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$(basename $<).d
TMPFILE = $(BUILDDIR)/runtests.out

.PHONY: all tests clean

all: tests

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CC) -c $(DEPFLAGS) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cc
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) -c $(DEPFLAGS) $(CXXFLAGS) $< -o $@

$(BUILDDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(info Building $<)
	@$(CXX) -c $(DEPFLAGS) $(CXXFLAGS) $< -o $@


tests: $(BUILDDIR)/runtests 
	@$(BUILDDIR)/runtests --out=$(TMPFILE) && echo "[√] Unit tests passed: $(notdir $(PWD))" || cat $(TMPFILE)

$(BUILDDIR)/runtests: $(OBJECTS)
	$(info Building $(BUILDDIR)/runtests) 
	@$(CXX) $(LDFLAGS) -o $@ $(OBJECTS)

clean:
	rm -rf $(BUILDDIR)

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(addprefix $(DEPDIR)/, $(addsuffix .d, $(basename $(TEST_SOURCES))))
$(DEPFILES):

include $(wildcard $(DEPFILES))

