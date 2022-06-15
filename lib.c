/* Header Include */
#include	"lib.h"

unsigned char LibTimer( unsigned char TimerEn, unsigned char timer, unsigned char Max )
{
    if ( TimerEn == TIMER_ON )
    {
        timer  = LibCountUp( timer, Max );
    }
    else
    {
         timer = CLEAR;
    }

    return ( timer );
}

unsigned char LibCountUp( unsigned char Count, unsigned char Max )
{
    if ( Count < Max )
    {
        Count++;
    }
    else
    {
        Count  = Max;
    }

    return ( Count );
}

unsigned char LibTimer_short( unsigned short TimerEn, unsigned short timer, unsigned short Max )
{
    if ( TimerEn == TIMER_ON )
    {
        timer  = LibCountUp_short( timer, Max );
    }
    else
    {
         timer = CLEAR;
    }

    return ( timer );
}

unsigned char LibCountUp_short( unsigned short Count, unsigned short Max )
{
    if ( Count < Max )
    {
        Count++;
    }
    else
    {
        Count  = Max;
    }

    return ( Count );
}

unsigned short    FadeControl( unsigned short Target, unsigned short TargetDuty, unsigned short MaxDuty, unsigned short FadeInTime, unsigned short FadeOutTime )
{
	unsigned short FadeInFreq;		/* Fade In Frequency */
	unsigned short FadeOutFreq;		/* Fade Out Frequency */

	if ( FadeInTime != CLEAR )
	{
		FadeInFreq		= MaxDuty / FadeInTime;
	}
	if ( FadeOutTime != CLEAR )
	{
		FadeOutFreq	= MaxDuty / FadeOutTime;
	}
	/* Fade In Control */
	if ( Target < TargetDuty )
	{
		if ( FadeInTime != CLEAR )
		{
			if ( ( Target + FadeInFreq ) > TargetDuty )
			{
				Target	= TargetDuty;
			}
			else
			{
				Target	+= FadeInFreq;
			}
		}
	}
	/* Fade Out Control */
	else if ( Target > TargetDuty )
	{
		if ( FadeOutTime != CLEAR )
		{
			if ( Target < FadeOutFreq )
			{
				Target	= CLEAR;
			}
			else
			{
				Target	-= FadeOutFreq;
			}
		}
	}
	else
	{
		/* 예외처리 */
	}

	return(Target);
}