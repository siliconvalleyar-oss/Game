CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g -MMD -MP -I. -Isrc -Isrc/cmp -Isrc/man -Isrc/sys -Isrc/util -Ilib/picoPNG/src -Ilib/tinyPTC/src
LDFLAGS = -lncurses -lX11 -lXext -lpthread

SRCDIR = src
LIBDIR = lib
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/retroman

SRCS = $(wildcard $(SRCDIR)/*.cpp)
SRCS += $(wildcard $(SRCDIR)/cmp/*.cpp)
SRCS += $(wildcard $(SRCDIR)/man/*.cpp)
SRCS += $(wildcard $(SRCDIR)/sys/*.cpp)
SRCS += $(wildcard $(SRCDIR)/util/*.cpp)
SRCS += $(wildcard $(LIBDIR)/picoPNG/src/*.cpp)
SRCS += $(wildcard $(LIBDIR)/tinyPTC/src/*.c)

OBJS = $(addprefix $(OBJDIR)/, $(notdir $(SRCS:.cpp=.o)))
OBJS := $(OBJS:.c=.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all clean dirs

all: dirs $(TARGET)

dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

$(TARGET): $(OBJS)
	$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "✅ Compilación exitosa: $(TARGET)"

# Reglas para compilar
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/entity.o: $(SRCDIR)/cmp/entity.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/entitymanager.o: $(SRCDIR)/man/entitymanager.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/collision.o: $(SRCDIR)/sys/collision.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/physics.o: $(SRCDIR)/sys/physics.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/rendersystem.o: $(SRCDIR)/sys/rendersystem.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/picopng.o: $(LIBDIR)/picoPNG/src/picopng.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/convert.o: $(LIBDIR)/tinyPTC/src/convert.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/xdbe.o: $(LIBDIR)/tinyPTC/src/xdbe.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/xlib.o: $(LIBDIR)/tinyPTC/src/xlib.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/xshm.o: $(LIBDIR)/tinyPTC/src/xshm.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/xvshm.o: $(LIBDIR)/tinyPTC/src/xvshm.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: all
	./$(TARGET)

debug: CXXFLAGS += -DDEBUG -g
debug: all
