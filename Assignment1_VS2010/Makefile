TARGET  = Assignment1
SRCS	= 	Util/cmdLineParser \
		Image/bmp \
		Image/image \
		Image/image.todo \
		Image/jpeg \
		Image/lineSegments \
		Image/lineSegments.todo \
		main

CC   = g++
CFLAGS	+= -I.
LFLAGS	+= -LJPEG -lJPEG

OBJECTS	= ${addsuffix .o, ${SRCS}}
CLEAN	= *.o Image/*.o Image/*~ JPEG/*~ JPEG/*.a Util/*~ JPEG/*.o Util/*.o *~ *.bak .depend ${TARGET} *.dsp *.dsw *.bak

#############################################################
all: debug

debug: CFLAGS += -DUSE_UNIX -DDEBUG -g3
debug: ${TARGET}

release: CFLAGS += -O2 -DUSE_UNIX -DRELEASE -pipe -fomit-frame-pointer
release: ${TARGET}

${TARGET}: JPEG/libJPEG.a ${OBJECTS}
	${CC} -o $@ ${OBJECTS} ${LFLAGS}

clean:	
	/bin/rm -f ${CLEAN}

.cpp.o:
	${CC} ${CFLAGS} -o $@ -c $<

JPEG/libJPEG.a:
	${MAKE} -C JPEG

# DO NOT DELETE
