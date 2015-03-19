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


#include <memory>


#ifndef NBT_CPP_NBT_ARRAY_DEFINITION
	// `nbt_##class_suffix##_array` class must be brought to default namespace (as by using namespace cpp_nbt)
	#define NBT_CPP_NBT_ARRAY_DEFINITION(class_suffix, contained_type, tag_id) \
const unsigned char nbt_##class_suffix##_array::nbt_##class_suffix##_array_id = tag_id; \
\
\
nbt_##class_suffix##_array::nbt_##class_suffix##_array() : nbt_base() {} \
nbt_##class_suffix##_array::nbt_##class_suffix##_array(const std::vector<contained_type> & value) : nbt_base(), payload(value) {} \
nbt_##class_suffix##_array::nbt_##class_suffix##_array(const nbt_##class_suffix##_array & other) : nbt_base(other), payload(other.payload) {} \
nbt_##class_suffix##_array::nbt_##class_suffix##_array(nbt_##class_suffix##_array && other) : nbt_base(std::move(other)), payload(std::move(other.payload)) {} \
\
void nbt_##class_suffix##_array::swap(nbt_base & with) { \
	swap(dynamic_cast<nbt_##class_suffix##_array &>(with)); \
} \
\
void nbt_##class_suffix##_array::swap(nbt_##class_suffix##_array & with) { \
	payload.swap(with.payload); \
} \
\
nbt_##class_suffix##_array & nbt_##class_suffix##_array::operator=(const nbt_##class_suffix##_array & from) { \
	nbt_##class_suffix##_array temp(from); \
	swap(temp); \
	return *this; \
} \
\
bool nbt_##class_suffix##_array::operator==(const nbt_base & to) { \
	return operator==(dynamic_cast<const nbt_##class_suffix##_array &>(to)); \
} \
\
bool nbt_##class_suffix##_array::operator==(const nbt_##class_suffix##_array & to) { \
	return nbt_base::operator==(to) && payload == to.payload; \
} \
\
void nbt_##class_suffix##_array::read(std::istream & from) { \
	int * length = new int; \
	from.read(static_cast<char *>(static_cast<void *>(length)), sizeof(*length)); \
\
	payload.resize(*length); \
	from.read(static_cast<char *>(static_cast<void *>(payload.data())), *length * sizeof(contained_type)); \
\
	delete length; length = nullptr; \
} \
\
void nbt_##class_suffix##_array::write(std::ostream & to) const { \
	const int * length = new int(payload.size()); \
	to.write(static_cast<const char *>(static_cast<const void *>(length)), sizeof(*length)); \
\
	to.write(static_cast<const char *>(static_cast<const void *>(payload.data())), payload.size() * sizeof(contained_type)); \
\
	delete length; length = nullptr; \
} \
\
unsigned char nbt_##class_suffix##_array::id() const { \
	return nbt_##class_suffix##_array##_id; \
} \
\
std::unique_ptr<nbt_base> nbt_##class_suffix##_array::clone() const { \
	return std::make_unique<nbt_##class_suffix##_array>(*this); \
} \
\
const std::vector<contained_type> & nbt_##class_suffix##_array::value() const { \
	return payload; \
} \
\
std::vector<contained_type> & nbt_##class_suffix##_array::value() { \
	return payload; \
}
#endif
