#include "audiors232-common.h"

void convertSend(short *buf, short c1, short c2, short value, int buflen, int bitlen)
{
	// start bit
	for (int i = 0; i < bitlen; ++i) {
		// left
		if (c1 >= 0) {
			*buf++ = +value;
		} else {
			*buf++ = 0;
		}
		// right
		if (c2 >= 0) {
			*buf++ = +value;
		} else {
			*buf++ = 0;
		}
	}

	// send char
	for (int b = 0; b < 8; ++b) {
		for (int i = 0; i < bitlen; ++i) {
			// left
			if (c1 >= 0) {
				*buf++ = (c1 & (1 << b)) ? -value : +value;
			} else {
				*buf++ = 0;
			}
			// right
			if (c2 >= 0) {
				*buf++ = (c2 & (1 << b)) ? -value : +value;
			} else {
				*buf++ = 0;
			}
		}
	}

	// stop bit
	for (int i = 0; i < bitlen; ++i) {
		// left
		if (c1 >= 0) {
			*buf++ = -value;
		} else {
			*buf++ = 0;
		}
		// right
		if (c2 >= 0) {
			*buf++ = -value;
		} else {
			*buf++ = 0;
		}
	}

	// wait
	for (int i = 0; i < buflen - 10 * bitlen; ++i) {
		// left
		*buf++ = 0;
		// right
		*buf++ = 0;
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
