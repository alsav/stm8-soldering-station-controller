#include "main.h"

int8_t update_pid(pid_struct *pid, int8_t error, uint8_t position)
{
    int16_t pterm, iterm, dterm, outval;
//    int8_t pterm, iterm, dterm;
//    int16_t outval;
//    int16_t pterm, iterm, dterm, outval;

    pterm = pid->pgain * error;		//proportional calculation
//    pterm = (pid->pgain * error)>>8;		//proportional calculation

    // update integrator state
    pid->istate += error;
    if (pid->istate > pid->imax)
	pid->istate = pid->imax;
    else if (pid->istate < pid->imin)
	pid->istate = pid->imin;

//    iterm = pid->igain * (pid->istate>>2) ;	//integral calcucation
    iterm = pid->igain * pid->istate;	//integral calcucation

    dterm = pid->dgain * (position - pid->dstate);	//differential calc

    pid->dstate = position;

//    return (int8_t)((pterm + iterm - dterm)>>8);
//    return pterm + iterm - dterm;

    outval=pterm + iterm - dterm;
//    outval=(int8_t)((pterm + iterm - dterm)>>8);
    if (outval>pid->vmax)
	outval=pid->vmax;
    else if (outval<pid->vmin)
	outval=pid->vmin;

    return (int8_t)outval;
}
