# Nombre del ejecutable
TARGET = carrera

# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -lpthread

# Fuentes
SRCS = carrera.cpp

# Ejecutable sin visualización
all: $(TARGET)

# Ejecutable con visualización
visual: CXXFLAGS += -DVISUALIZACION
visual: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CXXFLAGS) -o $(TARGET)

# Limpieza de archivos
clean:
	rm -f $(TARGET)
