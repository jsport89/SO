arch ?= x86_64
kernel := build/kernel-$(arch).bin
img := build/os-so-$(arch).img
IMG_NAME := os-so-$(arch).img

linker_script := src/arch/$(arch)/linker.ld
grub_cfg := src/arch/$(arch)/grub.cfg
assembly_source_files := $(wildcard src/arch/$(arch)/*.asm)
assembly_object_files := $(patsubst src/arch/$(arch)/%.asm, \
	build/arch/$(arch)/%.o, $(assembly_source_files))

# Build src files and link'm
lib_driver_files_dir = arch/$(arch)/lib_objs
lib_driver_files := $(shell find src -name '*.c')
lib_driver_objs := $(patsubst %.c, %.o, $(lib_driver_files))
lib_make = ~/Desktop/CPE-454/SO/src

.PHONY: all clean run iso

all: $(kernel)

clean:
	-sudo umount /mnt/loops4dayz
	-sudo losetup -d /dev/loop0
	-sudo losetup -d /dev/loop1
	-cd $(lib_make) && sudo $(MAKE) clean
	@rm -r build

run: $(img)
	@qemu-system-x86_64 -s -drive format=raw,file=$(IMG_NAME) -serial stdio

img: $(img)

$(img): $(kernel) $(grub_cfg)
	@mkdir -p build/imgfiles/boot/grub
	@dd if=/dev/zero of=$(IMG_NAME) bs=512 count=32768
	@parted $(IMG_NAME) mklabel msdos
	@parted $(IMG_NAME) mkpart primary fat32 2048s 30720s
	@parted $(IMG_NAME) set 1 boot on
	@sudo losetup /dev/loop0 $(IMG_NAME)
	@sudo losetup /dev/loop1 $(IMG_NAME) -o 1048576
	@sudo mkdosfs -F32 -f 2 /dev/loop1
	@sudo mount /dev/loop1 /mnt/loops4dayz
	@sudo grub-install --root-directory=/mnt/loops4dayz --no-floppy --modules="normal part_msdos ext2 multiboot" /dev/loop0
	@cp $(kernel) build/imgfiles/boot/kernel.bin
	@cp $(grub_cfg) build/imgfiles/boot/grub
	@sudo cp -r build/imgfiles/* /mnt/loops4dayz
	@sudo umount /mnt/loops4dayz
	@sudo losetup -d /dev/loop0
	@sudo losetup -d /dev/loop1

$(kernel): build_src $(assembly_object_files) $(linker_script)
	@ld -n -T $(linker_script) -o $(kernel) $(assembly_object_files) $(lib_driver_objs)

build_src:
	@cd $(lib_make) && $(MAKE)

# compile assembly files
build/arch/$(arch)/%.o: src/arch/$(arch)/%.asm
	@mkdir -p $(shell dirname $@)
	@nasm -felf64 $< -o $@
