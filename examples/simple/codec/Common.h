#ifndef MUDUO_EXAMPLES_SIMPLE_COMMON_H 
#define MUDUO_EXAMPLES_SIMPLE_COMMON_H
#include <stdlib.h>
#include <string>
#include <stdint.h>

const int32_t kPackageHeaderLength = 4;
const int32_t kPackageMaxLength = 0x100000; // 64M
const int32_t kCheckSumLength = 2;

// const uint16_t checksum(const uint16_t *buffer, int size);
// bool compress_(uint32_t i, char *buf, size_t &length);
// bool uncompress_(char *buf, size_t length, uint32_t &i);

const uint16_t checksum(const uint16_t *buffer, int size)
{
    uint16_t cksum = 0;
    while(size > 1)
    {
        cksum += *buffer++;
        size -= sizeof(uint16_t);
    }
    if(size)
    {
        cksum += *(unsigned char*)(buffer);
    }
    //将32位数转换成16
    while (cksum >> 16)
        cksum = (cksum >> 16) + (cksum & 0xffff);
    return static_cast<uint16_t>(~cksum);
}

bool compress_(uint32_t i, char *buf, size_t &length)
{
    length = 0;
    for (int a=4; a>=0; a--)
    {
        char c;
        c = i >> (a*7) & 0x7f;
        if (c == 0x00 && length == 0)
            continue;

        if (a == 0)
            c &= 0x7f;
        else
            c |= 0x80;
        buf[length] = c;
        length++;
    }

    if (length == 0) {
        length++;
        buf[0] = 0;
    }

    return true;
}

bool uncompress_(char *buf, size_t length, uint32_t &i)
{
    i = 0;
    for (int index = 0; index < (int)length; index++)
    {
        char c = *(buf + index);
        i = i << 7;

        c &= 0x7f;
        i |= c;
    }
    return true;
}

#endif // MUDUO_EXAMPLES_SIMPLE_COMMON_H
