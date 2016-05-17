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
#ifndef NBT_STRING_HPP
#define NBT_STRING_HPP


#include "nbt_base.hpp"
#include <string>
#include <memory>


namespace cpp_nbt {
	class nbt_string : public nbt_base {
		private:
			std::string payload;

		public:
			static const unsigned char nbt_tag_id;

			nbt_string();
			explicit nbt_string(const std::string & str);
			nbt_string(const nbt_string & other);
			nbt_string(nbt_string && other);

			virtual ~nbt_string();

			virtual void swap(nbt_base & with) override;
			virtual void swap(nbt_string & with);

			nbt_string & operator=(const nbt_string & from);
			virtual bool operator==(const nbt_base & to) override;
			virtual bool operator==(const nbt_string & to);

			virtual void read(std::istream & from) override;
			virtual void write(std::ostream & to) const override;

			virtual unsigned char id() const override;

			virtual std::unique_ptr<nbt_base> clone() const override;

			const std::string & value() const;
			std::string & value();
	};
}


#endif  // NBT_STRING_HPP
