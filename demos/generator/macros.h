/*!  \file  macros.h
 *	  \brief  This file constains definitions of some usedful macros
 * 
 *   \details   details
 *   \author    Yordan Madzhunkov German Research School for Simulation Sciences GmbH
 *   \version   1.0
 *   \date      05/14/2013 11:54:42 AM
 *   \copyright GNU Public License.
 */
#pragma once

#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);   \
  void operator=(const TypeName&i)
#endif

#ifndef RS 
#define RS __restrict__
#endif

#ifndef MISSING
#define MISSING  \
	cerr << endl; \
	cerr << "Missing Implementation at ";\
	cerr <<  __PRETTY_FUNCTION__ ; \
	cerr << "Line" ;\
	cerr << __LINE__;\
	cerr << endl;
#endif
#define delArr(x) if (x) delete [] x; x = NULL;
#define delObj(x) if (x) delete    x; x = NULL;

#define MIN(a, b) ((a < b) ? a : b)
#define MAX(a, b) ((a > b) ? a : b) 

