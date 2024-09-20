#include "stdio.h"

int __StringRead(void* str, int ch, int act) {
    char ret;
    __InStrCtrl* isc = (__InStrCtrl*)str;

    switch (act) {
        case __GetAChar:
            ret = *(isc->NextChar);

            if (ret == '\0') {
                isc->NullCharDetected = 1;
                return -1;
            } else {
                isc->NextChar++;
                return ret;
            }

        case __UngetAChar:
            if (isc->NullCharDetected == 0) {
                isc->NextChar--;
            } else {
                isc->NullCharDetected = 0;
            }

            return ch;

        case __TestForError:
            return isc->NullCharDetected;
    }

    return 0;
}
