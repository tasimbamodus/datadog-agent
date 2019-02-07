// Unless explicitly stated otherwise all files in this repository are licensed
// under the Apache License Version 2.0.
// This product includes software developed at Datadog (https://www.datadoghq.com/).
// Copyright 2019 Datadog, Inc.
#ifndef DATADOG_AGENT_SIX_SIX_H
#define DATADOG_AGENT_SIX_SIX_H
#include <string>

struct SixPyObject {};

class Six {
public:
    enum MethType { NOARGS = 0, ARGS, KEYWORDS };

    enum ExtensionModule { DATADOG_AGENT };

    Six()
        : _module_unknown("")
        , _module_datadog_agent("datadog_agent") {};
    virtual ~Six() {};

    // Public API
    virtual void init(const char *pythonHome) = 0;
    virtual int addModuleFunction(ExtensionModule module, MethType t, const char *funcName, void *func) = 0;

    // Public Const API
    virtual bool isInitialized() const = 0;
    virtual const char *getPyVersion() const = 0;
    virtual int runSimpleString(const char *code) const = 0;
    virtual SixPyObject *getNone() const = 0;

protected:
    const std::string &getExtensionModuleName(ExtensionModule);
    const std::string &getExtensionModuleUnknown() { return _module_unknown; }

    std::string _error;

private:
    // these strings need to be alive for the whole interpreter lifetime because
    // they'll be used from the CPython Inittab
    std::string _module_unknown;
    std::string _module_datadog_agent;
};

typedef Six *create_t();
typedef void destroy_t(Six *);

#endif