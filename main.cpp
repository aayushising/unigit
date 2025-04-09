#include <iostream>
#include <string>
#include <vector>
using namespace std;
class RepoManager {
public:
    void init() {
        cout << "Repository initialized.\n";
    }

    void createCommit(const std::string& parent_hash, const std::string& message) {
        cout << "Commit created with message: " << message << "\n";
        cout << "Parent: " << parent_hash << "\n";
    }

    void printLog() {
        cout << "Commit log:\n";
        cout << "commit abc123\nAuthor: You\nMessage: Initial commit\n\n";
        cout << "commit def456\nAuthor: You\nMessage: Added status command\n\n";
    }

    void showInfo() {
        cout << "Repository Info:\n";
        cout << "- Current Branch: main\n";
        cout << "- Total Commits: 2\n";
    }

    void retrieveFile(const std::string& file_path) {
        cout << "Retrieved version of: " << file_path << "\n";
        cout << "Mock file content here...\n";
    }
};

class IndexManager {
public:
    void printStatus() {
        cout << "Displaying current index status...\n";
    }

    string getLastCommitHash() {
        return "dummy_parent_hash";
    }
};
RepoManager repoManager;
IndexManager indexManager;

void printHelp() {
    cout << "  unigit init                      - Initialize repository\n";
    cout << "  unigit status                    - Show current changes\n";
    cout << "  unigit commit -m \"message\"       - Commit staged changes\n";
    cout << "  unigit log                       - Show commit history\n";
    cout << "  unigit retrieve <file>          - Retrieve last committed version of a file\n";
    cout << "  unigit info                      - Show repository info\n";
    cout << "  unigit help                      - Show this help menu\n";
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printHelp();
        return 1;
    }

    string cmd = argv[1];

    if (cmd == "init") {
        repoManager.init();
    }
    else if (cmd == "status") {
        indexManager.printStatus();
    }
    else if (cmd == "commit") {
        if (argc < 4 || std::string(argv[2]) != "-m") {
            cerr << "Usage: unigit commit -m \"commit message\"\n";
            return 1;
        }
        string message = argv[3];
        string parent_hash = indexManager.getLastCommitHash();
        repoManager.createCommit(parent_hash, message);
    }
    else if (cmd == "log") {
        repoManager.printLog();
    }
    else if (cmd == "retrieve") {
        if (argc < 3) {
            std::cerr << "Usage: unigit retrieve <file>\n";
            return 1;
        }
        string file_path = argv[2];
        repoManager.retrieveFile(file_path);
    }
    else if (cmd == "info") {
        repoManager.showInfo();
    }
    else if (cmd == "help") {
        printHelp();
    }
    else {
        cerr << "Unknown command: " << cmd << "\n";
        printHelp();
    }

    return 0;
}
