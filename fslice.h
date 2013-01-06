#ifndef FSLICE_H
#define FSLICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FSLICE_NAME "FSlice by Mwitishi"
#define FSLICE_VERSION "v0.2"

#define FSLICE_BUF_SIZE 20
#define FSLICE_DISPL_COLS 4
#define FSLICE_DISPL_DIST 20

#define FSLICE_COM_HELP "help"
#define FSLICE_COM_CREATE "create"
#define FSLICE_COM_DELETE "delete"
#define FSLICE_COM_SLICE "slice"
#define FSLICE_COM_WRITE "write"

#define FSLICE_VMODE_CHAR "char"
#define FSLICE_VMODE_NUM "num"
#define FSLICE_VMODE_FULL "full"

#define FSLICE_FULL_FORMAT "Position %d:%d"

#define FSLICE_MSG_NO_COMMAND "Error, command missing. Write \"%s %s\" for help.\n"
#define FSLICE_MSG_INVCOMMAND "Error, unable to recognise the issued command.\n"
#define FSLICE_MSG_HELP "This program allows you to read and modify files.\n\
These are the available commands:\n\
\"help\": display this help.\n\
\"create <filename>\": create a file with specified name.\n\
\"delete <filename>\": delete the file with specified name.\n\
\"slice <visualization mode> <filename> <start>:<end>\": read data from start to end in specified file,\n\
and print according to visualization mode.\n\
\"write <filename> <position>:<data>\": write a byte of data in specified position of a file.\n"
#define FSLICE_MSG_NO_FILENAME "Error, no filename specified.\n"
#define FSLICE_MSG_NEXISTS "Error, the specified file doesn\'t exist.\n"
#define FSLICE_MSG_INVPOS "Error, the specified position is invalid.\n"
#define FSLICE_MSG_NULL_POINTER "Error, received a NULL pointer.\n"
#define FSLICE_MSG_SIZE "File size: %d bytes.\n"
#define FSLICE_MSG_POS "Reading from position %d to %d.\n"
#define FSLICE_MSG_CREATE "Attempting to create file...\n"
#define FSLICE_MSG_CREATE_EXISTS "Error, the specified file already exists.\n"
#define FSLICE_MSG_CREATE_ERR "Error while creating file.\n"
#define FSLICE_MSG_DELETE "Attempting to delete file...\n"
#define FSLICE_MSG_DELETE_ERR "Error while deleting file.\n"
#define FSLICE_MSG_SLICE "Attempting to slice file...\n"
#define FSLICE_MSG_SLICE_ERR "Error while reading file.\n"
#define FSLICE_MSG_WRITE "Attempting to write on file...\n"
#define FSLICE_MSG_WRITE_CHECK "Writing value %d in position %d.\n"
#define FSLICE_MSG_WRITE_ERR "Error while writing on file.\n"

#endif
