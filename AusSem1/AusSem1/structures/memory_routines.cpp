#include "memory_routines.h"

namespace structures {
	byte & MemoryRoutines::byteSet(byte & B)
	{		
		return B = MAX_BYTE;
	}
	byte & MemoryRoutines::byteReset(byte & B)
	{
		return B = 0;
	}
	byte & MemoryRoutines::byteXOR(byte & B)
	{
		return B ^= B;
	}
	byte & MemoryRoutines::byteSHL(byte & B)
	{		
		return B<<=1;
	}
	byte & MemoryRoutines::byteSHR(byte & B)
	{
		return B>>=1;
	}
	bool MemoryRoutines::byteNthBitGet(byte & B, int n)
	{
		return false;
	}

	byte & MemoryRoutines::byteNthBitTo0(byte & B, int n)
	{
		return byteNthBitGet(B, n) ? B ^= B << n : B;
	}

	byte & MemoryRoutines::byteNthBitTo1(byte & B, int n)
	{
		return !byteNthBitGet(B, n) ? B |= 1 << n : B;
	}

	byte & MemoryRoutines::byteNthBitToggle(byte & B, int n)
	{
		return byteNthBitGet(B, n) ? byteNthBitTo0(B, n) : byteNthBitTo1(B, n);
	}

	MemoryRoutines::MemoryRoutines()
	{
	}

}
