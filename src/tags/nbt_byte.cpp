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


#include "nbt_byte.hpp"
#include <istream>
#include <ostream>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_byte::nbt_byte_id = 1;


nbt_byte::nbt_byte() : nbt_base(), payload(0) {}
nbt_byte::nbt_byte(char value) : nbt_base(), payload(value) {}
nbt_byte::nbt_byte(const nbt_byte & other) : nbt_base(other), payload(other.payload) {}
nbt_byte::nbt_byte(nbt_byte && other) : nbt_base(move(other)), payload(other.payload) {}

nbt_byte::~nbt_byte() {}

void nbt_byte::swap(nbt_base & with) {
	swap(dynamic_cast<nbt_byte &>(with));
}

void nbt_byte::swap(nbt_byte & with) {
	std::swap(payload, with.payload);
}

nbt_byte & nbt_byte::operator=(const nbt_byte & from) {
	nbt_byte temp(from);
	swap(temp);
	return *this;
}

bool nbt_byte::operator==(const nbt_base & to) {
	return operator==(dynamic_cast<const nbt_byte &>(to));
}

bool nbt_byte::operator==(const nbt_byte & to) {
	return nbt_base::operator==(to) && payload == to.payload;
}

void nbt_byte::read(istream & from) {
	payload = from.get();
}

void nbt_byte::write(ostream & to) const {
	to.put(payload);
}

unsigned char nbt_byte::id() const {
	return nbt_byte_id;
}

nbt_base * nbt_byte::clone() const {
	return new nbt_byte(*this);
}

const char & nbt_byte::value() const {
	return payload;
}

char & nbt_byte::value() {
	return payload;
}
