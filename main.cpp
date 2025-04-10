#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;



class RepoManager {
public:
    void init() {
        cout << "[unigit] Repository initialized in .unigit/\n";
        system("mkdir -p .unigit/refs");
        ofstream head(".unigit/refs/HEAD");
        head << "";
        head.close();
    }

    void createCommit(const string& parent_hash, const string& message) {
        string new_commit_hash = "commit_" + to_string(rand());

        ofstream commitFile(".unigit/commits/" + new_commit_hash);
        commitFile << "Parent: " << parent_hash << "\n";
        commitFile << "Message: " << message << "\n";
        commitFile.close();

        ofstream head(".unigit/refs/HEAD");
        head << new_commit_hash;
        head.close();

        cout << "[unigit] Commit created:\n";
        cout << "Hash: " << new_commit_hash << "\n";
        cout << "Message: " << message << "\n";
    }

    void printLog() {
        cout << "[unigit] Commit log:\n";
        cout << "commit 123abc\nMessage: Initial commit\n";
        cout << "commit 456def\nMessage: Added retrieve command\n";
    }

    void showInfo() {
        cout << "[unigit] Repository Info:\n";
        cout << "- Current Branch: main\n";
        cout << "- Total Commits: 2 (stubbed)\n";
        cout << "- User: local\n";
    }

    void retrieveFile(const string& file_path) {
        cout << "[unigit] Retrieving file: " << file_path << "\n";
        cout << "Mock content: <file contents here>\n";
    }
};

class IndexManager {
public:
    void printStatus() {
        cout << "[unigit] Checking for modified/tracked files...\n";
    }

    string getLastCommitHash() {
        ifstream head(".unigit/refs/HEAD");
        if (!head.is_open()) {
            cerr << "[unigit] Error: Could not read HEAD file.\n";
            return "";
        }

        string last_commit;
        getline(head, last_commit);
        head.close();
        return last_commit;
    }
};

RepoManager repoManager;
IndexManager indexManager;

void printHelp() {
    cout << "  Unigit Commands:\n";
    cout << "  unigit init                   → Initialize repository\n";
    cout << "  unigit status                 → Show current status\n";
    cout << "  unigit commit -m \"msg\"        → Commit changes\n";
    cout << "  unigit log                    → Show commit history\n";
    cout << "  unigit retrieve <file>       → Retrieve committed file\n";
    cout << "  unigit info                   → Show repository details\n";
    cout << "  unigit help                   → Show help menu\n";
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
        if (argc < 4 || string(argv[2]) != "-m") {
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
            cerr << "Usage: unigit retrieve <file>\n";
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

