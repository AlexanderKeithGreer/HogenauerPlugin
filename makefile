#Start with various definitions
CC = g++
CFLAGS = -std=c++11 -wall
RM = rm
BASE_FILES = cicBase.cpp cicRealisations.cpp cicBase.hpp cicRealisations.hpp
BASE_DOT_C_FILES = cicBase.cpp cicRealisations.cpp
DOT_O_FILES = cicBase.o cicRealisations.o cicRealisationInterface.o


##########################################################
# build an executable named test from our code
##########################################################
test: $(BASE_FILES) test.cpp
	g++ -std=c++11 $(BASE_DOT_C_FILES) test.cpp -o test



##########################################################
# build a form which python can interface with
##########################################################

# -c means that all that is produced is object files "do not link"
#  -fPIC means that we have Position Independant Code suitable for dynamic linking
dot_o: $(BASE_FILES) cicRealisationInterface.cpp
	g++ -std=c++11 -c -fPIC $(BASE_DOT_C_FILES) cicRealisationInterface.cpp

# -shared means that we have a shared object other objects can be linked to
# -Wl lets us pass objects to the linker
# -soname is a gnu linker option -- designate the library a shared lib, and
#		treat it as such when the dynamic linker runs the final executable
dot_so: $(DOT_O_FILES)
	g++ -shared -Wl,-soname,libhogenauer.so -o libhogenauer.so  $(DOT_O_FILES)

##########################################################
#Tidy up
##########################################################
clean:
	$(RM) *.o *.so
