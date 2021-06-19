/*
 * operations on IDE disk.
 */

#include "fs.h"
#include "lib.h"
#include <mmu.h>
extern int read_sector(int diskno, int offset);
extern int write_sector(int diskno, int offset);
// Overview:
// 	read data from IDE disk. First issue a read request through
// 	disk register and then copy data from disk buffer
// 	(512 bytes, a sector) to destination array.
//
// Parameters:
//	diskno: disk number.
// 	secno: start sector number.
// 	dst: destination for data read from IDE disk.
// 	nsecs: the number of sectors to read.
//
// Post-Condition:
// 	If error occurred during read the IDE disk, panic. 
// 	
// Hint: use syscalls to access device registers and buffers
void
ide_read(u_int diskno, u_int secno, void *dst, u_int nsecs)
{
	// 0x200: the size of a sector: 512 bytes.
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	int curoffset, r;
	while (offset_begin + offset < offset_end) {
            // Your code here
            // error occurred, then panic.
		curoffset = offset_begin + offset;
		//if (read_sector(diskno, curoffset) == 0) user_panic("ide.c: read sector fault!\n");
		//if (syscall_read_dev(dst, 0x13004000, 512) != 0) user_panic("ide.c: read dev fault!\n");
				
		if( syscall_write_dev(&diskno, 0x13000010, 4) < 0) {
			user_panic("Error in ide.c/ide_read 1\n");
		}
		
		if( syscall_write_dev(&curoffset, 0x13000000, 4) < 0) {
			user_panic("Error in ide.c/ide_read 2\n");
		}
		
		char tmp = 0;
		int temp = 0;
		if( syscall_write_dev(&temp, 0x13000020, 4) < 0) {
			user_panic("Error in ide.c/ide_read 3\n");
		}
		
		int val;
		if( syscall_read_dev(&val, 0x13000030, 4) < 0){
			user_panic("Error in ide.c/ide_read 4\n");
		}
		if( val == 0 ) {
			user_panic("Error in ide.c/ide_read 4 val = 0\n");
		}
		
		if( syscall_read_dev(dst, 0x13004000, 512) < 0){
			user_panic("Error in ide.c/ide_read 5\n");
		}
		
		offset += 512;
		dst += 512;
	}
}


// Overview:
// 	write data to IDE disk.
//
// Parameters:
//	diskno: disk number.
//	secno: start sector number.
// 	src: the source data to write into IDE disk.
//	nsecs: the number of sectors to write.
//
// Post-Condition:
//	If error occurred during read the IDE disk, panic.
//	
// Hint: use syscalls to access device registers and buffers
void
ide_write(u_int diskno, u_int secno, void *src, u_int nsecs)
{ 
	int offset_begin = secno * 0x200;
	int offset_end = offset_begin + nsecs * 0x200;
	int offset = 0;
	int curoffset, r;

	// DO NOT DELETE WRITEF !!!
	writef("diskno: %d\n", diskno);
	while (offset_begin < offset_end) {
            	
		if(syscall_write_dev(src, 0x13004000, 512) < 0) {
			user_panic("Error in ide.c/ide_write 1\n");
		}
		
		if(syscall_write_dev(&diskno, 0x13000010, 4) < 0) {
			user_panic("Error in ide.c/ide_write 2\n");
		}
		
		if(syscall_write_dev(&offset_begin, 0x13000000, 4) < 0) {
			user_panic("Error in ide.c/ide_write 3\n");
		}
		char tmp = 1;
		int temp = 1;
		if(syscall_write_dev(&temp, 0x13000020, 4) < 0) {
			user_panic("Error in ide.c/ide_write 4\n");
		}
		
		int val;
		if( syscall_read_dev(&val, 0x13000030, 4) < 0 ){
			user_panic("Error in ide.c/ide_write 5\n");
		}
		if(val == 0) {
			user_panic("Error in ide.c/ide_write 5 val = 0\n");
		}
		
		//if (syscall_write_dev(src, 0x13004000, 512) != 0) user_panic("ide.c: write dev fault!\n");
		//if (write_sector(diskno, offset_begin) == 0) user_panic("ide.c: write sector fault!\n");	
		offset_begin += 512;
		src += 512;
	}

}

