#include "fslice.h"

int main(int argc,char **argv)
{
	//Display name & version
	printf("%s %s\n",FSLICE_NAME,FSLICE_VERSION);

	//If no arguments passed
	if(argc<2)
	{
		printf("Error, command missing. Write \"%s %s\" for help.\n",argv[0],FSLICE_COM_HELP);
		return 1;
	}

	//Display program help
	if(strcmp(argv[1],FSLICE_COM_HELP)==0)	printf(FSLICE_MSG_HELP);

	return 0;
}
