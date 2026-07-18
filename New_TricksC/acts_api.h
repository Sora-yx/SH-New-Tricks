
#ifndef _ACTIONSAPI_H
#define __ACTIONSAPI_H_H
#include <vector>

#ifdef __cplusplus
#include <cstddef>
#include <cstdint>
#else
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#endif



#ifdef ACTIONS_API
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif


enum charaType
{
	speedType,
	flyType,
	powerType
};


#ifdef __cplusplus
extern "C"
{
#endif


	/*@brief Register a new mode for a character.
	*
	* Return the new ID of the mode (action) if success, otherwise -1.
	* @param charaType: Specify the type of the character (0 = speed, 1 = fly, 2 = power).
	*/
	API int32_t ActExp_RegisterNewCharacterMode(charaType type);

	/*@brief Register a new smode for a character.
	*
	* Return the new ID of the smode if success, otherwise -1.
	* @param charaType: Specify the type of the character (0 = speed, 1 = fly, 2 = power).
	*/
	API int32_t ActExp_RegisterNewCharacterSMode(charaType type);


	/*@brief Register a new team play mode for the Team.
	*
	* Return the new ID of the team play mode if success, otherwise -1.
	*/
	API int32_t ActExp_RegisterNewTeamPlayMode();

	/*@brief Register a new last team play mode for the Team.
	*
	* Return the new ID of the last team play mode if success, otherwise -1.
	*/
	API int32_t ActExp_RegisterNewLastTeamPlayMode();


#ifdef __cplusplus
}
#endif

#undef API

#endif