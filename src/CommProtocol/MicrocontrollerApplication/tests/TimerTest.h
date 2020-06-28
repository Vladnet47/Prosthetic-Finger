#pragma once
#include <iostream>
#include <string>
#include "Asserts.h"
#include "../src/Timer.h"

namespace TimerTest {
	static void Run();
	static void ConstructorTest();
	static void StartTest();
	static void SetTest();
	static void RestartTest();
	static void OverflowTest();
}

void TimerTest::Run() {
	TimerTest::ConstructorTest();
	TimerTest::StartTest();
	TimerTest::SetTest();
	TimerTest::RestartTest();
	TimerTest::OverflowTest();
}

void TimerTest::ConstructorTest() {
	cout << "Constructor Test" << endl;
	Timer timer{ 10 };
	Asserts::AssertTrue("1) Timer stopped", timer.isStopped());
}

void TimerTest::StartTest() {
	cout << "Start Test" << endl;
	unsigned long startTime = 1000;
	unsigned long endTime = 1500;
	Timer timer{ 10 };
	timer.start(startTime);
	Asserts::AssertFalse("1) Timer not elapsed", timer.isElapsed(startTime));
	Asserts::AssertTrue("2) Timer is elapsed", timer.isElapsed(endTime));
	timer.stop();
	Asserts::AssertFalse("3) Timer not elapsed", timer.isElapsed(startTime));
}

void TimerTest::SetTest() {
	cout << "Set Test" << endl;
	unsigned long startTime = 1000;
	unsigned long endTime1 = 1500;
	unsigned long endTime2 = 2500;
	Timer timer{ 10 };
	timer.start(startTime);
	timer.set(1000);
	Asserts::AssertTrue("1) Timer stopped", timer.isStopped());
	timer.start(startTime);
	Asserts::AssertFalse("2) Timer not elapsed", timer.isElapsed(startTime));
	Asserts::AssertFalse("3) Timer not elapsed", timer.isElapsed(endTime1));
	Asserts::AssertTrue("4) Timer is elapsed", timer.isElapsed(endTime2));
}

void TimerTest::RestartTest() {
	cout << "Restart Test" << endl;
	unsigned long startTime1 = 1000;
	unsigned long startTime2 = 2000;
	Timer timer{ 10 };
	timer.start(startTime1);
	Asserts::AssertTrue("1) Timer is elapsed", timer.isElapsed(startTime1 + 30));
	timer.start(startTime2);
	Asserts::AssertTrue("3) Timer is elapsed", timer.isElapsed(startTime2 + 30));
}

void TimerTest::OverflowTest() {
	cout << "Overflow Test" << endl;
	unsigned long startTime = 1000;
	Timer timer{ 10 };
	timer.start(startTime);
	Asserts::AssertTrue("1) Timer is elapsed", timer.isElapsed(startTime - 30)); // subtract to signify overlow, since time never goes backwards
}