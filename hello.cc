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

void				CustomLogic();
typedef RZRESULT (*CREATEKEYBOARDCUSTOMGRIDEFFECTS)(ChromaSDK::Keyboard::CUSTOM_GRID_EFFECT_TYPE CustomEffects, RZEFFECTID *pEffectId);

Handle<Value> Method(const Arguments& args) {
  HandleScope scope;
  CustomLogic();
  return scope.Close(String::New("here is some output"));
}

void init(Handle<Object> target) {
  target->Set(String::NewSymbol("methodName"),
      FunctionTemplate::New(Method)->GetFunction());
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
  //This line does not work for some reason
  std::cout << "About to modify keyboard...";
  try{
	  CreateKeyboardCustomGridEffects(Grid, nullptr);  //This line is broken
  }catch(const std::exception &exc) {
     std::cout << exc.what();
  }catch(...){
    std::cout << "Some unknown thing went wrong dangit.";
  }
  std::cout << "Done!";
}


NODE_MODULE(myModuleName, init)
