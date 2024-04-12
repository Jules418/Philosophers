
SRCS =		main.c \
			$(COMMON_SRCS) \
			$(UTILS_SRCS) \
			$(PHILO_SRCS)

COMMON_SRCS = common/common.c \
				common/initialize_common.c

PHILO_SRCS = philosopher/philosopher.c \
				philosopher/philo_behavior.c \
				philosopher/philo_checker.c \
				philosopher/philo_set_get.c

UTILS_SRCS = utils/utils.c