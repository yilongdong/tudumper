#pragma once
#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/Tooling.h>
#include "context/CXXAnalysisContext.h"

namespace CXXScanner::action {
    class FrontendAction : public clang::ASTFrontendAction {
    public:
        FrontendAction() = default;
    protected:
        std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &CI, clang::StringRef InFile) override;
        void EndSourceFileAction() override;
    private:
        context::CXXAnalysisContext cxxAnalysisContext;
    };

    class FrontendActionFactory : public clang::tooling::FrontendActionFactory {
    public:
        std::unique_ptr<clang::FrontendAction> create() override;
    };
}