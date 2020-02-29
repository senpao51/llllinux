lib = libmath.so
$(lib):add.o sub.o
	gcc -shared -o $@ $^
add.o:add.c
	gcc -fPIC -c $^
sub.o:sub.c
	gcc -fPIC -c $^
.PHONY:output
output:
	mkdir -p lib/lib
	mkdir -p lib/include
	cp *.so lib/lib
	cp *.h lib/include
.PHONY:clean
clean:
	rm -f *.o *.so
