# The MIT License (MIT)

# Copyright (c) 2015 nabijaczleweli

# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

include configMakefile

PRIMITIVE_TAGS = nbt_byte nbt_short nbt_int nbt_long nbt_float nbt_double
ARRAY_TAGS = nbt_byte_array nbt_int_array
COMPLEX_TAGS = nbt_list nbt_compound
SEGREGATED_TAGS = $(foreach tagt,PRIMITIVE_TAGS ARRAY_TAGS COMPLEX_TAGS,$(foreach tag,$($(tagt)),$(shell echo $(subst _TAGS,,$(tagt)) | tr A-Z a-z)/$(tag)))
TAGS = nbt_base nbt_end nbt_string $(SEGREGATED_TAGS)
SOURCES = nbt_registry nbt_manager $(foreach tag,$(TAGS),tags/$(tag))

.PHONY : clean all dll stlib

all : dll stlib

clean :
	rm -rf $(BUILD)

dll : $(BUILD)/$(PREDLL)cpp-nbt$(DLL)
stlib : $(BUILD)/libcpp-nbt$(ARCH)


$(BUILD)/$(PREDLL)cpp-nbt$(DLL) : $(foreach src,$(SOURCES),$(BUILD)/obj/$(src)$(OBJ))
	$(CXX) $(CPPAR) -shared $(PIC) -o$@ $^

$(BUILD)/libcpp-nbt$(ARCH) : $(foreach src,$(SOURCES),$(BUILD)/obj/$(src)$(OBJ))
	ar crs $@ $^


$(BUILD)/obj/%$(OBJ) : src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CPPAR) $(PIC) -Iinclude -c -o$@ $^
