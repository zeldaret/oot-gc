static void (*FatalFunc)();

void __DVDPrintFatalMessage(void) {
    if (FatalFunc != 0) {
        (*FatalFunc)();
    }
    return;
}
