#pragma once  // Ensures the header file is included only once during compilation

#include <iostream>  // For input and output functionalities
#include "clsUser.h"  // For managing user details

// Global variable to store the currently logged-in user
clsUser CurrentUser = clsUser::Find("", "");

// Global variable to track the number of allowed login attempts
short LoginTrials = 3;
