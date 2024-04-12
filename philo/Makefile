NAME				=	philo

include config/srcs.mk
SRC_PATH			=	srcs/
DIR_BUILD			=	.build/
OBJS				=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
OBJS_TEST			=	$(patsubst %.c, $(DIR_BUILD)%.o, $(TEST))
DEPS				=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
DEPS_FLAGS			=	-MMD -MP
BASE_CFLAGS			=	-Wall -Werror -Wextra -O2 -pipe
BASE_DEBUG_CFLAGS	=	-g3
DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=thread
# DEBUG_CLFAGS		=	$(BASE_DEBUG_CFLAGS) -fsanitize=memory -fsanitize-memory-track-origins
FLAGS				=	$(BASE_CFLAGS)
RM					=	rm -rf
AR					=	ar rcs
CC					=	cc


DIR_INCS =\
	includes/

INCLUDES =\
	$(addprefix -I , $(DIR_INCS))

LIBS = \
	-lpthread

DEPENDENCIES =

.PHONY:		all
all:
			$(MAKE) $(NAME)

test:	$(OBJS_TEST)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS_TEST) $(LIBS) -o $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(FLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(NAME)

.PHONY:	clean
clean:
			$(RM) $(DIR_BUILD)

.PHONY:	fclean
fclean:	clean
			$(RM) $(NAME)

.PHONY:	debug
debug:
			$(MAKE) -j FLAGS="$(DEBUG_CLFAGS)"

.PHONY:	re
re:		fclean
			$(MAKE) all

.PHONY: redebug
redebug:	fclean
			$(MAKE) debug

-include $(DEPS)
$(DIR_BUILD)%.o : $(SRC_PATH)%.c Makefile
			@mkdir -p $(shell dirname $@)
			$(CC) $(FLAGS) $(DEPS_FLAGS) $(INCLUDES) -c $< -o $@
