//********************************************************************************//
// MIT License                                                                    //
//                                                                                //
// Copyright (c) 2022 TeamViewer Germany GmbH                                     //
//                                                                                //
// Permission is hereby granted, free of charge, to any person obtaining a copy   //
// of this software and associated documentation files (the "Software"), to deal  //
// in the Software without restriction, including without limitation the rights   //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      //
// copies of the Software, and to permit persons to whom the Software is          //
// furnished to do so, subject to the following conditions:                       //
//                                                                                //
// The above copyright notice and this permission notice shall be included in all //
// copies or substantial portions of the Software.                                //
//                                                                                //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  //
// SOFTWARE.                                                                      //
//********************************************************************************//
#include "PyAgentConnection.h"

#include <TVAgentAPI/AgentConnectionStringify.h>
#include <TVAgentAPI/IAgentAPI.h>
#include <TVAgentAPI/IAgentConnection.h>

#include "PyAccessControlModule.h"
#include "PyInstantSupportModule.h"
#include "PyTVSessionManagementModule.h"
#include "PyChatModule.h"
#include "PyLogging.h"
#include "PyTVAgentAPI.h"
#include "PythonHelpers.h"
#include "Typesystem.h"

#include <type_traits>
#include <limits>

using namespace tvagentapipy;

namespace
{

// Methods
PyObject* PyAgentConnection_start(PyAgentConnection* self, PyObject* args)
{
	(void)args;
	self->m_connection->start();

	Py_RETURN_NONE;
}

PyObject* PyAgentConnection_stop(PyAgentConnection* self, PyObject* args)
{
	(void)args;
	self->m_connection->stop();

	Py_RETURN_NONE;
}

PyObject* PyAgentConnection_processEvents(PyAgentConnection* self, PyObject* args, PyObject* kwargs)
{
	int waitForMoreEvents = false;
	long long timeoutMs = 0;

	char waitForMoreEventsArg[] = "waitForMoreEvents";
	char timeoutMsArg[] = "timeoutMs";
	char* kwargList[] = {waitForMoreEventsArg, timeoutMsArg, {}};
	if (!PyArg_ParseTupleAndKeywords(args, kwargs, "|pL:processEvents", kwargList, &waitForMoreEvents, &timeoutMs))
	{
		return nullptr;
	}

	if (timeoutMs < 0 || timeoutMs > static_cast<long long>(std::numeric_limits<uint32_t>::max()))
	{
		PyErr_Format(
			PyExc_OverflowError,
			"Given value for timeoutMs (%lli) is not in range of an unsigned 32-bit integer",
			timeoutMs);
		return nullptr;
	}

	const bool result = self->m_connection->processEvents(waitForMoreEvents, static_cast<uint32_t>(timeoutMs));
	if (PyErr_Occurred())
	{
		return nullptr;
	}

	if (!result)
	{
		Py_RETURN_FALSE;
	}

	Py_RETURN_TRUE;
}

PyObject* PyAgentConnection_getModule(PyAgentConnection* self, PyObject* arg)
{
	using Type = tvagentapi::IModule::Type;

	Type moduleType = EnumFromPyEnumValue<Type>(arg);
	if (PyErr_Occurred())
	{
		return nullptr;
	}

	tvagentapi::IModule* module = self->m_connection->getModule(moduleType);
	PyObject*& pyModule = (*self->m_modules)[module];
	if (!pyModule)
	{
		pyModule = [self, moduleType]() -> PyObject*
		{
			switch (moduleType)
			{
				case tvagentapi::IModule::Type::AccessControl:
					return reinterpret_cast<PyObject*>(
						MakeWrapperObject<PyAccessControlModule>(self));
				case tvagentapi::IModule::Type::InstantSupport:
					return reinterpret_cast<PyObject*>(
						MakeWrapperObject<PyInstantSupportModule>(self));
				case tvagentapi::IModule::Type::TVSessionManagement:
					return reinterpret_cast<PyObject*>(
						MakeWrapperObject<PyTVSessionManagementModule>(self));
				case tvagentapi::IModule::Type::Chat:
					return reinterpret_cast<PyObject*>(
						MakeWrapperObject<PyChatModule>(self));
			}
			PyErr_BadInternalCall();
			return nullptr;
		}();
	}

	Py_XINCREF(pyModule);
	return pyModule;
}

PyObject* PyAgentConnection_setCallbacks(
	PyAgentConnection* self,
	PyObject* args,
	PyObject* kwargs)
{
	PyObject* statusChangedArg = Py_None;

	char statusChangedArgName[] = "statusChanged";
	char* kwargList[] = {statusChangedArgName, {}};
	if (!PyArg_ParseTupleAndKeywords(
		args,
		kwargs,
		"|O:setCallbacks",
		kwargList,
		&statusChangedArg))
	{
		return nullptr;
	}

	statusChangedArg = statusChangedArg == Py_None ? nullptr : statusChangedArg;

	if (statusChangedArg && !PyCallable_Check(statusChangedArg))
	{
		PyErr_Format(PyExc_TypeError, "%R is not callable", statusChangedArg);
		return nullptr;
	}

	Py_XINCREF(statusChangedArg);
	Py_XDECREF(self->m_pyStatusChangedCallback);
	self->m_pyStatusChangedCallback = statusChangedArg;

	auto statusChangedCallback = [](
		tvagentapi::IAgentConnection::Status status,
		void* userdata)
	{
		auto pyStatusChangedPyCallback = static_cast<PyObject*>(userdata);

		PyObject* enumVal = PyEnumValue(
			GetPyTypeAgentConnection_Status(),
			tvagentapi::toCString(status));

		// TODO When Python >= 3.9 use PyObject_CallOneArg
		PyObject* callArgs = Py_BuildValue("(O)", enumVal);
		PyObject* result = PyObject_CallObject(pyStatusChangedPyCallback, callArgs);
		Py_XDECREF(result);
		Py_DECREF(callArgs);
		Py_DECREF(enumVal);
	};

	if (statusChangedArg)
	{
		self->m_connection->setStatusChangedCallback({statusChangedCallback, statusChangedArg});
	}
	else
	{
		self->m_connection->setStatusChangedCallback({});
	}

	Py_RETURN_NONE;
}

namespace DocStrings
{

PyDoc_STRVAR(start,
R"__(start($self)
--

Tries to establish a connection to a running TeamViewer IoT Agent and maintains it until stop() is called.
The connection is re-established automatically if it was lost.
To be notified about the connectivity, set the statusChanged callback.
)__");

PyDoc_STRVAR(stop,
R"__(stop($self)
--

Shuts down all communication with the TeamViewer IoT Agent and changes state afterwards to Disconnected.
)__");

PyDoc_STRVAR(processEvents,
R"__(processEvents($self, waitForMoreEvents, timeoutMs)
--

Is responsible for executing all actions/events/etc. (or simply: "events") that are pending in the order they are issued:
- triggers user's callbacks
- updates internal states
- notifies modules
- handles modules' requests
The method can optionally wait for more events if no events are queued.

:param bool waitForMoreEvents: if true and no queued events, wait for events to be queued, otherwise process the queued events immediately.
:param int timeoutMs: wait timeout in milliseconds. If zero, wait indefinitely.
)__");

PyDoc_STRVAR(getModule,
R"__(getModule($self, type)
--

Returns an abstract module if possible for the given type.

:param tvagentapi.Module.Type type: what type of module to create.
:return module object.
)__");

PyDoc_STRVAR(setCallbacks,
R"__(setCallbacks($self, statusChanged=None)
--

Sets callback to handle changes in connection status.

:param statusChanged: called when the connection status changes
:type statusChanged: callback(tvagentapi.AgentConnection.Status status)
)__");

} // namespace DocStrings

PyMethodDef PyAgentConnection_methods[] =
{
	{
		"start",
		PyCFunctionCast(PyAgentConnection_start),
		METH_NOARGS,
		DocStrings::start
	},
	{
		"stop",
		PyCFunctionCast(PyAgentConnection_stop),
		METH_NOARGS,
		DocStrings::stop
	},
	{
		"processEvents",
		PyCFunctionCast(PyAgentConnection_processEvents),
		METH_VARARGS | METH_KEYWORDS,
		DocStrings::processEvents
	},
	{
		"getModule",
		PyCFunctionCast(PyAgentConnection_getModule),
		METH_O,
		DocStrings::getModule
	},
	{
		"setCallbacks",
		PyCFunctionCast(PyAgentConnection_setCallbacks),
		METH_VARARGS | METH_KEYWORDS,
		DocStrings::setCallbacks
	},

	{} // Sentinel
};

} // namespace

namespace tvagentapipy
{

PyAgentConnection::PyAgentConnection(PyTVAgentAPI* pyAgentAPI, PyLogging* pyLogging)
	: m_modules{std::make_unique<std::map<tvagentapi::IModule*, PyObject*>>()}
	, m_pyAgentAPI{pyAgentAPI}
	, m_pyLogging{pyLogging}
{
	m_connection = m_pyAgentAPI->m_agentAPI->createAgentConnectionLocal(
		m_pyLogging ? m_pyLogging->m_logging : nullptr);
	Py_INCREF(m_pyAgentAPI);
	Py_XINCREF(m_pyLogging);
}

PyAgentConnection::~PyAgentConnection()
{
	PyObject_ClearWeakRefs(reinterpret_cast<PyObject*>(this));

	for (const auto& p : *m_modules)
	{
		Py_XDECREF(p.second);
	}

	m_pyAgentAPI->m_agentAPI->destroyAgentConnection(m_connection);
	Py_XDECREF(m_pyLogging);
	Py_DECREF(m_pyAgentAPI);
	Py_XDECREF(m_pyStatusChangedCallback);
}

bool PyAgentConnection::IsReady() const
{
	return !!m_connection;
}

PyTypeObject* GetPyTypeAgentConnection()
{
	static PyTypeObject* pyTypeAgentConnection = []() -> PyTypeObject*
	{
		static PyTypeObject result = PyTypeObjectInitialized();
		result.tp_name = "tvagentapi.AgentConnection";

		static_assert(
			std::is_standard_layout<PyAgentConnection>::value,
			"PyAgentConnection has non-standard layout, offsetof below has UB");

		result.tp_basicsize = sizeof(PyAgentConnection);
		result.tp_dealloc = reinterpret_cast<destructor>(
			DeallocWrapperObject<PyAgentConnection>);
		result.tp_flags = Py_TPFLAGS_DEFAULT;
		result.tp_doc = "Agent Connection class";
		result.tp_methods = PyAgentConnection_methods;
		result.tp_weaklistoffset = offsetof(PyAgentConnection, m_weakRefList);

		result.tp_dict = PyDict_New();
		PyDict_SetItemString(
			result.tp_dict,
			"Status",
			reinterpret_cast<PyObject*>(GetPyTypeAgentConnection_Status()));

		if (PyType_Ready(&result) < 0)
		{
			return nullptr;
		}

		return &result;
	}();
	return pyTypeAgentConnection;
}

PyTypeObject* GetPyTypeAgentConnection_Status()
{
	static PyTypeObject* pyTypeAgentConnection_Status = []() -> PyTypeObject*
	{
		using Status = tvagentapi::IAgentConnection::Status;
		using tvagentapi::toCString;

		PyTypeObject* result =
			CreateEnumType(
				"tvagentapi.AgentConnection.Status",
				{{toCString(Status::Disconnected), static_cast<long>(Status::Disconnected)},
				 {toCString(Status::Disconnecting), static_cast<long>(Status::Disconnecting)},
				 {toCString(Status::Connecting), static_cast<long>(Status::Connecting)},
				 {toCString(Status::Connected), static_cast<long>(Status::Connected)},
				 {toCString(Status::ConnectionLost), static_cast<long>(Status::ConnectionLost)}});

		return result;
	}();
	return pyTypeAgentConnection_Status;
}

} // namespace tvagentapipy
