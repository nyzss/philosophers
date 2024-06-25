# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: okoca <okoca@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 19:32:31 by okoca             #+#    #+#              #
#    Updated: 2024/06/25 21:57:43 by okoca            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL=  /bin/bash

MAKEFLAGS += --no-print-directory

Black           =   $(shell echo -e "\033[0;30m")
FBlack          =   $(shell echo -e "\033[1;30m")
Red             =   $(shell echo -e "\033[0;31m")
FRed            =   $(shell echo -e "\033[1;31m")
Green           =   $(shell echo -e "\033[0;32m")
FGreen          =   $(shell echo -e "\033[1;32m")
Brown/Orange    =   $(shell echo -e "\033[0;33m")
FBrown/Orange   =   $(shell echo -e "\033[1;33m")
FYellow         =   $(shell echo -e "\033[1;33m")
Yellow          =   $(shell echo -e "\033[0;33m")
Blue            =   $(shell echo -e "\033[0;34m")
FBlue           =   $(shell echo -e "\033[1;34m")
Purple          =   $(shell echo -e "\033[0;35m")
FPurple         =   $(shell echo -e "\033[1;35m")
Cyan            =   $(shell echo -e "\033[0;36m")
FCyan           =   $(shell echo -e "\033[1;36m")
FWhite          =   $(shell echo -e "\033[1;37m")
White           =   $(shell echo -e "\033[0;37m")
RESET           =   $(shell echo -e "\033[0m")
TICK            =   $(shell echo -e "\xE2\x9C\x94")

CC = cc

SRC_DIR = src/

INCLUDES_DIR = includes

CFLAGS = -Wall -Werror -Wextra -I${INCLUDES_DIR} # -pthread -fsanitize=thread -g

SRC_FILES = main.c \
			utils.c \
			init.c \
			philos.c \
			start.c \
			actions.c \
			logging.c \
			forks.c

NAME = philo

SRC = ${addprefix ${SRC_DIR}, ${SRC_FILES}}

OBJS = ${SRC:.c=.o}

%.o: %.c
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}: ${OBJS}
	@echo "$$BANNER"
	@echo -e "${FRed}\n>>>Building ${FPurple}${NAME}${RESET}${Red}...${RESET}"
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "${FGreen}   Done [${TICK}]"

all: ${NAME}

clean:
	@echo "$(FRed)Cleaning $(NAME)$(FGreen)              [$(TICK)]"
	@rm -f ${OBJS}

fclean: clean
	@echo "$(FRed)Full Cleaning $(NAME)$(FGreen)         [$(TICK)]"
	@rm -f ${NAME}
	@echo "$(FYellow)------------------------------------------------------"

define BANNER
${FRed} ██▓███   ██░ ██  ██▓ ██▓     ▒█████${RESET}
${FRed}▓██░  ██▒▓██░ ██▒▓██▒▓██▒    ▒██▒  ██▒${RESET}
${FRed}▓██░ ██▓▒▒██▀▀██░▒██▒▒██░    ▒██░  ██▒${RESET}
${FRed}▒██▄█▓▒ ▒░▓█ ░██ ░██░▒██░    ▒██   ██░${RESET}
${FRed}▒██▒ ░  ░░▓█▒░██▓░██░░██████▒░ ████▓▒░${RESET}
${FRed}▒▓▒░ ░  ░ ▒ ░░▒░▒░▓  ░ ▒░▓  ░░ ▒░▒░▒░${RESET}
${FRed}░▒ ░      ▒ ░▒░ ░ ▒ ░░ ░ ▒  ░  ░ ▒ ▒░${RESET}
${FRed}░░        ░  ░░ ░ ▒ ░  ░ ░   ░ ░ ░ ▒${RESET}
${FRed}          ░  ░  ░ ░      ░  ░    ░ ░${RESET}
endef
export BANNER

re: fclean all

.PHONY: all clean fclean re
