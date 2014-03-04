/**
 @file lex_edl.h
 @brief Header extending the \c lexer base class for parsing C++.
 
 This file defines two subclasses of \c jdi::lexer. The first is meant to lex
 C++ definitions, and so returns a wide range of token types. It will also do
 any needed preprocessing, handing the second lexer to \c jdi::AST to handle
 #if expression evaluation. The second lexer is much simpler, and treats 
  
  @section License
    Copyright (C) 2008-2012 Josh Ventura
    This file is a part of the ENIGMA Development Environment.

    ENIGMA is free software: you can redistribute it and/or modify it under the
    terms of the GNU General Public License as published by the Free Software
    Foundation, version 3 of the license or any later version.

    This application and its source code is distributed AS-IS, WITHOUT ANY WARRANTY; 
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
    PURPOSE. See the GNU General Public License for more details.

    You should have recieved a copy of the GNU General Public License along
    with this code. If not, see <http://www.gnu.org/licenses/>
**/

#ifndef _LEX_EDL__H
#define _LEX_EDL__H

#include <System/lex_cpp.h>
#include <string>
using std::string;

/**
  @brief An implementation of \c jdi::lexer for lexing EDL. Handles preprocessing
         seamlessly, returning only relevant tokens.
**/
struct lexer_edl: jdip::lexer_cpp {
  /// This is the context parser that was used to 
  jdi::context *ctex;
  
  jdip::token_t get_token(jdi::error_handler *herr);
  
  /**
    Utility function designed to handle the preprocessor directive
    pointed to by \c pos upon invoking the function. Note that it should
    be the character directly after the brackets pointed to upon invoking
    the function, not the brackets themselves.
    @param herr  The error handler to use if the preprocessor doesn't
                 exist or is malformed.
  **/
  void handle_preprocessor(jdi::error_handler *herr);
  
  /// Utility function to skip a GML string; invoke with pos indicating the quotation mark: terminates indicating match.
  void skip_gml_string(jdi::error_handler *herr);
  /// Function used by the preprocessor to navigate to terminating double braces.
  string read_preprocessor_args(jdi::error_handler *herr);
  
  /**
   * Construct with all needed info.
   * @param ctex    The JDI context which contains the definitions used during preprocessing.
   * @param input   The input code stream.
   * @param pmacros The map of macros to use during preprocessing (this is available from the JDI context)
   * @param fname   The name of the file being processed, used for constructing tokens and ultimately for error reporting.
  */
  lexer_edl(jdi::context *ctex, llreader &input, jdi::macro_map &pmacros, const char *fname);
  ~lexer_edl();
};

#endif