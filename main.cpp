#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "priorityTodoQueue.hpp"
#include <boost/lambda/lambda.hpp>
#include <iterator>
#include <algorithm>

/*
	Note:
	Ok, so basically i'm gonna make this cli and
	then just add more and more features from there.
	Hopefully, this project won't be cli forever.
*/

const static std::time_t NOW = std::time(0);

int main(int argc, char* argsv[])
{
	using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 3) << " " );
}
