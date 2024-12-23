#include <iostream>
#include <filesystem>
#include <fstream>
#include <random>

using namespace std;
namespace fs = std::filesystem;

string generate_random_string(size_t length) {
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, characters.size() - 1);

    string result;
    for (size_t i = 0; i < length; ++i) {
        result += characters[distribution(generator)];
    }
    return result;
}

void task1(const string& dir_name) {
    try {
        fs::create_directory(dir_name);

        for (int i = 0; i < 5; ++i) {
            string file_name = generate_random_string(8) + ".txt";
            ofstream file(dir_name + "/" + file_name);
            if (file.is_open()) {
                file << "Random content for " << file_name;
                file.close();
            }
        }

        for (const auto& entry : fs::directory_iterator(dir_name)) {
            if (entry.is_regular_file()) {
                cout << "File: " << entry.path().filename() << ", Size: " << fs::file_size(entry) << " bytes" << std::endl;
            }
        }

        fs::create_directory(dir_name + "/backup");
        for (const auto& entry : fs::directory_iterator(dir_name)) {
            if (entry.is_regular_file()) {
                fs::copy(entry, dir_name + "/backup/" + entry.path().filename().string());
            }
        }

        for (const auto& entry : fs::directory_iterator(dir_name)) {
            if (entry.is_regular_file()) {
                fs::remove(entry);
            }
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main() {
    string directory_name;
    cout << "Enter directory name: ";
    cin >> directory_name;

    cout << "\n--- Task 1 ---\n";
    task1(directory_name);

    return 0;
}
