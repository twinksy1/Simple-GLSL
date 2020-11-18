OBJ=./Display/Display.o ./Shader/Shader.o ./Mesh/Mesh.o ./Texture/Texture.o ./Transform/Transform.o ./Camera/Camera.o ./Obj_Loader/Obj_Loader.o Main.o
EXE=app
HEADERS=./*/*.h
LIBS=-lSDL2 -lGL -lGLEW -lm
ARGS=-c
CC=g++

all: $(EXE)

%.o: %.cpp $(HEADERS)
	$(CC) $(ARGS) $< -o $@

$(EXE): $(OBJ)
	$(CC) $^ -o $@ $(LIBS)

clean:
	rm $(EXE) *.o ./*/*.o
