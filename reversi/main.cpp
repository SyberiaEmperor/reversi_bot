
#include"interface.h"

using namespace std;

int main(int argc, char*argv[])
{
	//reversi r;
	//auto p = make_shared<reversi>(r);
	//auto v = r.getNextVariants();
	//uint8_t compColor = 1;
	//chooseNewVariant(p, compColor);
	//chooseNewVariant(p, 0);

	Interface inter(atoi(argv[argc - 1]));

	return inter.startGameLoop();
}