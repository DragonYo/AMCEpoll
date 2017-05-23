/*******************************************************************************
	Copyright (C) 2017 by Andrew Chang <laplacezhang@126.com>
	Licensed under the LGPL v2.1, see the file COPYING in base directory.
	
	File name: 	utilTimeout.h
	
	Description: 	
	    This file provides common timeout storage service for all types of events. 
			
	History:
		2017-05-07: File created as "utilTimeout.h"

	------------------------------------------------------------------------

	    This library is free software; you can redistribute it and/or modify it 
	under the terms of the GNU Lesser General Public License as published by the 
	Free Software Foundation, version 2.1 of the License. 
	    This library is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
	details. 
	    You should have received a copy of the GNU Lesser General Public License 
	along with this library; if not, see <http://www.gnu.org/licenses/>.
		
********************************************************************************/

#ifndef __UTIL_TIMEOUT_H__
#define __UTIL_TIMEOUT_H__

/* headers */
#include "utilRbTree.h"
#include <time.h>
#include <stdlib.h>

/* ahead declarations */
struct AMCEpollEvent;

#ifndef BOOL
#ifndef _DO_NOT_DEFINE_BOOL
#define BOOL	int
#define FALSE	0
#define TRUE	(!(FALSE))
#endif
#endif

/* data definitions */
/* all data structures should be used INTERNALLY */
struct UtilTimeoutChain {
	BOOL               init_OK;
	struct UtilRbTree  time_obj_chain;		/* key: time --->   value: object list */
	struct UtilRbTree  obj_time_chain;		/* key: object ---> value: time */
};


/* public functions */
int 
	utilTimeout_Init(struct UtilTimeoutChain *chain);
int 
	utilTimeout_Clean(struct UtilTimeoutChain *chain);
int 
	utilTimeout_SetObject(struct UtilTimeoutChain *chain, struct AMCEpollEvent *event, struct timespec inTime);
BOOL 
	utilTimeout_ObjectExists(struct UtilTimeoutChain *chain, struct AMCEpollEvent *event);
int 
	utilTimeout_DelObject(struct UtilTimeoutChain *chain, struct AMCEpollEvent *event);
int 
	utilTimeout_GetSmallestTime(struct UtilTimeoutChain *chain, struct timespec *timeOut, struct AMCEpollEvent **eventOut);
struct timespec  
	utilTimeout_GetSysupTime(void);
struct timespec 
	utilTimeout_TimespecFromMilisecs(long milisecs);
signed long 
	utilTimeout_MinimumSleepMilisecs(struct UtilTimeoutChain *chain);
int 
	utilTimeout_CompareTime(const struct timespec *left, const struct timespec *right);
void 
	utilTimeout_Debug(void);


#endif
/* EOF */

