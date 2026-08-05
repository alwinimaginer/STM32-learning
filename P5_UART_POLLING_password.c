/*
 * password.c
 *
 *  Created on: 09-Jul-2026
 *      Author: Lenovo
 */
#include "password.h"
#include <string.h>

typedef enum {
	PASSWORD_ERROR = 0,
	CORRECT_PASSWORD
}PasswordStatus;

uint8_t Password_Check(const char *Userpassword){

	const char Correctpassword[] = "stm32";

	if(strcmp(Userpassword,Correctpassword) == 0){
		return CORRECT_PASSWORD;
	}
	return PASSWORD_ERROR;
}

