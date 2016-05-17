// The MIT License (MIT)

// Copyright (c) 2016 nabijaczleweli

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
#ifndef NBT_PRIMITIVE_HPP
#define NBT_PRIMITIVE_HPP


#include "nbt_base.hpp"
#include <memory>
#include <istream>
#include <ostream>


namespace cpp_nbt {
	template<class ContainedType, unsigned char NbtId>
	class nbt_number : public nbt_base {
		private:
			ContainedType payload;

		public:
			static const unsigned char nbt_tag_id;


			nbt_number();
			nbt_number(ContainedType value);
			nbt_number(const nbt_number & other);
			nbt_number(nbt_number && other);

			virtual ~nbt_number() = default;

			virtual void swap(nbt_base & with) override;
			virtual void swap(nbt_number & with);

			nbt_number & operator=(nbt_number from);
			virtual bool operator==(const nbt_base & to) override;
			virtual bool operator==(const nbt_number & to);

			virtual void read(std::istream & from) override;
			virtual void write(std::ostream & to) const override;

			virtual unsigned char id() const override;

			virtual std::unique_ptr<nbt_base> clone() const override;

			const ContainedType & value() const;
			ContainedType & value();
	};

	using nbt_byte = nbt_number<char, 1>;
	using nbt_short = nbt_number<short int, 2>;
	using nbt_int = nbt_number<int, 3>;
	using nbt_long = nbt_number<long int, 4>;
	using nbt_float = nbt_number<float, 5>;
	using nbt_double = nbt_number<double, 6>;
}


template<class ContainedType, unsigned char NbtId>
const unsigned char cpp_nbt::nbt_number<ContainedType, NbtId>::nbt_tag_id = NbtId;

template<class ContainedType, unsigned char NbtId>
cpp_nbt::nbt_number<ContainedType, NbtId>::nbt_number() : cpp_nbt::nbt_base(), payload(0) {}

template<class ContainedType, unsigned char NbtId>
cpp_nbt::nbt_number<ContainedType, NbtId>::nbt_number(ContainedType value) : cpp_nbt::nbt_base(), payload(value) {}

template<class ContainedType, unsigned char NbtId>
cpp_nbt::nbt_number<ContainedType, NbtId>::nbt_number(const cpp_nbt::nbt_number<ContainedType, NbtId> & other) : cpp_nbt::nbt_base(other), payload(other.payload) {}

template<class ContainedType, unsigned char NbtId>
cpp_nbt::nbt_number<ContainedType, NbtId>::nbt_number(cpp_nbt::nbt_number<ContainedType, NbtId> && other) : cpp_nbt::nbt_base(std::move(other)), payload(other.payload) {}

template<class ContainedType, unsigned char NbtId>
void cpp_nbt::nbt_number<ContainedType, NbtId>::swap(cpp_nbt::nbt_base & with) {
	swap(dynamic_cast<cpp_nbt::nbt_number<ContainedType, NbtId> &>(with));
}

template<class ContainedType, unsigned char NbtId>
void cpp_nbt::nbt_number<ContainedType, NbtId>::swap(cpp_nbt::nbt_number<ContainedType, NbtId> & with) {
	std::swap(payload, with.payload);
}

template<class ContainedType, unsigned char NbtId>
cpp_nbt::nbt_number<ContainedType, NbtId> & cpp_nbt::nbt_number<ContainedType, NbtId>::operator=(cpp_nbt::nbt_number<ContainedType, NbtId> from) {
	swap(from);
	return *this;
}

template<class ContainedType, unsigned char NbtId>
bool cpp_nbt::nbt_number<ContainedType, NbtId>::operator==(const cpp_nbt::nbt_base & to) {
	return operator==(dynamic_cast<const cpp_nbt::nbt_number<ContainedType, NbtId> &>(to));
}

template<class ContainedType, unsigned char NbtId>
bool cpp_nbt::nbt_number<ContainedType, NbtId>::operator==(const cpp_nbt::nbt_number<ContainedType, NbtId> & to) {
	return cpp_nbt::nbt_base::operator==(to) && payload == to.payload;
}

template<class ContainedType, unsigned char NbtId>
void cpp_nbt::nbt_number<ContainedType, NbtId>::read(std::istream & from) {
	from.get(static_cast<char *>(static_cast<void *>(&payload)), sizeof(payload));
}

template<class ContainedType, unsigned char NbtId>
void cpp_nbt::nbt_number<ContainedType, NbtId>::write(std::ostream & to) const {
	to.write(static_cast<const char *>(static_cast<const void *>(&payload)), sizeof(payload));
}

template<class ContainedType, unsigned char NbtId>
unsigned char cpp_nbt::nbt_number<ContainedType, NbtId>::id() const {
	return nbt_tag_id;
}

template<class ContainedType, unsigned char NbtId>
std::unique_ptr<cpp_nbt::nbt_base> cpp_nbt::nbt_number<ContainedType, NbtId>::clone() const {
	return std::make_unique<nbt_number>(*this);
}

template<class ContainedType, unsigned char NbtId>
const ContainedType & cpp_nbt::nbt_number<ContainedType, NbtId>::value() const {
	return payload;
}

template<class ContainedType, unsigned char NbtId>
ContainedType & cpp_nbt::nbt_number<ContainedType, NbtId>::value() {
	return payload;
}


#endif  // NBT_PRIMITIVE_HPP
