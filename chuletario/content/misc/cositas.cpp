// Strings
string firstletter(n, str[0]); // firstletter es n copias del char str[0] concatenadas.
s.insert(0, "012"); // Inserta en s en la posicion 0 el string "012".

// Convertir de enteros <-> string
int i = stoi("1893"); // 1893
string s = i.to_string(); // "1893"

// Ejemplos printf y similares
printf("%.5f", d); // Imprimir un double con 5 digitos tras el punto decimal. Usa %.5Lf para long double.
printf("%s\n", s.c_str()); // Imprimir un string de C++.
printf("%lld\n", unlonglong); // %lld para long long
printf("%0.5d / %0.5d\n", a, b); // Escribe los ints a, b con cinco cifras, paddeado con ceros a la izquierda si es necesario.
printf("%5d", x); // Imprimir un int con anchura 5. Sera paddeado por la izquierda con espacios.
sscanf(s.c_str(), "%s %s", &s, &t); // Parsea el string s en "%s %t"

// Imprimir un string alineado a la izquierda con anchura 21. El string sera paddeado por la derecha con espacios
// si su longitud es menor que 21. Por ejemplo, si p[i] = "San Bernardino", imprimira
// 'San Bernardino       '
printf("%-21s", p[i].c_str());

// Estructuras de datos
priority_queue<di, vector<di>, greater<di>> pq; // min priority queue de (double, int)

// Funciones guays de la STL
auto ai = find(perms.begin(), perms.end(), a); // Busca en perms el elemento a y devuelve un iterador apuntando al elemento, o el iterador perms.end() si no lo encuentra.
transform(t.begin(), t.end(), t.begin(), ::tolower); // Convierte el string t a lower.
bills.erase(--bills.end()); // Borrar el ultimo elemento de un contenedor como set, multiset, map etc.
value.erase(value.begin(), std::find_if(value.begin(), value.end(), std::bind1st(std::not_equal_to<char>(), ' '))); // Removes leading spaces from value.
// Elimina todos los elementos salvo el primero de cada grupo de elementos iguales en el rango.
// Por ejemplo: 10 20 20 20 30 30 20 20 10 ==> 10 20 30 20 10 ?  ?  ?  ?
// Devuelve un iterador al elemento que sigue al ultimo elemento no eliminado, en el ejemplo apuntaria a la primera interrogacion.
auto it = unique (myvector.begin(), myvector.end());
// lower_bound(first, last, val) ==> Returns an iterator pointing to the first element in the range [first,last) which does not compare less than val.
// upper_bound(first, last, val) ==> Returns an iterator pointing to the first element in the range [first,last) which compares greater than val.
// Usa distance(v.begin(), it) para convertir un iterador a una posicion dentro del contenedor

// Si los casos de prueba son lineas de texto y antes te viene el numero de casos de prueba T, asegurate de hacer cin.ignore() para consumir hasta el proximo \n
// (vease UVa 10374 para un ejemplo en el que cin.get() no basta porque meten espacios tras T).
int T;
cin >> T; cin.ignore();
while (T--) {
    string s;
    getline(cin, s);
}

// Leer de un stringstream splitteando por comas
stringstream st(t);
string token;
while (getline(st, token, ',')) {
    // hacer cosas con token
}

// Custom sorting comparator de un tipo. Usa tie() para structs que en realidad son tuplas.
// Pon const antes de { si estas definiendo operator < en un struct.
struct comp {
    bool operator() (const ii &x, const ii &y) {
        return x.first * y.second < x.second * y.first;
    }
};
sort(scores.begin(), scores.end(), cmp()); // Y asi se usa.
set<ii, comp> Fn; // Y asi lo puedes usar en un contenedor ordenado.

// Reverse un string en java.
new StringBuilder(hi).reverse().toString()

double DOUBLE_MAX = numeric_limits<double>::max(); // necesita #include <limits>
