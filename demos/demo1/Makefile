TARGET = demo1
CXX = clang++

all: $(TARGET).bin
#	./$(TARGET).bin

run: $(TARGET).bin
	./$(TARGET).bin


#ALLFLAGS     = -Wall -Wstrict-aliasing -Wextra -g -pthread -I/opt/intel/composer_xe_2013_sp1.0.080/mkl/include/
ALLFLAGS     = -Wall -Wstrict-aliasing -Wextra -g -I ../generator -Wno-c++11-extensions
RELEASEFLAGS = -DNDEBUG -fPIC -Os -fstrict-aliasing -O3
DEBUGFLAGS   = -O0
# OPENMPFLAGS  = -fopenmp
#LIBLAPACK= -L/usr/lib/lapack/ -llapack
#LIBLAPACK= -L./lapack-3.4.2/ -llapack
#LIBLAPACK= -llapack
#LIBMRRR= -L../mr3smp-20130228/LIB -lmrrr
#LIBBLAS= -lblas
#LIBBLAS= -L/home/mrdaka/Documents/Master/Thesis/code/OpenBLAS -lopenblas
#LIBBLAS= -L/opt/intel/composer_xe_2013_sp1.0.080/mkl/lib/ia32/ -lmkl_intel -lmkl_core -lmkl_gnu_thread -fopenmp

#LIBS = -lrt $(LIBBLAS) $(LIBLAPACK) $(LIBMRRR) -lgfortran -lm -lgcc_s 

INCLUDES = $(wildcard *.h)
SOURCES = $(wildcard *.cpp ../generator/*.cpp)
OPTIMIZEDOBJECTS = $(SOURCES:.cpp=.o) 
ifeq ($(wildcard .depend), .depend)
include .depend
endif


$(TARGET).bin: $(OPTIMIZEDOBJECTS) Makefile
	$(CXX) $(ALLFLAGS) $(RELEASEFLAGS) $(OPTIMIZEDOBJECTS) ${LIBS} -o $@


%.o: %.cpp %.h Makefile
	$(CXX) $(ALLFLAGS) $(RELEASEFLAGS) -c $< -o $@



clean:
	rm -f *.o $(TARGET).bin 

depend:
	rm .depend
	$(CXX) $(ALLFLAGS) -MM $(SOURCES) >.tmp
	cat .tmp | sed "s/h$$/h Makefile\n\t$$\(CXX\) $$\(ALLFLAGS\) $$\(RELEASEFLAGS\) -c $$< -o $$\@/">> .depend
	rm .tmp

