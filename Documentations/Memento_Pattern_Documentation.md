# Lab 03 -- Memento Pattern

## 1. Pattern Name

**Memento Design Pattern**

## 2. Category

**Behavioral Design Pattern**

Behavioral design patterns are concerned with communication and interaction between objects.

## 3. Intent

The main intent of the Memento Pattern is to capture and save the internal state of an object without violating encapsulation, so that the object can be restored to its previous state later.

In this project, the Memento Pattern is used to save previous versions of text in a text editor and restore them when the user performs an Undo operation.

## 4. Problem Statement

A text editor allows users to modify the content of a document multiple times. Sometimes, a user may accidentally change or delete some content and need to return to a previous version.

The problem is:
> How can we save the previous state of the text editor and restore it later without directly exposing its internal data?

If the text editor directly manages all previous states, the design can become complicated and the internal state may be exposed unnecessarily. The Memento Pattern solves this problem by storing the previous state in a separate Memento object.

## 5. Motivation

The motivation for using the Memento Pattern is to provide a simple Undo mechanism.

For example, suppose the text editor contains:
```
Hello
```
The user changes it to:
```
Hello World
```
Then changes it to:
```
Hello World! Welcome
```
If the user wants to undo the last operation, the editor should return to:
```
Hello World
```

The Memento Pattern stores the previous states so that they can be restored whenever required.

The basic process is:
```
Current State
      ↓
  Save State
      ↓
Modify Object
      ↓
 Modify Again
      ↓
     Undo
      ↓
Restore Previous State
```

## 6. Pattern Structure (UML Class Diagram)

> **UML diagram:** Add the Memento Pattern UML image pushed by the team to the repository and update the filename below.
>
> `![Memento Pattern UML](path/to/memento-pattern-uml.png)`

## 7. Class Responsibilities

-   **Memento** -- Stores the previous state of the text editor.
    -   Store the text state.
    -   Provide access to the saved text.
    -   Protect the saved state from unnecessary modification.
-   **TextEditor (Originator)** -- Maintains the current text and creates/restores Mementos.
    -   Maintain the current text.
    -   Modify the text.
    -   Create Memento objects.
    -   Store previous states.
    -   Restore previous states during Undo.
    -   Display the current text.
-   **History** -- The history collection stores multiple Memento objects.
    -   Keep previous versions of the text.
    -   Provide the latest saved state for Undo.
    -   Remove the restored state after an Undo operation.

## 8. Code Implementation

```cpp
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
```

## 9. Execution Flow (Object Interaction)

1.  **Create Text Editor**: A `TextEditor` object is created (`TextEditor editor;`). Initially, the text is empty.
2.  **Write Text**: The user writes `"Hello"`. Before changing the text, the current state is saved in a Memento.
3.  **Modify Text**: The user changes the text to `"Hello World"`. Again, the previous state is stored.
4.  **Modify Again**: The user changes the text to `"Hello World! Welcome"`. The previous state is again saved.
5.  **Undo**: When `undo()` is called, the latest Memento is retrieved:
    ```
    Hello World! Welcome
            ↓
          Undo
            ↓
       Hello World
    ```
6.  **Restore**: The saved state is restored to the `TextEditor`.

The overall interaction flow:
```
User
 ↓
TextEditor
 ↓
Save current state
 ↓
Memento
 ↓
Change text
 ↓
User requests Undo
 ↓
TextEditor retrieves Memento
 ↓
Previous state restored
```

## 10. Advantages

-   Provides an easy way to implement Undo and Redo functionality.
-   Preserves the encapsulation of the original object without violating internal state protection.
-   Separates state-saving responsibility from the main object.
-   Allows multiple previous states to be stored in history.
-   Makes state restoration easier and reliable.
-   The implementation is simple and suitable for applications requiring version history.

## 11. Limitations

-   Saving many states can consume a large amount of memory.
-   Large objects can make Memento objects expensive to create and store.
-   Managing a large history may increase application complexity.
-   If the object state is very large, creating multiple copies can reduce performance.
-   Developers must carefully decide how many previous states should be retained.

## 12. Real-life Applications

-   **Text Editors**: Undo/Redo systems in code editors and note apps.
-   **Drawing / Graphic Applications**: Photoshop, Paint, Figma undo histories.
-   **Database Transactions**: Transaction rollback mechanisms.
-   **Gaming**: Game save points and checkpoint systems.
-   **Web Forms**: Form data caching and drafts restoration.
-   **Configuration Management**: Rollback to previous configurations.
-   **Browser History**: Navigation state restoration.

## 13. Industry Examples

-   **Text Editors** -- Applications such as Microsoft Word and VS Code maintain previous document states to support Undo and Redo.
-   **Graphic Design Software** -- Image-editing applications maintain previous states of a canvas so users can undo destructive changes.
-   **Games** -- Games save a player's current character and world state and restore it upon respawn or loading a checkpoint.
-   **Transaction Systems** -- Enterprise databases maintain previous transaction states and roll back changes when an operation fails.

## 14. Conclusion

The Memento Pattern provides an effective way to save and restore the previous state of an object without exposing its internal implementation.

In this project, the pattern was implemented using a `TextEditor` and `Memento` class. The `TextEditor` saves its previous text states before making changes. When the user performs an Undo operation, the previous state is retrieved and restored.

Therefore, the project demonstrates how the Memento Pattern can be practically used to implement an Undo mechanism using object-oriented programming concepts.
