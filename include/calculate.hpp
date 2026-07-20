#pragma once

#include <cmath>
#include <node_class.hpp>

#define PI 3.14159265

void calculate();

double calculateAngle(Node observer, Node target);

double calculateDistanceBetweenPoints(double x1, double x2, double y1, double y2);
