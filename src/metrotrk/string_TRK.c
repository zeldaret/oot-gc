int TRK_strlen(const char* s) {
    unsigned char c;
    int result = -1;
    unsigned char* sTemp = (unsigned char*)s - 1;

    do {
        c = sTemp[1];
        sTemp++;
        result++;
    } while (c != 0);

    return result;
}
