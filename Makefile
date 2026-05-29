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
	@echo "✅ ¡Compilación exitosa!"
	@echo "🎮 Para ejecutar: make run"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/cmp/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/man/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/sys/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/util/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(LIBDIR)/picoPNG/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(LIBDIR)/tinyPTC/src/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJDIR) $(BINDIR)

run: all
	./$(TARGET)

debug: CXXFLAGS += -DDEBUG -g
debug: all
