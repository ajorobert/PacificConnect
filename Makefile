# PacificConnect App Makefile
#  	Created on: 27/07/2019
#   Author: Ajo Robert
#

TARGET = PacificConnect

SOURCES := $(wildcard *.cc)
OBJECTS=$(patsubst %.cc,%.o,$(SOURCES))
DEPENDS = $(patsubst %.cc,%.d,$(SOURCES))

CPPFLAGS = -g -Wall
LDFLAGS = -lboost_system -lboost_thread

.PHONY: all clean
all: $(TARGET)

$(TARGET): $(OBJECTS)
	g++ -o $@ $^ $(LDFLAGS)
	
-include $(DEPENDS)

%.o: %.cc
	g++ $(CPPFLAGS) -MMD -MP -c $< -o $@

clean:
	rm $(TARGET) $(OBJECTS) $(DEPENDS)
	