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

TAGS = nbt_base nbt_end nbt_byte nbt_short nbt_int nbt_long nbt_float nbt_double nbt_byte_array nbt_string nbt_list nbt_int_array
SOURCES = nbt_registry $(foreach tag,$(TAGS),tags/$(tag))

.PHONY : clean all dll

all : dll

clean :
	rm -rf $(BUILD) $(TEST)/*$(EXE)

dll : $(foreach src,$(SOURCES),$(BUILD)/$(src)$(OBJ))
	$(CPP) $(CPPAR) -shared -fpic -o$(BUILD)/cpp-nbt$(DLL) $^


$(BUILD)/%$(OBJ) : src/%.cpp
	@mkdir -p $(dir $@) 1>$(nul) 2>$(nul)
	$(CPP) $(CPPAR) -c -o$@ $^

%$(EXE) : %.cpp
	$(CPP) $(CPPAR) -Isrc -Lout -lcpponfig -o$@ $^
