CFLAGS=-std=c99 -Wall -Wextra -Wconversion `pkg-config --cflags glib-2.0` -g
LDLIBS=`pkg-config --libs glib-2.0` -lm

# Deze code hoort bij het laatste gedeelte van C (de parser)
# en is daarmee onderdeel van de eindopdracht.
#
# Deze Makefile zou je maar heel beperkt moeten wijzigen:
#
# - het is logisch dat object_files wordt uitgebreid
# - op moment dat je alle informatie uit een request hebt
#   verzamelt zodat je kan beginnen aan de afhandeling
#   van het request, kan je als unittest integration_test
#   gebruiken.
#
# De code die je krijgt mag je gebruiken voor je eindopdracht,
# onder de voorwaarde dat je deze code begrijpt. In het assessmen
# kan je vragen over deze code verwachten.
#
# Deze code hoeft beperkt veranderd te worden:
#
# - In eerste instantie zal vooral abnf.c aangevuld moeten worden.
# - Om de integratietests te laten slagen, zal je extra c en h
#   bestanden toe moeten voegen.
# - Tot slot zal je arduino_server.ino moeten aanvullen om de
#   acceptatietests te laten slagen.
#
# De werking van de Makefile mag niet wijzigen: `make`,
# `make arduino` en `make rpi` moeten blijven doen wat ze nu ook doen,
# namelijk, het uitvoeren van de integratietest respectievelijk
# acceptatietest.
#
# OK, de werking van de Makefile moet op een aspect wijzigen: in plaats
# van de unittests moeten de integratietest uitgevoerd worden.
#
# Voor het assessment is het essentieel dat:
#
# 1. de code zonder waarschuwing compileert
# 2. cppcheck geen waarschuwingen geeft
# 3. de integratietest foutloos draait
# 4. de acceptatietests op Arduino en Raspberry foutloos draaien
#
# Bovenstaande vier punten moet zonder aanpassing aan deze Makefile
# ook gelden wanneer de integratietest en acceptatietests vervangen worden.
#
# Tot slot, de eindopdracht moet worden opgeleverd zonder gecompileerde
# bestanden.

# your configuration:
arduino_IP=10.1.200.21
rpi_IP=10.1.200.11

object_files=$(project)/cserver.o \
             $(project)/token.o \
             $(project)/abnf.o \
             buffermock.o

unittest=unit_test
# unittest=integration_test

# do not change:

project=arduino_server
arduinotest=acceptation_test_arduino.py
rpitest=acceptation_test_rpi.py
virtualEnvironment=virtEnv

.PHONY: test_c_code arduino rpi fmt check prepare accept_arduino accept_rpi clean

test_c_code: check fmt clean

# needs a running server on Arduino on $(arduino_IP)
arduino: prepare fmt accept_arduino 

# needs a running server on RPi on $(rpi_IP)
rpi: prepare fmt accept_rpi


$(unittest): $(object_files)

fmt:
	clang-format -style='{PointerAlignment: Left, ColumnLimit: 60}' -i $(project)/*.c $(project)/*.h $(project)/*.ino
	clang-format -style='{PointerAlignment: Left, ColumnLimit: 60}' -i *.c *.h
	# autopep8 -i *.py

check: $(unittest)
	cppcheck --quiet --enable=all --suppress=missingIncludeSystem --inline-suppr --inconclusive --std=c99 $(project)/
	-./$(unittest)

# bar limits check to availability, no timestamp check performed
prepare: | $(virtualEnvironment)

$(virtualEnvironment):
	python3 -m venv $(virtualEnvironment)
	./$(virtualEnvironment)/bin/pip3 install pytest
	./$(virtualEnvironment)/bin/pip3 install requests
	./$(virtualEnvironment)/bin/pip3 install --force-reinstall -v "requests-raw==1.0.1"

accept_arduino:
	ip=$(arduino_IP) ./$(virtualEnvironment)/bin/python3 $(arduinotest)

accept_rpi:
	ip=$(rpi_IP) ./$(virtualEnvironment)/bin/python3 $(rpitest)

clean:
	-rm *.o $(project)/*.o
	-rm -rf $(unittest).dSYM/
	-rm $(unittest)

refresh:
	-rm -rf __pycache__/
	-rm -rf .pytest_cache/
	-rm -rf $(virtualEnvironment)

