include prorab.mk

this_name := tests

this_cxxflags += -Wall
# this_cxxflags += -Werror
this_cxxflags += -DDEBUG
this_cxxflags += -fstrict-aliasing
this_cxxflags += -std=c++14
this_cxxflags += -g

this_srcs += main.cpp

this_ldlibs += -lsvgdom -lpapki -lstdc++
this_ldflags += -L$(d)../../src/build

ifeq ($(os), linux)
    this_cxxflags += -fPIC
    this_ldlibs +=
else ifeq ($(os), macosx)
    this_cxxflags += -stdlib=libc++ # this is needed to be able to use c++11 std lib
    this_ldlibs += -lc++
else ifeq ($(os),windows)
endif

this_no_install := true

$(eval $(prorab-build-app))

this_dirs := $(subst /, ,$(d))
this_test := $(word $(words $(this_dirs)),$(this_dirs))

define this_rules
test:: $(prorab_this_name)
$(.RECIPEPREFIX)@myci-running-test.sh $(this_test)
$(.RECIPEPREFIX)$(a)cp $(d)../../src/build/*.dll $(d) || true
$(.RECIPEPREFIX)$(a)LD_LIBRARY_PATH=$(d)../../src/build DYLD_LIBRARY_PATH=$$$$LD_LIBRARY_PATH $(d)./tests; \
		if [ $$$$? -ne 0 ]; then myci-error.sh "test failed"; exit 1; fi
$(.RECIPEPREFIX)@myci-passed.sh
endef
$(eval $(this_rules))

# add dependency on libsvgdom
$(prorab_this_name): $(abspath $(d)../../src/build/libsvgdom$(dot_so))

$(eval $(call prorab-include, ../../src/makefile))
