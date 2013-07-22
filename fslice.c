#include "fslice.h"

//Global variable for counting bytes printed so far
int fslice_tbytes;

/*
 *  Function for printing the contents of the buffer in specified visualization mode.
 *  size is the number of bytes to be written (normally FSLICE_BUF_SIZE).
 *  offset is the position to start reading
 *  after printed bytes exceed maxbytes, stop
 */
int fslice_print(char *vmode, uint8_t *buf, int size, int offset, int maxbytes)
{
    int i1,i2;

    //Check for NULL pointers
    if(vmode == NULL || buf == NULL)
    {
        printf(FSLICE_MSG_NULL_POINTER);
        return 1;
    }

    //Loop through the buffer
    for(i1 = 0 ; i1 < size && fslice_tbytes < maxbytes ; i1++)
    {
        //Print bytes as characters
        if(strcmp(vmode, FSLICE_VMODE_CHAR) == 0)
            printf("%c", (char)buf[i1]);

        //Print byte values as numbers
        if(strcmp(vmode, FSLICE_VMODE_NUM) == 0)
            printf("%.2x ", (uint8_t)buf[i1]);

        //Print full format
        if(strcmp(vmode, FSLICE_VMODE_FULL) == 0)
        {
            //Print the data, calculate characters to fill
            i2 = FSLICE_DISPL_DIST - printf(FSLICE_FULL_FORMAT, fslice_tbytes + offset, (int)buf[i1]) % FSLICE_DISPL_DIST;

            //Newline after writing FSLICE_DISPL_COLS entries in each line
            if((fslice_tbytes + 1) % FSLICE_DISPL_COLS == 0) printf("\n");

            //Fill space until entry reaches FSLICE_DISPL_DIST length
            else printf("%*s", i2, "");
        }

        //Increase count of bytes written
        fslice_tbytes++;
    }

    return 0;
}

int main(int argc, char **argv)
{
    int i1, i2, i3;
    uint8_t *buf = (uint8_t*)malloc(FSLICE_BUF_SIZE);
    FILE *f1 = NULL;
    struct stat st1;

    //Display name & version
    printf("%s %s\n", FSLICE_NAME, FSLICE_VERSION);

    //If no arguments passed
    if(argc < 2)
    {
        printf(FSLICE_MSG_NO_COMMAND, argv[0], FSLICE_COM_HELP);
        return 1;
    }

    //Display program help
    if(strcmp(argv[1], FSLICE_COM_HELP) == 0)
    {
        printf(FSLICE_MSG_HELP);
        return 0;
    }

    //Create new file
    if(strcmp(argv[1], FSLICE_COM_CREATE) == 0)
    {
        printf(FSLICE_MSG_CREATE);

        //If no filename passed
        if(argc < 3)
        {
            printf(FSLICE_MSG_NO_FILENAME);
            return 2;
        }

        //Check if file exists
        f1 = fopen(argv[2], "rb+");
        if(f1 != NULL)
        {
            fclose(f1);
            f1 = NULL;
            printf(FSLICE_MSG_CREATE_EXISTS);
            return 3;
        }

        //Create file
        f1 = fopen(argv[2], "wb+");

        //Check if file created successfully
        if(f1 == NULL)
        {
            printf(FSLICE_MSG_CREATE_ERR);
            return 4;
        }

        //Close file
        fclose(f1);
        f1 = NULL;

        return 0;
    }

    //Delete existing file
    if(strcmp(argv[1], FSLICE_COM_DELETE) == 0)
    {
        printf(FSLICE_MSG_DELETE);

        //If no filename passed
        if(argc < 3)
        {
            printf(FSLICE_MSG_NO_FILENAME);
            return 2;
        }

        //Check if file exists
        f1 = fopen(argv[2], "rb+");
        if(f1 == NULL)
        {
            printf(FSLICE_MSG_NEXISTS);
            return 3;
        }

        //Close file
        fclose(f1);
        f1 = NULL;

        //Delete file
        if(remove(argv[2]) != 0)
        {
            printf(FSLICE_MSG_DELETE_ERR);
            return 4;
        }

        return 0;
    }

    //Print part of a file
    if(strcmp(argv[1], FSLICE_COM_SLICE) == 0)
    {
        printf(FSLICE_MSG_SLICE);

        //If any arguments are missing
        if(argc < 5)
        {
            printf(FSLICE_MSG_NO_FILENAME);
            return 2;
        }

        //Get stat data, return if file does not exist
        if(stat(argv[3], &st1) == -1)
        {
            printf(FSLICE_MSG_NEXISTS);
            return 3;
        }

        //Print file size
        printf(FSLICE_MSG_SIZE, (int)st1.st_size);

        //Process the positions, return if not valid
        if(sscanf(argv[4], "%d:%d", &i1, &i2) !=2 || i1 < 0 || i2 < 0
        || i1 > i2 || i1 >= st1.st_size || i2 >= st1.st_size)
        {
            printf(FSLICE_MSG_INVPOS);
            return 4;
        }

        //Check positions
        printf(FSLICE_MSG_POS, i1, i2);

        fslice_tbytes = 0;

        //Loop while there is data to read
        do {
            //Open file, check for errors
            f1 = fopen(argv[3], "rb+");
            if(f1 == NULL)
            {
                printf(FSLICE_MSG_SLICE_ERR);
                return 5;
            }

            //Access correspondent position and fill buffer
            //i3 stores bytes read, if different from FSLICE_BUF_SIZE, EOF was reached
            fseek(f1, i1 + fslice_tbytes, SEEK_SET);
            i3 = fread(buf, 1, FSLICE_BUF_SIZE, f1);

            //Close file
            fclose(f1);
            f1 = NULL;

            //Print data
            fslice_print(argv[2], buf, i3, i1, i2 - i1 + 1);
        } while(i3 == FSLICE_BUF_SIZE && fslice_tbytes < i2 - i1 + 1);

        //Add newline at the end
        if(strcmp(argv[2], FSLICE_VMODE_FULL) != 0 || fslice_tbytes % FSLICE_DISPL_COLS != 0) printf("\n");

        return 0;
    }

    //Write a particular byte in a file
    if(strcmp(argv[1], FSLICE_COM_WRITE) == 0)
    {
        printf(FSLICE_MSG_WRITE);

        //If arguments are missing
        if(argc < 4)
        {
            printf(FSLICE_MSG_NO_FILENAME);
            return 2;
        }

        //Get stat data, return if file does not exist
        if(stat(argv[2], &st1) == -1)
        {
            printf(FSLICE_MSG_NEXISTS);
            return 3;
        }

        //Print file size
        printf(FSLICE_MSG_SIZE, (int)st1.st_size);

        //Process the positions, return if not valid
        if(sscanf(argv[3], "%d:%d", &i1, &i2) != 2 || i1 < 0 || i2 < 0
        || i2 > 255)
        {
            printf(FSLICE_MSG_INVPOS);
            return 4;
        }

        //Check data and position
        printf(FSLICE_MSG_WRITE_CHECK, i2, i1);

        //Open file
        f1 = fopen(argv[2], "rb+");

        //Write data at position, check for errors
        fseek(f1, i1, SEEK_SET);
        if(fwrite(&i2, sizeof(char), 1, f1) != 1)
        {
            printf(FSLICE_MSG_WRITE_ERR);
            return 5;
        }

        //Close file
        fclose(f1);
        f1 = NULL;

        return 0;
    }

    //Invalid command
    printf(FSLICE_MSG_INVCOMMAND);
    return 1;
}
