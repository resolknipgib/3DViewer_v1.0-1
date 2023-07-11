CC:=gcc
CFLAGS:=-c -Wall -Wextra -Werror -std=c11 -pedantic
LDFLAGS:=-lm
SANFLAGS:=#-fsanitize=address -fsanitize=leak
GCFLAGS:=-fprofile-arcs -ftest-coverage 
GLFLAGS:=--coverage
CHECKFLAGS:=$(shell pkg-config --cflags --libs check)

# Используемые папки
SOURCE_DIR=core
TSOURCES_DIR=test
QT_DIR=qt
OBJ_DIR=build
INSTALL_DIR=bin
GCOV_DIR=gcov
DIST_DIR=3DViewer-1.0

# Списки .c файлов
SOURCES:=$(SOURCE_DIR)/*.c 
TSOURCES:=$(TSOURCES_DIR)/tests.c

# Исполняемые файлы
EXECUTABLE:=./bin/bin.app/Contents/MacOS/bin
TESTEXECUTABLE:=./tests

TEXI2DVI:=texi2dvi

all: clean tests install

clean: uninstall
	@rm -rf $(OBJ_DIR) $(GCOV_DIR)
	@rm -f $(TESTEXECUTABLE) *.gcda *.gcno *.gcov *.info *.dvi

install: uninstall
	@mkdir $(INSTALL_DIR)
	@cd ./$(INSTALL_DIR) && qmake -project ../qt ../core \
	&& echo "QT += widgets" >> bin.pro \
	&& echo "QT += gui openglwidgets" >> bin.pro \
	&& qmake -makefile bin.pro && make
	@$(EXECUTABLE)

uninstall:
	@rm -rf $(INSTALL_DIR)

dvi: 
	@makeinfo .infofile -o filedvi.dvi

dist:
	@mkdir $(DIST_DIR)
	@cp -r $(SOURCE_DIR) $(TSOURCES_DIR) $(QT_DIR) */*.pro *.conf Makefile $(EXECUTABLE) $(DIST_DIR)
	@tar -czf $(DIST_DIR).tar $(DIST_DIR)
	@rm -rf $(DIST_DIR)

tests:
	@$(CC) $(CFLAGS) $(GCFLAGS) $(SOURCES) $(TSOURCES)
	@mkdir $(OBJ_DIR)
	@mv *.o $(OBJ_DIR)
	@$(CC) $(OBJ_DIR)/*.o $(CHECKFLAGS) -o $(TESTEXECUTABLE) $(GLFLAGS) $(SANFLAGS) $(LDFLAGS)
	@$(TESTEXECUTABLE)

gcov_report: tests
	@rm -f settings.gcno settings.gcda
	@gcov *.gcno 
	@lcov --capture --directory ./ --output-file coverage.info
	@genhtml coverage.info --output-directory ./$(GCOV_DIR) 
	@open ./$(GCOV_DIR)/index.html

rebuild: clean all

lintc:
	@clang-format -n */*.c */*.cpp

linth:
	@clang-format -n */*.h

leaks:
	@leaks -atExit -- ./tests
