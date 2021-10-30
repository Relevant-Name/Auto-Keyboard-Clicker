// Chrono-Timer
// https://github.com/koenigbs18/Chrono-Timer
// Usage: Timer<(Chrono clock type)> t;
//		  Timer<std::chrono::steady_clock> t;
//		  t.start();
//		  if(t.get_elapsed_ms().count() < i) {
//		  ...
/*
MIT License

Copyright (c) 2020 Brett Koenig

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once
#include <chrono>

// Clock template constraints
template <class T>
requires
	requires{
		typename T::rep;
		typename T::period;
		typename T::duration;
		typename T::time_point;
		T::is_steady;
		T::now();
	}
class Timer {
public:
	Timer() : started(true), start_time(T::now()), stop_time(this->start_time) { }

	std::chrono::time_point<T> start() {
		this->started = true;
		this->stop_time = T::now();
		this->start_time = this->stop_time;
		return this->start_time;
	}

	std::chrono::time_point<T> stop() {
		this->stop_time = T::now();
		this->started = false;
		return this->stop_time;
	}

	bool is_running() {
		return this->started;;
	}

	std::chrono::time_point<T> get_elapsed() {
		return (T::now() - this->start_time);
	}

	std::chrono::duration<double, std::milli> get_elapsed_ms() {
		return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(T::now() - this->start_time);
	}

	std::chrono::time_point<T> get_start_time() {
		return this->start_time;
	}

	std::chrono::time_point<T> get_stop_time() {
		return this->stop_time;
	}
	std::chrono::time_point<T> get_run_time() {
		return (this->stop_time - this->start_time);
	}
	std::chrono::duration<double, std::milli> get_run_time_ms() {
		return std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(this->stop_time - this->start_time);
	}
private:
	std::chrono::time_point<T> start_time;
	std::chrono::time_point<T> stop_time;
	bool started;

};