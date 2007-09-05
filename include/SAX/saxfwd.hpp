#ifndef ARABICA_SAX_FWD_H
#define ARABICA_SAX_FWD_H

// $Id$

#include <string>

/** \mainpage Arabica XML Parser Toolkit
 *
 * \section intro Introduction
 * 
 * <p>Arabica has a full <a href='http://www.saxproject.org/'>SAX2, the Simple API for XML</a>, implementation 
 * including the optional interfaces and helper classes. Layered on 
 * SAX is a W3C <a href='http://www.w3.org/DOM/'>Document Object Model (DOM) Level 2.0 Core</a> 
 * implementation, together with an <a href='http://www.w3.org/tr/xpath'>XPath</a> engine. </p>
 *
 * <p>It delivers UTF-8 encoded std::strings or UCS-2 std::wstrings, 
 * but can also accommodate custom string types and alternative 
 * encodings. </p>
 * 
 * <p>It provides uniform SAX2 wrappers for the <A href='http://www.libexpat.org/'>expat</a> parser, 
 * <a href='http://xml.apache.org/xerces-c/index.html'>Xerces</a>, <a href='http://www.xmlsoft.org'>libxml</a>
 * and for the <a href='http://msdn.microsoft.com/xml'>Microsoft XML parser</a> COM component.</p>
 *
 * \section license License
 * 
 * Copyright (c) 2001-2007 Jez UK Ltd<br>
 * All rights reserved.
 * <p>
 * Redistribution and use in source and binary forms, with or <br>
 * without modification, are permitted provided that the following <br>
 * conditions are met:<br>
 * <ul>
 *   <li>Redistributions of source code must retain the above <br>
 *       copyright notice, this list of conditions and the following <br>
 *       disclaimer.</li>
 *   <li>Redistributions in binary form must reproduce the above <br>
 *       copyright notice, this list of conditions and the following <br>
 *       disclaimer in the documentation and/or other materials <br>
 *       provided with the distribution.</li>
 *   <li>Neither the name of Jez UK Ltd nor the names of  <br>
 *       contributors may be used to endorse or promote products <br>
 *       derived from this software without specific prior written <br>
 *       permission.</li>
 * </ul>
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND <br>
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, <br>
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF <br>
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE <br>
 * DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE <br>
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, <br>
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, <br>
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, <br>
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY <br>
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR <br>
 * TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT <br>
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY <br>
 * OF SUCH DAMAGE.<br>
 * 
 */


#include <SAX/ParserConfig.h>
#include <SAX/ArabicaConfig.h>

/**
 *  
 * SAX in C++ - A C++ implementation of the SAX2 interface.
 *
 */
namespace Arabica
{
namespace SAX 
{

template<class string_type> class basic_AttributeList;
template<class string_type> class basic_DocumentHandler;
template<class string_type> class basic_DTDHandler;
template<class string_type> class basic_EntityResolver;
template<class string_type> class basic_InputSource;
template<class string_type> class basic_Locator;
template<class string_type> class basic_Parser;
template<class string_type> class basic_SAXParseException;
template<class string_type> class basic_ErrorHandler;

typedef basic_AttributeList<std::string> AttributeList;
typedef basic_DocumentHandler<std::string> DocumentHandler;
typedef basic_DTDHandler<std::string> DTDHandler;
typedef basic_EntityResolver<std::string> EntityResolver;
typedef basic_InputSource<std::string> InputSource;
typedef basic_Locator<std::string> Locator;
typedef basic_Parser<std::string> Parser;
typedef basic_SAXParseException<std::string> SAXParseException;
typedef basic_ErrorHandler<std::string> ErrorHandler;

#ifndef ARABICA_NO_WCHAR_T
typedef basic_AttributeList<std::wstring> wAttributeList;
typedef basic_DocumentHandler<std::wstring> wDocumentHandler;
typedef basic_DTDHandler<std::wstring> wDTDHandler;
typedef basic_EntityResolver<std::wstring> wEntityResolver;
typedef basic_InputSource<std::wstring> wInputSource;
typedef basic_Locator<std::wstring> wLocator;
typedef basic_Parser<std::wstring> wParser;
typedef basic_SAXParseException<std::wstring> wSAXParseException;
typedef basic_ErrorHandler<std::wstring> wErrorHandler;
#endif 

} // namespace SAX
} // namespace Arabica

#endif
// end of file
