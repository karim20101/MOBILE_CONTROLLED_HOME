/*
 * APP.c
 *
 *  Created on: April 2, 2023
 *      Author: KARIM MOKHTAR
 */

// Built in Library
#include <util/delay.h>
// Library Layer
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"
// MCAL
#include "../include/MCAL/DIO/DIO_Interface.h"
#include "../include/MCAL/EXTI/EXTI_Interface.h"
#include "../include/MCAL/GI/GI_Interface.h"
#include "../include/MCAL/TIMERS/TIMERS_Interface.h"
#include "../include/MCAL/UART/UART_Interface.h"
// HAL
#include "../include/HAL/LCD/LCD_Interface.h"

#define F_CPU 8000000UL


int main(){
// D0 input RX D1 output TX
// B0 INPUT  MOTOR RELAY
// B1 INPUT  BUZZER RELAY
// B2 OUTPUT  LIGHT
// B3 OUTPUT  ALARM



	MDIO_voidInit();
    MUART_voidInit ();






    u8 local_u8readuser[6]={'0'};
    u8 local_u8usercounter=0;
    u8 local_u8readpass[5]={'x'};
    u8 local_u8passcounter=0;
    u8 local_u8passloop=0;
  	u8 local_u8errorcounter=0;
  	u8 local_u8flag0=0;
	while(1){
		local_u8readuser[0]='x';
		local_u8readuser[1]='x';
		local_u8readuser[2]='x';
		local_u8readuser[3]='x';
		local_u8readuser[4]='x';
		local_u8readuser[5]='x';
		local_u8usercounter=0;
		local_u8passcounter=0;
		local_u8passloop=0;
		local_u8errorcounter=0;


while(1){


	   	  local_u8readuser[local_u8usercounter]= MUART_u8ReadByteSynchBlocking ();
	   	  if(local_u8readuser[local_u8usercounter]=='v'){
	   		  continue;
	   	  }

	   			   	  if(local_u8readuser[local_u8usercounter]!='#')
	   			   			  {



	   			   			  local_u8usercounter++;
	   			   			  if(local_u8usercounter>5){break;}

	   			   			  }

	   			   	  else
	   			   			  {break; }
	   	 }

	   	 if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
	   					  && local_u8readuser[4]=='0'){

	   		MUART_voidSendByteSynchBlocking ('1');

	      while(local_u8passloop==0){
	    	  local_u8readpass[0]='x';
	    	  local_u8readpass[1]='x';
	    	  local_u8readpass[2]='x';
	    	  local_u8readpass[3]='x';
	    	  local_u8readpass[4]='x';
	    	  local_u8readpass[5]='x';
	    	  local_u8passcounter=0;


	    		 while(1){

	    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
	    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
	    		   			  		  {
	    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
	    		   			  				local_u8passloop=1;

	    		   			  				break;
	    		   			  				}

	    		   			  		local_u8passcounter++;}
	    		   			  		  else
	    		   			  		  {break; }
	    		   		 }

	    		        if(local_u8passloop==1){break;}


	    		   	 if( local_u8readpass[0]=='0' && local_u8readpass[1]=='0'  && local_u8readpass[2]=='0' && local_u8readpass[3]=='0'){

	    		   		  MUART_voidSendByteSynchBlocking ('2');
	    		   		  local_u8passloop=1;
	    		   	      local_u8flag0=1;
	    		   			  }
	    		   			  else{
	    		   				MUART_voidSendByteSynchBlocking ('3');
	    		   				local_u8errorcounter++;
	    		   				if(local_u8errorcounter ==3){


	    		   					while(1){
	    		   					MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
	    		   				 MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);
	    		   					MUART_voidSendByteSynchBlocking ('5');
	    		   					}
	    		   				}


	    		   			  }


	      }

	   			  	  }

	   	 else if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
		   					  && local_u8readuser[4]=='1'){

		   		MUART_voidSendByteSynchBlocking ('1');

		      while(local_u8passloop==0){
		    	  local_u8readpass[0]='x';
		    	  local_u8readpass[1]='x';
		    	  local_u8readpass[2]='x';
		    	  local_u8readpass[3]='x';
		    	  local_u8readpass[4]='x';
		    	  local_u8passcounter=0;



		    		 while(1){

		    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
		    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
		    		   			  		  {
		    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
		    		   			  				local_u8passloop=1;

		    		   			  				break;
		    		   			  				}

		    		   			  		local_u8passcounter++;}
		    		   			  		  else
		    		   			  		  {break; }
		    		   		 }

		    		        if(local_u8passloop==1){break;}


		    		   	 if( local_u8readpass[0]=='1' && local_u8readpass[1]=='1'  && local_u8readpass[2]=='1' && local_u8readpass[3]=='1'){

		    		   		  MUART_voidSendByteSynchBlocking ('2');
		    		   		  local_u8passloop=1;
		    		   	      local_u8flag0=1;
		    		   			  }
		    		   			  else{
		    		   				MUART_voidSendByteSynchBlocking ('3');
		    		   				local_u8errorcounter++;
		    		   				if(local_u8errorcounter ==3){


		    		   					while(1){


		    		   						MUART_voidSendByteSynchBlocking  ('5');
		    		   						    MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
		    		   						     MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);


		    		   					}
		    		   				}


		    		   			  }


		      }

		   			  	  }

	   	 else if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
		   					  && local_u8readuser[4]=='2'){

		   		MUART_voidSendByteSynchBlocking ('1');

		      while(local_u8passloop==0){
		    	  local_u8readpass[0]='x';
		    	  local_u8readpass[1]='x';
		    	  local_u8readpass[2]='x';
		    	  local_u8readpass[3]='x';
		    	  local_u8readpass[4]='x';
		    	  local_u8readpass[5]='x';
		    	  local_u8passcounter=0;


		    		 while(1){

		    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
		    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
		    		   			  		  {
		    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
		    		   			  				local_u8passloop=1;

		    		   			  				break;
		    		   			  				}

		    		   			  		local_u8passcounter++;}
		    		   			  		  else
		    		   			  		  {break; }
		    		   		 }

		    		        if(local_u8passloop==1){break;}


		    		   	 if( local_u8readpass[0]=='2' && local_u8readpass[1]=='2'  && local_u8readpass[2]=='2' && local_u8readpass[3]=='2'){
		    		   		  MUART_voidSendByteSynchBlocking ('2');
		    		   		  local_u8passloop=1;
		    		   	      local_u8flag0=1;
		    		   			  }
		    		   			  else{
		    		   				MUART_voidSendByteSynchBlocking ('3');
		    		   				local_u8errorcounter++;
		    		   				if(local_u8errorcounter ==3){


		    		   					while(1){
		    		   					MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
		    		   				 MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);
		    		   					MUART_voidSendByteSynchBlocking ('5');
		    		   					}
		    		   				}


		    		   			  }


		      }

		   			  	  }
	   	 else if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
		   					  && local_u8readuser[4]=='3'){

		   		MUART_voidSendByteSynchBlocking ('1');

		      while(local_u8passloop==0){
		    	  local_u8readpass[0]='x';
		    	  local_u8readpass[1]='x';
		    	  local_u8readpass[2]='x';
		    	  local_u8readpass[3]='x';
		    	  local_u8readpass[4]='x';
		    	  local_u8readpass[5]='x';
		    	  local_u8passcounter=0;


		    		 while(1){

		    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
		    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
		    		   			  		  {
		    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
		    		   			  				local_u8passloop=1;

		    		   			  				break;
		    		   			  				}

		    		   			  		local_u8passcounter++;}
		    		   			  		  else
		    		   			  		  {break; }
		    		   		 }

		    		        if(local_u8passloop==1){break;}


		    		   	 if( local_u8readpass[0]=='3' && local_u8readpass[1]=='3'  && local_u8readpass[2]=='3' && local_u8readpass[3]=='3'){
		    		   		  MUART_voidSendByteSynchBlocking ('2');
		    		   		  local_u8passloop=1;
		    		   	      local_u8flag0=1;
		    		   			  }
		    		   			  else{
		    		   				MUART_voidSendByteSynchBlocking ('3');
		    		   				local_u8errorcounter++;
		    		   				if(local_u8errorcounter ==3){


		    		   					while(1){
		    		   					MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
		    		   				 MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);
		    		   					MUART_voidSendByteSynchBlocking ('5');
		    		   					}
		    		   				}


		    		   			  }


		      }

		   			  	  }

	   	 else if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
		   					  && local_u8readuser[4]=='4'){

		   		MUART_voidSendByteSynchBlocking ('1');

		      while(local_u8passloop==0){
		    	  local_u8readpass[0]='x';
		    	  local_u8readpass[1]='x';
		    	  local_u8readpass[2]='x';
		    	  local_u8readpass[3]='x';
		    	  local_u8readpass[4]='x';
		    	  local_u8readpass[5]='x';
		    	  local_u8passcounter=0;


		    		 while(1){

		    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
		    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
		    		   			  		  {
		    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
		    		   			  				local_u8passloop=1;

		    		   			  				break;
		    		   			  				}

		    		   			  		local_u8passcounter++;}
		    		   			  		  else
		    		   			  		  {break; }
		    		   		 }

		    		        if(local_u8passloop==1){break;}


		    		   	 if( local_u8readpass[0]=='4' && local_u8readpass[1]=='4'  && local_u8readpass[2]=='4' && local_u8readpass[3]=='4'){
		    		   		  MUART_voidSendByteSynchBlocking ('2');
		    		   		  local_u8passloop=1;
		    		   	      local_u8flag0=1;
		    		   			  }
		    		   			  else{
		    		   				MUART_voidSendByteSynchBlocking ('3');
		    		   				local_u8errorcounter++;
		    		   				if(local_u8errorcounter ==3){


		    		   					while(1){
		    		   					MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
		    		   				 MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);
		    		   					MUART_voidSendByteSynchBlocking ('5');
		    		   					}
		    		   				}


		    		   			  }


		      }

		   			  	  }

	   	 else if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
		   					  && local_u8readuser[4]=='5'){

		   		MUART_voidSendByteSynchBlocking ('1');

		      while(local_u8passloop==0){
		    	  local_u8readpass[0]='x';
		    	  local_u8readpass[1]='x';
		    	  local_u8readpass[2]='x';
		    	  local_u8readpass[3]='x';
		    	  local_u8readpass[4]='x';
		    	  local_u8readpass[5]='x';
		    	  local_u8passcounter=0;


		    		 while(1){

		    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
		    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
		    		   			  		  {
		    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
		    		   			  				local_u8passloop=1;

		    		   			  				break;
		    		   			  				}

		    		   			  		local_u8passcounter++;}
		    		   			  		  else
		    		   			  		  {break; }
		    		   		 }

		    		        if(local_u8passloop==1){break;}


		    		   	 if( local_u8readpass[0]=='5' && local_u8readpass[1]=='5'  && local_u8readpass[2]=='5' && local_u8readpass[3]=='5'){
		    		   		  MUART_voidSendByteSynchBlocking ('2');
		    		   		  local_u8passloop=1;
		    		   	      local_u8flag0=1;
		    		   			  }
		    		   			  else{
		    		   				MUART_voidSendByteSynchBlocking ('3');
		    		   				local_u8errorcounter++;
		    		   				if(local_u8errorcounter ==3){


		    		   					while(1){
		    		   					MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
		    		   				 MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);
		    		   					MUART_voidSendByteSynchBlocking ('5');
		    		   					}
		    		   				}


		    		   			  }


		      }

		   			  	  }

	   	 else if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
		   					  && local_u8readuser[4]=='6'){

		   		MUART_voidSendByteSynchBlocking ('1');

		      while(local_u8passloop==0){
		    	  local_u8readpass[0]='x';
		    	  local_u8readpass[1]='x';
		    	  local_u8readpass[2]='x';
		    	  local_u8readpass[3]='x';
		    	  local_u8readpass[4]='x';
		    	  local_u8readpass[5]='x';
		    	  local_u8passcounter=0;


		    		 while(1){

		    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
		    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
		    		   			  		  {
		    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
		    		   			  				local_u8passloop=1;

		    		   			  				break;
		    		   			  				}

		    		   			  		local_u8passcounter++;}
		    		   			  		  else
		    		   			  		  {break; }
		    		   		 }

		    		        if(local_u8passloop==1){break;}


		    		   	 if( local_u8readpass[0]=='6' && local_u8readpass[1]=='6'  && local_u8readpass[2]=='6' && local_u8readpass[3]=='6'){
		    		   		  MUART_voidSendByteSynchBlocking ('2');
		    		   		  local_u8passloop=1;
		    		   	      local_u8flag0=1;
		    		   			  }
		    		   			  else{
		    		   				MUART_voidSendByteSynchBlocking ('3');
		    		   				local_u8errorcounter++;
		    		   				if(local_u8errorcounter ==3){


		    		   					while(1){
		    		   					MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
		    		   				 MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);
		    		   					MUART_voidSendByteSynchBlocking ('5');
		    		   					}
		    		   				}


		    		   			  }


		      }

		   			  	  }

	   	 else if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
		   					  && local_u8readuser[4]=='7'){

	//	   		MDIO_voidSetPinValue (DIO_PORTB, 0, DIO_HIGH);
		   		MUART_voidSendByteSynchBlocking ('1');

		      while(local_u8passloop==0){
		    	  local_u8readpass[0]='x';
		    	  local_u8readpass[1]='x';
		    	  local_u8readpass[2]='x';
		    	  local_u8readpass[3]='x';
		    	  local_u8readpass[4]='x';
		    	  local_u8readpass[5]='x';
		    	  local_u8passcounter=0;


		    		 while(1){

		    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
		    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
		    		   			  		  {
		    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
		    		   			  				local_u8passloop=1;

		    		   			  				break;
		    		   			  				}

		    		   			  		local_u8passcounter++;}
		    		   			  		  else
		    		   			  		  {break; }
		    		   		 }

		    		        if(local_u8passloop==1){break;}


		    		   	 if( local_u8readpass[0]=='7' && local_u8readpass[1]=='7'  && local_u8readpass[2]=='7' && local_u8readpass[3]=='7'){
		    		   		  MUART_voidSendByteSynchBlocking ('2');
		    		   		  local_u8passloop=1;
		    		   	      local_u8flag0=1;
		    		   			  }
		    		   			  else{
		    		   				MUART_voidSendByteSynchBlocking ('3');
		    		   				local_u8errorcounter++;
		    		   				if(local_u8errorcounter ==3){


		    		   					while(1){
		    		   					MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
		    		   				 MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);
		    		   					MUART_voidSendByteSynchBlocking ('5');
		    		   					}
		    		   				}


		    		   			  }


		      }

		   			  	  }
	   	 else if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
		   					  && local_u8readuser[4]=='8'){

		   		MUART_voidSendByteSynchBlocking ('1');

		      while(local_u8passloop==0){
		    	  local_u8readpass[0]='x';
		    	  local_u8readpass[1]='x';
		    	  local_u8readpass[2]='x';
		    	  local_u8readpass[3]='x';
		    	  local_u8readpass[4]='x';
		    	  local_u8readpass[5]='x';
		    	  local_u8passcounter=0;


		    		 while(1){

		    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
		    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
		    		   			  		  {
		    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
		    		   			  				local_u8passloop=1;

		    		   			  				break;
		    		   			  				}

		    		   			  		local_u8passcounter++;}
		    		   			  		  else
		    		   			  		  {break; }
		    		   		 }

		    		        if(local_u8passloop==1){break;}


		    		   	 if( local_u8readpass[0]=='8' && local_u8readpass[1]=='8'  && local_u8readpass[2]=='8' && local_u8readpass[3]=='8'){
		    		   		  MUART_voidSendByteSynchBlocking ('2');
		    		   		  local_u8passloop=1;
		    		   	      local_u8flag0=1;
		    		   			  }
		    		   			  else{
		    		   				MUART_voidSendByteSynchBlocking ('3');
		    		   				local_u8errorcounter++;
		    		   				if(local_u8errorcounter ==3){


		    		   					while(1){
		    		   					MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
		    		   				 MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);
		    		   					MUART_voidSendByteSynchBlocking ('5');
		    		   					}
		    		   				}


		    		   			  }


		      }

		   			  	  }

	   	 else if(local_u8readuser[0]=='u'&& local_u8readuser[1]=='s'&& local_u8readuser[2]=='e'&& local_u8readuser[3]=='r'
		   					  && local_u8readuser[4]=='9'){

		   		MUART_voidSendByteSynchBlocking ('1');

		      while(local_u8passloop==0){
		    	  local_u8readpass[0]='x';
		    	  local_u8readpass[1]='x';
		    	  local_u8readpass[2]='x';
		    	  local_u8readpass[3]='x';
		    	  local_u8readpass[4]='x';
		    	  local_u8readpass[5]='x';
		    	  local_u8passcounter=0;


		    		 while(1){

		    		   				   local_u8readpass[local_u8passcounter]= MUART_u8ReadByteSynchBlocking ();
		    		   			  		  if(local_u8readpass[local_u8passcounter]!='#')
		    		   			  		  {
		    		   			  			  if(local_u8readpass[local_u8passcounter]=='v'){
		    		   			  				local_u8passloop=1;

		    		   			  				break;
		    		   			  				}

		    		   			  		local_u8passcounter++;}
		    		   			  		  else
		    		   			  		  {break; }
		    		   		 }

		    		        if(local_u8passloop==1){break;}


		    		   	 if( local_u8readpass[0]=='9' && local_u8readpass[1]=='9'  && local_u8readpass[2]=='9' && local_u8readpass[3]=='9'){
		    		   		  MUART_voidSendByteSynchBlocking ('2');
		    		   		  local_u8passloop=1;
		    		   	      local_u8flag0=1;
		    		   			  }
		    		   			  else{
		    		   				MUART_voidSendByteSynchBlocking ('3');
		    		   				local_u8errorcounter++;
		    		   				if(local_u8errorcounter ==3){


		    		   					while(1){
		    		   					MDIO_voidSetPinValue (DIO_PORTB, 3, DIO_HIGH);
		    		   				 MDIO_voidSetPinValue     (DIO_PORTB, 1, DIO_HIGH);
		    		   					MUART_voidSendByteSynchBlocking ('5');
		    		   					}
		    		   				}


		    		   			  }


		      }

		   			  	  }

	   	 else{
	   		MUART_voidSendByteSynchBlocking ('0');

	   	 }

	     while(local_u8flag0==1){
	   			  u8 local_u8action=0;

	   			  local_u8action=  MUART_u8ReadByteSynchBlocking ();
	   			  switch(local_u8action){
	   			  case 'p':
                     // OPEN THE DOOR
	   		      	 MDIO_voidSetPinValue     (DIO_PORTB, 0, DIO_HIGH);

	   			          break;
	   			  case 'c':
                     // CLOSE THE DOOR
	   				 MDIO_voidSetPinValue     (DIO_PORTB, 0, DIO_LOW);

	   			         break;
	   			  case 'h':
	   				  //OPEN THE LIGHT
	   				  MDIO_voidSetPinValue     (DIO_PORTB, 2, DIO_HIGH);
	   				  break;
	   			  case 'l':
	   				  // CLOSE THE LIGHT
	   				  MDIO_voidSetPinValue     (DIO_PORTB, 2, DIO_LOW);
	   				  break;
	   			  case 'n':
	   				  // END THE PROGRAM
	   				  local_u8flag0=0;
	   				  break;
	   			  case 'v': local_u8flag0=0; break;
	   			  default:  MUART_voidSendString ("wrong action\r\n");
	   			  }

	   		  }




	 }


	}

