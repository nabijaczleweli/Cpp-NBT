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


#include "nbt_end.hpp"
#include <functional>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_end::nbt_end_id = 0;


nbt_end::nbt_end() : nbt_base() {}
nbt_end::nbt_end(const nbt_end & other) : nbt_base(other) {}
nbt_end::nbt_end(nbt_end && other) : nbt_base(move(other)) {}

nbt_end::~nbt_end() {}

void nbt_end::swap(nbt_base &) {}

void nbt_end::read(std::istream &) {}
void nbt_end::write(std::ostream &) const {}

unsigned char nbt_end::id() const {
	return nbt_end_id;
}

unique_ptr<nbt_base> nbt_end::clone() const {
	return make_unique<nbt_end>(*this);
}
