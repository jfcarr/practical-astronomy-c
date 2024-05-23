SRC_DIR = src
LIB_DIR = $(SRC_DIR)/lib
TEST_DIR = $(SRC_DIR)/test
FORMATTER = clang-format -i
LINTER = cppcheck

default:
	@echo 'Targets:'
	@echo '  run       Run the compiled binary'
	@echo '  build     Build the library and binary'
	@echo '  bin       Build the binary'
	@echo '  lib       Build the library'
	@echo '  clean     Remove all build artifacts (object files, library archives, and binaries)'
	@echo '  format    Beautify source code'
	@echo '  check     Run linter'

run: build
	@echo '----------'
	@./pa_cli

build: lib bin

bin: lib $(SRC_DIR)/main.o $(TEST_DIR)/pa_datetime.o $(TEST_DIR)/pa_coordinates.o $(TEST_DIR)/pa_sun.o $(TEST_DIR)/pa_planets.o $(TEST_DIR)/pa_comet.o $(TEST_DIR)/pa_binary.o
	gcc -L. -o pa_cli src/main.o src/test/*.o -lpa_lib -lm

lib: $(LIB_DIR)/pa_datetime.o $(LIB_DIR)/pa_coordinates.o $(LIB_DIR)/pa_sun.o $(LIB_DIR)/pa_planets.o $(LIB_DIR)/pa_planets_data.o $(LIB_DIR)/pa_comet.o $(LIB_DIR)/pa_comet_data.o $(LIB_DIR)/pa_binary.o $(LIB_DIR)/pa_binary_data.o $(LIB_DIR)/pa_macros.o $(LIB_DIR)/pa_util.o
	ar -r libpa_lib.a src/lib/*.o

src/main.o: $(SRC_DIR)/main.c $(LIB_DIR)/pa_datetime.h
	gcc -c $(SRC_DIR)/main.c -o $(SRC_DIR)/main.o

$(LIB_DIR)/pa_datetime.o: $(LIB_DIR)/pa_datetime.c $(LIB_DIR)/pa_datetime.h
	gcc -c $(LIB_DIR)/pa_datetime.c -o $(LIB_DIR)/pa_datetime.o

$(LIB_DIR)/pa_coordinates.o: $(LIB_DIR)/pa_coordinates.c $(LIB_DIR)/pa_coordinates.h
	gcc -c $(LIB_DIR)/pa_coordinates.c -o $(LIB_DIR)/pa_coordinates.o

$(LIB_DIR)/pa_sun.o: $(LIB_DIR)/pa_sun.c $(LIB_DIR)/pa_sun.h
	gcc -c $(LIB_DIR)/pa_sun.c -o $(LIB_DIR)/pa_sun.o

$(LIB_DIR)/pa_planets.o: $(LIB_DIR)/pa_planets.c $(LIB_DIR)/pa_planets.h
	gcc -c $(LIB_DIR)/pa_planets.c -o $(LIB_DIR)/pa_planets.o

$(LIB_DIR)/pa_planets_data.o: $(LIB_DIR)/pa_planets_data.c $(LIB_DIR)/pa_planets_data.h
	gcc -c $(LIB_DIR)/pa_planets_data.c -o $(LIB_DIR)/pa_planets_data.o

$(LIB_DIR)/pa_comet.o: $(LIB_DIR)/pa_comet.c $(LIB_DIR)/pa_comet.h
	gcc -c $(LIB_DIR)/pa_comet.c -o $(LIB_DIR)/pa_comet.o

$(LIB_DIR)/pa_comet_data.o: $(LIB_DIR)/pa_comet_data.c $(LIB_DIR)/pa_comet_data.h
	gcc -c $(LIB_DIR)/pa_comet_data.c -o $(LIB_DIR)/pa_comet_data.o

$(LIB_DIR)/pa_binary.o: $(LIB_DIR)/pa_binary.c $(LIB_DIR)/pa_binary.h
	gcc -c $(LIB_DIR)/pa_binary.c -o $(LIB_DIR)/pa_binary.o

$(LIB_DIR)/pa_binary_data.o: $(LIB_DIR)/pa_binary_data.c $(LIB_DIR)/pa_binary_data.h
	gcc -c $(LIB_DIR)/pa_binary_data.c -o $(LIB_DIR)/pa_binary_data.o

$(LIB_DIR)/pa_macros.o: $(LIB_DIR)/pa_macros.c $(LIB_DIR)/pa_macros.h
	gcc -c $(LIB_DIR)/pa_macros.c -o $(LIB_DIR)/pa_macros.o

$(LIB_DIR)/pa_util.o: $(LIB_DIR)/pa_util.c $(LIB_DIR)/pa_util.h
	gcc -c $(LIB_DIR)/pa_util.c -o $(LIB_DIR)/pa_util.o

$(TEST_DIR)/pa_datetime.o: $(TEST_DIR)/pa_datetime.c $(TEST_DIR)/pa_datetime.h $(LIB_DIR)/pa_datetime.h
	gcc -c $(TEST_DIR)/pa_datetime.c -o $(TEST_DIR)/pa_datetime.o

$(TEST_DIR)/pa_coordinates.o: $(TEST_DIR)/pa_coordinates.c $(TEST_DIR)/pa_coordinates.h $(LIB_DIR)/pa_coordinates.h
	gcc -c $(TEST_DIR)/pa_coordinates.c -o $(TEST_DIR)/pa_coordinates.o

$(TEST_DIR)/pa_sun.o: $(TEST_DIR)/pa_sun.c $(TEST_DIR)/pa_sun.h $(LIB_DIR)/pa_sun.h
	gcc -c $(TEST_DIR)/pa_sun.c -o $(TEST_DIR)/pa_sun.o

$(TEST_DIR)/pa_planets.o: $(TEST_DIR)/pa_planets.c $(TEST_DIR)/pa_planets.h $(LIB_DIR)/pa_planets.h
	gcc -c $(TEST_DIR)/pa_planets.c -o $(TEST_DIR)/pa_planets.o

$(TEST_DIR)/pa_comet.o: $(TEST_DIR)/pa_comet.c $(TEST_DIR)/pa_comet.h $(LIB_DIR)/pa_comet.h
	gcc -c $(TEST_DIR)/pa_comet.c -o $(TEST_DIR)/pa_comet.o

$(TEST_DIR)/pa_binary.o: $(TEST_DIR)/pa_binary.c $(TEST_DIR)/pa_binary.h $(LIB_DIR)/pa_binary.h
	gcc -c $(TEST_DIR)/pa_binary.c -o $(TEST_DIR)/pa_binary.o

clean:
	-rm -f pa_cli
	-rm -f libpa_lib.a
	-rm -f $(SRC_DIR)/*.o
	-rm -f $(SRC_DIR)/*.orig
	-rm -f $(LIB_DIR)/*.o
	-rm -f $(LIB_DIR)/*.orig
	-rm -f $(TEST_DIR)/*.o
	-rm -f $(TEST_DIR)/*.orig

format:
	$(FORMATTER) $(SRC_DIR)/main.c

	$(FORMATTER) $(LIB_DIR)/pa_datetime.c $(LIB_DIR)/pa_datetime.h
	$(FORMATTER) $(LIB_DIR)/pa_coordinates.c $(LIB_DIR)/pa_coordinates.h
	$(FORMATTER) $(LIB_DIR)/pa_sun.c $(LIB_DIR)/pa_sun.h
	$(FORMATTER) $(LIB_DIR)/pa_planets.c $(LIB_DIR)/pa_planets.h
	$(FORMATTER) $(LIB_DIR)/pa_planets_data.c $(LIB_DIR)/pa_planets_data.h
	$(FORMATTER) $(LIB_DIR)/pa_comet.c $(LIB_DIR)/pa_comet.h
	$(FORMATTER) $(LIB_DIR)/pa_comet_data.c $(LIB_DIR)/pa_comet_data.h
	$(FORMATTER) $(LIB_DIR)/pa_binary.c $(LIB_DIR)/pa_binary.h
	$(FORMATTER) $(LIB_DIR)/pa_binary_data.c $(LIB_DIR)/pa_binary_data.h
	$(FORMATTER) $(LIB_DIR)/pa_macros.c $(LIB_DIR)/pa_macros.h
	$(FORMATTER) $(LIB_DIR)/pa_util.c $(LIB_DIR)/pa_util.h
	$(FORMATTER) $(LIB_DIR)/pa_types.h

	$(FORMATTER) $(TEST_DIR)/pa_datetime.c $(TEST_DIR)/pa_datetime.h
	$(FORMATTER) $(TEST_DIR)/pa_coordinates.c $(TEST_DIR)/pa_coordinates.h
	$(FORMATTER) $(TEST_DIR)/pa_sun.c $(TEST_DIR)/pa_sun.h
	$(FORMATTER) $(TEST_DIR)/pa_planets.c $(TEST_DIR)/pa_planets.h
	$(FORMATTER) $(TEST_DIR)/pa_comet.c $(TEST_DIR)/pa_comet.h
	$(FORMATTER) $(TEST_DIR)/pa_binary.c $(TEST_DIR)/pa_binary.h

check:
	$(LINTER) $(SRC_DIR)/main.c

	$(LINTER) $(LIB_DIR)/pa_datetime.c $(LIB_DIR)/pa_datetime.h
	$(LINTER) $(LIB_DIR)/pa_coordinates.c $(LIB_DIR)/pa_coordinates.h
	$(LINTER) $(LIB_DIR)/pa_sun.c $(LIB_DIR)/pa_sun.h
	$(LINTER) $(LIB_DIR)/pa_planets.c $(LIB_DIR)/pa_planets.h
	$(LINTER) $(LIB_DIR)/pa_planets_data.c $(LIB_DIR)/pa_planets_data.h
	$(LINTER) $(LIB_DIR)/pa_comet.c $(LIB_DIR)/pa_comet.h
	$(LINTER) $(LIB_DIR)/pa_comet_data.c $(LIB_DIR)/pa_comet_data.h
	$(LINTER) $(LIB_DIR)/pa_binary.c $(LIB_DIR)/pa_binary.h
	$(LINTER) $(LIB_DIR)/pa_binary_data.c $(LIB_DIR)/pa_binary_data.h
	$(LINTER) $(LIB_DIR)/pa_macros.c $(LIB_DIR)/pa_macros.h
	$(LINTER) $(LIB_DIR)/pa_util.c $(LIB_DIR)/pa_util.h
	$(LINTER) $(LIB_DIR)/pa_types.h

	$(LINTER) $(TEST_DIR)/pa_datetime.c $(TEST_DIR)/pa_datetime.h
	$(LINTER) $(TEST_DIR)/pa_coordinates.c $(TEST_DIR)/pa_coordinates.h
	$(LINTER) $(TEST_DIR)/pa_sun.c $(TEST_DIR)/pa_sun.h
	$(LINTER) $(TEST_DIR)/pa_planets.c $(TEST_DIR)/pa_planets.h
	$(LINTER) $(TEST_DIR)/pa_comet.c $(TEST_DIR)/pa_comet.h
	$(LINTER) $(TEST_DIR)/pa_binary.c $(TEST_DIR)/pa_binary.h