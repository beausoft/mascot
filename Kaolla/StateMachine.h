#pragma once
#include <functional>
#include <list>
#include <algorithm>

using namespace std;

// 状态机：https://gitee.com/andwp/cpp-state

// 表示动作
template<typename TType>
class Action
{
public:
	Action() { 
	}
	Action(const TType& type) {
		setType(type);
	}
	/// <summary>
	/// 类型。
	/// </summary>
	/// <returns></returns>
	TType type() const {
		return m_type;
	}

	/// <summary>
	///  设置类型。
	/// </summary>
	/// <param name="type"></param>
	void setType(const TType& type) {
		m_type = type;
	}
private:
	TType m_type;
};

template<typename TType> class State;   // 声明状态

/// <summary>
/// 表示状态转换。
/// </summary>
/// <typeparam name="TType"></typeparam>
template<typename TType>
class Transition
{
public:
	Transition() {
		m_state = nullptr;
	}
	/// <summary>
	/// 状态转换。
	/// </summary>
	/// <param name="type"></param>
	/// <param name="state"></param>
	Transition(const TType& type, State<TType>* state) {
		m_type = type;
		m_state = state;
	}
	/// <summary>
	/// 设置转换的类型。
	/// </summary>
	/// <param name="type"></param>
	void setType(TType type) {
		m_type = type;
	}
	/// <summary>
	/// 获取转换的类型。
	/// </summary>
	/// <returns></returns>
	TType type() const {
		return m_type;
	}
	/// <summary>
	/// 获取状态。
	/// </summary>
	/// <typeparam name="TType"></typeparam>
	State<TType>* state() const {
		return m_state;
	}
	/// <summary>
	/// 设置状态。
	/// </summary>
	/// <param name="state"></param>
	void setState(State<TType>* state) {
		m_state = state;
	}
private:
	TType m_type;
	State<TType>* m_state;
};

/// <summary>
/// 表示状态。
/// </summary> 
/// <typeparam name="TType"></typeparam>
template<typename TType>
class State
{
public:
	State() {
	}

	~State() {
		for_each(m_trans.begin(), m_trans.end(), [](Transition<TType>* item) {delete item; });
		m_trans.clear();
	}
	/// <summary>
	/// 添加一个转换。
	/// </summary>
	/// <param name="type"></param>
	/// <param name="dest"></param>
	Transition<TType>* addTransition(const TType& type, State<TType>* dest) {
		Transition<TType>* transition = new Transition<TType>(type, dest);
		m_trans.push_back(transition);
		return transition;
	}
	/// <summary>
	/// 执行操作。
	/// </summary>
	/// <param name="action"></param>
	/// <returns>返回操作对应的状态。</returns>
	State<TType>* doAction(const Action<TType>& action) {
		Transition<TType>* transition = nullptr;

		for (auto item = m_trans.begin(); item != m_trans.end(); item++)
		{
			if ((*item)->type() == action.type())
			{
				transition = (*item);
				break;
			}
		}
		State<TType>* state = nullptr;
		if (transition)
		{
			state = transition->state();
		}
		return state;
	}
public:
	/// <summary>
	/// 设置进入状态的执行回调。
	/// </summary>
	/// <param name="enterCall"></param>
	void setEnter(function<void()> enterCall) {
		m_enter = enterCall;
	}
	/// <summary>
	/// 设置执行状态的回调。
	/// </summary>
	/// <param name="execCall"></param>
	void setExec(function<void()> execCall) {
		m_exec = execCall;
	}
	/// <summary>
	/// 设置退出状态的回调。
	/// </summary>
	/// <param name="exitCall"></param>
	void setExit(function<void()> exitCall) {
		m_exit = exitCall;
	}
	/// <summary>
	/// 进入状态。
	/// </summary>
	void onEnter() {
		if (m_enter != nullptr)
		{
			m_enter();
		}
	}
	/// <summary>
	/// 执行状态。
	/// </summary>
	void onExec() {
		if (m_exec)
		{
			m_exec();
		}
	}
	/// <summary>
	/// 退出状态。
	/// </summary>
	void onExit() {
		if (m_exit) {
			m_exit();
		}
	}
private:
	list<Transition<TType>*>  m_trans;
	function<void()> m_enter;
	function<void()> m_exec;
	function<void()> m_exit;
};

/// <summary>
/// 表示状态机。
/// </summary>
/// <typeparam name="TType"></typeparam>
template<typename TType>
class StateMachine
{
public:
	StateMachine() {
		m_currentState = nullptr;
	}
	~StateMachine() {
		for_each(m_states.begin(), m_states.end(), [](State<TType>* item) {delete item; });
		m_states.clear();
	}
	/// <summary>
	/// 添加状态。
	/// </summary>
	/// <param name="state"></param>
	void addState(State<TType>* state) {
		if (state != nullptr)
		{
			m_states.push_back(state);
		}
	}
	/// <summary>
	/// 初始的状态。
	/// </summary>
	/// <param name="state"></param>
	void initState(State<TType>* state) {
		m_currentState = state;
	}
	/// <summary>
	/// 启动状态机，失败返回false。
	/// </summary>
	/// <returns></returns>
	bool start() {
		if (!m_currentState)
		{
			return false;
		}
		m_currentState->onEnter();
		m_currentState->onExec();
		return true;
	}
	/// <summary>
	/// 执行处理。
	/// </summary>
	/// <param name="action"></param>
	/// <returns></returns>
	State<TType>* doAction(const Action<TType>& action) {
		auto state = m_currentState->doAction(action);
		if (!state)
		{
			return state;
		}
		// 状态未变化的情况。
		if (m_currentState != state)
		{
			m_currentState->onExit();
			m_currentState = state;
			m_currentState->onEnter();
		}
		m_currentState->onExec();
		return state;
	}
private:
	list<State<TType>*> m_states; // 状态机集合。
	State<TType>* m_currentState; // 当前状态。
};
