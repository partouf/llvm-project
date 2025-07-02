# Pascal Language Support for clang-format

This document describes the implementation of Pascal language support in clang-format.

## Overview

Pascal/Delphi language support has been added to clang-format to enable automatic formatting of Pascal source files.

## Implementation Status

### Completed Features

**Language Detection:**
- File extensions: `.pas`, `.dpr`, `.pp`, `.inc`
- Language selection via configuration: `Language: Pascal`

**Lexical Analysis:**
- 57 Pascal keywords recognized (including modern Delphi keywords)
- Pascal assignment operator `:=` properly tokenized
- Three comment styles supported: `{ }`, `(* *)`, `//`
- Proper handling of dotted identifiers (e.g., `System.SysUtils`)

**Formatting Features:**
- Context-aware `var` keyword handling:
  - Declaration context: `var` section with proper indentation
  - Inline context: `for var i := 1 to 10 do` stays on one line
- Class structure formatting with visibility sections
- Interface and implementation section support
- Property declarations with SingleLine/MultiLine modes
- Type declaration blocks
- Uses clause formatting
- Begin/end block indentation

**Configuration Options:**
- `AllowShortInlineVariablesOnASingleLine`: Controls inline variable formatting
- `PascalProperties`: Choose between `SingleLine` and `MultiLine` property formatting

### Known Issues

**Progressive Indentation in Implementation Section:**
Implementation section procedures exhibit progressive indentation:
```pascal
implementation

function TDataProcessor.GetMetadata: string;        // Correct
  function TDataProcessor.GetSecondaryData: string; // Extra indent
    function TDataProcessor.GetPrimaryData: string; // More extra indent
```

This is a visual issue only and does not affect code functionality.

## Technical Details

### Modified Files

The implementation spans 8 files:
- `clang/include/clang/Format/Format.h` - Language enum and configuration
- `clang/lib/Format/Format.cpp` - File detection and style mapping
- `clang/lib/Format/FormatToken.h` - Pascal token types and keywords
- `clang/lib/Format/FormatTokenLexer.cpp` - Assignment operator tokenization
- `clang/lib/Format/TokenAnnotator.cpp` - Token relationships and spacing
- `clang/lib/Format/UnwrappedLineParser.cpp` - Pascal syntax parsing
- `clang/lib/Format/UnwrappedLineFormatter.cpp` - Line breaking logic
- `clang/tools/clang-format/ClangFormat.cpp` - Debug support

### Key Implementation Aspects

**Context-Aware Parsing:**
The implementation distinguishes between different uses of the same keyword based on context. For example, `var` can be:
- A section declaration requiring indentation
- An inline variable declaration that should not break

**Specialized Parsing Functions:**
- `parseBlockPascal()` - Handles begin/end blocks
- `parsePascalTypeDeclaration()` - Parses type sections
- `parsePascalInterfaceContent()` - Handles interface declarations
- `parsePascalClassContent()` - Manages class structure with visibility

## Testing

A comprehensive test suite is maintained separately with approval tests covering:
- Basic Pascal formatting
- Property formatting modes
- Interface and class declarations
- Nested begin/end blocks
- Complex real-world Pascal code

## Usage Example

Create a `.clang-format` file:
```yaml
Language: Pascal
IndentWidth: 2
AllowShortInlineVariablesOnASingleLine: true
PascalProperties: MultiLine
```

Format Pascal files:
```bash
clang-format -style=file MyProgram.pas
```

## Future Work

- Address progressive indentation in implementation sections
- Add support for additional Pascal-specific constructs as needed
- Enhance property formatting options
- Improve handling of complex generic declarations