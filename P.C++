#include <iostream>
#include <list>

class Cliente {
public:
    int numeroCuenta;
    char tipoCuenta; // '1' para preferencial, '2' para tradicional
    Cliente(int cuenta, char tipo) : numeroCuenta(cuenta), tipoCuenta(tipo) {}
};

class Banco {
private:
    std::list<Cliente> filaTradicional;
    std::list<Cliente> filaPreferencial;

    void transferirCliente() {
        if (filaTradicional.size() >= 5 && filaPreferencial.size() <= 2) {
            auto it = std::next(filaTradicional.begin(), 2); // Encuentra el tercer cliente
            filaPreferencial.push_back(*it); // Lo añade a la fila preferencial
            filaTradicional.erase(it); // Lo elimina de la fila tradicional
        }
    }

public:
    void registrarCliente(int numeroCuenta, char tipoCuenta) {
        Cliente nuevoCliente(numeroCuenta, tipoCuenta);
        if (tipoCuenta == '1') {
            filaPreferencial.push_back(nuevoCliente);
        } else {
            filaTradicional.push_back(nuevoCliente);
        }
        transferirCliente();
    }

    void atenderCliente(char tipoFila) {
        if (tipoFila == '1' && !filaPreferencial.empty()) {
            filaPreferencial.pop_front();
            std::cout << "Cliente preferencial atendido.\n";
        } else if (tipoFila == '2' && !filaTradicional.empty()) {
            filaTradicional.pop_front();
            std::cout << "Cliente tradicional atendido.\n";
        } else {
            std::cout << "No hay clientes en la fila seleccionada para atender.\n";
        }
    }

    void mostrarFila(char tipoFila) {
        int turno = 1;
        if (tipoFila == '1') {
            for (auto& cliente : filaPreferencial) {
                std::cout << "Turno " << turno++ << ": Cuenta No. " << cliente.numeroCuenta << " - Preferencial\n";
            }
        } else if (tipoFila == '2') {
            for (auto& cliente : filaTradicional) {
                std::cout << "Turno " << turno++ << ": Cuenta No. " << cliente.numeroCuenta << " - Tradicional\n";
            }
        } else {
            std::cout << "Tipo de fila no reconocido. Por favor ingrese '1' para Preferencial o '2' para Tradicional.\n";
        }
    }
};

int main() {
    Banco banco;
    int opcion;
    char tipoCuenta;
    int numeroCuenta;

    do {
        std::cout << "1. Registrar Cliente\n";
        std::cout << "2. Atender Cliente\n";
        std::cout << "3. Mostrar Filas\n";
        std::cout << "4. Salir\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                std::cout << "Ingrese numero de cuenta: ";
                std::cin >> numeroCuenta;
                std::cout << "Ingrese tipo de cuenta (1-Preferencial, 2-Tradicional): ";
                std::cin >> tipoCuenta;
                banco.registrarCliente(numeroCuenta, tipoCuenta);
                break;
            case 2:
                std::cout << "Ingrese tipo de fila a atender (1-Preferencial, 2-Tradicional): ";
                std::cin >> tipoCuenta;
                banco.atenderCliente(tipoCuenta);
                break;
            case 3:
                std::cout << "Ingrese tipo de fila a mostrar (1-Preferencial, 2-Tradicional): ";
                std::cin >> tipoCuenta;
                banco.mostrarFila(tipoCuenta);
                break;
            case 4:
                std::cout << "Saliendo del programa...\n";
                break;
            default:
                std::cout << "Opcion no valida.\n";
                break;
        }
    } while (opcion != 4);

    return 0;
}
