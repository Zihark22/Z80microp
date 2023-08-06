/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * This is a bare minimum user application template.
 *
 * For documentation of the board, go \ref group_common_boards "here" for a link
 * to the board-specific documentation.
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# Minimal main function that starts with a call to system_init()
 * -# Basic usage of on-board LED and button
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include "Specification.h"

Tc *ptr_TC;
Dac *ptr_DAC;
defetat etat;
int Temps;

//prototypes
void config_PM(void);
void configure_TC6_callback(void);
void procedure_traitement_it(void);
int calculGabarit(int palier, defactivate unetat);
void config_GCLK_DAC(void);
void config_PORT_DAC(void);
void config_DAC(void);
void ecriture_DAC(int consigne);

void config_GCLK_ADC(void);
void config_PORT_ADC(void);
void config_ADC(void);

void config_TC4(void);
void config_PORT_TC4(void);
void config_GCLK_TC4(void);

void config_GCLK_TC6(void);
void config_PORT_TC6(void);
void config_TC6(void);

void config_GCLK_TC7(void);
void config_PORT_TC7(void);
void config_TC7(void);

//void ecriture_ADC(int consigne);

//fonctions
void config_PM(void)
{
	Pm *ptr_Pm;
	ptr_Pm = PM;
	ptr_Pm->CPUSEL.reg = PM_CPUSEL_CPUDIV_DIV1;
	ptr_Pm->APBCSEL.reg = PM_APBCSEL_APBCDIV(0);
	ptr_Pm->APBCMASK.reg =
	PM_APBCMASK_TC6|
	PM_APBCMASK_DAC|
	PM_APBCMASK_ADC;

	//PM du DAC(validtion horloge bus pour le peripherique)
}


/*timer*/
void config_GCLK_TC6(void)
{
	Gclk *ptr_GCLK;
	ptr_GCLK = GCLK;
	ptr_GCLK->CLKCTRL.reg =
					GCLK_CLKCTRL_NOWRTLOCK|
					GCLK_CLKCTRL_CLKEN|
					GCLK_CLKCTRL_GEN_GCLK0|
					GCLK_CLKCTRL_ID_TC6_TC7;
	ptr_GCLK->GENCTRL.reg =
					GCLK_GENCTRL_RUNSTDBY_0|
					GCLK_GENCTRL_DIVSEL_0|
					GCLK_GENCTRL_OE_0|
					GCLK_GENCTRL_OOV_0|
					GCLK_GENCTRL_IDC_0|
					GCLK_GENCTRL_GENEN|
					GCLK_GENCTRL_SRC_OSC8M|
					GCLK_GENCTRL_ID(0);			 
	
}
void config_PORT_TC6(void)
{
	Port *ptr_port;
	ptr_port = PORT;
	ptr_port->Group[1].DIRSET.reg = PORT_PB02;
	ptr_port->Group[1].PMUX[PB02_PIN_NUM/2].reg = PORT_PMUX_PMUXE_E;
	ptr_port->Group[1].PINCFG[PB02_PIN_NUM].reg = PORT_PINCFG_PMUXEN|
	PORT_PINCFG_DRVLEAK|
	PORT_PINCFG_NOPULLEN|
	PORT_PINCFG_NOINEN;
}

void config_TC6(void)
{
	ptr_TC = TC6;
	ptr_TC->COUNT16.CTRLA.reg =
							TC_CTRLA_PRESCSYNC_PRESC|
							TC_CTRLA_NORUNSTDBY|
							TC_CTRLA_PRESCALER_DIV1|
							TC_CTRLA_ENABLE|
							TC_CTRLA_WAVEGEN_MFRQ|
							TC_CTRLA_MODE_COUNT16|
							TC_CTRLA_NOSWRST;
	
	/*doc p556 */
	ptr_TC->COUNT16.CTRLC.reg =
							TC_CTRLC_CPDIS0|
							TC_CTRLC_CPDIS1|
							TC_CTRLC_NOINVEN0|
							TC_CTRLC_NOINVEN1;
	ptr_TC->COUNT16.CTRLBCLR.reg =
							TC_CTRLBCLR_CMD_NONE|
							TC_CTRLBCLR_DIR|
							TC_CTRLBCLR_ONESHOT;
	ptr_TC->COUNT16.CC[0].reg = DEMIE_PERIODE_1kHZ*2; //on veut une periode de 1ms, le handler gère une demi periode; Il faut doubler la clock pour obtenir 1ms
	ptr_TC->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
}
//TC4
void config_GCLK_TC4(void)
{
	Gclk *ptr_GCLK;
	ptr_GCLK = GCLK;
	ptr_GCLK->CLKCTRL.reg =
						GCLK_CLKCTRL_NOWRTLOCK|
						GCLK_CLKCTRL_CLKEN|
						GCLK_CLKCTRL_GEN_GCLK3|
						GCLK_CLKCTRL_ID_TC4_TC5;
	ptr_GCLK->GENCTRL.reg =
						GCLK_GENCTRL_RUNSTDBY_0|
						GCLK_GENCTRL_DIVSEL_0|
						GCLK_GENCTRL_OE_0|
						GCLK_GENCTRL_OOV_0|
						GCLK_GENCTRL_IDC_0|
						GCLK_GENCTRL_GENEN|
						GCLK_GENCTRL_SRC_OSC8M|
						GCLK_GENCTRL_ID(3);
	
}

void config_PORT_TC4(void)
{
	Port *ptr_port;
	ptr_port = PORT;
	ptr_port->Group[1].DIRSET.reg = PORT_PB08;
	ptr_port->Group[1].PMUX[PB08_PIN_NUM/2].reg = PORT_PMUX_PMUXE_E;
	ptr_port->Group[1].PINCFG[PB08_PIN_NUM].reg = 
											PORT_PINCFG_PMUXEN|
											PORT_PINCFG_DRVLEAK|
											PORT_PINCFG_NOPULLEN|
											PORT_PINCFG_NOINEN;
}

void config_TC4(void)
{
	ptr_TC = TC4;
	ptr_TC->COUNT16.CTRLA.reg =
						TC_CTRLA_PRESCSYNC_PRESC|
						TC_CTRLA_NORUNSTDBY|
						TC_CTRLA_PRESCALER_DIV1|
						TC_CTRLA_ENABLE|
						TC_CTRLA_WAVEGEN_MFRQ|
						TC_CTRLA_MODE_COUNT8 |
						TC_CTRLA_NOSWRST;
	
	/*doc p556 */
	ptr_TC->COUNT16.CTRLC.reg =
						TC_CTRLC_CPDIS0|
						TC_CTRLC_CPDIS1|
						TC_CTRLC_NOINVEN0|
						TC_CTRLC_NOINVEN1;
	ptr_TC->COUNT16.CTRLBCLR.reg =
						TC_CTRLBCLR_CMD_NONE|
						TC_CTRLBCLR_DIR|
						TC_CTRLBCLR_ONESHOT;
	ptr_TC->COUNT16.CC[0].reg = DEMIE_PERIODE_SIGNAL_10kHz;
	ptr_TC->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
}
//TC7
void config_GCLK_TC7(void)
{
	Gclk *ptr_GCLK;
	ptr_GCLK = GCLK;
	ptr_GCLK->CLKCTRL.reg =
					GCLK_CLKCTRL_NOWRTLOCK|
					GCLK_CLKCTRL_CLKEN|
					GCLK_CLKCTRL_GEN_GCLK4|
					GCLK_CLKCTRL_ID_TC6_TC7;
	ptr_GCLK->GENCTRL.reg =
					GCLK_GENCTRL_RUNSTDBY_0|
					GCLK_GENCTRL_DIVSEL_0|
					GCLK_GENCTRL_OE_0|
					GCLK_GENCTRL_OOV_0|
					GCLK_GENCTRL_IDC_0|
					GCLK_GENCTRL_GENEN|
					GCLK_GENCTRL_SRC_OSC8M|
					GCLK_GENCTRL_ID(4);
	
}

void config_PORT_TC7(void)
{
	Port *ptr_port;
	ptr_port = PORT;
	ptr_port->Group[1].DIRSET.reg = PORT_PB00;
	ptr_port->Group[1].PMUX[PB00_PIN_NUM/2].reg = PORT_PMUX_PMUXE_E;
	ptr_port->Group[1].PINCFG[PB00_PIN_NUM].reg =
											PORT_PINCFG_PMUXEN|
											PORT_PINCFG_DRVLEAK|
											PORT_PINCFG_NOPULLEN|
											PORT_PINCFG_NOINEN;
}-

void config_TC7(void)
{
	ptr_TC = TC7;
	ptr_TC->COUNT16.CTRLA.reg =
							TC_CTRLA_PRESCSYNC_PRESC|
							TC_CTRLA_NORUNSTDBY|
							TC_CTRLA_PRESCALER_DIV1|
							TC_CTRLA_ENABLE|
							TC_CTRLA_WAVEGEN_MPWM|
							TC_CTRLA_MODE_COUNT8 |
							TC_CTRLA_NOSWRST;
	
	/*doc p556 */
	ptr_TC->COUNT16.CTRLC.reg =
							TC_CTRLC_CPDIS0|
							TC_CTRLC_CPDIS1|
							TC_CTRLC_NOINVEN0|
							TC_CTRLC_NOINVEN1;
	ptr_TC->COUNT16.CTRLBCLR.reg =
						TC_CTRLBCLR_CMD_NONE|
						TC_CTRLBCLR_DIR|
						TC_CTRLBCLR_ONESHOT;
	ptr_TC->COUNT16.CC[0].reg = DEMIE_PERIODE_SIGNAL_10kHz;
	ptr_TC->COUNT16.CTRLA.reg |= TC_CTRLA_ENABLE;
}


/*DAC*/
void config_GCLK_DAC(void)
{
	Gclk *ptr_GCLK;
	ptr_GCLK = GCLK;
	ptr_GCLK->CLKCTRL.reg =
					GCLK_CLKCTRL_NOWRTLOCK|
					GCLK_CLKCTRL_CLKEN|
					GCLK_CLKCTRL_GEN_GCLK1|
					GCLK_CLKCTRL_ID_DAC;
	ptr_GCLK->GENCTRL.reg =
					GCLK_GENCTRL_RUNSTDBY_0|
					GCLK_GENCTRL_DIVSEL|
					GCLK_GENCTRL_OE_0|
					GCLK_GENCTRL_OOV_0|
					GCLK_GENCTRL_IDC_0|
					GCLK_GENCTRL_GENEN|
					GCLK_GENCTRL_SRC_OSC8M|
					GCLK_GENCTRL_ID(1);
	ptr_GCLK->GENDIV.reg = 
					GCLK_GENDIV_DIV(valeur_division)|
					GCLK_GENDIV_ID(1);
}

void config_DAC(void)
{
	ptr_DAC = DAC;
	ptr_DAC->CTRLB.reg = DAC_CTRLB_EOEN|
						 DAC_CTRLB_REFSEL(1);//configuration 
	ptr_DAC->CTRLA.reg = DAC_CTRLA_ENABLE;
}



void config_PORT_DAC(void)
{
	Port *ptr_port;
	ptr_port = PORT;
	ptr_port->Group[0].DIRSET.reg = PORT_PA02;
	ptr_port->Group[0].PMUX[PA02_PIN_NUM/2].reg = PORT_PMUX_PMUXE_B;
	ptr_port->Group[0].PINCFG[PA02_PIN_NUM].reg =
												PORT_PINCFG_PMUXEN|
												PORT_PINCFG_DRVLEAK|
												PORT_PINCFG_NOPULLEN|
												PORT_PINCFG_NOINEN;
}

void ecriture_DAC(int consigne)
{
		ptr_DAC->DATA.reg = consigne*resolution;
}

void configure_TC6_callback(void)
{
	system_interrupt_enable(SYSTEM_INTERRUPT_MODULE_TC6);

	/* Validation de l'IT sur Overflow du compteur dans le TC6. */
	ptr_TC->COUNT16.INTENSET.reg = TC_INTFLAG_MC0;
}

/*ADC*/
void config_GCLK_ADC(void)
{
	Gclk *ptr_GCLK;
	ptr_GCLK = GCLK;
	ptr_GCLK->CLKCTRL.reg =
						GCLK_CLKCTRL_NOWRTLOCK|
						GCLK_CLKCTRL_CLKEN|
						GCLK_CLKCTRL_GEN_GCLK2|
						GCLK_CLKCTRL_ID_ADC;
	ptr_GCLK->GENCTRL.reg =
						GCLK_GENCTRL_RUNSTDBY_0|
						GCLK_GENCTRL_DIVSEL|
						GCLK_GENCTRL_OE_0|
						GCLK_GENCTRL_OOV_0|
						GCLK_GENCTRL_IDC_0|
						GCLK_GENCTRL_GENEN|
						GCLK_GENCTRL_SRC_OSC8M|
						GCLK_GENCTRL_ID(2);
	ptr_GCLK->GENDIV.reg =
						GCLK_GENDIV_DIV(valeur_division)|
						GCLK_GENDIV_ID(2);
}


void config_PORT_ADC(void)
{
	Adc *ptr_ADC;
	ptr_ADC = ADC;
	ptr_ADC->CTRLB.reg = DAC_CTRLB_REFSEL(2); //le dac veut resevoir une tension entre 1 et 2.7v. On prend le REFSEL(2) le plus proche de 3.3/2
	ptr_ADC->CTRLA.reg = ADC_CTRLA_ENABLE;
}
void Asservissement(int Vit_Mot, int Vconsigne, int Cmd_Mot)
{
	int Kp=;
	int Ki=;
	int Kd=;
	Cmd_Mot=Vit_Mot;
}
int calculGabarit(int VPalier, defactivate active)
{
	int Vconsigne=VPalier;
	// Début cycle H
	switch(etat)
	{
		case Repos :
		Vconsigne=0;
		if(active == Marche)
		{	if(Temps>=TRepos){
			etat=Accel;
			Temps=0;
		}
		else
		{
			Temps+=1;
		}
	}
	break;
	case Accel :
	if (Temps>=TMontee)
	{
		etat=Vconst;
		Temps=0;
		Vconsigne=VPalier;
	}
	else
	{
		Temps+=1;
		Vconsigne=(VPalier*Temps)/TMontee;
	}
	break;

	case Vconst :
	if (Temps>=TPalier)
	{
		etat=Decel;
		Temps=0;
	}
	else
	{
		Temps+=1;
	}
	break;

	case Decel :
	if (Temps>=TDescente)
	{
		etat=Repos;
		Temps=0;
		Vconsigne=0;
	}
	else
	{
		Temps+=1;
		Vconsigne=VPalier*(TDescente-Temps)/TDescente;
	}
	break;
	default : etat=Repos; break;// rajouté
	
}
// fin du cycle H
return Vconsigne;
}

void procedure_traitement_it(void)
{
	int Vpalier = 5000;
	int Vconsigne = 0;
	defactivate active = Marche;
	Port *ptr_Port;
	ptr_Port =PORT;
	
	/* Vérification du bon fonctionnement de l'IT par commutation broche PB06 */
	ptr_Port->Group[1].OUTTGL.reg = PORT_PB06;
	
	/*calcul de la consigne */
	Vconsigne = calculGabarit(Vpalier, active);
	ecriture_DAC(Vconsigne);
}

//Handler d'interruption
void TC6_Handler(){
	procedure_traitement_it();
	
	ptr_TC->COUNT16.INTFLAG.reg=TC_INTFLAG_MC0;
}


int main (void)
{
	system_init();
	etat = Repos;
	Temps = 0;
	ptr_TC = TC6;
	config_GCLK_TC6();
	config_PM();
	config_PORT_TC6();
	config_TC6();
	configure_TC6_callback();
	
	config_GCLK_TC7();
	config_PORT_TC7();
	config_TC7();
	
	config_GCLK_DAC();
	config_PORT_DAC();
	config_DAC();
	
	while (1) {
		/* Is button pressed? */
		if (port_pin_get_input_level(BUTTON_0_PIN) == BUTTON_0_ACTIVE) {
			/* Yes, so turn LED on. */
			port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
		} 
		else {
			/* No, so turn LED off. */
			port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);
		}
	}
}


