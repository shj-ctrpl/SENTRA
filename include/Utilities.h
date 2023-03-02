#pragma once

#include <iostream>

constexpr double PI() {
	return 3.14159265358979;
}

// Minimum distance error
constexpr double EPS() {
	return 1E-14;
}

// Minimum surface distance
constexpr double MSD() { 
	return 1E-10;
}

// Count as inf
constexpr double INF() {
	return 3E+30;
}


