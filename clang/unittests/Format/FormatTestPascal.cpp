//===- unittest/Format/FormatTestPascal.cpp - Pascal formatting tests -----===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "FormatTestBase.h"

namespace clang {
namespace format {
namespace test {
namespace {

class FormatTestPascal : public FormatTestBase {
protected:
  FormatStyle getDefaultStyle() const override {
    FormatStyle Style = getLLVMStyle();
    Style.Language = FormatStyle::LK_Pascal;
    return Style;
  }
};

TEST_F(FormatTestPascal, LanguageDetection) {
  // Test that Pascal files are detected correctly
  EXPECT_EQ(FormatStyle::LK_Pascal, guessLanguage("test.pas", ""));
  EXPECT_EQ(FormatStyle::LK_Pascal, guessLanguage("test.dpr", ""));
  EXPECT_EQ(FormatStyle::LK_Pascal, guessLanguage("test.pp", ""));
  EXPECT_EQ(FormatStyle::LK_Pascal, guessLanguage("test.inc", ""));
  
  // Test language comment detection
  EXPECT_EQ(FormatStyle::LK_Pascal, 
            guessLanguage("test.txt", "// clang-format Language: Pascal\n"));
}

TEST_F(FormatTestPascal, SimplestProgram) {
  // Start with the absolute simplest Pascal program
  verifyFormat("program helloworld;\n"
               "\n"
               "begin\n"
               "end.");
}

TEST_F(FormatTestPascal, BasicProgram) {
  // For now, just verify that Pascal code doesn't crash the formatter
  // We'll add more specific formatting tests as we implement the lexer
  verifyFormat("program HelloWorld;\n"
               "begin\n"
               "  WriteLn('Hello, World!');\n"
               "end.");
}

TEST_F(FormatTestPascal, Comments) {
  // Test different Pascal comment styles
  verifyFormat("// Single line comment\n"
               "{ Multi-line\n"
               "  comment }\n"
               "(* Another multi-line\n"
               "   comment style *)");
}

TEST_F(FormatTestPascal, VariableDeclarations) {
  verifyFormat("var\n"
               "  x, y: Integer;\n"
               "  name: string;\n"
               "  pi: Real = 3.14159;");
}

TEST_F(FormatTestPascal, ProceduresAndFunctions) {
  verifyFormat("procedure DrawLine(x1, y1, x2, y2: Integer);\n"
               "begin\n"
               "  MoveTo(x1, y1);\n"
               "  LineTo(x2, y2);\n"
               "end;\n"
               "\n"
               "function Max(a, b: Integer): Integer;\n"
               "begin\n"
               "  if a > b then\n"
               "    Result := a\n"
               "  else\n"
               "    Result := b;\n"
               "end;");
}

TEST_F(FormatTestPascal, ControlStructures) {
  verifyFormat("if x > 0 then\n"
               "  WriteLn('Positive')\n"
               "else if x < 0 then\n"
               "  WriteLn('Negative')\n"
               "else\n"
               "  WriteLn('Zero');\n"
               "\n"
               "for i := 1 to 10 do\n"
               "  WriteLn(i);\n"
               "\n"
               "while not EOF do\n"
               "  ReadLn(line);");
}

TEST_F(FormatTestPascal, BeginEnd) {
  verifyFormat("begin\n"
               "  Statement1;\n"
               "  Statement2;\n"
               "  begin\n"
               "    NestedStatement1;\n"
               "    NestedStatement2;\n"
               "  end;\n"
               "  Statement3;\n"
               "end;");
}

} // namespace
} // namespace test
} // namespace format
} // namespace clang