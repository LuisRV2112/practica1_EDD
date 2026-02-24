# Makefile – Practica1EDD 2026 | Laboratorio EDD – USAC CUNOC

CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -I include -I include/TADs -I Modelo
TARGET   := bin/Practica1EDD
TEST_BIN := bin/test_pila

SRCS := src/main.cpp \
        src/Modelo/Baraja.cpp \
        src/Modelo/ConfigPartida.cpp \
        src/Modelo/Contendiente.cpp \
        src/Modelo/FichaEspecial.cpp \
        src/Modelo/FichaLibre.cpp \
        src/Modelo/FichaNumeral.cpp \
        src/Modelo/FichaPoderosa.cpp \
        src/Modelo/FichaVolteo.cpp \
        src/Modelo/Pantalla.cpp \
        src/Modelo/RuedaTurnos.cpp

TEST_SRCS := tests/test_pila.cpp \
             src/Modelo/Baraja.cpp \
             src/Modelo/ConfigPartida.cpp \
             src/Modelo/Contendiente.cpp \
             src/Modelo/FichaEspecial.cpp \
             src/Modelo/FichaLibre.cpp \
             src/Modelo/FichaNumeral.cpp \
             src/Modelo/FichaPoderosa.cpp \
             src/Modelo/FichaVolteo.cpp \
             src/Modelo/Pantalla.cpp \
             src/Modelo/RuedaTurnos.cpp

.PHONY: all clean run test dirs

all: dirs $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo ""
	@echo "  Compilado: $(TARGET)"
	@echo ""

test: dirs $(TEST_BIN)
	@echo ""
	@echo "  Ejecutando pruebas..."
	@echo ""
	./$(TEST_BIN)

$(TEST_BIN): $(TEST_SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

run: all
	./$(TARGET)

clean:
	rm -f bin/Practica1EDD bin/test_pila
	@echo "  Limpieza completa."

dirs:
	@mkdir -p bin build

help:
	@echo "  make       - Compila"
	@echo "  make run   - Compila y ejecuta"
	@echo "  make test  - Pruebas unitarias"
	@echo "  make clean - Elimina binarios"
