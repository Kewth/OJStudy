#include <iostream>
#include <string>

std::string week[7] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

int main(void)
{
	int y, m, d;
	int w;
	std::cin >> y >> m >> d;
	w = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400 + 1) % 7;
	std::cout << week[w] << std::endl;
	return 0;
}
