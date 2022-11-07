#include "Input.h"
#include <GLFW/glfw3.h>
#include <windows.h>
#include <stdexcept>
#include <iostream>
#include <fstream>

#define keyID data[0].kv
#define hatId data[0].i
#define hdirection data[1].hd
#define stickID data[0].i
#define sdirection data[1].sd
#define buttonID data[0].i
#define mouseAxis data[0].ma

Input::KeyboardLayout Input::keyboardLayout;
std::vector<Input::Instance> Input::globalInstances;
std::vector<Input::KeyNotify> Input::keyNotifs;
std::vector<Input::StickNotify> Input::mouseAxisNotifs;
Input::KeyNotifyFinder Input::notifFinder;
Input::StickNotifyFinder Input::stickNotifFinder;
Notify Input::eventExecutor;
std::vector<Input::JoystickDevice> Input::joystickDevices;
Input::KeyNotifyFinder::Device* Input::listener;
Input::DeviceID Input::lastUsedDevice;
int Input::maxButtons;
int Input::maxHats;
int Input::maxSticks;
Input::MousePos Input::mousePos;
Input::MousePos Input::lastMouseDelta;

std::string Input::Key::KeyToString() const
{
	const char* kName = glfwGetKeyName(keyID, 0);
	if (kName) return kName;
	switch (keyID)
	{
	case Input::KeyVal::SPACE: return "space";
	case Input::KeyVal::APOSTROPHE: return "'";
	case Input::KeyVal::COMMA: return ",";
	case Input::KeyVal::MINUS: return "-";
	case Input::KeyVal::PERIOD: return ".";
	case Input::KeyVal::SLASH: return "/";
	case Input::KeyVal::NUM0: return "num0";
	case Input::KeyVal::NUM1: return "num1";
	case Input::KeyVal::NUM2: return "num2";
	case Input::KeyVal::NUM3: return "num3";
	case Input::KeyVal::NUM4: return "num4";
	case Input::KeyVal::NUM5: return "num5";
	case Input::KeyVal::NUM6: return "num6";
	case Input::KeyVal::NUM7: return "num7";
	case Input::KeyVal::NUM8: return "num8";
	case Input::KeyVal::NUM9: return "num9";
	case Input::KeyVal::COLON: return ";";
	case Input::KeyVal::SEMICOLON: return ":";
	case Input::KeyVal::LESSER: return "<";
	case Input::KeyVal::EQUAL: return "=";
	case Input::KeyVal::A: return "A";
	case Input::KeyVal::B: return "B";
	case Input::KeyVal::C: return "C";
	case Input::KeyVal::D: return "D";
	case Input::KeyVal::E: return "E";
	case Input::KeyVal::F: return "F";
	case Input::KeyVal::G: return "G";
	case Input::KeyVal::H: return "H";
	case Input::KeyVal::I: return "I";
	case Input::KeyVal::J: return "J";
	case Input::KeyVal::K: return "K";
	case Input::KeyVal::L: return "L";
	case Input::KeyVal::M: return "M";
	case Input::KeyVal::N: return "N";
	case Input::KeyVal::O: return "O";
	case Input::KeyVal::P: return "P";
	case Input::KeyVal::Q: return "Q";
	case Input::KeyVal::R: return "R";
	case Input::KeyVal::S: return "S";
	case Input::KeyVal::T: return "T";
	case Input::KeyVal::U: return "U";
	case Input::KeyVal::V: return "V";
	case Input::KeyVal::W: return "W";
	case Input::KeyVal::X: return "X";
	case Input::KeyVal::Y: return "Y";
	case Input::KeyVal::Z: return "Z";
	case Input::KeyVal::LEFT_BRACKET: return "[";
	case Input::KeyVal::BACKSLASH: return "\\";
	case Input::KeyVal::RIGHT_BRACKET: return "]";
	case Input::KeyVal::GRAVE_ACCENT: return "`";
	case Input::KeyVal::WORLD_1: return "W1";
	case Input::KeyVal::WORLD_2: return "W2";
	case Input::KeyVal::ESCAPE: return "esc";
	case Input::KeyVal::ENTER: return "enter";
	case Input::KeyVal::TAB: return "tab";
	case Input::KeyVal::BACKSPACE: return "backspace";
	case Input::KeyVal::INSERT: return "insert";
	case Input::KeyVal::DEL: return "delete";
	case Input::KeyVal::RIGHT: return "right";
	case Input::KeyVal::LEFT: return "left";
	case Input::KeyVal::DOWN: return "down";
	case Input::KeyVal::UP: return "up";
	case Input::KeyVal::PAGE_UP: return "pgup";
	case Input::KeyVal::PAGE_DOWN: return "pgdown";
	case Input::KeyVal::HOME: return "home";
	case Input::KeyVal::END: return "end";
	case Input::KeyVal::CAPS_LOCK: return "capslock";
	case Input::KeyVal::SCROLL_LOCK: return "scrolllock";
	case Input::KeyVal::NUM_LOCK: return "numlock";
	case Input::KeyVal::PRINT_SCREEN: return "printscreen";
	case Input::KeyVal::PAUSE: return "pause";
	case Input::KeyVal::F1: return "F1";
	case Input::KeyVal::F2: return "F2";
	case Input::KeyVal::F3: return "F3";
	case Input::KeyVal::F4: return "F4";
	case Input::KeyVal::F5: return "F5";
	case Input::KeyVal::F6: return "F6";
	case Input::KeyVal::F7: return "F7";
	case Input::KeyVal::F8: return "F8";
	case Input::KeyVal::F9: return "F9";
	case Input::KeyVal::F10: return "F10";
	case Input::KeyVal::F11: return "F11";
	case Input::KeyVal::F12: return "F12";
	case Input::KeyVal::F13: return "F13";
	case Input::KeyVal::F14: return "F14";
	case Input::KeyVal::F15: return "F15";
	case Input::KeyVal::F16: return "F16";
	case Input::KeyVal::F17: return "F17";
	case Input::KeyVal::F18: return "F18";
	case Input::KeyVal::F19: return "F19";
	case Input::KeyVal::F20: return "F20";
	case Input::KeyVal::F21: return "F21";
	case Input::KeyVal::F22: return "F22";
	case Input::KeyVal::F23: return "F23";
	case Input::KeyVal::F24: return "F24";
	case Input::KeyVal::F25: return "F25";
	case Input::KeyVal::KP_0: return "numpad0";
	case Input::KeyVal::KP_1: return "numpad1";
	case Input::KeyVal::KP_2: return "numpad2";
	case Input::KeyVal::KP_3: return "numpad3";
	case Input::KeyVal::KP_4: return "numpad4";
	case Input::KeyVal::KP_5: return "numpad5";
	case Input::KeyVal::KP_6: return "numpad6";
	case Input::KeyVal::KP_7: return "numpad7";
	case Input::KeyVal::KP_8: return "numpad8";
	case Input::KeyVal::KP_9: return "numpad9";
	case Input::KeyVal::KP_DECIMAL: return "numpaddec";
	case Input::KeyVal::KP_DIVIDE: return "numpad/";
	case Input::KeyVal::KP_MULTIPLY: return "numpad*";
	case Input::KeyVal::KP_SUBTRACT: return "numpad-";
	case Input::KeyVal::KP_ADD: return "numpad+";
	case Input::KeyVal::KP_ENTER: return "numpadenter";
	case Input::KeyVal::KP_EQUAL: return "numpad=";
	case Input::KeyVal::LEFT_SHIFT: return "LShift";
	case Input::KeyVal::LEFT_CONTROL: return "LCtrl";
	case Input::KeyVal::LEFT_ALT: return "LAlt";
	case Input::KeyVal::LEFT_SUPER: return "LSup";
	case Input::KeyVal::RIGHT_SHIFT: return "RShift";
	case Input::KeyVal::RIGHT_CONTROL: return "RCtrl";
	case Input::KeyVal::RIGHT_ALT: return "RAlt";
	case Input::KeyVal::RIGHT_SUPER: return "RSup";
	case Input::KeyVal::MENU: return "Menu";
	case Input::KeyVal::MOUSE0: return "leftclick";
	case Input::KeyVal::MOUSE1: return "rightclick";
	case Input::KeyVal::MOUSE2: return "middleclick";
	case Input::KeyVal::MOUSEWUP: return "wheelup";
	case Input::KeyVal::MOUSEWDOWN: return "wheeldown";
	case Input::KeyVal::MOUSEWLEFT: return "wheelleft";
	case Input::KeyVal::MOUSEWRIGHT: return "wheelright";
	default: return "unknown";
	}
}

std::string Input::Key::HatToString() const
{
	std::string h = std::string("Hat") + std::to_string(hatId) + " ";
	std::string d;
	switch (hdirection)
	{
	case Input::HatDirection::Up:
		d = "up";
		break;
	case Input::HatDirection::Right:
		d = "right";
		break;
	case Input::HatDirection::Down:
		d = "down";
		break;
	case Input::HatDirection::Left:
		d = "left";
		break;
	}
	return h + d;
}

std::string Input::Key::StickToString() const
{
	std::string s = std::string("Stick") + std::to_string(stickID) + " ";
	std::string d;
	switch (sdirection)
	{
	case Input::StickDirection::Forward:
		d = "forward";
		break;
	case Input::StickDirection::Backward:
		d = "backward";
		break;
	}
	return s + d;
}

std::string Input::Key::ButtonToString() const
{
	return std::string("Button ") + std::to_string(buttonID);
}

void Input::Action::KeyCallback(Input::Key& key, Input::Mode _mode)
{
	bool pressed = _mode == Input::Mode::Press;
	KeyStates[key] = pressed;

	if (pressed)
		for (auto& keyState : KeyStates)
		{
			bool isK = keyState.first == key;
			if (!isK && !keyState.second)
			{
				pressed = false;
				break;
			}
		}

	if (wasPressed && !pressed)
	{
		Input::eventExecutor.Bind(this, &Input::Action::ExecuteReleased);
		Input::eventExecutor.Unbind(this, &Input::Action::ExecuteHold);
	}
	else if (!wasPressed && pressed)
	{
		Input::eventExecutor.Bind(this, &Input::Action::ExecutePressed);
		Input::eventExecutor.Bind(this, &Input::Action::ExecuteHold);
	}

	wasPressed = pressed;
}

void Input::Action::SetKeys(std::list<Input::Key>& keys)
{
	ClearKeys();

	for (Key& key : keys)
	{
		KeyStates[key] = false;
	}

	Rebind();
}

void Input::Action::SetKeys(std::vector<Input::Key>& keys)
{
	ClearKeys();

	for (Key& key : keys)
	{
		KeyStates[key] = false;
	}

	Rebind();
}

void Input::Action::ClearKeys()
{
	Unbind();
	KeyStates.clear();
}

void Input::Action::Unbind()
{
	Input::eventExecutor.Unbind(this, &Input::Action::ExecuteHold);
	Input::eventExecutor.Unbind(this, &Input::Action::ExecutePressed);
	Input::eventExecutor.Unbind(this, &Input::Action::ExecuteReleased);
	for (auto key : KeyStates)
	{
		(*dNotifFinder)[key.first].Unbind(this, &Input::Action::KeyCallback);
	}
}

void Input::Action::Rebind()
{
	for (auto& key : KeyStates)
	{
		(*dNotifFinder)[key.first].Bind(this, &Input::Action::KeyCallback);
	}
}

std::string Input::Action::GetKeyString()
{
	std::string keyStr = "";

	int i = 0;
	for (auto& key : KeyStates)
	{
		if (i != 0) keyStr += " + ";
		keyStr += key.first.ToString();
		++i;
	}

	return keyStr;
}

void Input::Action::ExecuteHold()
{
	action[Input::Mode::Hold]();
}

void Input::Action::ExecutePressed()
{
	action[Input::Mode::Press]();
	Input::eventExecutor.Unbind(this, &Input::Action::ExecutePressed);
}

void Input::Action::ExecuteReleased()
{
	action[Input::Mode::Release]();
	Input::eventExecutor.Unbind(this, &Input::Action::ExecuteReleased);
}

void Input::JoystickDevice::ConfigureAsAny()
{
	name = "virtual Any Joystick";
	for (int x = stickStatusNotifs[Forward].size(); x < maxSticks; ++x)
	{
		stickStatusNotifs[Forward].push_back(Input::KeyNotify());
		stickStatusNotifs[Backward].push_back(Input::KeyNotify());

		stickValueNotifs[Forward].push_back(Input::StickNotify());
		stickValueNotifs[Backward].push_back(Input::StickNotify());
	}
	for (int x = ButtonNotifs.size(); x < maxButtons; ++x)
	{
		ButtonNotifs.push_back(Input::KeyNotify());
	}
	for (int x = hatNotifs[Up].size(); x < maxHats; ++x)
	{
		hatNotifs[Up].push_back(Input::KeyNotify());
		hatNotifs[Right].push_back(Input::KeyNotify());
		hatNotifs[Down].push_back(Input::KeyNotify());
		hatNotifs[Left].push_back(Input::KeyNotify());
	}
}

void Input::JoystickDevice::ConfigureJoystick()
{
	if (!connected) return;

	if (id == JoystickID::Any)
	{
		ConfigureAsAny();
		return;
	}

	std::string tmpName = glfwGetJoystickName(id);

	if (tmpName == name) return;

	int axisCount;
	glfwGetJoystickAxes(id, &axisCount);
	if (axisCount > maxSticks) maxSticks = axisCount;
	int buttonCount;
	glfwGetJoystickButtons(id, &buttonCount);
	if (buttonCount > maxButtons) maxButtons = buttonCount;
	int hatCount;
	glfwGetJoystickHats(id, &hatCount);
	if (hatCount > maxHats) maxHats = hatCount;

	name = tmpName;
	deadZones.clear();
	stickValues.clear();
	buttonValues.clear();
	hatValues.clear();
	stickStatusNotifs[Forward].clear();
	stickStatusNotifs[Backward].clear();
	ButtonNotifs.clear();
	hatNotifs[Up].clear();
	hatNotifs[Right].clear();
	hatNotifs[Down].clear();
	hatNotifs[Left].clear();

	for (int x = 0; x < axisCount; ++x)
	{
		stickValues.push_back(0);
		deadZones.push_back(0.25f);

		stickStatusNotifs[Forward].push_back(Input::KeyNotify());
		stickStatusNotifs[Backward].push_back(Input::KeyNotify());

		stickValueNotifs[Forward].push_back(Input::StickNotify());
		stickValueNotifs[Backward].push_back(Input::StickNotify());
	}

	for (int x = 0; x < buttonCount; ++x)
	{
		buttonValues.push_back(false);
		ButtonNotifs.push_back(Input::KeyNotify());
	}

	for (int x = 0; x < hatCount; ++x)
	{
		hatValues.push_back(GLFW_HAT_CENTERED);
		hatNotifs[Up].push_back(Input::KeyNotify());
		hatNotifs[Right].push_back(Input::KeyNotify());
		hatNotifs[Down].push_back(Input::KeyNotify());
		hatNotifs[Left].push_back(Input::KeyNotify());
	}
}

void Input::JoystickDevice::UpdateValues()
{
	if (!connected) return;

	UpdateSticks();
	UpdateButtons();
	UpdateHats();
}

void Input::JoystickDevice::UpdateSticks()
{
	JoystickDeviceID jID(id);
	JoystickDeviceID jIDAny(Any);
	int axisCount;
	const float* axis = glfwGetJoystickAxes(id, &axisCount);
	for (int x = 0; x < axisCount; ++x)
	{
		if (axis[x] != stickValues[x])
		{
			Key kf(x, Forward);
			Key kb(x, Backward);
			bool lastFor = stickValues[x] > deadZones[x];
			bool lastBak = -stickValues[x] > deadZones[x];
			bool currentFor = axis[x] > deadZones[x];
			bool currentBak = -axis[x] > deadZones[x];
			stickNotifFinder[jID][kf](kf, axis[x], stickValues[x]);
			stickNotifFinder[jID][kb](kb, -axis[x], -stickValues[x]);
			stickNotifFinder[jIDAny][kf](kf, axis[x], stickValues[x]);
			stickNotifFinder[jIDAny][kb](kb, -axis[x], -stickValues[x]);
			if (lastFor != currentFor)
			{
				if (lastFor)
				{
					notifFinder[jID][kf](kf, Input::Mode::Release);
					notifFinder[jIDAny][kf](kf, Input::Mode::Release);
				}
				else
				{
					notifFinder[jID][kf](kf, Input::Mode::Press);
					notifFinder[jIDAny][kf](kf, Input::Mode::Press);
				}
			}
			if (lastBak != currentBak)
			{
				if (lastBak)
				{
					notifFinder[jID][kb](kb, Input::Mode::Release);
					notifFinder[jIDAny][kb](kb, Input::Mode::Release);
				}
				else
				{
					notifFinder[jID][kb](kb, Input::Mode::Press);
					notifFinder[jIDAny][kb](kb, Input::Mode::Press);
				}
			}
			stickValues[x] = axis[x];
		}
	}
}

void Input::JoystickDevice::UpdateButtons()
{
	JoystickDeviceID jID(id);
	JoystickDeviceID jIDAny(Any);
	int buttonCount;
	const unsigned char* button = glfwGetJoystickButtons(id, &buttonCount);
	for (int x = 0; x < buttonCount; ++x)
	{
		bool pressed = button[x] == GLFW_PRESS;
		if (pressed != buttonValues[x])
		{
			Key k(x);
			if (pressed && !buttonValues[x])
			{
				notifFinder[jID][k](k, Input::Mode::Press);
				notifFinder[jIDAny][k](k, Input::Mode::Press);
			}
			else if (!pressed && buttonValues[x])
			{
				notifFinder[jID][k](k, Input::Mode::Release);
				notifFinder[jIDAny][k](k, Input::Mode::Release);
			}
			buttonValues[x] = pressed;
		}
	}
}

void Input::JoystickDevice::UpdateHats()
{
	JoystickDeviceID jID(id);
	JoystickDeviceID jIDAny(Any);
	int hatCount;
	const unsigned char* hat = glfwGetJoystickHats(id, &hatCount);
	for (int x = 0; x < hatCount; ++x)
	{
		if (hatValues[x] != hat[x])
		{
			unsigned char diffMask = hatValues[x] ^ hat[x];
			unsigned char wasPressedMask = diffMask & hatValues[x];
			unsigned char isPressedMask = diffMask & hat[x];

			if (wasPressedMask || isPressedMask)
			{
				for (int i = 0; i < 4; ++i)
				{
					Key k(x, (Input::HatDirection)i);
					if ((wasPressedMask >> i) & 1)
					{
						notifFinder[jID][k](k, Input::Mode::Release);
						notifFinder[jIDAny][k](k, Input::Mode::Release);
					}
					if ((isPressedMask >> i) & 1)
					{
						notifFinder[jID][k](k, Input::Mode::Press);
						notifFinder[jIDAny][k](k, Input::Mode::Press);
					}
				}
			}
			hatValues[x] = hat[x];
		}
	}
}

void Input::Init()
{
	maxButtons = 64;
	maxHats = 64;
	maxSticks = 64;
	for (int i = 0; i < KeyVal::Count; ++i)
		keyNotifs.push_back(Input::KeyNotify());

	mouseAxisNotifs.push_back(Input::StickNotify());
	mouseAxisNotifs.push_back(Input::StickNotify());

	GLFWwindow* window = glfwGetCurrentContext();
	std::string testKeyboardLayout;
	if ((testKeyboardLayout = glfwGetKeyName(Input::KeyVal::W, 0)) == "w")
	{
		keyboardLayout = KeyboardLayout::QWERTY;
	}
	else if ((testKeyboardLayout = glfwGetKeyName(Input::KeyVal::A, 0)) == "a")
	{
		keyboardLayout = KeyboardLayout::DVORAK;
	}
	else if (testKeyboardLayout == "q")
	{
		keyboardLayout = KeyboardLayout::AZERTY;
	}
	else
	{
		keyboardLayout = KeyboardLayout::UNKNOWNKEYBOARD;
	}
	lastUsedDevice = KeyBoardDeviceID();
	listener = nullptr;
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	CheckJoysticks();
	UpdateJoysticks();
	glfwSetKeyCallback(window, &Input::Key_Callback);
	glfwSetJoystickCallback(&Input::JoystickConnection_Callback);
	glfwSetMouseButtonCallback(window, &Input::MouseButton_Callback);
	glfwSetScrollCallback(window, &Input::MouseWheel_Callback);
}

void Input::CheckJoysticks()
{
	for (int i = JoystickID::J0; i <= JoystickID::Any; ++i)
	{
		joystickDevices.push_back(JoystickDevice());

		if (i == JoystickID::Any) joystickDevices[i].connected = true;
		else joystickDevices[i].connected = glfwJoystickPresent(i) == 1 ? true : false;

		joystickDevices[i].id = (Input::JoystickID)i;
		joystickDevices[i].ConfigureJoystick();
	}
}

void Input::UpdateJoysticks()
{
	for (int i = Input::JoystickID::J0; i < Input::JoystickID::Any; ++i)
	{
		joystickDevices[i].UpdateValues();
	}
}

void Input::PollEvents()
{
	glfwPollEvents();

	Key kH = Key(Horizontal);
	Key kV = Key(Vertical);

	double x, y;
	glfwGetCursorPos(glfwGetCurrentContext(), &x, &y);
	double dx = x - mousePos.x;
	double dy = y - mousePos.y;

	if (dx != lastMouseDelta.x)
	{
		stickNotifFinder[KeyBoardDeviceID()][kH](kH, dx, lastMouseDelta.x);
	}
	if (dy != lastMouseDelta.y)
	{
		stickNotifFinder[KeyBoardDeviceID()][kV](kV, dy, lastMouseDelta.y);
	}

	mousePos = MousePos{ x, y };
	lastMouseDelta = MousePos{ dx, dy };

	UpdateJoysticks();
	eventExecutor();
}

void Input::SetMousePosition(MousePos _newPos)
{
	mousePos = _newPos;
	glfwSetCursorPos(glfwGetCurrentContext(), mousePos.x, mousePos.y);
}

void Input::SetCursorVisible(bool _visible)
{
	if (_visible)
	{
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Input::Instance::AddAction(std::string name, Input::Key defaultKeyID)
{
	auto action = actions.find(name);
	if (action == actions.end())
	{
		actions[name] = Action(deviceNotifFinder);
		SetActionKey(name, defaultKeyID);
	}
}

void Input::Instance::AddAction(std::string name, std::vector<Input::Key>& defaultKeyID)
{
	auto action = actions.find(name);
	if (action == actions.end())
	{
		actions[name] = Action(deviceNotifFinder);
		SetActionKey(name, defaultKeyID);
	}
}

void Input::Instance::RemoveAction(std::string name)
{
	auto action = actions.find(name);
	if (action != actions.end())
	{
		action->second.ClearKeys();
		actions.erase(name);
	}
}

void Input::Instance::SetAction(BindSet::ActionDescriptor& _ad)
{
	auto action = actions.find(_ad.name);
	if (action == actions.end())
	{
		AddAction(_ad.name, _ad.keys);
	}
	else
	{
		action->second.SetKeys(_ad.keys);
	}
}

void Input::Instance::SetActionKey(std::string name, std::vector<Key>& keys)
{
	auto action = actions.find(name);
	if (action == actions.end()) return;

	action->second.SetKeys(keys);
}

void Input::Instance::SetActionKey(std::string name, Key key)
{
	auto action = actions.find(name);
	if (action == actions.end()) return;

	std::vector<Input::Key> tmp;
	tmp.push_back(key);
	action->second.SetKeys(tmp);
}

void Input::Instance::SetActionListening(std::string name)
{
	auto action = actions.find(name);
	if (action == actions.end()) return;
	deviceNotifFinder.SetListening(&action->second);
}

void Input::Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key >= 0 && key < KeyVal::Count)
	{
		Key k = Key((Input::KeyVal)key);
		if (action < Mode::Hold)
		{
			notifFinder[KeyBoardDeviceID()][k](k, (Input::Mode)action);
		}
	}
}

void Input::MouseButton_Callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button >= 0 && button < KeyVal::Count)
	{
		Key k = Key((Input::KeyVal)(button + Input::KeyVal::MOUSE0));
		if (action < Mode::Hold)
		{
			notifFinder[KeyBoardDeviceID()][k](k, (Input::Mode)action);
		}
	}
}

void Input::MouseWheel_Callback(GLFWwindow* window, double x, double y)
{
	Key ky = Input::Key(0);
	Key kx = Input::Key(0);

	if (y > 0) ky = Key((Input::KeyVal)(Input::KeyVal::MOUSEWUP));
	else if(y < 0) ky = Key((Input::KeyVal)(Input::KeyVal::MOUSEWDOWN));
	notifFinder[KeyBoardDeviceID()][ky](ky, Input::Mode::Press);
	notifFinder[KeyBoardDeviceID()][ky](ky, Input::Mode::Release);

	if (x > 0) kx = Key((Input::KeyVal)(Input::KeyVal::MOUSEWRIGHT));
	else if(x < 0) kx = Key((Input::KeyVal)(Input::KeyVal::MOUSEWLEFT));
	notifFinder[KeyBoardDeviceID()][kx](kx, Input::Mode::Press);
	notifFinder[KeyBoardDeviceID()][kx](kx, Input::Mode::Release);
}

void Input::JoystickConnection_Callback(int ID, int status)
{
	if (joystickDevices[ID].connected = status == GLFW_CONNECTED)
	{
		joystickDevices[ID].ConfigureJoystick();
		joystickDevices[Any].ConfigureJoystick();
	}
}

Input::Instance& Input::GetGlobalInput(int i)
{
	if (i >= 0 && i < globalInstances.size())
	{
		return globalInstances[i];
	}
	else if (i >= globalInstances.size())
	{
		for (int x = globalInstances.size(); x <= i; ++x)
		{
			globalInstances.push_back(Instance(Input::KeyBoardDeviceID()));
		}
		return globalInstances[i];
	}
	throw std::out_of_range("tried to access a negative id global Input::Instance");
}

std::string Input::Instance::GetActionKeyString(std::string name)
{
	auto action = actions.find(name);
	if (action == actions.end()) return "";
	else return action->second.GetKeyString();
}

Input::BindSet Input::Instance::GetBindSet()
{
	return BindSet(deviceNotifFinder.id, actions, axes);
}

void Input::Instance::ApplyBindSet(BindSet& _bs)
{
	if (_bs.FailedToLoad()) return;

	UnbindAll();

	deviceNotifFinder.id = _bs.GetDevice();
	deviceStickNotifFinder.id = _bs.GetDevice();

	for (BindSet::ActionDescriptor& act : _bs.GetActions())
	{
		SetAction(act);
	}
	for (BindSet::AxisDescriptor& ax : _bs.GetAxes())
	{
		SetAxis(ax);
	}
}

void Input::Instance::AllowInput(bool val)
{
	if (IsListening()) return;
	if (allowInput != val)
	{
		if (val)
		{
			RebindAll();
		}
		else
		{
			UnbindAll();
		}
	}
	allowInput = val;
}

std::string Input::Instance::GetDeviceName()
{
	if (deviceNotifFinder.id.type == Keyboard)
		return "mouse and keyboard";
	else if (deviceNotifFinder.id.jID == Any)
	{
		return "Any joystick/controller";
	}
	else if (deviceNotifFinder.id.jID >= J0 && deviceNotifFinder.id.jID < Any)
	{
		return joystickDevices[deviceNotifFinder.id.jID].GetName();
	}
	else
		return "unknown";
}

void Input::Instance::UnbindAll()
{
	for (auto& act : actions)
	{
		act.second.Unbind();
	}
	for (auto& ax : axes)
	{
		ax.second.Unbind();
	}
}

void Input::Instance::RebindAll()
{
	for (auto& act : actions)
	{
		act.second.Rebind();
	}
	for (auto& ax : axes)
	{
		ax.second.Rebind();
	}
}

Input::Instance::Instance(Input::DeviceID _defaultDevice) :
	deviceNotifFinder(_defaultDevice),
	deviceStickNotifFinder(_defaultDevice)
{
	allowInput = true;
}

Input::KeyNotifyFinder::Device::Device(const DeviceID& d)
{
	id = d;
	//listener.Bind(this, &Input::KeyNotifyFinder::Device::Listen);
	listening = false;
	listenAction = nullptr;
}

bool Input::KeyNotifyFinder::Device::IsValidInput(Input::Key& key)
{
	return id.IsValidInput(key);
}

void Input::KeyNotifyFinder::Device::Listen(Input::Key& key, Input::Mode mode)
{
	bool isValid = IsValidInput(key);
	if (!isValid) return;
	if (listenAction)
	{
		if (mode == Mode::Press)
		{
			listenActionKey.push_back(key);
		}
		else if (mode == Mode::Release)
		{
			if (listenActionKey.size() > 0 && *listenActionKey.begin() == key)
			{
				listening = false;
				Input::listener = nullptr;
				listenAction->SetKeys(listenActionKey);
			}
			else
			{
				listenActionKey.remove(key);
			}
		}
	}
	else if (listenAxis)
	{
		if (mode == Mode::Press)
		{
			listening = false;
			Input::listener = nullptr;

			switch (axisListeningMode)
			{
			case OnlyForward:
				listenAxis->SetKeys(key);
				break;
			case ReplaceForward:
				listenAxis->SetKeys(key, listenAxis->backwardKey);
				break;
			case ReplaceBackward:
				listenAxis->SetKeys(listenAxis->forwardKey, key);
				break;
			}
		}
	}
}

Input::Key::Key(Input::KeyVal kID)
{
	keyID = kID;
	type = Input::KeyType::KKey;
}

Input::Key::Key(Input::MouseAxis mAxis)
{
	mouseAxis = mAxis;
	type = Input::KeyType::MAxis;
}

bool Input::Key::operator==(const Key& k) const
{
	if (type != k.GetType()) return false;
	switch (type)
	{
	case Input::KeyType::MAxis:
		return mouseAxis == k.mouseAxis;
	case Input::KeyType::KKey:
		return keyID == k.keyID;
	case Input::KeyType::JStick:
		return stickID == k.stickID &&
			sdirection == k.sdirection;
	case Input::KeyType::JButton:
		return buttonID == k.buttonID;
	case Input::KeyType::JHat:
		return hatId == k.hatId &&
			hdirection == k.hdirection;
	}
}

Input::Key Input::Key::MakeFromString(std::string keyStr)
{
	size_t endWord;
	if (keyStr.find("Stick") != std::string::npos)
	{
		std::string subStr = std::string(keyStr.c_str() + 5);
		std::string val = std::string(subStr.c_str(), endWord = subStr.find_first_of(" "));
		int joyID = std::stoi(val);
		subStr = std::string(subStr.c_str() + endWord + 1);
		Input::StickDirection sDir;
		if (subStr == "forward") sDir = Forward;
		else sDir = Backward;
		return Input::Key(joyID, sDir);
	}
	else if (keyStr.find("Button") != std::string::npos)
	{
		std::string val = std::string(keyStr.c_str() + 7);
		int butID = std::stoi(val);
		return Input::Key(butID);
	}
	else if (keyStr.find("Hat") != std::string::npos)
	{
		std::string subStr = std::string(keyStr.c_str() + 3);
		std::string val = std::string(subStr.c_str(), endWord = subStr.find_first_of(" "));
		int hatID = std::stoi(val);
		subStr = std::string(subStr.c_str() + endWord + 1);
		Input::HatDirection hDir;
		if (subStr == "up") hDir = Up;
		else if (subStr == "right") hDir = Right;
		else if (subStr == "down") hDir = Down;
		else hDir = Left;
		return Input::Key(hatID, hDir);
	}
	else if (keyStr == "MouseVertical")
	{
		return Input::Key(Input::MouseAxis::Vertical);
	}
	else if (keyStr == "MouseHorizontal")
	{
		return Input::Key(Input::MouseAxis::Horizontal);
	}
	else
	{
		for (Input::KeyVal v = Input::KeyVal::SPACE; v < Input::KeyVal::Count; v = (Input::KeyVal)(v + 1))
		{
			Input::Key k = Input::Key(v);
			if (k.ToString() == keyStr) return k;
		}
	}
	MessageBoxA(nullptr, (keyStr + " : key name doesn't match").c_str(), "error", MB_ICONERROR | MB_OK);
	return Input::Key((Input::KeyVal)0);
}

std::string Input::Key::ToString() const
{
	switch (type)
	{
	case Input::KeyType::MAxis:
		return mouseAxis == Vertical ? "MouseVertical" : "MouseHorizontal";
	case Input::KeyType::KKey:
		return KeyToString();
	case Input::KeyType::JStick:
		return StickToString();
	case Input::KeyType::JButton:
		return ButtonToString();
	case Input::KeyType::JHat:
		return HatToString();
	default:
		return "unknown";
	}
}

Input::Key::Key(int hID, Input::HatDirection dir)
{
	hatId = hID;
	hdirection = dir;
	type = Input::KeyType::JHat;
}

Input::Key::Key(int sID, Input::StickDirection dir)
{
	stickID = sID;
	sdirection = dir;
	type = Input::KeyType::JStick;
}

Input::Key::Key(int bID)
{
	buttonID = bID;
	type = Input::KeyType::JButton;
}

Input::KeyNotify& Input::KeyNotifyFinder::Device::operator[](const Input::Key& key)
{
	if (listening)
		return listener;

	switch (id.type)
	{
	case Keyboard:
	{
		return keyNotifs[key.keyID];
	}
	break;
	case Joystick:
		JoystickDevice& j = joystickDevices[id.jID];
		switch (key.GetType())
		{
		case JStick:
		{
			if (key.stickID >= 0 && key.stickID < j.stickStatusNotifs[key.sdirection].size())
			{
				return j.stickStatusNotifs[key.sdirection][key.stickID];
			}
		}
		break;
		case JButton:
		{
			if (key.buttonID >= 0 && key.buttonID < j.ButtonNotifs.size())
			{
				return j.ButtonNotifs[key.buttonID];
			}
		}
		break;
		case JHat:
		{
			if (key.hatId >= 0 && key.hatId < j.hatNotifs[key.hdirection].size())
			{
				return j.hatNotifs[key.hdirection][key.hatId];
			}
		}
		break;
		}
		break;
	}
	MessageBoxA(nullptr, "unknown key, this binding might not work correctly", "warning", MB_ICONWARNING | MB_OK);
	return dummy;
}

void Input::KeyNotifyFinder::Device::SetListening(Action* action)
{
	listening = true;
	listenAction = action;
	listenAxis = nullptr;
	listenActionKey.clear();
	listener.Clear();
	listener.Bind(this, &Input::KeyNotifyFinder::Device::Listen);
	Input::listener = this;
}

void Input::KeyNotifyFinder::Device::SetListening(Axis* axis, AxisListeningMode mode)
{
	axisListeningMode = mode;
	listening = true;
	listenAction = nullptr;
	listenAxis = axis;
	listenActionKey.clear();
	listener.Clear();
	listener.Bind(this, &Input::KeyNotifyFinder::Device::Listen);
	Input::listener = this;
}

Input::KeyNotifyFinder::Device& Input::KeyNotifyFinder::operator[](const Input::DeviceID& dID)
{
	static Device d = Device(Input::KeyBoardDeviceID());

	if (!(dID == d.id))
	{
		if (!(dID == DeviceID(Joystick, Any)))
		{
			lastUsedDevice = dID;
		}
		d = Device(dID);
	}

	if (listener)
		return *listener;
	else
		return d;
}

Input::StickNotifyFinder::Device::Device(const DeviceID& d)
{
	id = d;
}

bool Input::StickNotifyFinder::Device::IsValidInput(Input::Key& key)
{
	return id.IsValidInput(key);
}

Input::StickNotify& Input::StickNotifyFinder::Device::operator[](const Input::Key& key)
{
	switch (key.GetType())
	{
	case MAxis:
		return mouseAxisNotifs[key.mouseAxis];
	case JStick:
	{
		JoystickDevice& j = joystickDevices[id.jID];
		if (key.stickID >= 0 && key.stickID < j.stickStatusNotifs[key.sdirection].size())
		{
			return j.stickValueNotifs[key.sdirection][key.stickID];
		}
	}
	}
	MessageBoxA(nullptr, "unknown Stick/Axis, this binding might not work correctly", "warning", MB_ICONWARNING | MB_OK);
	return dummy;
}

Input::StickNotifyFinder::Device& Input::StickNotifyFinder::operator[](const Input::DeviceID& dID)
{
	static Device d = Device(Input::KeyBoardDeviceID());

	if (!(dID == d.id))
	{
		if (!(dID == DeviceID(Joystick, Any)))
		{
			lastUsedDevice = dID;
		}
		d = Device(dID);
	}
	return d;
}

bool operator<(const Input::Key& k1, const Input::Key& k2)
{
	if (k1.GetType() < k2.GetType()) return true;
	else if (k2.GetType() < k1.GetType()) return false;
	else
	{
		switch (k1.GetType())
		{
		case Input::KeyType::KKey:
		{
			return k1.keyID < k2.keyID;
			break;
		}
		case Input::KeyType::JStick:
		{
			bool sid = k1.stickID < k2.stickID;
			bool d = k1.sdirection < k2.sdirection;
			return sid || (k1.stickID == k2.stickID && d);
			break;
		}
		case Input::KeyType::JButton:
		{
			bool bid = k1.buttonID < k2.buttonID;
			return bid;
			break;
		}
		case Input::KeyType::JHat:
		{
			bool hid = k1.hatId < k2.hatId;
			bool d = k1.hdirection < k2.hdirection;
			return hid || (k1.hatId == k2.hatId && d);
			break;
		}
		}
	}
}

std::string Input::BindSet::ActionDescriptor::ToString()
{
	std::string out = name + ":";

	std::string keyStr = "";

	int i = 0;
	for (auto& key : keys)
	{
		if (i != 0) keyStr += " + ";
		keyStr += key.ToString();
		++i;
	}

	return out + keyStr;
}

Input::BindSet::ActionDescriptor& Input::BindSet::ActionDescriptor::SetFromString(std::string str)
{
	keys.clear();
	size_t endWord = str.find_first_of(":");
	name = std::string(str.c_str(), endWord);
	str = str.c_str() + endWord + 1;
	while (endWord = str.find(" + ") != std::string::npos)
	{
		keys.push_back(Input::Key::MakeFromString(std::string(str.c_str(), endWord)));
		str = str.c_str() + endWord + 3;
	}
	keys.push_back(Input::Key::MakeFromString(str));
	return *this;
}

Input::BindSet::ActionDescriptor::ActionDescriptor(std::string _name, Action& _action)
{
	SetFromString(_name + ":" + _action.GetKeyString());
}

bool Input::DeviceID::operator==(const DeviceID& d) const
{
	return (type == Keyboard && type == d.type) || (d.jID == jID && d.type == type);
}

bool Input::DeviceID::IsValidInput(Input::Key& key)
{
	if (type == Keyboard)
	{
		return key.GetType() <= Input::KeyType::KKey;
	}
	else
	{
		return key.GetType() > Input::KeyType::KKey;
	}
}

Input::BindSet::BindSet() : device(KeyBoardDeviceID())
{
}

Input::BindSet::BindSet(std::string path) : BindSet()
{
	loadingFailed = true;
	std::ifstream file;
	file.open(path);
	if (file.is_open())
	{
		char buf[512];
		file.getline(buf, 512);
		std::string line = buf;
		int endWord = line.find_first_of(" ");
		DeviceType type = (DeviceType)std::stoi(std::string(line.c_str(), endWord));
		JoystickID jID = (JoystickID)std::stoi(std::string(line.c_str() + endWord + 1));
		device.type = type;
		device.jID = jID;
		bool readingAxes = false;
		while (!file.eof())
		{
			file.getline(buf, 512);
			line = buf;
			if (line == "actions") continue;
			else if (line == "axes")
			{
				readingAxes = true;
				continue;
			}
			else if (line == "") break;
			
			if (readingAxes) axes.push_back(AxisDescriptor().SetFromString(line));
			else actions.push_back(ActionDescriptor().SetFromString(line));
		}
		loadingFailed = false;
	}
}

Input::BindSet::BindSet(Input::DeviceID dID, std::map<std::string, Input::Action>& actionMap) :
	BindSet(dID.type, actionMap)
{
	device.jID = dID.jID;
}

Input::BindSet::BindSet(Input::DeviceID dID, std::map<std::string, Input::Axis>& axisMap) :
	BindSet(dID.type, axisMap)
{
	device.jID = dID.jID;
}

Input::BindSet::BindSet(Input::DeviceID dID, std::map<std::string, Input::Action>& actionMap, std::map<std::string, Input::Axis>& axisMap) :
	BindSet(dID.type, actionMap, axisMap)
{
	device.jID = dID.jID;
}

Input::BindSet::BindSet(Input::DeviceType type, std::map<std::string, Input::Action>& actionMap) : BindSet()
{
	device.type = type;
	device.jID = Any;
	for (auto& action : actionMap)
	{
		actions.push_back(ActionDescriptor(action.first, action.second));
	}
}

Input::BindSet::BindSet(Input::DeviceType type, std::map<std::string, Input::Axis>& axisMap) : BindSet()
{
	device.type = type;
	device.jID = Any;
	for (auto& axis : axisMap)
	{
		axes.push_back(AxisDescriptor(axis.first, axis.second));
	}
}

Input::BindSet::BindSet(Input::DeviceType type, std::map<std::string, Input::Action>& actionMap, std::map<std::string, Input::Axis>& axisMap)
{
	device.type = type;
	device.jID = Any;
	for (auto& action : actionMap)
	{
		actions.push_back(ActionDescriptor(action.first, action.second));
	}
	for (auto& axis : axisMap)
	{
		axes.push_back(AxisDescriptor(axis.first, axis.second));
	}
}

void Input::BindSet::AddAction(std::string _name, Action& _action)
{
	actions.push_back(ActionDescriptor(_name, _action));
}

void Input::BindSet::AddAction(std::string _name, std::vector<Key>& _keys)
{
	ActionDescriptor ad;
	ad.name = _name;
	ad.keys = _keys;
	actions.push_back(ad);
}

void Input::BindSet::AddAction(std::string _name, Key& _key)
{
	ActionDescriptor ad;
	ad.name = _name;
	ad.keys.push_back(_key);
	actions.push_back(ad);
}

void Input::BindSet::RemoveAction(std::string _name)
{
	actions.remove_if([_name](ActionDescriptor& act) { return act.name == _name; });
}

void Input::BindSet::AddAxis(std::string _name, Axis& _axis)
{
	axes.push_back(AxisDescriptor(_name, _axis));
}

void Input::BindSet::AddAxis(std::string _name, Key& _fkey, Key& _bkey)
{
	AxisDescriptor ad;
	ad.name = _name;
	ad.fkey = _fkey;
	ad.bkey = _bkey;
	axes.push_back(ad);
}

void Input::BindSet::AddAxis(std::string _name, Key& _key)
{
	AxisDescriptor ad;
	ad.name = _name;
	ad.fkey = _key;
	ad.bkey = INVALID_KEY;
	axes.push_back(ad);
}

void Input::BindSet::RemoveAxis(std::string _name)
{
	axes.remove_if([_name](AxisDescriptor& ax) { return ax.name == _name; });
}

void Input::BindSet::SetDevice(DeviceID _dID)
{
	device = _dID;
}

void Input::BindSet::SetDevice(DeviceType _type)
{
	device.type = _type;
	device.jID = Any;
}

void Input::BindSet::Save(std::string _path)
{
	std::ofstream file;
	file.open(_path);
	if (file.is_open())
	{
		file << std::to_string(device.type) << " " << std::to_string(device.type) << "\n";
		file << "actions\n";
		for (ActionDescriptor& act : actions)
		{
			file << act.ToString();
			file << "\n";
		}
		file << "axes\n";
		for (AxisDescriptor& ax : axes)
		{
			file << ax.ToString();
			file << "\n";
		}
		file.close();
	}
}

void Input::Axis::KeyCallback(Input::Key& key, Input::Mode _mode)
{
	lastValue = currentValue;
	bool isForward = key == forwardKey;
	float& tmp = isForward ? tmpF : tmpB;

	if (_mode == Press)
	{
		if (isForward)
		{
			tmp = 1.0f;
		}
		else
		{
			tmp = -1.0f;
		}
	}
	else
	{
		tmp = 0.0f;
	}

	currentValue = tmpF + tmpB;

	if (lastValue == 0.0f) Input::eventExecutor.Bind(this, &Input::Axis::Execute);
	else if (currentValue == 0.0f)
	{
		Input::eventExecutor.Unbind(this, &Input::Axis::Execute);
		Input::eventExecutor.Bind(this, &Input::Axis::ExecuteOnce);
	}
}

void Input::Axis::StickCallback(Input::Key& key, float _currentValue, float _lastValue)
{
	if (key == forwardKey)
	{
		currentValue = _currentValue;
		lastValue = _lastValue;
	}
	else
	{
		currentValue = -_currentValue;
		lastValue = -_lastValue;
	}
	
	if (currentValue == 0.0f)
	{
		Input::eventExecutor.Unbind(this, &Input::Axis::Execute);
		Input::eventExecutor.Bind(this, &Input::Axis::ExecuteOnce);
	}
	else if (lastValue == 0.0f)
	{
		Input::eventExecutor.Bind(this, &Input::Axis::Execute);
	}
}

void Input::Axis::Execute()
{
	notif(currentValue, lastValue);
}

void Input::Axis::ExecuteOnce()
{
	Execute();
	Input::eventExecutor.Unbind(this, &Input::Axis::ExecuteOnce);
}

void Input::Axis::Unbind()
{
	Input::eventExecutor.Unbind(this, &Input::Axis::Execute);
	Input::eventExecutor.Unbind(this, &Input::Axis::ExecuteOnce);
	
	if (forwardKey.GetType() == MAxis || forwardKey.GetType() == JStick)
	{
		(*dStickNotifFinder)[forwardKey].Unbind(this, &Input::Axis::StickCallback);
		if (!(backwardKey == INVALID_KEY)) (*dStickNotifFinder)[backwardKey].Unbind(this, &Input::Axis::StickCallback);
	}
	else
	{
		(*dNotifFinder)[forwardKey].Unbind(this, &Input::Axis::KeyCallback);
		if (!(backwardKey == INVALID_KEY)) (*dNotifFinder)[backwardKey].Unbind(this, &Input::Axis::KeyCallback);
	}
}

void Input::Axis::Rebind()
{
	if (forwardKey.GetType() == MAxis || forwardKey.GetType() == JStick)
	{
		(*dStickNotifFinder)[forwardKey].Bind(this, &Input::Axis::StickCallback);
		if (!(backwardKey == INVALID_KEY)) (*dStickNotifFinder)[backwardKey].Bind(this, &Input::Axis::StickCallback);
	}
	else
	{
		(*dNotifFinder)[forwardKey].Bind(this, &Input::Axis::KeyCallback);
		if (!(backwardKey == INVALID_KEY)) (*dNotifFinder)[backwardKey].Bind(this, &Input::Axis::KeyCallback);
	}
}

void Input::Axis::SetKeys(Input::Key& _forwardKey, Input::Key& _backwardKey)
{
	Unbind();

	forwardKey = _forwardKey;
	backwardKey = _backwardKey;
	listeningPreference = TwoKeys;

	Rebind();
}

void Input::Axis::SetKeys(Input::Key& forwardStick)
{
	Unbind();

	forwardKey = forwardStick;
	backwardKey = INVALID_KEY;
	listeningPreference = OneKey;

	Rebind();
}

std::string Input::Axis::GetKeyString()
{
	std::string keyStr = "";

	keyStr += forwardKey.ToString();
	if (!(backwardKey == INVALID_KEY))
	{
		keyStr += " | ";
		keyStr += backwardKey.ToString();
	}

	return keyStr;
}

void Input::Instance::AddAxis(std::string name, Input::Key defaultKeyID)
{
	auto axis = axes.find(name);
	if (axis == axes.end())
	{
		axes[name] = Axis(deviceNotifFinder, deviceStickNotifFinder);
		SetAxisKey(name, defaultKeyID);
	}
}

void Input::Instance::AddAxis(std::string name, Input::Key defaultForwardKeyID, Input::Key defaultBackwardKeyID)
{
	auto axis = axes.find(name);
	if (axis == axes.end())
	{
		axes[name] = Axis(deviceNotifFinder, deviceStickNotifFinder);
		SetAxisKey(name, defaultForwardKeyID, defaultBackwardKeyID);
	}
}

void Input::Instance::RemoveAxis(std::string name)
{
	auto axis = axes.find(name);
	if (axis != axes.end())
	{
		axis->second.Unbind();
		axes.erase(name);
	}
}

void Input::Instance::SetAxis(BindSet::AxisDescriptor& ad)
{
	auto axis = axes.find(ad.name);
	if (axis == axes.end())
	{
		AddAxis(ad.name, ad.fkey, ad.bkey);
	}
	else
	{
		axis->second.SetKeys(ad.fkey, ad.bkey);
	}
}

void Input::Instance::SetAxisKey(std::string name, Input::Key key)
{
	auto axis = axes.find(name);
	if (axis == axes.end()) return;

	axis->second.SetKeys(key);
}

void Input::Instance::SetAxisKey(std::string name, Input::Key forwardKey, Input::Key backwardKey)
{
	auto axis = axes.find(name);
	if (axis == axes.end()) return;

	axis->second.SetKeys(forwardKey, backwardKey);
}

void Input::Instance::SetAxisListening(std::string name, AxisListeningMode mode)
{
	auto axis = axes.find(name);
	if (axis == axes.end()) return;
	deviceNotifFinder.SetListening(&axis->second, mode);
}

std::string Input::Instance::GetAxisKeyString(std::string name)
{
	auto axis = axes.find(name);
	if (axis == axes.end()) return "";
	else return axis->second.GetKeyString();
}

std::string Input::BindSet::AxisDescriptor::ToString()
{
	std::string out = name + ":";

	std::string keyStr = "";

	keyStr += fkey.ToString();
	if (!(bkey == INVALID_KEY))
	{
		keyStr += " | ";
		keyStr += bkey.ToString();
	}

	return out + keyStr;
}

Input::BindSet::AxisDescriptor& Input::BindSet::AxisDescriptor::SetFromString(std::string str)
{
	fkey = INVALID_KEY;
	bkey = INVALID_KEY;
	size_t endWord = str.find_first_of(":");
	name = std::string(str.c_str(), endWord);
	str = str.c_str() + endWord + 1;
	if ((endWord = str.find(" | ")) != std::string::npos)
	{
		fkey = Input::Key::MakeFromString(std::string(str.c_str(), endWord));
		str = str.c_str() + endWord + 3;
		bkey = Input::Key::MakeFromString(str);
	}
	else
	{
		fkey = Input::Key::MakeFromString(str);
	}
	return *this;
}

Input::BindSet::AxisDescriptor::AxisDescriptor(std::string _name, Input::Axis& _axis) :
	AxisDescriptor()
{
	SetFromString(_name + ":" + _axis.GetKeyString());
}

Input::AxisListeningPreference Input::BindSet::AxisDescriptor::GetListeningPreference()
{
	return (bkey == INVALID_KEY) ? OneKey : TwoKeys;
}
