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


#include "nbt_int.hpp"
#include <istream>
#include <ostream>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_int::nbt_int_id = 3;


nbt_int::nbt_int() : nbt_base(), payload(0) {}
nbt_int::nbt_int(int value) : nbt_base(), payload(value) {}
nbt_int::nbt_int(const nbt_int & other) : nbt_base(other), payload(other.payload) {}
nbt_int::nbt_int(nbt_int && other) : nbt_base(move(other)), payload(other.payload) {}

nbt_int::~nbt_int() {}

void nbt_int::swap(nbt_base & with) {
	swap(dynamic_cast<nbt_int &>(with));
}

void nbt_int::swap(nbt_int & with) {
	std::swap(payload, with.payload);
}

nbt_int & nbt_int::operator=(const nbt_int & from) {
	nbt_int temp(from);
	swap(temp);
	return *this;
}

void nbt_int::read(istream & from) {
	from.get(static_cast<char *>(static_cast<void *>(&payload)), sizeof(payload));
}

void nbt_int::write(ostream & to) const {
	to.write(static_cast<const char *>(static_cast<const void *>(&payload)), sizeof(payload));
}

unsigned char nbt_int::id() const {
	return nbt_int_id;
}

nbt_base * nbt_int::clone() const {
	return new nbt_int(*this);
}

const int & nbt_int::value() const {
	return payload;
}

int & nbt_int::value() {
	return payload;
}
