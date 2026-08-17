#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ===============================
// MEMENTO
// ===============================
class Memento {
private:
    string text;

public:
    Memento(string text) {
        this->text = text;
    }

    string getText() {
        return text;
    }
};

// ===============================
// ORIGINATOR
// ===============================
class TextEditor {
private:
    string text;
    vector<Memento> history;

public:
    // Write new text
    void write(string newText) {
        // Save current state before changing
        save();
        text = newText;
        cout << "Text changed to: " << text << endl;
    }

    // Save current state
    void save() {
        Memento m(text);
        history.push_back(m);
    }

    // Undo last change
    void undo() {
        if (history.empty()) {
            cout << "Nothing to undo!" << endl;
            return;
        }

        Memento lastState = history.back();
        history.pop_back();
        text = lastState.getText();
        cout << "Undo successful!" << endl;
        cout << "Current text: " << text << endl;
    }

    // Show current text
    void showText() {
        cout << "Current text: " << text << endl;
    }
};

// ===============================
// MAIN
// ===============================
int main() {
    TextEditor editor;

    cout << "----- Text Editor -----\n\n";

    editor.write("Hello");
    editor.write("Hello World");
    editor.write("Hello World! Welcome");

    cout << "\n";
    editor.showText();

    cout << "\n--- Undo ---\n";
    editor.undo();

    cout << "\n--- Undo ---\n";
    editor.undo();

    cout << "\n--- Undo ---\n";
    editor.undo();

    return 0;
}