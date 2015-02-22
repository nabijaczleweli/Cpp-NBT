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


#include "nbt_double.hpp"
#include <istream>
#include <ostream>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_double::nbt_double_id = 6;


nbt_double::nbt_double() : nbt_base(), payload(0) {}
nbt_double::nbt_double(double value) : nbt_base(), payload(value) {}
nbt_double::nbt_double(const nbt_double & other) : nbt_base(other), payload(other.payload) {}
nbt_double::nbt_double(nbt_double && other) : nbt_base(move(other)), payload(other.payload) {}

nbt_double::~nbt_double() {}

void nbt_double::swap(nbt_base & with) {
	swap(dynamic_cast<nbt_double &>(with));
}

void nbt_double::swap(nbt_double & with) {
	std::swap(payload, with.payload);
}

nbt_double & nbt_double::operator=(const nbt_double & from) {
	nbt_double temp(from);
	swap(temp);
	return *this;
}

bool nbt_double::operator==(const nbt_base & to) {
	return operator==(dynamic_cast<const nbt_double &>(to));
}

bool nbt_double::operator==(const nbt_double & to) {
	return nbt_base::operator==(to) && payload == to.payload;
}

void nbt_double::read(istream & from) {
	from.get(static_cast<char *>(static_cast<void *>(&payload)), sizeof(payload));
}

void nbt_double::write(ostream & to) const {
	to.write(static_cast<const char *>(static_cast<const void *>(&payload)), sizeof(payload));
}

unsigned char nbt_double::id() const {
	return nbt_double_id;
}

nbt_base * nbt_double::clone() const {
	return new nbt_double(*this);
}

const double & nbt_double::value() const {
	return payload;
}

double & nbt_double::value() {
	return payload;
}
