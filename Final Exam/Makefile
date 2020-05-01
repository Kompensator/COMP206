all: sum sum1 sum2
# main.c might need common.h in the future
sum: main.o common.o
	gcc -o sum main.o common.o
sum1: sum1.o common.o
	gcc -o sum1 sum1.o common.o
sum2: sum2.o common.o
	gcc -o sum2 sum2.o common.o
main.o: main.c common.c common.h
	gcc -c main.c
sum1.o: sum1.c common.c common.h
	gcc -c -O2 sum1.c
sum2.o: sum2.c common.c common.h
	gcc -c -O2 sum2.c
common.o: common.c
	gcc -c common.c
run:
	./sum ~/COMP206/Final\ Exam/numbers.txt & ./sum1 & ./sum2
	rm values1.txt values2.txt
	rm sum1.txt sum2.txt
cleanup:
	rm main.o sum1.o sum2.o common.o