//Shanti Gharib
//Lab 3

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>




class Creature {


private:


    int health{0}, strength{0};
    std::string type{""}, name{""};


public:
    
    enum class Field {
    
        NAME = 1,
        TYPE,
        HEALTH,
        STRENGTH,
    
    };
    
    inline int GetHealth();
    inline int GetStrength();

    inline const std::string &GetType();
    inline const std::string &GetName();
    std::string ToString() const;

    void SetCreature(const std::string &creatureName, const std::string &creatureType, int health, int strength);

};







void PrintArrayOfCreatures(Creature *creatures[], const int &creaturesCount);
void      PrintArrayHeader();
void   PrintSeparationLine(int width);

inline int                GetIntegerCreatureField(Creature &creature, int field);
inline const std::string&  GetStringCreatureField(Creature &creature, int field);

char     NormalizedChar(const char c);
void    NormalizeString(std::string &str);
bool     CompareStrings(const std::string &str1, const std::string &str2, bool decreasing);
inline bool CompareInts(const int v0, const int v1, bool decreasing);

void               SortCreatures(Creature   creatures[], const int &creaturesCount);
void             SearchCreatures(Creature   creatures[], const int &creaturesCount);
void SortArrayofCreaturePointers(Creature *pCreatures[], const int field, const int &creaturesCount);

void              ReadFile(Creature creatures[], Creature *pCreatures[], int &creaturesCount);
void       DisplayMainMenu();
void    DisplaySortSubMenu();
void HandleDefaultMenuCase();






static constexpr const int CREATURE_SIZE_MAX{25}, HEADING_WIDTH{65};

static const std::string INPUT_FILE{"in_creatures.txt"};


int main() {

    
    Creature   creatures[CREATURE_SIZE_MAX];
    
    Creature *pCreatures[CREATURE_SIZE_MAX];
    
    int creaturesCount{0};

    ReadFile(creatures, pCreatures, creaturesCount);


    enum { PRINT_CREATURES = 1, SORT_CREATURES, SEARCH_CREATURES, QUIT };

    int option{0};

    while (option != QUIT) {
    
        
        DisplayMainMenu();
        
        std::cin >> option;


        switch (option) {
        
            case PRINT_CREATURES: {
                
                PrintArrayOfCreatures(pCreatures, creaturesCount);

                break;
            
            }

            case SORT_CREATURES: {
            
                SortCreatures(creatures, creaturesCount);

                break;
            
            }

            case SEARCH_CREATURES: {
            
                SearchCreatures(creatures, creaturesCount);

                break;
            
            
            }

            case QUIT: {
            
                std::cout << "Program now closed.\n\n";

                break;
            
            }

            default: {
            
                HandleDefaultMenuCase();

                break;
            
            }


        }
    
    
    }


}






inline int Creature::GetHealth() {
    
    return health;

}

inline int Creature::GetStrength() {

    return strength;

}

inline const std::string & Creature::GetType() {

    return type;

}

inline const std::string & Creature::GetName() {

    return name;

}

void Creature::SetCreature(const std::string &creatureName, const std::string &creatureType, int creatureHealth, int creatureStrength) {


        name =     creatureName;
        type =     creatureType;
      health =   creatureHealth;
    strength = creatureStrength;


}

std::string Creature::ToString() const {
    

    std::stringstream stream;
    
    
    stream << "| " << std::left
        << std::setw(15) << name     << " | "
        << std::setw(15) << type     << " | " << std::right
        << std::setw(10) << health   << " | "
        << std::setw(10) << strength << " | ";
    

    return stream.str();


}






void ReadFile(Creature creatures[], Creature *pCreatures[], int &creaturesCount) {

    
    std::ifstream stream(INPUT_FILE);


    if (stream.is_open()) {
    
        
        while (creaturesCount < CREATURE_SIZE_MAX && stream.good()) {
        

            std::string name{""}, type{""};
            int health{0}, strength{0};

            stream >> name >> type >> health >> strength;
            for (int i = 0; i < name.size(); ++i) if (name[i] == '_') name[i] = ' ';
            stream.ignore(std::numeric_limits<int>::max(), '\n');

            creatures[creaturesCount].SetCreature(name, type, health, strength);
            ++creaturesCount;
        

        }
        
        
        if ( creaturesCount == CREATURE_SIZE_MAX && stream.good() ) {
            
            std::cout << "\nCreatures in input file exceed max amount\n";
        
        }


        stream.close();
    
        
        for (int i = 0; i < creaturesCount; ++i) pCreatures[i] = &creatures[i];


    }

    else {
    

        std::cout << "Could not open input file. Now terminating\n\n";
        
        exit(EXIT_FAILURE);
    

    }
    

}

void HandleDefaultMenuCase() {


    std::cout << "\nInvalid option selected\n";
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


}

void PrintArrayHeader() {
    
    
    std::cout << "\n\n| " << std::left
        << std::setw(15)  << "Name"     << " | "
        << std::setw(15)  << "Type"     << " | "
        << std::setw(10)  << "Health"   << " | "
        << std::setw(10)  << "Strength" << " | " << std::right; 


}

inline int GetIntegerCreatureField(Creature &creature, int field) {

    return (field == static_cast<int>(Creature::Field::HEALTH) ? creature.GetHealth() : creature.GetStrength());

}

inline const std::string& GetStringCreatureField(Creature &creature, int field) {
    
    return (field == static_cast<int>(Creature::Field::NAME) ? creature.GetName() : creature.GetType());


}

char NormalizedChar(const char c) {

    char res{c};

    if ('a' <= res && res <= 'z') {
    
        res += 'A' - 'a';

    }

    return res;

}

bool CompareStrings(const std::string &str1, const std::string &str2, bool decreasing = 1) {

    const int end = std::min(str1.size(), str2.size());
    
    int i{0}; while (i < end && NormalizedChar(str1[i]) == NormalizedChar(str2[i])) ++i;

    bool res{0};
    
    if (i == end) {
        

        res = (decreasing) ? str1.size() > str2.size() : str1.size() < str2.size();

    }
    
    else {
        
        const char c1{NormalizedChar(str1[i])}, c2{NormalizedChar(str2[i])};
        res = (decreasing) ? c1 > c2 : c1 < c2;
    
    }

    return res;

}

void PrintArrayOfCreatures(Creature *creatures[], const int &creaturesCount) {
          
         
    PrintArrayHeader();
    std::cout << "\n";


    PrintSeparationLine(HEADING_WIDTH);
         
        
    for (int i = 0; i < creaturesCount; ++i) {
         
        std::cout << creatures[i]->ToString() << "\n";

    }   


    PrintSeparationLine(HEADING_WIDTH);
    std::cout << "\n";


}

inline bool CompareInts(const int v0, const int v1, bool decreasing = 1) {

    return (decreasing) ? v0 > v1 : v0 < v1;

}

void PrintSeparationLine(int width) {
    std::cout << std::setfill('-') << std::setw(width) << "" << std::setfill(' ') << "\n";
}

void SortArrayofCreaturePointers(Creature *pCreatures[], const int field, const int &creaturesCount) {


    bool isSorted{0};

    while (!isSorted) {
    
        isSorted = 1;

        for (int i = 1; i < creaturesCount; ++i) {
        
            if (  ( field <= static_cast<int>(Creature::Field::TYPE) && CompareStrings( GetStringCreatureField(*pCreatures[i], field), GetStringCreatureField(*pCreatures[i-1], field) ) )
                                
                    || ( field > static_cast<int>(Creature::Field::TYPE) && CompareInts( GetIntegerCreatureField(*pCreatures[i], field), GetIntegerCreatureField(*pCreatures[i-1], field) ) )  ) {
                        
                            
                    isSorted = 0;

                    Creature *pTemp{pCreatures[i]};

                    pCreatures[i] = pCreatures[i-1];
                    pCreatures[i-1] = pTemp;
                          
                        
            }
        
        }
    
    
    }

}

void SortCreatures(Creature creatures[], const int &creaturesCount) {
    
    Creature *pCreatures[CREATURE_SIZE_MAX];

    for (int i = 0; i < creaturesCount; ++i) {
    
        pCreatures[i] = &creatures[i];
    
    }
    
    int option{0};
    static constexpr const int ESCAPE{5};

    while (option != ESCAPE) {
    
        DisplaySortSubMenu();

        std::cin >> option;

        switch (option) {
        
            case static_cast<int>(Creature::Field::    NAME):
            case static_cast<int>(Creature::Field::    TYPE):
            case static_cast<int>(Creature::Field::  HEALTH):
            case static_cast<int>(Creature::Field::STRENGTH): {
            
                
                SortArrayofCreaturePointers(pCreatures, option, creaturesCount);
                

                PrintArrayOfCreatures(pCreatures, creaturesCount);


                break;
                        
            }

            case ESCAPE: {
            
                std::cout << "Leaving sub-menu\n\n";

                break;
            
            }

            default: {
            
                HandleDefaultMenuCase();
            
            }
        
        }
    
    }


}

void NormalizeString(std::string &str) {

        for (int i = 0; i < str.size(); ++i) {
        
            str[i] = NormalizedChar(str[i]);
            
        }

}

void SearchCreatures(Creature creatures[], const int &creaturesCount) {

    
    std::cout << "\nEnter search query:\n\n";
    
    std::string searchQuery{""};
    while (searchQuery.empty()) std::getline(std::cin, searchQuery);

    NormalizeString(searchQuery);

    std::cout << "\nEntries Found:\n\n";

    PrintArrayHeader();
    
    std::cout << "\n";

    PrintSeparationLine(HEADING_WIDTH);

    for (int i = 0; i < creaturesCount; ++i) {
        
        std::string name{creatures[i].GetName()}, type{creatures[i].GetType()};
        NormalizeString(name); NormalizeString(type);
        if (name.find(searchQuery) != std::string::npos || type.find(searchQuery) != std::string::npos) {
        
            std::cout << creatures[i].ToString() << "\n";

        }
    
    }

    
    std::cout << "\n\n";


}

void DisplayMainMenu() {


    std::cout << "\n\nOptions:"
        
        "\n\t1. Print creatures"
        
        "\n\t2. Sort creatures"
        
        "\n\t3. Search creatures"
        
        "\n\t4. Quit\n\n";


}

void DisplaySortSubMenu() {

    std::cout << "\n\nSort Options:"
        
        "\n\t1. Name"
        
        "\n\t2. Type"
        
        "\n\t3. Health"

        "\n\t4. Strength"
        
        "\n\t5. None: Go back to outer menu\n\n";

}



//TestCases
//Input:

//TC1: Print function

//Output:


// Options:
//         1. Print creatures
//         2. Sort creatures
//         3. Search creatures
//         4. Quit

// 1


// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Centaur         | Animal          |         50 |        125 |
// | Kitty           | Animal          |         75 |        120 |
// | Walrus          | Animal          |        125 |        145 |
// | Elephant        | Animal          |         54 |         63 |
// | Tiger           | Animal          |         75 |        131 |
// | Squirrel        | Animal          |        119 |         52 |
// | Mouse           | Animal          |        121 |         89 |
// | Spider          | Animal          |        175 |         39 |
// | Lizard          | Animal          |        164 |        101 |
// | Unicorn         | Myth            |        205 |        227 |
// | Goat            | Animal          |        131 |        165 |
// | Rainman         | Human           |        121 |        177 |
// | Desert Scorcher | Human           |        167 |        125 |
// | Magic Caster    | Human           |        131 |        155 |
// | Honey Boo Boo   | Human           |        290 |         53 |
// | Spongebob       | Animal          |        303 |          5 |
// | Jimmy Neutron   | Human           |         85 |        305 |
// | Wolf            | Animal          |        173 |        219 |
// | Animal Pocher   | Human           |         75 |        201 |
// | Fanboy          | Human           |         91 |         35 |
// | Paimon          | Legend          |        205 |        370 |
// | Pikachu         | Animal          |         83 |        311 |
// | Peter Griffin   | Human           |         21 |        150 |
// | Veggietales     | Myth            |         10 |         15 |
// | Paw Patrol      | Animal          |        183 |         31 |
// -----------------------------------------------------------------



// Options:
//         1. Print creatures
//         2. Sort creatures
//         3. Search creatures
//         4. Quit

// 2


// Sort Options:
//         1. Name
//         2. Type
//         3. Health
//         4. Strength
//         5. None: Go back to outer menu

// 1


// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Wolf            | Animal          |        173 |        219 |
// | Walrus          | Animal          |        125 |        145 |
// | Veggietales     | Myth            |         10 |         15 |
// | Unicorn         | Myth            |        205 |        227 |
// | Tiger           | Animal          |         75 |        131 |
// | Squirrel        | Animal          |        119 |         52 |
// | Spongebob       | Animal          |        303 |          5 |
// | Spider          | Animal          |        175 |         39 |
// | Rainman         | Human           |        121 |        177 |
// | Pikachu         | Animal          |         83 |        311 |
// | Peter Griffin   | Human           |         21 |        150 |
// | Paw Patrol      | Animal          |        183 |         31 |
// | Paimon          | Legend          |        205 |        370 |
// | Mouse           | Animal          |        121 |         89 |
// | Magic Caster    | Human           |        131 |        155 |
// | Lizard          | Animal          |        164 |        101 |
// | Kitty           | Animal          |         75 |        120 |
// | Jimmy Neutron   | Human           |         85 |        305 |
// | Honey Boo Boo   | Human           |        290 |         53 |
// | Goat            | Animal          |        131 |        165 |
// | Fanboy          | Human           |         91 |         35 |
// | Elephant        | Animal          |         54 |         63 |
// | Desert Scorcher | Human           |        167 |        125 |
// | Centaur         | Animal          |         50 |        125 |
// | Animal Pocher   | Human           |         75 |        201 |
// -----------------------------------------------------------------



// Sort Options:
//         1. Name
//         2. Type
//         3. Health
//         4. Strength
//         5. None: Go back to outer menu

// 2


// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Veggietales     | Myth            |         10 |         15 |
// | Unicorn         | Myth            |        205 |        227 |
// | Paimon          | Legend          |        205 |        370 |
// | Rainman         | Human           |        121 |        177 |
// | Peter Griffin   | Human           |         21 |        150 |
// | Magic Caster    | Human           |        131 |        155 |
// | Jimmy Neutron   | Human           |         85 |        305 |
// | Honey Boo Boo   | Human           |        290 |         53 |
// | Fanboy          | Human           |         91 |         35 |
// | Desert Scorcher | Human           |        167 |        125 |
// | Animal Pocher   | Human           |         75 |        201 |
// | Wolf            | Animal          |        173 |        219 |
// | Walrus          | Animal          |        125 |        145 |
// | Tiger           | Animal          |         75 |        131 |
// | Squirrel        | Animal          |        119 |         52 |
// | Spongebob       | Animal          |        303 |          5 |
// | Spider          | Animal          |        175 |         39 |
// | Pikachu         | Animal          |         83 |        311 |
// | Paw Patrol      | Animal          |        183 |         31 |
// | Mouse           | Animal          |        121 |         89 |
// | Lizard          | Animal          |        164 |        101 |
// | Kitty           | Animal          |         75 |        120 |
// | Goat            | Animal          |        131 |        165 |
// | Elephant        | Animal          |         54 |         63 |
// | Centaur         | Animal          |         50 |        125 |
// -----------------------------------------------------------------



// Sort Options:
//         1. Name
//         2. Type
//         3. Health
//         4. Strength
//         5. None: Go back to outer menu

// 3


// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Spongebob       | Animal          |        303 |          5 |
// | Honey Boo Boo   | Human           |        290 |         53 |
// | Unicorn         | Myth            |        205 |        227 |
// | Paimon          | Legend          |        205 |        370 |
// | Paw Patrol      | Animal          |        183 |         31 |
// | Spider          | Animal          |        175 |         39 |
// | Wolf            | Animal          |        173 |        219 |
// | Desert Scorcher | Human           |        167 |        125 |
// | Lizard          | Animal          |        164 |        101 |
// | Magic Caster    | Human           |        131 |        155 |
// | Goat            | Animal          |        131 |        165 |
// | Walrus          | Animal          |        125 |        145 |
// | Rainman         | Human           |        121 |        177 |
// | Mouse           | Animal          |        121 |         89 |
// | Squirrel        | Animal          |        119 |         52 |
// | Fanboy          | Human           |         91 |         35 |
// | Jimmy Neutron   | Human           |         85 |        305 |
// | Pikachu         | Animal          |         83 |        311 |
// | Animal Pocher   | Human           |         75 |        201 |
// | Tiger           | Animal          |         75 |        131 |
// | Kitty           | Animal          |         75 |        120 |
// | Elephant        | Animal          |         54 |         63 |
// | Centaur         | Animal          |         50 |        125 |
// | Peter Griffin   | Human           |         21 |        150 |
// | Veggietales     | Myth            |         10 |         15 |
// -----------------------------------------------------------------



// Sort Options:
//         1. Name
//         2. Type
//         3. Health
//         4. Strength
//         5. None: Go back to outer menu

// 4


// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Paimon          | Legend          |        205 |        370 |
// | Pikachu         | Animal          |         83 |        311 |
// | Jimmy Neutron   | Human           |         85 |        305 |
// | Unicorn         | Myth            |        205 |        227 |
// | Wolf            | Animal          |        173 |        219 |
// | Animal Pocher   | Human           |         75 |        201 |
// | Rainman         | Human           |        121 |        177 |
// | Goat            | Animal          |        131 |        165 |
// | Magic Caster    | Human           |        131 |        155 |
// | Peter Griffin   | Human           |         21 |        150 |
// | Walrus          | Animal          |        125 |        145 |
// | Tiger           | Animal          |         75 |        131 |
// | Desert Scorcher | Human           |        167 |        125 |
// | Centaur         | Animal          |         50 |        125 |
// | Kitty           | Animal          |         75 |        120 |
// | Lizard          | Animal          |        164 |        101 |
// | Mouse           | Animal          |        121 |         89 |
// | Elephant        | Animal          |         54 |         63 |
// | Honey Boo Boo   | Human           |        290 |         53 |
// | Squirrel        | Animal          |        119 |         52 |
// | Spider          | Animal          |        175 |         39 |
// | Fanboy          | Human           |         91 |         35 |
// | Paw Patrol      | Animal          |        183 |         31 |
// | Veggietales     | Myth            |         10 |         15 |
// | Spongebob       | Animal          |        303 |          5 |
// -----------------------------------------------------------------



// Sort Options:
//         1. Name
//         2. Type
//         3. Health
//         4. Strength
//         5. None: Go back to outer menu

// 5
// Leaving sub-menu



// Options:
//         1. Print creatures
//         2. Sort creatures
//         3. Search creatures
//         4. Quit

// 3

// Enter search query:

// Veggieta

// Entries Found:



// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Veggietales     | Myth            |         10 |         15 |




// Options:
//         1. Print creatures
//         2. Sort creatures
//         3. Search creatures
//         4. Quit

// 3

// Enter search query:

// VEGGIe

// Entries Found:



// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Veggietales     | Myth            |         10 |         15 |




// Options:
//         1. Print creatures
//         2. Sort creatures
//         3. Search creatures
//         4. Quit

// 3

// Enter search query:

// PAW

// Entries Found:



// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Paw Patrol      | Animal          |        183 |         31 |




// Options:
//         1. Print creatures
//         2. Sort creatures
//         3. Search creatures
//         4. Quit

// 3

// Enter search query:

// patr

// Entries Found:



// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Paw Patrol      | Animal          |        183 |         31 |




// Options:
//         1. Print creatures
//         2. Sort creatures
//         3. Search creatures
//         4. Quit

// 3

// Enter search query:

// MyTH

// Entries Found:



// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Unicorn         | Myth            |        205 |        227 |
// | Veggietales     | Myth            |         10 |         15 |




// Options:
//         1. Print creatures
//         2. Sort creatures
//         3. Search creatures
//         4. Quit

// 3

// Enter search query:

// y

// Entries Found:



// | Name            | Type            | Health     | Strength   |
// -----------------------------------------------------------------
// | Kitty           | Animal          |         75 |        120 |
// | Unicorn         | Myth            |        205 |        227 |
// | Honey Boo Boo   | Human           |        290 |         53 |
// | Jimmy Neutron   | Human           |         85 |        305 |
// | Fanboy          | Human           |         91 |         35 |
// | Veggietales     | Myth            |         10 |         15 |




// Options:
//         1. Print creatures
//         2. Sort creatures
//         3. Search creatures
//         4. Quit

// 4
// Program now closed.
