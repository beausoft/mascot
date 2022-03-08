#pragma once
#include <functional>
#include <list>
#include <algorithm>

using namespace std;

// ״̬����https://gitee.com/andwp/cpp-state

// ��ʾ����
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
	/// ���͡�
	/// </summary>
	/// <returns></returns>
	TType type() const {
		return m_type;
	}

	/// <summary>
	///  �������͡�
	/// </summary>
	/// <param name="type"></param>
	void setType(const TType& type) {
		m_type = type;
	}
private:
	TType m_type;
};

template<typename TType> class State;   // ����״̬

/// <summary>
/// ��ʾ״̬ת����
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
	/// ״̬ת����
	/// </summary>
	/// <param name="type"></param>
	/// <param name="state"></param>
	Transition(const TType& type, State<TType>* state) {
		m_type = type;
		m_state = state;
	}
	/// <summary>
	/// ����ת�������͡�
	/// </summary>
	/// <param name="type"></param>
	void setType(TType type) {
		m_type = type;
	}
	/// <summary>
	/// ��ȡת�������͡�
	/// </summary>
	/// <returns></returns>
	TType type() const {
		return m_type;
	}
	/// <summary>
	/// ��ȡ״̬��
	/// </summary>
	/// <typeparam name="TType"></typeparam>
	State<TType>* state() const {
		return m_state;
	}
	/// <summary>
	/// ����״̬��
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
/// ��ʾ״̬��
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
	/// ���һ��ת����
	/// </summary>
	/// <param name="type"></param>
	/// <param name="dest"></param>
	Transition<TType>* addTransition(const TType& type, State<TType>* dest) {
		Transition<TType>* transition = new Transition<TType>(type, dest);
		m_trans.push_back(transition);
		return transition;
	}
	/// <summary>
	/// ִ�в�����
	/// </summary>
	/// <param name="action"></param>
	/// <returns>���ز�����Ӧ��״̬��</returns>
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
	/// ���ý���״̬��ִ�лص���
	/// </summary>
	/// <param name="enterCall"></param>
	void setEnter(function<void()> enterCall) {
		m_enter = enterCall;
	}
	/// <summary>
	/// ����ִ��״̬�Ļص���
	/// </summary>
	/// <param name="execCall"></param>
	void setExec(function<void()> execCall) {
		m_exec = execCall;
	}
	/// <summary>
	/// �����˳�״̬�Ļص���
	/// </summary>
	/// <param name="exitCall"></param>
	void setExit(function<void()> exitCall) {
		m_exit = exitCall;
	}
	/// <summary>
	/// ����״̬��
	/// </summary>
	void onEnter() {
		if (m_enter != nullptr)
		{
			m_enter();
		}
	}
	/// <summary>
	/// ִ��״̬��
	/// </summary>
	void onExec() {
		if (m_exec)
		{
			m_exec();
		}
	}
	/// <summary>
	/// �˳�״̬��
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
/// ��ʾ״̬����
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
	/// ���״̬��
	/// </summary>
	/// <param name="state"></param>
	void addState(State<TType>* state) {
		if (state != nullptr)
		{
			m_states.push_back(state);
		}
	}
	/// <summary>
	/// ��ʼ��״̬��
	/// </summary>
	/// <param name="state"></param>
	void initState(State<TType>* state) {
		m_currentState = state;
	}
	/// <summary>
	/// ����״̬����ʧ�ܷ���false��
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
	/// ִ�д���
	/// </summary>
	/// <param name="action"></param>
	/// <returns></returns>
	State<TType>* doAction(const Action<TType>& action) {
		auto state = m_currentState->doAction(action);
		if (!state)
		{
			return state;
		}
		// ״̬δ�仯�������
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
	list<State<TType>*> m_states; // ״̬�����ϡ�
	State<TType>* m_currentState; // ��ǰ״̬��
};
