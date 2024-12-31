CC = gcc-14
OPTS = -O0 -flax-vector-conversions -DACCELERATE_NEW_LAPACK
REPORT = $()
TARGET = acc
LDFLAGS = -framework Accelerate
LIBS_MATH = -lm

RM = rm
SRC_DIR = src
INCLUDE_DIR=include
CFLAGS = -I${INCLUDE_DIR} -Wall -Wextra -std=c17 $(OPTS)

# Detecting the OS type.
OS := $(shell uname -s)
$(info Make is being run in ${MODE} mode on the ${OS} OS.)

CFLAGS_MKL = -I${MKLROOT}/include
LIBS_MKL = -L${MKLROOT}/lib -Wl,-rpath,${MKLROOT}/lib -lmkl_rt -lpthread $(LIBS) -ldl

$(shell mkdir -p obj/)

$(TARGET):obj/main.o obj/linalg.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) obj/main.o obj/reps.o obj/utils.o obj/rand.o obj/sampling.o obj/constants.o obj/printfuns.o obj/mt19937ar.o obj/logmetrics.o obj/checks.o obj/memory.o obj/qecc.o obj/decode.o obj/effective.o obj/benchmark.o obj/hybrid.o obj/linalg.o $(LIBS_MATH)

obj/main.o: $(SRC_DIR)/main.c Makefile
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.c -o obj/main.o $(LIBS_MATH)

obj/linalg.o: $(SRC_DIR)/linalg.c $(INCLUDE_DIR)/linalg.h Makefile
	$(CC) $(CFLAGS) $(CFLAGS_MKL) $(LIBS_MKL) -c $(SRC_DIR)/linalg.c -o obj/linalg.o $(LIBS_MATH)

clean:
	$(RM) acc obj/main.o obj/linalg.o
