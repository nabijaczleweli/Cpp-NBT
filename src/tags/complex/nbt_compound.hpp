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


#pragma once
#ifndef NBT_COMPOUND_HPP
#define NBT_COMPOUND_HPP


#include "../nbt_base.hpp"
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>


namespace cpp_nbt {
	class nbt_compound : public nbt_base {
		private:
			std::unordered_map<std::string, std::shared_ptr<nbt_base>> tags;

		public:
			static const unsigned char nbt_compound_id;

			nbt_compound();
			explicit nbt_compound(const std::unordered_map<std::string, std::shared_ptr<nbt_base>> & thetags);
			nbt_compound(const nbt_compound & other);
			nbt_compound(nbt_compound && other);

			virtual ~nbt_compound();

			virtual void swap(nbt_base & with) override;
			virtual void swap(nbt_compound & with);

			nbt_compound & operator=(const nbt_compound & from);
			virtual bool operator==(const nbt_base & to) override;
			virtual bool operator==(const nbt_compound & to);

			virtual void read(std::istream & from) override;
			virtual void write(std::ostream & to) const override;

			virtual unsigned char id() const override;

			virtual nbt_base * clone() const override;

			void set_tag(const std::string & key, const nbt_base & tag);
			void remove_tag(const std::string & key);
			std::shared_ptr<const nbt_base> get_tag(const std::string & key) const;
			std::shared_ptr<nbt_base> get_tag(const std::string & key);
			bool has_key(const std::string & key) const;
			bool empty() const;

#define SET_TAG_SIMPLE(name, type) void set_##name(const std::string & key, const type & val);
			SET_TAG_SIMPLE(byte, char)
			SET_TAG_SIMPLE(short, short)
			SET_TAG_SIMPLE(integer, int)
			SET_TAG_SIMPLE(long, long)
			SET_TAG_SIMPLE(float, float)
			SET_TAG_SIMPLE(double, double)
			SET_TAG_SIMPLE(string, std::string)
			SET_TAG_SIMPLE(byte_array, std::vector<char>)
			SET_TAG_SIMPLE(int_array, std::vector<int>)
			SET_TAG_SIMPLE(boolean, bool)
#undef SET_TAG_SIMPLE
#define GET_TAG_SIMPLE(name, type) \
	const type * get_##name(const std::string & key) const; \
	type * get_##name(const std::string & key);
			GET_TAG_SIMPLE(byte, char)
			GET_TAG_SIMPLE(short, short)
			GET_TAG_SIMPLE(integer, int)
			GET_TAG_SIMPLE(long, long)
			GET_TAG_SIMPLE(float, float)
			GET_TAG_SIMPLE(double, double)
			GET_TAG_SIMPLE(string, std::string)
			GET_TAG_SIMPLE(byte_array, std::vector<char>)
			GET_TAG_SIMPLE(int_array, std::vector<int>)
			GET_TAG_SIMPLE(boolean, bool)
#undef GET_TAG_SIMPLE
	};
}


#endif  // NBT_COMPOUND_HPP
