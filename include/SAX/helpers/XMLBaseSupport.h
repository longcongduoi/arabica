#ifndef ARABICA_XMLBASE_SUPPORT_H
#define ARABICA_XMLBASE_SUPPORT_H

/*
 * $Id$
 *
 * XMLBaseSupport is a helper class for tracking xml:base attributes.
 * Usage:
 *   set location of the containing document by calling setDocumentLocation
 *       this is usually done when during the setDocumentLocator SAX event
 *   forward each startElement and endElement event 
 *   to resolve a relative URL against the current base, call makeAbsolute
 *
 * Derived from org.apache.cocoon.xml.XMLBaseSupport.
 *
 * XML Base is described at http://www.w3.org/TR/xmlbase/
 */

#include <stack>
#include <utility>
#include <sstream>
#include <XML/UnicodeCharacters.h>
#include <Utils/uri.hpp>

namespace SAX
{

template<class string_type, class string_adaptor_type>
struct XMLBaseConstants
{
  typedef string_type stringT;
  typedef string_adaptor_type string_adaptorT;

  const stringT xml;
  const stringT xml_uri;
  const stringT colon;
  const stringT base;

  XMLBaseConstants() :
    xml(string_adaptorT().construct_from_utf8("xml")),
    xml_uri(string_adaptorT().construct_from_utf8("http://www.w3.org/XML/1998/namespace")),
    colon(string_adaptorT().construct_from_utf8(":")),
    base(string_adaptorT().construct_from_utf8("base"))
  {
  } // XMLBaseConstants
}; // struct XMLBaseConstants

template<class string_type, class string_adaptor_type = Arabica::default_string_adaptor<string_type> >
class basic_XMLBaseSupport
{
public:
  typedef string_type stringT;
  typedef string_adaptor_type string_adaptorT;
  typedef typename string_adaptor_type::value_type valueT;
  typedef basic_Attributes<stringT> AttributesT;

  basic_XMLBaseSupport() :
      depth_(0) { }

  void setDocumentLocation(const stringT& loc)
  {
    bases_.push(std::make_pair(-1, trim(loc)));
  } // setDocumentLocation

  void startElement(const AttributesT& atts)
  {
    ++depth_;
    stringT base = atts.getValue(xbc_.xml_uri, xbc_.base);
    if(base.empty())
      return;

    stringT baseURI = absolutiseAndTrim(currentBase(), base);
    bases_.push(std::make_pair(depth_, baseURI));
  } // startElement

  void endElement()
  {
    if(currentDepth() == depth_)
      bases_.pop();
    --depth_;
  } // endElement

  stringT makeAbsolute(const stringT& spec)
  {
    return absolutise(currentBase(), spec);
  } // makeAbsolute

private:
  stringT absolutise(const stringT& baseURI, const stringT& location)
  {
    Arabica::io::URI absolute(Arabica::io::URI(baseURI), location);
    return string_adaptorT::construct_from_utf8(absolute.as_string().c_str());
  } // absolutise

  stringT absolutiseAndTrim(const stringT& baseURI, const stringT& location)
  {
    return trim(absolutise(baseURI, location));
  } // absolutiseAndTrim

  stringT trim(const stringT& location)
  {
    static const valueT FORWARD_SLASH = string_adaptorT::convert_from_utf8(Arabica::Unicode<char>::SLASH);

    if(location[location.length()] == FORWARD_SLASH)
      return location;

    return location.substr(0, location.rfind(FORWARD_SLASH)+1);
  } // trim

  stringT currentBase() const
  {
    if(!bases_.size())
      return stringT();
    return bases_.top().second;
  } // currentBase()

  int currentDepth() const
  {
    if(!bases_.size())
      return -1;
    return bases_.top().first;
  } // currentDepths

private:
  typedef std::pair<int, stringT> baseInfoT;
  typedef std::stack<baseInfoT> baseStackT;

  baseStackT bases_;
  int depth_;

  const XMLBaseConstants<stringT, string_adaptorT> xbc_;

  // no impl
  basic_XMLBaseSupport(const basic_XMLBaseSupport&);
  basic_XMLBaseSupport& operator=(const basic_XMLBaseSupport&);
  bool operator==(const basic_XMLBaseSupport&);
}; // class basic_XMLBaseSupport

typedef basic_XMLBaseSupport<std::string> XMLBaseSupport;
#ifndef ARABICA_NO_WCHAR_T
typedef basic_XMLBaseSupport<std::wstring> wXMLBaseSupport;
#endif

} // namespace SAX

#endif

