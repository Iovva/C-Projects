#ifndef TESTE_H_
#define TESTE_H_

#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "service.h"
#include "validators.h"

// teste pentru validatori
void teste_validators();

// teste pentru repository
void teste_repository();

//teste pentru service
void teste_service();

// lanseaza toate testele
void teste_all();

#endif