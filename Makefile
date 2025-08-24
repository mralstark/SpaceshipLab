
CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -O2

INCLUDES = -I"C:/sfml/include"

LIBS = -L"C:/sfml/lib" -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32

DEFINES = -DSFML_STATIC

TARGET = spaceship.exe

SOURCES = main.cpp Game.cpp Spaceship.cpp Asteroid.cpp Nebula.cpp Vector2.cpp Explosion.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(DEFINES) $(INCLUDES) -c $< -o $@

clean:
	del /Q $(OBJECTS) $(TARGET)

run: $(TARGET)
	$(TARGET)

help:
	@echo "Доступные команды:"
	@echo "  make          - скомпилировать проект"
	@echo "  make clean    - удалить сгенерированные файлы"
	@echo "  make run      - запустить игру"
	@echo "  make help     - показать эту справку"

.PHONY: clean run help all
