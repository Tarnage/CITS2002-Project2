NAME		= duplicates
TIMESHA2	= timeSHA2

DOTH		= $(NAME).h hashtable.h
OBJ		= duplicates.o \
			directories.o \
			listthings.o \
			hashtable.o \
			minimize.o \
			paths.o \
			strSHA2.o

SRC		= duplicates.c \
			directories.c \
			listthings.c \
			hashtable.c \
			minimize.c \
			paths.c \
			strSHA2.c

CC		= cc
CSTD		= c11
CFLAGS		= -std=$(CSTD) -Wall -Werror -pedantic
LD		= cc
#
# For the basic project we do not need any preprocessor defines
#DEFINES		=
#
# For the advanced project we need to define the ADVANCED token
DEFINES		= -DADVANCED
#

$(NAME) : $(OBJ)
	$(LD) -o $(NAME) $(OBJ)
	@make both

%.o :	%.c $(DOTH)
	$(CC) $(CFLAGS) $(DEFINES) -c $<

both:
	@echo compiling $(NAME)-basic
	@$(CC) $(CFLAGS) -DBASIC    -o $(NAME)-basic    $(SRC)
	@echo compiling $(NAME)-advanced
	@$(CC) $(CFLAGS) -DADVANCED -o $(NAME)-advanced $(SRC)


lines:
	cat *.h [a-p]*.c | grep -v '^//' | grep -v '^$$' | wc -l


$(TIMESHA2):	$(TIMESHA2).c
	$(CC) $(CFLAGS) -o $(TIMESHA2) $(TIMESHA2).c

clean:
	rm -f $(NAME) $(NAME)-basic $(NAME)-advanced $(OBJ) $(TIMESHA2)
