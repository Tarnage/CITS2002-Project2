# defining headers
PROJECT = duplicates
HEADERS = $(PROJECT).h
OBJ 	= duplicates.o hashtable.o list.o strSHA2.o read_dir.o 

C11		= cc -std=c11
CFLAGS 	= -Wall -Werror -pedantic

# headers are accessed by $([headers])
$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ)

%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<

# compile and run tests
# using [make test] in terminal will run test and then delete the exe file
TEST_LIST = test_list.c unit_test.c list.c
LIST_EXE  = test_list
testlist :
	$(C11) $(CFLAGS) -o $(LIST_EXE) $(TEST_LIST)
	@./$(LIST_EXE)
	rm -f $(LIST_EXE)

TEST_HASH = test_hash_table.c unit_test.c list.c hashtable.c strSHA2.c
HASH_EXE  = test_hash
testhash :
	$(C11) $(CFLAGS) -o $(HASH_EXE) $(TEST_HASH)
	@./$(HASH_EXE)
	rm -f $(HASH_EXE)

TEST_READ = read_dir.c unit_test.c test_read_dir.c
READ_EXE  = test_read
testreaddir :
	$(C11) $(CFLAGS) -o $(READ_EXE) $(TEST_READ)
	@./$(READ_EXE)
	rm -f $(READ_EXE)

# using [make clean] in terminal will remove %.o files
clean :
	rm -f $(PROJECT) $(OBJ)
