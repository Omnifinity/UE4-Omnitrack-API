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

#include "OmnitrackBPLibrary.h"
#include "Omnitrack.h"


// handle to DLL
void *v_dllHandle;

// storage for calling methods in API
typedef int32(*_getAPIVersionMajor)(); // Declare a method to store the DLL method getAPIVersionMajor.
typedef int32(*_getAPIVersionMinor)();
typedef int32(*_getAPIVersionPatch)();

typedef int32(*_InitializeOmnitrackAPI)();
typedef int32(*_EstablishOmnitrackConnection)(int port, FString trackerName);
typedef int32(*_CloseOmnitrackConnection)();
typedef void(*_UpdateOmnitrack)();
typedef bool(*_IsOmnitrackOnline)();
typedef int32(*_SendHeartBeatToOmnitrack)(uint16 major, uint16 minor, uint16 patch, uint16 platformType);
typedef double(*_GetVX)();
typedef double(*_GetVY)();
typedef double(*_GetVZ)();

_getAPIVersionMajor m_getAPIVersionMajor = NULL;
_getAPIVersionMajor m_getAPIVersionMinor = NULL;
_getAPIVersionMajor m_getAPIVersionPatch = NULL;

_InitializeOmnitrackAPI m_InitializeOmnitrackAPI = NULL;
_EstablishOmnitrackConnection m_EstablishOmnitrackConnection = NULL;
_CloseOmnitrackConnection m_CloseOmnitrackConnection = NULL;

_UpdateOmnitrack m_UpdateOmnitrack = NULL;
_IsOmnitrackOnline m_IsOmnitrackOnline = NULL;
_SendHeartBeatToOmnitrack m_SendHeartBeatToOmnitrack = NULL;

_GetVX m_GetVX = NULL;
_GetVY m_GetVY = NULL;
_GetVZ m_GetVZ = NULL;

// keep track of version
int32 m_verMajor = 0;
int32 m_verMinor = 0;
int32 m_verPatch = 0;


UOmnitrackBPLibrary::UOmnitrackBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

bool UOmnitrackBPLibrary::importDll(FString folder, FString name)
{
	FString filePath = *FPaths::ProjectPluginsDir() + folder + "/" + name;

	if (FPaths::FileExists(filePath))
	{
		v_dllHandle = FPlatformProcess::GetDllHandle(*filePath); // Retrieve the DLL.
		if (v_dllHandle != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("importDll success"));
			return true;
		}
	}
	UE_LOG(LogTemp, Display, TEXT("importDll error. Requested path: %s"), *filePath);
	return false;	// Return an error.
}

void UOmnitrackBPLibrary::freeDll()
{
	if (v_dllHandle != NULL)
	{
		// TODO: Put all to Zero
		m_getAPIVersionMajor = NULL;
		m_getAPIVersionMinor = NULL;
		m_getAPIVersionPatch = NULL;

		FPlatformProcess::FreeDllHandle(v_dllHandle);
		v_dllHandle = NULL;
	}
}

#pragma endregion Unload DLL

#pragma region Import Methods
/*
* Methods to import all methods in the DLL
*/
bool UOmnitrackBPLibrary::importDllMethods() {
	if (!importMethod_InitializeOmnitrackAPI())
		return false;

	if (!importMethod_EstablishOmnitrackConnection())
		return false;

	if (!importMethod_CloseOmnitrackConnection())
		return false;

	if (!importMethod_IsOmnitrackOnline())
		return false;

	if (!importMethod_UpdateOmnitrack())
		return false;

	if (!importMethod_SendHeartbeatToOmnitrack())
		return false;

	if (!importMethod_GetVX())
		return false;

	if (!importMethod_GetVY())
		return false;

	if (!importMethod_GetVZ())
		return false;

	if (!importMethod_GetAPIVersionMajor())
		return false;

	if (!importMethod_GetAPIVersionMinor())
		return false;

	if (!importMethod_GetAPIVersionPatch())
		return false;

	UE_LOG(LogTemp, Display, TEXT("imported all DLL methods."));

	// all good if we reach here
	return true;
}

// Imports the method InitializeOmnitrackAPI from the DLL.
bool UOmnitrackBPLibrary::importMethod_InitializeOmnitrackAPI()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "InitializeOmnitrackAPI";	// Needs to be the exact name of the DLL method.
		m_InitializeOmnitrackAPI = (_InitializeOmnitrackAPI)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_InitializeOmnitrackAPI != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import InitializeOmnitrackAPI success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import InitializeOmnitrackAPI failed"));
			return false;
		}
	}
	return false;	// Return an error.
}

// Imports the method EstablishOmnitrackConnection from the DLL.
bool UOmnitrackBPLibrary::importMethod_EstablishOmnitrackConnection()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "EstablishOmnitrackConnection";	// Needs to be the exact name of the DLL method.
		m_EstablishOmnitrackConnection = (_EstablishOmnitrackConnection)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_InitializeOmnitrackAPI != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import EstablishOmnitrackConnection success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import EstablishOmnitrackConnection failed"));
			return false;
		}
	}
	return false;	// Return an error.
}

// Imports the method CloseOmnitrackConnection from the DLL.
bool UOmnitrackBPLibrary::importMethod_CloseOmnitrackConnection()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "CloseOmnitrackConnection";	// Needs to be the exact name of the DLL method.
		m_CloseOmnitrackConnection = (_CloseOmnitrackConnection)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_CloseOmnitrackConnection != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import CloseOmnitrackConnection success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import CloseOmnitrackConnection failed"));
			return false;
		}
	}
	return false;	// Return an error.
}

// Imports the method UpdateOmnitrack from the DLL.
bool UOmnitrackBPLibrary::importMethod_UpdateOmnitrack()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "UpdateOmnitrack";	// Needs to be the exact name of the DLL method.
		m_UpdateOmnitrack = (_UpdateOmnitrack)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_UpdateOmnitrack != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import UpdateOmnitrack success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import UpdateOmnitrack failed"));
			return false;
		}
	}
	return false;	// Return an error.
}

// Imports the method IsOmnitrackOnline from the DLL.
bool UOmnitrackBPLibrary::importMethod_IsOmnitrackOnline()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "IsOmnitrackOnline";	// Needs to be the exact name of the DLL method.
		m_IsOmnitrackOnline = (_IsOmnitrackOnline)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_IsOmnitrackOnline != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import IsOmnitrackOnline success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import IsOmnitrackOnline failed"));
			return false;
		}
	}
	return false;	// Return an error.
}


// Imports the method SendHeartBeatToOmnitrack from the DLL.
bool UOmnitrackBPLibrary::importMethod_SendHeartbeatToOmnitrack()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "SendHeartbeatToOmnitrack";	// Needs to be the exact name of the DLL method.
		m_SendHeartBeatToOmnitrack = (_SendHeartBeatToOmnitrack)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_SendHeartBeatToOmnitrack != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import SendHeartBeatToOmnitrack success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import SendHeartBeatToOmnitrack failed"));
			return false;
		}
	}
	return false;	// Return an error.
}


// Imports the method GetAPIVersionMajor from the DLL.
bool UOmnitrackBPLibrary::importMethod_GetAPIVersionMajor()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "GetAPIVersionMajor";	// Needs to be the exact name of the DLL method.
		m_getAPIVersionMajor = (_getAPIVersionMajor)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_getAPIVersionMajor != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import GetAPIVersionMajor success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import GetAPIVersionMajor failed"));
			return false;
		}
	}
	return false;	// Return an error.
}

// Imports the method GetAPIVersionMajor from the DLL.
bool UOmnitrackBPLibrary::importMethod_GetAPIVersionMinor()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "GetAPIVersionMinor";	// Needs to be the exact name of the DLL method.
		m_getAPIVersionMinor = (_getAPIVersionMajor)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_getAPIVersionMinor != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import GetAPIVersionMinor success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import GetAPIVersionMinor failed"));
			return false;
		}
	}
	return false;	// Return an error.
}

// Imports the method GetAPIVersionMajor from the DLL.
bool UOmnitrackBPLibrary::importMethod_GetAPIVersionPatch()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "GetAPIVersionPatch";	// Needs to be the exact name of the DLL method.
		m_getAPIVersionPatch = (_getAPIVersionMajor)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_getAPIVersionPatch != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import GetAPIVersionPatch success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import GetAPIVersionPatch failed"));
			return false;
		}
	}
	return false;	// Return an error.
}


// Imports the method GetX from the DLL.
bool UOmnitrackBPLibrary::importMethod_GetVX()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "getX";	// Needs to be the exact name of the DLL method.
		m_GetVX = (_GetVX)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_GetVX != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import GetVX success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import GetVX failed"));
			return false;
		}
	}
	return false;	// Return an error.
}

// Imports the method GetY from the DLL.
bool UOmnitrackBPLibrary::importMethod_GetVY()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "getY";	// Needs to be the exact name of the DLL method.
		m_GetVY = (_GetVY)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_GetVY != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import GetVY success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import GetVY failed"));
			return false;
		}
	}
	return false;	// Return an error.
}

// Imports the method GetZ from the DLL.
bool UOmnitrackBPLibrary::importMethod_GetVZ()
{
	if (v_dllHandle != NULL)
	{
		FString procName = "getVZ";	// Needs to be the exact name of the DLL method.
		m_GetVZ = (_GetVZ)FPlatformProcess::GetDllExport(v_dllHandle, *procName);
		if (m_GetVZ != NULL)
		{
			UE_LOG(LogTemp, Display, TEXT("import GetVZ success."));
			return true;
		}
		else {
			UE_LOG(LogTemp, Display, TEXT("import GetVZ failed"));
			return false;
		}
	}
	return false;	// Return an error.
}

#pragma endregion Import Methods


#pragma region APIMethod Calls

// Calls the method that was imported from the DLL.
int32 UOmnitrackBPLibrary::GetAPIVersionMajor()
{
	if (m_getAPIVersionMajor != NULL)
	{
		unsigned out = unsigned int(m_getAPIVersionMajor()); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return 0;	// Return an error.
}

// Calls the method that was imported from the DLL.
int32 UOmnitrackBPLibrary::GetAPIVersionMinor()
{
	if (m_getAPIVersionMinor != NULL)
	{
		unsigned out = unsigned int(m_getAPIVersionMinor()); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return 0;	// Return an error.
}

// Calls the method that was imported from the DLL.
int32 UOmnitrackBPLibrary::GetAPIVersionPatch()
{
	if (m_getAPIVersionPatch != NULL)
	{
		unsigned out = unsigned int(m_getAPIVersionPatch()); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return 0;	// Return an error.
}

// Initialize Omnitrack API communication
bool UOmnitrackBPLibrary::InitializeOmnitrackAPI() {
	if (m_InitializeOmnitrackAPI != NULL)
	{
		unsigned out = unsigned int(m_InitializeOmnitrackAPI()); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return true;
	}
	return false;
}

// Establish network connection with Omnitrack
bool UOmnitrackBPLibrary::EstablishOmnitrackConnection(int serverPort, FString trackerName) {
	UE_LOG(LogTemp, Display, TEXT("Trying to call EstablishOmnitrackConnection() trackerName: %s port: %d"), *trackerName, serverPort);
	if (m_EstablishOmnitrackConnection != NULL)
	{
		unsigned out = unsigned int(m_EstablishOmnitrackConnection(serverPort, *trackerName)); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		UE_LOG(LogTemp, Display, TEXT("Result: %d"), out);

		return true;
	}
	UE_LOG(LogTemp, Display, TEXT("Result: Fail"));
	return false;
}

// Close the connection with Omnitrack
bool UOmnitrackBPLibrary::CloseOmnitrackConnection() {
	UE_LOG(LogTemp, Display, TEXT("Trying to call CloseOmnitrackConnection()"));
	if (m_CloseOmnitrackConnection != NULL)
	{
		unsigned out = unsigned int(m_CloseOmnitrackConnection()); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		UE_LOG(LogTemp, Display, TEXT("Result: %d"), out);
		return true;
	}
	UE_LOG(LogTemp, Display, TEXT("Result: No method to use"));
	return false;
}

// Run the Omnitrack mainloop each frame to properly receive new data
void UOmnitrackBPLibrary::UpdateOmnitrack() {
	if (m_UpdateOmnitrack != NULL)
	{
		//UE_LOG(LogTemp, Display, TEXT("API CALL: UpdateOmnitrack()"));
		m_UpdateOmnitrack(); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
	}
}

// Check if the treadmill is online and communicating with game
bool UOmnitrackBPLibrary::IsOmnitrackOnline() {
	if (m_IsOmnitrackOnline != NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("API CALL: IsOmnitrackOnline()"));
		bool out = bool(m_IsOmnitrackOnline()); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}

	UE_LOG(LogTemp, Display, TEXT("Result: No method to use"));
	return false;
}

// Extract and fill in version information of the Omnitrack API
bool  UOmnitrackBPLibrary::ExtractAPIVersion() {
	if (v_dllHandle != NULL)
	{
		m_verMajor = GetAPIVersionMajor();
		m_verMinor = GetAPIVersionMinor();
		m_verPatch = GetAPIVersionPatch();
		UE_LOG(LogTemp, Display, TEXT("Extracted API version: .%d.%d.%d"), m_verMajor, m_verMinor, m_verPatch);

		return true;
	}
	return false;
}

// Send heart beat to Omnitrack and notify it which DLL version and platform this game is using
bool UOmnitrackBPLibrary::SendHeartbeatToOmnitrack() {
	if (m_SendHeartBeatToOmnitrack != NULL)
	{
		UE_LOG(LogTemp, Display, TEXT("API CALL: SendHeartBeatToOmnitrack()"));

		if (m_verMajor == 0 || m_verMinor == 0 || m_verPatch == 0) {
			if (!ExtractAPIVersion()) {
				UE_LOG(LogTemp, Display, TEXT("Unable to extract API version"));
			}
		}

		bool out = bool(m_SendHeartBeatToOmnitrack((uint16)m_verMajor, (uint16)m_verMinor, (uint16)m_verPatch, API_Platform_Type)); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return false;
}

float UOmnitrackBPLibrary::GetVX() {
	if (m_GetVX != NULL)
	{
		float out = float(m_GetVX()); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return 0;
}

float UOmnitrackBPLibrary::GetVY() {
	if (m_GetVY != NULL)
	{
		float out = float(m_GetVY()); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return 0;
}

float UOmnitrackBPLibrary::GetVZ() {
	if (m_GetVZ != NULL)
	{
		float out = float(m_GetVZ()); // Call the DLL method with arguments corresponding to the exact signature and return type of the method.
		return out;
	}
	return 0;
}

#pragma endregion API Method Calls

#pragma region User Method Calls

void UOmnitrackBPLibrary::debugMovementData() {
	float vx = GetVX();
	float vy = GetVY();
	float vz = GetVZ();

	UE_LOG(LogTemp, Display, TEXT("vx: %.2f vy: %.2f vz: %.2f"), vx, vy, vz);
}

#pragma endregion User Method Calls
