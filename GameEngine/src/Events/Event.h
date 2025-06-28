#pragma once

enum class EventType
{
	WindowCloseEvent, WindowResizeEvent,
	MousePressedEvent, MouseReleasedEvent, MouseScrolledEvent, MouseMovedEvent,
	KeyPressedEvent, KeyReleasedEvent
};

class Event
{
	friend class EventDispatcher;
public:
	virtual EventType getType() const = 0;
	virtual std::string toString() const = 0;

protected:
	bool m_Handled = false;
	std::string m_name;
};

class EventDispatcher
{
	template <typename T>
	using EventFn = std::function<bool(T&)>;

public:
	EventDispatcher(Event& event)
		: m_Event(event) {}

	template <typename T>
	inline bool Dispatch(EventFn<T> func)
	{
		if (m_Event.getType() == T::getStaticType())
		{
			m_Event.m_Handled = func(*(T*)&m_Event);
			return true;
		}
		return false;
	}
private:
	Event& m_Event;
};


inline std::ostream& operator<< (std::ostream& os, const Event& e)
{
	return os << e.toString();
}