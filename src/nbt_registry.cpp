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


#include "cpp-nbt/nbt_registry.hpp"
#include "cpp-nbt/tags/nbt_end.hpp"
#include "cpp-nbt/tags/nbt_array.hpp"
#include "cpp-nbt/tags/nbt_string.hpp"
#include "cpp-nbt/tags/nbt_primitive.hpp"
#include "cpp-nbt/tags/complex/nbt_list.hpp"
#include "cpp-nbt/tags/complex/nbt_compound.hpp"
#include <memory>


using namespace std;
using namespace std::experimental;
using namespace cpp_nbt;


typedef nbt_registry::creator_t creator_t;


template<class T>
struct default_creator {
	unique_ptr<nbt_base> operator()() const {
		return make_unique<T>();
	}
};


unordered_map<unsigned char, creator_t> nbt_registry::id_to_pointer_map({
	{nbt_end::nbt_tag_id, default_creator<nbt_end>()},
	{nbt_byte::nbt_tag_id, default_creator<nbt_byte>()},
	{nbt_short::nbt_tag_id, default_creator<nbt_short>()},
	{nbt_int::nbt_tag_id, default_creator<nbt_int>()},
	{nbt_long::nbt_tag_id, default_creator<nbt_long>()},
	{nbt_float::nbt_tag_id, default_creator<nbt_float>()},
	{nbt_double::nbt_tag_id, default_creator<nbt_double>()},
	{nbt_byte_array::nbt_tag_id, default_creator<nbt_byte_array>()},
	{nbt_string::nbt_tag_id, default_creator<nbt_string>()},
	{nbt_list::nbt_tag_id, default_creator<nbt_list>()},
	{nbt_compound::nbt_tag_id, default_creator<nbt_compound>()},
	{nbt_int_array::nbt_tag_id, default_creator<nbt_int_array>()}
});


void nbt_registry::register_id(unsigned char id, const creator_t & func) {
	id_to_pointer_map.emplace(id, func);
}

unique_ptr<nbt_base> nbt_registry::create(unsigned char id) {
	const auto temp(creator(id));
	return temp ? (*temp)() : unique_ptr<nbt_base>();
}

optional<creator_t> nbt_registry::creator(unsigned char id) {
	const auto itr = id_to_pointer_map.find(id);
	return (itr == id_to_pointer_map.end()) ? optional<creator_t>() : optional<creator_t>(itr->second);
}
