
OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS= -L/usr/local/lib 
CPPFLAGS= -I/usr/local/include

BIN1=bin/Disk
BIN2=bin/Ring
BIN3=bin/Slime

SRCS1= Disk/main.cpp Disk/shader.cpp
SRCS2= Ring/main.cpp Ring/shader.cpp
SRCS3= Slime/main.cpp Slime/shader.cpp

INCLUDES=

all: $(BIN1) $(BIN2) $(BIN3)


$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)

$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)

$(BIN3): $(SRCS3) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS3) -o $(BIN3) $(LDFLAGS) $(LIBS)


clean:
	rm -f *~ *.o $(BIN1)