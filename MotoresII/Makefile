#
# Makefile:
#	wiringPi - Wiring Compatable library for the Raspberry Pi
#	https://projects.drogon.net/wiring-pi
#
#	Copyright (c) 2012-2015 Gordon Henderson
#################################################################################
# This file is part of wiringPi:
#	Wiring Compatable library for the Raspberry Pi
#
#    wiringPi is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    wiringPi is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
#################################################################################

ifneq ($V,1)
Q ?= @
endif

#DEBUG	= -g -O0
DEBUG	= -O3
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS    = -lwiringPi -lwiringPiDev -lpthread -lm

# Should not alter anything below this line
###############################################################################

SRC	=	robot.c motores.c sensores-spi.c motores-2m.c \
                pruebas-cny70.c sensores-spi-test.c pruebas-gp2xxx.c \
                pruebas-motores-gp2xxx.c

OBJ	=	$(SRC:.c=.o)

BINS	=	$(SRC:.c=)

all:	
	$Q cat README.TXT
	$Q echo "    $(BINS)" | fmt
	$Q echo ""

really-all:	$(BINS)

robot:	robot.o
	$Q echo [link]
	$Q $(CC) -o $@ robot.o $(LDFLAGS) $(LDLIBS)

motores: motores.o motores-2m.o
	$Q echo [link]
	$Q $(CC) -o $@ motores.o motores-2m.o $(LDFLAGS) $(LDLIBS)

sensores-spi: sensores-spi.o sensores-spi-test.o
	$Q echo [link]
	$Q $(CC) -o $@ sensores-spi.o sensores-spi-test.o $(LDFLAGS) $(LDLIBS)

pruebas-cny70: sensores-spi.o motores.o pruebas-cny70.o
	$Q echo [link]
	$Q $(CC) -o $@ sensores-spi.o motores.o pruebas-cny70.o $(LDFLAGS) $(LDLIBS)

pruebas-gp2xxx: sensores-spi.o pruebas-gp2xxx.o
	$Q echo [link]
	$Q $(CC) -o $@ sensores-spi.o pruebas-gp2xxx.o $(LDFLAGS) $(LDLIBS)

motores-gp2xxx: sensores-spi.o motores.o pruebas-motores-gp2xxx.o
	$Q echo [link]
	$Q $(CC) -o $@ sensores-spi.o motores.o pruebas-motores-gp2xxx.o $(LDFLAGS) $(LDLIBS)

.c.o:
	$Q echo [CC] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJ) *~ core tags $(BINS)

tags:	$(SRC)
	$Q echo [ctags]
	$Q ctags $(SRC)

depend:
	makedepend -Y $(SRC)

# DO NOT DELETE
