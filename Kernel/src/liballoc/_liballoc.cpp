#include <paging.h>
#include <physicalallocator.h>
#include <serial.h>
#include <string.h>
#include <stddef.h>

char test[50];

extern "C" {

	int liballoc_lock() {
		asm("cli");
		return 0;
	}

	int liballoc_unlock() {
		asm("sti");
		return 0;
	}

	void* liballoc_alloc(int pages) {
		void* addr = (void*)Memory::KernelAllocateVirtualPages(pages);
		for (int i = 0; i < pages; i++)
		{
			uint32_t phys = Memory::AllocatePhysicalMemoryBlock();
			Memory::MapVirtualPages(phys, (uint32_t)addr + i * PAGE_SIZE, 1);
		}
		return addr;
	}

	int liballoc_free(void* addr, size_t pages) {
		Memory::FreeVirtualPages((uint32_t)addr, pages);
		return 0;
	}
}