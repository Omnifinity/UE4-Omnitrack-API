/*
   Copyright 2019-2020 MSE Omnifinity AB
   The code below is part of the Omnitrack Unreal API

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
 */

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "OmnitrackBPLibrary.generated.h"



/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UOmnitrackBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	#pragma region Method Referencing

		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importDll(FString folder, FString name);

		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static void freeDll();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importDllMethods();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_InitializeOmnitrackAPI();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_EstablishOmnitrackConnection();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_CloseOmnitrackConnection();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_UpdateOmnitrack();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_IsOmnitrackOnline();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_SendHeartbeatToOmnitrack();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_GetAPIVersionMajor();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_GetAPIVersionMinor();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_GetAPIVersionPatch();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_GetVX();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_GetVY();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool importMethod_GetVZ();
	
	#pragma endregion Method Referencing
	
	#pragma region API Calls
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static int32 GetAPIVersionMajor();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static int32 GetAPIVersionMinor();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static int32 GetAPIVersionPatch();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool InitializeOmnitrackAPI();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool EstablishOmnitrackConnection(int serverPort, FString trackerName);
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool CloseOmnitrackConnection();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static void UpdateOmnitrack();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool IsOmnitrackOnline();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool ExtractAPIVersion();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static bool SendHeartbeatToOmnitrack();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static float GetVX();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static float GetVY();
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static float GetVZ();
	
	#pragma endregion API Calls
	
	#pragma region Omnitrack Variables
		// 2 == Unreal. Do not edit.
		static const uint16 API_Platform_Type = 2;
	#pragma endregion Omnitrack Variables
	
	#pragma region Omnitrack Other Method Calls
	
		UFUNCTION(BlueprintCallable, Category = "Omnitrack Interface")
			static void debugMovementData();
	
	#pragma endregion Omnitrack Other Method Calls
};