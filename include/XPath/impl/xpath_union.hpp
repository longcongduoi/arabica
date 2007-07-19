#ifndef ARABICA_XPATHIC_XPATH_UNION_HPP
#define ARABICA_XPATHIC_XPATH_UNION_HPP

#include "xpath_value.hpp"
#include <algorithm>

namespace Arabica
{
namespace XPath
{
namespace impl
{

template<class string_type, class string_adaptor>
class UnionExpression : private BinaryExpression<string_type, string_adaptor>, 
                        public XPathExpression<string_type, string_adaptor>
{
  typedef BinaryExpression<string_type, string_adaptor> baseT;
public:
  UnionExpression(XPathExpression<string_type, string_adaptor>* lhs, 
                  XPathExpression<string_type, string_adaptor>* rhs) :
       BinaryExpression<string_type, string_adaptor>(lhs, rhs) { }

  virtual XPathValuePtr<string_type> evaluate(const DOM::Node<string_type>& context, 
                                              const ExecutionContext<string_type, string_adaptor>& executionContext) const
  {
    XPathValuePtr<string_type> p1 = baseT::lhs()->evaluate(context, executionContext);
    if(p1->type() != NODE_SET)
      throw RuntimeException("Union operator joins node-sets.  First argument is not a node-set.");
    XPathValuePtr<string_type> p2 = baseT::rhs()->evaluate(context, executionContext);
    if(p2->type() != NODE_SET)
      throw RuntimeException("Union operator joins node-sets.  Second argument is not a node-set.");

    NodeSet<string_type> ns1(p1->asNodeSet());
    NodeSet<string_type> ns2(p2->asNodeSet());

    // do the obvious optimizations
    if(ns1.empty())
      return wrap(ns2);
    if(ns2.empty())
      return wrap(ns1);

    ns1.insert(ns1.end()-1, ns2.begin(), ns2.end());
    ns1.to_document_order();

    return wrap(ns1);
  } // evaluate

private:
  XPathValuePtr<string_type> wrap(const NodeSet<string_type>& ns) const
  {
    return XPathValuePtr<string_type>(new NodeSetValue<string_type, string_adaptor>(ns));
  } // wrap
}; // UnionExpression

} // namespace impl
} // namespace XPath
} // namespace Arabica
#endif
