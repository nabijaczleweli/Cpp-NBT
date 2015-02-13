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


#include "nbt_base.hpp"
#include <istream>
#include <ostream>


using namespace cpp_nbt;
using namespace std;


nbt_base::nbt_base() {}
nbt_base::nbt_base(unsigned char theid) : id(theid) {}
nbt_base::nbt_base(const nbt_base & other) : id(other.id) {}
nbt_base::nbt_base(nbt_base && other) : id(other.id) {}

nbt_base::~nbt_base() {}

nbt_base & nbt_base::operator=(const nbt_base & from) {
	nbt_base * temp = from.clone();
	swap(*temp);
	delete temp; temp = nullptr;
	return *this;
}

bool nbt_base::operator==(const nbt_base & to) {
	return id == to.id;
}

void nbt_base::swap(nbt_base & other) {
	std::swap(id, other.id);
}

void nbt_base::read(istream & from) {
	id = from.get();
}

void nbt_base::write(ostream & to) const {
	to.put(id);
}


namespace std {
	void swap(nbt_base & lhs, nbt_base & rhs) {
		lhs.swap(rhs);
	}
}
