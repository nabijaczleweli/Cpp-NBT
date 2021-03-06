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


#include "cpp-nbt/tags/complex/nbt_list.hpp"
#include "cpp-nbt/nbt_registry.hpp"
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <istream>
#include <ostream>
#include <sstream>


using namespace std;
using namespace cpp_nbt;


const unsigned char nbt_list::nbt_tag_id = 9;


bool nbt_list::try_tag_type(const nbt_base & tag) {
	if(!tag_type)
		tag_type = tag.id();
	else if(tag_type != tag.id())
		return false;
	return true;
}

nbt_list::nbt_list(const vector<shared_ptr<nbt_base>> & thetags) : nbt_base(), tag_type(0) {
	transform(thetags.begin(), thetags.end(), back_inserter(tags), [&](const shared_ptr<nbt_base> & ptr) {
		return shared_ptr<nbt_base>(ptr ? ptr->clone() : nullptr);
	});
	tags.erase(remove_if(tags.begin(), tags.end(), logical_not<>()), tags.end());

	if(!tags.empty()) {
		if(adjacent_find(tags.begin(), tags.end(), [&](const shared_ptr<nbt_base> & lhs, const shared_ptr<nbt_base> & rhs) {
				return lhs->id() != rhs->id();
			}) != tags.end()) {
			vector<unsigned char> ids;
			transform(tags.begin(), tags.end(), back_inserter(ids), [&](const shared_ptr<nbt_base> & ptr) {
				return ptr->id();
			});
			sort(ids.begin(), ids.end());

			ostringstream strm;
			strm << "Multiple tag id()s: ";
			unique_copy(ids.begin(), ids.end(), ostream_iterator<unsigned int>(strm, ", "));

			string msg = strm.str();
			msg.replace(msg.size() - 2, 2, "!");
			throw invalid_argument(msg);
		} else
			tag_type = tags[0]->id();
	}
}

void nbt_list::swap(nbt_base & with) {
	swap(dynamic_cast<nbt_list &>(with));
}

void nbt_list::swap(nbt_list & with) {
	std::swap(tag_type, with.tag_type);
	tags.swap(with.tags);
}

nbt_list & nbt_list::operator=(nbt_list from) {
	swap(from);
	return *this;
}

bool nbt_list::operator==(const nbt_base & to) {
	return operator==(dynamic_cast<const nbt_list &>(to));
}

bool nbt_list::operator==(const nbt_list & to) {
	const bool temp = nbt_base::operator==(to);
	if(!temp || tags.size() != to.tags.size())
		return false;

	return equal(tags.begin(), tags.end(), to.tags.begin(), to.tags.end(), [&](const shared_ptr<nbt_base> & lhs, const shared_ptr<nbt_base> & rhs) {
		return (lhs == rhs) || ((lhs && rhs) && (*lhs == *rhs));
	});
}

void nbt_list::read(istream & from) {
	from.read(static_cast<char *>(static_cast<void *>(&tag_type)), 1);

	unsigned int length;
	from.read(static_cast<char *>(static_cast<void *>(&length)), sizeof(length));

	const auto creatorr = nbt_registry::creator(tag_type);
	if(creatorr) {
		const auto & creator(*creatorr);
		tags.resize(length, nullptr);
		for(auto & ptr : tags) {
			ptr = creator();
			ptr->read(from);
		}
	}
}

void nbt_list::write(ostream & to) const {
	to.write(static_cast<const char *>(static_cast<const void *>(&tag_type)), 1);

	const unsigned int length = tags.size();
	to.write(static_cast<const char *>(static_cast<const void *>(&length)), sizeof(length));

	for(auto ptr : tags)
		ptr->write(to);
}

unsigned char nbt_list::id() const {
	return nbt_tag_id;
}

unique_ptr<nbt_base> nbt_list::clone() const {
	return make_unique<nbt_list>(*this);
}

bool nbt_list::append_tag(const nbt_base & tag) {
	if(!try_tag_type(tag))
		return false;
	tags.emplace_back(tag.clone());
	return true;
}

bool nbt_list::set_tag(unsigned int idx, const nbt_base & tag) {
	if(idx >= tags.size() || !try_tag_type(tag))
		return false;

	tags[idx] = tag.clone();
	return true;
}

void nbt_list::remove_tag(unsigned int idx) {
	if(idx >= tags.size())
	   return;

	tags.erase(tags.cbegin() + idx);
}

size_t nbt_list::count() const {
	return tags.size();
}

shared_ptr<const nbt_base> nbt_list::get(unsigned int idx) const {
	return (idx < tags.size()) ? tags[idx] : shared_ptr<const nbt_base>();
}

shared_ptr<nbt_base> nbt_list::get(unsigned int idx) {
	return (idx < tags.size()) ? tags[idx] : shared_ptr<nbt_base>();
}
