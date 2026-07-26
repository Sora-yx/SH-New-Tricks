
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

	/*@brief Register a new animation for a character.
	*
	* Return 0 if success, otherwise -1.
	* @param chara: specify the character that will use this animation.
	* @param animName: specify the animation name, this is mainly for debugging purpose.
	* @param mtnInfo: specify the information of the animation such as its type, the speed etc, see PL_MOTION struct for more info.
	* @param animData: The actual animation data from the loaded file, these data are returned when you load an animation using the function ONEFILE::OneFileLoadHAnimation.
	* @param outAnimID: Out parameter, pass a variable that will get the new animation ID from the anim list.
	* @param outAnimFileID: Out parameter, pass a variable that will get the new animation File ID from the anim list (player_motions).
	*/
	API int32_t ActExp_RegisterNewAnimation(Character chara, const char* animName, PL_MOTION* mtnInfo, RtAnimAnimation* animData, uint32_t* outAnimID, uint32_t* outAnimFileID);

	/*@brief Get the new animations list of a specific character.
	*
	* Return a PL_MOTION pointer of the animation list if success, otherwise nullptr.
	* @param chara: specify the character.
	*/
	API PL_MOTION* ActExp_GetNewCharacterAnimationList(const Character chara);

	/*@brief Get the new animations files list (player_motions).
	*
	* Return a MML_MOTIONTABLE pointer of the list if success, otherwise nullptr.
	*/
	API MML_MOTIONTABLE* ActExp_GetNewPlayerMotionList();

	/*@brief Get the next reserved animation index, useful if you have to build an animation list and need to know in advance
	the anim index, such as a series of animations that use the "next anim" feature (ex flip1 -> flip2 -> flip3, 3 different anims.)
	*
	* Return the next anim index if success, otherwise -1.
	* @param chara: specify the character.
	*/
	API int ActExp_GetNextAvailableAnimID(const Character chara);

	/*@brief Get the next reserved animation file index (player_motions), useful if you have to build an animation list and need to know in advance
	the anim file index.
	*
	* Return the next anim file index if success, otherwise -1.
	*/
	API int ActExp_GetNextAvailableAnimFileID();


#ifdef __cplusplus
}
#endif

#undef API

#endif