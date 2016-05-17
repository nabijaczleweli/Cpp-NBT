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
#ifndef NBT_ARRAY_HPP
#define NBT_ARRAY_HPP


#include "nbt_base.hpp"
#include <memory>
#include <vector>
#include <istream>
#include <ostream>


namespace cpp_nbt {
	template<class ContainedType, unsigned char NbtId>
	class nbt_array : public nbt_base {
		private:
			std::vector<ContainedType> payload;

		public:
			static const unsigned char nbt_tag_id;


			nbt_array() = default;
			explicit nbt_array(std::vector<ContainedType> value);
			nbt_array(const nbt_array & other) = default;
			nbt_array(nbt_array && other) = default;

			virtual ~nbt_array() = default;

			virtual void swap(nbt_base & with) override;
			virtual void swap(nbt_array & with);

			nbt_array & operator=(nbt_array from);
			virtual bool operator==(const nbt_base & to) override;
			virtual bool operator==(const nbt_array & to);

			virtual void read(std::istream & from) override;
			virtual void write(std::ostream & to) const override;

			virtual unsigned char id() const override;

			virtual std::unique_ptr<nbt_base> clone() const override;

			const std::vector<ContainedType> & value() const;
			std::vector<ContainedType> & value();
	};

	using nbt_byte_array = nbt_array<char, 7>;
	using nbt_int_array = nbt_array<int, 11>;
}


template<class ContainedType, unsigned char NbtId>
const unsigned char cpp_nbt::nbt_array<ContainedType, NbtId>::nbt_tag_id = NbtId;


template<class ContainedType, unsigned char NbtId>
cpp_nbt::nbt_array<ContainedType, NbtId>::nbt_array(std::vector<ContainedType> value) : nbt_base(), payload(std::move(value)) {}

template<class ContainedType, unsigned char NbtId>
void cpp_nbt::nbt_array<ContainedType, NbtId>::swap(cpp_nbt::nbt_base & with) {
	swap(dynamic_cast<cpp_nbt::nbt_array<ContainedType, NbtId> &>(with));
}

template<class ContainedType, unsigned char NbtId>
void cpp_nbt::nbt_array<ContainedType, NbtId>::swap(cpp_nbt::nbt_array<ContainedType, NbtId> & with) {
	payload.swap(with.payload);
}

template<class ContainedType, unsigned char NbtId>
cpp_nbt::nbt_array<ContainedType, NbtId> & cpp_nbt::nbt_array<ContainedType, NbtId>::operator=(cpp_nbt::nbt_array<ContainedType, NbtId> from) {
	swap(from);
	return *this;
}

template<class ContainedType, unsigned char NbtId>
bool cpp_nbt::nbt_array<ContainedType, NbtId>::operator==(const cpp_nbt::nbt_base & to) {
	return operator==(dynamic_cast<const cpp_nbt::nbt_array<ContainedType, NbtId> &>(to));
}

template<class ContainedType, unsigned char NbtId>
bool cpp_nbt::nbt_array<ContainedType, NbtId>::operator==(const cpp_nbt::nbt_array<ContainedType, NbtId> & to) {
	return nbt_base::operator==(to) && payload == to.payload;
}

template<class ContainedType, unsigned char NbtId>
void cpp_nbt::nbt_array<ContainedType, NbtId>::read(std::istream & from) {
	int * length = new int;
	from.read(static_cast<char *>(static_cast<void *>(length)), sizeof(*length));

	payload.resize(*length);
	from.read(static_cast<char *>(static_cast<void *>(payload.data())), *length * sizeof(ContainedType));

	delete length; length = nullptr;
}

template<class ContainedType, unsigned char NbtId>
void cpp_nbt::nbt_array<ContainedType, NbtId>::write(std::ostream & to) const {
	const int * length = new int(payload.size());
	to.write(static_cast<const char *>(static_cast<const void *>(length)), sizeof(*length));

	to.write(static_cast<const char *>(static_cast<const void *>(payload.data())), payload.size() * sizeof(ContainedType));

	delete length; length = nullptr;
}

template<class ContainedType, unsigned char NbtId>
unsigned char cpp_nbt::nbt_array<ContainedType, NbtId>::id() const {
	return nbt_tag_id;
}

template<class ContainedType, unsigned char NbtId>
std::unique_ptr<cpp_nbt::nbt_base> cpp_nbt::nbt_array<ContainedType, NbtId>::clone() const {
	return std::make_unique<nbt_array>(*this);
}

template<class ContainedType, unsigned char NbtId>
const std::vector<ContainedType> & cpp_nbt::nbt_array<ContainedType, NbtId>::value() const {
	return payload;
}

template<class ContainedType, unsigned char NbtId>
std::vector<ContainedType> & cpp_nbt::nbt_array<ContainedType, NbtId>::value() {
	return payload;
}


#endif  // NBT_ARRAY_HPP
