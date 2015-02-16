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


#include "nbt_registry.hpp"
#include "tags/nbt_end.hpp"
#include "tags/nbt_byte.hpp"


using namespace cpp_nbt;
using namespace std;


template<class T>
struct default_creator {
	constexpr nbt_base * operator()() const {
		return new T;
	}
};


unordered_map<unsigned char, function<nbt_base *()>> nbt_registry::id_to_pointer_map({
	{nbt_end::nbt_end_id, default_creator<nbt_end>()},
	{nbt_byte::nbt_byte_id, default_creator<nbt_byte>()}
});


void nbt_registry::register_id(unsigned char id, const function<nbt_base *()> & func) {
	id_to_pointer_map.emplace(id, func);
}

nbt_base * nbt_registry::create(unsigned char id) {
	const auto itr = id_to_pointer_map.find(id);
	if(itr == id_to_pointer_map.end())
		return nullptr;
	return itr->second();
}
