#include <iostream>
#include <filesystem>
#include <map>
using namespace std;

namespace fs = filesystem;

void task2(const string& dir_name) {
    try {
        size_t total_files = 0;
        size_t total_size = 0;
        map<string, size_t> file_types;

        for (const auto& entry : fs::directory_iterator(dir_name)) {
            if (entry.is_regular_file()) {
                ++total_files;
                total_size += fs::file_size(entry);

                std::string extension = entry.path().extension().string();
                if (extension.empty()) {
                    extension = "[no extension]";
                }
                ++file_types[extension];
            }
        }

        cout << "Total files: " << total_files << endl;
        cout << "Total size: " << total_size << " bytes" << endl;
        cout << "File type distribution:" << endl;
        for (const auto& [type, count] : file_types) {
            cout << "  " << type << ": " << count << " files" << endl;
        }

    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    string directory_name;
    cout << "Enter directory name: ";
    cin >> directory_name;

    cout << "\n--- Task 2 ---\n";
    task2(directory_name);

    return 0;
}
