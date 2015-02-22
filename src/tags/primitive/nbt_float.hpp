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
#ifndef NBT_FLOAT_HPP
#define NBT_FLOAT_HPP


#include "../nbt_base.hpp"


namespace cpp_nbt {
	class nbt_float : public nbt_base {
		private:
			float payload;

		public:
			static const unsigned char nbt_float_id;

			nbt_float();
			nbt_float(float value);
			nbt_float(const nbt_float & other);
			nbt_float(nbt_float && other);

			virtual ~nbt_float();

			virtual void swap(nbt_base & with) override;
			virtual void swap(nbt_float & with);

			nbt_float & operator=(const nbt_float & from);
			virtual bool operator==(const nbt_base & to) override;
			virtual bool operator==(const nbt_float & to);

			virtual void read(std::istream & from) override;
			virtual void write(std::ostream & to) const override;

			virtual unsigned char id() const override;

			virtual nbt_base * clone() const override;

			const float & value() const;
			float & value();
	};
}


#endif  // NBT_FLOAT_HPP
