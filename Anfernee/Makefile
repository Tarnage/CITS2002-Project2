# defining headers
PROJECT = duplicates
HEADERS = $(PROJECT).h 
TESTFILE = test_duplicates.c
#OBJ 	= UNCOMMENT THIS ONCE WE HAVE SOURCE FILES

C11		= cc -std=c11
CFLAGS 	= -Wall -Werror -pedantic

# headers are accessed by $([headers])
$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm

#% is a wildcard
%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<

# compile and run tests
# using [make test] in terminal will run test and then delete the exe file
test :
	$(C11) $(CFLAGS) -o test $(TESTFILE)
	@./test
	rm -f test

# using [make clean] in terminal will remove %.o files
clean :
	rm -f $(PROJECT) $(OBJ)
