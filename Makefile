coroutine:
	g++ -std=c++20 -fcoroutines coroutine.cpp -o coroutine
	./coroutine

fiber:
	g++ fiber.cpp -o fiber
	./fiber

clean:
	rm ./fiber
	rm ./coroutine
