
OPENGLLIB= -framework OpenGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS= -L/usr/local/lib 
CPPFLAGS= -I/usr/local/include

BIN1=bin/Triangle
BIN2=bin/Chess

SRCS1= Triangle/main.cpp Triangle/shader.cpp
SRCS2= Chess/main.cpp Chess/shader.cpp

INCLUDES=

all: $(BIN1) $(BIN2) $(BIN3)


$(BIN1): $(SRCS1) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS1) -o $(BIN1) $(LDFLAGS) $(LIBS)

$(BIN2): $(SRCS2) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS2) -o $(BIN2) $(LDFLAGS) $(LIBS)



clean:
	rm -f *~ *.o $(BIN1)