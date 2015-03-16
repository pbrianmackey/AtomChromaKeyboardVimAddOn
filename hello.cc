#include <node.h>

#include "stdafx.h"
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include "RazerChromaPeakMeter.h"
#include "RzErrors.h"
#include "RzChromaSDKTypes.h"
#include <iostream>

using namespace v8;
using namespace ChromaSDK::Keyboard;

//Global variables
HMODULE hModule = NULL;                         // Chroma SDK module handle
const COLORREF RED = RGB(255,0,0);
IAudioMeterInformation *pMeterInfo = NULL;

#ifdef _WIN64
#define CHROMASDKDLL        _T("RzChromaSDK64.dll")
#else
#define CHROMASDKDLL        _T("RzChromaSDK.dll")
#endif

typedef RZRESULT (*INIT)(void);
/*
typedef RZRESULT (*UNINIT)(void);
typedef RZRESULT (*CREATEKEYBOARDCUSTOMGRIDEFFECTS)(ChromaSDK::Keyboard::CUSTOM_GRID_EFFECT_TYPE CustomEffects, RZEFFECTID *pEffectId);
typedef RZRESULT (*CREATEMOUSECUSTOMEFFECTS)(ChromaSDK::Mouse::CUSTOM_EFFECT_TYPE CustomEffect, RZEFFECTID *pEffectId);
typedef RZRESULT (*DELETEEFFECT)(RZEFFECTID EffectId);
typedef RZRESULT (*SETEFFECT)(RZEFFECTID EffectId);*/

//forward declarations
void        InitStuff();
void				CustomLogic();
typedef RZRESULT (*CREATEKEYBOARDCUSTOMGRIDEFFECTS)(ChromaSDK::Keyboard::CUSTOM_GRID_EFFECT_TYPE CustomEffects, RZEFFECTID *pEffectId);

Handle<Value> Method(const Arguments& args) {
  HandleScope scope;
  InitStuff();
  CustomLogic();
  return scope.Close(String::New("here is some output"));
}

void init(Handle<Object> target) {
  target->Set(String::NewSymbol("methodName"),
      FunctionTemplate::New(Method)->GetFunction());
}

void InitStuff()
{
  hModule = LoadLibrary(CHROMASDKDLL);
  if(hModule)
  {
      INIT Init = (INIT)GetProcAddress(hModule, "Init");
      if(Init)
      {
        Init();
      }
  }
  /*
  CoInitialize(NULL);

    // Get enumerator for audio endpoint devices.
    IMMDeviceEnumerator *pEnumerator = NULL;
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
                                  NULL, CLSCTX_INPROC_SERVER,
                                  __uuidof(IMMDeviceEnumerator),
                                  (void**)&pEnumerator);

    if(FAILED(hr)) goto Exit;

    // Get peak meter for default audio-rendering device.
    IMMDevice *pDevice = NULL;
    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

    if(FAILED(hr)) goto Exit;

    hr = pDevice->Activate(__uuidof(IAudioMeterInformation),
                           CLSCTX_ALL, NULL, (void**)&pMeterInfo);

    if(FAILED(hr)) goto Exit;

    if(pMeterInfo)
    {
        //SetTimer(hWnd, 1, 100, NULL);
    }

Exit:

    if(pDevice)
    {
        pDevice->Release();
        pDevice = NULL;
    }

    if(pEnumerator)
    {
        pEnumerator->Release();
        pEnumerator = NULL;
    }*/  //I dont think I need any of this
}

void CustomLogic()
{
	std::cout << "Hello World!";
	CREATEKEYBOARDCUSTOMGRIDEFFECTS CreateKeyboardCustomGridEffects = (CREATEKEYBOARDCUSTOMGRIDEFFECTS)GetProcAddress(hModule, "CreateKeyboardCustomGridEffects");

	CUSTOM_GRID_EFFECT_TYPE Grid = {};

  // Presets
  Grid.Key[4][18] = RED;
	int r = rand() % 255;
	int g = rand() % 255;
	int b = rand() % 255;
	Grid.Key[4][18] = RGB(r,g,b);

	int ROWS = 6;
	int COLUMNS = 22;
	for(int i = 0; i < ROWS; i++)
	{
		int r = rand() % 255;
		int g = rand() % 255;
		int b = rand() % 255;


		for(int j = 0; j < COLUMNS; j++)
		{
			Grid.Key[i][j] = RGB(r,g,b);
		}

	}

  try{
	  CreateKeyboardCustomGridEffects(Grid, nullptr);//No exception, keyboard is not changing either
    std::cout << "modified keyboard. Sleeping thread";
    /*Sleep(4000);
    std::cout << "done sleeping.";*/
  }catch(const std::exception &exc) {
     std::cout << exc.what();
  }catch(...){
    std::cout << "Some unknown thing went wrong dangit.";
  }
  std::cout << "Done!";
}


NODE_MODULE(myModuleName, init)
