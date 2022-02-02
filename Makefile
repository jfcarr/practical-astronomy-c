SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib
TEST_DIR = $(SRC_DIR)/test
FORMATTER = clang-format -i

default:
	@echo 'Targets:'
	@echo '  run'
	@echo '  build'
	@echo '  clean'
	@echo '  format'

run: build
	@echo '----------'
	@./pa_cli

build: pa_cli

pa_cli: $(SRC_DIR)/main.o $(LIB_DIR)/pa_datetime.o $(LIB_DIR)/pa_macros.o $(LIB_DIR)/pa_util.o $(TEST_DIR)/pa_datetime.o
	gcc -o pa_cli $(SRC_DIR)/main.o $(LIB_DIR)/pa_datetime.o $(LIB_DIR)/pa_macros.o $(LIB_DIR)/pa_util.o $(TEST_DIR)/pa_datetime.o -lm

src/main.o: $(SRC_DIR)/main.c $(LIB_DIR)/pa_datetime.h
	gcc -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(LIB_DIR)/pa_datetime.o: $(LIB_DIR)/pa_datetime.c $(LIB_DIR)/pa_datetime.h
	gcc -c $(LIB_DIR)/pa_datetime.c -o $(LIB_DIR)/pa_datetime.o

$(LIB_DIR)/pa_macros.o: $(LIB_DIR)/pa_macros.c $(LIB_DIR)/pa_macros.h
	gcc -c $(LIB_DIR)/pa_macros.c -o $(LIB_DIR)/pa_macros.o

$(LIB_DIR)/pa_util.o: $(LIB_DIR)/pa_util.c $(LIB_DIR)/pa_util.h
	gcc -c $(LIB_DIR)/pa_util.c -o $(LIB_DIR)/pa_util.o

$(TEST_DIR)/pa_datetime.o: $(TEST_DIR)/pa_datetime.c $(TEST_DIR)/pa_datetime.h $(LIB_DIR)/pa_datetime.h
	gcc -c $(TEST_DIR)/pa_datetime.c -o $(TEST_DIR)/pa_datetime.o

clean:
	-rm -f pa_cli
	-rm -f $(SRC_DIR)/*.o
	-rm -f $(SRC_DIR)/*.orig
	-rm -f $(LIB_DIR)/*.o
	-rm -f $(LIB_DIR)/*.orig
	-rm -f $(TEST_DIR)/*.o
	-rm -f $(TEST_DIR)/*.orig

format:
	$(FORMATTER) $(SRC_DIR)/main.c

# Library files
	$(FORMATTER) $(LIB_DIR)/pa_datetime.c $(LIB_DIR)/pa_datetime.h
	$(FORMATTER) $(LIB_DIR)/pa_macros.c $(LIB_DIR)/pa_macros.h
	$(FORMATTER) $(LIB_DIR)/pa_util.c $(LIB_DIR)/pa_util.h

# Test files
	$(FORMATTER) $(TEST_DIR)/pa_datetime.c $(TEST_DIR)/pa_datetime.h
