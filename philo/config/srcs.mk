
SRCS =		main.c \
			$(COMMON_SRCS) \
			$(UTILS_SRCS) \
			$(PHILO_SRCS)

COMMON_SRCS = common/common.c

PHILO_SRCS = philosopher/philosopher.c

UTILS_SRCS = utils/utils.c