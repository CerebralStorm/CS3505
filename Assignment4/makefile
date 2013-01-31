tester: tester.cc date.o warehouse.o food_item.o parser_helper.o
	g++ -o tester tester.cc date.o warehouse.o food_item.o parser_helper.o

date.o: date.cc date.h 
	g++ -c date.cc date.h

warehouse.o: warehouse.cc warehouse.h
	g++ -c warehouse.cc warehouse.h

food_item.o: food_item.cc food_item.h
	g++ -c food_item.cc food_item.h

parser_helper.o: food_item.o warehouse.o date.o
	g++ -c parser_helper.cc parser_helper.h