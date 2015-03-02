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


#include "nbt_manager.hpp"
#include "nbt_registry.hpp"
#include "tags/complex/nbt_compound.hpp"
#include <istream>


using namespace std;
using namespace cpp_nbt;


unsigned char nbt_manager::read_id(istream & from) {
	auto ret = from.get();
	return (ret == istream::traits_type::eof()) ? -1 : ret;
}

nbt_base * nbt_manager::read_tag(istream & from) {
	nbt_base * temp = nbt_registry::create(read_id(from));
	if(temp)
		temp->read(from);
	return temp;
}

bool nbt_manager::read_readable(istream & from, nbt_readable & toread) {
	nbt_base * tag = read_tag(from);
	nbt_compound * compound = dynamic_cast<nbt_compound *>(tag);
	if(!compound) {
		delete tag;
		tag = nullptr;
		return false;
	}
	toread.read_from_nbt(*compound);
	return true;
}

void nbt_manager::write_id(ostream & to, unsigned char id) {
	to.put(id);
}

void nbt_manager::write_tag(ostream & to, const nbt_base & tag) {
	write_id(to, tag.id());
	tag.write(to);
}

void nbt_manager::write_writeable(ostream & to, const nbt_writeable & towrite) {
	nbt_compound tag;
	towrite.write_to_nbt(tag);
	write_tag(to, tag);
}
