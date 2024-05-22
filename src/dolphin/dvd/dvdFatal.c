static void (*FatalFunc)();

/* void ShowMessage(void)
{
    // UNUSED FUNCTION
} */

/* void DVDSetAutoFatalMessaging(void)
{
    // UNUSED FUNCTION
} */

void __DVDPrintFatalMessage(void) {
    if (FatalFunc != 0) {
        (*FatalFunc)();
    }
    return;
}
