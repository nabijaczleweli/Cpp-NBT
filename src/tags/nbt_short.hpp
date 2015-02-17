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
#ifndef NBT_SHORT_HPP
#define NBT_SHORT_HPP


#include "nbt_base.hpp"


namespace cpp_nbt {
	class nbt_short : public nbt_base {
		private:
			short int payload;

		public:
			static const unsigned char nbt_short_id;

			nbt_short();
			nbt_short(short int value);
			nbt_short(const nbt_short & other);
			nbt_short(nbt_short && other);

			virtual ~nbt_short();

			virtual void swap(nbt_base & with);
			virtual void swap(nbt_short & with);
			nbt_short & operator=(const nbt_short & from);

			virtual void read(std::istream & from);
			virtual void write(std::ostream & to) const;

			virtual unsigned char id() const;

			virtual nbt_base * clone() const;

			const short int & value() const;
			short int & value();
	};
}


#endif  // NBT_SHORT_HPP
