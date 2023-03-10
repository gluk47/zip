all: list  # что запускать при вызове `make` без параметров

CXX_FLAGS = -Wall -Wextra -std=c++20
BUILD = clang++ -o $@ $^ $(CXX_FLAGS)
DEBUG_MODE = -fno-omit-frame-pointer -g
BUILD_DEFAULT_MODE = $(BUILD) $(DEBUG_MODE) -fsanitize=address

TASK_CPP = $(filter-out list.cc, $(wildcard *.cc) $(wildcard filters/*.cc))

list: $(TASK_CPP) list.cc
	clang++ -o $@ $^ -fsanitize=address $(DEBUG_MODE) $(CXX_FLAGS)

# Запускается каждый раз, потому что такого выходного файла не создаётся
# $(basename $<) — это $(basename multiplication.cpp) — это multiplication
tidy: $(TASK_CPP)
	cd ../../build && ../run_linter.sh $(basename $<)

run: test
	./test

#  $@: цель сборки
#  $<: первая зависимость сборки
#  $^: все зависимости сборки

%: %.cc
	$(BUILD_DEFAULT_MODE)
