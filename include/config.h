/*
 * config.h
 *
 *  Created on: 2014��3��20��
 *      Author: john
 */

#ifndef CONFIG_H_
#define CONFIG_H_


#define MUM	100

#ifdef BUILD_FENGER_STATIC
	#define FENGER_DLL
#else
	#ifdef BUILD_FENGER_DLL
	#define FENGER_DLL __declspec(dllexport)
	#else
	#define FENGER_DLL __declspec(dllimport)
	#endif
#endif


#endif /* CONFIG_H_ */
