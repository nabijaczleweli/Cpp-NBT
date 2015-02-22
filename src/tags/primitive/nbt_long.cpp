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


#include "nbt_long.hpp"
#include <istream>
#include <ostream>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_long::nbt_long_id = 4;


nbt_long::nbt_long() : nbt_base(), payload(0) {}
nbt_long::nbt_long(long int value) : nbt_base(), payload(value) {}
nbt_long::nbt_long(const nbt_long & other) : nbt_base(other), payload(other.payload) {}
nbt_long::nbt_long(nbt_long && other) : nbt_base(move(other)), payload(other.payload) {}

nbt_long::~nbt_long() {}

void nbt_long::swap(nbt_base & with) {
	swap(dynamic_cast<nbt_long &>(with));
}

void nbt_long::swap(nbt_long & with) {
	std::swap(payload, with.payload);
}

nbt_long & nbt_long::operator=(const nbt_long & from) {
	nbt_long temp(from);
	swap(temp);
	return *this;
}

bool nbt_long::operator==(const nbt_base & to) {
	return operator==(dynamic_cast<const nbt_long &>(to));
}

bool nbt_long::operator==(const nbt_long & to) {
	return nbt_base::operator==(to) && payload == to.payload;
}

void nbt_long::read(istream & from) {
	from.get(static_cast<char *>(static_cast<void *>(&payload)), sizeof(payload));
}

void nbt_long::write(ostream & to) const {
	to.write(static_cast<const char *>(static_cast<const void *>(&payload)), sizeof(payload));
}

unsigned char nbt_long::id() const {
	return nbt_long_id;
}

nbt_base * nbt_long::clone() const {
	return new nbt_long(*this);
}

const long int & nbt_long::value() const {
	return payload;
}

long int & nbt_long::value() {
	return payload;
}
