#include "IPrintable.h"

std::ostream& operator<<(std::ostream& stream, IPrintable& printable)
{
	printable.print(stream);
	return stream;
}
