#include <nagisa/bit/bit.h>

int main()
{
	static_assert(::nagisa::bits::mask<12>() == 0xfff);

	return 0;
}