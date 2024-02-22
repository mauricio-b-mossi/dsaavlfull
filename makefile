buildRun: 
	g++ -o build/main.exe src/*.cpp && .\\build\\main.exe

run: build/main.exe
	.\\build\\main.exe

build/main.exe:
	g++ -o build/main.exe src/*.cpp 


build/tests.exe: 
	g++ -o build/tests.exe src/tests.cpp && .\\build\\tests.exe

iotest:
	g++ -std=c++14 -Werror -Wuninitialized -o build\\test_io src\\*.cpp
	.\\build\\test_io < test-io\\input-files\\1.txt
	.\\build\\test_io < test-io\\input-files\\2.txt
	.\\build\\test_io < test-io\\input-files\\3.txt
	.\\build\\test_io < test-io\\input-files\\4.txt
	.\\build\\test_io < test-io\\input-files\\5.txt



clean:
	del build\tests.exe

test:
	g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp src/inputHandler.cpp src/inputHandlerHelpers.cpp src/gatorAvl.cpp && .\\build\\test

