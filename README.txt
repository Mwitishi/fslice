FSlice is an application for carrying out several operations on files, such as creating and deleting them, reading and writing data...

Syntax: fslice <command> <parameters>

Currently encoded commands:

  * "help": lists available commands and usage

  * "create <filename>": attempts to create an empty file with the specified filename.
        It does not overwrite existing files.

  * "delete <filename>": attempts to delete an already existing file.

  * "slice <visualization mode> <filename> <start>:<end>":
        shows data read from file <filename>,
        from position <start> to <end> of file,
        according to <visualization mode>.

  * "write <filename> <position>:<data>":
        overwrites specified position in file
        with a byte of data (in decimal form).

Planned commands:

Visualization modes:

  * "char": write each byte of data as a character.

  * "num": write each byte of data as a number (0 to 255), separated by spaces.

  * "full": write each byte next to its position in format "Position <position>: <data>".
