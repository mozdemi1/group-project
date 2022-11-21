COURSE = cs240
SEMESTER = spring2022

CP_NUMBER = 5
GROUP_NUMBER = 19

EXE = teams

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
CC = g++
BIN = bin
OBJ = obj

all: $(EXE)

$(EXE): $(OBJ)/main.o 
	$(CC) $(FLAGS) $(OBJ)/main.o  -o $@

$(OBJ)/main.o: main.cpp 
	$(CC) $(FLAGS) -c main.cpp -o $@


tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz
