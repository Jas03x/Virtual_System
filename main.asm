
ARRAY1: BYTE [0, 1, 2, 3]
DATA1: BYTE 4
DATA2: INT 5

STRING: BYTE "Hello World"

#define PRINT_CHAR BIOS_PRINT_CHAR
#define EXIT BIOS_EXIT

START:
    MOVI ESI STRING

LOOP:
    INT PRINT_CHAR
    INC ESI
    CMP ESI 0
    JNE LOOP

INT EXIT
