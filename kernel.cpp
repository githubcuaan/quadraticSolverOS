#include "types.h"
#include "gdt.h"

void printf(char* str)
{
    // GPU reads from address 0xb8000 what to write to the screen
    // With variable type 'short' we group 2 bytes together
    // First byte is of background/foreground (4 bits each), and other byte for character
    uint16_t* VideoMemory = (uint16_t*)0xb8000;
    
    for (int i = 0; str[i] != '\0'; ++i)
    {
        // Set character to low-byte of the element and keep old value of high-byte
        VideoMemory[i] = (VideoMemory[i] & 0xFF00) | str[i];
    }

}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;

extern "C" void callConstructors()
{
    for (constructor* i = &start_ctors; i != &end_ctors; ++i)
        (*i)();
}

extern "C" void kernelMain(void* multibootStruct, uint32_t magicNum)
{
    printf("Hello world");

    GlobalDescriptorTable gdt;

    while (true);
}