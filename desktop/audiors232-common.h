#ifndef AUDIORS232_COMMON_H
#define AUDIORS232_COMMON_H

void convertSend(short *buf, short c1, short c2, short value, int buflen, int bitlen);

class CyclicBuffer
{
public:
	CyclicBuffer(int size);
	~CyclicBuffer();
	void put(const char c);
	void put(const char *str);
	short get();

private:
	int size, start, end;
	char *buf;
};

#endif
