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


using namespace cpp_nbt;
using namespace std;


class copying_creator {
	private:
		const nbt_base * base;

	public:
		copying_creator(const nbt_base & from) : base(from.clone()) {}
		copying_creator(const copying_creator & other) : base(other.base->clone()) {}
		copying_creator(copying_creator && other) : base(other.base) {
			other.base = nullptr;
		}

		~copying_creator() {
			if(base) {
				delete base;
				base = nullptr;
			}
		}

		nbt_base * operator()() {
			return base->clone();
		}
};


unordered_map<unsigned char, function<nbt_base *()>> nbt_registry::id_to_pointer_map;


void nbt_registry::register_id(unsigned char id, const function<nbt_base *()> & func) {
	id_to_pointer_map.emplace(id, func);
}

void nbt_registry::register_id(const nbt_base & from) {
	id_to_pointer_map.emplace(from.id(), copying_creator(from));
}

nbt_base * nbt_registry::create(unsigned char id) {
	const auto itr = id_to_pointer_map.find(id);
	if(itr == id_to_pointer_map.end())
		return nullptr;
	return itr->second();
}
