/*
Copyright (C) 2015 Alexander Sadakov <al.sadakov_dog_gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/


typedef struct {
    int8_t dstate;	//last position input
    int8_t istate;	//integrator state

    int8_t imax, imin;	//integratir limits

    int8_t vmax,vmin;	//result limits

    int8_t pgain, igain, dgain;
} pid_struct;


int8_t update_pid(pid_struct *pid, int8_t error, uint8_t position);
