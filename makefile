CC      = gcc
CFLAGS  = -Wall -Wextra -O2 -I./include
LDFLAGS = -lm -Wl,-rpath,'\$$ORIGIN'
SRCS_LIB = src/centroid.c src/dbscan.c src/kmeans.c src/silhouette.c src/pca.c
SRCS_MAIN = src/main.c
LIB      = build/clustering.so
APP      = build/imperative_clustering

.PHONY: all clean

all: $(APP)

$(LIB): $(SRCS_LIB) include/clustering.h
	@mkdir -p build
	$(CC) -shared -fPIC $(CFLAGS) -o $@ $(SRCS_LIB) -lm

$(APP): $(SRCS_MAIN) $(LIB) include/clustering.h
	@mkdir -p build
	$(CC) $(CFLAGS) -o $@ $(SRCS_MAIN) $(LIB) $(LDFLAGS)

clean:
	rm -rf build