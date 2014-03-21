#pragma once 
#ifndef WIN32_INPUT_H 
#define WIN32_INPUT_H 
  
#include <vector> 
  
#include <Windows.h> 
#include "Mouse.h" 
#include "Keys.h" 
//#include "WindowsInclude.h" 
  
struct MouseCoords 
{ 
    int x; 
    int y; 
  
    MouseCoords() { } 
  
    MouseCoords(const int x, const int y) 
        : x(x), y(y) { } 
}; 
  
class Input 
  
{ 
public: 
  
    static bool isKeyDown(const Key::Enum key); 
  
    static bool isMouseButtonDown(const Mouse::Enum button); 
  
    static MouseCoords mouseCoords(); 
  
    static int mouseWheel(); 
  
    static MouseCoords relativeMouseCoords(); 

	
  
private: 
  
    typedef std::vector<char> InputData; 
    typedef std::vector<bool> InputStates; 
  
    friend class Window; 
  
    static Input* _instance; 
      
    InputData _inputData; 
    InputStates _keyStates; 
    InputStates _mouseButtonStates; 
    int _mouseX; 
    int _mouseY; 
    int _relativeMouseX; 
    int _relativeMouseY; 
    int _mouseWheel; 
  
    Input(); 
    Input(const Input& input); 
    ~Input(); 
  
    void getRawInputData(const HRAWINPUT inputHandle); 
    void processKeyboardInput(RAWKEYBOARD& inputData); 
    void processMouseInput(const RAWMOUSE& inputData); 
    void processMouseButtonInput(const unsigned int buttonData); 
  
    static void parseKeyCode(RAWKEYBOARD& inputData); 
    static void processRawInput(const HRAWINPUT inputHandle); 
    static void processMouseMovement(const LPARAM inputData); 
  
    Input& operator =(const Input& input); 
}; 
  
#endif