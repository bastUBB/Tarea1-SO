# Nombre del ejecutable
TARGET = carrera
TARGET_VISUAL = carrera_visual  # Nombre para la versión con visualización

# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -lpthread

# Fuentes
SRCS = carrera.cpp

# Ejecutable sin visualización y con visualización
all: $(TARGET_VISUAL) $(TARGET) 

# Ejecutable con visualización
visual: CXXFLAGS += -DVISUALIZACION
visual: $(TARGET_VISUAL)

# Regla para compilar el ejecutable sin visualización
$(TARGET): $(SRCS)
	$(CXX) $(SRCS) $(CXXFLAGS) -o $(TARGET)

# Regla para compilar el ejecutable con visualización
$(TARGET_VISUAL): $(SRCS)
	$(CXX) $(SRCS) $(CXXFLAGS) -o $(TARGET_VISUAL)

# Limpieza de archivos
clean:
	rm -f $(TARGET_VISUAL) $(TARGET) 

