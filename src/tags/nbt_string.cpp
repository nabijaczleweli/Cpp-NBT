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


#include "cpp-nbt/tags/nbt_string.hpp"
#include <istream>
#include <ostream>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_string::nbt_tag_id = 8;


nbt_string::nbt_string() : nbt_base() {}
nbt_string::nbt_string(const string & str) : nbt_base(), payload(str) {}
nbt_string::nbt_string(const nbt_string & other) : nbt_base(other), payload(other.payload) {}
nbt_string::nbt_string(nbt_string && other) : nbt_base(move(other)), payload(move(other.payload)) {}

nbt_string::~nbt_string() {}

void nbt_string::swap(nbt_base & with) {
	swap(dynamic_cast<nbt_string &>(with));
}

void nbt_string::swap(nbt_string & with) {
	payload.swap(with.payload);
}

nbt_string & nbt_string::operator=(nbt_string from) {
	swap(from);
	return *this;
}

bool nbt_string::operator==(const nbt_base & to) {
	return operator==(dynamic_cast<const nbt_string &>(to));
}

bool nbt_string::operator==(const nbt_string & to) {
	return nbt_base::operator==(to) && payload == to.payload;
}

void nbt_string::read(istream & from) {
	short int length;
	from.read(static_cast<char *>(static_cast<void *>(&length)), sizeof(length));

	payload.resize(length);
	from.read(&payload[0], length);
}

void nbt_string::write(ostream & to) const {
	const short int length = payload.size();
	to.write(static_cast<const char *>(static_cast<const void *>(&length)), sizeof(length));

	to.write(payload.c_str(), length);
}

unique_ptr<nbt_base> nbt_string::clone() const {
	return make_unique<nbt_string>(*this);
}

unsigned char nbt_string::id() const {
	return nbt_tag_id;
}

const string & nbt_string::value() const {
	return payload;
}

string & nbt_string::value() {
	return payload;
}
