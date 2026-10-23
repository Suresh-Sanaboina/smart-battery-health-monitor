CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11 -Isrc
APP = battery.exe
TEST = test_battery.exe

.PHONY: all test clean
all: $(APP)

$(APP): src/main.c src/battery_monitor.c src/battery_monitor.h
	$(CC) $(CFLAGS) src/main.c src/battery_monitor.c -o $(APP)

$(TEST): tests/test_battery_monitor.c src/battery_monitor.c src/battery_monitor.h
	$(CC) $(CFLAGS) tests/test_battery_monitor.c src/battery_monitor.c -o $(TEST)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(APP) $(TEST) battery_log.txt
