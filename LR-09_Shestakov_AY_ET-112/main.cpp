//
//  main.cpp
//  LR-09_Shestakov_AY_ET-112
//
//  Created by Alexander on 4/13/26.
//

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

enum FilmType {
    DRAMA,
    COMEDY,
    THRILLER,
    ACTION,
    HORROR,
    FANTASY,
    BIOGRAPHY
};

struct Director {
    char firstName[50];
    char lastName[50];
};

struct Film {
    char title[100];
    Director director;
    FilmType type;
    int year;
    int duration;
    double budget;
    double kinopoiskRating;
    char mainActor[100];
};

const char* filmTypeToString(FilmType t) {
    switch (t) {
        case DRAMA:     return "Драма";
        case COMEDY:    return "Комедия";
        case THRILLER:  return "Триллер";
        case ACTION:    return "Боевик";
        case HORROR:    return "Ужасы";
        case FANTASY:   return "Фэнтези";
        case BIOGRAPHY: return "Биография";
        default:        return "Неизвестно";
    }
}

void printFilm(const Film& f) {
    cout << "  Название:        " << f.title << "\n";
    cout << "  Режиссёр:        " << f.director.firstName << " " << f.director.lastName << "\n";
    cout << "  Жанр:            " << filmTypeToString(f.type) << "\n";
    cout << "  Год выпуска:     " << f.year << "\n";
    cout << "  Длительность:    " << f.duration << " мин.\n";
    cout << "  Бюджет:          " << f.budget << " млн $\n";
    cout << "  Рейтинг КП:      " << f.kinopoiskRating << "\n";
    cout << "  Главный актёр:   " << f.mainActor << "\n";
    cout << "  ----------------------------------------\n";
}

void printArray(const Film arr[], int n, const char* header) {
    cout << "\n========================================\n";
    cout << header << "\n";
    cout << "========================================\n";
    for (int i = 0; i < n; i++) {
        cout << "[" << i + 1 << "]\n";
        printFilm(arr[i]);
    }
}

int filterNicoleKidman(const Film src[], int srcSize, Film dst[]) {
    int count = 0;
    for (int i = 0; i < srcSize; i++) {
        if (strcmp(src[i].mainActor, "Nicole Kidman") == 0) {
            dst[count++] = src[i];
        }
    }
    return count;
}

void bubbleSortByTitle(Film arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j].title, arr[j + 1].title) > 0) {
                Film tmp = arr[j];
                arr[j]   = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

void printFilmByTitle(const Film arr[], int n, const char* title) {
    cout << "\n========================================\n";
    cout << "Поиск фильма: \"" << title << "\"\n";
    cout << "========================================\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].title, title) == 0) {
            printFilm(arr[i]);
            found = true;
        }
    }
    if (!found) cout << "  Фильм не найден.\n";
}

void printTop6ExpensiveIn2000s(const Film arr[], int n) {
    int idx[20], cnt = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].year >= 2000 && arr[i].year <= 2009)
            idx[cnt++] = i;
    }
    for (int i = 0; i < cnt - 1; i++) {
        for (int j = 0; j < cnt - i - 1; j++) {
            if (arr[idx[j]].budget < arr[idx[j + 1]].budget) {
                int tmp  = idx[j];
                idx[j]   = idx[j + 1];
                idx[j + 1] = tmp;
            }
        }
    }
    int top = (cnt < 6) ? cnt : 6;
    cout << "\n========================================\n";
    cout << "Топ-6 самых дорогих фильмов 2000-х годов\n";
    cout << "========================================\n";
    for (int i = 0; i < top; i++) {
        cout << "[" << i + 1 << "]\n";
        printFilm(arr[idx[i]]);
    }
}

void editFilm(Film arr[], int n, const char* title,
              double newBudget, double newRating, int newDuration) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].title, title) == 0) {
            arr[i].budget          = newBudget;
            arr[i].kinopoiskRating = newRating;
            arr[i].duration        = newDuration;
            cout << "\n[Редактирование] Фильм \"" << title << "\" обновлён.\n";
            printFilm(arr[i]);
            return;
        }
    }
    cout << "\n[Редактирование] Фильм \"" << title << "\" не найден.\n";
}

void filterWrapper(const Film arr[], int n,
                   FilmType requiredType, const char* directorFirstName,
                   Film result[], int& resultCount) {
    resultCount = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].type == requiredType &&
            strcmp(arr[i].director.firstName, directorFirstName) == 0) {
            result[resultCount++] = arr[i];
        }
    }
    int unique = 0;
    Film tmp[20];
    for (int i = 0; i < resultCount; i++) {
        bool dup = false;
        for (int j = 0; j < i; j++) {
            if (strcmp(result[i].director.lastName,
                       result[j].director.lastName) == 0) {
                dup = true;
                break;
            }
        }
        if (!dup) tmp[unique++] = result[i];
    }
    for (int i = 0; i < unique; i++) result[i] = tmp[i];
    resultCount = unique;
}

void printFilteredWrapper(const Film arr[], int n,
                          FilmType type, const char* firstName) {
    Film result[20];
    int cnt = 0;
    filterWrapper(arr, n, type, firstName, result, cnt);

    cout << "\n========================================\n";
    cout << "Триллеры с режиссёром по имени \"" << firstName
         << "\" (разные режиссёры)\n";
    cout << "========================================\n";
    if (cnt == 0) {
        cout << "  Нет подходящих фильмов.\n";
        return;
    }
    for (int i = 0; i < cnt; i++) {
        cout << "[" << i + 1 << "]\n";
        printFilm(result[i]);
    }
}

int main() {
    // ===== Массив из 20 фильмов =====
    Film films[20] = {
        {"Moulin Rouge!",        {"Baz",      "Luhrmann"}, DRAMA,     2001, 127, 52.5,  7.6, "Nicole Kidman"},
        {"The Others",           {"Alejandro","Amenabar"}, HORROR,    2001, 101, 17.0,  7.6, "Nicole Kidman"},
        {"Eyes Wide Shut",       {"Stanley",  "Kubrick"},  THRILLER,  1999, 159, 65.0,  7.4, "Nicole Kidman"},
        {"Dogville",             {"Lars",     "von Trier"},DRAMA,     2003, 178, 10.0,  7.9, "Nicole Kidman"},
        {"The Dark Knight",      {"Christopher","Nolan"},  ACTION,    2008, 152, 185.0, 8.9, "Christian Bale"},
        {"Inception",            {"Christopher","Nolan"},  THRILLER,  2010, 148, 160.0, 8.7, "Leonardo DiCaprio"},
        {"Gladiator",            {"Ridley",   "Scott"},    ACTION,    2000, 155, 103.0, 8.6, "Russell Crowe"},
        {"The Aviator",          {"Martin",   "Scorsese"}, BIOGRAPHY, 2004, 170, 110.0, 7.5, "Leonardo DiCaprio"},
        {"Se7en",                {"David",    "Fincher"},  THRILLER,  1995, 127, 33.0,  8.6, "Brad Pitt"},
        {"Zodiac",               {"David",    "Fincher"},  THRILLER,  2007, 157, 65.0,  7.7, "Jake Gyllenhaal"},
        {"John Wick",            {"Chad",     "Stahelski"}, ACTION,   2014, 101, 20.0,  7.4, "Keanu Reeves"},
        {"John Wick 2",          {"Chad",     "Stahelski"}, ACTION,   2017, 122, 40.0,  7.5, "Keanu Reeves"},
        {"Prisoners",            {"Denis",    "Villeneuve"},THRILLER, 2013, 153, 46.0,  8.1, "Hugh Jackman"},
        {"Australia",            {"Baz",      "Luhrmann"}, DRAMA,     2008, 165, 130.0, 6.6, "Nicole Kidman"},
        {"Batman Begins",        {"Christopher","Nolan"},  ACTION,    2005, 140, 150.0, 8.2, "Christian Bale"},
        {"Psycho",               {"John",     "Carpenter"},THRILLER,  1960, 109,  6.5,  8.5, "Anthony Perkins"},
        {"Halloween",            {"John",     "Carpenter"},HORROR,    1978,  91,  0.3,  7.7, "Donald Pleasence"},
        {"The Thing",            {"John",     "Carpenter"},HORROR,    1982, 109, 15.0,  8.1, "Kurt Russell"},
        {"Minority Report",      {"Steven",   "Spielberg"},ACTION,    2002, 145, 102.0, 7.6, "Tom Cruise"},
        {"War of the Worlds",    {"Steven",   "Spielberg"},ACTION,    2005, 116, 132.0, 6.5, "Tom Cruise"}
    };
    const int N = 20;

    printArray(films, N, "Исходный массив фильмов");

    Film kidmanFilms[20];
    int kidmanCount = filterNicoleKidman(films, N, kidmanFilms);
    printArray(kidmanFilms, kidmanCount, "Фильмы с Николь Кидман");

    bubbleSortByTitle(kidmanFilms, kidmanCount);
    printArray(kidmanFilms, kidmanCount, "Фильмы с Николь Кидман (по алфавиту)");

    printFilmByTitle(films, N, "Inception");

    printTop6ExpensiveIn2000s(films, N);

    editFilm(films, N, "Gladiator", 115.0, 8.7, 157);

    printFilteredWrapper(films, N, THRILLER, "John");

    return 0;
}
