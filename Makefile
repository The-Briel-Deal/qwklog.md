args := ./testdata/test_table.md this was run with example args

main: main.c
	cc main.c -o main

clean:
	echo "Its cleanup time! I'm deleting all da tings!"
	rm -f main

run: main
	./main $(args)

