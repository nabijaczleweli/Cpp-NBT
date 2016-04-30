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


#include "nbt_compound.hpp"
#include "../../nbt_registry.hpp"
#include "../../nbt_manager.hpp"
#include "../nbt_end.hpp"
#include "../primitive/nbt_byte.hpp"
#include "../primitive/nbt_short.hpp"
#include "../primitive/nbt_int.hpp"
#include "../primitive/nbt_long.hpp"
#include "../primitive/nbt_float.hpp"
#include "../primitive/nbt_double.hpp"
#include "../array/nbt_byte_array.hpp"
#include "../array/nbt_int_array.hpp"
#include "../nbt_string.hpp"
#include "nbt_list.hpp"
#include <algorithm>
#include <istream>
#include <ostream>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_compound::nbt_compound_id = 10;


nbt_compound::nbt_compound() : nbt_base() {}
nbt_compound::nbt_compound(const unordered_map<string, shared_ptr<nbt_base>> & thetags) : nbt_base() {
	transform(thetags.begin(), thetags.end(), inserter(tags, tags.begin()), [&](const pair<string, shared_ptr<nbt_base>> & pr) {
		return make_pair(pr.first, shared_ptr<nbt_base>(pr.second ? pr.second->clone() : nullptr));
	});
}
nbt_compound::nbt_compound(const nbt_compound & other) : nbt_compound(other.tags) {}
nbt_compound::nbt_compound(nbt_compound && other) : nbt_base(move(other)), tags(move(other.tags)) {}

nbt_compound::~nbt_compound() {}

void nbt_compound::swap(nbt_base & with) {
	swap(dynamic_cast<nbt_compound &>(with));
}

void nbt_compound::swap(nbt_compound & with) {
	tags.swap(with.tags);
}

nbt_compound & nbt_compound::operator=(const nbt_compound & from) {
	nbt_compound temp(from);
	swap(temp);
	return *this;
}

bool nbt_compound::operator==(const nbt_base & to) {
	return operator==(dynamic_cast<const nbt_compound &>(to));
}

bool nbt_compound::operator==(const nbt_compound & to) {
	typedef decltype(tags)::value_type value_type;

	const bool temp = nbt_base::operator==(to);
	if(!temp || tags.size() != to.tags.size())
		return false;

	return is_permutation(tags.begin(), tags.end(), to.tags.begin(), to.tags.end(), [&](const value_type & lhs, const value_type & rhs) {
		return lhs.first == rhs.first && ((lhs.second == rhs.second) || ((lhs.second && rhs.second) && (*lhs.second == *rhs.second)));
	});
}

void nbt_compound::read(istream & from) {
	nbt_string name;
	unsigned char id;
	while((id = nbt_manager::read_id(from)) != nbt_end::nbt_end_id) {  // Read id
		name.read(from);  // Read name
		unique_ptr<nbt_base> tag = nbt_registry::create(id);
		if(!tag)
			return;  // PANIC MODE!!!
		tag->read(from);  // Read the tag itself
		tags.emplace(name.value(), shared_ptr<nbt_base>(move(tag)));
	}

	// Ends with an nbt_end
	name.read(from);
	nbt_end().read(from);
}

void nbt_compound::write(ostream & to) const {
	nbt_string name;
	for(const auto & pr : tags)
		if(pr.second) {
			nbt_manager::write_id(to, pr.second->id());  // Write id
			name.value() = pr.first;
			name.write(to);  // Write name
			pr.second->write(to);  // Write tag itself
		}

	// End with an nbt_end
	nbt_manager::write_id(to, nbt_end::nbt_end_id);
	name.value().clear();
	name.write(to);
	nbt_end().write(to);
}

unsigned char nbt_compound::id() const {
	return nbt_compound_id;
}

unique_ptr<nbt_base> nbt_compound::clone() const {
	return make_unique<nbt_compound>(*this);
}

void nbt_compound::set_tag(const string & key, const nbt_base & tag) {
	tags[key] = tag.clone();
}

void nbt_compound::remove_tag(const string & key) {
	tags.erase(key);
}

shared_ptr<const nbt_base> nbt_compound::get_tag(const string & key) const {
	const auto itr = tags.find(key);
	return (itr == tags.end()) ? shared_ptr<const nbt_base>() : itr->second;
}

shared_ptr<nbt_base> nbt_compound::get_tag(const string & key) {
	const auto itr = tags.find(key);
	return (itr == tags.end()) ? shared_ptr<nbt_base>() : itr->second;
}

bool nbt_compound::has_key(const string & key) const {
	return tags.find(key) != tags.end();
}

bool nbt_compound::empty() const {
	return tags.empty();
}

// Keep last

#define SET_TAG_IMPL_SIMPLE(name, type, class) void nbt_compound::set_##name(const string & key, const type & val) { \
		set_tag(key, class(val)); \
	}

SET_TAG_IMPL_SIMPLE(byte, char, nbt_byte)
SET_TAG_IMPL_SIMPLE(short, short, nbt_short)
SET_TAG_IMPL_SIMPLE(integer, int, nbt_int)
SET_TAG_IMPL_SIMPLE(long, long, nbt_long)
SET_TAG_IMPL_SIMPLE(float, float, nbt_float)
SET_TAG_IMPL_SIMPLE(double, double, nbt_double)
SET_TAG_IMPL_SIMPLE(string, string, nbt_string)
SET_TAG_IMPL_SIMPLE(byte_array, vector<char>, nbt_byte_array)
SET_TAG_IMPL_SIMPLE(int_array, vector<int>, nbt_int_array)
SET_TAG_IMPL_SIMPLE(boolean, bool, nbt_byte)

#undef SET_TAG_IMPL_SIMPLE
#define GET_TAG_IMPL_SIMPLE(name, type, clas) \
	const type * nbt_compound::get_##name(const string & key) const { \
		const auto tagptr = get_tag(key); \
		return tagptr ? &dynamic_cast<const clas &>(*tagptr).value() : nullptr; \
	} \
	type * nbt_compound::get_##name(const string & key) { \
		const auto tagptr = get_tag(key); \
		return tagptr ? &dynamic_cast<clas &>(*tagptr).value() : nullptr; \
	}

GET_TAG_IMPL_SIMPLE(byte, char, nbt_byte)
GET_TAG_IMPL_SIMPLE(short, short, nbt_short)
GET_TAG_IMPL_SIMPLE(integer, int, nbt_int)
GET_TAG_IMPL_SIMPLE(long, long, nbt_long)
GET_TAG_IMPL_SIMPLE(float, float, nbt_float)
GET_TAG_IMPL_SIMPLE(double, double, nbt_double)
GET_TAG_IMPL_SIMPLE(string, string, nbt_string)
GET_TAG_IMPL_SIMPLE(byte_array, vector<char>, nbt_byte_array)
GET_TAG_IMPL_SIMPLE(int_array, vector<int>, nbt_int_array)

#undef GET_TAG_IMPL_SIMPLE

const bool * nbt_compound::get_boolean(const string & key) const {
	const auto tagptr = get_tag(key);
	return tagptr ? static_cast<const bool *>(static_cast<const void *>(&dynamic_cast<const nbt_byte &>(*tagptr).value())) : nullptr;
}

bool * nbt_compound::get_boolean(const string & key) {
	const auto tagptr = get_tag(key);
	return tagptr ? static_cast<bool *>(static_cast<void *>(&dynamic_cast<nbt_byte &>(*tagptr).value())) : nullptr;
}
