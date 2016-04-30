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
#ifndef NBT_LIST_HPP
#define NBT_LIST_HPP


#include "../nbt_base.hpp"
#include <memory>
#include <vector>


namespace cpp_nbt {
	class nbt_list : public nbt_base {
		private:
			unsigned char tag_type;
			std::vector<std::shared_ptr<nbt_base>> tags;

			bool try_tag_type(const nbt_base & tag);

		public:
			static const unsigned char nbt_list_id;

			nbt_list();
			explicit nbt_list(const std::vector<std::shared_ptr<nbt_base>> & thetags);
			nbt_list(const nbt_list & other);
			nbt_list(nbt_list && other);

			virtual ~nbt_list();

			virtual void swap(nbt_base & with) override;
			virtual void swap(nbt_list & with);

			nbt_list & operator=(const nbt_list & from);
			virtual bool operator==(const nbt_base & to) override;
			virtual bool operator==(const nbt_list & to);

			virtual void read(std::istream & from) override;
			virtual void write(std::ostream & to) const override;

			virtual unsigned char id() const override;

			virtual std::unique_ptr<nbt_base> clone() const override;

			bool append_tag(const nbt_base & tag);
			bool set_tag(unsigned int idx, const nbt_base & tag);
			void remove_tag(unsigned int idx);
			size_t count() const;
			std::shared_ptr<const nbt_base> get(unsigned int idx) const;
			std::shared_ptr<nbt_base> get(unsigned int idx);
	};
}


#endif  // NBT_LIST_HPP
