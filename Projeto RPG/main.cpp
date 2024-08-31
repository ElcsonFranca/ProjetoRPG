#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

///Constantes para definir as cores de texto
const char* T_ROSA = "\033[38;5;205m";
const char* T_VERMELHO = "\033[31m";
const char* T_CIANO = "\033[36m";
const char* RESET_COR = "\033[0m"; ///Resetar a cor para o padrão
const char* T_MARROM = "\033[33;2m";
const char* T_LARANJA = "\033[38;5;202m";
const char* T_VERDE = "\033[32m";
const char* T_VERDE_C = "\033[92m";
const char* T_VERMELHO_C = "\033[91m";
const char* T_AZUL_C = "\033[94m";
const char* T_AMARELO = "\033[33m";
const char* T_AZUL_E = "\033[34m";
const char* T_ROXO = "\033[35m";
const char* T_CIANO_C = "\033[96m";
const char* T_CINZA = "\033[90m"; // Grey text


struct ArmaCorpoACorpo {
    string nome;
    string dano;
    int precisao;
    float velocidade;
    int peso;
    int critico;
    int manunseio;  // One or two-handed
    bool registrado;
    string descricao;
    bool impureza;
};

struct ArmaLongaDistancia {
    string nome;
    string dano;
    int precisao;
    float velocidade;
    int peso;
    int critico;
    int manunseio;  // One or two-handed
    bool registrado;
    string descricao;
    bool impureza;
};

struct ArmaMagica {
    string nome;
    string dano;
    int precisao;
    float TempoDeCanalizacao;
    int custo;
    int slots;
    bool registrado;
    string descricao;
    bool impureza;
};

struct Pergaminho {
    string nome;
    int ValorDeArea;
    string descricao;
};

struct Pocao {
    string nome;
    int ValorDeArea;
    string descricao;
};


vector<Pergaminho> readPergaminhosFromFile(const string& filename) {
    vector<Pergaminho> pergaminhos;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Could not open the file!" << endl;
        return pergaminhos;
    }

    string line;
    // Skip the header line
    getline(file, line);

    while (getline(file, line)) {
        Pergaminho pergaminho;
        stringstream ss(line);

        getline(ss, pergaminho.nome, ',');  // Read the name

        string ValorDeArea;
        getline(ss, ValorDeArea, ',');  // Read the ValorDeArea
        pergaminho.ValorDeArea = stoi(ValorDeArea);

        // Read the rest of the line as the description, handling possible commas
        getline(ss, pergaminho.descricao);

        // Remove any surrounding quotes from the description, if they exist
        if (pergaminho.descricao.front() == '"') {
            pergaminho.descricao.erase(0, 1);  // Remove the first quote
        }
        if (pergaminho.descricao.back() == '"') {
            pergaminho.descricao.pop_back();  // Remove the last quote
        }

        pergaminhos.push_back(pergaminho);
    }

    file.close();
    return pergaminhos;
}


string replacePlaceholder(const string& descricao, const string& placeholder, const string& value) {
    string result = descricao;
    size_t pos = result.find(placeholder);
    if (pos != string::npos) {
        result.replace(pos, placeholder.length(), value);
    }
    return result;
}


// Chances de raridades dos baús.
string determinaRaridade(int randValue, int Bau, int& VComum, int& VIncomum, int& VRaro, int& VEpico, int& VLendario, int& VMitico) {
    //Baú de madeira quebrado
    if (Bau == 1) {
        if (randValue <= 40) {
            return "Comum";
        } else if (randValue <= 70) {
            return "Incomum";
        } else if (randValue <= 95) {
            return "Raro";
        } else if (randValue <= 99) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }
          //Baú de madeira
          if (Bau == 2) {
        if (randValue <= 32) {
            return "Comum";
        } else if (randValue <= 62) {
            return "Incomum";
        } else if (randValue <= 90) {
            return "Raro";
        } else if (randValue <= 97) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }
         //Baú de Ferro
         if (Bau == 3) {
        if (randValue <= 30) {
            return "Comum";
        } else if (randValue <= 66) {
            return "Incomum";
        } else if (randValue <= 88) {
            return "Raro";
        } else if (randValue <= 96) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }

          //Baú de Ouro
         if (Bau == 4) {
        if (randValue <= 25) {
            return "Comum";
        } else if (randValue <= 60) {
            return "Incomum";
        } else if (randValue <= 80) {
            return "Raro";
        } else if (randValue <= 94) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }

     //Baú de Enorme
         if (Bau == 5) {
        if (randValue <= 32) {
            return "Comum";
        } else if (randValue <= 62) {
            return "Incomum";
        } else if (randValue <= 90) {
            return "Raro";
        } else if (randValue <= 98) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }
           //Baú de Balanceado
         if (Bau == 6) {
        if (randValue <= 20) {
            return "Comum";
        } else if (randValue <= 40) {
            return "Incomum";
        } else if (randValue <= 60) {
            return "Raro";
        } else if (randValue <= 80) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }
           //Baú de Esmeralda
         if (Bau == 7) {
        if (randValue <= 20) {
            return "Comum";
        } else if (randValue <= 60) {
            return "Incomum";
        } else if (randValue <= 80) {
            return "Raro";
        } else if (randValue <= 90) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }

          //Baú Estranho
         if (Bau == 8) {
        if (randValue <= 30) {
            return "Comum";
        } else if (randValue <= 45) {
            return "Incomum";
        } else if (randValue <= 55) {
            return "Raro";
        } else if (randValue <= 70) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }

    //Baú Excepcional
         if (Bau == 9) {
        if (randValue <= 1) {
            return "Comum";
        } else if (randValue <= 5) {
            return "Incomum";
        } else if (randValue <= 30) {
            return "Raro";
        } else if (randValue <= 60) {
            return "Épico";
        } else if (randValue <= 99) {
            return "Lendário";
        }else{
            return "Mítico";
        }
    }

    //Baú Apex
         if (Bau == 10) {
        if (randValue <= 40) {
            return "Comum";
        } else if (randValue <= 68) {
            return "Raro";
        } else if (randValue <= 93) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }

    //Baú de Safira
         if (Bau == 11) {
        if (randValue <= 10) {
            return "Comum";
        } else if (randValue <= 30) {
            return "Incomum";
        } else if (randValue <= 70) {
            return "Raro";
        } else if (randValue <= 90) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }

    //Baú de Ametista
         if (Bau == 12) {
        if (randValue <= 10) {
            return "Comum";
        } else if (randValue <= 20) {
            return "Incomum";
        } else if (randValue <= 40) {
            return "Raro";
        } else if (randValue <= 80) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }

    //Baú de Topázio
         if (Bau == 13) {
        if (randValue <= 20) {
            return "Comum";
        } else if (randValue <= 30) {
            return "Incomum";
        } else if (randValue <= 40) {
            return "Raro";
        } else if (randValue <= 60) {
            return "Épico";
        } else {
            return "Lendário";
        }
    }

    //Baú de Chefe
         if (Bau == 14) {
        if (randValue <= 40) {
            return "Raro";
        } else if (randValue <= 70) {
            return "Épico";
        } else if (randValue <= 95) {
            return "Lendário";
        } else {
            return "Mítico";
        }
    }

     //Baú da Injustiça
    if (Bau == 15) {
        if (randValue <= 1) {
            return "Lendário";
        } else if (randValue <= 5) {
            return "Épico";
        } else if (randValue <= 30) {
            return "Raro";
        } else if (randValue <= 60) {
            return "Incomum";
        } else {
            return "Comum";
        }
    }

     //Baú Customizado
    if (Bau == 16) {
        if (randValue <= VComum) {
            return "Comum";
        } else if (randValue <= VComum + VIncomum) {
            return "Incomum";
        } else if (randValue <= VComum + VIncomum + VRaro) {
            return "Raro";
        } else if (randValue <= VComum + VIncomum + VRaro + VEpico) {
            return "Épico";
         } else if (randValue <= VComum + VIncomum + VRaro + VEpico + VLendario) {
            return "Lendário";
        } else {
            return "Mítico";
        }
    }


}

// Definição do tipo do item
string determinaItemTipo(int TipoFiltro) {
    vector<string> itemTypes;

    if (TipoFiltro == 1){
        itemTypes = {"Arma"};
    }
    else if (TipoFiltro == 2){
        itemTypes = {"Armadura"};
    }
     else if (TipoFiltro == 3){
        itemTypes = {"Poção"};
    }
     else if (TipoFiltro == 4){
        itemTypes = {"Pergaminho"};
    }
     else if (TipoFiltro == 5){
        itemTypes = {"Acessório"};
    }
     else if (TipoFiltro == 6){
        itemTypes = {"Miscelânia"};
    }
     else {
     // Seleciona o tipo de item aleatoriamente
    itemTypes = {"Arma", "Armadura", "Poção", "Pergaminho", "Acessório", "Miscelânia"};
     }
     // Executa a Seleção de tipo de item aleatorio
    int index = rand() % itemTypes.size();
    return itemTypes[index];
}

// Definição do tipo da arma
string determinaArmaTipo(int TipoArmaFiltro) {
    vector<string> TipoArma;

    if (TipoArmaFiltro == 1){
        TipoArma = {"Corpo-a-Corpo"};
    }
    else if (TipoArmaFiltro == 2){
        TipoArma = {"Longa Distância"};
    }
     else if (TipoArmaFiltro == 3){
        TipoArma = {"Mágica"};
    }
     else if (TipoArmaFiltro == 4){
        TipoArma = {"Musical"};
    }else {
     // Seleciona o tipo de arma aleatoriamente
    TipoArma = {"Corpo-a-Corpo", "Longa Distância", "Mágica", "Musical"};
     }
     // Executa a Seleção de tipo de item aleatorio
    int index = rand() % TipoArma.size();
    return TipoArma[index];
}

// Define as características do bau customizado
void DefBauCustom(int& MinCustom, int& MaxCustom, int& ValorRestante, char& Escolha, int& VComum, int& VIncomum, int& VRaro, int& VEpico, int& VLendario, int& VMitico) {

    cout << "Insira a quantidade de itens:" << endl;
    cout << "Mínimo: ";
    cin >> MinCustom;
    cout << "Máximo: ";
    cin >> MaxCustom;
    MaxCustom + 1;

      if (MinCustom > 0){
      MaxCustom - MinCustom;
      }

while (Escolha != 'n' && Escolha != 'N'){
   ValorRestante = 100;

   cout << "Insira a chance de itens " << T_CINZA << "Comums" << RESET_COR << " em %: ";
   cin >> VComum;
   ValorRestante -= VComum;
   cout << "Valores Restantes (Insira valores menores que esse): " << T_VERMELHO << ValorRestante << RESET_COR << endl;

 if (ValorRestante > 0){
   cout << "Insira a chance de itens " << T_VERDE_C << "Incomums" << RESET_COR << " em %: ";
   cin >> VIncomum;
   ValorRestante -= VIncomum;
   cout << "Valores Restantes (Insira valores menores que esse): " << T_VERMELHO << ValorRestante << RESET_COR << endl;
 }
  if (ValorRestante > 0){
   cout << "Insira a chance de itens " << T_AZUL_C << "Raros" << RESET_COR << " em %: ";
   cin >> VRaro;
   ValorRestante -= VRaro;
   cout << "Valores Restantes (Insira valores menores que esse): " << T_VERMELHO << ValorRestante << RESET_COR << endl;
 }
  if (ValorRestante > 0){
   cout << "Insira a chance de itens " << T_ROXO << "Épicos" << RESET_COR << " em %: ";
   cin >> VEpico;
   ValorRestante -= VEpico;
   cout << "Valores Restantes (Insira valores menores que esse): " << T_VERMELHO << ValorRestante << RESET_COR << endl;
 }
  if (ValorRestante > 0){
   cout << "Insira a chance de itens " << T_AMARELO << "Lendários" << RESET_COR << " em % (Provavelmente " << ValorRestante << "): ";
   cin >> VLendario;
   ValorRestante -= VLendario;
   cout << "Valores Restantes (Insira valores menores que esse): " << T_VERMELHO << ValorRestante << RESET_COR << endl;
 }
  if (ValorRestante > 0){
   cout << "Insira a chance de itens " << T_ROSA << "Míticos" << RESET_COR << " em % (Provavelmente " << ValorRestante << "): ";
   cin >> VMitico;
   ValorRestante -= VMitico;
   cout << "Valores Restantes (É pra ser 0): " << T_VERMELHO << ValorRestante << RESET_COR << endl;
  }
   cout << endl;
   cout << "Essas são as chances de raridade do Baú: " << endl;

   cout << T_CINZA << "Comum: ";
  if (VComum > 1){
   cout << T_VERMELHO_C << "1-" << VComum << RESET_COR << endl;
}else if (VComum == 1 || VComum == 0){
   cout << T_VERMELHO_C << VComum << "-" << VComum << RESET_COR << endl;
}

if (VIncomum > 0){
   cout << T_VERDE_C << "Incomum: ";
   if (VIncomum >= 1){
   cout << T_VERMELHO_C << VComum + 1 << "-" << VComum + VIncomum << RESET_COR << endl;
   } else if (VIncomum == 0){
   cout << T_VERMELHO_C << VIncomum << RESET_COR << endl;
   }
}

if (VRaro > 0){
   cout << T_AZUL_C << "Raro: ";
   if (VRaro >= 1){
   cout << T_VERMELHO_C << VComum + VIncomum + 1 << "-" << VComum + VIncomum + VRaro << RESET_COR << endl;
   } else if (VRaro == 0){
   cout << T_VERMELHO_C << VRaro << RESET_COR << endl;
   }
}

if (VEpico > 0){
   cout << T_ROXO << "Épico: ";
   if (VEpico >= 1){
   cout << T_VERMELHO_C << VComum + VIncomum + VRaro + 1 << "-" << VComum + VIncomum + VRaro + VEpico << RESET_COR << endl;
   } else if (VEpico == 0){
   cout << T_VERMELHO_C << VEpico << RESET_COR << endl;
   }
}

if (VLendario > 0){
   cout << T_AMARELO << "Lendário: ";
   if (VLendario >= 1){
   cout << T_VERMELHO_C << VComum + VIncomum + VRaro + VEpico + 1 << "-" << VComum + VIncomum + VRaro + VEpico + VLendario << RESET_COR << endl;
   } else if (VLendario == 0){
   cout << T_VERMELHO_C << VLendario << RESET_COR << endl;
   }
}

if (VMitico > 0){
   cout << T_ROSA << "Mítico: " << RESET_COR;
   if (VMitico >= 1){
   cout << T_VERMELHO_C << VComum + VIncomum + VRaro + VEpico + VLendario + 1 << "-" << VComum + VIncomum + VRaro + VEpico + VLendario + VMitico << RESET_COR << endl;
   } else if (VMitico == 0){
   cout << T_VERMELHO_C << VMitico << RESET_COR << endl;
   }
}

   cout << endl;
   cout << "Deseja Refazer? (S)(N): ";
   cout << endl;
   cin >> Escolha;
   system("cls");
  }


}

 //Gera a quantidade de itens para o bau desejado
void GeraQtdItens (int& Bau, int& numItems, int& sorte, int& MinCustom, int& MaxCustom){

    if (Bau == 1){
    numItems = rand() % 4; // Seleciona itens de 0 a 3.
    }
    else if (Bau == 2){
    numItems = rand() % 5; // Seleciona itens de 0 a 4.
    }
    else if (Bau == 3){
    numItems = rand() % 6; // Seleciona itens de 0 a 5.
    }
    else if (Bau == 4){
    numItems = rand() % 6 + 1; // Seleciona itens de 1 a 6.
    }
    else if (Bau == 5){
    numItems = rand() % 10 + 1; // Seleciona itens de 1 a 10.
    }
    else if (Bau == 6){
    numItems = rand() % 5 + 1; // Seleciona itens de 1 a 5.
    }
    else if (Bau == 7){
    numItems = rand() % 2 + 1; // Seleciona itens de 1 a 2.
    }
    else if (Bau == 8){
    numItems = rand() % 5; // Seleciona itens de 0 a 4.
    }
    else if (Bau == 9){
    numItems = rand() % 6 + 4; // Seleciona itens de 4 a 9.
    }
    else if (Bau == 10){
    numItems = 3; // Seleciona 3 itens.
    }
    else if (Bau == 11){
    numItems = rand() % 3 + 1; // Seleciona itens de 1 a 3.
    }
    else if (Bau == 12){
    numItems = rand() % 4 + 1; // Seleciona itens de 1 a 4.
    }
    else if (Bau == 13){
    numItems = rand() % 5 + 1; // Seleciona itens de 1 a 5.
    }
    else if (Bau == 14){
    numItems = 3; // Seleciona 3 itens.
    }
    else if (Bau == 15){
    numItems = rand() % 4; // Seleciona 0 a 3 itens.
    }
     else if (Bau == 16){
     if (MaxCustom == MinCustom){
        numItems = MinCustom; // Se for um valor fixo
      }else{
       numItems = (rand() % MaxCustom) + MinCustom; // Seleciona numero de itens definido pelo usuário.
      }

    }
    else {
        cout << "Valor Inválido." << endl;
    }


    //Manipulação na quantidade de itens pela sorte.

  if (Bau != 15){

    if (sorte >= 100){
    numItems = numItems + 4;
    }
    else if (sorte >= 75){
    numItems = numItems + 3;
    }
    else if (sorte >= 50){
    numItems = numItems + 2;
    }
    else if (sorte >= 25){
    numItems = numItems + 1;
    }

    //Caso a sorte seja negativa
    if (sorte <= -100){
    numItems = numItems - 4;
    }
    else if (sorte <= -75){
    numItems = numItems - 3;
    }
    else if (sorte <= -50){
    numItems = numItems - 2;
    }
    else if (sorte <= -25){
    numItems = numItems - 1;
    }
  }

//Caso o bau seja o da injustiça
    else if (Bau == 15){

      if (sorte >= 100){
      numItems = numItems - 8;
      }
       else if (sorte >= 75){
       numItems = numItems - 6;
       }
        else if (sorte >= 50){
        numItems = numItems - 4;
        }
         else if (sorte >= 25){
         numItems = numItems - 2;
         }

    if (sorte <= -100){
    numItems = numItems + 8;
    }
     else if (sorte <= -75){
     numItems = numItems + 6;
     }
      else if (sorte <= -50){
      numItems = numItems + 4;
      }
       else if (sorte <= -25){
       numItems = numItems + 2;
       }

    }

}

string IdDeBau(int& Bau){

switch (Bau) {
  case 1:
    return "Baú de Madeira Quebrado";
    break;
  case 2:
    return "Baú de Madeira";
    break;
  case 3:
    return "Baú de Ferro";
    break;
  case 4:
    return "Baú de Ouro";
    break;
  case 5:
    return "Baú de Madeira Grande";
    break;
  case 6:
    return "Baú Balanceado";
    break;
  case 7:
    return "Baú de Esmeralda";
    break;
  case 8:
    return "Baú de Estranho";
    break;
  case 9:
    return "Baú de Excepcional";
    break;
  case 10:
    return "Baú Apex";
    break;
  case 11:
    return "Baú de Safira";
    break;
  case 12:
    return "Baú de Ametista";
    break;
  case 13:
    return "Baú de Topázio";
    break;
  case 14:
    return "Baú de Chefe";
    break;
  case 15:
    return "Baú da Injustiça";
    break;
  case 16:
    return "Baú de Customizado";
    break;
}


    cout << "1. Baú de Madeira Quebrado" << endl;
    cout << "2. Baú de Madeira" << endl;
    cout << "3. Baú de Ferro" << endl;
    cout << "4. Baú de Ouro" << endl;
    cout << "5. Baú de Madeira Grande" << endl;
    cout << "6. Baú Balanceado" << endl;
    cout << "7. Baú de Esmeralda" << endl;
    cout << "8. Baú Estranho" << endl;
    cout << "9. Baú Excepcional" << endl;
    cout << "10. Baú Apex" << endl;
    cout << "11. Baú de Safira" << endl;
    cout << "12. Baú de Ametista" << endl;
    cout << "13. Baú de Topázio" << endl;
    cout << "14. Baú de Chefe" << endl;
    cout << "15. Baú da Injustiça" << endl;
    cout << "16. Baú Customizado" << endl;

}

void DisplayDasEscolhas (int& sorte, int& area, char& EscolhaFiltro, int& TipoFiltro, int& TipoArmaFiltro, int& Bau){
system("cls");
cout << "Sorte: " << sorte;
cout << ", Area: " << area;
cout << ", Filtro?: ";
  if (EscolhaFiltro == 's' || EscolhaFiltro == 'S'){
   cout << "Sim";
   cout << ", Tipo do Filtro: " << determinaItemTipo(TipoFiltro);
   if (TipoFiltro == 1){cout << ", Classe da Arma: " << determinaArmaTipo(TipoArmaFiltro);}
  }else{cout << "Não";}
cout << ", Baú: " << Bau << " (" << IdDeBau(Bau) << ")" << endl;
cout << endl;
}

void DiretorioDeLista(vector<Pergaminho>& pergaminhos, const string& rarity, const string& itemType, const string& ArmaTipo) {
    if (rarity == "Comum") {
        if (itemType == "Pergaminho") pergaminhos = readPergaminhosFromFile("RPG - Pergaminhos/Pergaminhos Comuns.csv");
        if (itemType == "Poção"){}///Em desenvolvimento
        if (itemType == "Miscelânea"){}///Em desenvolvimento
        if (itemType == "Arma"){}///Em desenvolvimento
        if (itemType == "Acessório"){}///Em desenvolvimento
        if (itemType == "Armadura"){}///Em desenvolvimento
    }
    if (rarity == "Incomum") {
        if (itemType == "Pergaminho") pergaminhos = readPergaminhosFromFile("RPG - Pergaminhos/Pergaminhos Incomuns.csv");
        if (itemType == "Poção"){}///Em desenvolvimento
        if (itemType == "Miscelânea"){}///Em desenvolvimento
        if (itemType == "Arma"){}///Em desenvolvimento
        if (itemType == "Acessório"){}///Em desenvolvimento
        if (itemType == "Armadura"){}///Em desenvolvimento
    }
    if (rarity == "Raro") {
        if (itemType == "Pergaminho") pergaminhos = readPergaminhosFromFile("RPG - Pergaminhos/Pergaminhos Raros.csv");
        if (itemType == "Poção"){}///Em desenvolvimento
        if (itemType == "Miscelânea"){}///Em desenvolvimento
        if (itemType == "Arma"){}///Em desenvolvimento
        if (itemType == "Acessório"){}///Em desenvolvimento
        if (itemType == "Armadura"){}///Em desenvolvimento
    }
    if (rarity == "Épico") {
        if (itemType == "Pergaminho") pergaminhos = readPergaminhosFromFile("RPG - Pergaminhos/Pergaminhos Épicos.csv");
        if (itemType == "Poção"){}///Em desenvolvimento
        if (itemType == "Miscelânea"){}///Em desenvolvimento
        if (itemType == "Arma"){}///Em desenvolvimento
        if (itemType == "Acessório"){}///Em desenvolvimento
        if (itemType == "Armadura"){}///Em desenvolvimento
    }
    if (rarity == "Lendários") {
        if (itemType == "Pergaminho") pergaminhos = readPergaminhosFromFile("RPG - Pergaminhos/Pergaminhos Lendários.csv");
        if (itemType == "Poção"){}///Em desenvolvimento
        if (itemType == "Miscelânea"){}///Em desenvolvimento
        if (itemType == "Arma"){}///Em desenvolvimento
        if (itemType == "Acessório"){}///Em desenvolvimento
        if (itemType == "Armadura"){}///Em desenvolvimento
    }
    if (rarity == "Mítico") {
        if (itemType == "Pergaminho") pergaminhos = readPergaminhosFromFile("RPG - Pergaminhos/Pergaminhos Míticos.csv");
        if (itemType == "Poção"){}///Em desenvolvimento
        if (itemType == "Miscelânea"){}///Em desenvolvimento
        if (itemType == "Arma"){}///Em desenvolvimento
        if (itemType == "Acessório"){}///Em desenvolvimento
        if (itemType == "Armadura"){}///Em desenvolvimento
    }

}

int main() {
    setlocale(LC_ALL, "portuguese");

    unsigned seed = time(0);

    srand(seed);

    int sorte;
    int area;

    char EscolhaFiltro;
    int TipoFiltro;
    int TipoArmaFiltro;

    cout << "Insira a Sorte. (-100 a 100 para resultados 'notáveis' e 'realistas')" << endl;
    cin >> sorte;
    cout << "Insira a Área. (1 a 5)(Inserir valores fora dessa margem irá gerar itens com atributos ridículos...)" << endl;
    cin >> area;
    cout << "Filtrar tipos de itens? (s/n)" << endl;
    cin >> EscolhaFiltro;

    if ((EscolhaFiltro == 's') || (EscolhaFiltro == 'S')){
    cout << "Qual item deve ser filtrado?" << endl;
    cout << "1. Arma." << endl;
    cout << "2. Armadura." << endl;
    cout << "3. Poção." << endl;
    cout << "4. Pergaminho." << endl;
    cout << "5. Acessório." << endl;
    cout << "6. Miscelânia." << endl;
    cin >> TipoFiltro;

    if (TipoFiltro == 1){
    cout << "Filtrar tipos de armas? (s/n)" << endl;
    cin >> EscolhaFiltro;

        if (TipoFiltro == 1 && EscolhaFiltro == 's'){
        cout << "Qual arma deve ser filtrada?" << endl;
        cout << "1. Corpo-a-Corpo." << endl;
        cout << "2. Longa Distância." << endl;
        cout << "3. Mágica." << endl;
        cout << "4. Musical." << endl;
        cin >> TipoArmaFiltro;
        }
    }

    }

    cout << "Escolha o Baú:" << endl;
    cout << "1. Baú de Madeira Quebrado" << endl;
    cout << "2. Baú de Madeira" << endl;
    cout << "3. Baú de Ferro" << endl;
    cout << "4. Baú de Ouro" << endl;
    cout << "5. Baú de Madeira Grande" << endl;
    cout << "6. Baú Balanceado" << endl;
    cout << "7. Baú de Esmeralda" << endl;
    cout << "8. Baú Estranho" << endl;
    cout << "9. Baú Excepcional" << endl;
    cout << "10. Baú Apex" << endl;
    cout << "11. Baú de Safira" << endl;
    cout << "12. Baú de Ametista" << endl;
    cout << "13. Baú de Topázio" << endl;
    cout << "14. Baú de Chefe" << endl;
    cout << "15. Baú da Injustiça" << endl;
    cout << "16. Baú Customizado" << endl;

    int Bau;
    cin >> Bau;

    int MinCustom, MaxCustom;
    int VComum = 0, VIncomum = 0, VRaro = 0, VEpico = 0, VLendario = 0, VMitico = 0;
    int ValorRestante = 100;
    char Escolha;

    int numItems;

if (Bau == 16){
    DefBauCustom(MinCustom, MaxCustom, ValorRestante, Escolha, VComum, VIncomum, VRaro, VEpico, VLendario, VMitico);
}



    //Gera a quantidade de itens para o bau customizado desejado
    GeraQtdItens(Bau, numItems, sorte, MinCustom, MaxCustom);

    DisplayDasEscolhas(sorte, area, EscolhaFiltro, TipoFiltro, TipoArmaFiltro, Bau);



    ///Resultado final

    cout << "Loot do Baú (" << numItems << " itens):" << endl;

    for (int i = 0; i < numItems; ++i) {
        int randValue = rand() % 100 + 1 + sorte; // Adicona sorte no valor aleatorio
        int ogrand = randValue - sorte; // mostra o valor original

        string rarity = determinaRaridade(randValue, Bau, VComum, VIncomum, VRaro, VEpico, VLendario, VMitico);
        string itemType = determinaItemTipo(TipoFiltro);
        string ArmaTipo = determinaArmaTipo(TipoArmaFiltro);

        cout << "Item " << (i + 1) << ": Raridade - ";
        if (rarity == "Incomum"){ cout << T_VERDE_C << rarity << RESET_COR;}
        else if (rarity == "Raro"){ cout << T_AZUL_C << rarity << RESET_COR;}
        else if (rarity == "Épico"){ cout << T_ROXO << rarity << RESET_COR;}
        else if (rarity == "Lendário"){ cout << T_AMARELO << rarity << RESET_COR;}
        else if (rarity == "Mítico"){ cout << T_ROSA << rarity << RESET_COR;}
        else {cout << T_CINZA << rarity << RESET_COR;}
        cout << ", Tipo - " << itemType;
        if (itemType == "Arma") cout << " " << ArmaTipo << endl;
        else cout << endl;

         if (itemType == "Pergaminho") {
            vector<Pergaminho> pergaminhos;
            DiretorioDeLista(pergaminhos, rarity, itemType, ArmaTipo);

            if (!pergaminhos.empty()) {
                int pergaminhoIndex = rand() % pergaminhos.size();
                const Pergaminho& selectedPergaminho = pergaminhos[pergaminhoIndex];

                int totalAreaValue = selectedPergaminho.ValorDeArea * area;
                string finalDescription = replacePlaceholder(selectedPergaminho.descricao, "[ValorDeArea]", to_string(totalAreaValue));

                cout << selectedPergaminho.nome << endl;
                cout << finalDescription << endl;
            } else {
                cout << "Nenhum pergaminho disponível para esta combinação." << endl;
            }
        }

        cout << "Valor Original (Sem sorte): " << ogrand << endl;
        cout << "Valor Modificado (Com sorte): " << randValue << endl;
        cout << endl;
    }

    return 0;
}
