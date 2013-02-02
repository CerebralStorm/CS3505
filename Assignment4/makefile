tester: tester.cc date.o warehouse.o food_item.o receive.o request.o parser_helper.o
	g++  tester tester.cc date.o warehouse.o food_item.o receive.o request.o parser_helper.o

date.o: date.cc date.h 
	g++ -c date.cc date.h

warehouse.o: warehouse.cc warehouse.h
	g++ -c warehouse.cc

food_item.o: food_item.cc food_item.h
	g++ -c food_item.cc

receive.o: receive.cc receive.h
	g++ -c food_item.cc
	
request.o: request.cc request.h
	g++ -c request.cc
	
parser_helper.o: parser_helper.cc parser_helper.h
	g++ -c parser_helper.cc