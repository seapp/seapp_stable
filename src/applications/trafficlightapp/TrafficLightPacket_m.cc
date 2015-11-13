//
// Generated file, do not edit! Created by nedtool 4.6 from applications/trafficlightapp/TrafficLightPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "TrafficLightPacket_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(TrafficLightBase);

TrafficLightBase::TrafficLightBase(const char *name, int kind) : ::cPacket(name,kind)
{
}

TrafficLightBase::TrafficLightBase(const TrafficLightBase& other) : ::cPacket(other)
{
    copy(other);
}

TrafficLightBase::~TrafficLightBase()
{
}

TrafficLightBase& TrafficLightBase::operator=(const TrafficLightBase& other)
{
    if (this==&other) return *this;
    ::cPacket::operator=(other);
    copy(other);
    return *this;
}

void TrafficLightBase::copy(const TrafficLightBase& other)
{
}

void TrafficLightBase::parsimPack(cCommBuffer *b)
{
    ::cPacket::parsimPack(b);
}

void TrafficLightBase::parsimUnpack(cCommBuffer *b)
{
    ::cPacket::parsimUnpack(b);
}

class TrafficLightBaseDescriptor : public cClassDescriptor
{
  public:
    TrafficLightBaseDescriptor();
    virtual ~TrafficLightBaseDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(TrafficLightBaseDescriptor);

TrafficLightBaseDescriptor::TrafficLightBaseDescriptor() : cClassDescriptor("TrafficLightBase", "cPacket")
{
}

TrafficLightBaseDescriptor::~TrafficLightBaseDescriptor()
{
}

bool TrafficLightBaseDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<TrafficLightBase *>(obj)!=NULL;
}

const char *TrafficLightBaseDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int TrafficLightBaseDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int TrafficLightBaseDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *TrafficLightBaseDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int TrafficLightBaseDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *TrafficLightBaseDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *TrafficLightBaseDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int TrafficLightBaseDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightBase *pp = (TrafficLightBase *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string TrafficLightBaseDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightBase *pp = (TrafficLightBase *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool TrafficLightBaseDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightBase *pp = (TrafficLightBase *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *TrafficLightBaseDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *TrafficLightBaseDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightBase *pp = (TrafficLightBase *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(TrafficLightStatus);

TrafficLightStatus::TrafficLightStatus(const char *name, int kind) : ::TrafficLightBase(name,kind)
{
    this->time_var = 0;
    this->roadType_var = 0;
    this->periodGreen_var = 0;
    this->periodYellow_var = 0;
    this->periodRed_var = 0;
}

TrafficLightStatus::TrafficLightStatus(const TrafficLightStatus& other) : ::TrafficLightBase(other)
{
    copy(other);
}

TrafficLightStatus::~TrafficLightStatus()
{
}

TrafficLightStatus& TrafficLightStatus::operator=(const TrafficLightStatus& other)
{
    if (this==&other) return *this;
    ::TrafficLightBase::operator=(other);
    copy(other);
    return *this;
}

void TrafficLightStatus::copy(const TrafficLightStatus& other)
{
    this->time_var = other.time_var;
    this->roadType_var = other.roadType_var;
    this->periodGreen_var = other.periodGreen_var;
    this->periodYellow_var = other.periodYellow_var;
    this->periodRed_var = other.periodRed_var;
}

void TrafficLightStatus::parsimPack(cCommBuffer *b)
{
    ::TrafficLightBase::parsimPack(b);
    doPacking(b,this->time_var);
    doPacking(b,this->roadType_var);
    doPacking(b,this->periodGreen_var);
    doPacking(b,this->periodYellow_var);
    doPacking(b,this->periodRed_var);
}

void TrafficLightStatus::parsimUnpack(cCommBuffer *b)
{
    ::TrafficLightBase::parsimUnpack(b);
    doUnpacking(b,this->time_var);
    doUnpacking(b,this->roadType_var);
    doUnpacking(b,this->periodGreen_var);
    doUnpacking(b,this->periodYellow_var);
    doUnpacking(b,this->periodRed_var);
}

double TrafficLightStatus::getTime() const
{
    return time_var;
}

void TrafficLightStatus::setTime(double time)
{
    this->time_var = time;
}

const char * TrafficLightStatus::getRoadType() const
{
    return roadType_var.c_str();
}

void TrafficLightStatus::setRoadType(const char * roadType)
{
    this->roadType_var = roadType;
}

double TrafficLightStatus::getPeriodGreen() const
{
    return periodGreen_var;
}

void TrafficLightStatus::setPeriodGreen(double periodGreen)
{
    this->periodGreen_var = periodGreen;
}

double TrafficLightStatus::getPeriodYellow() const
{
    return periodYellow_var;
}

void TrafficLightStatus::setPeriodYellow(double periodYellow)
{
    this->periodYellow_var = periodYellow;
}

double TrafficLightStatus::getPeriodRed() const
{
    return periodRed_var;
}

void TrafficLightStatus::setPeriodRed(double periodRed)
{
    this->periodRed_var = periodRed;
}

class TrafficLightStatusDescriptor : public cClassDescriptor
{
  public:
    TrafficLightStatusDescriptor();
    virtual ~TrafficLightStatusDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(TrafficLightStatusDescriptor);

TrafficLightStatusDescriptor::TrafficLightStatusDescriptor() : cClassDescriptor("TrafficLightStatus", "TrafficLightBase")
{
}

TrafficLightStatusDescriptor::~TrafficLightStatusDescriptor()
{
}

bool TrafficLightStatusDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<TrafficLightStatus *>(obj)!=NULL;
}

const char *TrafficLightStatusDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int TrafficLightStatusDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int TrafficLightStatusDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *TrafficLightStatusDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "time",
        "roadType",
        "periodGreen",
        "periodYellow",
        "periodRed",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int TrafficLightStatusDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "time")==0) return base+0;
    if (fieldName[0]=='r' && strcmp(fieldName, "roadType")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "periodGreen")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "periodYellow")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "periodRed")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *TrafficLightStatusDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "string",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *TrafficLightStatusDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int TrafficLightStatusDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightStatus *pp = (TrafficLightStatus *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string TrafficLightStatusDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightStatus *pp = (TrafficLightStatus *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getTime());
        case 1: return oppstring2string(pp->getRoadType());
        case 2: return double2string(pp->getPeriodGreen());
        case 3: return double2string(pp->getPeriodYellow());
        case 4: return double2string(pp->getPeriodRed());
        default: return "";
    }
}

bool TrafficLightStatusDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightStatus *pp = (TrafficLightStatus *)object; (void)pp;
    switch (field) {
        case 0: pp->setTime(string2double(value)); return true;
        case 1: pp->setRoadType((value)); return true;
        case 2: pp->setPeriodGreen(string2double(value)); return true;
        case 3: pp->setPeriodYellow(string2double(value)); return true;
        case 4: pp->setPeriodRed(string2double(value)); return true;
        default: return false;
    }
}

const char *TrafficLightStatusDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *TrafficLightStatusDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightStatus *pp = (TrafficLightStatus *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(TrafficLightCmd);

TrafficLightCmd::TrafficLightCmd(const char *name, int kind) : ::TrafficLightBase(name,kind)
{
    this->sequenceNumber_var = 0;
    this->periodGreen_var = 0;
    this->periodYellow_var = 0;
    this->periodRed_var = 0;
}

TrafficLightCmd::TrafficLightCmd(const TrafficLightCmd& other) : ::TrafficLightBase(other)
{
    copy(other);
}

TrafficLightCmd::~TrafficLightCmd()
{
}

TrafficLightCmd& TrafficLightCmd::operator=(const TrafficLightCmd& other)
{
    if (this==&other) return *this;
    ::TrafficLightBase::operator=(other);
    copy(other);
    return *this;
}

void TrafficLightCmd::copy(const TrafficLightCmd& other)
{
    this->sequenceNumber_var = other.sequenceNumber_var;
    this->periodGreen_var = other.periodGreen_var;
    this->periodYellow_var = other.periodYellow_var;
    this->periodRed_var = other.periodRed_var;
}

void TrafficLightCmd::parsimPack(cCommBuffer *b)
{
    ::TrafficLightBase::parsimPack(b);
    doPacking(b,this->sequenceNumber_var);
    doPacking(b,this->periodGreen_var);
    doPacking(b,this->periodYellow_var);
    doPacking(b,this->periodRed_var);
}

void TrafficLightCmd::parsimUnpack(cCommBuffer *b)
{
    ::TrafficLightBase::parsimUnpack(b);
    doUnpacking(b,this->sequenceNumber_var);
    doUnpacking(b,this->periodGreen_var);
    doUnpacking(b,this->periodYellow_var);
    doUnpacking(b,this->periodRed_var);
}

long TrafficLightCmd::getSequenceNumber() const
{
    return sequenceNumber_var;
}

void TrafficLightCmd::setSequenceNumber(long sequenceNumber)
{
    this->sequenceNumber_var = sequenceNumber;
}

double TrafficLightCmd::getPeriodGreen() const
{
    return periodGreen_var;
}

void TrafficLightCmd::setPeriodGreen(double periodGreen)
{
    this->periodGreen_var = periodGreen;
}

double TrafficLightCmd::getPeriodYellow() const
{
    return periodYellow_var;
}

void TrafficLightCmd::setPeriodYellow(double periodYellow)
{
    this->periodYellow_var = periodYellow;
}

double TrafficLightCmd::getPeriodRed() const
{
    return periodRed_var;
}

void TrafficLightCmd::setPeriodRed(double periodRed)
{
    this->periodRed_var = periodRed;
}

class TrafficLightCmdDescriptor : public cClassDescriptor
{
  public:
    TrafficLightCmdDescriptor();
    virtual ~TrafficLightCmdDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(TrafficLightCmdDescriptor);

TrafficLightCmdDescriptor::TrafficLightCmdDescriptor() : cClassDescriptor("TrafficLightCmd", "TrafficLightBase")
{
}

TrafficLightCmdDescriptor::~TrafficLightCmdDescriptor()
{
}

bool TrafficLightCmdDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<TrafficLightCmd *>(obj)!=NULL;
}

const char *TrafficLightCmdDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int TrafficLightCmdDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int TrafficLightCmdDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *TrafficLightCmdDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "sequenceNumber",
        "periodGreen",
        "periodYellow",
        "periodRed",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int TrafficLightCmdDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequenceNumber")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "periodGreen")==0) return base+1;
    if (fieldName[0]=='p' && strcmp(fieldName, "periodYellow")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "periodRed")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *TrafficLightCmdDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "long",
        "double",
        "double",
        "double",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *TrafficLightCmdDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int TrafficLightCmdDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightCmd *pp = (TrafficLightCmd *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string TrafficLightCmdDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightCmd *pp = (TrafficLightCmd *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSequenceNumber());
        case 1: return double2string(pp->getPeriodGreen());
        case 2: return double2string(pp->getPeriodYellow());
        case 3: return double2string(pp->getPeriodRed());
        default: return "";
    }
}

bool TrafficLightCmdDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightCmd *pp = (TrafficLightCmd *)object; (void)pp;
    switch (field) {
        case 0: pp->setSequenceNumber(string2long(value)); return true;
        case 1: pp->setPeriodGreen(string2double(value)); return true;
        case 2: pp->setPeriodYellow(string2double(value)); return true;
        case 3: pp->setPeriodRed(string2double(value)); return true;
        default: return false;
    }
}

const char *TrafficLightCmdDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *TrafficLightCmdDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    TrafficLightCmd *pp = (TrafficLightCmd *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


