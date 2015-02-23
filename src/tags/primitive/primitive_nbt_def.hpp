// The MIT License (MIT)

// Copyright (c) 2015 nabijaczleweli

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#ifndef NBT_CPP_NBT_PRIMITIVE_DEFINITION
	// `nbt_##class_suffix` class must be brought to default namespace (as by using namespace cpp_nbt)
	#define NBT_CPP_NBT_PRIMITIVE_DEFINITION(class_suffix, contained_type, tag_id) \
const unsigned char nbt_##class_suffix::nbt_##class_suffix##_id = tag_id; \
\
\
nbt_##class_suffix::nbt_##class_suffix() : nbt_base(), payload(0) {} \
nbt_##class_suffix::nbt_##class_suffix(contained_type value) : nbt_base(), payload(value) {} \
nbt_##class_suffix::nbt_##class_suffix(const nbt_##class_suffix & other) : nbt_base(other), payload(other.payload) {} \
nbt_##class_suffix::nbt_##class_suffix(nbt_##class_suffix && other) : nbt_base(std::move(other)), payload(other.payload) {} \
\
nbt_##class_suffix::~nbt_##class_suffix() {} \
\
void nbt_##class_suffix::swap(nbt_base & with) { \
	swap(dynamic_cast<nbt_##class_suffix &>(with)); \
} \
\
void nbt_##class_suffix::swap(nbt_##class_suffix & with) { \
	std::swap(payload, with.payload); \
} \
\
nbt_##class_suffix & nbt_##class_suffix::operator=(const nbt_##class_suffix & from) { \
	nbt_##class_suffix temp(from); \
	swap(temp); \
	return *this; \
} \
\
bool nbt_##class_suffix::operator==(const nbt_base & to) { \
	return operator==(dynamic_cast<const nbt_##class_suffix &>(to)); \
} \
\
bool nbt_##class_suffix::operator==(const nbt_##class_suffix & to) { \
	return nbt_base::operator==(to) && payload == to.payload; \
} \
\
void nbt_##class_suffix::read(std::istream & from) { \
	from.get(static_cast<char *>(static_cast<void *>(&payload)), sizeof(payload)); \
} \
\
void nbt_##class_suffix::write(std::ostream & to) const { \
	to.write(static_cast<const char *>(static_cast<const void *>(&payload)), sizeof(payload)); \
} \
\
unsigned char nbt_##class_suffix::id() const { \
	return nbt_##class_suffix##_id; \
} \
\
nbt_base * nbt_##class_suffix::clone() const { \
	return new nbt_##class_suffix(*this); \
} \
\
const contained_type & nbt_##class_suffix::value() const { \
	return payload; \
} \
\
contained_type & nbt_##class_suffix::value() { \
	return payload; \
}
#endif
