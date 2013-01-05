#include "fslice.h"

//Global variable for counting bytes printed so far
int fslice_tbytes;

/*
 *  Function for printing the contents of the buffer in specified visualization mode.
 *  size is the number of bytes to be written (normally FSLICE_BUF_SIZE).
 */
int fslice_write(char *vmode,char *buf,int size)
{
    int i1,i2;

    //Check for NULL pointers
    if(vmode==NULL||buf==NULL)
    {
        printf(FSLICE_MSG_NULL_POINTER);
        return 1;
    }

    //Loop through the buffer
    for(i1=0;i1<size;i1++)
    {
        //Print bytes as characters
        if(strcmp(vmode,FSLICE_VMODE_CHAR)==0)
            printf("%c",buf[i1]);

        //Print byte values as numbers
        if(strcmp(vmode,FSLICE_VMODE_NUM)==0)
            printf("%d",(int)buf[i1]);

        //Print full format
        if(strcmp(vmode,FSLICE_VMODE_FULL)==0)
        {
            //Print the data, calculate characters to fill
            i2=FSLICE_DISPL_DIST-(printf(FSLICE_FULL_FORMAT,fslice_tbytes,(int)buf[i1]))%FSLICE_DISPL_DIST;

            //Newline after writing FSLICE_DISPL_COLS entries in each line
            if((fslice_tbytes+1)%FSLICE_DISPL_COLS==0) printf("\n");

            //Fill space until entry reaches FSLICE_DISPL_DIST length
            else printf("%*s",i2,"");
        }

        //Increase count of bytes written
        fslice_tbytes++;
    }

    return 0;
}

int main(int argc,char **argv)
{
    char *buf=(char*)malloc(FSLICE_BUF_SIZE);
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
    if(strcmp(argv[1],FSLICE_COM_HELP)==0)
    {
        printf(FSLICE_MSG_HELP);
        return 0;
    }

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

        return 0;
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
            printf(FSLICE_MSG_NEXISTS);
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

        return 0;
    }

    if(strcmp(argv[1],FSLICE_COM_SLICE)==0)
    {
        if(argc<3)
        {
            printf(FSLICE_MSG_NO_FILENAME);
            return 2;
        }

        return 0;
    }

    printf(FSLICE_MSG_INVCOMMAND);
    return 1;
}
