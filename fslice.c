#include "fslice.h"

int main(int argc,char **argv)
{
	if(argc<2)
	{
		printf("Error, command missing. Write \"%s %s\" for help.\n",argv[0],FSLICE_COM_HELP);
		return 1;
	}

	return 0;
}
