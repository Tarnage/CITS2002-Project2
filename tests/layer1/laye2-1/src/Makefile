# defining headers
PROJECT = duplicates
HEADERS = $(PROJECT).h 
#OBJ 	= UNCOMMENT THIS ONCE WE HAVE SOURCE FILES

C11		= cc -std=c11
CFLAGS 	= -Wall -Werror -pedantic

# headers are accessed by $([headers])
$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) -lm

# % is a wildcard
%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<


# using [make clean] in terminal will remove %.o files
clean :
	rm -f $(PROJECT) $(OBJ)
