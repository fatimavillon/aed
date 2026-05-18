#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <typename T>
class List {
private:
    Node<T>* head;
    int current_size;

public:
    List() : head(nullptr), current_size(0) {}

    ~List() {
        clear();
    }

    Node<T>* get_head() {
        return head;
    }

    // 1.1 front(): Retorna el elemento al comienzo. O(1)
    T front() {
        if (empty()) {
            throw out_of_range("front(): La lista esta vacia.");
        }
        return head->data;
    }

    // 1.2 back(): Retorna el elemento al final. O(n)
    T back() {
        if (empty()) {
            throw out_of_range("back(): La lista esta vacia.");
        }
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        return temp->data;
    }

    // 1.3 push_front(T): Agrega un elemento al comienzo. O(1)
    void push_front(T value) {
        Node<T>* new_node = new Node<T>(value);
        new_node->next = head;
        head = new_node;
        current_size++;
    }

    // 1.4 push_back(T): Agrega un elemento al final. O(n)
    void push_back(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (empty()) {
            head = new_node;
        } else {
            Node<T>* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new_node;
        }
        current_size++;
    }

    // 1.5 pop_front(): Remueve y retorna el elemento al comienzo. O(1)
    T pop_front() {
        if (empty()) {
            throw out_of_range("pop_front(): La lista esta vacia.");
        }
        Node<T>* temp = head;
        T val = temp->data;
        head = head->next;
        delete temp;
        current_size--;
        return val;
    }

    // 1.6 pop_back(): Remueve y retorna el elemento al final. O(n)
    T pop_back() {
        if (empty()) {
            throw out_of_range("pop_back(): La lista esta vacia.");
        }
        T val;
        if (head->next == nullptr) {
            val = head->data;
            delete head;
            head = nullptr;
        } else {
            Node<T>* temp = head;
            while (temp->next->next != nullptr) {
                temp = temp->next;
            }
            val = temp->next->data;
            delete temp->next;
            temp->next = nullptr;
        }
        current_size--;
        return val;
    }

    // 1.7 operator[]: Retorna el elemento en la posición indicada. O(n)
    T operator[](int index) {
        if (index < 0 || index >= current_size) {
            throw out_of_range("operator[]: indice fuera de rango.");
        }
        Node<T>* temp = head;
        for (int i = 0; i < index; i++) {
            temp = temp->next;
        }
        return temp->data;
    }

    // 1.8 empty(): Retorna true si la lista está vacía. O(1)
    bool empty() const {
        return head == nullptr;
    }

    // 1.9 size(): Retorna el tamaño de la lista. O(1)
    int size() const {
        return current_size;
    }

    // 1.10 clear(): Elimina todos los elementos de la lista. O(n)
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    // 1.11 sort(): Insertion Sort sobre nodos enlazados. O(n^2)
    void sort() {
        if (empty() || head->next == nullptr) return;

        Node<T>* sorted_head = nullptr;
        Node<T>* current = head;

        while (current != nullptr) {
            Node<T>* next_node = current->next;

            if (sorted_head == nullptr || current->data < sorted_head->data) {
                current->next = sorted_head;
                sorted_head = current;
            } else {
                Node<T>* temp = sorted_head;
                while (temp->next != nullptr && temp->next->data < current->data) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }

            current = next_node;
        }

        head = sorted_head;
    }


    // 1.12 reverse(): Invierte el flujo de enlaces. O(n)
    void reverse() {
        Node<T>* prev    = nullptr;
        Node<T>* current = head;
        Node<T>* next_node = nullptr;

        while (current != nullptr) {
            next_node    = current->next;
            current->next = prev;
            prev         = current;
            current      = next_node;
        }
        head = prev;
    }

    void print() const {
        if (head == nullptr) {
            cout << "Lista vacia." << endl;
            return;
        }
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << " -> NULL" << endl;
    }
};

int main() {

    List<int> lista;

    // --- push_back / push_front ---
    lista.push_back(10);
    lista.push_front(20);
    lista.push_back(5);
    lista.push_front(30);

    cout << "\n[1] Lista inicial:      ";
    lista.print();

    // --- front / back / size ---
    cout << "    front()  = " << lista.front() << endl;
    cout << "    back()   = " << lista.back()  << endl;
    cout << "    size()   = " << lista.size()  << endl;
    cout << "    empty()  = " << (lista.empty() ? "true" : "false") << endl;

    // --- operator[] ---
    cout << "\n[2] Acceso por indice:" << endl;
    for (int i = 0; i < lista.size(); i++) {
        cout << "    lista[" << i << "] = " << lista[i] << endl;
    }

    // --- pop_front / pop_back ---
    cout << "\n[3] pop_front() -> " << lista.pop_front() << endl;
    cout << "    pop_back()  -> " << lista.pop_back()  << endl;
    cout << "    Lista tras eliminaciones: ";
    lista.print();

    // --- sort ---
    lista.push_back(45);
    lista.push_front(1);
    lista.push_back(15);

    cout << "\n[4] Lista antes de sort():  ";
    lista.print();

    lista.sort();
    cout << "    Lista despues de sort(): ";
    lista.print();

    // --- reverse ---
    lista.reverse();
    cout << "\n[5] Lista despues de reverse(): ";
    lista.print();

    // --- clear ---
    lista.clear();
    cout << "\n[6] Despues de clear():  ";
    lista.print();
    cout << "    size()  = " << lista.size()  << endl;
    cout << "    empty() = " << (lista.empty() ? "true" : "false") << endl;

    // --- Prueba con strings ---
    cout << "\n[7] Prueba con tipo string:" << endl;
    List<string> palabras;
    palabras.push_back("banana");
    palabras.push_back("apple");
    palabras.push_back("mango");
    palabras.push_front("cherry");

    cout << "    Antes de sort():   ";
    palabras.print();
    palabras.sort();
    cout << "    Despues de sort(): ";
    palabras.print();

    // --- Manejo de excepciones ---
    cout << "\n[8] Prueba de excepciones:" << endl;
    List<int> vacia;
    try {
        vacia.front();
    } catch (const out_of_range& e) {
        cout << "    Excepcion capturada -> " << e.what() << endl;
    }
    try {
        vacia.pop_back();
    } catch (const out_of_range& e) {
        cout << "    Excepcion capturada -> " << e.what() << endl;
    }
    try {
        vacia[3];
    } catch (const out_of_range& e) {
        cout << "    Excepcion capturada -> " << e.what() << endl;
    }

    return 0;
}