TARGET  = libJPEG.a
SRCS	= 	ckconfig  \
		jcapimin \
		jcapistd \
		jccoefct \
		jccolor \
		jcdctmgr \
		jchuff \
		jcinit \
		jcmainct \
		jcmarker \
		jcmaster \
		jcomapi \
		jcparam \
		jcphuff \
		jcprepct \
		jcsample \
		jctrans \
		jdapimin \
		jdapistd \
		jdatadst \
		jdatasrc \
		jdcoefct \
		jdcolor \
		jddctmgr \
		jdhuff \
		jdinput \
		jdmainct \
		jdmarker \
		jdmaster \
		jdmerge \
		jdphuff \
		jdpostct \
		jdsample \
		jdtrans \
		jerror \
		jfdctflt \
		jfdctfst \
		jfdctint \
		jidctflt \
		jidctfst \
		jidctint \
		jidctred \
		jmemmgr \
		jmemnobs \
		jquant1 \
		jquant2 \
		jutils 


CC   = g++
CFLAGS		+=
LFLAGS		+=

OBJECTS		= ${addsuffix .o, ${SRCS}}
CLEAN		= *.o ${TARGET}

#############################################################
all: debug

debug: CFLAGS += -DDEBUG -g3
debug: ${TARGET}

release: CFLAGS += -O2 -DRELEASE -pipe -fomit-frame-pointer
release: ${TARGET}

${TARGET}: depend ${OBJECTS} 
	ar r ${TARGET} ${OBJECTS}

clean:	
	/bin/rm -f ${CLEAN}

.cpp.o:
	${CC} ${CFLAGS} -c $<

depend: 
	makedepend -- ${CFLAGS} -- ${addsuffix .cpp, ${SRCS}}
# DO NOT DELETE

ckconfig.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
ckconfig.o: /usr/include/stdlib.h /usr/include/features.h
ckconfig.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
ckconfig.o: /usr/include/stdio.h /usr/include/bits/types.h
ckconfig.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
ckconfig.o: /usr/include/libio.h /usr/include/_G_config.h
ckconfig.o: /usr/include/wchar.h /usr/include/bits/wchar.h
ckconfig.o: /usr/include/gconv.h
ckconfig.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
ckconfig.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
ckconfig.o: /usr/include/string.h
jcapimin.o: jinclude.h jconfig.h
jcapimin.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcapimin.o: /usr/include/stdlib.h /usr/include/features.h
jcapimin.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcapimin.o: /usr/include/stdio.h /usr/include/bits/types.h
jcapimin.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcapimin.o: /usr/include/libio.h /usr/include/_G_config.h
jcapimin.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jcapimin.o: /usr/include/gconv.h
jcapimin.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcapimin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcapimin.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcapistd.o: jinclude.h jconfig.h
jcapistd.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcapistd.o: /usr/include/stdlib.h /usr/include/features.h
jcapistd.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcapistd.o: /usr/include/stdio.h /usr/include/bits/types.h
jcapistd.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcapistd.o: /usr/include/libio.h /usr/include/_G_config.h
jcapistd.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jcapistd.o: /usr/include/gconv.h
jcapistd.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcapistd.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcapistd.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jccoefct.o: jinclude.h jconfig.h
jccoefct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jccoefct.o: /usr/include/stdlib.h /usr/include/features.h
jccoefct.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jccoefct.o: /usr/include/stdio.h /usr/include/bits/types.h
jccoefct.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jccoefct.o: /usr/include/libio.h /usr/include/_G_config.h
jccoefct.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jccoefct.o: /usr/include/gconv.h
jccoefct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jccoefct.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jccoefct.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jccolor.o: jinclude.h jconfig.h
jccolor.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jccolor.o: /usr/include/stdlib.h /usr/include/features.h
jccolor.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jccolor.o: /usr/include/stdio.h /usr/include/bits/types.h
jccolor.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jccolor.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jccolor.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jccolor.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jccolor.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jccolor.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcdctmgr.o: jinclude.h jconfig.h
jcdctmgr.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcdctmgr.o: /usr/include/stdlib.h /usr/include/features.h
jcdctmgr.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcdctmgr.o: /usr/include/stdio.h /usr/include/bits/types.h
jcdctmgr.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcdctmgr.o: /usr/include/libio.h /usr/include/_G_config.h
jcdctmgr.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jcdctmgr.o: /usr/include/gconv.h
jcdctmgr.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcdctmgr.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcdctmgr.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcdctmgr.o: jdct.h
jchuff.o: jinclude.h jconfig.h
jchuff.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jchuff.o: /usr/include/stdlib.h /usr/include/features.h
jchuff.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jchuff.o: /usr/include/stdio.h /usr/include/bits/types.h
jchuff.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jchuff.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jchuff.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jchuff.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jchuff.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jchuff.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jchuff.o: jchuff.h
jcinit.o: jinclude.h jconfig.h
jcinit.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcinit.o: /usr/include/stdlib.h /usr/include/features.h
jcinit.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcinit.o: /usr/include/stdio.h /usr/include/bits/types.h
jcinit.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcinit.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jcinit.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jcinit.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcinit.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcinit.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcmainct.o: jinclude.h jconfig.h
jcmainct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcmainct.o: /usr/include/stdlib.h /usr/include/features.h
jcmainct.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcmainct.o: /usr/include/stdio.h /usr/include/bits/types.h
jcmainct.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcmainct.o: /usr/include/libio.h /usr/include/_G_config.h
jcmainct.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jcmainct.o: /usr/include/gconv.h
jcmainct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcmainct.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcmainct.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcmarker.o: jinclude.h jconfig.h
jcmarker.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcmarker.o: /usr/include/stdlib.h /usr/include/features.h
jcmarker.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcmarker.o: /usr/include/stdio.h /usr/include/bits/types.h
jcmarker.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcmarker.o: /usr/include/libio.h /usr/include/_G_config.h
jcmarker.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jcmarker.o: /usr/include/gconv.h
jcmarker.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcmarker.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcmarker.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcmaster.o: jinclude.h jconfig.h
jcmaster.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcmaster.o: /usr/include/stdlib.h /usr/include/features.h
jcmaster.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcmaster.o: /usr/include/stdio.h /usr/include/bits/types.h
jcmaster.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcmaster.o: /usr/include/libio.h /usr/include/_G_config.h
jcmaster.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jcmaster.o: /usr/include/gconv.h
jcmaster.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcmaster.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcmaster.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcomapi.o: jinclude.h jconfig.h
jcomapi.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcomapi.o: /usr/include/stdlib.h /usr/include/features.h
jcomapi.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcomapi.o: /usr/include/stdio.h /usr/include/bits/types.h
jcomapi.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcomapi.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jcomapi.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jcomapi.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcomapi.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcomapi.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcparam.o: jinclude.h jconfig.h
jcparam.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcparam.o: /usr/include/stdlib.h /usr/include/features.h
jcparam.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcparam.o: /usr/include/stdio.h /usr/include/bits/types.h
jcparam.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcparam.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jcparam.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jcparam.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcparam.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcparam.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcphuff.o: jinclude.h jconfig.h
jcphuff.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcphuff.o: /usr/include/stdlib.h /usr/include/features.h
jcphuff.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcphuff.o: /usr/include/stdio.h /usr/include/bits/types.h
jcphuff.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcphuff.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jcphuff.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jcphuff.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcphuff.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcphuff.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcphuff.o: jchuff.h
jcprepct.o: jinclude.h jconfig.h
jcprepct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcprepct.o: /usr/include/stdlib.h /usr/include/features.h
jcprepct.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcprepct.o: /usr/include/stdio.h /usr/include/bits/types.h
jcprepct.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcprepct.o: /usr/include/libio.h /usr/include/_G_config.h
jcprepct.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jcprepct.o: /usr/include/gconv.h
jcprepct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcprepct.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcprepct.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jcsample.o: jinclude.h jconfig.h
jcsample.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jcsample.o: /usr/include/stdlib.h /usr/include/features.h
jcsample.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jcsample.o: /usr/include/stdio.h /usr/include/bits/types.h
jcsample.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jcsample.o: /usr/include/libio.h /usr/include/_G_config.h
jcsample.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jcsample.o: /usr/include/gconv.h
jcsample.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jcsample.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jcsample.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jctrans.o: jinclude.h jconfig.h
jctrans.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jctrans.o: /usr/include/stdlib.h /usr/include/features.h
jctrans.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jctrans.o: /usr/include/stdio.h /usr/include/bits/types.h
jctrans.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jctrans.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jctrans.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jctrans.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jctrans.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jctrans.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdapimin.o: jinclude.h jconfig.h
jdapimin.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdapimin.o: /usr/include/stdlib.h /usr/include/features.h
jdapimin.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdapimin.o: /usr/include/stdio.h /usr/include/bits/types.h
jdapimin.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdapimin.o: /usr/include/libio.h /usr/include/_G_config.h
jdapimin.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdapimin.o: /usr/include/gconv.h
jdapimin.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdapimin.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdapimin.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdapistd.o: jinclude.h jconfig.h
jdapistd.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdapistd.o: /usr/include/stdlib.h /usr/include/features.h
jdapistd.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdapistd.o: /usr/include/stdio.h /usr/include/bits/types.h
jdapistd.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdapistd.o: /usr/include/libio.h /usr/include/_G_config.h
jdapistd.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdapistd.o: /usr/include/gconv.h
jdapistd.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdapistd.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdapistd.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdatadst.o: jinclude.h jconfig.h
jdatadst.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdatadst.o: /usr/include/stdlib.h /usr/include/features.h
jdatadst.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdatadst.o: /usr/include/stdio.h /usr/include/bits/types.h
jdatadst.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdatadst.o: /usr/include/libio.h /usr/include/_G_config.h
jdatadst.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdatadst.o: /usr/include/gconv.h
jdatadst.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdatadst.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdatadst.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdatasrc.o: jinclude.h jconfig.h
jdatasrc.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdatasrc.o: /usr/include/stdlib.h /usr/include/features.h
jdatasrc.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdatasrc.o: /usr/include/stdio.h /usr/include/bits/types.h
jdatasrc.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdatasrc.o: /usr/include/libio.h /usr/include/_G_config.h
jdatasrc.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdatasrc.o: /usr/include/gconv.h
jdatasrc.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdatasrc.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdatasrc.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdcoefct.o: jinclude.h jconfig.h
jdcoefct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdcoefct.o: /usr/include/stdlib.h /usr/include/features.h
jdcoefct.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdcoefct.o: /usr/include/stdio.h /usr/include/bits/types.h
jdcoefct.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdcoefct.o: /usr/include/libio.h /usr/include/_G_config.h
jdcoefct.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdcoefct.o: /usr/include/gconv.h
jdcoefct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdcoefct.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdcoefct.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdcolor.o: jinclude.h jconfig.h
jdcolor.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdcolor.o: /usr/include/stdlib.h /usr/include/features.h
jdcolor.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdcolor.o: /usr/include/stdio.h /usr/include/bits/types.h
jdcolor.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdcolor.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jdcolor.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jdcolor.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdcolor.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdcolor.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jddctmgr.o: jinclude.h jconfig.h
jddctmgr.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jddctmgr.o: /usr/include/stdlib.h /usr/include/features.h
jddctmgr.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jddctmgr.o: /usr/include/stdio.h /usr/include/bits/types.h
jddctmgr.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jddctmgr.o: /usr/include/libio.h /usr/include/_G_config.h
jddctmgr.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jddctmgr.o: /usr/include/gconv.h
jddctmgr.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jddctmgr.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jddctmgr.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jddctmgr.o: jdct.h
jdhuff.o: jinclude.h jconfig.h
jdhuff.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdhuff.o: /usr/include/stdlib.h /usr/include/features.h
jdhuff.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdhuff.o: /usr/include/stdio.h /usr/include/bits/types.h
jdhuff.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdhuff.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jdhuff.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jdhuff.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdhuff.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdhuff.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdhuff.o: jdhuff.h
jdinput.o: jinclude.h jconfig.h
jdinput.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdinput.o: /usr/include/stdlib.h /usr/include/features.h
jdinput.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdinput.o: /usr/include/stdio.h /usr/include/bits/types.h
jdinput.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdinput.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jdinput.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jdinput.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdinput.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdinput.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdmainct.o: jinclude.h jconfig.h
jdmainct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdmainct.o: /usr/include/stdlib.h /usr/include/features.h
jdmainct.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdmainct.o: /usr/include/stdio.h /usr/include/bits/types.h
jdmainct.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdmainct.o: /usr/include/libio.h /usr/include/_G_config.h
jdmainct.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdmainct.o: /usr/include/gconv.h
jdmainct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdmainct.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdmainct.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdmarker.o: jinclude.h jconfig.h
jdmarker.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdmarker.o: /usr/include/stdlib.h /usr/include/features.h
jdmarker.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdmarker.o: /usr/include/stdio.h /usr/include/bits/types.h
jdmarker.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdmarker.o: /usr/include/libio.h /usr/include/_G_config.h
jdmarker.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdmarker.o: /usr/include/gconv.h
jdmarker.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdmarker.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdmarker.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdmaster.o: jinclude.h jconfig.h
jdmaster.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdmaster.o: /usr/include/stdlib.h /usr/include/features.h
jdmaster.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdmaster.o: /usr/include/stdio.h /usr/include/bits/types.h
jdmaster.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdmaster.o: /usr/include/libio.h /usr/include/_G_config.h
jdmaster.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdmaster.o: /usr/include/gconv.h
jdmaster.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdmaster.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdmaster.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdmerge.o: jinclude.h jconfig.h
jdmerge.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdmerge.o: /usr/include/stdlib.h /usr/include/features.h
jdmerge.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdmerge.o: /usr/include/stdio.h /usr/include/bits/types.h
jdmerge.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdmerge.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jdmerge.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jdmerge.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdmerge.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdmerge.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdphuff.o: jinclude.h jconfig.h
jdphuff.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdphuff.o: /usr/include/stdlib.h /usr/include/features.h
jdphuff.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdphuff.o: /usr/include/stdio.h /usr/include/bits/types.h
jdphuff.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdphuff.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jdphuff.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jdphuff.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdphuff.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdphuff.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdphuff.o: jdhuff.h
jdpostct.o: jinclude.h jconfig.h
jdpostct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdpostct.o: /usr/include/stdlib.h /usr/include/features.h
jdpostct.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdpostct.o: /usr/include/stdio.h /usr/include/bits/types.h
jdpostct.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdpostct.o: /usr/include/libio.h /usr/include/_G_config.h
jdpostct.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdpostct.o: /usr/include/gconv.h
jdpostct.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdpostct.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdpostct.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdsample.o: jinclude.h jconfig.h
jdsample.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdsample.o: /usr/include/stdlib.h /usr/include/features.h
jdsample.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdsample.o: /usr/include/stdio.h /usr/include/bits/types.h
jdsample.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdsample.o: /usr/include/libio.h /usr/include/_G_config.h
jdsample.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jdsample.o: /usr/include/gconv.h
jdsample.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdsample.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdsample.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jdtrans.o: jinclude.h jconfig.h
jdtrans.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jdtrans.o: /usr/include/stdlib.h /usr/include/features.h
jdtrans.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jdtrans.o: /usr/include/stdio.h /usr/include/bits/types.h
jdtrans.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jdtrans.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jdtrans.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jdtrans.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jdtrans.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jdtrans.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jerror.o: jinclude.h jconfig.h
jerror.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jerror.o: /usr/include/stdlib.h /usr/include/features.h
jerror.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jerror.o: /usr/include/stdio.h /usr/include/bits/types.h
jerror.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jerror.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jerror.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jerror.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jerror.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jerror.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jerror.o: jversion.h
jfdctflt.o: jinclude.h jconfig.h
jfdctflt.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jfdctflt.o: /usr/include/stdlib.h /usr/include/features.h
jfdctflt.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jfdctflt.o: /usr/include/stdio.h /usr/include/bits/types.h
jfdctflt.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jfdctflt.o: /usr/include/libio.h /usr/include/_G_config.h
jfdctflt.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jfdctflt.o: /usr/include/gconv.h
jfdctflt.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jfdctflt.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jfdctflt.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jfdctflt.o: jdct.h
jfdctfst.o: jinclude.h jconfig.h
jfdctfst.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jfdctfst.o: /usr/include/stdlib.h /usr/include/features.h
jfdctfst.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jfdctfst.o: /usr/include/stdio.h /usr/include/bits/types.h
jfdctfst.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jfdctfst.o: /usr/include/libio.h /usr/include/_G_config.h
jfdctfst.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jfdctfst.o: /usr/include/gconv.h
jfdctfst.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jfdctfst.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jfdctfst.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jfdctfst.o: jdct.h
jfdctint.o: jinclude.h jconfig.h
jfdctint.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jfdctint.o: /usr/include/stdlib.h /usr/include/features.h
jfdctint.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jfdctint.o: /usr/include/stdio.h /usr/include/bits/types.h
jfdctint.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jfdctint.o: /usr/include/libio.h /usr/include/_G_config.h
jfdctint.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jfdctint.o: /usr/include/gconv.h
jfdctint.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jfdctint.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jfdctint.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jfdctint.o: jdct.h
jidctflt.o: jinclude.h jconfig.h
jidctflt.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jidctflt.o: /usr/include/stdlib.h /usr/include/features.h
jidctflt.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jidctflt.o: /usr/include/stdio.h /usr/include/bits/types.h
jidctflt.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jidctflt.o: /usr/include/libio.h /usr/include/_G_config.h
jidctflt.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jidctflt.o: /usr/include/gconv.h
jidctflt.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jidctflt.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jidctflt.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jidctflt.o: jdct.h
jidctfst.o: jinclude.h jconfig.h
jidctfst.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jidctfst.o: /usr/include/stdlib.h /usr/include/features.h
jidctfst.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jidctfst.o: /usr/include/stdio.h /usr/include/bits/types.h
jidctfst.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jidctfst.o: /usr/include/libio.h /usr/include/_G_config.h
jidctfst.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jidctfst.o: /usr/include/gconv.h
jidctfst.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jidctfst.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jidctfst.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jidctfst.o: jdct.h
jidctint.o: jinclude.h jconfig.h
jidctint.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jidctint.o: /usr/include/stdlib.h /usr/include/features.h
jidctint.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jidctint.o: /usr/include/stdio.h /usr/include/bits/types.h
jidctint.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jidctint.o: /usr/include/libio.h /usr/include/_G_config.h
jidctint.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jidctint.o: /usr/include/gconv.h
jidctint.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jidctint.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jidctint.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jidctint.o: jdct.h
jidctred.o: jinclude.h jconfig.h
jidctred.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jidctred.o: /usr/include/stdlib.h /usr/include/features.h
jidctred.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jidctred.o: /usr/include/stdio.h /usr/include/bits/types.h
jidctred.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jidctred.o: /usr/include/libio.h /usr/include/_G_config.h
jidctred.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jidctred.o: /usr/include/gconv.h
jidctred.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jidctred.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jidctred.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jidctred.o: jdct.h
jmemmgr.o: jinclude.h jconfig.h
jmemmgr.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jmemmgr.o: /usr/include/stdlib.h /usr/include/features.h
jmemmgr.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jmemmgr.o: /usr/include/stdio.h /usr/include/bits/types.h
jmemmgr.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jmemmgr.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jmemmgr.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jmemmgr.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jmemmgr.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jmemmgr.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jmemmgr.o: jmemsys.h
jmemnobs.o: jinclude.h jconfig.h
jmemnobs.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jmemnobs.o: /usr/include/stdlib.h /usr/include/features.h
jmemnobs.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jmemnobs.o: /usr/include/stdio.h /usr/include/bits/types.h
jmemnobs.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jmemnobs.o: /usr/include/libio.h /usr/include/_G_config.h
jmemnobs.o: /usr/include/wchar.h /usr/include/bits/wchar.h
jmemnobs.o: /usr/include/gconv.h
jmemnobs.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jmemnobs.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jmemnobs.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jmemnobs.o: jmemsys.h
jquant1.o: jinclude.h jconfig.h
jquant1.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jquant1.o: /usr/include/stdlib.h /usr/include/features.h
jquant1.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jquant1.o: /usr/include/stdio.h /usr/include/bits/types.h
jquant1.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jquant1.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jquant1.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jquant1.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jquant1.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jquant1.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jquant2.o: jinclude.h jconfig.h
jquant2.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jquant2.o: /usr/include/stdlib.h /usr/include/features.h
jquant2.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jquant2.o: /usr/include/stdio.h /usr/include/bits/types.h
jquant2.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jquant2.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jquant2.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jquant2.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jquant2.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jquant2.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
jutils.o: jinclude.h jconfig.h
jutils.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stddef.h
jutils.o: /usr/include/stdlib.h /usr/include/features.h
jutils.o: /usr/include/sys/cdefs.h /usr/include/gnu/stubs.h
jutils.o: /usr/include/stdio.h /usr/include/bits/types.h
jutils.o: /usr/include/bits/wordsize.h /usr/include/bits/typesizes.h
jutils.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
jutils.o: /usr/include/bits/wchar.h /usr/include/gconv.h
jutils.o: /usr/lib/gcc/i386-redhat-linux/3.4.4/include/stdarg.h
jutils.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
jutils.o: /usr/include/string.h jpeglib.h jmorecfg.h jpegint.h jerror.h
