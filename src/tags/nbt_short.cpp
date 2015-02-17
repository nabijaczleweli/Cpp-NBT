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


#include "nbt_short.hpp"
#include <istream>
#include <ostream>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_short::nbt_short_id = 2;


nbt_short::nbt_short() : nbt_base(), payload(0) {}
nbt_short::nbt_short(short int value) : nbt_base(), payload(value) {}
nbt_short::nbt_short(const nbt_short & other) : nbt_base(other), payload(other.payload) {}
nbt_short::nbt_short(nbt_short && other) : nbt_base(move(other)), payload(other.payload) {}

nbt_short::~nbt_short() {}

void nbt_short::swap(nbt_base & with) {
	swap(dynamic_cast<nbt_short &>(with));
}

void nbt_short::swap(nbt_short & with) {
	std::swap(payload, with.payload);
}

nbt_short & nbt_short::operator=(const nbt_short & from) {
	nbt_short temp(from);
	swap(temp);
	return *this;
}

void nbt_short::read(istream & from) {
	from.get(static_cast<char *>(static_cast<void *>(&payload)), sizeof(payload));
}

void nbt_short::write(ostream & to) const {
	to.write(static_cast<const char *>(static_cast<const void *>(&payload)), sizeof(payload));
}

unsigned char nbt_short::id() const {
	return nbt_short_id;
}

nbt_base * nbt_short::clone() const {
	return new nbt_short(*this);
}

const short int & nbt_short::value() const {
	return payload;
}

short int & nbt_short::value() {
	return payload;
}
