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
#include "tags/nbt_short.hpp"
#include "tags/nbt_int.hpp"
#include "tags/nbt_long.hpp"
#include "tags/nbt_float.hpp"
#include "tags/nbt_double.hpp"


using namespace cpp_nbt;
using namespace std;


typedef nbt_registry::creator_t creator_t;


template<class T>
struct default_creator {
	constexpr nbt_base * operator()() const {
		return new T;
	}
};


unordered_map<unsigned char, creator_t> nbt_registry::id_to_pointer_map({
	{nbt_end::nbt_end_id, default_creator<nbt_end>()},
	{nbt_byte::nbt_byte_id, default_creator<nbt_byte>()},
	{nbt_short::nbt_short_id, default_creator<nbt_short>()},
	{nbt_int::nbt_int_id, default_creator<nbt_int>()},
	{nbt_long::nbt_long_id, default_creator<nbt_long>()},
	{nbt_float::nbt_float_id, default_creator<nbt_float>()},
	{nbt_double::nbt_double_id, default_creator<nbt_double>()}
});


void nbt_registry::register_id(unsigned char id, const creator_t & func) {
	id_to_pointer_map.emplace(id, func);
}

nbt_base * nbt_registry::create(unsigned char id) {
	return creator(id)();
}

const creator_t & nbt_registry::creator(unsigned char id) {
	static const creator_t placeholder_creator([&]() {
		return nullptr;
	});

	const auto itr = id_to_pointer_map.find(id);
	if(itr == id_to_pointer_map.end())
		return placeholder_creator;
	return itr->second;
}
