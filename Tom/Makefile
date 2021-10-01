# defining headers
PROJECT = duplicates
HEADERS = $(PROJECT).h
OBJ 	= duplicates.o hashtable.o list.o strSHA2.o

C11		= cc -std=c11
CFLAGS 	= -Wall -Werror -pedantic

# headers are accessed by $([headers])
$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ)

#% is a wildcard
%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<

# compile and run tests
# using [make test] in terminal will run test and then delete the exe file
TEST_LIST = test_list.c unit_test.c list.c
testlist :
	$(C11) $(CFLAGS) -o test_list $(TEST_LIST)
	@./test_list
	rm -f test_list

# using [make clean] in terminal will remove %.o files
clean :
	rm -f $(PROJECT) $(OBJ)
