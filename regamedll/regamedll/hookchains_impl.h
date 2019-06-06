/*
*
*    This program is free software; you can redistribute it and/or modify it
*    under the terms of the GNU General Public License as published by the
*    Free Software Foundation; either version 2 of the License, or (at
*    your option) any later version.
*
*    This program is distributed in the hope that it will be useful, but
*    WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*    General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program; if not, write to the Free Software Foundation,
*    Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*    In addition, as a special exception, the author gives permission to
*    link the code of this program with the Half-Life Game Engine ("HL
*    Engine") and Modified Game Libraries ("MODs") developed by Valve,
*    L.L.C ("Valve").  You must obey the GNU General Public License in all
*    respects for all of the code used other than the HL Engine and MODs
*    from Valve.  If you modify this file, you may extend this exception
*    to your version of the file, but you are not obligated to do so.  If
*    you do not wish to do so, delete this exception statement from your
*    version.
*
*/

#pragma once

#include "hookchains.h"

#define MAX_HOOKS_IN_CHAIN 30

template <typename t_ret, typename t_class, typename ...t_args>
bool is_void(t_ret (t_class::*)(t_args...)) { return false; }

template <typename t_ret, typename ...t_args>
bool is_void(t_ret (*)(t_args...)) { return false; }

template <typename t_class, typename ...t_args>
bool is_void(void (t_class::*)(t_args...)) { return true; }

template <typename ...t_args>
bool is_void(void (*)(t_args...)) { return true; }

// Implementation for chains in modules
template <typename t_ret, typename ...t_args>
class IHookChainImpl : public IHookChain<t_ret, t_args...> {
public:
	typedef t_ret(*hookfunc_t)(IHookChain<t_ret, t_args...>*, t_args...);
	typedef t_ret(*origfunc_t)(t_args...);

	IHookChainImpl(void** hooks, origfunc_t orig) : m_Hooks(hooks), m_OriginalFunc(orig)
	{
		if (orig == nullptr && !is_void(orig))
			Sys_Error("%s: Non-void HookChain without original function.", __FUNC__);
	}

	virtual ~IHookChainImpl() {}

	virtual t_ret callNext(t_args... args) {
		hookfunc_t nexthook = (hookfunc_t)m_Hooks[0];

		if (nexthook)
		{
			IHookChainImpl nextChain(m_Hooks + 1, m_OriginalFunc);
			return nexthook(&nextChain, args...);
		}

		return m_OriginalFunc ? m_OriginalFunc(args...) : t_ret();
	}

	virtual t_ret callOriginal(t_args... args) {
		return m_OriginalFunc ? m_OriginalFunc(args...) : t_ret();
	}

private:
	void** m_Hooks;
	origfunc_t m_OriginalFunc;
};

// Implementation for chains in modules
template <typename t_ret, typename t_class, typename ...t_args>
class IHookChainClassImpl : public IHookChainClass<t_ret, t_class, t_args...> {
public:
	typedef t_ret(*hookfunc_t)(IHookChainClass<t_ret, t_class, t_args...>*, t_class *, t_args...);
	typedef t_ret(t_class::*origfunc_t)(t_args...);

	IHookChainClassImpl(void** hooks, origfunc_t orig) : m_Hooks(hooks), m_OriginalFunc(orig)
	{
		if (orig == nullptr && !is_void(orig))
			Sys_Error("%s: Non-void HookChain without original function.", __FUNC__);
	}

	virtual ~IHookChainClassImpl() {}

	virtual t_ret callNext(t_class *object, t_args... args) {
		hookfunc_t nexthook = (hookfunc_t)m_Hooks[0];

		if (nexthook)
		{
			IHookChainClassImpl nextChain(m_Hooks + 1, m_OriginalFunc);
			return nexthook(&nextChain, object, args...);
		}

		return m_OriginalFunc ? (object->*m_OriginalFunc)(args...) : t_ret();
	}

	virtual t_ret callOriginal(t_class *object, t_args... args) {
		return m_OriginalFunc ? (object->*m_OriginalFunc)(args...) : t_ret();
	}

private:
	void** m_Hooks;
	origfunc_t m_OriginalFunc;
};

// Implementation for chains in modules
template <typename t_ret, typename t_class, typename ...t_args>
class IHookChainClassEmptyImpl : public IHookChain<t_ret, t_args...> {
public:
	typedef t_ret(*hookfunc_t)(IHookChain<t_ret, t_args...>*, t_args...);
	typedef t_ret(t_class::*origfunc_t)(t_args...);

	IHookChainClassEmptyImpl(void** hooks, origfunc_t orig, t_class *object) : m_Hooks(hooks), m_Object(object), m_OriginalFunc(orig)
	{
		if (orig == nullptr && !is_void(orig))
			Sys_Error("%s: Non-void HookChain without original function.", __FUNC__);
	}

	virtual ~IHookChainClassEmptyImpl() {}

	virtual t_ret callNext(t_args... args) {
		hookfunc_t nexthook = (hookfunc_t)m_Hooks[0];

		if (nexthook)
		{
			IHookChainClassEmptyImpl nextChain(m_Hooks + 1, m_OriginalFunc, m_Object);
			return nexthook(&nextChain, args...);
		}

		return m_OriginalFunc ? (m_Object->*m_OriginalFunc)(args...) : t_ret();
	}

	virtual t_ret callOriginal(t_args... args) {
		return m_OriginalFunc ? (m_Object->*m_OriginalFunc)(args...) : t_ret();
	}

private:
	void** m_Hooks;
	t_class *m_Object;
	origfunc_t m_OriginalFunc;
};

class AbstractHookChainRegistry {
protected:
	void* m_Hooks[MAX_HOOKS_IN_CHAIN + 1]; // +1 for null
	int m_Priorities[MAX_HOOKS_IN_CHAIN + 1];
	int m_NumHooks;

protected:
	void addHook(void* hookFunc, int priority);
	bool findHook(void* hookFunc) const;
	void removeHook(void* hookFunc);

public:
	AbstractHookChainRegistry();
};

template <typename t_ret, typename ...t_args>
class IHookChainRegistryImpl : public IHookChainRegistry<t_ret, t_args...>, public AbstractHookChainRegistry {
public:
	typedef t_ret(*hookfunc_t)(IHookChain<t_ret, t_args...>*, t_args...);
	typedef t_ret(*origfunc_t)(t_args...);

	virtual ~IHookChainRegistryImpl() { }

	t_ret callChain(origfunc_t origFunc, t_args... args) {
		IHookChainImpl<t_ret, t_args...> chain(m_Hooks, origFunc);
		return chain.callNext(args...);
	}

	virtual void registerHook(hookfunc_t hook, int priority) {
		addHook((void*)hook, priority);
	}
	virtual void unregisterHook(hookfunc_t hook) {
		removeHook((void*)hook);
	}
};

template <typename t_ret, typename t_class, typename ...t_args>
class IHookChainRegistryClassImpl : public IHookChainRegistryClass<t_ret, t_class, t_args...>, public AbstractHookChainRegistry {
public:
	typedef t_ret(*hookfunc_t)(IHookChainClass<t_ret, t_class, t_args...>*, t_class *, t_args...);
	typedef t_ret(t_class::*origfunc_t)(t_args...);

	virtual ~IHookChainRegistryClassImpl() { }

	t_ret callChain(origfunc_t origFunc, t_class *object, t_args... args) {
		IHookChainClassImpl<t_ret, t_class, t_args...> chain(m_Hooks, origFunc);
		return chain.callNext(object, args...);
	}

	virtual void registerHook(hookfunc_t hook, int priority) {
		addHook((void*)hook, priority);
	}
	virtual void unregisterHook(hookfunc_t hook) {
		removeHook((void*)hook);
	}
};

template <typename t_ret, typename t_class, typename ...t_args>
class IHookChainRegistryClassEmptyImpl : public IHookChainRegistry<t_ret, t_args...>, public AbstractHookChainRegistry {
public:
	typedef t_ret(*hookfunc_t)(IHookChain<t_ret, t_args...>*, t_args...);
	typedef t_ret(t_class::*origfunc_t)(t_args...);

	virtual ~IHookChainRegistryClassEmptyImpl() { }

	t_ret callChain(origfunc_t origFunc, t_class *object, t_args... args) {
		IHookChainClassEmptyImpl<t_ret, t_class, t_args...> chain(m_Hooks, origFunc, object);
		return chain.callNext(args...);
	}

	virtual void registerHook(hookfunc_t hook, int priority) {
		addHook((void*)hook, priority);
	}
	virtual void unregisterHook(hookfunc_t hook) {
		removeHook((void*)hook);
	}
};
