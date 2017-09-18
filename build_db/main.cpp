#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <filesystem>
#include <unordered_set>
#include <unordered_map>

using namespace std;
namespace fs = std::experimental::filesystem;

#include "C:/dev/Global/log2.h"
#include "C:/dev/Global/string_tool.h"

using namespace jlib;

void rename(string path)
{
	size_t files = 0;
	//std::vector<std::string> exts;
	std::unordered_set<std::string> exts;

	auto valid_exts = { "mp4", "m2ts", "ts", "rmvb", "mkv", "rm", "avi", "sfv", "m4v", "wmv", "bdmv" };
	std::unordered_map<uintmax_t, std::vector<std::string>> movies;

	for (auto& p : fs::recursive_directory_iterator(path)) {
		if (!fs::is_directory(p)) {
			try {
				//JLOG_INFO("file:{}", utf8::u16_to_mbcs(p.path().wstring()));
				if (p.path().has_extension()) {
					auto ext = p.path().extension().string().substr(1);
					if (is_contain(valid_exts, ext)) {
						exts.insert(ext);

						auto path = utf8::u16_to_mbcs(p.path().wstring());
						auto size = fs::file_size(p.path());
						movies[size].push_back(path);
						files++;
					}
				}
				
			} catch (std::exception& e) {
				JLOG_ERRO(e.what());
			}
		}
	}

	JLOG_INFO("total {} files, {} types", files, exts.size());
	for (auto& ext : exts) {
		JLOG_INFO(ext);
	}

	JLOG_INFO("all movies:");
	for (auto& m : movies) {
		if (m.second.size() > 1) {
			JLOG_WARN("same file:");
			for (auto & f : m.second) {
				JLOG_INFO(f);
			}
		} else {

		}
	}
}

int main(int argc, char** argv)
{
	{
		auto path = get_exe_path_a() + "\\log";
		if (!fs::exists(path)) {
			fs::create_directory(path);
		}
		path += "\\build_db";
		jlib::init_logger(path);
	}
	
	rename("G:/电影");
}
