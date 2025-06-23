GPPPARAMS = -m32 -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fno-stack-protector
ASPARAMS = --32
LDPARAMS = -melf_i386

# Source directories
BOOT_DIR = boot
DRIVERS_DIR = drivers
KERNEL_DIR = kernel
KERNEL_CORE_DIR = kernel/core
KERNEL_INTERRUPTS_DIR = kernel/interrupts
KERNEL_MEMORY_DIR = kernel/memory

# Include paths
INCLUDES = -I$(KERNEL_DIR) -I$(DRIVERS_DIR) -I$(KERNEL_CORE_DIR) -I$(KERNEL_MEMORY_DIR) -I$(KERNEL_INTERRUPTS_DIR)

objects = $(BOOT_DIR)/loader.o \
          $(KERNEL_MEMORY_DIR)/gdt.o \
          $(DRIVERS_DIR)/port.o \
          $(KERNEL_INTERRUPTS_DIR)/interrupts_asm.o \
          $(KERNEL_INTERRUPTS_DIR)/interrupts.o \
          $(KERNEL_CORE_DIR)/kernel.o

%.o: %.cpp
	g++ $(GPPPARAMS) $(INCLUDES) -o $@ -c $<

%.o: %.s
	as $(ASPARAMS) -o $@ $<

mykernel.bin: $(BOOT_DIR)/linker.ld $(objects)
	ld $(LDPARAMS) -T $< -o $@ $(objects)

mykernel.iso: mykernel.bin
	mkdir iso
	mkdir iso/boot
	mkdir iso/boot/grub
	
	cp $< iso/boot/
	
	echo 'set timeout=0' >> iso/boot/grub/grub.cfg
	echo 'set default=0' >> iso/boot/grub/grub.cfg
	echo '' >> iso/boot/grub/grub.cfg
	echo 'menuentry "My OS" {' >> iso/boot/grub/grub.cfg
	echo '	multiboot /boot/mykernel.bin' >> iso/boot/grub/grub.cfg
	echo '	boot' >> iso/boot/grub/grub.cfg
	echo '}' >> iso/boot/grub/grub.cfg
	
	grub-mkrescue --output=$@ iso
	rm -rf iso

run: mykernel.iso
	(killall VirtualBox && sleep 1) || true
	VirtualBox --startvm "My OS" &


.PHONY: clean
clean:
	rm -f $(objects) mykernel.bin mykernel.iso