#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;



struct item { //структура для описания элемента карты
    int s, c; //начальный и конечный узлы
    int v; //"вес" пути
};


struct Node
{
    string City; // поле данных
    int index;
    Node* Next; // указатель на следующий элемент
};

Node* AddItem(Node* node, string str, int index)
{
    Node* newNode = new Node();
    newNode->index = index;
    newNode->City = str; // сохранение поля данных добавляемого узла  
    newNode->Next = node->Next; // созданный узел указывает на следующий элемент  
    node->Next = newNode; // предыдущий узел указывает на создаваемый  
    return newNode;
}

bool FindItem(Node* head, string str) {
    Node* temp = head;
    bool check = 0;
    while (temp != NULL) {
        if (temp->City == str) {
            check = 1;
        }
        temp = temp->Next; // переход к следующему узлу 
    };
    return check
        ;
}

int FindIndex(Node* head, string str) {
    Node* temp = head;
    int ind;
    while (temp != NULL) {
        if (temp->City == str) {
            ind = temp->index;
        }
        temp = temp->Next; // переход к следующему узлу 
    };
    return  ind;
    ;
}


string FindNameByIndex(Node* head, int inaa) {
    Node* temp = head;
    string ind;
    while (temp != NULL) {
        if (temp->index == inaa) {
            ind = temp->City;
        }
        temp = temp->Next; // переход к следующему узлу 
    };
    return  ind;
    ;
}

Node* Init(string str, int index) // number - значение первого узла
{
    Node* newNode;
    // выделение памяти под корень списка
    newNode = new Node();
    newNode->City = str;
    newNode->index = index;
    newNode->Next = NULL; // это последний узел списка
    return newNode;
}
Node* Citys;
int counter = 0;
int index = 1;
int matrixC[10][3] = { NULL };

void createListCity() {
    std::ifstream file("city.txt");
    std::string str;
    std::string delimiter = ";";
    size_t pos = 0;
    std::string token;
    while (getline(file, str)) {
        string arrStr[2];
        int i = 0;
        int arrInt[2];
        while (((pos = str.find(delimiter)) != std::string::npos) && i != 2) {
            arrStr[i] = str.substr(0, pos);
            i++;
            str.erase(0, pos + delimiter.length());
        }
        i = 0;

        if (index == 1)
            Citys = Init(arrStr[0], index++);
        if (!FindItem(Citys, arrStr[0]))
            AddItem(Citys, arrStr[0], index++);
        if (!FindItem(Citys, arrStr[1]))
            AddItem(Citys, arrStr[1], index++);

    }
    file.close();
    file.open("city.txt");
    int   fIndexCity = 0;
    while (getline(file, str)) {
        int arrcheck[2] = { NULL };

        int    sIndexCity = 0;
        string arrStr[2];
        int i = 0;
        int arrInt[2];
        while (((pos = str.find(delimiter)) != std::string::npos) && i != 2) {
            arrStr[i] = str.substr(0, pos);
            i++;
            str.erase(0, pos + delimiter.length());
        }
        i = 0;
        while (((pos = str.find(delimiter)) != std::string::npos) && i != 2) {
            if (str[0] == 'N') {

                arrcheck[0] = 1;
            }
            else {
                arrInt[i] = stoi(str.substr(0, pos));
                i++;
            }
            str.erase(0, pos + delimiter.length());
        }
        pos = str.find('\0');
        if (str[0] == 'N')
        {
            arrcheck[1] = 1;

        }
        else {
            arrInt[i] = stoi(str.substr(0, pos));
        }
        if (arrcheck[0] == 1 && arrcheck[1] == 0) {
            matrixC[fIndexCity][sIndexCity++] = FindIndex(Citys, arrStr[0]);
            matrixC[fIndexCity][sIndexCity++] = FindIndex(Citys, arrStr[1]);
            matrixC[fIndexCity++][sIndexCity] = arrInt[0];
            counter++;
        }
        if (arrcheck[1] == 1 && arrcheck[0] == 0) {
            matrixC[fIndexCity][sIndexCity++] = FindIndex(Citys, arrStr[1]);
            matrixC[fIndexCity][sIndexCity++] = FindIndex(Citys, arrStr[0]);
            matrixC[fIndexCity++][sIndexCity] = arrInt[1];
            counter++;
        }
        if (arrcheck[0] == 0 && arrcheck[1] == 0) {
            matrixC[fIndexCity][sIndexCity++] = FindIndex(Citys, arrStr[0]);
            matrixC[fIndexCity][sIndexCity++] = FindIndex(Citys, arrStr[1]);
            matrixC[fIndexCity++][sIndexCity] = arrInt[0];
            sIndexCity = 0;
            matrixC[fIndexCity][sIndexCity++] = FindIndex(Citys, arrStr[1]);
            matrixC[fIndexCity][sIndexCity++] = FindIndex(Citys, arrStr[0]);
            matrixC[fIndexCity++][sIndexCity] = arrInt[1];
            counter += 2;
        }
    }
}


const int m = 6; //количество путей по графу
struct item map[m];

string  citys[10];

const int n = 5; //количество вершин графа
int road[n]; //номера узлов текущей "дороги"
bool incl[n]; //true, если i-ая вершина включена в путь
int way[n]; //искомый самый короткий путь
int waylen; //его длина
int start, finish; //начальная и конечная вершины
bool found;
int len; //найденный "вес" маршрута
int c_len; //текущий "вес" маршрута

int find(int s, int c) { //вес пути из s и c или 0, если пути нет
    for (int i = 0; i < m; i++)
        if (map[i].s == s && map[i].c == c) return map[i].v;
    return 0;
}

int step(int s, int f, int p) { //рекурсивный поиск шага пути
    int c; //номер вершины, куда делаем шаг
    if (s == f) { //путь найден
        found = true; //поставить флажок "найдено"
        len = c_len; //запомнить общий вес пути
        waylen = p; //запомнить длину пути (количество узлов)
        for (int i = 0; i < waylen; i++) way[i] = road[i]; //запомнить сам путь
    }
    else { //выбор очередной точки
        for (c = 0; c < n; c++) { //проверяем все вершины
            int w = find(s, c); //есть ли путь из s в c
            if (w && !incl[c] && (len == 0 || c_len + w < len)) { //нужная точка не включена?
                road[p] = c; //включить точку в путь
                incl[c] = true; //пометить как включенную
                c_len += w; //учесть в общем весе пути
                step(c, f, p + 1); //вызвать себя для поиска следующей точки
                road[p] = 0; //вернуть всё как было
                incl[c] = false;
                c_len -= w;
            }
        }
    }
    return len;
}





int main() {
    setlocale(LC_ALL, "rus");
    //Инициализация данных:
    
    createListCity();
    int first = 0;
    for (int aa = 0; aa < counter; aa++) {
        int second = 0;
        map[aa].s = matrixC[first][second++];
        map[aa].c = matrixC[first][second++];
        map[aa].v = matrixC[first++][second];
    }
    for (int i = 0; i < n; i++) {
        road[i] = way[i] = 0; incl[i] = false;
    }
    len = c_len = waylen = 0;

    start = 1; //начало пути - нумерация с 0
    finish = 4; //конец пути - нумерация с 0
    road[0] = start; //первую точку внесли в маршрут
    incl[start] = true; //и пометили как включённую
    found = false; //но путь пока не найден
    step(start, finish, 1); //ищем вторую точку

    if (found) {
        cout << "Проложенный путь";
        for (int i = 0; i < waylen; i++)
        {
            string strCity;
            strCity = FindNameByIndex(Citys, way[i]);
            cout << " " << strCity;
        }
        cout << ", цена равна " << len;
    }
    else cout << "Города не найдены!";
    cout << endl;
    system("pause");
    return 0;
}