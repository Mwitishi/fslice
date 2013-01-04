#ifndef FSLICE_H
#define FSLICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FSLICE_NAME "FSlice by Mwitishi"
#define FSLICE_VERSION "v0.1"

#define FSLICE_COM_HELP "help"
#define FSLICE_COM_CREATE "create"
#define FSLICE_COM_DELETE "delete"

#define FSLICE_MSG_NO_COMMAND "Error, command missing. Write \"%s %s\" for help.\n"
#define FSLICE_MSG_HELP "This program allows you to read and modify files.\n\
These are the available commands:\n\
help: display this help.\n\
create <filename>: create a file with specified name.\n\
delete <filename>: delete the file with specified name.\n"
#define FSLICE_MSG_CREATE "Attempting to create file...\n"
#define FSLICE_MSG_NO_FILENAME "Error, no filename specified.\n"
#define FSLICE_MSG_CREATE_EXISTS "Error, the specified file already exists.\n"
#define FSLICE_MSG_CREATE_ERR "Error while creating file.\n"
#define FSLICE_MSG_DELETE "Attempting to delete file...\n"
#define FSLICE_MSG_DELETE_NEXISTS "Error, the specified file doesn\'t exist.\n"
#define FSLICE_MSG_DELETE_ERR "Error while deleting file.\n"

#endif
