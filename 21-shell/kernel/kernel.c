#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "shell.h"
#include "../libc/string.h"

void main() {
    isr_install();
    irq_install();

    kprint("Type something, it will go through the kernel\n"
        "Type EXIT to halt the CPU\n> ");   
}

void user_input(char *input) {
    shell(input);
}
