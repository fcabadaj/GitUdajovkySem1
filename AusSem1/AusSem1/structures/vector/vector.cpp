#include "vector.h"
#include "../ds_routines.h"
#include <cstdlib>
#include <cstring>

namespace structures {

	Vector::Vector(size_t size) :
		memory_(calloc(size, 1)),
		size_(size)
	{
	}

	Vector::Vector(const Vector& other) :
		Vector(other.size_)
	{
		memcpy(this->memory_,other.memory_,other.size_);
	}

	Vector::~Vector()
	{
		free(memory_);
		this->size_ = 0;
		memory_ = nullptr;
	}

	Structure* Vector::clone() const
	{
		return new Vector(*this);
	}

	size_t Vector::size() const
	{
		return size_;
	}

	Structure & Vector::operator=(const Structure & other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other)
	{
		if (this != &other) {
			this->size_ = other.size_;
			this->memory_ = realloc(this->memory_,other.size_);
			memcpy(this->memory_, other.memory_, other.size_);
		};
		return *this;
	}

	bool Vector::operator==(const Vector& other) const
	{
		return (this->size_ == other.size_ && memcmp(this->memory_, other.memory_, other.size_) == 0);
	}

	byte& Vector::operator[](const int index)
	{
		return *this->getBytePointer(index);
	}

	byte Vector::operator[](const int index) const
	{
		return *this->getBytePointer(index);
	}

	byte* Vector::getBytePointer(const int index) const
	{
		DSRoutines::rangeCheckExcept(index, this->size_, "Vector index out of range.");
		return reinterpret_cast<byte*>(this->memory_) + index;
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest)
	{
		DSRoutines::rangeCheckExcept(index, this->size_ + 1, "Vector index out of range.");
		memcpy(&dest, getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length)
	{
		DSRoutines::rangeCheckExcept(srcStartIndex, src.size_, "Vector index out of range.");
		DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Vector index out of range.");
		DSRoutines::rangeCheckExcept(destStartIndex, dest.size_, "Vector index out of range.");
		DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Vector index out of range.");
		if (&src == &dest &&
			(srcStartIndex <= destStartIndex && srcStartIndex + length > destStartIndex) ||
			(destStartIndex <= srcStartIndex && destStartIndex + length > srcStartIndex)) {
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else {
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	

}