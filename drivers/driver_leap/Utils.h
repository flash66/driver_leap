#pragma once

#define LEFT_CONTROLLER 0
#define RIGHT_CONTROLLER 1

void GenerateSerialNumber(char* p, int psize, int controller);
vr::HmdQuaternion_t CalculateRotation(float(* a)[3]);
vr::HmdQuaternion_t rotate_around_axis(const Leap::Vector& v, const float& a);
vr::HmdQuaternion_t operator*(const vr::HmdQuaternion_t& a, const vr::HmdQuaternion_t& b);
int ReadEnumVector(const std::string &f_val, const std::vector<std::string> &f_vec);
