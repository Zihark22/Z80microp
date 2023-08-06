/*
 * Specification.h
 *
 * Created: 19/11/2021 08:39:08
 *  Author: Vernet Badajoz
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include <asf.h>
#include <stdio.h>
#include <stdlib.h>

// Definition for PORT
//#define PORT_B ((Port     *)0x41004480UL)

// Definition for GCLK
#define GCLK_CLKCTRL_NOWRTLOCK (0x0ul << GCLK_CLKCTRL_WRTLOCK_Pos)
#define GCLK_GENCTRL_RUNSTDBY_0 (0x0ul << GCLK_GENCTRL_RUNSTDBY_Pos)
#define GCLK_GENCTRL_DIVSEL_0 (0x0ul << GCLK_GENCTRL_DIVSEL_Pos)
#define GCLK_GENCTRL_OOV_0 (0x0ul << GCLK_GENCTRL_OOV_Pos)
#define GCLK_GENCTRL_IDC_0 (0x0ul << GCLK_GENCTRL_IDC_Pos)
#define GCLK_GENCTRL_OE_0 (0x0ul << GCLK_GENCTRL_OE_Pos)


//Definition for PORT
#define PB02_PIN_NUM	PIN_PB02%32 //TC6
#define PA02_PIN_NUM	PIN_PA02%32 // pour le DAC

#define PB08_PIN_NUM	PIN_PB08%32 //TC4

#define PB00_PIN_NUM	PIN_PB00%32 //TC7

#define PORT_PINCFG_NOPULLEN	(0x0ul << PORT_PINCFG_PULLEN_Pos)
#define PORT_PINCFG_NOINEN (0x0ul << PORT_PINCFG_INEN_Pos)
#define PORT_PINCFG_DRVLEAK	(0x0ul << PORT_PINCFG_DRVSTR_Pos)
#define TC_CTRLA_NOSWRST              (0x0ul << TC_CTRLA_SWRST_Pos)
#define TC_CTRLA_NORUNSTDBY           (0x0ul << TC_CTRLA_RUNSTDBY_Pos)

//definition
#define TC_CTRLC_NOINVEN0             (0 << TC_CTRLC_INVEN0_Pos)
#define TC_CTRLC_NOINVEN1             (0 << TC_CTRLC_INVEN1_Pos)
#define TC_CTRLC_CPDIS0				  (0 << TC_CTRLC_CPTEN0_Pos)
#define TC_CTRLC_CPDIS1				  (0 << TC_CTRLC_CPTEN1_Pos)

#define DEMIE_PERIODE_1kHZ 3999 //8M/2k -1

//constante de calcul gabarit
#define TMontee 128
#define TPalier 512
#define TDescente 128
#define TRepos 64
#define valeur_division 4 //2^4+1=facteur de division
#define resolution 1023/5000 

//defination pour le ADC
#define comptage 0
#define DEMIE_PERIODE_SIGNAL_10kHz 799 //	8M/(10k) -1

typedef enum
{
	Repos,
	Accel,
	Vconst,
	Decel
} defetat;

 typedef enum
{
	Marche,
	Arret
}defactivate;
#endif /* INCFILE1_H_ */