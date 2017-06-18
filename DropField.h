#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <CString>
#include <string>
#include "resource.h"
#include "log.h"

class Drop_Field_class{
public:
	int drop_field(int field_id[],int length);
	Log log;
};