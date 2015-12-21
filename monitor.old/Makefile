AS = ../as-042012/as
M4 = m4
TEMPFILE = __preproc
ASFLAGS =
#ASFLAGS2 = -a 18000h -f hex
ASFLAGS2 = -a 8000h -f bin

main.hex : $(TEMPFILE)
		$(AS) $(ASFLAGS2) $(TEMPFILE) -o kernel.hex
		@rm $(TEMPFILE)

__preproc : main.asm kern_defs.asm kern_shell.asm kern_util.asm kern_rs232.asm kern_rtc.asm
		$(M4) main.asm > $(TEMPFILE)

clean:
		rm *.hex



