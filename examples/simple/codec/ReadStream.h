#ifndef MUDUO_EXAMPLES_SIMPLE_READSTREAM_H 
#define MUDUO_EXAMPLES_SIMPLE_READSTREAM_H
#include "Common.h"

#include <stdlib.h>
#include <cassert>
#include <string>
#include <stdint.h>

class BinaryReadStream
{
public:
    BinaryReadStream(const char* data, size_t length)
        : data_(data), length_(length), current_(data)
    {
        current_ += kPackageHeaderLength + kCheckSumLength;
    }

    bool IsEmpty() const { return length_ <= kPackageHeaderLength; }
    bool IsEnd() const {
        assert(current_ <= data_ + length_);
        return current_ == data_ + length_;
    }
    const char* GetData() const { return data_; }
    size_t GetSize() const { return length_; }
	const char* GetCurrent() const{ return current_; }

	bool Read(std::string *str, size_t maxlen, size_t& outlen);
	bool Read(char* str, size_t strlen, size_t& length);
	bool Read(const char** str, size_t maxlen, size_t& outlen);
	bool Read(int &i);
	bool Read(int16_t &i);
	bool Read(char &c);
	size_t ReadAll(char* szBuffer, size_t iLen) const;
	bool ReadLength(size_t& length);
	bool ReadLengthWithoutOffset(size_t& headlen, size_t& outlen);

private:
	const char* const data_;
	const size_t length_;
	const char* current_;
};

#endif // MUDUO_EXAMPLES_SIMPLE_STREAM_H
