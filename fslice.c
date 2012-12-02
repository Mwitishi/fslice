#include "fslice.h"

int main(int argc,char **argv)
{
	FILE *f1;

	//Display name & version
	printf("%s %s\n",FSLICE_NAME,FSLICE_VERSION);

	//If no arguments passed
	if(argc<2)
	{
		printf(FSLICE_MSG_NO_COMMAND,argv[0],FSLICE_COM_HELP);
		return 1;
	}

	//Display program help
	if(strcmp(argv[1],FSLICE_COM_HELP)==0)	printf(FSLICE_MSG_HELP);

	//Create new file
	if(strcmp(argv[1],FSLICE_COM_CREATE)==0)
	{
		printf(FSLICE_MSG_CREATE);

		//If no filename passed
		if(argc<3)
		{
			printf(FSLICE_MSG_NO_FILENAME);
			return 2;
		}

		//Check if file exists
		f1=fopen(argv[2],"rb+");
		if(f1!=NULL)
		{
			fclose(f1);
			printf(FSLICE_MSG_CREATE_EXISTS);
			return 3;
		}

		//Create file
		f1=fopen(argv[2],"wb+");

		//Check if file created successfully
		if(f1==NULL)
		{
			printf(FSLICE_MSG_CREATE_ERR);
			return 4;
		}

		//Close file
		fclose(f1);
	}

	//Delete existing file
	if(strcmp(argv[1],FSLICE_COM_DELETE)==0)
	{
		printf(FSLICE_MSG_DELETE);

		//If no filename passed
		if(argc<3)
		{
			printf(FSLICE_MSG_NO_FILENAME);
			return 2;
		}

		//Check if file exists
		f1=fopen(argv[2],"rb+");
		if(f1==NULL)
		{
			printf(FSLICE_MSG_DELETE_NEXISTS);
			return 3;
		}

		//Close file
		fclose(f1);

		//Delete file
		if(remove(argv[2])!=0)
		{
			printf(FSLICE_MSG_DELETE_ERR);
			return 4;
		}
	}

	return 0;
}
