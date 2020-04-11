project('Lemon Kernel')

kernel_include_dirs = [
    include_directories('include'),
    include_directories('include/arch/x86_64'),
]

add_languages('c', 'cpp')

nasm = find_program('nasm')
asmg = generator(nasm,
    output : '@BASENAME@.asm.o',
    arguments : [
        '-f', 'elf64',
        '-g', '-F', 'dwarf', '-w+gnu-elf-extensions',
        '@INPUT@',
        '-o', '@OUTPUT@'])

kernel_cpp_args = ['-Wno-write-strings', '-Wno-pointer-arith',
    '-DLemon64',
    '-ffreestanding', '-nostdlib',
    '-mcmodel=large', '-mno-red-zone', '-fno-pic',
    '-mno-mmx', '-mno-sse', '-mno-sse2',
    '-z', 'max-page-size=0x1000',
    '-fno-stack-protector', '-fno-exceptions', '-fno-rtti']

add_project_arguments(kernel_cpp_args, language : ['c', 'cpp'])

cpp_files = [
    'src/kernel.cpp',
    'src/characterbuffer.cpp',
    'src/devicemanager.cpp',
    'src/gpt.cpp',
    'src/gui.cpp',
    'src/lemon.cpp',
    'src/logging.cpp',
    'src/math.cpp',
    'src/panic.cpp',
    'src/runtime.cpp',
    'src/string.cpp',
    'src/video.cpp',
    'src/videoconsole.cpp',

    'src/fs/fat32.cpp',
    'src/fs/initrd.cpp',
    'src/fs/filesystem.cpp',
    'src/fs/fsvolume.cpp',

    'src/liballoc/_liballoc.cpp',
    'src/liballoc/liballoc.c',
    
    'src/net/8254x.cpp',

    'src/storage/ahci.cpp',
    'src/storage/ahciport.cpp',
    'src/storage/ata.cpp',
    'src/storage/atadrive.cpp',
    'src/storage/diskdevice.cpp',
    'src/storage/nvme.cpp',
    'src/storage/partitiondevice.cpp',
    
    'src/tty/pty.cpp',
    
    'src/usb/xhci.cpp',
]

cpp_files_x86_64 = [
    'src/arch/x86_64/acpi.cpp',
    'src/arch/x86_64/hal.cpp',
    'src/arch/x86_64/idt.cpp',
    'src/arch/x86_64/keyboard.cpp',
    'src/arch/x86_64/lai.cpp',
    'src/arch/x86_64/mouse.cpp',
    'src/arch/x86_64/paging.cpp',
    'src/arch/x86_64/pci.cpp',
    'src/arch/x86_64/physicalallocator.cpp',
    'src/arch/x86_64/scheduler.cpp',
    'src/arch/x86_64/serial.cpp',
    'src/arch/x86_64/sse2.cpp',
    'src/arch/x86_64/ssp.cpp',
    'src/arch/x86_64/syscalls.cpp',
    'src/arch/x86_64/system.cpp',
    'src/arch/x86_64/timer.cpp',
]

asm_files_x86_64 = [
    'src/arch/x86_64/entry.asm',
    'src/arch/x86_64/idt.asm',
    'src/arch/x86_64/scheduler.asm',
    'src/arch/x86_64/sse2.asm',
    'src/arch/x86_64/tss.asm',
]

kernel_link_args = [
    '-m64',
    '-T', meson.current_source_dir() + '/linkscript-x86_64.ld'
]

kernel_link_args += kernel_cpp_args

executable('kernel.sys', [asmg.process(asm_files_x86_64), cpp_files, cpp_files_x86_64], objects : 'initrd.o', include_directories : kernel_include_dirs, cpp_args : kernel_cpp_args, link_args: kernel_link_args, link_depends: 'linkscript-x86_64.ld')