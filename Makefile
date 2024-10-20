# Compilador y flags
CXX = g++
CXXFLAGS = -lpthread
TARGET_NO_VIS = carrera
TARGET_VIS = carrera_con_dibujo
SRC = carrera.cpp

# Regla para construir el programa sin visualización
$(TARGET_NO_VIS): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET_NO_VIS)

# Regla para construir el programa con visualización
$(TARGET_VIS): $(SRC)
	$(CXX) -DVISUALIZACION $(SRC) $(CXXFLAGS) -o $(TARGET_VIS)

# Regla por defecto
all: $(TARGET_NO_VIS) $(TARGET_VIS)

# Limpiar los archivos generados
clean:
	rm -f $(TARGET_NO_VIS) $(TARGET_VIS)
