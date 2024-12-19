#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <Windows.h>
#include <cctype>
#include <set>
#include <fstream>
using namespace std;

string word;
string gword;
int n;  // Количество игроков
vector<int> score;
string guessingWords[5]; // Слова игроков для угадывания
set<string> usedWords;  // Набор для хранения уже использованных слов
vector<int> UsedWordsIndex; //Индексы использованных слов

// Проверка на ввод числа
int proverkaInt() {
    int k;
    while (1) {
        if (scanf_s("%d", &k) == 1) {
            break;
        }
        else {
            printf("Некорректный ввод! Попробуйте снова\n");
            while (getchar() != '\n');
        }
    }
    return(k);
}

// Для поиска макс элемента списка
int max_of(vector<int> arr, int len) {
    int maximum = arr[0];
    for (int i = 1; i < len; i++) {
        if (arr[i] > maximum) {
            maximum = arr[i];
        }
    }
    return maximum;
}

// Сдвиг массива на 1 вправо
void arrShift(int arr[], int len) {
    int temp = arr[len - 1];
    for (int i = len - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = temp;
}

// Вывод очков
void ScorePrint() {
    for (int i = 0; i < n; i++) {
        cout << "Очки игрока номер " << i + 1 << ": " << score[i] << '\n';
    }
}

// Функция для введения количества игроков
void CountOfPlayers() {
    cout << "Введите количество игроков (от 2 до 5): ";
    n = proverkaInt();
    while (n < 2 || n > 5) {
        cout << "Недопустимое число игроков\n";
        n = proverkaInt();
    }
    score.resize(n, 0);  // Инициализация вектора для хранения очков игроков

}

// Функция для проверки, что введено число, а не буква
bool isValidNumber(const string& str) {
    return all_of(str.begin(), str.end(), ::isdigit);
}

string associations_0[5][3]{};

bool in_use(int index) {
    for (int i = 0; i < UsedWordsIndex.size(); i++) {
        if (index == UsedWordsIndex[i]) {
            return true;
        }
    }
    return false;
}

// функция для преобразования всех букв слова в строчные
string toLowerCase(const string& word)
{
    string result = word;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Ввод отгадываемых слов
void guessword() {
    cout << "Введите слово: ";
    cin >> gword;
    gword = toLowerCase(gword);
}

// Функция для словаря
void vocabulary() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned int>(time(0)));
    vector<string> vocabulary = { "яблоко", "зима", "книга", "урок", "утро", "ночь", "солнце", "луна", "звезда", "дождь", "снег", "мороз", "ветер", "туман", "облако", "день", "осень", "весна", "лето", "роза", "лес", "река", "море", "озеро", "гора", "пик", "берег", "пляж", "трава", "цветок", "дерево", "птица", "рыба", "кот", "собака", "мышь", "заяц", "волк", "лиса", "еж", "медведь", "бабочка", "пчела", "жук", "паутина", "шар", "игра", "музыка", "песня", "танец", "улыбка", "смех", "радость", "грусть", "любовь", "дружба", "детство", "школа", "университет", "работа", "отдых", "праздник", "вечер", "дом", "квартира", "комната", "окно", "дверь", "стол", "стул", "кресло", "кровать", "шкаф", "тетрадь", "ручка", "карандаш", "линейка", "сумка", "рюкзак", "одежда", "обувь", "шапка", "шарф", "перчатки", "куртка", "пальто", "рубашка", "брюки", "юбка", "платье", "футболка", "блузка", "свитер", "ботинки", "туфли", "сапоги", "шорты", "плавки", "шляпа", "очки", "часы", "кольцо", "браслет", "серьги", "цепочка", "кулон", "машина", "автобус", "трамвай", "троллейбус", "поезд", "самолет", "вертолет", "корабль", "лодка", "велосипед", "скутер", "мотоцикл", "улица", "площадь", "парк", "мост", "здание", "библиотека", "музей", "театр", "кино", "магазин", "кафе", "ресторан", "бар", "пицца", "суп", "каша", "блины", "варенье", "молоко", "сыр", "мясо", "хлеб", "масло" };

    if (vocabulary.size() == UsedWordsIndex.size()) {
        UsedWordsIndex.clear();
    }
    int randomIndex = rand() % vocabulary.size();

    while (in_use(randomIndex)) {
        randomIndex = rand() % vocabulary.size();
    }
    word = vocabulary[randomIndex];
    // Пока слово уже использовано, генерировать новое
    usedWords.insert(word);
    UsedWordsIndex.push_back(randomIndex);
    cout << "Ваше слово: " << word << endl;
}

// Функция для проверки корректности ввода
int check(int i, int b) {
    int sizes = associations_0[i][b].size(); // размер введенной строки

    // Удаляет лишние пробелы в начале и конце строки
    while (!associations_0[i][b].empty() && associations_0[i][b][0] == ' ') {
        associations_0[i][b].erase(0, 1);
        sizes = associations_0[i][b].size();
    }

    while (!associations_0[i][b].empty() && associations_0[i][b][sizes - 1] == ' ') {
        associations_0[i][b].erase(sizes - 1, 1);
        sizes = associations_0[i][b].size();
    }

    // Удаляет лишние пробелы между словами
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        for (int j = 0; j < sizes - 1; j++) {
            if (associations_0[i][b][j] == ' ' && associations_0[i][b][j + 1] == ' ') {
                associations_0[i][b].erase(j, 1);
                sizes = associations_0[i][b].size();
                sorted = false;
            }
        }
    }

    // Преобразует все буквы в буквы нижнего регистра
    for (int q = 0; q < sizes; q++) {
        associations_0[i][b][q] = tolower(associations_0[i][b][q]);
    }

    // Проверяет количество введенных слов
    int counter = 0;
    for (int q = 0; q < sizes; q++) {
        if (associations_0[i][b][q] == ' ')
            counter++;
    }
    counter++;

    if (counter != 3) {
        cout << "Вы ввели неправильное количество слов!\n";
        return 1;
    }
    else {
        return 0;
    }
}

// Функция для угадывания
void guessing() {
    int answer;
    cout << "Если Вы довольны ответами игроков, нажмите 1" << endl << "Если нет, нажмите 0" << endl;
    cin >> answer;
    if (answer == 1)
        cout << "Слово отгадано" << endl;
    else if (answer == 0)
        cout << "Игроки не смогли отгадать слово" << endl;
}

// Функция для ввода ассоциаций каждым игроком
void create_associations() {
    getchar();
    for (int i = 0; i < n; i++) {
        cout << "Игрок " << i + 1 << endl;
        vocabulary();
        guessingWords[i] = word;
        bool is_input_true = true; // остается true если игрок ввел неправильное количество слов
        while (is_input_true) {
            cout << "Придумайте 3 прилагательных к слову и введите их в строку через пробел\n";

            getline(cin, associations_0[i][0]);

            is_input_true = check(i, 0);
        }

        is_input_true = true;
        while (is_input_true) {
            cout << "Придумайте 3 глагола к слову и введите их в строку через пробел\n";
            getline(cin, associations_0[i][1]);

            is_input_true = check(i, 1);
        }

        is_input_true = true;
        while (is_input_true) {
            cout << "Придумайте 3 существительных к слову и введите их в строку через пробел\n";
            getline(cin, associations_0[i][2]);
            is_input_true = check(i, 2);
        }

        system("cls"); // очистка консоли
    }
}

// Функция для вывода ассоциаций, угадывания, подсчёта очков
void OutputAssociations(int order[]) {
    for (int i = 0; i < n; i++) {
        cout << "Сейчас играет игрок номер " << i + 1 << '\n';
        cout << "Угадай слово игрока номер " << order[i] + 1 << '\n';
        cout << "Ассоциации игрока (прилагательные) " << order[i] + 1 << ": " << associations_0[order[i]][0] << endl;
        guessword();
        word = guessingWords[order[i]];
        if (gword == word) {
            cout << "Вы победили и получили 3 очка" << endl;
            score[i] += 3;
        }
        else {
            cout << "Неправильно!\nАссоциации игрока (глаголы) " << order[i] + 1 << ": " << associations_0[order[i]][1] << endl;
            guessword();
            if (gword == word) {
                cout << "Вы победили и получили 2 очка" << endl;
                score[i] += 2;
            }
            else {
                cout << "Неправильно!\nАссоциации игрока (существительные) " << order[i] + 1 << ": " << associations_0[order[i]][2] << endl;
                guessword();
                if (gword == word) {
                    cout << "Вы победили и получили 1 очко" << endl;
                    score[i] += 1;
                    score[order[i]] += 1;
                }
                else {
                    cout << "Неправильно!\nВы проиграли" << endl;
                    score[order[i]] -= 1;
                }
            }
        }
        guessing();
        system("cls"); // очистка консоли  
    }


}

//Проверка на конец игры от 15 очков
bool CheckForEnd() {

    for (int i = 0; i < n; i++) {
        if (score[i] > 15) {
            return true;
        }
    }

    return false;
}

//Главная функция игрового процесса
void Game() {
    int* order = new int[n];    //ордер - порядок т.е. слово какого игрока текущий игрок будет угадывать
    for (int i = 0; i < n; i++) {
        order[i] = i;
    }

    arrShift(order, n);         //Функция для сдвига порядка (1-5, 2-1, 3-2, 4-3, 5-4) и т.д.
    while (!CheckForEnd()) {

        create_associations();
        OutputAssociations(order);

        arrShift(order, n);
        if (order[0] == 0) {
            arrShift(order, n);
        }
        ScorePrint();
        cout << "Нажмите любую клавишу для продолжения";
        system("pause>nul");
        system("cls");
    }
    ScorePrint();
    int maxScore = max_of(score, n);
    cout << "Поздравляем победителя(ей)!!!\n";
    for (int i = 0; i < n; i++) {
        if (score[i] == maxScore) {
            cout << "Игрок номер " << i + 1 << '\n';
        }
    }

    cout << "Спасибо за игру :)";

    delete[] order;
}

int main() {

    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    CountOfPlayers();

    Game();


    system("pause>nul"); // Эта команда приостанавливает выполнение программы до тех пор, пока пользователь не нажмет клавишу, чтобы он мог увидеть результат 
}
