/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmGlobalJOMMakefileGenerator.h"

#include "cmLocalUnixMakefileGenerator3.h"
#include "cmMakefile.h"

cmGlobalJOMMakefileGenerator::cmGlobalJOMMakefileGenerator(cmake* cm)
  : cmGlobalUnixMakefileGenerator3(cm)
{
  this->FindMakeProgramFile = "CMakeJOMFindMake.cmake";
  this->ForceUnixPaths = false;
  this->ToolSupportsColor = true;
  this->UseLinkScript = false;
  cm->GetState()->SetWindowsShell(true);
  cm->GetState()->SetNMake(true);
  this->DefineWindowsNULL = true;
  this->PassMakeflags = true;
  this->UnixCD = false;
  this->MakeSilentFlag = "/nologo";
}

void cmGlobalJOMMakefileGenerator
::EnableLanguage(std::vector<std::string>const& l,
                 cmMakefile *mf,
                 bool optional)
{
  // pick a default
  mf->AddDefinition("CMAKE_GENERATOR_CC", "cl");
  mf->AddDefinition("CMAKE_GENERATOR_CXX", "cl");
  this->cmGlobalUnixMakefileGenerator3::EnableLanguage(l, mf, optional);
}

void cmGlobalJOMMakefileGenerator
::GetDocumentation(cmDocumentationEntry& entry)
{
  entry.Name = cmGlobalJOMMakefileGenerator::GetActualName();
  entry.Brief = "Generates JOM makefiles.";
}

void cmGlobalJOMMakefileGenerator::PrintCompilerAdvice(std::ostream& os,
                                                  std::string const& lang,
                                                  const char* envVar) const
{
  if(lang == "CXX" || lang == "C")
    {
    /* clang-format off */
    os <<
      "To use the JOM generator with Visual C++, cmake must be run from a "
      "shell that can use the compiler cl from the command line. This "
      "environment is unable to invoke the cl compiler. To fix this problem, "
      "run cmake from the Visual Studio Command Prompt (vcvarsall.bat).\n";
    /* clang-format on */
    }
  this->cmGlobalUnixMakefileGenerator3::PrintCompilerAdvice(os, lang, envVar);
}
