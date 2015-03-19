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
#ifndef NBT_BASE_HPP
#define NBT_BASE_HPP


#include <iosfwd>
#include <memory>


namespace cpp_nbt {
	class nbt_base {
		public:
			nbt_base();
			nbt_base(const nbt_base & other);
			nbt_base(nbt_base && other);

			virtual ~nbt_base();

			virtual void swap(nbt_base & with) = 0;

			nbt_base & operator=(const nbt_base & from);
			virtual bool operator==(const nbt_base & to);

			virtual void read(std::istream & from) = 0;
			virtual void write(std::ostream & to) const = 0;

			virtual unsigned char id() const = 0;

			virtual std::unique_ptr<nbt_base> clone() const = 0;
	};
}


namespace std {
	void swap(cpp_nbt::nbt_base & lhs, cpp_nbt::nbt_base & rhs);
}


#endif  // NBT_BASE_HPP
