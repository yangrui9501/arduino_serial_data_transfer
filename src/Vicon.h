/**
 * @file Vicon.h
 * @author your name (you@domain.com)
 * @brief Extension Library for dealing with Vicon data
 * @version 0.1
 * @date 2022-03-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <Arduino.h>

void ViconRot_to_Euler(float *Vicon_Rotation, float *Euler_Angle)
{
    double phi_s = Vicon_Rotation[0] * DEG_TO_RAD;
    double theta_s = Vicon_Rotation[1] * DEG_TO_RAD;
    double psi_s = Vicon_Rotation[2] * DEG_TO_RAD;

    // Auxilary variables avoid the repetitive calculations
    double sphi = sin(phi_s);
    double cphi = cos(phi_s);
    double stheta = sin(theta_s);
    double ctheta = cos(theta_s);
    double spsi = sin(psi_s);
    double cpsi = cos(psi_s);

    Euler_Angle[0] = atan2(cpsi * sphi + cphi * spsi * stheta, cphi * ctheta);
    Euler_Angle[1] = atan2(-(sphi * spsi - cphi * cpsi * stheta), cphi * cpsi * stheta - sphi * spsi + 1);
    Euler_Angle[2] = atan2(cphi * spsi + cpsi * sphi * stheta, cpsi * ctheta);
}

void ViconRot_to_DCM(float *Vicon_Rotation, float *DCM)
{
    double phi_s = Vicon_Rotation[0] * DEG_TO_RAD;
    double theta_s = Vicon_Rotation[1] * DEG_TO_RAD;
    double psi_s = Vicon_Rotation[2] * DEG_TO_RAD;

    // Auxilary variables avoid the repetitive calculations
    double sphi = sin(phi_s);
    double cphi = cos(phi_s);
    double stheta = sin(theta_s);
    double ctheta = cos(theta_s);
    double spsi = sin(psi_s);
    double cpsi = cos(psi_s);

    DCM[0] = cpsi * ctheta;
    DCM[1] = -ctheta * spsi;
    DCM[2] = stheta;
    DCM[3] = cphi * spsi + cpsi * sphi * stheta;
    DCM[4] = cphi * cpsi - sphi * spsi * stheta;
    DCM[5] = -ctheta * sphi;
    DCM[6] = sphi * spsi - cphi * cpsi * stheta;
    DCM[7] = cpsi * sphi + cphi * spsi * stheta;
    DCM[8] = cphi * ctheta;
}