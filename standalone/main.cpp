#include <iostream>
#include <filesystem>
#include <gflags/gflags.h>
#include <clang/Tooling/Tooling.h>
#include <clang/Tooling/CompilationDatabase.h>

#include "utility/log.h"
#include "action/FrontendAction.h"

DEFINE_string(output_dir, "", "输出目录");
DEFINE_string(compdb, "", "编译数据库文件");
DEFINE_string(files, "", "分析文件目录");
DEFINE_bool(verbose, false, "");

int main(int argc, char* argv[]) {
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    std::vector<std::string> files = { FLAGS_files };
    if(FLAGS_verbose) {
        SET_LOGLEVEL("trace");
    }
    std::filesystem::path compdbPath { FLAGS_compdb };

    LOG_INFO("options (compdb: {}, output_dir: {}, files: {}, verbose: {} )",
             compdbPath.u8string(), FLAGS_output_dir, FLAGS_files , FLAGS_verbose);

    std::string errorMsg;
    if (auto db =
            clang::tooling::CompilationDatabase::loadFromDirectory(compdbPath.parent_path().u8string(), errorMsg)) {
        if (FLAGS_files == "all") {
            files = db->getAllFiles();
        }
        else {
//            TODO
//            files = split(FLAGS_files, ',');
        }
        clang::tooling::ClangTool tool(*db, files);
        tudumper::FrontendActionFactory factory;
        tool.run(&factory);
    } else {
        LOG_ERROR("Fail to load compile database from {} with error msg {}", compdbPath.parent_path().u8string(), errorMsg);
    }

    return 0;
}
