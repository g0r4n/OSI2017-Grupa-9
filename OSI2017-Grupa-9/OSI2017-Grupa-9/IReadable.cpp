#include "IReadable.h"

std::istream& operator>>(std::istream& stream, IReadable& readable)
{
	readable.read(stream);
	return stream;
}
