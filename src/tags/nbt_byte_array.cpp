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


#include "nbt_byte_array.hpp"
#include <functional>
#include <istream>
#include <ostream>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_byte_array::nbt_byte_array_id = 7;


nbt_byte_array::nbt_byte_array() : nbt_base() {}
nbt_byte_array::nbt_byte_array(const vector<char> value) : nbt_base(), payload(value) {}
nbt_byte_array::nbt_byte_array(const nbt_byte_array & other) : nbt_base(other), payload(other.payload) {}
nbt_byte_array::nbt_byte_array(nbt_byte_array && other) : nbt_base(move(other)), payload(move(other.payload)) {}

nbt_byte_array::~nbt_byte_array() {}

void nbt_byte_array::swap(nbt_base & with) {
	swap(dynamic_cast<nbt_byte_array &>(with));
}

void nbt_byte_array::swap(nbt_byte_array & with) {
	payload.swap(with.payload);
}

nbt_byte_array & nbt_byte_array::operator=(const nbt_byte_array & from) {
	nbt_byte_array temp(from);
	swap(temp);
	return *this;
}

bool nbt_byte_array::operator==(const nbt_base & to) {
	return operator==(dynamic_cast<const nbt_byte_array &>(to));
}

bool nbt_byte_array::operator==(const nbt_byte_array & to) {
	return nbt_base::operator==(to) && payload == to.payload;
}

void nbt_byte_array::read(istream & from) {
	int * length = new int;
	from.read(static_cast<char *>(static_cast<void *>(length)), sizeof(*length));

	payload.resize(*length);
	from.read(payload.data(), *length);

	delete length; length = nullptr;
}

void nbt_byte_array::write(ostream & to) const {
	int * length = new int(payload.size());
	to.write(static_cast<char *>(static_cast<void *>(length)), sizeof(*length));

	to.write(payload.data(), payload.size());

	delete length; length = nullptr;
}

unsigned char nbt_byte_array::id() const {
	return nbt_byte_array_id;
}

nbt_base * nbt_byte_array::clone() const {
	return new nbt_byte_array(*this);
}

const vector<char> & nbt_byte_array::value() const {
	return payload;
}

vector<char> & nbt_byte_array::value() {
	return payload;
}
