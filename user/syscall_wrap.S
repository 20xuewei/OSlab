#include <asm/regdef.h>
#include <asm/cp0regdef.h>
#include <asm/asm.h>

/*** exercise 4.1 ***/
LEAF(msyscall)
    // TODO: you JUST need to execute a `syscall` instruction and return from msyscall
	move v0, a0
	syscall
	jr ra
	nop
END(msyscall)

LEAF(read_sector)
        sw      a0, 0xB3000010
        sw      a1, 0xB3000000
        li      t0, 0
        sb      t0, 0xB3000020
        lw      v0, 0xB3000030
        jr      ra
        nop
END(read_sector)

LEAF(write_sector)
        sw      a0, 0xB3000010
        sw      a1, 0xB3000000
        li      t0, 1
        sb      t0, 0xB3000020
        lw      v0, 0xB3000030
        jr      ra
        nop
END(write_sector)
