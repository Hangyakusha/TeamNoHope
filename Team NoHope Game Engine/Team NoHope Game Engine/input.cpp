#include "input.h" 
  
#include <cassert>  
  
// External 
  
static const unsigned int KEY_COUNT = 256u; 
  
static const unsigned int MOUSE_BUTTONS[] = 
{ 
    RI_MOUSE_LEFT_BUTTON_DOWN, 
    RI_MOUSE_MIDDLE_BUTTON_DOWN, 
    RI_MOUSE_RIGHT_BUTTON_DOWN, 
    RI_MOUSE_BUTTON_4_DOWN, 
    RI_MOUSE_BUTTON_5_DOWN, 
    RI_MOUSE_LEFT_BUTTON_UP, 
    RI_MOUSE_MIDDLE_BUTTON_UP, 
    RI_MOUSE_RIGHT_BUTTON_UP, 
    RI_MOUSE_BUTTON_4_UP, 
    RI_MOUSE_BUTTON_5_UP 
}; 
  
#define MOUSE_BUTTON_COUNT sizeof(MOUSE_BUTTONS) / sizeof(MOUSE_BUTTONS[0]) / 2u 
  
  
// Public 
  
// Static 
  
bool Input::isKeyDown(const Key::Enum key) 
{ 
    return _instance->_keyStates[key]; 
} 
  
bool Input::isMouseButtonDown(const Mouse::Enum button) 
{ 
    return _instance->_mouseButtonStates[button]; 
} 
  
MouseCoords Input::mouseCoords() 
{ 
    return MouseCoords(_instance->_mouseX, _instance->_mouseY); 
} 
  
int Input::mouseWheel() 
{ 
    return _instance->_mouseWheel; 
} 
  
MouseCoords Input::relativeMouseCoords() 
{ 
    const MouseCoords mouseCoords(_instance->_relativeMouseX, _instance->_relativeMouseY); 
    _instance->_relativeMouseX = 0; 
    _instance->_relativeMouseY = 0; 
  
    return mouseCoords; 
} 
  
  
// Private 
  
Input::Input() 
    : _keyStates(KEY_COUNT, false), 
      _mouseButtonStates(MOUSE_BUTTON_COUNT, false), 
      _mouseX(0u), 
      _mouseY(0u), 
      _relativeMouseX(0u), 
      _relativeMouseY(0u), 
      _mouseWheel(0) 
{ 
    assert(_instance == NULL); 
    _instance = this; 
} 
  
Input::~Input() 
{ 
    _instance = NULL; 
} 
  
void Input::getRawInputData(const HRAWINPUT inputHandle) 
{ 
    unsigned int dataSize; 
    unsigned int result = GetRawInputData(inputHandle, RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER)); 
    assert(result == 0u); 
  
    if(_inputData.size() < dataSize) 
        _inputData.resize(dataSize); 
  
    result = GetRawInputData(inputHandle, RID_INPUT, &_inputData.front(), &dataSize, sizeof(RAWINPUTHEADER)); 
    assert(result == dataSize); 
} 
  
void Input::processKeyboardInput(RAWKEYBOARD& inputData) 
{ 
    if(inputData.VKey < KEY_COUNT - 1u) 
    { 
        parseKeyCode(inputData); 
        _keyStates[inputData.VKey] = (inputData.Flags & RI_KEY_BREAK) == 0u; 
    } 
} 
  
void Input::processMouseInput(const RAWMOUSE& inputData) 
{ 
    processMouseButtonInput(inputData.usButtonFlags); 
    _relativeMouseX = static_cast<int>(inputData.lLastX); 
    _relativeMouseY = static_cast<int>(inputData.lLastY); 
  
    if((inputData.usButtonFlags & RI_MOUSE_WHEEL) != 0u) 
        _mouseWheel += static_cast<short>(inputData.usButtonData); 
} 
  
void Input::processMouseButtonInput(const unsigned int buttonData) 
{ 
    for(unsigned int i = 0u; i < MOUSE_BUTTON_COUNT; ++i) 
    { 
        if((buttonData & MOUSE_BUTTONS[i]) != 0u) 
            _mouseButtonStates[i] = true; 
        else if((buttonData & MOUSE_BUTTONS[i + MOUSE_BUTTON_COUNT]) != 0u) 
            _mouseButtonStates[i] = false; 
    } 
} 
  
// Static 
  
Input* Input::_instance = NULL; 
  
void Input::parseKeyCode(RAWKEYBOARD& inputData) 
{ 
    bool isE0BitSet = (inputData.Flags & RI_KEY_E0) != 0u; 
  
    switch(inputData.VKey) 
    { 
        case VK_CLEAR: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad5); 
  
            break; 
  
        case VK_RETURN: 
            if(isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::NumpadEnter); 
  
            break; 
  
        case VK_SHIFT: 
            inputData.VKey = static_cast<unsigned short>(MapVirtualKey(inputData.MakeCode, MAPVK_VSC_TO_VK_EX)); 
            break; 
  
        case VK_CONTROL: 
            if(isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::RightControl); 
  
            break; 
  
        case VK_MENU: 
            if(isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::RightAlt); 
              
            break; 
  
        case VK_PRIOR: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad9); 
  
            break; 
  
        case VK_NEXT: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad3); 
  
            break; 
  
        case VK_END: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad1); 
  
            break; 
  
        case VK_HOME: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad7); 
              
            break; 
  
        case VK_LEFT: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad4); 
  
            break; 
  
        case VK_UP: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad8); 
  
            break; 
  
        case VK_RIGHT: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad6); 
  
            break; 
  
        case VK_DOWN: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad2); 
  
            break; 
  
        case VK_INSERT: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::Numpad0); 
  
            break; 
  
        case VK_DELETE: 
            if(!isE0BitSet) 
                inputData.VKey = static_cast<unsigned short>(Key::NumpadDecimal); 
  
            break; 
  
        default: 
            break; 
    } 
} 
  
void Input::processRawInput(const HRAWINPUT inputHandle) 
{ 
    _instance->getRawInputData(inputHandle); 
    RAWINPUT& inputData = *reinterpret_cast<RAWINPUT*>(&_instance->_inputData.front()); 
  
    switch(inputData.header.dwType) 
    { 
        case RIM_TYPEKEYBOARD: 
            _instance->processKeyboardInput(inputData.data.keyboard); 
            break; 
  
        case RIM_TYPEMOUSE: 
            _instance->processMouseInput(inputData.data.mouse); 
            break; 
  
        default: 
            break; 
    } 
} 
  
void Input::processMouseMovement(const LPARAM inputData) 
{ 
    _instance->_mouseX = static_cast<short>(inputData & 0xFFFF); 
    _instance->_mouseY = static_cast<short>(inputData >> 16); 
}