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

void maxScaleConsole()
{
    HWND Hwnd = GetForegroundWindow();
    ShowWindow(Hwnd, SW_MAXIMIZE);
} //полноэкранный режим


int getConsoleWidth()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
} //нахождение длины консоли


void printCentered(const string& text)
{
    int width = getConsoleWidth();
    int padding = (width - text.length()) / 2;

    cout << string(padding, ' ') << text << endl;
} //текст по центру


void beginning()
{
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");

    system("pause>nul");

    maxScaleConsole();

    system("pause>nul");
    system("cls");

    cout << endl;

    printCentered("    аааа    ссссссс   ссссссс   ооооооо    цц    цц     ии    иии       аааа    цц    цц     ии    иии   ии    иии");
    printCentered("   аа аа    сс        сс        оо   оо    цц    цц     ии   ииии      аа аа    цц    цц     ии   ииии   ии   ииии");
    printCentered("  аа  аа    сс        сс        оо   оо    цц    цц     ии иии ии     аа  аа    цц    цц     ии иии ии   ии иии ии");
    printCentered(" ааааааа    сс        сс        оо   оо    цц    цц     ииии   ии    ааааааа    цц    цц     ииии   ии   ииии   ии");
    printCentered("аа    аа    ссссссс   ссссссс   ооооооо    цццццццццц   иии    ии   аа    аа    цццццццццц   иии    ии   иии    ии");
    printCentered("                                                   цц                                   цц                        ");

    cout << endl << endl;

    printCentered("Добро пожаловать в игру! :)");
    printCentered("Нажмите любой символ для просмотра правил");

    system("pause>nul");
    system("cls");

    cout << endl;

    printCentered("    !!!!!!!!!!!    ");
    printCentered("  !!!!!!!!!!!!!!!  ");
    printCentered(" !!!!!!!!!!!!!!!!! ");
    printCentered("!!!!!!!!!!!!!!!!!!!");
    printCentered("!!!!!!!!!!!!!!!!!!!");
    printCentered(" !!!!!!!!!!!!!!!!! ");
    printCentered("  !!!!!!!!!!!!!!!  ");
    printCentered("   !!!!!!!!!!!!!   ");
    printCentered("    !!!!!!!!!!!    ");
    printCentered("     !!!!!!!!!     ");
    printCentered("      !!!!!!!      ");
    printCentered("       !!!!!       ");
    printCentered("                   ");
    printCentered("      !!!!!!!      ");
    printCentered("      !!!!!!!      ");
    printCentered("      !!!!!!!      ");

    cout << endl << endl;

    printCentered("*********    *********      ****    *******    **    ***       ****       ****");
    printCentered("**     **    **     **     ** **    **   **    **   ****      ** **      ** **");
    printCentered("**     **    *********    **  **    *****      ** **  **     **  **     **  **");
    printCentered("**     **    **          *******    **   **    ****   **    **   **    *******");
    printCentered("**     **    **         **    **    *******    ***    **   **    **   **    **");

    cout << endl << endl;

    printCentered("В игре участвуют 2-5 игроков. Игра делится на несколько раундов. Каждый раунд проходит в 2 этапа."); cout << endl << endl;
    printCentered("Этап 1 - Загадывание.");
    printCentered("Вам дается слово. Ваша задача:");
    printCentered("1) Придумать 3 прилагательных-ассоциации к слову. ");
    printCentered("2) Придумать 3 глагола-ассоциации к слову.        ");
    printCentered("3) Придумать 3 существительных-ассоциации к слову."); cout << endl << endl;
    printCentered("Этап 2 - Угадывание.          ");
    printCentered("У вас есть 3 попытки, чтобы угадать загаданное слово.                    ");
    printCentered("В каждой попытке вам будут представлены ассоциации к этому слову.        ");
    printCentered("Ваша задача - угадать загаданное слово за наименьшее количество попыток. ");
    printCentered("Если вы угадали слово с 1-ой попытки, то вы получаете 3 очка; если со 2-ой попытки - вы получаете 2 очка.              ");
    printCentered("Если вы угадали слово с 3-ей попытки, то вы получаете 1 очко, и игрок, загадавший слово, также получает 1 очко.        ");
    printCentered("Если вы и с 3-ей попытки не угадали слово, то у игрока, загадавшего слово, отнимается 1 очко                           ");
    cout << endl << endl;
    printCentered("Игра длится до тех пор, пока хотя бы один из игроков не наберет 15 очков."); cout << endl;
    printCentered("УДАЧИ В ИГРЕ!!! ;)");

    system("pause>nul");
    system("cls");
}


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
            printf("    Некорректный ввод! Попробуйте снова\n");
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
    cout << "Итоги раунда: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "   Очки игрока номер " << i + 1 << ": " << score[i] << '\n';
    }
}

// Функция для введения количества игроков
void CountOfPlayers() {
    cout << endl;
    cout << "   Введите количество игроков (от 2 до 5): ";
    n = proverkaInt();
    while (n < 2 || n > 5) {
        cout << "   Недопустимое число игроков\n";
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
    cout << "   Введите слово: ";
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
    cout << "\n   Ваше слово: # " << word << " #\n" << endl;
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
        cout << "   Вы ввели неправильное количество слов!\n";
        return 1;
    }
    else {
        return 0;
    }
}




// Функция для ввода ассоциаций каждым игроком
void create_associations() {
    getchar();
    for (int i = 0; i < n; i++) {
        cout << "   Игрок " << i + 1 << ", приготовьтесь загадывать!" << endl;
        cout << "   Нажмите любую клавишу для продолжения" << endl;
        system("pause>nul");
        vocabulary();
        guessingWords[i] = word;
        bool is_input_true = true; // остается true если игрок ввел неправильное количество слов
        while (is_input_true) {
            cout << "   Придумайте 3 прилагательных к слову и введите их в строку через пробел\n";

            getline(cin, associations_0[i][0]);

            is_input_true = check(i, 0);
        }

        is_input_true = true;
        while (is_input_true) {
            cout << "   Придумайте 3 глагола к слову и введите их в строку через пробел\n";
            getline(cin, associations_0[i][1]);

            is_input_true = check(i, 1);
        }

        is_input_true = true;
        while (is_input_true) {
            cout << "   Придумайте 3 существительных к слову и введите их в строку через пробел\n";
            getline(cin, associations_0[i][2]);
            is_input_true = check(i, 2);
        }

        system("cls"); // очистка консоли
    }
}

// Функция для вывода ассоциаций, угадывания, подсчёта очков
void OutputAssociations(int order[]) {
    for (int i = 0; i < n; i++) {
        cout << endl;
        cout << "   Сейчас играет игрок номер " << i + 1 << '\n';
        cout << "   Нажмите любую клавишу для продолжения";
        system("pause>nul");
        cout << endl<< "   Угадай слово игрока номер " << order[i] + 1 << '\n';
        cout << "   Ассоциации игрока номер " << order[i] + 1 << " (прилагательные) " << ": " << associations_0[order[i]][0] << endl;
        guessword();
        word = guessingWords[order[i]];
        if (gword == word) {
            cout << endl;
            cout << "   Вы угадали и получили 3 очка" << endl;
            score[i] += 3;
            cout << "   Нажмите любую клавишу для продолжения";
            system("pause>nul");
        }
        else {
            cout << "   Неправильно!\n  Ассоциации игрока (глаголы) " << order[i] + 1 << ": " << associations_0[order[i]][1] << endl;
            guessword();
            if (gword == word) {
                cout << "   Вы угадали и получили 2 очка" << endl;
                score[i] += 2;
                cout << "   Нажмите любую клавишу для продолжения";
                system("pause>nul");
            }
            else {
                cout << "   Неправильно!\n  Ассоциации игрока (существительные) " << order[i] + 1 << ": " << associations_0[order[i]][2] << endl;
                guessword();
                if (gword == word) {
                    cout << "   Вы угадали и получили 1 очко" << endl;
                    score[i] += 1;
                    score[order[i]] += 1;
                    cout << "   Нажмите любую клавишу для продолжения";
                    system("pause>nul");
                }
                else {
                    cout << "   Неправильно!\n  Вы не угадали слово!" << endl;
                    score[order[i]] -= 1;
                    cout << "   Нажмите любую клавишу для продолжения";
                    system("pause>nul");
                }
            }
        }
        
        system("cls"); // очистка консоли  
    }


}

//Проверка на конец игры от 15 очков
bool CheckForEnd() {

    for (int i = 0; i < n; i++) {
        if (score[i] >= 15) {
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
        cout << endl;
        cout << "   Нажмите любую клавишу для продолжения";
        system("pause>nul");
        system("cls");
    }
    ScorePrint();
    int maxScore = max_of(score, n);
    cout << endl;
    cout << "   Поздравляем победителя(ей)!!!\n";
    for (int i = 0; i < n; i++) {
        if (score[i] == maxScore) {
            cout << "   *Игрок номер " << i + 1 << '\n';
        }
    }

    delete[] order;
}

void ending()
{
    printCentered("Спасибо за игру :)"); cout << endl;

    printCentered("_______________00000­00000000000_________­_______");
    printCentered("_____________000___­_____________0000___­_________");
    printCentered("_________000__________________________00­_________");
    printCentered("_______00__________­____________________­_0_______");
    printCentered("_____00________0000­00_______000000_____­___0_____");
    printCentered("___00_____000000000­0000___000000000000_­____00___");
    printCentered("__0_____0000_______­_________________000­0_____0__");
    printCentered("_0_________________­__________000000____­_______0_");
    printCentered("0__________________­________00______00__­________0");
    printCentered("0___________000000_­_______00__0000__00_­________0");
    printCentered("0________0000000000­00_____00_000000_00_­________0");
    printCentered("0__________________­_______00_000000_00_­________0");
    printCentered("0__________________­_______00__0000__00_­________0");
    printCentered("0__________________­________00______00__­________0");
    printCentered("0__________________­__________000000____­________0");
    printCentered("_0_________________­________________00__­___00__0_");
    printCentered("__0___________000__­_______________0__0_­__0__0___");
    printCentered("___0____________000­0______________0__0_­_0__0____");
    printCentered("_____0____________0­000000_________0__0_­0__0_____");
    printCentered("_______00__________­_______________0___0­___00000_");
    printCentered("_________000_______­______________000000­0___0__0_");
    printCentered("_____________000___­_____________0______­_0__0__0_");
    printCentered("________________000­000000000000_00__000­0_00_00__");
    printCentered("___________________­_____________000____­______");
}


int main() {

    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    beginning();
    CountOfPlayers();

    Game();

    ending();

    system("pause>nul"); // Эта команда приостанавливает выполнение программы до тех пор, пока пользователь не нажмет клавишу, чтобы он мог увидеть результат 
}
