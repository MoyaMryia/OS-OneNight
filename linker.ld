OUTPUT_ARCH( "riscv" )
ENTRY( _start )

SECTIONS
{
    . = 0x80000000;
    
    .text : {
        *(.text .text.*)
    }

    .data : {
        *(.text .text.*)
    }

    .bss : {
        *(.bss .bss.*)
    }

    . = ALIGN(16);
    stack_top = . + 0x1000;
    
}