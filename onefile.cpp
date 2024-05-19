//    Judul: ASCII BIRD
//    
//    Kelas : (X-9)
//    
//    Anggota Kelompok
//    - I Putu Bagus Artha Sanjaya (16)
//    - Sean Filbert Pangawijaya (37)
//    - Ni Komang Nethania Ariyani(31)

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>
#include <conio.h>
#include <random>


namespace Tampilan {

  void Clear() {
    system("cls"); //windows
  }

  class Layar {
    private:
      std::vector<std::string> kanvas;
      char background;
      int lebar;
      int tinggi;
    public:
      //constructor
      Layar(int lebar, int tinggi, char background): lebar(lebar), tinggi(tinggi), background(background) {
        std::string baris = "";

        for (int x = 0; x < this->lebar; x++) {
          baris.push_back(background);
        }
        
        for (int y = 0; y < this->tinggi; y++) {
          this->kanvas.push_back(baris);
        }
      }

      //getter
      int CenterY() {
        return (this->tinggi+1)/2;
      }

      int CenterX() {
        return (this->lebar+1)/2;
      }

      int GetTinggi() {
        return this->tinggi;
      }
      
      int GetLebar() {
        return this->lebar;
      }

      void print() {
        for (std::string baris: this->kanvas) {
          std::cout << baris << std::endl;
        }
      }

      //setter
      void Clear() {
        for (int y = 0; y < this->tinggi; y++) {
          for (int x = 0; x < this->lebar; x++) {
            this->kanvas.at(y).at(x) = this->background;
          }
        }
      }
      void ganti(int x, int y, char chara) {
        this->kanvas.at(y).at(x) = chara;
      }
  };
}

namespace Game {
  class Burung {
    private:
    char model;
    int tinggi_lompat;
    int gravitasi;
    int x;
    int y;
    int score;
    int score_inc;
    bool die = false;

    public:

    int GetScore() {
      return this->score;
    }

    void AddScore() {
      this->score += this->score_inc;
    }

    int GetX() {
      return this->x;
    }

    int GetY() {
      return this->y;
    }

    Burung(int x, int y, int tinggi_lompat, int gravitasi, char model, int score = 0, int score_inc = 1): x(x), y(y), tinggi_lompat(tinggi_lompat), gravitasi(gravitasi), model(model), score(score), score_inc(score_inc){
    }

    void Lompat() {
      this-> y -= this->tinggi_lompat;
      if (this-> y < 0) {
        this->die = true;
      }
    }

    void Gambar(Tampilan::Layar &layar) {
      layar.ganti(this->x, this->y, this->model);
    }

    void Gravitasi(int floor_y) {
      this->y -= this->gravitasi;
      if (this->y >= floor_y) {
        this->die = true;
      }
    }

    void Die() {
      this->die = true;
    }

    bool IsDie() {
      return this->die;
    }
  };

  class Pilar {
    private:
      char model;
      int tinggi;
      int x;
      struct Gap {int y1; int y2;} gap;

    public:
      Pilar(int x, int tinggi, Gap gap, char model): x(x), tinggi(tinggi), gap(gap), model(model) {
      }

      Pilar(int x, int tinggi, int max_gap, char model): x(x), tinggi(tinggi), model(model) {
        this->GenerateRandomLevel(max_gap);
      }

      int GetX() {
        return this->x;
      }
      
      void SetX(int new_value) {
        this->x = new_value;
      }

      void GenerateRandomLevel(int minimum_gap) {
        int gap_size = minimum_gap + std::rand() % (this->tinggi - minimum_gap + 1);
        int gap_top = std::rand() % (this->tinggi - gap_size + 1);

        this->gap.y1 = gap_top;
        this->gap.y2 = gap_top + minimum_gap;
      }

      void Gambar(Tampilan::Layar &layar) {
        for (int y = 0; y < this->tinggi; y++) {
          if ((this->gap.y1 > y) || (this->gap.y2 < y)) {
            layar.ganti(this->x, y, model);
          }
      }
      }

      bool kena_burung(Burung &burung) {
        if (this->x == burung.GetX()) {
          if ((this->gap.y1 > burung.GetY()) || (this->gap.y2 < burung.GetY())) {
            return true;
          }
          burung.AddScore();
        }
        return false;
      }

      void MoveX(int distance) {
        this->x += distance;
      }
  };

  class Pilars {
    private:
    std::vector<Pilar> pilars;
    int banyak_pilar;
    int minimum_gap;
    int movement;
    Tampilan::Layar & layar;


    public:
    Pilars(int banyak_pilar, Pilar pilar, int interval_distance, int minimum_gap, int movement, Tampilan::Layar &layar): banyak_pilar(banyak_pilar), minimum_gap(minimum_gap), movement(movement), layar(layar) {

      int interval_buf = 0;

      for (int i = 0; i < banyak_pilar; i++) {
        this->pilars.push_back(pilar);
        pilar.GenerateRandomLevel(minimum_gap);
        this->pilars[i].MoveX(interval_buf);
        interval_buf+=interval_distance;
      }
    }

    void Move(int spawn_x, int despawn_x) {
      for (Pilar &pilar: this->pilars) {
        pilar.MoveX(movement);
        if (pilar.GetX() == despawn_x) {
          pilar.SetX(spawn_x);
        }
      }
    }

    void GambarSemua() {
      for (Pilar &pilar: this->pilars) {
        if (!((pilar.GetX() >= layar.GetLebar()) || (pilar.GetX() < 0))) {
          pilar.Gambar(layar);
        }
      }
    }

    bool kena_burung(Burung &burung) {
      for (Pilar &pilar: this->pilars) {
        if (pilar.kena_burung(burung) == true) {
          return true;
        }
      }
      return false;
    }
  };

  void GameOver(int score) {
    Tampilan::Clear();
    std::cout << "Game Over" << std::endl;
    std::cout << "=============================" << std::endl;
    std::cout << "Score: " << score << std::endl;
  }
};

int main() {
  Tampilan::Layar layar = Tampilan::Layar(50, 10, '.');
  Game::Burung burung = Game::Burung(layar.CenterX(), layar.CenterY(), 2, -1, '%');
  Game::Pilar pilar = Game::Pilar(layar.GetLebar(), layar.GetTinggi(), layar.GetTinggi(), '|');
  Game::Pilars pilars = Game::Pilars(10, pilar, 4, 3, -1, layar);

  char key_press = 255;

  int level = 1;

  std::cout << "masukkan level: ";
  std::cin >> level;

  while(!burung.IsDie()) {
    /* menampilkan objek */
    Tampilan::Clear();
    layar.Clear();
    pilars.GambarSemua();
    burung.Gambar(layar);
    layar.print();


    if (kbhit()) { //cek jika ada tombol yang ditekan
      key_press = getch(); //keypress input

      if ((key_press == 'w') || (key_press == 'W')) {
        burung.Lompat();
        key_press = 255; //reset key_press
      }
    }

    burung.Gravitasi(layar.GetTinggi());
    pilars.Move(layar.GetLebar() - 1, 0);

    if (pilars.kena_burung(burung)) {
      burung.Die();
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000/level));
  }

  Game::GameOver(burung.GetScore());

  if (burung.GetScore() < 5) {
    std::cout << "Latihan lagi ya!!!!";
  }
  else if (burung.GetScore() < 10) {
    std::cout << "Kamu hebat!!!!";
  }
  else {
    std::cout << "AMAZING!!!";
  }
  
  std::cin.get();

  return 0;
}
