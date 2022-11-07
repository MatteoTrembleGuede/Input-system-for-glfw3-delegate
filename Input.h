#pragma once
#include <string>
#include <vector>
#include <map>
#include "Delegate.h"

// TODO add mouse and axis management

struct GLFWwindow;

class Input
{
private:

	friend struct JoystickDevice;
	friend struct Action;

public:

	struct MousePos
	{
		double x;
		double y;
	};

	enum AxisListeningMode
	{
		OnlyForward,
		ReplaceForward,
		ReplaceBackward
	};

	// just a hint at what listening mode would be better for a given axis
	enum AxisListeningPreference
	{
		OneKey, // for sticks going from -1 to 1 or triggers going from 0 to 1
		TwoKeys, // for simulated sticks with a forward key (1) and a backward key (-1)
	};

	enum KeyboardLayout
	{
		QWERTY,
		AZERTY,
		DVORAK,
		UNKNOWNKEYBOARD
	};

	// keyboard = keybord+mouse
	// Joystick = Any joystick/gamepad...
	enum DeviceType
	{
		Keyboard,
		Joystick
	};

	enum MouseAxis
	{
		Vertical,
		Horizontal
	};

	enum KeyType
	{
		MAxis,
		KKey,
		JStick,
		JButton,
		JHat,
		MButton = KKey
	};

	enum KeyVal
	{
		UNKNOWN = -1,
		SPACE = 32,
		APOSTROPHE = 39,
		COMMA = 44,
		MINUS = 45,
		PERIOD = 46,
		SLASH = 47,
		NUM0 = 48,
		NUM1 = 49,
		NUM2 = 50,
		NUM3 = 51,
		NUM4 = 52,
		NUM5 = 53,
		NUM6 = 54,
		NUM7 = 55,
		NUM8 = 56,
		NUM9 = 57,
		COLON = 58,
		SEMICOLON = 59,
		LESSER = 60,
		EQUAL = 61,
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LEFT_BRACKET = 91,
		BACKSLASH = 92,
		RIGHT_BRACKET = 93,
		GRAVE_ACCENT = 96,
		WORLD_1 = 161,
		WORLD_2 = 162,
		ESCAPE = 256,
		ENTER = 257,
		TAB = 258,
		BACKSPACE = 259,
		INSERT = 260,
		DEL = 261,
		RIGHT = 262,
		LEFT = 263,
		DOWN = 264,
		UP = 265,
		PAGE_UP = 266,
		PAGE_DOWN = 267,
		HOME = 268,
		END = 269,
		CAPS_LOCK = 280,
		SCROLL_LOCK = 281,
		NUM_LOCK = 282,
		PRINT_SCREEN = 283,
		PAUSE = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		KP_0 = 320,
		KP_1 = 321,
		KP_2 = 322,
		KP_3 = 323,
		KP_4 = 324,
		KP_5 = 325,
		KP_6 = 326,
		KP_7 = 327,
		KP_8 = 328,
		KP_9 = 329,
		KP_DECIMAL = 330,
		KP_DIVIDE = 331,
		KP_MULTIPLY = 332,
		KP_SUBTRACT = 333,
		KP_ADD = 334,
		KP_ENTER = 335,
		KP_EQUAL = 336,
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		LEFT_SUPER = 343,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345,
		RIGHT_ALT = 346,
		RIGHT_SUPER = 347,
		MENU = 348,
		MOUSE0 = 349,
		MOUSE1 = 350,
		MOUSE2 = 351,
		MOUSEWUP = 352,
		MOUSEWDOWN = 353,
		MOUSEWLEFT = 354,
		MOUSEWRIGHT = 355,
		Count
	};

	enum Mode
	{
		Release,
		Press,
		Hold
	};

	enum JoystickID
	{
		J0,
		J1,
		J2,
		J3,
		J4,
		J5,
		J6,
		J7,
		J8,
		J9,
		J10,
		J11,
		J12,
		J13,
		J14,
		J15,
		Any
	};

	enum HatDirection
	{
		Up,
		Right,
		Down,
		Left
	};

	enum StickDirection
	{
		Forward,
		Backward
	};

private:

	class KeyNotifyFinder;
	union KeyData
	{
		int i;
		Input::KeyVal kv;
		Input::HatDirection hd;
		Input::StickDirection sd;
		Input::MouseAxis ma;
	};

	static KeyboardLayout keyboardLayout;
	static MousePos mousePos;
	static MousePos lastMouseDelta;

public:

	// float 1 is current value, float 2 is last value
	DeclareDelegate(NotifyAxisValue, float, float);

	class Key;

	struct DeviceID
	{
	public:
		DeviceType type;
		JoystickID jID;

		DeviceID() {};
		bool operator==(const DeviceID& d) const;
		DeviceID(DeviceType _type, JoystickID _jID) : type(_type), jID(_jID){};
		bool IsValidInput(Input::Key& key);
	};

	struct KeyBoardDeviceID : public DeviceID
	{
		KeyBoardDeviceID() { type = DeviceType::Keyboard; };
	};

	struct JoystickDeviceID : public DeviceID
	{
		JoystickDeviceID(JoystickID id) { type = DeviceType::Joystick; jID = id; };
	};

	struct Key 
	{
	protected:

		Input::KeyType type;

		std::string KeyToString() const;
		std::string StickToString() const;
		std::string ButtonToString() const;
		std::string HatToString() const;

	public:

		Input::KeyData data[2];

		Key(Input::KeyVal kID);
		Key(Input::MouseAxis mAxis);
		Key(int hID, Input::HatDirection dir);
		Key(int sID, Input::StickDirection dir);
		Key(int bID);
		Input::KeyType GetType() const { return type; };
		virtual std::string ToString() const;
		virtual bool operator==(const Key& k) const;
		static Input::Key MakeFromString(std::string keyStr);
	};

#define INVALID_KEY Key(-1)

private:

	DeclareDelegate(KeyNotify, Key&, Mode);
	DeclareDelegate(StickNotify, Key&, float, float);

	class Action;
	class Axis;

	class KeyNotifyFinder
	{
	public:

		struct Device
		{
			bool listening;
			Input::Action* listenAction;
			Input::Axis* listenAxis;
			std::list<Input::Key> listenActionKey;
			AxisListeningMode axisListeningMode;
			KeyNotify listener;
			KeyNotify dummy;
			DeviceID id;
			KeyNotify& operator[](const Key& key);
			void SetListening(Action* action);
			void SetListening(Axis* axis, AxisListeningMode mode);
			void Listen(Input::Key& key, Input::Mode mode);
			Device(const DeviceID& d);
			bool IsValidInput(Input::Key& key);
		};

		Device& operator[](const DeviceID& dID);
	};

	class StickNotifyFinder
	{
	public:

		struct Device
		{
			StickNotify dummy;
			DeviceID id;
			StickNotify& operator[](const Key& key);
			Device(const DeviceID& d);
			bool IsValidInput(Input::Key& key);
		};
		Device& operator[](const DeviceID& dID);
	};

	class Action
	{
	private:

		Input::KeyNotifyFinder::Device* dNotifFinder;
		bool wasPressed = false;
		std::map<Input::Key, bool> KeyStates;

		void ExecuteHold();
		void KeyCallback(Input::Key& key, Input::Mode _mode);
		void ExecutePressed();
		void ExecuteReleased();

	public:

		// shouldn't be used
		Action() : dNotifFinder(nullptr) {};

		Action(Input::KeyNotifyFinder::Device& dnf) : dNotifFinder(&dnf) {};
		Notify action[3];

		void Unbind();
		void Rebind();
		void SetKeys(std::vector<Input::Key>& keys);
		void SetKeys(std::list<Input::Key>& keys);
		void ClearKeys();
		std::string GetKeyString();

	};

	class Axis
	{
		friend class Input::KeyNotifyFinder::Device;
	private:

		Input::AxisListeningPreference listeningPreference;
		Input::KeyNotifyFinder::Device* dNotifFinder;
		Input::StickNotifyFinder::Device* dStickNotifFinder;
		Input::Key forwardKey;
		Input::Key backwardKey;
		float tmpF;
		float tmpB;
		float currentValue;
		float lastValue;

		void KeyCallback(Input::Key& key, Input::Mode _mode);
		void StickCallback(Input::Key& key, float _currentValue, float _lastValue);
		void Execute();
		void ExecuteOnce();

	public:

		NotifyAxisValue notif;

		// shouldn't be used
		Axis() :
			dNotifFinder(nullptr), dStickNotifFinder(nullptr), 
			forwardKey(Key(0)), backwardKey(Key(0)),
			lastValue(0), currentValue(0),
			tmpB(0), tmpF(0)
		{};

		Axis(Input::KeyNotifyFinder::Device& dnf, Input::StickNotifyFinder::Device& dsnf) : 
			dNotifFinder(&dnf), dStickNotifFinder(&dsnf), 
			forwardKey(Key(0)), backwardKey(Key(0)),
			lastValue(0), currentValue(0),
			tmpB(0), tmpF(0)
		{};

		void Unbind();
		void Rebind();
		void SetKeys(Input::Key& _forwardKey, Input::Key& _backwardKey);
		void SetKeys(Input::Key& forwardStick);
		AxisListeningPreference GetListeningPreferedMode() { return listeningPreference; };
		std::string GetKeyString();

	};

	class JoystickDevice
	{
	private:

		std::string name;

		// sticks
		std::vector<float> deadZones;
		std::vector<float> stickValues;

		// buttons
		std::vector<bool> buttonValues;

		// hats
		std::vector<unsigned char> hatValues;
		
		void UpdateHats();
		void UpdateSticks();
		void UpdateButtons();

	public:

		bool connected;
		Input::JoystickID id;
		std::vector<Input::KeyNotify> hatNotifs[4];
		std::vector<Input::KeyNotify> ButtonNotifs;
		std::vector<Input::KeyNotify> stickStatusNotifs[2];
		std::vector<Input::StickNotify> stickValueNotifs[2];

		void UpdateValues();
		void ConfigureAsAny();
		void ConfigureJoystick();
		std::string GetName() { return name; };

	};

public:

	// need a glfw window to be created first
	static void Init();
	static void PollEvents();
	static KeyboardLayout GetKeyboardLayout() { return keyboardLayout; };
	static DeviceID GetLastUsedDeviceID() { return lastUsedDevice; };
	static MousePos GetMousePosition() { return mousePos; };
	static void SetMousePosition(MousePos _newPos);
	static void SetCursorVisible(bool _visible);

private:

	static Notify eventExecutor;
	static KeyNotifyFinder notifFinder;
	static StickNotifyFinder stickNotifFinder;
	static std::vector<KeyNotify> keyNotifs;
	static std::vector<StickNotify> mouseAxisNotifs;
	static std::vector<JoystickDevice> joystickDevices;
	static DeviceID lastUsedDevice;

	static void Key_Callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButton_Callback(GLFWwindow* window, int button, int action, int mods);
	static void MouseWheel_Callback(GLFWwindow* window, double x, double y);
	static void JoystickConnection_Callback(int ID, int status);
	static void CheckJoysticks();
	static void UpdateJoysticks();

public:

	struct BindSet
	{
		BindSet(); 
		BindSet(std::string path); 
		BindSet(Input::DeviceID dID, std::map<std::string, Input::Action>& actionMap);
		BindSet(Input::DeviceID dID, std::map<std::string, Input::Axis>& axisMap);
		BindSet(Input::DeviceID dID, std::map<std::string, Input::Action>& actionMap, std::map<std::string, Input::Axis>& axisMap);

		BindSet(Input::DeviceType type, std::map<std::string, Input::Action>& actionMap);
		BindSet(Input::DeviceType type, std::map<std::string, Input::Axis>& axisMap);
		BindSet(Input::DeviceType type, std::map<std::string, Input::Action>& actionMap, std::map<std::string, Input::Axis>& axisMap);

		struct ActionDescriptor
		{
			std::string name;
			std::vector<Input::Key> keys;
			std::string ToString();
			ActionDescriptor& SetFromString(std::string str);

			ActionDescriptor(std::string _name, Input::Action& _action);
			ActionDescriptor() {};
		};
		
		struct AxisDescriptor
		{
			std::string name;
			Input::Key fkey;
			Input::Key bkey;
			std::string ToString();
			AxisDescriptor& SetFromString(std::string str);

			AxisDescriptor(std::string _name, Input::Axis& _axis);
			AxisDescriptor() : fkey(Key(0)), bkey(Key(0)) {};
			AxisListeningPreference GetListeningPreference();
		};

		void AddAction(std::string _name, Action& _action);
		void AddAction(std::string _name, std::vector<Key>& _keys);
		void AddAction(std::string _name, Key& _key);
		void RemoveAction(std::string _name);
		
		void AddAxis(std::string _name, Axis& _axis);
		void AddAxis(std::string _name, Key& _fkey, Key& _bkey);
		void AddAxis(std::string _name, Key& _key);
		void RemoveAxis(std::string _name);

		void SetDevice(DeviceID _dID);
		void SetDevice(DeviceType _type);
		Input::DeviceID GetDevice() { return device; };
		std::list<ActionDescriptor> GetActions() { return actions; };
		std::list<AxisDescriptor> GetAxes() { return axes; };

		void Save(std::string _path);
		bool FailedToLoad() { return loadingFailed; };

	private:

		Input::DeviceID device;
		std::list<ActionDescriptor> actions;
		std::list<AxisDescriptor> axes;
		bool loadingFailed = false;

	};

	class Instance
	{
	private:

		Input::KeyNotifyFinder::Device deviceNotifFinder;
		Input::StickNotifyFinder::Device deviceStickNotifFinder;
		bool allowInput;
		std::map<std::string, Input::Action> actions;
		std::map<std::string, Input::Axis> axes;

		void UnbindAll();
		void RebindAll();

	public:

		Instance(Input::DeviceID _defaultDevice);

		void AllowInput(bool val);
		std::string GetDeviceName();
		DeviceType GetDeviceType() { return deviceNotifFinder.id.type; };
		DeviceID GetDeviceID() { return deviceNotifFinder.id; };

		BindSet GetBindSet();
		void ApplyBindSet(BindSet& _bs);
		bool IsListening() { return deviceNotifFinder.listening; };

		void AddAction(std::string name, Input::Key defaultKeyID);
		void AddAction(std::string name, std::vector<Input::Key>& defaultKeyID);
		void RemoveAction(std::string name);
		void SetAction(BindSet::ActionDescriptor& _ad);
		void SetActionKey(std::string name, Input::Key key);
		void SetActionKey(std::string name, std::vector<Input::Key>& key);
		void SetActionListening(std::string name);
		std::string GetActionKeyString(std::string name);

		// args can be one of these :
		// - Bind("name", Input::Mode, &obj, &class::member)
		// - Bind("name", Input::Mode, &function)
		// - Bind("name", Input::Mode, +[]{}), you won't be able to unbind lambdas unless your stored them, ex : auto lambda = +[]{};
		// - Bind("name", Input::Mode, [&]{}), be carefull with capturing lambdas as you won't be able to unbind them
		// function signature must be void func(void)
		template<typename... Types>
		void BindAction(std::string name, Input::Mode mode, Types... args);

		// args can be one of these :
		// - Bind("name", Input::Mode, &obj, &class::member)
		// - Bind("name", Input::Mode, &function)
		// - Bind("name", Input::Mode, &lambda), you won't be able to unbind lambdas unless your stored them, ex : auto lambda = +[]{};
		template<typename... Types>
		void UnbindAction(std::string name, Input::Mode mode, Types... args);

		void AddAxis(std::string name, Input::Key defaultKeyID);
		void AddAxis(std::string name, Input::Key defaultForwardKeyID, Input::Key defaultBackwardKeyID);
		void RemoveAxis(std::string name);
		void SetAxis(BindSet::AxisDescriptor& ad);
		void SetAxisKey(std::string name, Input::Key key);
		void SetAxisKey(std::string name, Input::Key forwardKey, Input::Key backwardKey);
		void SetAxisListening(std::string name, AxisListeningMode mode);
		std::string GetAxisKeyString(std::string name);

		// args can be one of these :
		// - Bind("name", Input::Mode, &obj, &class::member)
		// - Bind("name", Input::Mode, &function)
		// - Bind("name", Input::Mode, +[]{}), you won't be able to unbind lambdas unless your stored them, ex : auto lambda = +[]{};
		// - Bind("name", Input::Mode, [&]{}), be carefull with capturing lambdas as you won't be able to unbind them
		// function signature must be void func(float, float)
		template<typename... Types>
		void BindAxis(std::string name, Types... args);

		// args can be one of these :
		// - Bind("name", Input::Mode, &obj, &class::member)
		// - Bind("name", Input::Mode, &function)
		// - Bind("name", Input::Mode, &lambda), you won't be able to unbind lambdas unless your stored them, ex : auto lambda = +[]{};
		template<typename... Types>
		void UnbindAxis(std::string name, Types... args);

	};

private:

	static std::vector<Instance> globalInstances;
	static Input::KeyNotifyFinder::Device* listener;
	static int maxButtons;
	static int maxHats;
	static int maxSticks;

public:

	static Instance& GetGlobalInput(int i);

};

static bool operator<(const Input::Key& k1, const Input::Key& k2);

template<typename ...Types>
inline void Input::Instance::BindAction(std::string name, Input::Mode mode, Types ...args)
{
	auto action = actions.find(name);
	if (action != actions.end())
	{
		action->second.action[mode].Bind(args...);
	}
}

template<typename ...Types>
inline void Input::Instance::UnbindAction(std::string name, Input::Mode mode, Types ...args)
{
	auto action = actions.find(name);
	if (action != actions.end())
	{
		action->second.action[mode].Unbind(args...);
	}
}

template<typename ...Types>
inline void Input::Instance::BindAxis(std::string name, Types ...args)
{
	auto axis = axes.find(name);
	if (axis != axes.end())
	{
		axis->second.notif.Bind(args...);
	}
}

template<typename ...Types>
inline void Input::Instance::UnbindAxis(std::string name, Types ...args)
{
	auto axis = axes.find(name);
	if (axis != axes.end())
	{
		axis->second.notif.Unbind(args...);
	}
}
