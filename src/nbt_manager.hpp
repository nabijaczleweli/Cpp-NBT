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
#ifndef NBT_MANAGER_HPP
#define NBT_MANAGER_HPP


#include "tags/nbt_base.hpp"
#include "nbt_readable.hpp"
#include "nbt_writeable.hpp"
#include <iosfwd>
#include <memory>


namespace cpp_nbt {
	class nbt_manager {
		private:
			nbt_manager() = delete;  // Don't instantiate

		public:
			static unsigned char read_id(std::istream & from);
			static std::unique_ptr<nbt_base> read_tag(std::istream & from);
			static bool read_readable(std::istream & from, nbt_readable & toread);

			static void write_id(std::ostream & to, unsigned char id);
			static void write_tag(std::ostream & to, const nbt_base & tag);
			static void write_writeable(std::ostream & to, const nbt_writeable & towrite);
	};
}


#endif  // NBT_MANAGER_HPP
