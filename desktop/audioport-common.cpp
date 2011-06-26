#include <limits.h>
#include "audioport-common.h"

#define MAX SHRT_MAX
#define MIN SHRT_MIN

void convertSendRS232(short *buf, short character)
{
	const int len = 3;
	int idx = 0;

	// start bit
	for (int i = 0; i < len; ++i) {
		if (character >= 0) {
			*buf++ = MAX;
			*buf++ = MAX;
		} else {
			*buf++ = MIN;
			*buf++ = MIN;
		}
	}

	// send char
	for (int b = 0; b < 8; ++b) {
		for (int i = 0; i < len; ++i) {
			if (character >= 0) {
				*buf++ = (character & (1 << b)) ? MIN : MAX;
				*buf++ = (character & (1 << b)) ? MIN : MAX;
			} else {
				*buf++ = MIN;
				*buf++ = MIN;
			}
		}
	}

	// stop bit
	for (int i = 0; i < len; ++i) {
		*buf++ = MIN;
		*buf++ = MIN;
	}

	// filling
	*buf++ = MIN;
	*buf++ = MIN;
	*buf++ = MIN;
	*buf++ = MIN;
}

void convertSendManchester(short *buf, short character)
{
	const int len = 4;
	for (int b = 0; b < 8; ++b) {
		for (int i = 0; i < len; ++i) {
			if (character >= 0) {
				*buf++ = (character & (1 << b)) ? MAX : MIN;
				*buf++ = (character & (1 << b)) ? MAX : MIN;
			} else {
				*buf++ = 0;
				*buf++ = 0;
			}
		}
		for (int i = 0; i < len; ++i) {
			if (character >= 0) {
				*buf++ = (character & (1 << b)) ? MIN : MAX;
				*buf++ = (character & (1 << b)) ? MIN : MAX;
			} else {
				*buf++ = 0;
				*buf++ = 0;
			}
		}
	}
}

void convertSendRZ(short *buf, short character)
{
	const int len = 4;
	for (int b = 0; b < 8; ++b) {
		for (int i = 0; i < len; ++i) {
			if (character >= 0) {
				*buf++ = (character & (1 << b)) ? MAX : MIN;
				*buf++ = (character & (1 << b)) ? MAX : MIN;
			} else {
				*buf++ = 0;
				*buf++ = 0;
			}
		}
		for (int i = 0; i < len; ++i) {
			*buf++ = 0;
			*buf++ = 0;
		}
	}
}

CyclicBuffer::CyclicBuffer(int _size) : size(_size), start(0), end(0)
{
	buf = new char[size];
}

CyclicBuffer::~CyclicBuffer()
{
	delete buf;
}

void CyclicBuffer::put(const char c)
{
	if (end + 1 == start) return;
	buf[end] = c;
	end = (end + 1) % size;
}

void CyclicBuffer::put(const char *str)
{
	for (const char *i = str; (*i) && (end + 1 != start); ++i) {
		buf[end] = *i;
		end = (end + 1) % size;
	}
}

short CyclicBuffer::get()
{
	if (start != end) {
		short r = buf[start];
		start = (start + 1) % size;
		return r;
	} else {
		return -1;
	}
}
