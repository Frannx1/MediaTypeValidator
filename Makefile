all: clean comp run
comp: 
	cd src; make all

clean:
	cd src; make clean

run: 
	chmod 777 run.sh	
	./run.sh
test:
	
.PHONY: clean test all
