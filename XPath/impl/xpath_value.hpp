#ifndef ARABICA_XPATHIC_XPATH_VALUE_H
#define ARABICA_XPATHIC_XPATH_VALUE_H

#include <string>
#include <DOM/Node.h>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <Utils/StringAdaptor.h>
#include "xpath_object.hpp"
#include "xpath_expression.hpp"

namespace Arabica
{
namespace XPath
{

template<class string_type, class string_adaptor>
class BoolValue : public XPathValue<string_type>, public XPathExpression<string_type, string_adaptor>
{
public:
  BoolValue(bool value) :
      value_(value) { }

  static XPathValuePtr<string_type> createValue(bool value) { return XPathValuePtr<string_type>(new BoolValue(value)); }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return XPathValuePtr<string_type>(new BoolValue(value_));
  } // evaluate
  virtual bool evaluateAsBool(const DOM::Node<string_type>& context) { return asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<string_type>& context) { return asNumber(); }
  virtual string_type evaluateAsString(const DOM::Node<string_type>& context) { return asString(); }
  virtual NodeSet<string_type> evaluateAsNodeSet(const DOM::Node<string_type>& context) { return asNodeSet(); }

  virtual bool asBool() const { return value_; }
  virtual double asNumber() const { return value_ ? 1 : 0; }
  virtual string_type asString() const { return string_adaptor::construct_from_utf8(value_ ? "true" : "false"); }
  virtual const NodeSet<string_type>& asNodeSet() const { static NodeSet<string_type> empty; return empty; }

  virtual ValueType type() const { return BOOL; }

private:
  bool value_;
}; // class BoolValue

template<class string_type, class string_adaptor>
class NumericValue : public XPathValue<string_type>, public XPathExpression<string_type, string_adaptor>
{
public:
  NumericValue(double value) :
      value_(value) { }
  
  static XPathValuePtr<string_type> createValue(double value) { return XPathValuePtr<string_type>(new NumericValue(value)); }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return createValue(value_);
  } // evaluate
  virtual bool evaluateAsBool(const DOM::Node<string_type>& context) { return asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<string_type>& context) { return asNumber(); }
  virtual string_type evaluateAsString(const DOM::Node<string_type>& context) { return asString(); }
  virtual NodeSet<string_type> evaluateAsNodeSet(const DOM::Node<string_type>& context) { return asNodeSet(); }

  virtual bool asBool() const { return (value_ != 0.0); }
  virtual double asNumber() const { return value_; }
  virtual string_type asString() const
  {
    if(isNaN(value_)) 
      return string_adaptor::construct_from_utf8("NaN");
    if(isInfinity(value_))
      return string_adaptor::construct_from_utf8("Infinity");
    if(isNegativeInfinity(value_))
      return string_adaptor::construct_from_utf8("-Infinity");
    return string_adaptor::construct_from_utf8(boost::lexical_cast<std::string>(value_).c_str());
  } // asString
  virtual const NodeSet<string_type>& asNodeSet() const { static NodeSet<string_type> empty; return empty; }

  virtual ValueType type() const { return NUMBER; }

private:
  double value_;
}; // class NumberValue

template<class string_type, class string_adaptor>
class StringValue : public XPathValue<string_type>, public XPathExpression<string_type, string_adaptor>
{
public:
  StringValue(const char* value) :
      value_(string_adaptor::construct_from_utf8(value)) { }
  StringValue(const string_type& value) :
      value_(value) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return XPathValuePtr<string_type>(new StringValue(value_));
  } // evaluate
  virtual bool evaluateAsBool(const DOM::Node<string_type>& context) { return asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<string_type>& context) { return asNumber(); }
  virtual string_type evaluateAsString(const DOM::Node<string_type>& context) { return asString(); }
  virtual NodeSet<string_type> evaluateAsNodeSet() const { return asNodeSet(); }

  virtual bool asBool() const { return !string_adaptor::empty(value_); }
  virtual double asNumber() const 
  { 
    return impl::stringAsNumber(value_);
  } // asNumber
  virtual string_type asString() const { return value_; }
  virtual const NodeSet<string_type>& asNodeSet() const { static NodeSet<string_type> empty; return empty; }
 
  virtual ValueType type() const { return STRING; }

private:
  string_type value_;
}; // class StringValue

template<class string_type, class string_adaptor>
class NodeSetValue : public XPathValue<string_type>, public XPathExpression<string_type, string_adaptor>
{
public:
  NodeSetValue(const NodeSet<string_type>& set) : set_(set) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    return XPathValuePtr<string_type>(this);
  } // evaluate
  virtual bool evaluateAsBool(const DOM::Node<string_type>& context) const{ return asBool(); }
  virtual double evaluateAsNumber(const DOM::Node<string_type>& context) const { return asNumber(); }
  virtual string_type evaluateAsString(const DOM::Node<string_type>& context) const { return asString(); }
  virtual const NodeSet<string_type>& evaluateAsNodeSet() const { return asNodeSet(); }

  virtual bool asBool() const 
  { 
    return !set_.empty();
  } // asBool
  virtual double asNumber() const 
  { 
    return impl::stringAsNumber(asString());
  } // asNumber
  virtual string_type asString() const 
  { 
    return !set_.empty() ? impl::nodeStringValue<string_type, string_adaptor>(set_.top()) : string_adaptor::construct_from_utf8("");
  } // asStringx
  virtual const NodeSet<string_type>& asNodeSet() const { return set_; }

  virtual ValueType type() const { return NODE_SET; }

private:
  NodeSet<string_type> set_;
}; // NodeSetValue

} // namespace XPath
} // namespace Arabica

#endif
